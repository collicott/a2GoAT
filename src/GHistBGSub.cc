#include "GHistBGSub.h"
#include "GTreeTagger.h"

using namespace std;


Double_t    GHistBGSub::cutPromptMin  = -1000000;
Double_t    GHistBGSub::cutPromptMax  =  1000000;
std::vector<Double_t>     GHistBGSub::cutRandMin;
std::vector<Double_t>     GHistBGSub::cutRandMax;
Double_t    GHistBGSub::backgroundSubstractionFactor  = 0;

void    GHistBGSub::InitCuts(const Double_t PromptMin, const Double_t PromptMax, const Double_t RandMin, const Double_t RandMax)
{
    cutPromptMin    = PromptMin;
    cutPromptMax    = PromptMax;
    cutRandMin.assign(1, RandMin);
    cutRandMax.assign(1, RandMax);
    backgroundSubstractionFactor = (PromptMax - PromptMin)/(RandMax - RandMin);
}

void    GHistBGSub::AddRandCut(const Double_t RandMin, const Double_t RandMax)
{
    cutRandMin.push_back(RandMin);
    cutRandMax.push_back(RandMax);
    backgroundSubstractionFactor = cutRandMax[0] - cutRandMin[0];
    for(int i=1; i<cutRandMin.size(); i++)
        backgroundSubstractionFactor += cutRandMax[i] - cutRandMin[i];
    backgroundSubstractionFactor    = (cutPromptMax - cutPromptMin)/backgroundSubstractionFactor;
}






GHistBGSub::GHistBGSub(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram) :
    GHistScaCor(name, title, nbinsx, xlow, xup, linkHistogram),
    rand(GetNRandCuts())
{
    rand.SetOwner();
    for(int i=0; i<GetNRandCuts(); i++)
    {
        gROOT->cd();
        GHistScaCor*    hist_rand = new GHistScaCor(TString(GetName()).Append("_rand").Append(TString::Itoa(i, 10)).Data(),
                                                    TString(GetTitle()).Append(" rand").Append(TString::Itoa(i, 10)).Data(),
                                                    nbinsx, xlow, xup,
                                                    kFALSE,
                                                    TString::Itoa(i,10).Prepend("RandomWindow").Data());
        rand.AddAtFree(hist_rand);
    }
}

GHistBGSub::GHistBGSub(const GHistBGSub& obj) :
    GHistScaCor(obj),
    rand(obj.GetNRandCuts())
{
    rand.SetOwner();
    for(int i=0; i<GetNRandCuts(); i++)
    {
        gROOT->cd();
        GHistScaCor*    hist_rand = new GHistScaCor(*((GHistScaCor*)obj.rand.At(i)));
        rand.AddAtFree(hist_rand);
    }
}

GHistBGSub::~GHistBGSub()
{
}

void    GHistBGSub::Reset(Option_t* option)
{
    GHistScaCor::Reset(option);
    TIter   iter(&rand);
    GHistScaCor*    hist;
    while(hist=(GHistScaCor*)iter.Next())
        hist->Reset(option);
}

void    GHistBGSub::ExpandRand(const Int_t newSize)
{
    while(rand.GetEntriesFast()<newSize)
    {
        gROOT->cd();
        GHistScaCor*    hist_rand = new GHistScaCor(TString(GetName()).Append("_rand").Append(TString::Itoa(rand.GetEntriesFast(), 10)).Data(),
                                                    TString(GetTitle()).Append(" rand").Append(TString::Itoa(rand.GetEntriesFast(), 10)).Data(),
                                                    GetNbinsX(),
                                                    GetXaxis()->GetXmin(),
                                                    GetXaxis()->GetXmax(),
                                                    kFALSE,
                                                    TString::Itoa(rand.GetEntriesFast(),10).Prepend("RandomWindow").Data());
        rand.Add(hist_rand);
    }
}

Int_t   GHistBGSub::Fill(const Double_t value, const Double_t taggerTime)
{
    if(taggerTime>=cutPromptMin && taggerTime<=cutPromptMax)
        GHistScaCor::Fill(value);
    for(int i=0; i<GetNRandCuts(); i++)
    {
        if(i>=rand.GetEntriesFast())
            ExpandRand(i+1);
        if(taggerTime>=cutRandMin[i] && taggerTime<=cutRandMax[i])
            ((GHistScaCor*)rand.At(i))->Fill(value);
    }
}

Int_t   GHistBGSub::Fill(const Double_t value, const GTreeTagger& tagger)
{
    for(int i=0; i<tagger.GetNTagged(); i++)
        Fill(value, tagger.GetTagged_t(i));
}

void    GHistBGSub::ScalerReadCorrection(const Double_t CorrectionFactor)
{
    if(GetNRandCuts()==0)
        GHistScaCor::ScalerReadCorrection(CorrectionFactor);
    else
    {
        TString oldName(GetName());
        TString oldTitle(GetTitle());
        SetName(TString(GetName()).Append("_prompt").Data());
        SetTitle(TString(GetTitle()).Append(" prompt").Data());
        GHistScaCor::ScalerReadCorrection(CorrectionFactor);
        SetName(oldName.Data());
        SetTitle(oldTitle.Data());

        TIter   iter(&rand);
        GHistScaCor*    hist;
        while(hist=(GHistScaCor*)iter.Next())
            hist->ScalerReadCorrection(CorrectionFactor);
    }
}

Int_t    GHistBGSub::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(GetNRandCuts()==0)
        GHistScaCor::Write();
    else
    {
        AddOutputDirectory("PromptWindow");
        TString oldName(GetName());
        TString oldTitle(GetTitle());
        SetName(TString(GetName()).Append("_prompt").Data());
        SetTitle(TString(GetTitle()).Append(" prompt").Data());
        TH1D::Write(name, option, bufsize);
        SetName(oldName.Data());
        SetTitle(oldTitle.Data());

        {
            TIter   iter(&rand);
            GHistScaCor*    hist;
            while(hist=(GHistScaCor*)iter.Next())
                hist->Write(name, option, bufsize);
        }

        GHistScaCor*    res = new GHistScaCor(GetName(),
                                              GetTitle(),
                                              GetNbinsX(),
                                              GetXaxis()->GetXmin(),
                                              GetXaxis()->GetXmax(),
                                              kFALSE,
                                              GetOutputDirectoryName().Data());
        res->Add(this);
        if(rand.GetEntriesFast()>1)
        {
            GHistScaCor*    sum = new GHistScaCor(TString(GetName()).Append("_randSum").Data(),
                                                  TString(GetTitle()).Append(" randSum").Data(),
                                                  GetNbinsX(),
                                                  GetXaxis()->GetXmin(),
                                                  GetXaxis()->GetXmax(),
                                                  kFALSE);
            TIter   iter(&rand);
            GHistScaCor*    hist;
            while(hist=(GHistScaCor*)iter.Next())
                sum->Add(hist);
            sum->Write(name, option, bufsize);
            res->Add(sum, -backgroundSubstractionFactor);
        }
        else
            res->Add((GHistScaCor*)rand.At(0), -backgroundSubstractionFactor);

        res->Write(name, option, bufsize);
    }
}







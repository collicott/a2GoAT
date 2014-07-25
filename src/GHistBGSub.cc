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






GHistBGSub::GHistBGSub(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    GHistScaCor(name, title, nbinsx, xlow, xup, linkHistogram, dirName),
    rand()
{
    rand.SetOwner();
}

GHistBGSub::GHistBGSub(const GHistBGSub& obj, Bool_t linkHistogram) :
    GHistScaCor(obj, linkHistogram),
    rand(obj.rand.GetEntriesFast())
{
    rand.SetOwner();
    for(int i=0; i<obj.rand.GetEntriesFast(); i++)
    {
        gROOT->cd();
        GHistScaCor*    hist_rand = new GHistScaCor(*((GHistScaCor*)obj.rand.At(i)), kFALSE);
        rand.AddAtFree(hist_rand);
    }
}

GHistBGSub::~GHistBGSub()
{
}

Bool_t	GHistBGSub::Add(const GHistBGSub* h, Double_t c)
{
    GHistScaCor::Add(h, c);
    for(int i=0; i<h->rand.GetEntriesFast(); i++)
    {
        if(i>=rand.GetEntriesFast())
        {
            gROOT->cd();
            GHistScaCor*    hist_rand = new GHistScaCor(*((GHistScaCor*)h->rand.At(i)), kFALSE);
            hist_rand->SetName(TString(GetName()).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend("_rand")));
            hist_rand->SetTitle(TString(GetTitle()).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend(" rand ")));
            hist_rand->SetOutputDirectory(GetOutputDirectoryName().Data());
            hist_rand->AddOutputDirectory(TString::Itoa(i,10).Prepend("RandomWindow_"));
            rand.AddAtFree(hist_rand);
        }
        else
            ((GHistScaCor*)rand.At(i))->Add((GHistScaCor*)h->rand.At(i), c);
    }
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
                                                    GHistScaCor::GetOutputDirectoryName().Data());
        hist_rand->AddOutputDirectory(TString::Itoa(rand.GetEntriesFast(),10).Prepend("RandomWindow_"));
        rand.Add(hist_rand);
    }
}

Int_t   GHistBGSub::Fill(const Double_t value, const Double_t taggerTime)
{
    if(taggerTime>=cutPromptMin && taggerTime<=cutPromptMax)
        return GHistScaCor::Fill(value);
    for(int i=0; i<GetNRandCuts(); i++)
    {
        if(i>=rand.GetEntriesFast())
            ExpandRand(i+1);
        if(taggerTime>=cutRandMin[i] && taggerTime<=cutRandMax[i])
            return ((GHistScaCor*)rand.At(i))->Fill(value);
    }
}

Int_t   GHistBGSub::Fill(const Double_t value, const GTreeTagger& tagger)
{
    for(int i=0; i<tagger.GetNTagged(); i++)
        Fill(value, tagger.GetTagged_t(i));
}



void    GHistBGSub::ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads)
{
    if(rand.GetEntriesFast()==0)
        GHistScaCor::ScalerReadCorrection(CorrectionFactor, CreateHistogramsForSingleScalerReads);
    else
    {
        TString oldName(GetName());
        TString oldTitle(GetTitle());
        GHistScaCor::SetName(TString(GetName()).Append("_prompt").Data());
        GHistScaCor::SetTitle(TString(GetTitle()).Append(" prompt").Data());
        GHistScaCor::ScalerReadCorrection(CorrectionFactor, CreateHistogramsForSingleScalerReads);
        GHistScaCor::SetName(oldName.Data());
        GHistScaCor::SetTitle(oldTitle.Data());

        TIter   iter(&rand);
        GHistScaCor*    hist;
        while(hist=(GHistScaCor*)iter.Next())
            hist->ScalerReadCorrection(CorrectionFactor, CreateHistogramsForSingleScalerReads);
    }
}

void    GHistBGSub::AddOutputDirectory(const TString& directoryName)
{
    GHistScaCor::AddOutputDirectory(directoryName);
    for(int i=0; i<rand.GetEntriesFast(); i++)
    {
        ((GHistLinked*)rand.At(i))->SetOutputDirectory(GHistLinked::GetOutputDirectoryName());
        ((GHistLinked*)rand.At(i))->AddOutputDirectory(TString::Itoa(i,10).Prepend("RandomWindow_"));
    }
}

void    GHistBGSub::SetOutputDirectory(const TString& directoryName)
{
    GHistScaCor::SetOutputDirectory(directoryName);
    for(int i=0; i<rand.GetEntriesFast(); i++)
    {
        ((GHistLinked*)rand.At(i))->SetOutputDirectory(directoryName);
        ((GHistLinked*)rand.At(i))->AddOutputDirectory(TString::Itoa(i,10).Prepend("RandomWindow_"));
    }
}

void	GHistBGSub::SetName(const char* name)
{
    GHistScaCor::SetName(name);
    for(int i=0; i<rand.GetEntriesFast(); i++)
        ((GHistScaCor*)rand.At(i))->SetName(TString(name).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend("_rand")));
}

void	GHistBGSub::SetTitle(const char* title)
{
    GHistScaCor::SetTitle(title);
    for(int i=0; i<rand.GetEntriesFast(); i++)
        ((GHistScaCor*)rand.At(i))->SetTitle(TString(title).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend(" rand ")));
}

Int_t    GHistBGSub::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(rand.GetEntriesFast()==0)
        return GHistScaCor::Write();

    TString oldName(GetName());
    TString oldTitle(GetTitle());
    TString oldDirectory(GetOutputDirectoryName());
    GHistScaCor::SetName(TString(GetName()).Append("_prompt").Data());
    GHistScaCor::SetTitle(TString(GetTitle()).Append(" prompt").Data());

    GHistScaCor*    res = new GHistScaCor(oldName.Data(),
                                          oldTitle.Data(),
                                          GetNbinsX(),
                                          GetXaxis()->GetXmin(),
                                          GetXaxis()->GetXmax(),
                                          kFALSE,
                                          GetOutputDirectoryName().Data());

    GHistScaCor::AddOutputDirectory("PromptWindow");
    GHistScaCor::Write(name, option, bufsize);
    GHistScaCor::SetOutputDirectory(oldDirectory.Data());
    GHistScaCor::SetName(oldName.Data());
    GHistScaCor::SetTitle(oldTitle.Data());

    {
        TIter   iter(&rand);
        GHistScaCor*    hist;
        while(hist=(GHistScaCor*)iter.Next())
            hist->Write(name, option, bufsize);
    }

    res->Add(this);
    if(rand.GetEntriesFast()>1)
    {
        GHistScaCor*    sum = new GHistScaCor(TString(GetName()).Append("_randSum").Data(),
                                              TString(GetTitle()).Append(" randSum").Data(),
                                              GetNbinsX(),
                                              GetXaxis()->GetXmin(),
                                              GetXaxis()->GetXmax(),
                                              kFALSE,
                                              GetOutputDirectoryName().Data());

        sum->AddOutputDirectory("RandomWindowSum");
        TIter   iter(&rand);
        GHistScaCor*    hist;
        while(hist=(GHistScaCor*)iter.Next())
            sum->Add(hist);
        sum->Write(name, option, bufsize);
        res->Add(sum, -backgroundSubstractionFactor);
        sum->Delete();
    }
    else
        res->Add((GHistScaCor*)rand.At(0), -backgroundSubstractionFactor);

    res->Write(name, option, bufsize);
    res->Delete();
}







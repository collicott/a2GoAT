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





GHistBGSub::GHistBGSub() :
    GHistTaggerBinning(),
    rand()
{
    rand.SetOwner();
}

GHistBGSub::GHistBGSub(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    GHistTaggerBinning(name, title, nbinsx, xlow, xup, linkHistogram, dirName),
    rand()
{
    rand.SetOwner();
}

GHistBGSub::~GHistBGSub()
{
}

Bool_t	GHistBGSub::Add(const GHistBGSub* h, Double_t c)
{
    GHistTaggerBinning::Add(h, c);
    for(int i=0; i<h->rand.GetEntriesFast(); i++)
    {
        if(i>=rand.GetEntriesFast())
        {
            gROOT->cd();
            GHistTaggerBinning*    hist_rand = new GHistTaggerBinning(TString(GetName()).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend("_rand")),
                                                                      TString(GetTitle()).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend(" rand ")),
                                                                      GetNbinsX(),
                                                                      GetXaxis()->GetXmin(),
                                                                      GetXaxis()->GetXmax(),
                                                                      kFALSE,
                                                                      GetOutputDirectoryName().Data());
            hist_rand->AddOutputDirectory(TString::Itoa(i,10).Prepend("RandomWindow_"));
            rand.AddAtFree(hist_rand);
        }
        ((GHistTaggerBinning*)rand.At(i))->Add((GHistTaggerBinning*)h->rand.At(i), c);
    }
}

void    GHistBGSub::Reset(Option_t* option)
{
    GHistTaggerBinning::Reset(option);
    TIter   iter(&rand);
    GHistTaggerBinning*    hist;
    while(hist=(GHistTaggerBinning*)iter.Next())
        hist->Reset(option);
}

void    GHistBGSub::ExpandRand(const Int_t newSize)
{
    while(rand.GetEntriesFast()<newSize)
    {
        gROOT->cd();
        GHistTaggerBinning*    hist_rand = new GHistTaggerBinning(TString(GetName()).Append("_rand").Append(TString::Itoa(rand.GetEntriesFast(), 10)).Data(),
                                                    TString(GetTitle()).Append(" rand").Append(TString::Itoa(rand.GetEntriesFast(), 10)).Data(),
                                                    GetNbinsX(),
                                                    GetXaxis()->GetXmin(),
                                                    GetXaxis()->GetXmax(),
                                                    kFALSE,
                                                    GHistTaggerBinning::GetOutputDirectoryName().Data());
        hist_rand->AddOutputDirectory(TString::Itoa(rand.GetEntriesFast(),10).Prepend("RandomWindow_"));
        rand.Add(hist_rand);
    }
}

Int_t   GHistBGSub::Fill(const Double_t value, const Double_t taggerTime, const Int_t taggerChannel)
{
    if(taggerTime>=cutPromptMin && taggerTime<=cutPromptMax)
        return GHistTaggerBinning::Fill(value, taggerChannel);
    for(int i=0; i<GetNRandCuts(); i++)
    {
        if(i>=rand.GetEntriesFast())
            ExpandRand(i+1);
        if(taggerTime>=cutRandMin[i] && taggerTime<=cutRandMax[i])
            return ((GHistTaggerBinning*)rand.At(i))->Fill(value, taggerChannel);
    }
}

Int_t   GHistBGSub::Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t DoTaggerBinning)
{
    for(int i=0; i<tagger.GetNTagged(); i++)
    {
        if(DoTaggerBinning == kTRUE)
            Fill(value, tagger.GetTagged_t(i), tagger.GetTagged_ch(i));
        else
            Fill(value, tagger.GetTagged_t(i));
    }
}

void    GHistBGSub::AddOutputDirectory(const TString& directoryName)
{
    GHistTaggerBinning::AddOutputDirectory(directoryName);
    for(int i=0; i<rand.GetEntriesFast(); i++)
    {
        ((GHistLinked*)rand.At(i))->SetOutputDirectory(GHistLinked::GetOutputDirectoryName());
        ((GHistLinked*)rand.At(i))->AddOutputDirectory(TString::Itoa(i,10).Prepend("RandomWindow_"));
    }
}

void    GHistBGSub::SetOutputDirectory(const TString& directoryName)
{
    GHistTaggerBinning::SetOutputDirectory(directoryName);
    for(int i=0; i<rand.GetEntriesFast(); i++)
    {
        ((GHistLinked*)rand.At(i))->SetOutputDirectory(directoryName);
        ((GHistLinked*)rand.At(i))->AddOutputDirectory(TString::Itoa(i,10).Prepend("RandomWindow_"));
    }
}

void	GHistBGSub::SetName(const char* name)
{
    GHistTaggerBinning::SetName(name);
    for(int i=0; i<rand.GetEntriesFast(); i++)
        ((GHistTaggerBinning*)rand.At(i))->SetName(TString(name).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend("_rand")));
}

void	GHistBGSub::SetTitle(const char* title)
{
    GHistTaggerBinning::SetTitle(title);
    for(int i=0; i<rand.GetEntriesFast(); i++)
        ((GHistTaggerBinning*)rand.At(i))->SetTitle(TString(title).Append(TString::Itoa(rand.GetEntriesFast(),10).Prepend(" rand ")));
}

Int_t    GHistBGSub::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(rand.GetEntriesFast()==0)
        return GHistTaggerBinning::Write();

    TString oldName(GetName());
    TString oldTitle(GetTitle());
    TString oldDirectory(GetOutputDirectoryName());
    GHistTaggerBinning::SetName(TString(GetName()).Append("_prompt").Data());
    GHistTaggerBinning::SetTitle(TString(GetTitle()).Append(" prompt").Data());

    GHistTaggerBinning*    res = new GHistTaggerBinning(oldName.Data(),
                                          oldTitle.Data(),
                                          GetNbinsX(),
                                          GetXaxis()->GetXmin(),
                                          GetXaxis()->GetXmax(),
                                          kFALSE,
                                          GetOutputDirectoryName().Data());

    GHistTaggerBinning::AddOutputDirectory("PromptWindow");
    GHistTaggerBinning::Write(name, option, bufsize);
    {
        TIter   iter(&rand);
        GHistTaggerBinning*    hist;
        while(hist=(GHistTaggerBinning*)iter.Next())
            hist->Write(name, option, bufsize);
    }
    res->Add(this);
    GHistTaggerBinning::SetOutputDirectory(oldDirectory.Data());
    GHistTaggerBinning::SetName(oldName.Data());
    GHistTaggerBinning::SetTitle(oldTitle.Data());

    if(rand.GetEntriesFast()>1)
    {
        GHistTaggerBinning*    sum = new GHistTaggerBinning(TString(GetName()).Append("_randSum").Data(),
                                              TString(GetTitle()).Append(" randSum").Data(),
                                              GetNbinsX(),
                                              GetXaxis()->GetXmin(),
                                              GetXaxis()->GetXmax(),
                                              kFALSE,
                                              GetOutputDirectoryName().Data());

        sum->AddOutputDirectory("RandomWindowSum");
        TIter   iter(&rand);
        GHistTaggerBinning*    hist;
        while(hist=(GHistTaggerBinning*)iter.Next())
            sum->Add(hist);
        sum->Write(name, option, bufsize);
        res->Add(sum, -backgroundSubstractionFactor);
        sum->Delete();
    }
    else
        res->Add((GHistTaggerBinning*)rand.At(0), -backgroundSubstractionFactor);

    res->Write(name, option, bufsize);
    res->Delete();
}







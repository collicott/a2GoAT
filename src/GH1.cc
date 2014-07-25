#include "GH1.h"
#include "GTreeTagger.h"


GH1::GH1(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    GHistBGSub(name, title, nbinsx, xlow, xup, linkHistogram, dirName),
    bin(352)
{
    bin.SetOwner();
}

GH1::GH1(const GH1& obj, Bool_t linkHistogram) :
    GHistBGSub(obj, linkHistogram),
    bin(352)
{
    bin.SetOwner();
    for(int i=0; i<obj.bin.GetEntriesFast(); i++)
    {
        gROOT->cd();
        GHistBGSub*    hist = new GHistBGSub(*((GHistBGSub*)obj.bin.At(i)), kFALSE);
        hist->SetName(TString(GetName()).Append("_bin").Append(TString::Itoa(i+1, 10)).Data());
        hist->SetTitle(TString(GetTitle()).Append(" bin").Append(TString::Itoa(i+1, 10)).Data());
        hist->SetOutputDirectory(GetOutputDirectoryName().Data());
        hist->AddOutputDirectory("taggerBinning");
        hist->AddOutputDirectory(TString::Itoa(i+1,10).Prepend("channel_"));
        bin.AddAtFree(hist);
    }
}

GH1::~GH1()
{

}

void    GH1::ExpandBin(const Int_t newSize)
{
    while(bin.GetEntriesFast()<newSize)
    {
        gROOT->cd();
        GHistBGSub*    hist = new GHistBGSub(TString(GetName()).Append("_bin").Append(TString::Itoa(bin.GetEntriesFast()+1, 10)).Data(),
                                             TString(GetTitle()).Append(" bin").Append(TString::Itoa(bin.GetEntriesFast()+1, 10)).Data(),
                                             GetNbinsX(),
                                             GetXaxis()->GetXmin(),
                                             GetXaxis()->GetXmax(),
                                             kFALSE,
                                             GHistBGSub::GetOutputDirectoryName().Data());
        hist->AddOutputDirectory("taggerBinning");
        hist->AddOutputDirectory(TString::Itoa(bin.GetEntriesFast()+1,10).Prepend("channel_"));
        bin.Add(hist);
    }
}

Bool_t	GH1::Add(const GH1* h, Double_t c)
{
    GHistBGSub::Add(h, c);
    for(int i=0; i<h->bin.GetEntriesFast(); i++)
    {
        if(i>=GetNRandCuts())
        {
            gROOT->cd();
            GHistBGSub*    hist = new GHistBGSub(*((GHistBGSub*)h->bin.At(i)), kFALSE);
            hist->SetName(TString(GetName()).Append(TString::Itoa(bin.GetEntriesFast(),10).Prepend("_bin")));
            hist->SetTitle(TString(GetTitle()).Append(TString::Itoa(bin.GetEntriesFast(),10).Prepend(" bin ")));
            hist->SetOutputDirectory(GetOutputDirectoryName().Data());
            ((GHistBGSub*)bin.At(i))->AddOutputDirectory("taggerBinning");
            ((GHistBGSub*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1,10).Prepend("channel_"));
            bin.AddAtFree(hist);
        }
        else
            ((GHistBGSub*)bin.At(i))->Add((GHistBGSub*)h->bin.At(i), c);
    }
}

void    GH1::AddOutputDirectory(const TString& directoryName)
{
    GHistBGSub::AddOutputDirectory(directoryName);
    for(int i=0; i<bin.GetEntriesFast(); i++)
    {
        ((GHistBGSub*)bin.At(i))->SetOutputDirectory(GetOutputDirectoryName().Data());
        ((GHistBGSub*)bin.At(i))->AddOutputDirectory("taggerBinning");
        ((GHistBGSub*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1,10).Prepend("channel_"));
    }
}

void    GH1::SetOutputDirectory(const TString& directoryName)
{
    GHistBGSub::SetOutputDirectory(directoryName);
    for(int i=0; i<bin.GetEntriesFast(); i++)
    {
        ((GHistBGSub*)bin.At(i))->SetOutputDirectory(directoryName);
        ((GHistBGSub*)bin.At(i))->AddOutputDirectory("taggerBinning");
        ((GHistBGSub*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1,10).Prepend("channel_"));
    }
}

void    GH1::Reset(Option_t* option)
{
    GHistBGSub::Reset(option);
}

Int_t   GH1::Fill(const Double_t value, const Double_t taggerTime, const Int_t taggerChannel)
{
    if(taggerChannel==0)
        return GHistBGSub::Fill(value, taggerTime);
    if(taggerChannel>bin.GetEntriesFast())
        ExpandBin(taggerChannel);
    ((GHistBGSub*)bin.At(taggerChannel-1))->Fill(value, taggerTime);
}

Int_t   GH1::Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t CreateHistogramsForTaggerBinning)
{
    for(int i=0; i<tagger.GetNTagged(); i++)
    {
        if(CreateHistogramsForTaggerBinning)
            Fill(value, tagger.GetTagged_t(i), tagger.GetTagged_ch(i));
        else
            Fill(value, tagger.GetTagged_t(i));
    }
}

void    GH1::ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads)
{
    GHistBGSub::ScalerReadCorrection(CorrectionFactor, CreateHistogramsForSingleScalerReads);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistBGSub*)bin.At(i))->ScalerReadCorrection(CorrectionFactor, CreateHistogramsForSingleScalerReads);
}

void	GH1::SetName(const char* name)
{
    GHistBGSub::SetName(name);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistBGSub*)bin.At(i))->SetName(TString(GetName()).Append("_bin").Append(TString::Itoa(i+1, 10)).Data());
}

void	GH1::SetTitle(const char* title)
{
    GHistBGSub::SetTitle(title);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistBGSub*)bin.At(i))->SetTitle(TString(GetTitle()).Append(" bin ").Append(TString::Itoa(i+1, 10)).Data());
}

Int_t   GH1::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(bin.GetEntriesFast()==0)
    {
        return  GHistBGSub::Write(name, option, bufsize);
    }

    TString oldName(GetName());
    TString oldTitle(GetTitle());
    TString oldDirectory(GetOutputDirectoryName());
    GHistBGSub::SetName(TString(GetName()).Append("_bin0").Data());
    GHistBGSub::SetTitle(TString(GetTitle()).Append(" bin 0").Data());

    GHistBGSub*    res = new GHistBGSub(oldName.Data(),
                                        oldTitle.Data(),
                                        GetNbinsX(),
                                        GetXaxis()->GetXmin(),
                                        GetXaxis()->GetXmax(),
                                        kFALSE,
                                        GetOutputDirectoryName().Data());

    GHistBGSub::AddOutputDirectory("taggerBinning");
    GHistBGSub::AddOutputDirectory("channel_0");
    GHistBGSub::Write(name, option, bufsize);
    res->Add(this);
    {
        TIter   iter(&bin);
        GHistBGSub*    hist;
        while(hist=(GHistBGSub*)iter.Next())
        {
            hist->Write(name, option, bufsize);
            res->Add(hist);
        }
    }

    res->Write(name, option, bufsize);
    res->Delete();

    GHistBGSub::SetName(oldName.Data());
    GHistBGSub::SetTitle(oldTitle.Data());
    GHistBGSub::SetOutputDirectory(oldDirectory.Data());

}


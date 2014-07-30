#include "GH1.h"
#include "GTreeTagger.h"


GH1::GH1(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    GHistLinked(name, title, nbinsx, xlow, xup, linkHistogram, dirName),
    bin(352)
{
    bin.SetOwner();
}

GH1::GH1(const GH1& obj, Bool_t linkHistogram) :
    GHistLinked(obj, linkHistogram),
    bin(352)
{
    bin.SetOwner();
    for(int i=0; i<obj.bin.GetEntriesFast(); i++)
    {
        gROOT->cd();
        GHistLinked*    hist = new GHistLinked(*((GHistLinked*)obj.bin.At(i)), kFALSE);
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
        GHistLinked*    hist = new GHistLinked(TString(GetName()).Append("_bin").Append(TString::Itoa(bin.GetEntriesFast()+1, 10)).Data(),
                                             TString(GetTitle()).Append(" bin").Append(TString::Itoa(bin.GetEntriesFast()+1, 10)).Data(),
                                             GetNbinsX(),
                                             GetXaxis()->GetXmin(),
                                             GetXaxis()->GetXmax(),
                                             kFALSE,
                                             GHistLinked::GetOutputDirectoryName().Data());
        hist->AddOutputDirectory("taggerBinning");
        hist->AddOutputDirectory(TString::Itoa(bin.GetEntriesFast()+1,10).Prepend("channel_"));
        bin.Add(hist);
    }
}

Bool_t	GH1::Add(const GH1* h, Double_t c)
{
    GHistLinked::Add(h, c);
    for(int i=0; i<h->bin.GetEntriesFast(); i++)
    {
        if(i>=bin.GetEntriesFast())
        {
            gROOT->cd();
            GHistLinked*    hist = new GHistLinked(*((GHistLinked*)h->bin.At(i)), kFALSE);
            hist->SetName(TString(GetName()).Append(TString::Itoa(bin.GetEntriesFast(),10).Prepend("_bin")));
            hist->SetTitle(TString(GetTitle()).Append(TString::Itoa(bin.GetEntriesFast(),10).Prepend(" bin ")));
            hist->SetOutputDirectory(GetOutputDirectoryName().Data());
            ((GHistLinked*)bin.At(i))->AddOutputDirectory("taggerBinning");
            ((GHistLinked*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1,10).Prepend("channel_"));
            bin.AddAtFree(hist);
        }
        else
            ((GHistLinked*)bin.At(i))->Add((GHistLinked*)h->bin.At(i), c);
    }
}

void    GH1::AddOutputDirectory(const TString& directoryName)
{
    GHistLinked::AddOutputDirectory(directoryName);
    for(int i=0; i<bin.GetEntriesFast(); i++)
    {
        ((GHistLinked*)bin.At(i))->SetOutputDirectory(GetOutputDirectoryName().Data());
        ((GHistLinked*)bin.At(i))->AddOutputDirectory("taggerBinning");
        ((GHistLinked*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1,10).Prepend("channel_"));
    }
}

void    GH1::SetOutputDirectory(const TString& directoryName)
{
    GHistLinked::SetOutputDirectory(directoryName);
    for(int i=0; i<bin.GetEntriesFast(); i++)
    {
        ((GHistLinked*)bin.At(i))->SetOutputDirectory(directoryName);
        ((GHistLinked*)bin.At(i))->AddOutputDirectory("taggerBinning");
        ((GHistLinked*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1,10).Prepend("channel_"));
    }
}

void    GH1::Reset(Option_t* option)
{
    GHistLinked::Reset(option);
}

Int_t   GH1::Fill(const Double_t value, const Int_t taggerChannel)
{
    if(taggerChannel==0)
        return GHistLinked::Fill(value);
    if(taggerChannel>bin.GetEntriesFast())
        ExpandBin(taggerChannel);
    ((GHistLinked*)bin.At(taggerChannel-1))->Fill(value);
}

Int_t   GH1::Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t CreateHistogramsForTaggerBinning)
{
    for(int i=0; i<tagger.GetNTagged(); i++)
    {
        if(CreateHistogramsForTaggerBinning)
            Fill(value, tagger.GetTagged_ch(i));
        else
            Fill(value);
    }
}

void	GH1::SetName(const char* name)
{
    GHistLinked::SetName(name);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistLinked*)bin.At(i))->SetName(TString(GetName()).Append("_bin").Append(TString::Itoa(i+1, 10)).Data());
}

void	GH1::SetTitle(const char* title)
{
    GHistLinked::SetTitle(title);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistLinked*)bin.At(i))->SetTitle(TString(GetTitle()).Append(" bin ").Append(TString::Itoa(i+1, 10)).Data());
}

Int_t   GH1::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(bin.GetEntriesFast()==0)
    {
        return  GHistLinked::Write(name, option, bufsize);
    }

    TString oldName(GetName());
    TString oldTitle(GetTitle());
    TString oldDirectory(GetOutputDirectoryName());
    GHistLinked::SetName(TString(GetName()).Append("_bin0").Data());
    GHistLinked::SetTitle(TString(GetTitle()).Append(" bin 0").Data());

    GHistLinked*    res = new GHistLinked(oldName.Data(),
                                        oldTitle.Data(),
                                        GetNbinsX(),
                                        GetXaxis()->GetXmin(),
                                        GetXaxis()->GetXmax(),
                                        kFALSE,
                                        GetOutputDirectoryName().Data());

    GHistLinked::AddOutputDirectory(TString("taggerBinning"));
    GHistLinked::AddOutputDirectory(TString("channel_0"));
    GHistLinked::Write(name, option, bufsize);

    res->Add(this);
    {
        TIter   iter(&bin);
        GHistLinked*    hist;
        while(hist=(GHistLinked*)iter.Next())
        {
            hist->Write(name, option, bufsize);
            res->Add(hist);
        }
    }

    res->Write(name, option, bufsize);
    res->Delete();

    GHistLinked::SetName(oldName.Data());
    GHistLinked::SetTitle(oldTitle.Data());
    GHistLinked::SetOutputDirectory(oldDirectory.Data());

}


#include "GHistTaggerBinning.h"
#include "GTreeTagger.h"

Int_t   GHistTaggerBinning::TaggerBinningRangeMin = 0;
Int_t   GHistTaggerBinning::TaggerBinningRangeMax = -1;

void    GHistTaggerBinning::InitTaggerBinning(const Int_t min, const Int_t max)
{
    TaggerBinningRangeMin = min;
    TaggerBinningRangeMax = max;
}



GHistTaggerBinning::GHistTaggerBinning() :
    GHistScaCor(),
    bin()
{
    SetDirectory(gROOT);
    bin.SetOwner();
}

GHistTaggerBinning::GHistTaggerBinning(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    GHistScaCor(name, title, nbinsx, xlow, xup, linkHistogram, dirName),
    bin()
{
    SetDirectory(gROOT);
    bin.SetOwner();
}

GHistTaggerBinning::~GHistTaggerBinning()
{

}

void    GHistTaggerBinning::ExpandBin(const Int_t newSize)
{
    while(bin.GetEntriesFast()<newSize)
    {
        gROOT->cd();
        GHistScaCor*    hist = new GHistScaCor(TString(GetName()).Append("_bin").Append(TString::Itoa(bin.GetEntriesFast()+1+TaggerBinningRangeMin, 10)).Data(),
                                             TString(GetTitle()).Append(" bin").Append(TString::Itoa(bin.GetEntriesFast()+1+TaggerBinningRangeMin, 10)).Data(),
                                             GetNbinsX(),
                                             GetXaxis()->GetXmin(),
                                             GetXaxis()->GetXmax(),
                                             kFALSE,
                                             GHistScaCor::GetOutputDirectoryName().Data());
        hist->AddOutputDirectory("taggerBinning");
        hist->AddOutputDirectory(TString::Itoa(bin.GetEntriesFast()+1+TaggerBinningRangeMin,10).Prepend("channel_"));
        bin.Add(hist);
    }
}

Bool_t	GHistTaggerBinning::Add(const GHistTaggerBinning* h, Double_t c)
{
    GHistScaCor::Add(h, c);
    for(int i=0; i<h->bin.GetEntriesFast(); i++)
    {
        if(i>=bin.GetEntriesFast())
        {
            gROOT->cd();
            GHistScaCor*    hist = new GHistScaCor(TString(GetName()).Append(TString::Itoa(bin.GetEntriesFast()+TaggerBinningRangeMin,10).Prepend("_bin")).Data(),
                                                   TString(GetTitle()).Append(TString::Itoa(bin.GetEntriesFast()+TaggerBinningRangeMin,10).Prepend(" bin ")).Data(),
                                                   GetNbinsX(),
                                                   GetXaxis()->GetXmin(),
                                                   GetXaxis()->GetXmax(),
                                                   kFALSE,
                                                   GetOutputDirectoryName().Data());
            hist->AddOutputDirectory("taggerBinning");
            hist->AddOutputDirectory(TString::Itoa(i+1+TaggerBinningRangeMin,10).Prepend("channel_"));
            bin.AddAtFree(hist);
        }
        ((GHistScaCor*)bin.At(i))->Add((GHistScaCor*)h->bin.At(i), c);
    }
}

void    GHistTaggerBinning::AddOutputDirectory(const TString& directoryName)
{
    GHistScaCor::AddOutputDirectory(directoryName);
    for(int i=0; i<bin.GetEntriesFast(); i++)
    {
        ((GHistScaCor*)bin.At(i))->SetOutputDirectory(GetOutputDirectoryName().Data());
        ((GHistScaCor*)bin.At(i))->AddOutputDirectory("taggerBinning");
        ((GHistScaCor*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1+TaggerBinningRangeMin,10).Prepend("channel_"));
    }
}

void    GHistTaggerBinning::SetOutputDirectory(const TString& directoryName)
{
    GHistScaCor::SetOutputDirectory(directoryName);
    for(int i=0; i<bin.GetEntriesFast(); i++)
    {
        ((GHistScaCor*)bin.At(i))->SetOutputDirectory(directoryName);
        ((GHistScaCor*)bin.At(i))->AddOutputDirectory("taggerBinning");
        ((GHistScaCor*)bin.At(i))->AddOutputDirectory(TString::Itoa(i+1+TaggerBinningRangeMin,10).Prepend("channel_"));
    }
}

void    GHistTaggerBinning::Reset(Option_t* option)
{
    GHistScaCor::Reset(option);
}

Int_t   GHistTaggerBinning::Fill(const Double_t value, const Int_t taggerChannel)
{
    if(TaggerBinningRangeMax==-1)
    {
        if(taggerChannel==0)
            return GHistScaCor::Fill(value);
        if(taggerChannel>bin.GetEntriesFast())
            ExpandBin(taggerChannel);
        ((GHistScaCor*)bin.At(taggerChannel-1))->Fill(value);
    }
    else
    {
        if(taggerChannel<TaggerBinningRangeMin || taggerChannel>TaggerBinningRangeMax)
            return 0;
        if(taggerChannel==TaggerBinningRangeMin)
            return GHistScaCor::Fill(value);
        if(taggerChannel>(bin.GetEntriesFast()+TaggerBinningRangeMin))
            ExpandBin(taggerChannel-TaggerBinningRangeMin);
        ((GHistScaCor*)bin.At(taggerChannel-TaggerBinningRangeMin-1))->Fill(value);
    }
}

Int_t   GHistTaggerBinning::Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t CreateHistogramsForTaggerBinning)
{
    for(int i=0; i<tagger.GetNTagged(); i++)
    {
        if(CreateHistogramsForTaggerBinning)
            Fill(value, tagger.GetTagged_ch(i));
        else
            Fill(value);
    }
}

void    GHistTaggerBinning::ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads)
{
    GHistScaCor::ScalerReadCorrection(CorrectionFactor, CreateHistogramsForSingleScalerReads);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistScaCor*)bin.At(i))->ScalerReadCorrection(CorrectionFactor, CreateHistogramsForSingleScalerReads);
}

void	GHistTaggerBinning::SetBins(Int_t nx, Double_t xmin, Double_t xmax)
{
    GHistScaCor::SetBins(nx, xmin, xmax);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistScaCor*)bin.At(i))->SetBins(nx, xmin, xmax);
}

void	GHistTaggerBinning::SetName(const char* name)
{
    GHistScaCor::SetName(name);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistScaCor*)bin.At(i))->SetName(TString(GetName()).Append("_bin").Append(TString::Itoa(i+1+TaggerBinningRangeMin, 10)).Data());
}

void	GHistTaggerBinning::SetTitle(const char* title)
{
    GHistScaCor::SetTitle(title);
    for(int i=0; i<bin.GetEntriesFast(); i++)
        ((GHistScaCor*)bin.At(i))->SetTitle(TString(GetTitle()).Append(" bin ").Append(TString::Itoa(i+1+TaggerBinningRangeMin, 10)).Data());
}

Int_t   GHistTaggerBinning::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(bin.GetEntriesFast()==0)
    {
        return  GHistScaCor::Write(name, option, bufsize);
    }

    TString oldName(GetName());
    TString oldTitle(GetTitle());
    TString oldDirectory(GetOutputDirectoryName());
    GHistScaCor::SetName(TString(GetName()).Append(TString::Itoa(TaggerBinningRangeMin,10).Prepend("_bin")).Data());
    GHistScaCor::SetTitle(TString(GetTitle()).Append(TString::Itoa(TaggerBinningRangeMin,10).Prepend(" bin ")).Data());

    GHistScaCor*    res = new GHistScaCor(oldName.Data(),
                                        oldTitle.Data(),
                                        GetNbinsX(),
                                        GetXaxis()->GetXmin(),
                                        GetXaxis()->GetXmax(),
                                        kFALSE,
                                        GetOutputDirectoryName().Data());

    GHistScaCor::AddOutputDirectory(TString("taggerBinning"));
    GHistScaCor::AddOutputDirectory(TString::Itoa(TaggerBinningRangeMin,10).Prepend("channel_"));
    GHistScaCor::Write(name, option, bufsize);

    res->Add(this);
    {
        TIter   iter(&bin);
        GHistScaCor*    hist;
        while(hist=(GHistScaCor*)iter.Next())
        {
            hist->Write(name, option, bufsize);
            res->Add(hist);
        }
    }

    res->Write(name, option, bufsize);
    res->Delete();

    GHistScaCor::SetName(oldName.Data());
    GHistScaCor::SetTitle(oldTitle.Data());
    GHistScaCor::SetOutputDirectory(oldDirectory.Data());

}


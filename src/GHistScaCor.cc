#include "GHistScaCor.h"

#include <iostream>


Int_t   GHistScaCor::WriteHistogram(GHistLinked& hist, const TString& name, const TString& title, Int_t option, Int_t bufsize)
{
    TString oldName(hist.GetName());
    TString oldTitle(hist.GetTitle());
    hist.SetName(name.Data());
    hist.SetTitle(title.Data());
    Int_t   ret = hist.Write(0, option, bufsize);
    hist.SetName(oldName.Data());
    hist.SetTitle(oldTitle.Data());
    return ret;
}


GHistScaCor::GHistScaCor(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    GHistLinked(name, title, nbinsx, xlow, xup, linkHistogram, dirName),
    accumulated(TString(name).Append("_Acc").Data(),
                TString(title).Append(" Accumulated"),
                nbinsx, xlow, xup,
                kFALSE,
                dirName),
    accumulatedCorrected(TString(name).Append("_AccCor").Data(),
                         TString(title).Append(" Accumulated and Corrected").Data(),
                         nbinsx, xlow, xup,
                         kFALSE,
                         dirName),
    singleScalerReads(128),
    singleScalerReadsCorrected(128),
    corrected(kFALSE)
{
    accumulated.AddOutputDirectory("ScalerCorrection");
    singleScalerReads.SetOwner();
    singleScalerReadsCorrected.SetOwner();
}

GHistScaCor::GHistScaCor(const GHistScaCor& obj, Bool_t linkHistogram) :
    GHistLinked(obj, linkHistogram),
    accumulated(obj.accumulated, kFALSE),
    accumulatedCorrected(obj.accumulatedCorrected, kFALSE),
    singleScalerReads(obj.singleScalerReads.GetEntriesFast()),
    singleScalerReadsCorrected(obj.singleScalerReadsCorrected.GetEntriesFast()),
    corrected(obj.corrected)
{
    singleScalerReads.SetOwner();
    singleScalerReadsCorrected.SetOwner();
    for(int i=0; i<obj.GetNScalerReadCorrections(); i++)
    {
        gROOT->cd();
        GHistLinked*    uncor   = new GHistLinked(*((GHistLinked*)obj.singleScalerReads.At(i)), kFALSE);
        uncor->SetName(TString(GetName()).Append("_UnCor_ScaRead").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
        uncor->SetTitle(TString(GetTitle()).Append(" Uncorrected Scaler Read ").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
        singleScalerReads.Add(uncor);

        gROOT->cd();
        GHistLinked*    cor     = new GHistLinked(*((GHistLinked*)obj.singleScalerReadsCorrected.At(i)), kFALSE);
        cor->SetName(TString(GetName()).Append("_ScaRead").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
        cor->SetTitle(TString(GetTitle()).Append(" Scaler Read ").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
        singleScalerReadsCorrected.Add(cor);
    }
}

GHistScaCor::~GHistScaCor()
{
}

Bool_t	GHistScaCor::Add(const GHistScaCor *h, Double_t c)
{
    TH1D::Add(h, c);
    accumulated.Add(&h->accumulated, c);
    accumulatedCorrected.Add(&h->accumulatedCorrected, c);
    for(int i=0; i<h->GetNScalerReadCorrections(); i++)
    {
        if(i>=GetNScalerReadCorrections())
        {
            gROOT->cd();
            GHistLinked*    uncor   = new GHistLinked(*((GHistLinked*)h->singleScalerReads.At(i)), kFALSE);
            uncor->SetName(TString(GetName()).Append("_UnCor_ScaRead").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
            uncor->SetTitle(TString(GetTitle()).Append(" Uncorrected Scaler Read ").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
            uncor->SetOutputDirectory(TString(GetOutputDirectoryName()));
            uncor->AddOutputDirectory("ScalerCorrection/SingleScalerReads_Uncorrected");
            singleScalerReads.Add(uncor);

            gROOT->cd();
            GHistLinked*    cor     = new GHistLinked(*((GHistLinked*)h->singleScalerReadsCorrected.At(i)), kFALSE);
            cor->SetName(TString(GetName()).Append("_ScaRead").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
            cor->SetTitle(TString(GetTitle()).Append(" Scaler Read ").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
            cor->SetOutputDirectory(TString(GetOutputDirectoryName()));
            cor->AddOutputDirectory("ScalerCorrection/SingleScalerReads");
            singleScalerReadsCorrected.Add(cor);
        }
        else
        {
            ((GHistLinked*)singleScalerReads.At(i))->Add((GHistLinked*)h->singleScalerReads.At(i), c);
            ((GHistLinked*)singleScalerReadsCorrected.At(i))->Add(((GHistLinked*)h->singleScalerReadsCorrected.At(i)), c);
        }
    }
    corrected = h->corrected;
}

void    GHistScaCor::AddOutputDirectory(const TString& directoryName)
{
    GHistLinked::AddOutputDirectory(directoryName);
    accumulated.SetOutputDirectory(GHistLinked::GetOutputDirectoryName());
    accumulated.AddOutputDirectory("ScalerCorrection");
    accumulatedCorrected.AddOutputDirectory(directoryName);
    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        ((GHistLinked*)singleScalerReads.At(i))->SetOutputDirectory(GHistLinked::GetOutputDirectoryName());
        ((GHistLinked*)singleScalerReads.At(i))->AddOutputDirectory("ScalerCorrection/SingleScalerReads_Uncorrected");
        ((GHistLinked*)singleScalerReadsCorrected.At(i))->SetOutputDirectory(GHistLinked::GetOutputDirectoryName());
        ((GHistLinked*)singleScalerReadsCorrected.At(i))->AddOutputDirectory("ScalerCorrection/SingleScalerReads");
    }
}

void    GHistScaCor::SetOutputDirectory(const TString& directoryName)
{
    GHistLinked::SetOutputDirectory(directoryName);
    accumulated.SetOutputDirectory(directoryName);
    accumulated.AddOutputDirectory("ScalerCorrection");
    accumulatedCorrected.SetOutputDirectory(directoryName);
    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        ((GHistLinked*)singleScalerReads.At(i))->SetOutputDirectory(directoryName);
        ((GHistLinked*)singleScalerReads.At(i))->AddOutputDirectory("ScalerCorrection/SingleScalerReads_Uncorrected");
        ((GHistLinked*)singleScalerReadsCorrected.At(i))->SetOutputDirectory(directoryName);
        ((GHistLinked*)singleScalerReadsCorrected.At(i))->AddOutputDirectory("ScalerCorrection/SingleScalerReads");
    }
}

void    GHistScaCor::Reset(Option_t* option)
{
    accumulated.Reset(option);
    accumulatedCorrected.Reset(option);
    singleScalerReads.Clear();
    singleScalerReadsCorrected.Clear();
    TH1D::Reset(option);
    corrected   = kFALSE;
}

void    GHistScaCor::ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads)
{
    accumulated.Add(this);

    if(CreateHistogramsForSingleScalerReads)
    {
        gROOT->cd();
        GHistLinked*    uncor   = new GHistLinked(*this, kFALSE);
        uncor->SetName(TString(GetName()).Append("_UnCor_ScaRead").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
        uncor->SetTitle(TString(GetTitle()).Append(" Uncorrected Scaler Read ").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
        uncor->AddOutputDirectory("ScalerCorrection/SingleScalerReads_Uncorrected");
        singleScalerReads.Add(uncor);

        Scale(CorrectionFactor);

        gROOT->cd();
        GHistLinked*    cor     = new GHistLinked(*this, kFALSE);
        cor->SetName(TString(GetName()).Append("_ScaRead").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
        cor->SetTitle(TString(GetTitle()).Append(" Scaler Read ").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
        cor->AddOutputDirectory("ScalerCorrection/SingleScalerReads");
        singleScalerReadsCorrected.Add(cor);
    }
    else
        Scale(CorrectionFactor);

    accumulatedCorrected.Add(this);
    TH1D::Reset();
    corrected   = kTRUE;
}

void	GHistScaCor::SetName(const char* name)
{
    TH1::SetName(name);
    accumulated.SetName(TString(name).Append("_Acc").Data());
    accumulatedCorrected.SetName(TString(name).Append("_AccCor").Data());
    for(int i=0; i<GetNScalerReadCorrections(); i++)
    {
        ((GHistLinked*)singleScalerReads.At(i))->SetName(TString(name).Append("_UnCor_ScaRead").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
        ((GHistLinked*)singleScalerReadsCorrected.At(i))->SetName(TString(name).Append("_ScaRead").Append(TString::Itoa(singleScalerReads.GetEntriesFast(), 10)));
    }
}

void	GHistScaCor::SetTitle(const char* title)
{
    TH1::SetTitle(title);
    accumulated.SetTitle(TString(title).Append(" Accumulated").Data());
    accumulatedCorrected.SetTitle(TString(title).Append(" Accumulated and Corrected").Data());
    for(int i=0; i<GetNScalerReadCorrections(); i++)
    {
        ((GHistLinked*)singleScalerReads.At(i))->SetTitle(TString(title).Append(" Scaler Read ").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
        ((GHistLinked*)singleScalerReadsCorrected.At(i))->SetTitle(TString(title).Append(" Scaler Read ").Append(TString::Itoa(singleScalerReadsCorrected.GetEntriesFast(), 10)));
    }
}


Int_t   GHistScaCor::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(corrected==kFALSE)
    {
        return GHistLinked::Write(0, option, bufsize);
    }

    Int_t   ret = WriteHistogram(accumulated,
                                 TString(GetName()).Append("_UnCor"),
                                 TString(GetTitle()).Append(" Uncorrected"),
                                 option,
                                 bufsize);

    for(int i=0; i<singleScalerReads.GetEntriesFast(); i++)
    {
        ret += singleScalerReads.At(i)->Write();
        ret += singleScalerReadsCorrected.At(i)->Write();
    }

    ret += WriteHistogram(accumulatedCorrected,
                          TString(GetName()),
                          TString(GetTitle()),
                          option,
                          bufsize);
    return ret;
}





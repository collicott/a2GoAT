#include "GH1.h"


GH1::GH1(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    GHistBGSub(name, title, nbinsx, xlow, xup, linkHistogram, dirName),
    bin()
{

}

GH1::GH1(const GH1& obj, Bool_t linkHistogram) :
    GHistBGSub(obj, linkHistogram),
    bin()
{

}

GH1::~GH1()
{

}


Bool_t	GH1::Add(const GH1* h, Double_t c)
{
    GHistBGSub::Add(h, c);
}

void    GH1::AddOutputDirectory(const TString& directoryName)
{
    GHistBGSub::AddOutputDirectory(directoryName);
}

void    GH1::SetOutputDirectory(const TString& directoryName)
{
    GHistBGSub::SetOutputDirectory(directoryName);
}

void    GH1::Reset(Option_t* option)
{
    GHistBGSub::Reset(option);
}

Int_t   GH1::Fill(const Double_t value, const Double_t taggerTime)
{
    GHistBGSub::Fill(value, taggerTime);
}

Int_t   GH1::Fill(const Double_t value, const GTreeTagger& tagger)
{
    GHistBGSub::Fill(value, tagger);
}

void    GH1::ScalerReadCorrection(const Double_t CorrectionFactor)
{
    GHistBGSub::ScalerReadCorrection(CorrectionFactor);
}

void	GH1::SetName(const char* name)
{
    GHistBGSub::SetName(name);
}

void	GH1::SetTitle(const char* title)
{
    GHistBGSub::SetTitle(title);
}

Int_t   GH1::Write(const char* name, Int_t option, Int_t bufsize)
{
    GHistBGSub::Write(name, option, bufsize);
}


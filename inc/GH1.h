#ifndef __GH1_h__
#define __GH1_h__


#include <TDirectory.h>

#include "GHistBGSub.h"


class   GTreeTagger;

class  GH1  : public GHistBGSub
{
private:
    TObjArray   bin;

            void    ExpandBin(const Int_t newSize);
    static  void    WriteHistogram(GHistScaCor *hist, const char* name, const char* title, TDirectory* dir = 0);

public:
    GH1(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    GH1(const GH1& obj, Bool_t linkHistogram = kTRUE);
    virtual ~GH1();

    virtual Bool_t	Add(const GH1* h, Double_t c = 1);
    virtual void    AddOutputDirectory(const TString& directoryName);
    virtual void    SetOutputDirectory(const TString& directoryName);
    virtual void    Reset(Option_t* option = "");
    virtual Int_t   Fill(const Double_t value, const Double_t taggerTime = 0, const Int_t taggerChannel = 0);
    virtual Int_t   Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t CreateHistogramsForTaggerBinning = kFALSE);
    virtual void    ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads = kFALSE);
    virtual void	SetName(const char* name);
    virtual void	SetTitle(const char* title);
    virtual void	SetNameTitle(const char* name, const char* title)   {SetName(name); SetTitle(title);}
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};




#endif

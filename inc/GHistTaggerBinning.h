#ifndef __GHistTaggerBinning_h__
#define __GHistTaggerBinning_h__


#include <TROOT.h>
#include <TDirectory.h>

#include "GHistScaCor.h"


class   GTreeTagger;

class  GHistTaggerBinning  : public GHistScaCor
{
private:
    TObjArray   bin;

    static  Int_t   TaggerBinningRangeMin;
    static  Int_t   TaggerBinningRangeMax;

            void    ExpandBin(const Int_t newSize);
    static  void    WriteHistogram(GHistLinked *hist, const char* name, const char* title, TDirectory* dir = 0);

public:
    GHistTaggerBinning();
    GHistTaggerBinning(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    virtual ~GHistTaggerBinning();

    virtual Bool_t	Add(const GHistTaggerBinning* h, Double_t c = 1);
    virtual void    AddOutputDirectory(const TString& directoryName);
    static  void    InitTaggerBinning(const Int_t min, const Int_t max);
    virtual Int_t   Fill(const Double_t value, const Int_t taggerChannel = 0);
    virtual Int_t   Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t CreateHistogramsForTaggerBinning = kFALSE);
    virtual void    Reset(Option_t* option = "");
    virtual void    ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads = kFALSE);
    virtual void	SetBins(Int_t nx, Double_t xmin, Double_t xmax);
    virtual void	SetName(const char* name);
    virtual void    SetOutputDirectory(const TString& directoryName);
    virtual void	SetTitle(const char* title);
    virtual void	SetNameTitle(const char* name, const char* title)   {SetName(name); SetTitle(title);}
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};




#endif

#ifndef __GHistScaCor_h__
#define __GHistScaCor_h__


#include <TROOT.h>
#include <TObjArray.h>

#include "GHistManager.h"





class   GHistScaCor : public GHistLinked
{
private:
    GHistLinked accumulated;
    GHistLinked accumulatedCorrected;
    TObjArray   singleScalerReads;
    TObjArray   singleScalerReadsCorrected;

    static  Int_t   WriteHistogram(GHistLinked& hist, const TString& name, const TString& title, Int_t option, Int_t bufsize);

protected:

public:
    GHistScaCor(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    GHistScaCor(const GHistScaCor& obj);
    virtual ~GHistScaCor();

    virtual Bool_t	Add(const GHistScaCor* h, Double_t c = 1);
    virtual void    AddOutputDirectory(const TString& directoryName);
    virtual void    SetOutputDirectory(const TString& directoryName);
    virtual void    Reset(Option_t* option = "");
            Int_t   GetNScalerReadCorrections() const   {return singleScalerReads.GetEntriesFast();}
    virtual void    ScalerReadCorrection(const Double_t CorrectionFactor);
    virtual void	SetName(const char* name);
    virtual void	SetTitle(const char* title);
    virtual void	SetNameTitle(const char* name, const char* title)   {SetName(name); SetTitle(title);}
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};


#endif

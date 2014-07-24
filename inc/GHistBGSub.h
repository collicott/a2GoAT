#ifndef __GHistBGSub_h__
#define __GHistBGSub_h__


#include <TDirectory.h>

#include "GHistScaCor.h"


class   GTreeTagger;

class  GHistBGSub  : public GHistScaCor
{
private:
    TObjArray   rand;

    static  Double_t    cutPromptMin;
    static  Double_t    cutPromptMax;
    static  std::vector<Double_t> cutRandMin;
    static  std::vector<Double_t> cutRandMax;
    static  Double_t    backgroundSubstractionFactor;

            void    ExpandRand(const Int_t newSize);
    static  void    WriteHistogram(GHistScaCor *hist, const char* name, const char* title, TDirectory* dir = 0);

public:
    GHistBGSub(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    GHistBGSub(const GHistBGSub& obj, Bool_t linkHistogram = kTRUE);
    virtual ~GHistBGSub();

    virtual Bool_t	Add(const GHistBGSub* h, Double_t c = 1);
    static  void    AddRandCut(const Double_t RandMin, const Double_t RandMax);
    virtual void    AddOutputDirectory(const TString& directoryName);
    virtual void    SetOutputDirectory(const TString& directoryName);
    virtual void    Reset(Option_t* option = "");
    virtual Int_t   Fill(const Double_t value, const Double_t taggerTime = 0);
    virtual Int_t   Fill(const Double_t value, const GTreeTagger& tagger);
    static  Int_t   GetNRandCuts()   {cutRandMin.size();}
    static  void    InitCuts(const Double_t PromptMin, const Double_t PromptMax, const Double_t RandMin, const Double_t RandMax);
    virtual void    ScalerReadCorrection(const Double_t CorrectionFactor);
    virtual void	SetName(const char* name);
    virtual void	SetTitle(const char* title);
    virtual void	SetNameTitle(const char* name, const char* title)   {SetName(name); SetTitle(title);}
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);

    friend class PPhysics;
};




#endif

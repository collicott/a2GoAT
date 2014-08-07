#ifndef __GHistBGSub_h__
#define __GHistBGSub_h__


#include <TDirectory.h>

#include "GHistTaggerBinning.h"


class   GTreeTagger;

class  GHistBGSub  : public GHistTaggerBinning
{
private:
    TObjArray   rand;

    static  Double_t    cutPromptMin;
    static  Double_t    cutPromptMax;
    static  std::vector<Double_t> cutRandMin;
    static  std::vector<Double_t> cutRandMax;
    static  Double_t    backgroundSubstractionFactor;

            void    ExpandRand(const Int_t newSize);
    static  void    WriteHistogram(GHistTaggerBinning *hist, const char* name, const char* title, TDirectory* dir = 0);

public:
    GHistBGSub();
    GHistBGSub(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    virtual ~GHistBGSub();

    virtual Bool_t	Add(const GHistBGSub* h, Double_t c = 1);
    static  void    AddRandCut(const Double_t RandMin, const Double_t RandMax);
    virtual void    AddOutputDirectory(const TString& directoryName);
    virtual Int_t   Fill(const Double_t value, const Double_t taggerTime = 0, const Int_t taggerChannel = 0);
    virtual Int_t   Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t DoTaggerBinning = kFALSE);
    static  Int_t   GetNRandCuts()   {cutRandMin.size();}
    static  void    InitCuts(const Double_t PromptMin, const Double_t PromptMax, const Double_t RandMin, const Double_t RandMax);
    virtual void    Reset(Option_t* option = "");
    virtual void    ScalerReadCorrection(const Double_t CorrectionFactor, const Bool_t CreateHistogramsForSingleScalerReads = kFALSE);
    virtual void	SetName(const char* name);
    virtual void    SetOutputDirectory(const TString& directoryName);
    virtual void	SetTitle(const char* title);
    virtual void	SetNameTitle(const char* name, const char* title)   {SetName(name); SetTitle(title);}
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};




#endif

#ifndef __GHistTaggerBinning_h__
#define __GHistTaggerBinning_h__


#include <TROOT.h>
#include <TDirectory.h>

#include "GHistManager.h"


class   GTreeTagger;

class  GHistTaggerBinning  : public GHistLinked
{
private:
    TObjArray   bin;

            void    ExpandBin(const Int_t newSize);
    static  void    WriteHistogram(GHistLinked *hist, const char* name, const char* title, TDirectory* dir = 0);

public:
    GHistTaggerBinning();
    GHistTaggerBinning(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    GHistTaggerBinning(const GHistTaggerBinning& obj, Bool_t linkHistogram = kTRUE);
    virtual ~GHistTaggerBinning();

    virtual Bool_t	Add(const GHistTaggerBinning* h, Double_t c = 1);
    virtual void    AddOutputDirectory(const TString& directoryName);
    virtual void    SetOutputDirectory(const TString& directoryName);
    virtual void    Reset(Option_t* option = "");
    virtual Int_t   Fill(const Double_t value, const Int_t taggerChannel = 0);
    virtual Int_t   Fill(const Double_t value, const GTreeTagger& tagger, const Bool_t CreateHistogramsForTaggerBinning = kFALSE);
    virtual void	SetBins(Int_t nx, Double_t xmin, Double_t xmax);
    virtual void	SetName(const char* name);
    virtual void	SetTitle(const char* title);
    virtual void	SetNameTitle(const char* name, const char* title)   {SetName(name); SetTitle(title);}
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};




#endif

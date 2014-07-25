#ifndef __GHistManager_h__
#define __GHistManager_h__


#include <TH1.h>
#include <TObjArray.h>
#include <TDirectory.h>



class   GLinkedHist;

class   GHistManager
{
private:
    TObjArray   histList;

    void        AddHistogramToList(GLinkedHist* hist);
    //virtual TDirectory* GetOutputDirectory() = 0;
    void        RemoveHistogramFromList(GLinkedHist* hist);

protected:

public:
    GHistManager();
    virtual ~GHistManager();

    void    ClearLinkedHistograms();
    void    WriteLinkedHistograms(TDirectory* dir);

    friend  class   GLinkedHist;
};





class   GLinkedHist : public TH1D
{
private:
    Bool_t  linked;

public:
    GLinkedHist(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE);
    GLinkedHist(const GLinkedHist& obj);
    virtual ~GLinkedHist();

    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0)  const                     {return TH1D::Write(name, option, bufsize);}
    virtual Int_t   Write(TDirectory* dir, const char* name = 0, Int_t option = 0, Int_t bufsize = 0)  const;
};


#endif

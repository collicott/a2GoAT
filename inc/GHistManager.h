#ifndef __GHistManager_h__
#define __GHistManager_h__


#include <iostream>

#include <TH1.h>
#include <TObjArray.h>
#include <TDirectory.h>



class   GLinkedHist;

class   GHistManager
{
private:
    TObjArray   histList;

    void        AddHistogramToList(GLinkedHist* hist);
    virtual     TDirectory* GetOutputDirectory() = 0;
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
    TString dir;

    static  TDirectory* GetCreateDirectory(TDirectory* dir, const TString& dirName);

protected:
            TDirectory* GetOutputDirectory();

public:
    GLinkedHist(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    GLinkedHist(const GLinkedHist& obj, Bool_t linkHistogram);
    GLinkedHist(const GLinkedHist& obj);
    virtual ~GLinkedHist();

            void    SetOutputDirectory(const TString& directoryName)    {dir = directoryName;}
            void    SetOutputDirectory(const char* directoryName)       {SetOutputDirectory(TString(directoryName));}
    virtual Int_t   Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};


#endif

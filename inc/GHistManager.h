#ifndef __GHistManager_h__
#define __GHistManager_h__


#include <iostream>

#include <TH1.h>
#include <TObjArray.h>
#include <TDirectory.h>



class   GHistLinked;

class   GHistManager
{
private:
    TObjArray   histList;

    void        AddHistogramToList(GHistLinked* hist);
    virtual     TDirectory* GetOutputDirectory() = 0;
    void        RemoveHistogramFromList(GHistLinked* hist);

protected:

public:
    GHistManager();
    virtual ~GHistManager();

    void    ClearLinkedHistograms();
    void    WriteLinkedHistograms(TDirectory* dir);

    friend  class   GHistLinked;
};





class   GHistLinked : public TH1D
{
private:
    Bool_t  linked;
    TString dir;

    static  TDirectory* GetCreateDirectory(TDirectory* dir, const TString& dirName);

protected:
            TDirectory* GetOutputDirectory();

public:
    GHistLinked();
    GHistLinked(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    GHistLinked(const GHistLinked& obj, Bool_t linkHistogram);
    virtual ~GHistLinked();

    virtual void        AddOutputDirectory(const TString& directoryName);
    const   TString&    GetOutputDirectoryName() const                      {return dir;}
            void        Link();
    virtual void        SetOutputDirectory(const TString& directoryName)    {dir = directoryName;}
            void        Unlink();
    virtual Int_t       Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};


#endif

#include "GHistManager.h"



GHistManager*   gGHistManager = 0;


GHistManager::GHistManager()    :
    histList()
{
    gGHistManager   = this;
    histList.SetOwner(kFALSE);
}

GHistManager::~GHistManager()
{
    gGHistManager   = 0;
}

void    GHistManager::AddHistogramToList(GLinkedHist* hist)
{
    histList.AddAtFree(hist);
}

void    GHistManager::RemoveHistogramFromList(GLinkedHist* hist)
{
    histList.Remove(hist);
}

void GHistManager::ClearLinkedHistograms()
{
    TIter   iter(&histList);
    GLinkedHist*    hist;
    while(hist=(GLinkedHist*)iter.Next())
        hist->Reset();
}

void GHistManager::WriteLinkedHistograms(TDirectory* dir)
{
    TIter   iter(&histList);
    GLinkedHist*    hist;
    while(hist=(GLinkedHist*)iter.Next())
        hist->Write(0, TObject::kWriteDelete);
}





TDirectory* GLinkedHist::GetCreateDirectory(TDirectory* dir, const TString& dirName)
{
    dir->cd();
    TDirectory* curDir  = dir->GetDirectory(dirName);
    if(!curDir)
    {
        dir->cd();
        curDir  = gDirectory->mkdir(dirName);
    }
    dir->cd();
    return curDir;
}


GLinkedHist::GLinkedHist(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    TH1D(name, title, nbinsx, xlow, xup),
    linked(linkHistogram),
    dir(dirName)
{
    if(linked == kTRUE)
    {
        if(gGHistManager)
            gGHistManager->AddHistogramToList(this);
    }
}

GLinkedHist::GLinkedHist(const GLinkedHist& obj, Bool_t linkHistogram) :
    TH1D(obj),
    linked(linkHistogram),
    dir(obj.dir)
{
    if(linked == kTRUE)
    {
        if(gGHistManager)
            gGHistManager->AddHistogramToList(this);
    }
}

GLinkedHist::GLinkedHist(const GLinkedHist& obj) :
    TH1D(obj),
    linked(obj.linked)
{
    if(linked == kTRUE)
    {
        if(gGHistManager)
            gGHistManager->AddHistogramToList(this);
    }
}

GLinkedHist::~GLinkedHist()
{
    if(linked == kTRUE)
    {
        if(gGHistManager)
            gGHistManager->RemoveHistogramFromList(this);
    }
}

TDirectory*    GLinkedHist::GetOutputDirectory()
{
    if(gGHistManager)
    {
        return GetCreateDirectory((TDirectory*)gGHistManager->GetOutputDirectory(), dir);
    }
    return  GetCreateDirectory((TDirectory*)GetDirectory(), dir);
}

Int_t   GLinkedHist::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(GetOutputDirectory())
        GetOutputDirectory()->cd();
    TH1D::Write(name, option, bufsize);
}

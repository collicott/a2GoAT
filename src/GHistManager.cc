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
        hist->Write(dir, 0, TObject::kWriteDelete);
}






GLinkedHist::GLinkedHist(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram) :
    TH1D(name, title, nbinsx, xlow, xup),
    linked(linkHistogram)
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

Int_t    GLinkedHist::Write(TDirectory* dir, const char* name, Int_t option, Int_t bufsize) const
{
    if(dir)
        dir->cd();
    return  Write(name, option, bufsize);
}

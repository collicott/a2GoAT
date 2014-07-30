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

void    GHistManager::AddHistogramToList(GHistLinked* hist)
{
    histList.AddAtFree(hist);
}

void    GHistManager::RemoveHistogramFromList(GHistLinked* hist)
{
    histList.Remove(hist);
}

void GHistManager::ClearLinkedHistograms()
{
    TIter   iter(&histList);
    GHistLinked*    hist;
    while(hist=(GHistLinked*)iter.Next())
        hist->Reset();
}

void GHistManager::WriteLinkedHistograms(TDirectory* dir)
{
    TIter   iter(&histList);
    GHistLinked*    hist;
    while(hist=(GHistLinked*)iter.Next())
        hist->Write(0, TObject::kWriteDelete);
}





TDirectory* GHistLinked::GetCreateDirectory(TDirectory* dir, const TString& dirName)
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


GHistLinked::GHistLinked() :
    TH1D(),
    linked(kFALSE),
    dir()
{
}

GHistLinked::GHistLinked(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram, const char* dirName) :
    TH1D(name, title, nbinsx, xlow, xup),
    linked(linkHistogram),
    dir(dirName)
{
    if(linked == kTRUE)
        Link();
}

GHistLinked::GHistLinked(const GHistLinked& obj, Bool_t linkHistogram) :
    TH1D(obj),
    linked(linkHistogram),
    dir(obj.dir)
{
    if(linked == kTRUE)
        Link();
}

GHistLinked::~GHistLinked()
{
    Unlink();
}

void        GHistLinked::AddOutputDirectory(const TString& directoryName)
{
    if(dir.Length()==0)
        dir = directoryName;
    else
        dir.Append("/").Append(directoryName);
}

TDirectory*    GHistLinked::GetOutputDirectory()
{
    if(gGHistManager)
    {
        return GetCreateDirectory((TDirectory*)gGHistManager->GetOutputDirectory(), dir);
    }
    return  GetCreateDirectory((TDirectory*)GetDirectory(), dir);
}

void    GHistLinked::Link()
{
    if(linked)
        Unlink();
    if(gGHistManager)
    {
        gGHistManager->AddHistogramToList(this);
        linked = kTRUE;
    }
}

void    GHistLinked::Unlink()
{
    linked = kFALSE;
    if(gGHistManager)
        gGHistManager->RemoveHistogramFromList(this);
}

Int_t   GHistLinked::Write(const char* name, Int_t option, Int_t bufsize)
{
    if(GetOutputDirectory())
        GetOutputDirectory()->cd();
    TH1D::Write(name, option, bufsize);
}

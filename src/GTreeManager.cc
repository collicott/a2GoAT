#include "GTreeManager.h"


using namespace std;


GTreeManager::GTreeManager()    :
    file_in(0),
    file_out(0),
    //minEntry(0),
    //nEntries(0),
    rawEvent(0),
    tagger(0),
    scalers(0),
    photons(0),
    protons(0)
{
}

GTreeManager::~GTreeManager()
{

}

Bool_t  GTreeManager::TraverseEntries(const UInt_t min, const UInt_t max)
{
    if(photons->IsOpenForInput())
    {
        if(rawEvent->IsOpenForInput())
        {
            if(tagger->IsOpenForInput())
            {
                for(int i=min; i<max; i++)
                {
                    photons->GetEntryFast(i);
                    rawEvent->GetEntryFast(i);
                    tagger->GetEntryFast(i);
                    ProcessEvent();
                }
            }
            else
            {
                for(int i=min; i<max; i++)
                {
                    photons->GetEntryFast(i);
                    rawEvent->GetEntryFast(i);
                    ProcessEvent();
                }
            }
        }
        else
        {
            if(tagger->IsOpenForInput())
            {
                for(int i=min; i<max; i++)
                {
                    photons->GetEntryFast(i);
                    tagger->GetEntryFast(i);
                    ProcessEvent();
                }
            }
            else
            {
                for(int i=min; i<max; i++)
                {
                    photons->GetEntryFast(i);
                    ProcessEvent();
                }
            }
        }
    }
    else if(rawEvent->IsOpenForInput())
    {
        if(tagger->IsOpenForInput())
        {
            for(int i=min; i<max; i++)
            {
                rawEvent->GetEntryFast(i);
                tagger->GetEntryFast(i);
                ProcessEvent();
            }
        }
        else
        {
            for(int i=min; i<max; i++)
            {
                rawEvent->GetEntryFast(i);
                ProcessEvent();
            }
        }
    }
    else if(tagger->IsOpenForInput())
    {
        for(int i=min; i<max; i++)
        {
            tagger->GetEntryFast(i);
            ProcessEvent();
        }
    }
    else
    {
        for(int i=min; i<max; i++)
            ProcessEvent();
    }
}

Bool_t   GTreeManager::Create(const char* filename)
{
    if(file_out) delete file_out;
    file_out = TFile::Open(filename, "RECREATE");
    if(!file_out)
        return kFALSE;
    return kTRUE;
}

Bool_t   GTreeManager::CreateParticle(GTreeParticle*& particleTree, const TString& _Name)
{
    if(!file_out) return kFALSE;
    if(!particleTree)   particleTree = new GTreeParticle(_Name);
    return particleTree->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateRawEvent()
{
    if(!file_out) return kFALSE;
    if(!rawEvent)   rawEvent = new GTreeRawEvent();
    return rawEvent->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateTagger()
{
    if(!file_out) return kFALSE;
    if(!tagger)   tagger = new GTreeTagger();
    return tagger->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateScalers()
{
    if(!file_out) return kFALSE;
    if(!scalers)   scalers = new GTreeScaler();
    return scalers->OpenForOutput(*file_out);
}


Bool_t   GTreeManager::Open(const char* filename)
{
    if(file_in) delete file_in;
    file_in = TFile::Open(filename);
    if(!file_in)
        return kFALSE;
    return kTRUE;
}

/*Bool_t  GTreeManager::EntryChecking(const GTree* tree)
{
    Int_t   oldNEntries = nEntries;
    nEntries = tree->GetNEntries();
    if(nEntries < oldNEntries)
    {
        std::cout << "#ERROR# treeRawEvent has different Entries (" << nEntries << ") others " << oldNEntries << std::endl;
        return kFALSE;
    }
    if(oldNEntries == 0)
        return kTRUE;
    if(nEntries > oldNEntries)
    {
        std::cout << "#ERROR# treeRawEvent has different Entries (" << nEntries << ") others " << oldNEntries << std::endl;
        nEntries = oldNEntries;
        return kFALSE;
    }
    return kTRUE;
}*/

Bool_t   GTreeManager::OpenParticle(GTreeParticle*& particleTree, const TString& _Name)
{
    if(!file_in) return kFALSE;
    if(!particleTree)   particleTree = new GTreeParticle(_Name);
    if(!particleTree->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(rawEvent);
    return kTRUE;
}

Bool_t   GTreeManager::OpenRawEvent()
{
    if(!file_in) return kFALSE;
    if(!rawEvent)   rawEvent = new GTreeRawEvent();
    if(!rawEvent->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(rawEvent);
    return kTRUE;
}

Bool_t   GTreeManager::OpenTagger()
{
    if(!file_in) return kFALSE;
    if(!tagger)   tagger = new GTreeTagger();
    if(!tagger->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(tagger);
    return kTRUE;
}

Bool_t   GTreeManager::OpenScalers()
{
    if(!file_in) return kFALSE;
    if(!scalers)   scalers = new GTreeScaler();
    return scalers->OpenForInput(*file_in);
}

Bool_t  GTreeManager::Write()
{
    if(photons)     photons->Write();
    if(protons)     protons->Write();
    if(rawEvent)    rawEvent->Write();
    if(tagger)      tagger->Write();
    if(scalers)     scalers->Write();
}

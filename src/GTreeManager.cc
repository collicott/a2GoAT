#include "GTreeManager.h"

#include <TROOT.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

using namespace std;


GTreeManager::GTreeManager()    :
    file_in(0),
    file_out(0),
    treeList(),
    treeCorreleatedToScalerReadList(),
    readList(),
    readCorreleatedToScalerReadList(),
    writeList(),
    rawEvent(0),
    tagger(0),
    trigger(0),
    scalers(0),
    detectorHits(0),
    photons(0),
    electrons(0),
    chargedPi(0),
    protons(0),
    neutrons(0),
    pi0(0),
    eta(0),
    etap(0),
    linpol(0),
    nValidScalerReads(0),
    currentEvent(0)
{
    etap = new GTreeMeson(this, TString("Etap"));
    eta = new GTreeMeson(this, TString("Eta"));
    pi0 = new GTreeMeson(this, TString("Pi0"));
    photons = new GTreeParticle(this, TString("Photons"));
    electrons = new GTreeParticle(this, TString("Electrons"));
    chargedPi = new GTreeParticle(this, TString("ChargedPi"));
    protons = new GTreeParticle(this, TString("Protons"));
    neutrons = new GTreeParticle(this, TString("Neutrons"));
    detectorHits = new GTreeDetectorHits(this);
    rawEvent = new GTreeRawEvent(this);
    tagger = new GTreeTagger(this);
    trigger = new GTreeTrigger(this);
    scalers = new GTreeScaler(this);
    linpol = new GTreeLinPol(this);

    pdgDB = TDatabasePDG::Instance();
}

GTreeManager::~GTreeManager()
{
    while(treeList.GetEntries()>0)
    {
        if((GTree*)treeList[0])
            delete (GTree*)treeList[0];
    }

    CloseFiles();
}

void    GTreeManager::CloseFiles()
{
    if(file_in)     delete file_in;
    if(file_out)    delete file_out;
}

Bool_t  GTreeManager::TraverseEntries(const UInt_t min, const UInt_t max)
{
    if(!file_in)
        return kFALSE;

    for(UInt_t i=min; i<max; i++)
    {
        for(int l=0; l<readList.GetEntriesFast(); l++)
            ((GTree*)readList[l])->GetEntryFast(i);

        currentEvent = i;
        ProcessEvent();
    }

    return kTRUE;
}

Bool_t  GTreeManager::TraverseScalerEntries(const UInt_t min, const UInt_t max)
{
    if(!file_in)
        return kFALSE;

    if(!scalers)
        return kFALSE;
    if(!scalers->IsOpenForInput())
    {
        if(!scalers->OpenForInput())
        {
            std::cout << "Can not open treeScaler in input file." << std::endl;
            return kFALSE;
        }
    }

    for(UInt_t i=min; i<=max; i++)
    {
        scalers->GetEntryFast(i);
        ProcessEvent();
    }

    return kTRUE;
}


Bool_t  GTreeManager::StartFile(const char* input_filename, const char* output_filename)
{
    for(int l=0; l<treeList.GetEntries(); l++)
        ((GTree*)treeList[l])->Close();
    for(int l=0; l<treeCorreleatedToScalerReadList.GetEntries(); l++)
        ((GTree*)treeCorreleatedToScalerReadList[l])->Close();

    if(file_in) delete file_in;
    file_in = TFile::Open(input_filename);
    if(!file_in)
    {
        cout << "#ERROR: Can not open input file " << input_filename << "!" << endl;
        return kFALSE;
    }
    cout << "Opened input file " << file_in->GetName() << "!" << file_in->GetTitle() << endl;

    for(int l=0; l<treeList.GetEntries(); l++)
    {
        if(file_in->Get(((GTree*)treeList[l])->GetName()))
            ((GTree*)treeList[l])->OpenForInput();
    }
    for(int l=0; l<treeCorreleatedToScalerReadList.GetEntries(); l++)
    {
        if(file_in->Get(((GTree*)treeCorreleatedToScalerReadList[l])->GetName()))
            ((GTree*)treeCorreleatedToScalerReadList[l])->OpenForInput();
    }

    if(file_out) delete file_out;
    file_out = TFile::Open(output_filename, "RECREATE");
    if(!file_out)
    {
        cout << "#ERROR: Can not create output file " << output_filename << "!" << endl;
        return kFALSE;
    }
    cout << "Created output file " << file_out->GetName() << "!" << file_out->GetTitle() << endl;

    isWritten   = kFALSE;

    if(!Start())
        return kFALSE;

    if(isWritten)
        return kTRUE;
    return Write();
}

Bool_t  GTreeManager::Write()
{
    if(!file_out)   return kFALSE;
    file_out->cd();

    for(int l=0; l<writeList.GetEntries(); l++)
        ((GTree*)writeList[l])->Write();

    isWritten   = kTRUE;

    return kTRUE;
}

Bool_t  GTreeManager::Write(const TNamed* object)
{
    if(!file_out)   return kFALSE;
    file_out->cd();
    object->Write();
    std::cout << "object " << object->GetName() << " has been written to disk." << std::endl;
    return kTRUE;
}


Bool_t  GTreeManager::TraverseValidEvents()
{
    cout << "Checking scaler reads for valid events:" << endl;
    if(!scalers->IsOpenForInput())
    {
        if(!scalers->OpenForInput())
        {
            cout << "No treeScaler available. Expect MC data. Loop over all events" << endl;
            cout << "\tProcess events from " << 0 << " to " << GetNEntries() << "."<< endl;
            TraverseEntries(0, GetNEntries());
            return true;
        }
    }

    if(scalers->GetNEntries()<2)
    {
        std::cout << "Less than 2 scaler reads. Can not find events with correct scalers" <<std::endl;
        return kFALSE;
    }

    int shift = scalers->GetEventNumber() - scalers->GetEventID();
    nValidScalerReads = 0;
    scalers->GetEntry(0);
    for(int i=1; i<scalers->GetNEntries(); i++)
    {
        scalers->GetEntry(i);
        if(scalers->GetEventNumber() - scalers->GetEventID() == shift)
        {
            eventNumberBeforeValidScalerRead[nValidScalerReads] = scalers->GetEventNumber();
            scalers->GetEntry(i-1);
            eventNumberValidScalerRead[nValidScalerReads] = scalers->GetEventNumber();
            validScalerRead[nValidScalerReads] = i;
            nValidScalerReads++;
        }
    }

    file_out->cd();
    TH1I*   accepted    = new TH1I("CountScalerValid", "Events with correct scalers (all=0,accepted=1,rejected=2)", 3, 0, 3);
    accepted->SetBinContent(1, rawEvent->GetNEntries());

    scalers->GetEntry(0);
    int start = eventNumberBeforeValidScalerRead[0];
    int stop  = eventNumberValidScalerRead[0];
    for(int i=1; i<nValidScalerReads; i++)
    {
        if(validScalerRead[i] == validScalerRead[i-1]+1)
            stop    = eventNumberValidScalerRead[i];
        else
        {
            cout << "\tValid events from " << start << " to " << stop << "."<< endl;
            accepted->SetBinContent(2, accepted->GetBinContent(2) + (stop-start));
            TraverseEntries(start, stop);
            start = eventNumberBeforeValidScalerRead[i];
            stop  = eventNumberValidScalerRead[i];
        }
    }
    cout << "\tValid events from " << start << " to " << stop << "."<< endl;
    accepted->SetBinContent(2, accepted->GetBinContent(2) + (stop-start));
    TraverseEntries(start, stop);

    accepted->SetBinContent(3, rawEvent->GetNEntries() - accepted->GetBinContent(2));

    if(!Write(accepted))  return kFALSE;
    return kTRUE;
}

UInt_t  GTreeManager::GetNEntries()       const
{
    for(int l=1; l<readList.GetEntriesFast(); l++)
    {
        if(((GTree*)readList[l])->GetNEntries() != ((GTree*)readList[l-1])->GetNEntries())
        {
            cout << "ERROR: input trees have different number of entries!"<< endl;
            return 0;
        }
    }

    if(readList.GetEntriesFast() == 0)
        return 0;

    return  ((GTree*)readList[0])->GetNEntries();
}

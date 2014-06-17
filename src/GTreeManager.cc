#include "GTreeManager.h"

#include <TROOT.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

using namespace std;


GTreeManager::GTreeManager()    :
    file_in(0),
    file_out(0),
    rawEvent(0),
    tagger(0),
    trigger(0),
    scalers(0),
    eventFlags(0),
    detectorHits(0),
    photons(0),
    electrons(0),
    chargedPi(0),
    protons(0),
    neutrons(0),
    pi0(0),
    eta(0),
    etap(0),
    fitData(0),
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
    eventFlags = new GTreeEvent(this);
    rawEvent = new GTreeRawEvent(this);
    tagger = new GTreeTagger(this);
    trigger = new GTreeTrigger(this);
    scalers = new GTreeScaler(this);
    fitData = new GTreeFit(this);

    pdgDB = TDatabasePDG::Instance();
}

GTreeManager::~GTreeManager()
{
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

    if(etap)
    {
        if(etap->IsOpenForInput())
            readList.Add(etap);
    }
    if(eta)
    {
        if(eta->IsOpenForInput())
            readList.Add(eta);
    }
    if(pi0)
    {
        if(pi0->IsOpenForInput())
            readList.Add(pi0);
    }

    if(photons)
    {
        if(photons->IsOpenForInput())
            readList.Add(photons);
    }
    if(electrons)
    {
        if(electrons->IsOpenForInput())
            readList.Add(electrons);
    }
    if(chargedPi)
    {
        if(chargedPi->IsOpenForInput())
            readList.Add(chargedPi);
    }
    if(protons)
    {
        if(protons->IsOpenForInput())
            readList.Add(protons);
    }
    if(neutrons)
    {
        if(neutrons->IsOpenForInput())
            readList.Add(photons);
    }

    if(rawEvent)
    {
        if(rawEvent->IsOpenForInput())
            readList.Add(rawEvent);
    }
    if(tagger)
    {
        if(tagger->IsOpenForInput())
            readList.Add(tagger);
    }
    if(eventFlags)
    {
        if(eventFlags->IsOpenForInput())
            readList.Add(eventFlags);
    }
    if(detectorHits)
    {
        if(detectorHits->IsOpenForInput())
            readList.Add(detectorHits);
    }
    if(trigger)
    {
        if(trigger->IsOpenForInput())
            readList.Add(trigger);
    }
    if(fitData)
    {
        if(fitData->IsOpenForInput())
            readList.Add(fitData);
    }

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

Int_t   GTreeManager::CheckInput(const char* input_filename)
{
    TFile*  file = TFile::Open(input_filename);
    if(!file)
    {
        cout << "#ERROR: Can not open input file " << input_filename << "!" << endl;
        return 0;
    }

    Int_t   ret = 0;

    if(file->Get("treeRawEvent"))
        ret = ret | TreeFlag_RawEvent;
    if(file->Get("treeTagger"))
        ret = ret | TreeFlag_Tagger;
    if(file->Get("treeTrigger"))
        ret = ret | TreeFlag_Trigger;
    if(file->Get("treeEventFlags"))
        ret = ret | TreeFlag_EventFlags;
    if(file->Get("treeDetectorHits"))
        ret = ret | TreeFlag_DetectorHits;
    if(file->Get("treeFit"))
        ret = ret | TreeFlag_Fit;
    if(file->Get("Etap"))
        ret = ret | TreeFlag_Etap;
    if(file->Get("Eta"))
        ret = ret | TreeFlag_Eta;
    if(file->Get("Pi0"))
        ret = ret | TreeFlag_Pi0;
    if(file->Get("Photons"))
        ret = ret | TreeFlag_Photons;
    if(file->Get("Electrons"))
        ret = ret | TreeFlag_Electrons;
    if(file->Get("ChargedPi"))
        ret = ret | TreeFlag_ChargedPi;
    if(file->Get("Protons"))
        ret = ret | TreeFlag_Protons;
    if(file->Get("Neutrons"))
        ret = ret | TreeFlag_Neutrons;

    delete file;
    return ret;
}



Bool_t  GTreeManager::StartFile(const char* input_filename, const char* output_filename)
{
    pi0->Close();
    eta->Close();
    etap->Close();
    photons->Close();
    electrons->Close();
    chargedPi->Close();
    protons->Close();
    neutrons->Close();
    detectorHits->Close();
    eventFlags->Close();
    rawEvent->Close();
    tagger->Close();
    trigger->Close();
    scalers->Close();
    fitData->Close();

    if(file_in) delete file_in;
    file_in = TFile::Open(input_filename);
    if(!file_in)
    {
        cout << "#ERROR: Can not open input file " << input_filename << "!" << endl;
        return kFALSE;
    }
    cout << "Opened input file " << file_in->GetName() << "!" << file_in->GetTitle() << endl;

    if(file_in->Get("treeRawEvent"))
        rawEvent->OpenForInput();
    if(file_in->Get("treeTagger"))
        tagger->OpenForInput();
    if(file_in->Get("treeTrigger"))
        trigger->OpenForInput();
    if(file_in->Get("treeEventFlags"))
        eventFlags->OpenForInput();
    if(file_in->Get("treeDetectorHits"))
        detectorHits->OpenForInput();
    if(file_in->Get("treeFit"))
        fitData->OpenForInput();
    if(file_in->Get("Etap"))
        etap->OpenForInput();
    if(file_in->Get("Eta"))
        eta->OpenForInput();
    if(file_in->Get("Pi0"))
        pi0->OpenForInput();
    if(file_in->Get("Photons"))
        photons->OpenForInput();
    if(file_in->Get("Electrons"))
        electrons->OpenForInput();
    if(file_in->Get("ChargedPi"))
        chargedPi->OpenForInput();
    if(file_in->Get("Protons"))
        protons->OpenForInput();
    if(file_in->Get("Neutrons"))
        neutrons->OpenForInput();



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

    if(pi0->IsOpenForOutput())         pi0->Write();
    if(eta->IsOpenForOutput())         eta->Write();
    if(etap->IsOpenForOutput())        etap->Write();
    if(photons->IsOpenForOutput())     photons->Write();
    if(electrons->IsOpenForOutput())   electrons->Write();
    if(chargedPi->IsOpenForOutput())   chargedPi->Write();
    if(protons->IsOpenForOutput())     protons->Write();
    if(neutrons->IsOpenForOutput())    neutrons->Write();
    if(detectorHits->IsOpenForOutput())detectorHits->Write();
    if(eventFlags->IsOpenForOutput())  eventFlags->Write();
    if(rawEvent->IsOpenForOutput())    rawEvent->Write();
    if(tagger->IsOpenForOutput())      tagger->Write();
    if(trigger->IsOpenForOutput())     trigger->Write();
    if(scalers->IsOpenForOutput())     scalers->Write();
    if(fitData->IsOpenForOutput())     fitData->Write();

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
            cout << "Can not check for valid events related to scaler. Now treeScaler available." << endl;
            return false;
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

/*Bool_t  GTreeManager::FindValidEvents(UInt_t& firstValidEvent, UInt_t& lastValidEvent)
{
    if(!FindValidEvents())
        return kFALSE;
    firstValidEvent = EventAtFirstScalerRead+1;
    lastValidEvent  = EventAtLastScalerRead;
    return kTRUE;
}*/

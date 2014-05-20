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
    photons(0),
    protons(0),
    pi0(0),
    eta(0),
    etap(0),
    fitData(0)
{
    etap = new GTreeMeson(this, TString("Etap"));
    eta = new GTreeMeson(this, TString("Eta"));
    pi0 = new GTreeMeson(this, TString("Pi0"));
    photons = new GTreeParticle(this, TString("Photons"));
    protons = new GTreeParticle(this, TString("Protons"));
    eventFlags = new GTreeEvent(this);
    rawEvent = new GTreeRawEvent(this);
    tagger = new GTreeTagger(this);
    trigger = new GTreeTrigger(this);
    scalers = new GTreeScaler(this);
    fitData = new GTreeFit(this);
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

    TObjArray   readList;

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
    if(protons)
    {
        if(protons->IsOpenForInput())
            readList.Add(protons);
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

    for(int i=min; i<=max; i++)
    {
        for(int l=0; l<readList.GetEntriesFast(); l++)
            ((GTree*)readList[l])->GetEntryFast(i);

        ProcessEvent();
    }
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
            return 0;
        }
    }

    for(int i=min; i<=max; i++)
    {
        scalers->GetEntryFast(i);
        ProcessEvent();
    }
}

Bool_t  GTreeManager::Process(const char* input_filename, const char* output_filename)
{
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
    if(file_in->Get("Protons"))
        protons->OpenForInput();



    if(file_out) delete file_out;
    file_out = TFile::Open(output_filename, "RECREATE");
    if(!file_out)
    {
        cout << "#ERROR: Can not create output file " << output_filename << "!" << endl;
        return kFALSE;
    }
    cout << "Created output file " << file_out->GetName() << "!" << file_out->GetTitle() << endl;

    return Process();
}

Bool_t  GTreeManager::Write()
{
    if(!file_out)   return kFALSE;

    if(pi0->IsOpenForOutput())         pi0->Write();
    if(eta->IsOpenForOutput())         eta->Write();
    if(etap->IsOpenForOutput())        etap->Write();
    if(photons->IsOpenForOutput())     photons->Write();
    if(protons->IsOpenForOutput())     protons->Write();
    if(eventFlags->IsOpenForOutput())  eventFlags->Write();
    if(rawEvent->IsOpenForOutput())    rawEvent->Write();
    if(tagger->IsOpenForOutput())      tagger->Write();
    if(trigger->IsOpenForOutput())     trigger->Write();
    if(scalers->IsOpenForOutput())     scalers->Write();
    if(fitData->IsOpenForOutput())     fitData->Write();

    return kTRUE;
}

Bool_t  GTreeManager::Write(const TNamed* object)
{
    if(!file_out)   return kFALSE;
    file_out->cd();
    object->Write();
    return kTRUE;
}


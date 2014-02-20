#include "GCorrectScalers.h"


using namespace std;


GCorrectScalers::GCorrectScalers()
{
}

GCorrectScalers::~GCorrectScalers()
{

}

void  GCorrectScalers::ProcessEvent()
{
    if(rawEvent->GetNCB() != 2 && rawEvent->GetNCB() != 6 && rawEvent->GetNCB() != 10)
        return;
    photons->Clear();
    protons->Clear();
    photons->SetEventNumber(actualEvent);
    for(Int_t i=0; i<rawEvent->GetNParticles(); i++)
    {
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_CB)
            photons->AddParticle(rawEvent->GetVector(i), i);
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_TAPS)
            protons->AddParticle(rawEvent->GetVector(i, 938.272046), i);
    }
    tagger->Fill();
    photons->Fill();
    protons->Fill();
    actualEvent++;
}

Bool_t  GCorrectScalers::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenRawEvent())    return kFALSE;
    if(!OpenTagger())    return kFALSE;
    if(!OpenScalers())    return kFALSE;

    if(scalers->GetNEntries()<2)    return kFALSE;
    scalers->GetEntry(0);
    EventAfterFirstScalerRead   = scalers->GetEventNumber()+1;
    scalers->GetEntry(scalers->GetNEntries()-1);
    EventAtLastScalerRead       = scalers->GetEventNumber();

    if(!Create(output_filename))    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;
    if(!CreateTagger())    return kFALSE;
    scalers->Clone(*file_out);

    actualEvent = EventAfterFirstScalerRead;
    TraverseEntries(EventAfterFirstScalerRead, EventAtLastScalerRead+1);

    if(!Write())    return kFALSE;
    return kTRUE;
}

#include "GParticleReconstruction.h"


using namespace std;


GParticleReconstruction::GParticleReconstruction()  :
    CBTime(0),
    TAPSTime(0),
    CBTimeAfterCut(0),
    TAPSTimeAfterCut(0)
{
    CBTimeCut[0]    = -1000000.0;
    CBTimeCut[1]    = 1000000.0;
    TAPSTimeCut[0]    = -1000000.0;
    TAPSTimeCut[1]    = 1000000.0;
}

GParticleReconstruction::~GParticleReconstruction()
{

}

void  GParticleReconstruction::ProcessEvent()
{
    if(rawEvent->GetNCB() != 2 && rawEvent->GetNCB() != 6 && rawEvent->GetNCB() != 10)
        return;

    for(Int_t i=0; i<rawEvent->GetNParticles(); i++)
    {
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_CB)
            CBTime->Fill(rawEvent->GetTime(i));
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_TAPS)
            TAPSTime->Fill(rawEvent->GetTime(i));
    }

    for(Int_t i=0; i<rawEvent->GetNParticles(); i++)
    {
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_CB)
        {
            if(rawEvent->GetTime(i)<CBTimeCut[0] || rawEvent->GetTime(i)>CBTimeCut[1])
                return;
        }
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_TAPS)
        {
            if(rawEvent->GetTime(i)<TAPSTimeCut[0] || rawEvent->GetTime(i)>TAPSTimeCut[1])
                return;
        }
    }

    GCorrectScalers::ProcessEvent();

    photons->Clear();
    protons->Clear();
    for(Int_t i=0; i<rawEvent->GetNParticles(); i++)
    {
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_CB)
        {
            CBTimeAfterCut->Fill(rawEvent->GetTime(i));
            photons->AddParticle(rawEvent->GetVector(i), i);
        }
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_TAPS)
        {
            TAPSTimeAfterCut->Fill(rawEvent->GetTime(i));
            protons->AddParticle(rawEvent->GetVector(i, 938.272046), i);
        }
    }
    photons->Fill();
    protons->Fill();
}

Bool_t  GParticleReconstruction::Process(const char* input_filename, const char* output_filename)
{
    if(!Create(output_filename))    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;

    file_out->cd();
    CBTime              = new TH1D("CBTimeOR", "CBTimeOR", 10000, -1000, 1000);
    TAPSTime            = new TH1D("TAPSTimeOR", "TAPSTimeOR", 10000, -1000, 1000);
    CBTimeAfterCut      = new TH1D("CBTimeOR_Cut", "CBTimeOR_Cut", 10000, -1000, 1000);
    TAPSTimeAfterCut    = new TH1D("TAPSTimeOR_Cut", "TAPSTimeOR_Cut", 10000, -1000, 1000);

    if(!GCorrectScalers::Process(input_filename, output_filename))  return kFALSE;

    if(!Write(CBTime))  return kFALSE;
    if(!Write(TAPSTime))  return kFALSE;
    if(!Write(CBTimeAfterCut))  return kFALSE;
    if(!Write(TAPSTimeAfterCut))  return kFALSE;
    return kTRUE;
}

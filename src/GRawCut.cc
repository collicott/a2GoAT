#include "GRawCut.h"
#include <string>

using namespace std;


GRawCut::GRawCut()
{
    nPhoton         = -1;
    nProton         = -1;
    
}

GRawCut::~GRawCut()
{

}

void  GRawCut::ProcessEvent()
{
    if(photons->GetNParticles() != nPhoton && nPhoton != -1)
        return;

    if(protons->GetNParticles() != nProton && nProton != -1)
        return;
            
    eventFlags->Fill();
    tagger->Fill();
    photons->Fill();
    protons->Fill();
}

Bool_t  GRawCut::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenPhotons())    return kFALSE;
    if(!OpenProtons())    return kFALSE;
    if(!OpenTagger())    return kFALSE;
    if(!OpenScalers())    return kFALSE;
    if(!OpenEventFlags())    return kFALSE;


    if(!Create(output_filename))    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;
    if(!CreateTagger())    return kFALSE;
    if(!CreateEventFlags())    return kFALSE;
    scalers->Clone(*file_out);

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;

}

void    GRawCut::SetNPhoton(const Int_t Multiplicity)
{
    nPhoton = Multiplicity;
}
void    GRawCut::SetNProton(const Int_t Multiplicity)
{
    nProton = Multiplicity;
}


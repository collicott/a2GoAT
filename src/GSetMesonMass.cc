#include "GSetMesonMass.h"


using namespace std;


TLorentzVector  GSetMesonMass::SetMass(const TLorentzVector& vec, const Double_t mass)
{
    TLorentzVector  res(0,0,0,vec.E()-vec.M()+mass);
    res.SetVect(TMath::Sqrt(res.E()*res.E() - mass*mass) * vec.Vect().Unit());
    return res;
}



GSetMesonMass::GSetMesonMass()
{
}

GSetMesonMass::~GSetMesonMass()
{

}

void  GSetMesonMass::ProcessEvent()
{
    if(photons->GetNParticles() == 6)
    {
        if(etap->GetNParticles() == 1)
        {
            pi0->Particle(0) = SetMass(pi0->Particle(0), MASS_PI0);
            pi0->Particle(1) = SetMass(pi0->Particle(1), MASS_PI0);
            eta->Particle(0) = SetMass(eta->Particle(0), MASS_ETA);
            etap->Particle(0) = pi0->Particle(0) + pi0->Particle(1) + eta->Particle(0);
        }
        else if(eta->GetNParticles() == 1)
        {
            pi0->Particle(0) = SetMass(pi0->Particle(0), MASS_PI0);
            pi0->Particle(1) = SetMass(pi0->Particle(1), MASS_PI0);
            pi0->Particle(2) = SetMass(pi0->Particle(2), MASS_PI0);
            eta->Particle(0) = pi0->Particle(0) + pi0->Particle(1) + pi0->Particle(2);
        }
        eventFlags->Fill();
        tagger->Fill();
        photons->Fill();
        protons->Fill();
        pi0->Fill();
        eta->Fill();
        etap->Fill();
    }
}

Bool_t  GSetMesonMass::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenEtap())    return kFALSE;
    if(!OpenEta())    return kFALSE;
    if(!OpenPi0())    return kFALSE;
    if(!OpenPhotons())    return kFALSE;
    if(!OpenProtons())    return kFALSE;
    if(!OpenTagger())    return kFALSE;
    if(!OpenScalers())    return kFALSE;
    if(!OpenEventFlags())    return kFALSE;


    if(!Create(output_filename))    return kFALSE;
    if(!CreateEtap())    return kFALSE;
    if(!CreateEta())    return kFALSE;
    if(!CreatePi0())    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;
    if(!CreateTagger())    return kFALSE;
    if(!CreateEventFlags())    return kFALSE;
    scalers->Clone(*file_out);

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;
}


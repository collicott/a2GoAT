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
        trigger->Fill();
        tagger->Fill();
        photons->Fill();
        protons->Fill();
        pi0->Fill();
        eta->Fill();
        etap->Fill();
    }
}

Bool_t  GSetMesonMass::Start()
{
    scalers->Clone();

    TraverseEntries(0, photons->GetNEntries()+1);

    return kTRUE;
}


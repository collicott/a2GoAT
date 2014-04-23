#include "GPlotCutMC.h"


using namespace std;


GPlotCutMC::GPlotCutMC()
{
    h_eta.invMassEta    = 0;
    h_eta.invMassPi0[0] = 0;
    h_eta.invMassPi0[1] = 0;
    h_eta.invMassPi0[2] = 0;
    
    h_etap.invMassEtap   = 0;
    h_etap.invMassPi0[0] = 0;
    h_etap.invMassPi0[1] = 0;
    h_etap.invMassEta    = 0;
}

GPlotCutMC::~GPlotCutMC()
{
    if(h_eta.invMassEta)   delete  h_eta.invMassEta;
    if(h_eta.invMassPi0[0])   delete  h_eta.invMassPi0[0];
    if(h_eta.invMassPi0[1])   delete  h_eta.invMassPi0[1];
    if(h_eta.invMassPi0[2])   delete  h_eta.invMassPi0[2];
    
    if(h_etap.invMassEtap)   delete  h_etap.invMassEtap;
    if(h_etap.invMassPi0[0])   delete  h_etap.invMassPi0[0];
    if(h_etap.invMassPi0[1])   delete  h_etap.invMassPi0[1];
    if(h_etap.invMassEta)   delete  h_etap.invMassEta;
}


    

void  GPlotCutMC::ProcessEvent()
{
        if(photons->GetNParticles() == 6)
        {
            if(etap->GetNParticles() == 1)
            {
                h_etap.invMassEtap->Fill(etap->Particle(0).M());
                h_etap.invMassPi0[0]->Fill(pi0->Particle(0).M());
                h_etap.invMassPi0[1]->Fill(pi0->Particle(1).M());
                h_etap.invMassEta->Fill(eta->Particle(0).M());
            }
            else if(eta->GetNParticles() == 1)
            {
                h_eta.invMassEta->Fill(eta->Particle(0).M());
                h_eta.invMassPi0[0]->Fill(pi0->Particle(0).M());
                h_eta.invMassPi0[1]->Fill(pi0->Particle(1).M());
                h_eta.invMassPi0[2]->Fill(pi0->Particle(2).M());
            }
        }
}

Bool_t  GPlotCutMC::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenPhotons())    return kFALSE;
    if(!OpenProtons())    return kFALSE;
    if(!OpenEtap())    return kFALSE;
    if(!OpenEta())    return kFALSE;
    if(!OpenPi0())    return kFALSE;
    if(!OpenTagger())    return kFALSE;

    if(!Create(output_filename))    return kFALSE;

    h_eta.invMassEta   = new TH1D("eta_invMass", "eta_invMass", 2000, 0, 2000);
    h_eta.invMassPi0[0]= new TH1D("eta_pi0a_invMass", "eta_pi0a_invMass", 2000, 0, 2000);
    h_eta.invMassPi0[1]= new TH1D("eta_pi0b_invMass", "eta_pi0b_invMass", 2000, 0, 2000);
    h_eta.invMassPi0[2]= new TH1D("eta_pi0c_invMass", "eta_pi0c_invMass", 2000, 0, 2000);

    h_etap.invMassEtap = new TH1D("etap_invMass", "etap_invMass", 2000, 0, 2000);
    h_etap.invMassPi0[0]= new TH1D("etap_pi0a_invMass", "etap_pi0a_invMass", 2000, 0, 2000);
    h_etap.invMassPi0[1]= new TH1D("etap_pi0b_invMass", "etap_pi0b_invMass", 2000, 0, 2000);
    h_etap.invMassEta   = new TH1D("etap_eta_invMass", "etap_eta_invMass", 2000, 0, 2000);

    TraverseEntries(0, pi0->GetNEntries()+1);
    
    Write(h_etap.invMassEtap);
    Write(h_etap.invMassPi0[0]);
    Write(h_etap.invMassPi0[1]);
    Write(h_etap.invMassEta);
    Write(h_eta.invMassEta);
    Write(h_eta.invMassPi0[0]);
    Write(h_eta.invMassPi0[1]);
    Write(h_eta.invMassPi0[2]);

    

    return kTRUE;
}


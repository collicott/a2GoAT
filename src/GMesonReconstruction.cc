#include "GMesonReconstruction.h"


using namespace std;


GMesonReconstruction::GMesonReconstruction()    :
    width_pi0(22),
    width_eta(40),
    width_etap(60)
{
}

GMesonReconstruction::~GMesonReconstruction()
{

}


Bool_t	GMesonReconstruction::Init()
{

    string  config = ReadConfig("Do-Meson-Reconstruction");
    if (strcmp(config.c_str(), "nokey") == 0)
    {
        meson_theta_min = 0.0;
        meson_theta_max = 180.0;
    }
    else if(sscanf( config.c_str(), "%*d %lf %lf\n", &meson_theta_min, &meson_theta_max) == 2)
    {
        cout << "meson reconstruction is active over theta range [" <<
        meson_theta_min << "," << meson_theta_max <<"]" << endl;
    }
    else
    {
        meson_theta_min = 0.0;
        meson_theta_max = 180.0;
    }

    config = ReadConfig("Cut-IM-Width-Pi0");
    sscanf( config.c_str(), "%lf\n", &width_pi0);
    if(width_pi0) cout << "Pi0 IM width cut set to " << width_pi0 << " MeV" << endl;
    else
    {
        width_pi0 = DEFAULT_PI0_IM_WIDTH;
        cout << "Pi0 IM width cut set to default (" << width_pi0 << " MeV)" << endl;
    }

    config = ReadConfig("Cut-IM-Width-Eta");
    sscanf( config.c_str(), "%lf\n", &width_eta);
    if(width_pi0) cout << "Eta IM width cut set to " << width_eta << " MeV" << endl;
    else
    {
        width_eta = DEFAULT_ETA_IM_WIDTH;
        cout << "Pi0 IM width cut set to default (" << width_eta << " MeV)" << endl;
    }

    config = ReadConfig("Cut-IM-Width-Eta-Prime");
    sscanf( config.c_str(), "%lf\n", &width_etap);
    if(width_etap) cout << "Eta-Prime IM width cut set to " << width_etap << " MeV" << endl;
    else
    {
        width_etap = DEFAULT_ETAP_IM_WIDTH;
        cout << "Eta-Prime IM width cut set to default (" << width_etap << " MeV)" << endl;
    }
    cout << endl;

    return kTRUE;
}

void  GMesonReconstruction::ProcessEvent()
{
    Int_t		index1	  [rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Int_t		index2	  [rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Int_t 		tempID    [rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Double_t 	diff_meson[rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Int_t 		sort_index[rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Bool_t 		is_meson  [rawEvent->GetNParticles()];

    //	TLorentzVector	initialParticle[GetNParticles()];
    TLorentzVector	reaction_p4;

    for (int i = 0; i < photons->GetNParticles(); i++)
    {
        if (photons->Particle(i).Theta() < meson_theta_min) continue; // user rejected theta region
        if (photons->Particle(i).Theta() > meson_theta_max) continue; // user rejected theta region

        is_meson[i] = kFALSE;

        reaction_p4 += photons->Particle(i);
        //daughter_list[ndaughter] = i;
        //ndaughter++;
    }
//###################################
//************From Here**************
//###################################
/*
    // LEVEL 1:
    // Test full reaction 4 momentum (ignoring protons and neutrons)
    // This is to test the following complex decays
    // n' -> pi+  pi-  n
    // n' -> pi0  pi0  n
    // n  -> pi0  pi0  pi0
    // n  -> pi0  pi+  pi-
    // n  -> pi0 (pi+  pi-  g)  - omega meson intermediate state
    // n  -> pi+  pi-  g		- direct n decay
    // 							    (or rho_0 intermediate state)

    Double_t diff_pi0  = TMath::Abs( reaction_p4.M() - (pdgDB->GetParticle("pi0" )->Mass()*1000)  )/width_pi0;
    Double_t diff_eta  = TMath::Abs( reaction_p4.M() - (pdgDB->GetParticle("eta" )->Mass()*1000)  )/width_eta;
    Double_t diff_etaP = TMath::Abs( reaction_p4.M() - (pdgDB->GetParticle("eta'")->Mass()*1000) )/width_etaP;

    if ((diff_pi0 <= 1.0) && (diff_pi0 < diff_eta) && (diff_eta < diff_etaP) && (ndaughter >= 2))
    {
        AddParticle(pdgDB->GetParticle("pi0")->PdgCode(),ndaughter,daughter_list);
        return;
    }

    if ((diff_eta <= 1.0) && (diff_eta < diff_pi0) && (diff_eta < diff_etaP) && (ndaughter >= 2))
    {
        AddParticle(pdgDB->GetParticle("eta")->PdgCode(),ndaughter,daughter_list);
        return;
    }

    if ((diff_etaP <= 1.0) && (diff_etaP < diff_pi0) && (diff_etaP < diff_eta) && (ndaughter >= 2))
    {
        AddParticle(pdgDB->GetParticle("eta'")->PdgCode(),ndaughter,daughter_list);
        return;
    }

    // LEVEL 2:
    // Well that didn't work, let's try to make some 2 particle checks
    // Loop over possible 2-particle combinations (skip i=j, ij = ji)
    // to check pi0 -> 2g, n -> 2g , n' -> 2g
    // Find all pairs within IM limits and sort by best Chi
    // Don't double count in sorting!
    // Reset daughter list
    ndaughter = 0;
    Int_t k = 0;
    for (int i = 0; i < GetNParticles(); i++)
    {
        if (GetTheta(i) < meson_theta_min) continue; // user rejected theta region
        if (GetTheta(i) > meson_theta_max) continue; // user rejected theta region

        if (Identified[i] == pdgDB->GetParticle("proton")->PdgCode()) continue;
        if (Identified[i] == pdgDB->GetParticle("neutron")->PdgCode()) continue;

        for (int j = i+1; j < GetNParticles(); j++)
        {
            if (GetTheta(j) < meson_theta_min) continue; // user rejected theta region
            if (GetTheta(j) > meson_theta_max) continue; // user rejected theta region

            if (Identified[i] == pdgDB->GetParticle("proton")->PdgCode()) continue;
            if (Identified[i] == pdgDB->GetParticle("neutron")->PdgCode()) continue;

            TLorentzVector p4 = GetVector(i) + GetVector(j);

            Double_t diff_pi0  = TMath::Abs( p4.M() - (pdgDB->GetParticle("pi0" )->Mass()*1000) )/width_pi0;
            Double_t diff_eta  = TMath::Abs( p4.M() - (pdgDB->GetParticle("eta" )->Mass()*1000) )/width_eta;
            Double_t diff_etaP = TMath::Abs( p4.M() - (pdgDB->GetParticle("eta'")->Mass()*1000) )/width_etaP;

            if ((diff_pi0 <= 1.0) && (diff_pi0 < diff_eta) && (diff_pi0 < diff_etaP))
            {
                diff_meson[k] 	= diff_pi0;
                tempID[k] 		= pdgDB->GetParticle("pi0")->PdgCode();
                index1[k]		= i;
                index2[k]		= j;
                k++;
            }
            if ((diff_eta <= 1.0) && (diff_eta < diff_pi0) && (diff_eta < diff_etaP))
            {
                diff_meson[k]	= diff_eta;
                tempID[k] 		= pdgDB->GetParticle("eta")->PdgCode();
                index1[k]		= i;
                index2[k]		= j;
                k++;
            }
            if ((diff_etaP <= 1.0) && (diff_etaP < diff_pi0) && (diff_etaP < diff_eta))
            {
                diff_meson[k]	= diff_etaP;
                tempID[k] 		= pdgDB->GetParticle("eta'")->PdgCode();
                index1[k]		= i;
                index2[k]		= j;
                k++;
            }
            }
        }

    TMath::Sort(k, diff_meson, sort_index, kFALSE);

    for (Int_t i = 0; i < k; i++)
    {
        //particle pair already involved in a meson reconstruction?
        if( is_meson[index1[i]] == kTRUE)  continue;
        if( is_meson[index2[i]] == kTRUE)  continue;

        // New meson identified!
        is_meson[index1[i]] = kTRUE;
        is_meson[index2[i]] = kTRUE;

        // Add to particle list
        daughter_list[0] = index1[i];
        daughter_list[1] = index2[i];

        AddParticle(tempID[i],2,daughter_list);
    }*/
}

Bool_t  GMesonReconstruction::Start()
{

}

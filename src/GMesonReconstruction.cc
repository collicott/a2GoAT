#include "GMesonReconstruction.h"
#include "GParticleReconstruction.h"

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

Bool_t GMesonReconstruction::Start()
{
    pi0->CloseForInput();
    eta->CloseForInput();
    etap->CloseForInput();

    if(!TraverseEntries(0, photons->GetNEntries()))		return kFALSE;

    return kTRUE;
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

Bool_t  GMesonReconstruction::ProcessEventWithoutFilling()
{
    pi0->Clear();
    eta->Clear();
    etap->Clear();

    Int_t       maxSubs = rootinos->GetNParticles() + photons->GetNParticles() + chargedPi->GetNParticles();

    Int_t		index1	  [maxSubs * maxSubs];
    Int_t		index2	  [maxSubs * maxSubs];
    Int_t 		tempID    [maxSubs * maxSubs];
    Double_t 	diff_meson[maxSubs * maxSubs];
    Int_t 		sort_index[maxSubs * maxSubs];
    Bool_t 		is_meson  [maxSubs];

    Int_t       countRootinos	= 0;
    Int_t       countPhotons	= 0;
    Int_t       countChargedPi	= 0;


    TLorentzVector* daughter_list[maxSubs];
    Int_t       	daughter_index[maxSubs];
    Int_t       	pdg_list[maxSubs];

	// one list including only rootinos and photons
    Int_t 			ndaughter   = 0;
    
	// another list including charged pions ((and electrons)) too (eta/eta')
    Int_t 			ndaughter_full   = 0;

//###################################
//************From Here**************
//###################################

    TLorentzVector	reaction_p4;
    TLorentzVector	reaction_p4_full;
    
    // LEVEL 1:
    // Test full reaction 4 momentum
    // We will ignoring protons and neutrons in all reconstructions
    // We will include only photons and rootinos in the pi0 reconstruction
    // This is to test the following complex decays
    // n' -> pi+  pi-  n
    // n' -> pi0  pi0  n
    // n  -> pi0  pi0  pi0
    // n  -> pi0  pi+  pi-
    // n  -> pi0 (pi+  pi-  g)  - omega meson intermediate state
    // n  -> pi+  pi-  g		- direct n decay
    // 							    (or rho_0 intermediate state)    

	for (int i = 0; i < rootinos->GetNParticles(); i++)
    {
        if (rootinos->Particle(i).Theta() < meson_theta_min) continue; // user rejected theta region
        if (rootinos->Particle(i).Theta() > meson_theta_max) continue; // user rejected theta region

        is_meson[ndaughter] = kFALSE;

        daughter_list[ ndaughter] = &rootinos->Particle(i);
        daughter_index[ndaughter] = i;
        pdg_list[ndaughter] 	  = pdg_rootino;

        reaction_p4 	 += rootinos->Particle(i);     
        reaction_p4_full += rootinos->Particle(i);  
        
		ndaughter++;   
        ndaughter_full++;
        
        countRootinos++;

    }
    for (int i = 0; i < photons->GetNParticles(); i++)
    {
        if (photons->Particle(i).Theta() < meson_theta_min) continue; // user rejected theta region
        if (photons->Particle(i).Theta() > meson_theta_max) continue; // user rejected theta region

        is_meson[ndaughter] = kFALSE;

        daughter_list[ ndaughter] = &photons->Particle(i);
        daughter_index[ndaughter] = i;
        pdg_list[ndaughter] 	  = pdgDB->GetParticle("gamma")->PdgCode();;

        reaction_p4 	 += photons->Particle(i);     
        reaction_p4_full += photons->Particle(i);  
        
		ndaughter++;   
        ndaughter_full++;
        
        countPhotons++;
    }
    for (int i = 0; i < chargedPi->GetNParticles(); i++)
    {
        if (chargedPi->Particle(i).Theta() < meson_theta_min) continue; // user rejected theta region
        if (chargedPi->Particle(i).Theta() > meson_theta_max) continue; // user rejected theta region

        is_meson[ndaughter_full] = kFALSE;

        daughter_list[ ndaughter_full] = &chargedPi->Particle(i);
        daughter_index[ndaughter_full] = i;
        pdg_list[ndaughter_full] 	   = pdgDB->GetParticle("pi+")->PdgCode();;

        reaction_p4_full += chargedPi->Particle(i);  
        ndaughter_full++;
      
        countChargedPi++;

    }

    Double_t diff_pi0  = TMath::Abs( reaction_p4.M() 	  - (pdgDB->GetParticle("pi0" )->Mass()*1000) )/width_pi0;
    Double_t diff_eta  = TMath::Abs( reaction_p4_full.M() - (pdgDB->GetParticle("eta" )->Mass()*1000) )/width_eta;
    Double_t diff_etap = TMath::Abs( reaction_p4_full.M() - (pdgDB->GetParticle("eta'")->Mass()*1000) )/width_etap;

    if ((diff_pi0 <= 1.0) && (diff_pi0 < diff_eta) && (diff_pi0 < diff_etap) && (ndaughter >= 2))
    {
		// Add pi0 (charged pion list not included)
        pi0->AddParticle(countRootinos, daughter_index, daughter_list, 
						countPhotons, &daughter_index[countRootinos], &daughter_list[countRootinos], 
						0, &daughter_index[0], &daughter_list[0]);
						
		// Remove rootinos and photons from original particle list
        rootinos->RemoveParticles(countRootinos, daughter_index);
        photons->RemoveParticles(countPhotons, &daughter_index[countRootinos]);

		// Complete reaction satisfied, return kTRUE
        return kTRUE;
    }
    else if ((diff_eta <= 1.0) && (diff_eta < diff_pi0) && (diff_eta < diff_etap) && (ndaughter >= 2))
    {
        // Add eta 
        eta->AddParticle(countRootinos, daughter_index, daughter_list, 
						countPhotons, &daughter_index[countRootinos], &daughter_list[countRootinos], 
						countChargedPi, &daughter_index[countRootinos+countPhotons], &daughter_list[countRootinos+countPhotons]);

		// Remove daughters from original particle list
        rootinos->RemoveParticles(countRootinos, daughter_index);
        photons->RemoveParticles(countPhotons, &daughter_index[countRootinos]);
        chargedPi->RemoveParticles(countChargedPi, &daughter_index[countRootinos+countPhotons]);
        
        // Complete reaction satisfied, return kTRUE
        return kTRUE;
    }
    else if ((diff_etap <= 1.0) && (diff_etap < diff_pi0) && (diff_etap < diff_eta) && (ndaughter >= 2))
    {
        // Add eta 
        etap->AddParticle(countRootinos, daughter_index, daughter_list, 
						countPhotons, &daughter_index[countRootinos], &daughter_list[countRootinos], 
						countChargedPi, &daughter_index[countRootinos+countPhotons], &daughter_list[countRootinos+countPhotons]);

		// Remove daughters from original particle list
        rootinos->RemoveParticles(countRootinos, daughter_index);
        photons->RemoveParticles(countPhotons, &daughter_index[countRootinos]);
        chargedPi->RemoveParticles(countChargedPi, &daughter_index[countRootinos+countPhotons]);
        
        // Complete reaction satisfied, return kTRUE
        return kTRUE;
    }

    // LEVEL 2:
    // Well that didn't work, let's try to make some 2 particle checks
    // Loop over possible 2-particle combinations (skip i=j, ij = ji)
    // to check pi0 -> 2g, n -> 2g , n' -> 2g
    // Find all pairs within IM limits and sort by best Chi
    // Use only photons and rootinos    
    // Don't double count in sorting!

    Int_t k = 0;
    for (int i = 0; i < ndaughter; i++)
    {
        if (daughter_list[i]->Theta() < meson_theta_min) continue; // user rejected theta region
        if (daughter_list[i]->Theta() > meson_theta_max) continue; // user rejected theta region

        for (int j = i+1; j < ndaughter; j++)
        {
            if (daughter_list[j]->Theta() < meson_theta_min) continue; // user rejected theta region
            if (daughter_list[j]->Theta() > meson_theta_max) continue; // user rejected theta region

            TLorentzVector p4 = *daughter_list[i] + *daughter_list[j];

            Double_t diff_pi0  = TMath::Abs( p4.M() - (pdgDB->GetParticle("pi0" )->Mass()*1000) )/width_pi0;
            Double_t diff_eta  = TMath::Abs( p4.M() - (pdgDB->GetParticle("eta" )->Mass()*1000) )/width_eta;
            Double_t diff_etap = TMath::Abs( p4.M() - (pdgDB->GetParticle("eta'")->Mass()*1000) )/width_etap;

            if ((diff_pi0 <= 1.0) && (diff_pi0 < diff_eta) && (diff_pi0 < diff_etap))
            {
                diff_meson[k] 	= diff_pi0;
                tempID[k] 		= pdgDB->GetParticle("pi0")->PdgCode();
                index1[k]		= i;
                index2[k]		= j;
                k++;
            }
            else if ((diff_eta <= 1.0) && (diff_eta < diff_pi0) && (diff_eta < diff_etap))
            {
                diff_meson[k]	= diff_eta;
                tempID[k] 		= pdgDB->GetParticle("eta")->PdgCode();
                index1[k]		= i;
                index2[k]		= j;
                k++;
            }
            else if ((diff_etap <= 1.0) && (diff_etap < diff_pi0) && (diff_etap < diff_eta))
            {
                diff_meson[k]	= diff_etap;
                tempID[k] 		= pdgDB->GetParticle("eta'")->PdgCode();
                index1[k]		= i;
                index2[k]		= j;
                k++;
            }
        }
    }

    TMath::Sort(k, diff_meson, sort_index, kFALSE);

    Int_t		nIndex_rootino_delete    = 0;
    Int_t		nIndex_photon_delete    = 0;
 //   Int_t		nIndex_chargedPi_delete = 0;
    Int_t		index_rootino_delete[GTreeParticle_MaxEntries];
    Int_t		index_photon_delete[GTreeParticle_MaxEntries];
  //  Int_t		index_chargedPi_delete[GTreeParticle_MaxEntries];

    for (Int_t i = 0; i < k; i++)
    {
        //particle pair already involved in a meson reconstruction?
        if(is_meson[index1[sort_index[i]]] == kTRUE)  continue;
        if(is_meson[index2[sort_index[i]]] == kTRUE)  continue;

        // New meson identified!
        is_meson[index1[sort_index[i]]] = kTRUE;
        is_meson[index2[sort_index[i]]] = kTRUE;

        // Add to particle list
        if(tempID[sort_index[i]] == pdgDB->GetParticle("pi0")->PdgCode())
        {
            pi0->AddParticle(daughter_index[index1[sort_index[i]]], *daughter_list[index1[sort_index[i]]], pdg_list[index1[sort_index[i]]], daughter_index[index2[sort_index[i]]], *daughter_list[index2[sort_index[i]]], pdg_list[index2[sort_index[i]]]);
            if(index1[sort_index[i]] < countRootinos)
            {
                index_rootino_delete[nIndex_rootino_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_rootino_delete++;
            }
            else if(index1[sort_index[i]] < (countRootinos+countPhotons))
            {
                index_photon_delete[nIndex_photon_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_photon_delete++;
            }
 /*           else
            {
                index_chargedPi_delete[nIndex_chargedPi_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_chargedPi_delete++;
            }*/
            if(index2[sort_index[i]] < countRootinos)
            {
                index_rootino_delete[nIndex_rootino_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_rootino_delete++;
            }
            else if(index2[sort_index[i]] < (countRootinos+countPhotons))
            {
                index_photon_delete[nIndex_photon_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_photon_delete++;
            }
/*            else
            {
                index_chargedPi_delete[nIndex_chargedPi_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_chargedPi_delete++;
            }*/
        }
        else if(tempID[sort_index[i]] == pdgDB->GetParticle("eta")->PdgCode())
        {
            eta->AddParticle(daughter_index[index1[sort_index[i]]], *daughter_list[index1[sort_index[i]]], pdg_list[index1[sort_index[i]]], daughter_index[index2[sort_index[i]]], *daughter_list[index2[sort_index[i]]], pdg_list[index2[sort_index[i]]]);
            if(index1[sort_index[i]] < countRootinos)
            {
                index_rootino_delete[nIndex_rootino_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_rootino_delete++;
            }
            else if(index1[sort_index[i]] < (countRootinos+countPhotons))
            {
                index_photon_delete[nIndex_photon_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_photon_delete++;
            }
/*          else
            {
                index_chargedPi_delete[nIndex_chargedPi_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_chargedPi_delete++;
            }*/
            if(index2[sort_index[i]] < countRootinos)
            {
                index_rootino_delete[nIndex_rootino_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_rootino_delete++;
            }
            else if(index2[sort_index[i]] < (countRootinos+countPhotons))
            {
                index_photon_delete[nIndex_photon_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_photon_delete++;
            }
/*            else
            {
                index_chargedPi_delete[nIndex_chargedPi_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_chargedPi_delete++;
            }*/
        }
        else if(tempID[sort_index[i]] == pdgDB->GetParticle("eta'")->PdgCode())
        {
            etap->AddParticle(daughter_index[index1[sort_index[i]]], *daughter_list[index1[sort_index[i]]], pdg_list[index1[sort_index[i]]], daughter_index[index2[sort_index[i]]], *daughter_list[index2[sort_index[i]]], pdg_list[index2[sort_index[i]]]);
            if(index1[sort_index[i]] < countRootinos)
            {
                index_rootino_delete[nIndex_rootino_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_rootino_delete++;
            }
            else if(index1[sort_index[i]] < (countRootinos+countPhotons))
            {
                index_photon_delete[nIndex_photon_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_photon_delete++;
            }
 /*           else
            {
                index_chargedPi_delete[nIndex_chargedPi_delete] = daughter_index[index1[sort_index[i]]];
                nIndex_chargedPi_delete++;
            }*/
            if(index2[sort_index[i]] < countRootinos)
            {
                index_rootino_delete[nIndex_rootino_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_rootino_delete++;
            }
            else if(index2[sort_index[i]] < (countRootinos+countPhotons))
            {
                index_photon_delete[nIndex_photon_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_photon_delete++;
            }
/*            else
            {
                index_chargedPi_delete[nIndex_chargedPi_delete] = daughter_index[index2[sort_index[i]]];
                nIndex_chargedPi_delete++;
            }*/
        }
    }
    rootinos->RemoveParticles(nIndex_rootino_delete, index_rootino_delete);
    photons->RemoveParticles(nIndex_photon_delete, index_photon_delete);
//    chargedPi->RemoveParticles(nIndex_chargedPi_delete, index_chargedPi_delete);


    return kTRUE;
}

void  GMesonReconstruction::ProcessEvent()
{
    if(!ProcessEventWithoutFilling())   return;

    eventParameters->SetNReconstructed(GetNReconstructed());
    eventParameters->Fill();

    pi0->Fill();
    eta->Fill();
    etap->Fill();
    FillReadList();
}

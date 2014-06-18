#include "GParticleReconstruction.h"


using namespace std;

GParticleReconstruction::GParticleReconstruction() :
    Identified(new Int_t[GTreeRawEvent_MAX]),
    Charge(new Int_t[GTreeRawEvent_MAX]),
    DoScalerCorrection(kFALSE),
    DoTrigger(kFALSE),
    E_Sum(50),
    multiplicity(1),
    charged_theta_min(0),
    charged_theta_max(180)
{
    CBTimeCut[0] = -1000000.0;
    CBTimeCut[1] = 1000000.0;
    TAPSTimeCut[0] = -1000000.0;
    TAPSTimeCut[1] = 1000000.0;
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t GParticleReconstruction::Trigger()
{
    if(trigger->GetESum() < E_Sum)
        return kFALSE;
    if(trigger->GetMult() < multiplicity)
        return kFALSE;
    return kTRUE;
}


Bool_t GParticleReconstruction::Start()
{
    photons->CloseForInput();
    electrons->CloseForInput();
    chargedPi->CloseForInput();
    protons->CloseForInput();
    neutrons->CloseForInput();

    if(!TraverseValidEvents())		return kFALSE;

    return kTRUE;
}

Bool_t	GParticleReconstruction::Init()
{		
    GDataChecks::Init();

	cout << endl << "Particle Reconstruction turned ON" << endl;

    //CB

    CB_type         = ReconstructionType_AllPhotons;
    CB_dEoverE_type = dEoverE_Cut_None;

    std::string config = ReadConfig("Cut-dE-E-CB-Proton");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type         = ReconstructionType_dEoverE;
            CB_dEoverE_type = dEoverE_Type(dEoverE_Cut_Proton | CB_dEoverE_type);
            if(!(Cut_CB_proton = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-CB-Proton set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-CB-Pion");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type         = ReconstructionType_dEoverE;
            CB_dEoverE_type = dEoverE_Type(dEoverE_Cut_PiPlus | CB_dEoverE_type);
            if(!(Cut_CB_pion = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-CB-Pion set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-CB-Electron");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            CB_type         = ReconstructionType_dEoverE;
            CB_dEoverE_type = dEoverE_Type(dEoverE_Cut_Electron | CB_dEoverE_type);
            if(!(Cut_CB_electron = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-CB-Pion set improperly" << endl;
            return kFALSE;
        }
    }

    //TAPS

    TAPS_type         = ReconstructionType_AllPhotons;
    TAPS_dEoverE_type = dEoverE_Cut_None;

    config = ReadConfig("TAPS-ALL-PROTONS");
    if (strcmp(config.c_str(), "nokey") != 0)
        TAPS_type   = ReconstructionType_AllProtons;

    config = ReadConfig("Cut-dE-E-TAPS-Proton");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type         = ReconstructionType_dEoverE;
            TAPS_dEoverE_type = dEoverE_Type(dEoverE_Cut_Proton | TAPS_dEoverE_type);
            if(!(Cut_TAPS_proton = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-TAPS-Proton set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-TAPS-Pion");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type         = ReconstructionType_dEoverE;
            TAPS_dEoverE_type = dEoverE_Type(dEoverE_Cut_PiPlus | TAPS_dEoverE_type);
            if(!(Cut_TAPS_pion = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-TAPS-Pion set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("Cut-dE-E-TAPS-Electron");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
        {
            TAPS_type           = ReconstructionType_dEoverE;
            TAPS_dEoverE_type     = dEoverE_Type(dEoverE_Cut_Electron | TAPS_dEoverE_type);
            if(!(Cut_TAPS_electron  = OpenCutFile(cutfilename,cutname)))
            {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
        }
        else
        {
            cout << "ERROR: Cut-dE-E-TAPS-Pion set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("CB-PARTICLE-TIME-CUT");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%lf %lf\n", &CBTimeCut[0], &CBTimeCut[1]) != 2)
        {
            cout << "ERROR: CB-PARTICLE-TIME-CUT set improperly" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("TAPS-PARTICLE-TIME-CUT");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        if(sscanf( config.c_str(), "%lf %lf\n", &TAPSTimeCut[0], &TAPSTimeCut[1]) != 2)
        {
            cout << "ERROR: CB-PARTICLE-TIME-CUT set improperly" << endl;
            return kFALSE;
        }
    }

/*
    std::string config = ReadConfig("Do-Charged-Particle-Reconstruction");
	if (strcmp(config.c_str(), "nokey") == 0) ReconstructChargedParticles = 0;	
	else if(sscanf( config.c_str(), "%d %lf %lf\n", 
		 &ReconstructChargedParticles,&charged_theta_min,&charged_theta_max) == 3)
	{
		cout << "Charged particle reconstruction is active over theta range [" << 
		charged_theta_min << "," << charged_theta_max <<"]" << endl;
	}	
	else if(sscanf( config.c_str(), "%d \n",  &ReconstructChargedParticles) == 1)
	{
		charged_theta_min = 0.0;
		charged_theta_max = 180.0;
	}
	else 
	{
		cout << "ERROR: Do-Charged-Particle-Reconstruction set improperly" << endl;
		return kFALSE;
	}
	
	if (ReconstructChargedParticles == 1) 
	{
		cout << "Full Charged particle reconstruction is active" << endl;
		
		config = ReadConfig("Cut-dE-E-CB-Proton");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_CB_proton_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_CB_proton_active = 1;
                Cut_CB_proton = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-CB-Proton set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-CB-Pion");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_CB_pion_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_CB_pion_active = 1;
                Cut_CB_pion = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-CB-Pion set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-CB-Electron");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_CB_electron_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_CB_electron_active = 1;
                Cut_CB_electron = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-CB-Electron set improperly" << endl;
			return kFALSE;
		}
		
		config = ReadConfig("Cut-dE-E-TAPS-Proton");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_TAPS_proton_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_TAPS_proton_active = 1;
                Cut_TAPS_proton = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-TAPS-Proton set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-TAPS-Pion");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_TAPS_pion_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_TAPS_pion_active = 1;
                Cut_TAPS_pion = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-TAPS-Pion set improperly" << endl;
			return kFALSE;
		}

		config = ReadConfig("Cut-dE-E-TAPS-Electron");
		if (strcmp(config.c_str(), "nokey") == 0) Cut_TAPS_electron_active = 0;
		else if(sscanf( config.c_str(), "%s %s\n", cutfilename,cutname) == 2)
		{
            try {
                Cut_TAPS_electron_active = 1;
                Cut_TAPS_electron = OpenCutFile(cutfilename,cutname);
            } catch (...) {
                cerr << "Failed to load cut! Terminating..." << endl;
                exit(1);
            }
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-TAPS-Electron set improperly" << endl;
			return kFALSE;
		}
		
	}
	else cout << "Charged particle reconstruction is NOT active." << endl;
    cout << endl;*/
	
	return kTRUE;
}

Bool_t	GParticleReconstruction::ProcessEventWithoutFilling()
{
    if(DoTrigger)
    {
        if(!Trigger())
            return kFALSE;
    }

    photons->Clear();
    electrons->Clear();
    chargedPi->Clear();
    protons->Clear();
    neutrons->Clear();

    for(Int_t i=0; i<rawEvent->GetNParticles(); i++)
    {
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_CB)
        {
            if(rawEvent->GetTime(i)<CBTimeCut[0] || rawEvent->GetTime(i)>CBTimeCut[1])
                return kFALSE;

            switch(CB_type)
            {
                case ReconstructionType_AllPhotons:
                    Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                    break;
                case ReconstructionType_dEoverE:
                    Identified[i] = pdg_rootino;
                    Charge[i] = 0;
                    if ((rawEvent->GetWC0_E(i) > 0.0) || (rawEvent->GetWC1_E(i) > 0.0)) 	Charge[i] = 1;
                    if ((rawEvent->Get_dE(i) > 0.0) && (rawEvent->Get_dE(i) < 1000.0)) 		Charge[i] = 1;
                    /**
                     * @todo Do TOF here!
                     * @todo Do Neutron ID here! (TOF + Cluster size)
                     **/
                    if (Charge[i] == 0)
                        Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                    if (rawEvent->GetTheta(i) < charged_theta_min) break; // user rejected theta region
                    if (rawEvent->GetTheta(i) > charged_theta_max) break; // user rejected theta region
                    ChargedReconstructionCB(i);
                    break;
            }
        }

        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_TAPS)
        {
            if(rawEvent->GetTime(i)<TAPSTimeCut[0] || rawEvent->GetTime(i)>TAPSTimeCut[1])
                return kFALSE;

            switch(TAPS_type)
            {
                case ReconstructionType_AllPhotons:
                    Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                    break;
                case ReconstructionType_AllProtons:
                    Identified[i] = pdgDB->GetParticle("proton")->PdgCode();
                    break;
                case ReconstructionType_dEoverE:
                    Identified[i] = pdg_rootino;
                    Charge[i] = 0;
                    if ((rawEvent->Get_dE(i) > 0.0) && (rawEvent->Get_dE(i) < 1000.0)) 		Charge[i] = 1;
                    /**
                     * @todo Do TOF here!
                     * @todo Do Neutron ID here! (TOF + Cluster size)
                     **/
                    if (Charge[i] == 0)
                        Identified[i] = pdgDB->GetParticle("gamma")->PdgCode();
                    if (rawEvent->GetTheta(i) < charged_theta_min) break; // user rejected theta region
                    if (rawEvent->GetTheta(i) > charged_theta_max) break; // user rejected theta region
                    ChargedReconstructionTAPS(i);
                    break;
            }
        }
    }

    for (int i = 0; i < rawEvent->GetNParticles(); i++)
    {
        // Finally add particles which were temporarily identified
        if (Identified[i] == pdgDB->GetParticle("proton")->PdgCode())
            protons->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("proton")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdgDB->GetParticle("pi+")->PdgCode())
            chargedPi->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("pi+")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdgDB->GetParticle("e-")->PdgCode())
            electrons->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("e-")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        else if (Identified[i] == pdgDB->GetParticle("gamma")->PdgCode())
            photons->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("gamma")->Mass()*1000), rawEvent->GetApparatus(i), rawEvent->Get_dE(i), rawEvent->GetWC0_E(i), rawEvent->GetWC1_E(i), rawEvent->GetTime(i), rawEvent->GetClusterSize(i));
        //else if (Identified[i] == pdg_rootino) 	AddParticle(pdg_rootino,i);
            //photons->AddParticle(rawEvent->GetVector(i, pdgDB->GetParticle("gamma")->Mass()*1000), i);
    }

    return kTRUE;
}


void	GParticleReconstruction::ProcessEvent()
{    
    if(!ProcessEventWithoutFilling())   return;

    trigger->SetEventNumber(GetEventNumber());

    photons->Fill();
    electrons->Fill();
    chargedPi->Fill();
    protons->Fill();
    neutrons->Fill();
    FillReadList();
}

void	GParticleReconstruction::ChargedReconstructionCB(const Int_t index)
{
    if(CB_dEoverE_type & dEoverE_Cut_Proton)
    {
        if(Cut_CB_proton->IsInside(rawEvent->GetEk(index),rawEvent->Get_dE(index)))
            Identified[index] = pdgDB->GetParticle("proton")->PdgCode();
    }
    if(CB_dEoverE_type & dEoverE_Cut_PiPlus)
    {
        if(Cut_CB_pion->IsInside(rawEvent->GetEk(index),rawEvent->Get_dE(index)))
            Identified[index] = pdgDB->GetParticle("pi+")->PdgCode();
    }

    if(CB_dEoverE_type & dEoverE_Cut_Electron)
    {
        if(Cut_CB_electron->IsInside(rawEvent->GetEk(index),rawEvent->Get_dE(index)))
            Identified[index] = pdgDB->GetParticle("e-")->PdgCode();
    }
}

void	GParticleReconstruction::ChargedReconstructionTAPS(const Int_t index)
{
    if(TAPS_dEoverE_type & dEoverE_Cut_Proton)
    {
        if(Cut_TAPS_proton->IsInside(rawEvent->GetEk(index),rawEvent->Get_dE(index)))
            Identified[index] = pdgDB->GetParticle("proton")->PdgCode();
    }
    if(TAPS_dEoverE_type & dEoverE_Cut_PiPlus)
    {
        if(Cut_TAPS_pion->IsInside(rawEvent->GetEk(index),rawEvent->Get_dE(index)))
            Identified[index] = pdgDB->GetParticle("pi+")->PdgCode();
    }

    if(TAPS_dEoverE_type & dEoverE_Cut_Electron)
    {
        if(Cut_TAPS_electron->IsInside(rawEvent->GetEk(index),rawEvent->Get_dE(index)))
            Identified[index] = pdgDB->GetParticle("e-")->PdgCode();
    }
}


void	GParticleReconstruction::MesonReconstruction()
{
    /*Int_t		index1	  [rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Int_t		index2	  [rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Int_t 		tempID    [rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Double_t 	diff_meson[rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Int_t 		sort_index[rawEvent->GetNParticles() * (rawEvent->GetNParticles() -1)];
    Bool_t 		is_meson  [rawEvent->GetNParticles()];

    Int_t 		ndaughter = 0;
    Int_t		daughter_list[GetNParticles()];

//	TLorentzVector	initialParticle[GetNParticles()];
    TLorentzVector	reaction_p4;

    for (int i = 0; i < GetNParticles(); i++)
    {
        if (GetTheta(i) < meson_theta_min) continue; // user rejected theta region
        if (GetTheta(i) > meson_theta_max) continue; // user rejected theta region

        // Construct reaction four-vector ignoring protons and neutrons
        if (Identified[i] == pdgDB->GetParticle("proton" )->PdgCode() ) continue;
        if (Identified[i] == pdgDB->GetParticle("neutron")->PdgCode() ) continue;

//		initialParticle[i] = GetVector(i);

        is_meson[i] = kFALSE;

        reaction_p4 += GetVector(i);
        daughter_list[ndaughter] = i;
        ndaughter++;
    }

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
    }
*/
}



/**
 * @brief Load a cut from a ROOT file
 * @param filename The ROOT file to open
 * @param cutname The name of the TCutG object to load
 * @return Pointer to the cut
 * @throw bool false on any error
 */
TCutG*	GParticleReconstruction::OpenCutFile(Char_t* filename, Char_t* cutname)
{
	CutFile 	= new TFile(filename, "READ");

    if( !CutFile || !CutFile->IsOpen() ) {
        cerr << "Can't open cut file: " << filename << endl;
        throw false;
    }


    // Try to find a TCutG with the name we want
    // GetObject checks the type to be TCutG,
    // see http://root.cern.ch/root/html534/TDirectory.html#TDirectory:GetObject
    CutFile->GetObject(cutname, Cut);

    if( !Cut ) {
        cerr << "Could not find a TCutG with the name " << cutname << " in " << filename << endl;
        throw false;
    }

    TCutG* Cut_clone = Cut;
    CutFile->Close();

    cout << "cut file " << filename << 	" opened (Cut-name = " << cutname << ")"<< endl;
    return Cut_clone;
}

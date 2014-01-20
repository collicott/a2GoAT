
#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction() :
							Identified(0),
							nParticles(0),
							nDaughterList(0),
							Charge(0)
{
	Identified 	= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
	Charge	 	= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t	GParticleReconstruction::PostInit()
{
	cout << endl << "Particle Reconstruction turned ON" << endl;

	cout << "Opening particle reconstruction tree: ";	
	InitTreeParticles();
	cout << endl;
	
	config = ReadConfig("Do-Charged-Particle-Reconstruction");	
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
			Cut_CB_proton_active = 1;
			Cut_CB_proton = OpenCutFile(cutfilename,cutname);
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
			Cut_CB_pion_active = 1;
			Cut_CB_pion = OpenCutFile(cutfilename,cutname);
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
			Cut_CB_electron_active = 1;
			Cut_CB_electron = OpenCutFile(cutfilename,cutname);
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
			Cut_TAPS_proton_active = 1;
			Cut_TAPS_proton = OpenCutFile(cutfilename,cutname);
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
			Cut_TAPS_pion_active = 1;
			Cut_TAPS_pion = OpenCutFile(cutfilename,cutname);
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
			Cut_TAPS_electron_active = 1;
			Cut_TAPS_electron = OpenCutFile(cutfilename,cutname);
		}
		else 
		{
			cout << "ERROR: Cut-dE-E-TAPS-Electron set improperly" << endl;
			return kFALSE;
		}
		
	}
	else cout << "Charged particle reconstruction is NOT active." << endl;
	cout << endl;
	
	config = ReadConfig("Do-Meson-Reconstruction");	
	if (strcmp(config.c_str(), "nokey") == 0) ReconstructMesons = 0;	
	else if(sscanf( config.c_str(), "%d %lf %lf\n", 
		 &ReconstructMesons,&meson_theta_min, &meson_theta_max) == 3)
	{
		cout << "meson reconstruction is active over theta range [" << 
		meson_theta_min << "," << meson_theta_max <<"]" << endl;
	}
	else if(sscanf( config.c_str(), "%d \n",  &ReconstructMesons) == 1)
	{
		cout << "Full meson reconstruction is active" << endl;
		meson_theta_min = 0.0;
		meson_theta_max = 180.0;
	}
	else 
	{
		cout << "ERROR: Do-Meson-Reconstruction set improperly" << endl;
		return kFALSE;
	}
	

	if (ReconstructMesons == 1) 
	{
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
		sscanf( config.c_str(), "%lf\n", &width_etaP);
		if(width_etaP) cout << "Eta-Prime IM width cut set to " << width_etaP << " MeV" << endl;
		else 
		{
			width_etaP = DEFAULT_ETAP_IM_WIDTH; 
			cout << "Eta-Prime IM width cut set to default (" << width_etaP << " MeV)" << endl;
		}		
		cout << endl;
	}
	else cout << "Meson reconstruction is NOT active." << endl;	
	
	return kTRUE;
}

void	GParticleReconstruction::Reconstruct()
{
	InitEvent();
	CheckNeutrality();
    
	/**
	 * @todo Do TOF here!
	 * @todo Do Neutron ID here! (TOF + Cluster size)
	 **/
	
	PhotonReconstruction();	
	
	if(ReconstructChargedParticles == 1) 	ChargedReconstruction();
	if(ReconstructMesons == 1)	 			MesonReconstruction();

	for (int i = 0; i < GetNParticles(); i++) 
	{
		// Finally add particles which were temporarily identified
		if (Identified[i] == pdg_chpion) 	AddParticle(pdg_chpion,i);
		if (Identified[i] == pdg_electron) 	AddParticle(pdg_electron,i);
		if (Identified[i] == pdg_photon) 	AddParticle(pdg_photon,i);
		if (Identified[i] == pdg_rootino) 	AddParticle(pdg_rootino,i);

	}
}

void	GParticleReconstruction::InitEvent()
{
	nParticles = 0; 	SetNParticles(nParticles);
	nDaughterList = 0; 	SetNDaughterList(nDaughterList);

	// Mark everything as rootino	
	for (int i = 0; i < GetNParticles(); i++)
	{
		Identified[i] = pdg_rootino; 
		SetInputMass(i,0.0);
	}	
}

void 	GParticleReconstruction::CheckNeutrality()
{
	// Rough start, this will soon be user controlled
	for (int i = 0; i < GetNParticles(); i++){
	
		if (  ((Get_dE(i) > 0.0) && (Get_dE(i) < 1000.0)) 
			|| (GetWC0_E(i) > 0.0) || (GetWC1_E(i) > 0.0) ) 
		{
			 Charge[i] = 1;
		}
		else Charge[i] = 0;
	}
}

void	GParticleReconstruction::PhotonReconstruction()
{
	// Mark neutral rootinos as photons (for now)
	// Note if neutron ID is done before this, they are left as neutrons
	
	for (int i = 0; i < GetNParticles(); i++) 
	{
		if ((Identified[i] == pdg_rootino) && (Charge[i] == 0))
		{			
			Identified[i] = pdg_photon;
		}
	}
}

void	GParticleReconstruction::ChargedReconstruction()
{
	
	for (int i = 0; i < GetNParticles(); i++) 
	{
		if (GetTheta(i) < charged_theta_min) continue; // user rejected theta region
		if (GetTheta(i) > charged_theta_max) continue; // user rejected theta region
		
		if (GetApparatus(i) == EAppCB) 
		{	
			if(Cut_CB_proton_active)
			{
				Cut_proton = Cut_CB_proton;
				Cut_proton_active = 1;
			}
			else Cut_proton_active = 0;
			if(Cut_CB_proton_active)
			{
				Cut_pion = Cut_CB_pion;
				Cut_pion_active = 1;
			}
			else Cut_pion_active = 0;
			if(Cut_CB_electron_active)
			{
				Cut_electron = Cut_CB_electron;
				Cut_electron_active = 1;
			}
			else Cut_electron_active = 0;
		}
		else if (GetApparatus(i) == EAppTAPS)
		{
			if(Cut_TAPS_proton_active)
			{
				Cut_proton = Cut_TAPS_proton;
				Cut_proton_active = 1;
			}
			else Cut_proton_active = 0;
			if(Cut_TAPS_proton_active)
			{
				Cut_pion = Cut_TAPS_pion;
				Cut_pion_active = 1;
			}
			else Cut_pion_active = 0;
			if(Cut_TAPS_electron_active)
			{
				Cut_electron = Cut_TAPS_electron;
				Cut_electron_active = 1;
			}
			else Cut_electron_active = 0;	

		}
		if(Cut_proton_active) 
		{
			if(Cut_proton->IsInside(GetEk(i),Get_dE(i)))
			{
				SetInputMass(i,m_proton);	
				AddParticle(pdg_proton,i);

			}
		}
		
		if(Cut_pion_active) 
		{		
			if(Cut_pion->IsInside(GetEk(i),Get_dE(i)))
			{
				SetInputMass(i,m_chpion);			
				Identified[i] = pdg_chpion; 
			}
		}
		
		if(Cut_electron_active) 
		{		
			if(Cut_electron->IsInside(GetEk(i),Get_dE(i)))
			{
				SetInputMass(i,m_electron);			
				Identified[i] = pdg_electron;
			}
		}	
				
	}			
				
}

void	GParticleReconstruction::MesonReconstruction()
{
	Int_t		index1	  [GetNParticles() * (GetNParticles() -1)];
	Int_t		index2	  [GetNParticles() * (GetNParticles() -1)];	
	Int_t 		tempID    [GetNParticles() * (GetNParticles() -1)];
	Double_t 	diff_meson[GetNParticles() * (GetNParticles() -1)];
	Int_t 		sort_index[GetNParticles() * (GetNParticles() -1)];
	Bool_t 		is_meson  [GetNParticles()];
	
	Int_t 		ndaughter = 0;
	Int_t		daughter_list[GetNParticles()];

	TLorentzVector	initialParticle[GetNParticles()];
	TLorentzVector	reaction_p4;	
		
	for (int i = 0; i < GetNParticles(); i++) 
	{
		if (GetTheta(i) < meson_theta_min) continue; // user rejected theta region
		if (GetTheta(i) > meson_theta_max) continue; // user rejected theta region
		
		initialParticle[i] = GetVector(i);

		is_meson[i] = kFALSE;
		
		// Construct reaction four-vector ignoring protons and neutrons
		if ((Identified[i] != pdg_proton) &&  (Identified[i] != pdg_neutron))
		{
			reaction_p4 += initialParticle[i];
			daughter_list[ndaughter] = i;
			ndaughter++;
		}
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
	
	Double_t diff_eta  = TMath::Abs( reaction_p4.M() - m_eta )/width_eta;
	Double_t diff_etaP = TMath::Abs( reaction_p4.M() - m_etaP)/width_etaP;
			
	if ((diff_eta <= 1.0) && (diff_eta < diff_etaP))
	{
		AddParticle(pdg_eta,ndaughter,daughter_list);
		return;		
	}
	if ((diff_etaP <= 1.0) && (diff_etaP < diff_eta))
	{
		AddParticle(pdg_etaP,ndaughter,daughter_list);
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
		
		if (Identified[i] == pdg_proton) 	continue;
		if (Identified[i] == pdg_neutron) 	continue;
		
		for (int j = i+1; j < GetNParticles(); j++) 
		{
			if (Identified[j] == pdg_proton) 	continue;
			if (Identified[j] == pdg_neutron) 	continue;
			
			TLorentzVector p4 = initialParticle[i] + initialParticle[j];
			
			Double_t diff_pi0  = TMath::Abs( p4.M() - m_pi0 )/width_pi0;
			Double_t diff_eta  = TMath::Abs( p4.M() - m_eta )/width_eta;
			Double_t diff_etaP = TMath::Abs( p4.M() - m_etaP)/width_etaP;
			
			if (diff_pi0 <= 1.0) 
			{
				diff_meson[k] 	= diff_pi0; 
				tempID[k] 		= pdg_pi0;
				index1[k]		= i;
				index2[k]		= j;
				k++;
			}
			if (diff_eta <= 1.0) 
			{
				diff_meson[k]	= diff_eta; 
				tempID[k] 		= pdg_eta;
				index1[k]		= i;
				index2[k]		= j;				
				k++;
			}
			if (diff_etaP <= 1.0) 
			{
				diff_meson[k]	= diff_etaP; 
				tempID[k] 		= pdg_etaP;
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
		
		if( tempID[i] == pdg_pi0) 
		{
			ndaughter = 2;
			daughter_list[0] = index1[i];
			daughter_list[1] = index2[i];
			AddParticle(pdg_pi0,ndaughter,daughter_list);
		}			
		if( tempID[i] == pdg_eta) 	
		{
			ndaughter = 2;
			daughter_list[0] = index1[i];
			daughter_list[1] = index2[i];
			AddParticle(pdg_eta,ndaughter,daughter_list);
		}
		if( tempID[i] == pdg_etaP) 			
		{
			ndaughter = 2;
			daughter_list[0] = index1[i];
			daughter_list[1] = index2[i];
			AddParticle(pdg_etaP,ndaughter,daughter_list);
		}
		
	}
		
}

void	GParticleReconstruction::AddParticle(Int_t pdg_code, Int_t nindex, Int_t index_list[])
{

	TLorentzVector part  = GetVector(index_list[0]);
	
	Double_t Ek			 = GetEk(index_list[0]);
	Double_t time		 = GetTime(index_list[0]);
	Double_t dE 		 = Get_dE(index_list[0]);
	Double_t WCO_E 		 = GetWC0_E(index_list[0]);	
	Double_t WC1_E 		 = GetWC1_E(index_list[0]);	
		
	Double_t WC_Vertex_X = GetWC_Vertex_X(index_list[0]);
	Double_t WC_Vertex_Y = GetWC_Vertex_Y(index_list[0]);	
	Double_t WC_Vertex_Z = GetWC_Vertex_Z(index_list[0]);
	
	Int_t 	 clusterSize = GetClusterSize(index_list[0]);
	UChar_t  Apparatus   = GetApparatus(index_list[0]);
	Int_t  	 SumCharge   = Charge[index_list[0]];
	
	Int_t	 ndaughters  = 0;
	if (nindex > 1) 
	{	
		// store in daughter list for meson analysis
		SetDaughter_index(nDaughterList,nParticles);
		SetDaughter_E(nDaughterList,	 GetEk(index_list[0]));
		SetDaughter_Theta(nDaughterList, GetTheta(index_list[0]));
		SetDaughter_Phi(nDaughterList,	 GetPhi(index_list[0]));
		SetDaughter_PDG(nDaughterList,   Identified[index_list[0]]);
		
		ndaughters++; 	 // particle counter
		nDaughterList++; // event counter 
		
		// Set new identification
		Identified[index_list[0]] = pdg_code;
				
		// Improve this by adding check to see if it is a real value 
		// and only include in average if it is real (aka E, dE, and WC vertex)

		for(Int_t i = 1; i < nindex; i++)
		{
	
			part += GetVector(index_list[i]);

			Ek 	 	+= GetEk(index_list[i]); 	
			time 	+= GetTime(index_list[i]);
			dE 	 	+= Get_dE(index_list[i]); 		
		
			WCO_E 	+= GetWC0_E(index_list[i]);	
			WC1_E 	+= GetWC1_E(index_list[i]);	
			
			WC_Vertex_X += GetWC_Vertex_X(index_list[i]); 	
			WC_Vertex_Y += GetWC_Vertex_Y(index_list[i]);	
			WC_Vertex_Z += GetWC_Vertex_Z(index_list[i]);	
			
			clusterSize += GetClusterSize(index_list[i]);
			if(Apparatus != GetApparatus(index_list[i])) Apparatus = 3;
			
			SumCharge += Charge[index_list[i]];
			
			// store in daughter list for meson analysis
			SetDaughter_index(nDaughterList,nParticles);
			SetDaughter_E(nDaughterList,	 GetEk(index_list[i]));
			SetDaughter_Theta(nDaughterList,GetTheta(index_list[i]));
			SetDaughter_Phi(nDaughterList,	 GetPhi(index_list[i]));
			SetDaughter_PDG(nDaughterList,  Identified[index_list[i]]);

			ndaughters++; 
			nDaughterList++;			
			
			// Set new identification
			Identified[index_list[i]] = pdg_code;		
				
		}
		
		// Average some values
		time = time/nindex;
		WC_Vertex_X = WC_Vertex_X/nindex;
		WC_Vertex_Y = WC_Vertex_Y/nindex;
		WC_Vertex_Z = WC_Vertex_Z/nindex;
		
	}
	else Identified[index_list[0]] = pdg_code;
	
	Double_t Px 	= part.Px();
	Double_t Py 	= part.Py();
	Double_t Pz 	= part.Pz();
	Double_t Theta 	= part.Theta() * TMath::RadToDeg();
	Double_t Phi 	= part.Phi()   * TMath::RadToDeg();
	Double_t Mass   = part.M();
	Ek 				= part.E() - part.M();
	
	SetPDG(nParticles,pdg_code);	
	SetCharge(nParticles,SumCharge);
	SetPx(nParticles,Px);
	SetPy(nParticles,Py);
	SetPz(nParticles,Pz);
	SetTheta(nParticles,Theta);
	SetPhi(nParticles,Phi);	
	SetMass(nParticles,Mass);
	SetEk(nParticles,Ek);
	SetTime(nParticles,time);
	SetClusterSize(nParticles,clusterSize);
	SetApparatus(nParticles,Apparatus);
	Set_dE(nParticles,dE);
	SetWC0_E(nParticles,WCO_E);
	SetWC1_E(nParticles,WC1_E);
	SetWC_Vertex_X(nParticles,WC_Vertex_X);
	SetWC_Vertex_Y(nParticles,WC_Vertex_Y);
	SetWC_Vertex_Z(nParticles,WC_Vertex_Z);
	SetNDaughterList(nDaughterList);
	SetNDaughters(nParticles,ndaughters);
	
	nParticles++;
	
	SetNParticles(nParticles);
	
}

TCutG*	GParticleReconstruction::OpenCutFile(Char_t* filename, Char_t* cutname)
{
	CutFile 	= new TFile(filename, "READ");
	Cut 		= (TCutG*)CutFile->Get(cutname);
	
	TCutG* Cut_clone = Cut;
	CutFile->Close();

	cout << "cut file " << filename << 
						" opened (Cut-name = " << cutname << ")"<< endl;
	return Cut_clone;
	
}

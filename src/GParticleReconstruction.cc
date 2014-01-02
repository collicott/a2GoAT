
#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction() :
							Identified(0),
							nParticles(0),
							PDG(0),
							nPi0(0),
							nEta(0),
							nEtaP(0),
							nProton(0),
							nChPion(0),
							nElectron(0)
{
	Identified 	= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
	PDG 		= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
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
	
	config = ReadConfig("Do-Charged-Particle-Reconstruction",GetConfigFile());	
	sscanf( config.c_str(), "%d\n", &ReconstructChargedParticles);

	if (ReconstructChargedParticles) 
	{
		cout << "Charged particle reconstruction is active:" << endl;
	
		config = ReadConfig("Cut-dE-E-CB-Proton",GetConfigFile());	
		sscanf( config.c_str(), "%s %s\n", cutfilename,cutname);
		Cut_CB_proton = OpenCutFile(cutfilename,cutname);
		
		config = ReadConfig("Cut-dE-E-CB-Pion",GetConfigFile());	
		sscanf( config.c_str(), "%s %s\n", cutfilename,cutname);
		Cut_CB_pion   = OpenCutFile(cutfilename,cutname);

		config = ReadConfig("Cut-dE-E-TAPS-Pion",GetConfigFile());	
		sscanf( config.c_str(), "%s %s\n", cutfilename,cutname);
		Cut_TAPS_pion   = OpenCutFile(cutfilename,cutname);	

		config = ReadConfig("Cut-dE-E-TAPS-Proton",GetConfigFile());	
		sscanf( config.c_str(), "%s %s\n", cutfilename,cutname);
		Cut_TAPS_proton   = OpenCutFile(cutfilename,cutname);
		cout << endl;
	}
	else cout << "Charged particle reconstruction is NOT active." << endl;
	
	config = ReadConfig("Do-Meson-Reconstruction",GetConfigFile());	
	sscanf( config.c_str(), "%d\n", &ReconstructMesons);

	if (ReconstructMesons) 
	{
		cout << "Meson reconstruction is active:" << endl;

		config = ReadConfig("Cut-IM-Width-Pi0",GetConfigFile());	
		sscanf( config.c_str(), "%lf\n", &width_pi0);
		if(width_pi0) cout << "Pi0 IM width cut set to " << width_pi0 << " MeV" << endl;
		else 
		{
			width_pi0 = DEFAULT_PI0_IM_WIDTH; 
			cout << "Pi0 IM width cut set to default (" << width_pi0 << " MeV)" << endl;
		}

		config = ReadConfig("Cut-IM-Width-Eta",GetConfigFile());	
		sscanf( config.c_str(), "%lf\n", &width_eta);
		if(width_pi0) cout << "Eta IM width cut set to " << width_eta << " MeV" << endl;
		else 
		{
			width_eta = DEFAULT_ETA_IM_WIDTH; 
			cout << "Pi0 IM width cut set to default (" << width_eta << " MeV)" << endl;
		}

		config = ReadConfig("Cut-IM-Width-Eta-Prime",GetConfigFile());	
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
	
	// read from PDG database in future (not configs)
	m_pi0  = 135.0;
	m_eta  = 545.0;
	m_etaP = 958.0;
	m_proton = 938.3;
	m_chpi = 139.6;
	m_electron = 0.511;	
	
	pdg_rootino = 0;
	pdg_pi0  = 1;
	pdg_eta  = 2; 
	pdg_etaP = 3;	
	pdg_proton = 4;
	pdg_chpi = 5;
	pdg_electron = 6;

	return kTRUE;
}

void	GParticleReconstruction::Reconstruct()
{
	nParticles = 0;
	nPi0  = 0;	
	nEta  = 0;	
	nEtaP = 0;
	nProton = 0;
	nChPion = 0;
	nElectron = 0;
	
	SetNParticles(nParticles);	
	
	for (int i = 0; i < GetNParticles(); i++){
		Identified[i] = 0; 
		SetInputMass(i,0.0);
	}	
	
	if(ReconstructChargedParticles) ChargedReconstruction();
	if(ReconstructMesons)	 MesonReconstruction();

	for (int i = 0; i < GetNParticles(); i++) 
	{
		if (Identified[i] == 2) AddParticle(pdg_chpi,i);		
		if (Identified[i] == 0) AddParticle(pdg_rootino,i);
	}

}

void	GParticleReconstruction::ChargedReconstruction()
{
	
	nProton	 	= 0;
	nElectron 	= 0;	
	nChPion		= 0;	
	
	for (int i = 0; i < GetNParticles(); i++) 
	{
		if (GetApparatus(i) == EAppCB) 
		{
			Cut_proton  = Cut_CB_proton;
			Cut_pion	= Cut_CB_pion;
		}
		else if (GetApparatus(i) == EAppTAPS)
		{
			Cut_proton  = Cut_TAPS_proton;
			Cut_pion	= Cut_TAPS_pion;
		}
			
		if(Cut_proton->IsInside(GetEk(i),Get_dE(i)))
		{
			SetInputMass(i,m_proton);			
			AddParticle(pdg_proton,i);  //  <--- Look it's a proton!
			Identified[i] = 1;
			nProton++;
		}
		else if(Cut_pion->IsInside(GetEk(i),Get_dE(i)))
		{
			SetInputMass(i,m_chpi);			
			// Not ready to include in full particle list because the
			// charged pion may be part of an eta decay
			Identified[i] = 2; // Temporary state
			nChPion++;
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
		initialParticle[i] = GetVector(i);

		is_meson[i] = kFALSE;
		
		if (Identified[i] == 0) 
		{
			reaction_p4 += initialParticle[i];
			daughter_list[ndaughter] = i;
			ndaughter++;
		}
	}
	 
	// LEVEL 1:   
	// Test full reaction 4 momentum (ignoring protons and electrons)
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
		// Reaction is an eta!		
		AddParticle(pdg_eta,ndaughter,daughter_list);
		nEta++;
		return;		
	}
	if ((diff_etaP <= 1.0) && (diff_etaP < diff_eta))
	{
		// Reaction is an eta'!
		AddParticle(pdg_etaP,ndaughter,daughter_list);
		nEtaP++;
		return;
	}				
	
	// LEVEL 2:
	// Well that didn't work, let's try to make some 2 photon checks	
	// Loop over possible 2-photon combinations (skip i=j, ij = ji)
	// to check pi0 -> 2g, n -> 2g , n' -> 2g
	// Find all pairs within IM limits and sort by best Chi
	// Don't double count in sorting!
	// Reset daughter list
	ndaughter = 0;
	Int_t k = 0;
	for (int i = 0; i < GetNParticles(); i++) 
    {
		if(Identified[i] == 1) continue;
		
		for (int j = i+1; j < GetNParticles(); j++) 
		{
			if(Identified[j] == 1) continue;
			
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
			// Found a pi0!
			ndaughter = 2;
			daughter_list[0] = index1[i];
			daughter_list[1] = index2[i];
			AddParticle(pdg_pi0,ndaughter,daughter_list);
			nPi0++;
		}			
		if( tempID[i] == pdg_eta) 	
		{
			// Found an eta!
			ndaughter = 2;
			daughter_list[0] = index1[i];
			daughter_list[1] = index2[i];
			AddParticle(pdg_eta,ndaughter,daughter_list);
			nEta++;
		}
		if( tempID[i] == pdg_etaP) 			
		{
			// Found an eta' !
			ndaughter = 2;
			daughter_list[0] = index1[i];
			daughter_list[1] = index2[i];
			AddParticle(pdg_etaP,ndaughter,daughter_list);
			nEtaP++;
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

	if (nindex > 1) 
	{	
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
		}
		
		// Average some values
		time = time/nindex;
		WC_Vertex_X = WC_Vertex_X/nindex;
		WC_Vertex_Y = WC_Vertex_Y/nindex;
		WC_Vertex_Z = WC_Vertex_Z/nindex;
		
	}
	
	Double_t Px 	= part.Px();
	Double_t Py 	= part.Py();
	Double_t Pz 	= part.Pz();
	Double_t Theta 	= part.Theta() * TMath::RadToDeg();
	Double_t Phi 	= part.Phi()   * TMath::RadToDeg();
	Double_t Mass   = part.M();
	
	SetPDG(nParticles,pdg_code);	
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

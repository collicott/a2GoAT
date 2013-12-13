
#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction() :
							Identified(0),
							nParticles(0),
							PDG(0),
							
							nPi0(0),
							nEta(0),
							nEtaP(0),
							
							Total_NPi0(0),
							Total_NEta(0),
							Total_NEtaP(0)						
{
	Identified 	= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
	PDG 		= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t	GParticleReconstruction::PostInit()
{
	//Setup configs	(read in from file)
	FindChargedParticles = kTRUE;
	ReconstructMesons = kTRUE;
	
	InitTreeParticles();

	m_pi0  = 135.0;
	m_eta  = 545.0;
	m_etaP = 958.0;
	
	pdg_rootino = 0;
	pdg_pi0  = 1;
	pdg_eta  = 2;
	pdg_etaP = 3;	
	pdg_proton = 4;
	pdg_chpi = 5;
	pdg_electron = 6;
	
	width_pi0 	 = 20.0;
	width_eta 	 = 44.0;
	width_etaP 	 = 60.0;

	return kTRUE;
}

void	GParticleReconstruction::Reconstruct()
{
	nParticles = 0;
	
	for (int i = 0; i < GetNParticles(); i++){
		Identified[i] = 0; 
		
	}	
		
	
	if(FindChargedParticles) ChargedReconstruction();
	if(ReconstructMesons)	 MesonReconstruction();

	Total_NPi0 	+= nPi0;
	Total_NEta 	+= nEta;	
	Total_NEtaP += nEtaP;	

	for (int i = 0; i < GetNParticles(); i++) 
	{
		if (Identified[i] == 0) AddParticle(pdg_rootino,i);
	}

}

void	GParticleReconstruction::ChargedReconstruction()
{
	// Check dE and E > 0
	// Check apparatus
	// Call correct cut file
	// Test XY

	nProton	 	= 0;
	nElectron 	= 0;	
	nChPion		= 0;	
	
	for (int i = 0; i < GetNParticles(); i++) 
	{
		if((Get_dE(i) > 0.) && (Get_dE(i) < 100.) && (GetE(i) > 0.) && (GetE(i) < 300.))
		{
			// No test for now, I'm GOD! call it a proton! 
			// Found a proton!
			Int_t index[1]; index[0] = i;
			Int_t nindex = 1;
			AddParticle(pdg_proton,i);  //  <--- Look it's a proton!
			Identified[i] = 1;
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

	nPi0  = 0;	
	nEta  = 0;	
	nEtaP = 0;
	
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

	Double_t Px 	= GetPx(index_list[0]);
	Double_t Py 	= GetPy(index_list[0]);
	Double_t Pz 	= GetPz(index_list[0]);	
	Double_t E 		= GetE(index_list[0]);	
	Double_t time 	= GetTime(index_list[0]);
	
	Double_t dE 	= Get_dE(index_list[0]);
	Double_t WCO_E 	= GetWC0_E(index_list[0]);	
	Double_t WC1_E 	= GetWC1_E(index_list[0]);	
	
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
			Px 		+= GetPx(index_list[i]);
			Py 		+= GetPy(index_list[i]);
			Pz 		+= GetPz(index_list[i]);	
			E  		+= GetE(index_list[i]);	
		
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
	
	SetPDG(nParticles,pdg_code);	
	SetPx(nParticles,Px);
	SetPy(nParticles,Py);
	SetPz(nParticles,Pz);
	SetE(nParticles,E);
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


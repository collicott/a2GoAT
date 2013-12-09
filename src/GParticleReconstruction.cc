
#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction() :
							Identified(0),
							nIdentified(0),
							PDG(0),
							nMeson(0)
{
	Identified 	= new Bool_t[GINPUTTREEMANAGER_MAX_PARTICLE];
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
	
	pdg_pi0  = 1;
	pdg_eta  = 2;
	pdg_etaP = 3;	
	
	width_pi0 	 = 20.0;
	width_eta 	 = 44.0;
	width_etaP 	 = 60.0;

	return kTRUE;
}

void	GParticleReconstruction::Reconstruct()
{
	for (int i = 0; i < GetNParticles(); i++) 
    {
		Identified[i] = kFALSE;
	}
	
	if(FindChargedParticles) ChargedReconstruction();
	if(ReconstructMesons)	 MesonReconstruction();

}

void	GParticleReconstruction::ChargedReconstruction()
{
	
}

void	GParticleReconstruction::MesonReconstruction()
{
	Int_t		index1	  [GetNParticles() * (GetNParticles() -1)];
	Int_t		index2	  [GetNParticles() * (GetNParticles() -1)];	
	Int_t 		tempID    [GetNParticles() * (GetNParticles() -1)];
	Double_t 	diff_meson[GetNParticles() * (GetNParticles() -1)];
	Int_t 		sort_index[GetNParticles() * (GetNParticles() -1)];
	Bool_t 		is_meson  [GetNParticles()];
	Int_t 		index_list[GetNParticles()];
	Int_t 		addparticle_list[GetNParticles()];

	TLorentzVector	initialParticle[GetNParticles()];		
	TLorentzVector	meson[GetNParticles()];		
	TLorentzVector	secondary_meson;

	for (int i = 0; i < GetNParticles(); i++) 
	{
		initialParticle[i] = GetVector(i);
		is_meson[i] = kFALSE;
	}
	  
	// Loop over possible 2-photon combinations (skip i=j, ij = ji)
	Int_t k = 0;
	for (int i = 0; i < GetNParticles(); i++) 
    {
		for (int j = i+1; j < GetNParticles(); j++) 
		{

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
	
	// Form initial meson list
	nMeson = 0;
	for (Int_t i = 0; i < k; i++)
	{
		//particle pair already involved in a meson reconstruction?
		if( is_meson[index1[i]] == kTRUE)  continue;
		if( is_meson[index2[i]] == kTRUE)  continue;		
		
		// New meson identified!
		is_meson[index1[i]] = kTRUE;
		is_meson[index2[i]] = kTRUE;
		
		secondary_meson	+= 	initialParticle[index1[i]] + 
							initialParticle[index2[i]];
		
		index_list[nMeson] = k;
		
		nMeson++;
	}

	// Check for the possibility that mesons come from eta(') decay
	if (nMeson > 1) 
	{		
		Double_t diff_eta  = TMath::Abs( secondary_meson.M() - m_eta )/width_eta;
		Double_t diff_etaP = TMath::Abs( secondary_meson.M() - m_etaP)/width_etaP;

		if ((diff_eta <= 1.0) && (diff_eta < diff_etaP))
		{
			//printf("Super Eta!\n");	
			AddParticle(pdg_eta);
	
		}
		else if ((diff_etaP <= 1.0) && (diff_eta < diff_etaP))
		{
			//printf("Super EtaP!\n");
			AddParticle(pdg_etaP);			
		}
	}	
	

		
}

void	GParticleReconstruction::AddParticle(Int_t pdg_code)
{
	printf("Particle: %d \n",pdg_code);
	
}


void	GParticleReconstruction::Analyse()
{

}

Bool_t	GParticleReconstruction::Write()
{
	return kTRUE;
}

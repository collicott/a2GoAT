
#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction() :
							
							Identified(0),
							nIdentified(0),
							PDG(0)
{
	Identified 	= new Bool_t[GetMaxParticle()];
	PDG 		= new Int_t[GetMaxParticle()];
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t	GParticleReconstruction::PostInit()
{
	//Setup configs	(read in from file)
	FindChargedParticles = kTRUE;
	ReconstructMesons = kTRUE;

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
	printf("%d\n",GetNParticles());	
	
	
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
	PrimaryMesonReconstruction();
	SecondaryMesonReconstruction();
	
}

void	GParticleReconstruction::PrimaryMesonReconstruction()
{
	Int_t		index1[GetNParticles()];
	Int_t		index2[GetNParticles()];
	Int_t	  	tempID[1000];
	Double_t 	diff_meson[1000];
	Int_t 		sort_index[1000];	
	Bool_t		is_meson[1000];
	
	TLorentzVector	initialParticle[GetNParticles()];	
	for (int i = 0; i < GetNParticles(); i++) 
	{
		initialParticle[i] = GetVector(i);
	}
	  
	// Loop over possible 2-photon combinations (skip i=j, ij = ji)
	int k = 0;

	for (int i = 0; i < GetNParticles(); i++) 
    {

		if (Identified[i] ) continue;
		for (int j = i+1; j < GetNParticles(); j++) 
		{
			if(Identified[j]) continue;
			
			TLorentzVector p4 = initialParticle[i] + initialParticle[j];
			
			Double_t diff_pi0  = TMath::Abs( p4.M() - m_pi0 )/width_pi0;
			Double_t diff_eta  = TMath::Abs( p4.M() - m_eta )/width_eta;
			Double_t diff_etaP = TMath::Abs( p4.M() - m_etaP)/width_etaP;
			
			printf("%f\n",diff_pi0);
			
			if (diff_pi0 <= 1.0) 
			{
				diff_meson[k]= diff_pi0; 
				tempID[k] = pdg_pi0;
				k++;
			}
			if (diff_eta <= 1.0) 
			{
				diff_meson[k]= diff_eta; 
				tempID[k] = pdg_eta;
				k++;
			}
			if (diff_etaP <= 1.0) 
			{
				diff_meson[k]= diff_etaP; 
				tempID[k] = pdg_etaP;
				k++;
			}			
		}
	}
  
	TMath::Sort(k, diff_meson, sort_index, kFALSE);

	
}

void	GParticleReconstruction::SecondaryMesonReconstruction()
{
	
	
}

void	GParticleReconstruction::Analyse()
{

}

Bool_t	GParticleReconstruction::Write()
{
	return kTRUE;
}

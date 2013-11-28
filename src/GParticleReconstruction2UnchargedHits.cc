
#include "GParticleReconstruction2UnchargedHits.h"


GParticleReconstruction2UnchargedHits::GParticleReconstruction2UnchargedHits(): invMass2g(0),
																				invMassSq2g(0),
																				histInvMass2g(0),
																				histInvMassSq2g(0),
																				histInvMassPi02g(0),
																				histInvMassPi0Sq2g(0),
																				histInvMassEta2g(0),
																				histInvMassEtaSq2g(0),
																				histInvMassEtap2g(0),
																				histInvMassEtapSq2g(0)
{
	massPi0				= 135;
	reciprocalWidthPi0	= 1.0/20.0;
	massEta				= 545;
	reciprocalWidthEta	= 1.0/44.0;
	massEtap			= 958;
	reciprocalWidthEtap	= 1.0/60.0;
	
}

GParticleReconstruction2UnchargedHits::~GParticleReconstruction2UnchargedHits()
{
	if(histInvMass2g)		delete histInvMass2g;
	if(histInvMassSq2g)		delete histInvMassSq2g;
	if(histInvMassPi02g)	delete histInvMassPi02g;
	if(histInvMassPi0Sq2g)	delete histInvMassPi0Sq2g;
	if(histInvMassEta2g)	delete histInvMassEta2g;
	if(histInvMassEtaSq2g)	delete histInvMassEtaSq2g;
	if(histInvMassEtap2g)	delete histInvMassEtap2g;
	if(histInvMassEtapSq2g)	delete histInvMassEtapSq2g;
}
	
Bool_t	GParticleReconstruction2UnchargedHits::InitHistograms()
{
	if(!histInvMass2g)
	{
		histInvMass2g	= new TH1D("InvMasss2g", "Invariant Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY);
		if(!histInvMass2g)	return kFALSE;
	}
	if(!histInvMassSq2g)
	{
		histInvMassSq2g	= new TH1D("histInvMassSq2g", "Squared Invariant Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY * GPR_MAX_MAMI_ENERGY);
		if(!histInvMassSq2g)	return kFALSE;
	}
	if(!histInvMassPi02g)
	{
		histInvMassPi02g	= new TH1D("histInvMassPi02g", "Invariant Pi0 Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY);
		if(!histInvMassPi02g)	return kFALSE;
	}
	if(!histInvMassPi0Sq2g)
	{
		histInvMassPi0Sq2g	= new TH1D("histInvMassPi0Sq2g", "Squared Invariant Pi0 Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY * GPR_MAX_MAMI_ENERGY);
		if(!histInvMassPi0Sq2g)	return kFALSE;
	}
	if(!histInvMassEta2g)
	{
		histInvMassEta2g	= new TH1D("histInvMassEta2g", "Invariant Eta Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY);
		if(!histInvMassEta2g)	return kFALSE;
	}
	if(!histInvMassEtaSq2g)
	{
		histInvMassEtaSq2g	= new TH1D("histInvMassEtaSq2g", "Squared Invariant Eta Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY * GPR_MAX_MAMI_ENERGY);
		if(!histInvMassEtaSq2g)	return kFALSE;
	}
	if(!histInvMassEtap2g)
	{
		histInvMassEtap2g	= new TH1D("histInvMassEtap2g", "Invariant Etap Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY);
		if(!histInvMassEtap2g)	return kFALSE;
	}
	if(!histInvMassEtapSq2g)
	{
		histInvMassEtapSq2g	= new TH1D("histInvMassEtapSq2g", "Squared Invariant Etap Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY * GPR_MAX_MAMI_ENERGY);
		if(!histInvMassEtapSq2g)	return kFALSE;
	}
	
	return kTRUE;
}

void	GParticleReconstruction2UnchargedHits::ClearHistograms()
{
	histInvMass2g->Reset();
	histInvMassSq2g->Reset();
	histInvMassPi02g->Reset();
	histInvMassPi0Sq2g->Reset();
	histInvMassEta2g->Reset();
	histInvMassEtaSq2g->Reset();
	histInvMassEtap2g->Reset();
	histInvMassEtapSq2g->Reset();
}


Bool_t	GParticleReconstruction2UnchargedHits::Write()
{
	GTreeManager::Write();
	
	histInvMass2g->Write();
	histInvMassSq2g->Write();
	histInvMassPi02g->Write();
	histInvMassPi0Sq2g->Write();
	histInvMassEta2g->Write();
	histInvMassEtaSq2g->Write();
	histInvMassEtap2g->Write();
	histInvMassEtapSq2g->Write();
}

void	GParticleReconstruction2UnchargedHits::Reconstruct2UnchargedHits()
{
	TLorentzVector	initialParticle[2];
	
	initialParticle[0]	= GetVector(0);
	initialParticle[1]	= GetVector(1);
	
	TLorentzVector	reconstructedParticle	= initialParticle[0] + initialParticle[1];
	invMassSq2g	= reconstructedParticle.M2();
	invMass2g	= invMassSq2g < 0.0 ? -TMath::Sqrt(-invMassSq2g) : TMath::Sqrt(invMassSq2g);
	histInvMassSq2g->Fill(invMassSq2g);
	histInvMass2g->Fill(invMass2g);
	
	Double_t	ChiSq[3];
	ChiSq[0]	 = (invMass2g - massPi0) * reciprocalWidthPi0;
	ChiSq[0]	*= ChiSq[0];
	ChiSq[1]	 = (invMass2g - massEta) * reciprocalWidthEta;
	ChiSq[1]	*= ChiSq[1];
	ChiSq[2]	 = (invMass2g - massEtap) * reciprocalWidthEtap;
	ChiSq[2]	*= ChiSq[2];
	
	Clear();
	
	if(ChiSq[0] < ChiSq[1])
	{
		if(ChiSq[0] < ChiSq[2])
		{
			histInvMassPi0Sq2g->Fill(invMassSq2g);
			histInvMassPi02g->Fill(invMass2g);
			FillPi0((UChar_t)0, (UChar_t)1);
			FillPi0();
		}
		else
		{
			histInvMassEtapSq2g->Fill(invMassSq2g);
			histInvMassEtap2g->Fill(invMass2g);
			FillEtap((UChar_t)0, (UChar_t)1);
			FillEtap();
		}
	}
	else
	{
		if(ChiSq[1] < ChiSq[2])
		{
			histInvMassEtaSq2g->Fill(invMassSq2g);
			histInvMassEta2g->Fill(invMass2g);
			FillEta((UChar_t)0, (UChar_t)1);
			FillEta();
		}
		else
		{
			histInvMassEtapSq2g->Fill(invMassSq2g);
			histInvMassEtap2g->Fill(invMass2g);
			FillEtap((UChar_t)0, (UChar_t)1);
			FillEtap();
		}
	}
	//Print();
}


#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction(): invMass2g(0),
													invMass2gSq(0),
													histInvMass2g(0),
													histInvMass2gSq(0)
{
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t	GParticleReconstruction::InitHistograms()
{
	if(!histInvMass2g)
	{
		histInvMass2g	= new TH1D("InvMasss2g", "Invariant Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY);
		if(!histInvMass2g)	return kFALSE;
	}
	if(!histInvMass2gSq)
	{
		histInvMass2gSq	= new TH1D("histInvMass2gSq", "Squared Invariant Mass of 2 Gamma", GPR_MAX_MAMI_ENERGY, 0, GPR_MAX_MAMI_ENERGY * GPR_MAX_MAMI_ENERGY);
		if(!histInvMass2gSq)	return kFALSE;
	}
	
	return kTRUE;
}

void	GParticleReconstruction::Reconstruct2Hits()
{
	initialParticle[0]	= GetVector(0);
	initialParticle[1]	= GetVector(1);
	
	reconstructedParticle[0]	= initialParticle[0] + initialParticle[1];
	invMass2gSq	= reconstructedParticle[0].M2();
	invMass2g	= invMass2gSq < 0.0 ? -TMath::Sqrt(-invMass2gSq) : TMath::Sqrt(invMass2gSq);
	histInvMass2gSq->Fill(invMass2gSq);
	histInvMass2g->Fill(invMass2g);
}

void	GParticleReconstruction::ClearHistograms()
{
	histInvMass2g->Reset();
	histInvMass2gSq->Reset();
}

void    GParticleReconstruction::Analysis(const char* inputtreefile, const char* outputfilename)
{
    if(InitHistograms())
    {
		ClearHistograms();
        GTreeManager::Analysis(inputtreefile, outputfilename);
	}
}

void	GParticleReconstruction::Reconstruct()
{
	switch(GetNParticles())
	{
	case 2:
		Reconstruct2Hits();
		return;
	default:
		printf("No Reconstruction methode for %d Hits found in GParticleReconstruction\n", GetNParticles());
	}
}

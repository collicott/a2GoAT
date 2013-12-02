
#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction()
{
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t	GParticleReconstruction::Init(const char* intreefile, const char* outtreefile, const Int_t Min, const Int_t Max)
{
	if(!OpenInputFile(intreefile))		return kFALSE;
	if(!OpenOutputFile(outtreefile))	return kFALSE;
	if(!FindValidEvents())				return kFALSE;
	
	Int_t	checkedMin	= Min;
	Int_t	checkedMax	= Max;
	CheckRange(checkedMin, checkedMax);
	
	if(!OpenTreeRawEvent())	return kFALSE;
	if(!InitTreePi0())		return kFALSE;
	if(!InitTreeEta())		return kFALSE;
	if(!InitTreeEtap())		return kFALSE;
	if(!InitHistograms())	return kFALSE;
	ClearHistograms();
	
	TraverseInputEntries(checkedMin, checkedMax);
	
	if(!Write())	return kFALSE;
	
	return kTRUE;
}

void    GParticleReconstruction::Analyse()
{
		Bool_t FindChargedParticles;
		if(FindChargedParticles) ChargedReconstruction();
		Reconstruct();
	
}

void	GParticleReconstruction::Reconstruct()
{
	// Do particle pairs
}

void	GParticleReconstruction::ChargedReconstruction()
{
	
}

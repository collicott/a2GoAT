
#include "GParticleReconstruction.h"


GParticleReconstruction::GParticleReconstruction()
{
}

GParticleReconstruction::~GParticleReconstruction()
{
}

Bool_t	GParticleReconstruction::Analyse(const char* intreefile, const char* outtreefile, const Int_t Min, const Int_t Max)
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

void	GParticleReconstruction::Reconstruct()
{
	switch(GetNParticles())
	{
	case 0:
		return;
	case 1:
		return;
	case 2:
		Reconstruct2UnchargedHits();
		return;
	case 3:
		return;
	case 4:
		return;
	case 5:
		return;
	case 6:
		return;
	case 7:
		return;
	case 8:
		return;
	case 9:
		return;
	case 10:
		return;
	case 11:
		return;
	case 12:
		return;
	case 13:
		return;
	case 14:
		return;
	case 15:
		return;
	case 16:
		return;
	default:
		printf("No Reconstruction methode for %d Hits found in GParticleReconstruction\n", GetNParticles());
	}
}

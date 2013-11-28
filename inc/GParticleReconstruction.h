//*************************************************************************
//* Author: Patrik Ott
//*************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TA2RootTree                                                          //
//                                                                      //
// This class is organising the output to ROOT files                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__


#include "GParticleReconstruction2UnchargedHits.h"


#define	GPR_MAX_MAMI_ENERGY	1600

class	GParticleReconstruction : public GParticleReconstruction2UnchargedHits
{
private:
	virtual Bool_t	InitHistograms()		{GParticleReconstruction2UnchargedHits::InitHistograms();}
    
public:
	GParticleReconstruction();
	~GParticleReconstruction();
	
	virtual void	ClearHistograms()		{GParticleReconstruction2UnchargedHits::ClearHistograms();}
	virtual Bool_t	Analyse(const char* intreefile, const char* outtreefile, const Int_t Min = -1, const Int_t Max = -1);
	virtual void	Reconstruct();
    virtual Bool_t	Write()					{GParticleReconstruction2UnchargedHits::Write();}
};


#endif


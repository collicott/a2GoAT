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


#include "GTreeManager.h"

#include "TH1D.h"


#define	GPR_MAX_MAMI_ENERGY	1600

class	GParticleReconstruction : public GTreeManager
{
private:
	TLorentzVector	initialParticle[6];
	TLorentzVector	reconstructedParticle[3];
	
	// 2 Gamma
	Double_t	invMass2g;
	Double_t	invMass2gSq;
	TH1D*		histInvMass2g;
	TH1D*		histInvMass2gSq;
	
	Bool_t	InitHistograms();
    void	Reconstruct2Hits();
    
public:
	GParticleReconstruction();
	~GParticleReconstruction();
	
	void	ClearHistograms();
	
	virtual void	Analysis(const char* inputtreefile, const char* outputfilename = 0);
	virtual void	Reconstruct();
};


#endif


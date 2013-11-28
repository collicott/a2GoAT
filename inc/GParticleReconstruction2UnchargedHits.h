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


#ifndef __GParticleReconstruction2UnchargedHits_h__
#define __GParticleReconstruction2UnchargedHits_h__


#include "GTreeManager.h"

#include "TH1D.h"


#define	GPR_MAX_MAMI_ENERGY	1600

class	GParticleReconstruction2UnchargedHits : public GTreeManager
{
private:	
	// 2 Gamma
	Double_t	invMass2g;
	Double_t	invMassSq2g;
	TH1D*		histInvMass2g;
	TH1D*		histInvMassSq2g;
	TH1D*		histInvMassPi02g;
	TH1D*		histInvMassPi0Sq2g;
	TH1D*		histInvMassEta2g;
	TH1D*		histInvMassEtaSq2g;
	TH1D*		histInvMassEtap2g;
	TH1D*		histInvMassEtapSq2g;
	
	// Cuts
	Double_t	massPi0;
	Double_t	reciprocalWidthPi0;
	Double_t	massEta;
	Double_t	reciprocalWidthEta;
	Double_t	massEtap;
	Double_t	reciprocalWidthEtap;

protected:
	virtual	Bool_t	InitHistograms();
    void	Reconstruct2UnchargedHits();
    
public:
	GParticleReconstruction2UnchargedHits();
	virtual	~GParticleReconstruction2UnchargedHits();
	
	virtual	void	ClearHistograms();
	virtual void	Reconstruct() = 0;
    virtual Bool_t	Write();
	
	Double_t	GetMassPi0()			const	{return massPi0;}
	Double_t	GetWidthPi0()			const	{return 1/reciprocalWidthPi0;}
	Double_t	GetMassEta()			const	{return massEta;}
	Double_t	GetWidthEta()			const	{return 1/reciprocalWidthEta;}
	Double_t	GetMassEtap()			const	{return massEtap;}
	Double_t	GetWidthEtap()			const	{return 1/reciprocalWidthEtap;}
	
	void	SetMassPi0(const Double_t Mass)		{massPi0 = Mass;}
	void	SetWidthPi0(const Double_t Width)	{reciprocalWidthPi0 = 1/Width;}
	void	SetMassEta(const Double_t Mass)		{massEta = Mass;}
	void	SetWidthEta(const Double_t Width)	{reciprocalWidthEta = 1/Width;}
	void	SetMassEtap(const Double_t Mass)	{massEtap = Mass;}
	void	SetWidthEtap(const Double_t Width)	{reciprocalWidthEtap = 1/Width;}
};


#endif


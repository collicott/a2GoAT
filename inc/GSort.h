
#ifndef __GSort_h__
#define __GSort_h__

#include "GParticleReconstruction.h"
#include "GTreeManager.h"

#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0

class	GSort : public GParticleReconstruction
{
private:

	Int_t 	SortRawNumberParticles;	 			// Sort on-off
	Int_t  	Sort_raw_nParticles_total;
	Int_t  	Sort_raw_nParticles_total_condition;
    Int_t   Sort_raw_nParticles_CB;
    Int_t   Sort_raw_nParticles_CB_condition;        
    Int_t   Sort_raw_nParticles_TAPS;
    Int_t   Sort_raw_nParticles_TAPS_condition;       	
    
    
    Int_t 		SortProton;						// Sort on-off
    Int_t 		Sort_nProton;
    Double_t 	Sort_Proton_theta_min;
    Double_t	Sort_Proton_theta_max;

protected:
	    
public:

	GSort();
	~GSort();

	virtual Bool_t	Init(const char* intreefile, const char* outtreefile) {return kTRUE;}
	virtual void	Analyse() {;}
	virtual void	Reconstruct();
	Bool_t	PostInit();

    Bool_t	SortAnalyseEvent();
    Bool_t	SortFillEvent();
//    Bool_t 	SortOnParticle(Int_t PDG, Int_t Num, Double_t ThetaMin, Double_t ThetaMax);
};


#endif


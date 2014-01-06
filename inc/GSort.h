
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

	Int_t 		SortRawNParticles;	 			// Sort on-off
	Int_t  		SR_nPart_total;
	Int_t  		SR_nPart_total_condition;
    Int_t   	SR_nPart_CB;
    Int_t   	SR_nPart_CB_condition;        
    Int_t   	SR_nPart_TAPS;
    Int_t   	SR_nPart_TAPS_condition;       	
 
 	Int_t 		SortRawCBESum;	 				// Sort on-off
	Double_t  	SR_CBESum;
	Int_t  		SR_CBESum_condition;
    
    Int_t 		SortNParticles;					// Sort on-off
    Int_t 		S_nParticles;
    Int_t		S_nParticles_condition;
    
    Int_t 		SortProton;						// Sort on-off
    Int_t 		S_nProton;
    Int_t 		S_nProton_condition;
    Double_t 	S_Proton_theta_min;
    Double_t	S_Proton_theta_max;

    Int_t 		SortChPion;						// Sort on-off
    Int_t 		S_nChPion;
    Int_t 		S_nChPion_condition;
    Double_t 	S_ChPion_theta_min;
    Double_t	S_ChPion_theta_max;

    Int_t 		SortPi0;						// Sort on-off
    Int_t 		S_nPi0;
    Int_t 		S_nPi0_condition;
    Double_t 	S_Pi0_theta_min;
    Double_t	S_Pi0_theta_max;

    Int_t 		SortEta;						// Sort on-off
    Int_t 		S_nEta;
    Int_t 		S_nEta_condition;
    Double_t 	S_Eta_theta_min;
    Double_t	S_Eta_theta_max;

    Int_t 		SortEtaP;						// Sort on-off
    Int_t 		S_nEtaP;
    Int_t 		S_nEtaP_condition;
    Double_t 	S_EtaP_theta_min;
    Double_t	S_EtaP_theta_max;
    
	char string_in1[256], string_in2[256], string_in3[256];
	std::string string_out1, string_out2, string_out3;
			    
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
    Bool_t 	SortOnParticle(Int_t PDG, Int_t Num, Int_t cond, Double_t ThetaMin, Double_t ThetaMax);
    void	CheckConfigCondition(char string[], int *condition, std::string& string_out);
};


#endif


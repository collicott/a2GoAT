
#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__

#include "GDataChecks.h"

#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0

#define	pdg_rootino 0

class	GParticleReconstruction : public GDataChecks
{
private:

	char 		cutfilename[256];
	char 		cutname[256];	
	
	TFile* 		CutFile;
	TCutG* 		Cut;
   	TCutG* 		Cut_CB_proton; 
   	TCutG* 		Cut_CB_pion; 
   	TCutG*		Cut_CB_electron;
   	TCutG* 		Cut_TAPS_proton; 
   	TCutG* 		Cut_TAPS_pion; 
   	TCutG*		Cut_TAPS_electron;
	
	Int_t 		ReconstructChargedParticles;
	Double_t	charged_theta_min;
	Double_t	charged_theta_max;
	
   	Int_t		Cut_CB_proton_active;   	
   	Int_t		Cut_TAPS_proton_active;  
   	Int_t 		Cut_proton_active;
   	
   	Int_t		Cut_CB_pion_active;
   	Int_t		Cut_TAPS_pion_active;
   	Int_t 		Cut_pion_active;
   	
   	Int_t		Cut_CB_electron_active; 
   	Int_t		Cut_TAPS_electron_active; 
   	Int_t 		Cut_electron_active;
   	   	   	
   	TCutG* 		Cut_proton;
   	TCutG*		Cut_pion;
   	TCutG*		Cut_electron;
   	
	Int_t		ReconstructMesons;
	Double_t	meson_theta_min;
	Double_t	meson_theta_max;
		
	Double_t	width_pi0;
	Double_t	width_eta;
	Double_t	width_etaP;

	Int_t* 		Identified;
    Int_t* 		Charge;
	
	Int_t 		nParticles;
	Int_t 		nDaughterList;
   	Int_t 		i;
   	
protected:
	    
public:

	GParticleReconstruction();
	~GParticleReconstruction();

	virtual void	Analyse() {;}
	virtual void	Reconstruct();

    
	Bool_t	PostInit();
	void	InitEvent();
	void	CheckNeutrality();
	void 	PhotonReconstruction();	
	void 	ChargedReconstruction();
	void 	MesonReconstruction();	
	void	AddParticle(Int_t pdg_code, Int_t nindex, Int_t index_list[]);
	void	AddParticle(Int_t pdg_code, Int_t i) 
			{Int_t index_list[1]; index_list[0] = i; AddParticle(pdg_code, 1, index_list);}

	TCutG*	OpenCutFile(Char_t* filename, Char_t* cutname);

	// Make some variables available for sorting/printing
};


#endif


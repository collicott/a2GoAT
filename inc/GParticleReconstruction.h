
#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__

#include "GTreeManager.h"
#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0

class	GParticleReconstruction : public GTreeManager
{
private:

	Bool_t 		ReconstructChargedParticles;
	Bool_t		ReconstructMesons;

	char 		cutfilename[256];
	char 		cutname[256];	
	
	TFile* 		CutFile;
	TCutG* 		Cut;
   	TCutG* 		Cut_CB_proton; 
   	TCutG* 		Cut_CB_pion; 
   	TCutG* 		Cut_TAPS_proton; 
   	TCutG* 		Cut_TAPS_pion; 
   	
   	TCutG* 		Cut_proton;
   	TCutG*		Cut_pion;
	
	Int_t* 		PDG;
	Int_t* 		Identified;
	
	Int_t 		nParticles;

	Double_t	m_pi0;
	Double_t	m_eta;
	Double_t	m_etaP;
	Double_t	m_proton;
	Double_t 	m_chpi;
	Double_t	m_electron;
	
	Int_t 		pdg_rootino;
	Int_t 		pdg_pi0;
	Int_t 		pdg_eta;
	Int_t 		pdg_etaP;
	Int_t		pdg_proton;
	Int_t 		pdg_chpi;
	Int_t		pdg_electron;
	
	Double_t	width_pi0;
	Double_t	width_eta;
	Double_t	width_etaP;

   	Int_t 		nPi0;
   	Int_t 		nEta;
   	Int_t 		nEtaP;
 	Int_t 		nProton;
	Int_t		nChPion;
	Int_t 		nElectron;		

   	Int_t 		i;
protected:
	    
public:

	GParticleReconstruction();
	~GParticleReconstruction();

	virtual Bool_t	Init(const char* intreefile, const char* outtreefile) {return kTRUE;}
	virtual void	Analyse() {;}
	virtual void	Reconstruct();

    
	Bool_t	PostInit();
	void 	ChargedReconstruction();
	void 	MesonReconstruction();	
	void	AddParticle(Int_t pdg_code, Int_t nindex, Int_t index_list[]);
	void	AddParticle(Int_t pdg_code, Int_t i) 
			{Int_t index_list[1]; index_list[0] = i; AddParticle(pdg_code, 1, index_list);}

	TCutG*	OpenCutFile(Char_t* filename, Char_t* cutname);

	// Make some variables available for sorting/printing
	Int_t 	GP_GetNParticles()	const 	{return nParticles;}
    Int_t	GetNPi0() 			const	{return nPi0;}
    Int_t	GetNEta() 			const	{return nEta;}	
    Int_t	GetNEtaP() 			const	{return nEtaP;}
    Int_t	GetNProton() 		const	{return nProton;}
    Int_t	GetNChPion() 		const	{return nChPion;}
   

};


#endif


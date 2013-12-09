
#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__

#include "GTreeManager.h"

class	GParticleReconstruction : public GTreeManager
{
private:

	Bool_t 		FindChargedParticles;
	Bool_t 		ReconstructMesons;	
	
	Int_t* 		PDG;
	Bool_t* 	Identified;
	Int_t		nIdentified;

	Double_t	m_pi0;
	Double_t	m_eta;
	Double_t	m_etaP;

	Int_t 		pdg_pi0;
	Int_t 		pdg_eta;
	Int_t 		pdg_etaP;
	
	Double_t	width_pi0;
	Double_t	width_eta;
	Double_t	width_etaP;
	
	Int_t 		nMeson;
	Int_t		nPi0;
	Int_t		nEta;
	
	

protected:
	    
public:
	GParticleReconstruction();
	~GParticleReconstruction();

	virtual Bool_t	Init(const char* intreefile, const char* outtreefile) {return kTRUE;}
	virtual void	Analyse();
	virtual void	Reconstruct();
    virtual Bool_t	Write();
    
	Bool_t	PostInit();
	void 	ChargedReconstruction();
	void 	MesonReconstruction();	
	void	AddParticle(Int_t pdg_code);
	

};


#endif


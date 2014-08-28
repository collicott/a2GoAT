#ifndef __PPhysics_h__
#define __PPhysics_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string> 

#include <TH3.h>

#include "GTreeManager.h"
#include "GH1.h"
#include "GConfigFile.h"


class	PPhysics : virtual public GTreeManager
{
private:

	Double_t targetmass;
	Double_t Prompt_low;
	Double_t Prompt_high;
	Double_t Random_low1;
	Double_t Random_high1;
	Double_t Random_low2;
	Double_t Random_high2;
	
	Double_t PvR_ratio;
		
	TLorentzVector beam;
	TLorentzVector target;
	TLorentzVector particle;
	TLorentzVector missingp4;
	
	Double_t time;
	Bool_t 	Prompt;
	Bool_t 	Random;
	
protected:


public:
    PPhysics();
    virtual ~PPhysics();

    virtual Bool_t	Init(const Char_t* file_config);
	virtual void	Analyse() {;}
	virtual void	Reconstruct();
    virtual Bool_t	Write();

	void	FillMissingMass(const GTreeParticle& tree, GH1* gHist);
	void	FillMissingMass(const GTreeParticle& tree, Int_t particle_index, GH1* gHist);
	void 	FillMissingMass(const GTreeParticle& tree, Int_t particle_index, Int_t tagger_index, GH1* gHist);

    Double_t CalcMissingMass(const GTreeParticle &tree, Int_t particle_index, Int_t tagger_index);
    Double_t CalcMissingEnergy(const GTreeParticle &tree, Int_t particle_index, Int_t tagger_index);
    TLorentzVector CalcMissingP4(const GTreeParticle &tree, Int_t particle_index, Int_t tagger_index);

	void 	FillTime(const GTreeParticle& tree, GH1* gHist);
	void 	FillTime(const GTreeParticle& tree, Int_t particle_index, GH1* gHist);
	void 	FillTimeCut(const GTreeParticle& tree, GH1* gHist);
	void 	FillTimeCut(const GTreeParticle& tree, Int_t particle_index, GH1* gHist);

	void 	FillMass(const GTreeParticle& tree, GH1* gHist);
	void 	FillMass(const GTreeParticle& tree, Int_t particle_index, GH1* gHist);
				
	void	SetTarget(Double_t mass) {target = TLorentzVector(0.,0.,0.,mass);}
	TLorentzVector GetTarget() {return target;}
	
};
#endif

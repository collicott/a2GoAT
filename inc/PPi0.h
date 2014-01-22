#ifndef __PPi0_h__
#define __PPi0_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "PPhysics.h"

class	PPi0 : public PPhysics
{
private:

	TH1* 	time_pi0;
	TH1* 	time_pi0_cuts;	

	TH1* 	MM_prompt_pi0;
	TH1* 	MM_random_pi0;
	TH1* 	MM_pi0;
	
	Int_t 	nentries;
	Int_t	TC;
	Double_t E;
	Double_t time;
	Double_t theta;
	Double_t thetaCM;
	Double_t phi;
	Double_t phiCM;
	Double_t MissMass;
	Double_t MissE;	
	
	
protected:


public:
    PPi0();
    virtual ~PPi0();

    virtual Bool_t	Init(Char_t* file_config);	
    virtual void 	Analyse();
	virtual void	Reconstruct();
	void	PostReconstruction();

	Bool_t 	InitPhysicsTree(TFile* F);
	void	DefineHistograms();
	Bool_t	WriteHistograms(TFile* pfile);
	Bool_t	WriteHistograms() {return WriteHistograms(PhysFile);}
};
#endif

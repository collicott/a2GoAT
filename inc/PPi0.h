#ifndef __PPi0_h__
#define __PPi0_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "GoATTreeManager.h"

class	PPi0 : public GoATTreeManager
{
private:
    char 	file_in[256];
	char 	file_out[256];

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
	
	TH1* MM_prompt;
	TH1* MM_random;
	TH1* MM;
	
	TCanvas* canvas;

protected:


public:
    PPi0();
    virtual ~PPi0();

    virtual Bool_t	Init(Char_t* file_config);	
    virtual void 	Analyse();
	virtual void	Reconstruct();
    virtual Bool_t	Write();

	void 	MissingMass(Int_t pdg);
	virtual Bool_t 	IsPrompt(Double_t time);
	virtual Bool_t 	IsRandom(Double_t time);
    
};
#endif

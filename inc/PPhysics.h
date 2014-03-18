#ifndef __PPhysics_h__
#define __PPhysics_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "GoATTreeManager.h"

class	PPhysics : public GoATTreeManager
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

    virtual Bool_t	Init(Char_t* file_config);	
	virtual void	Analyse() {;}
	virtual void	Reconstruct();
    virtual Bool_t	Write();

	void 	MissingMassPDG(Int_t pdg, TH1* Hprompt, TH1* Hrandom);
	Bool_t	FillMissingMass(Int_t particle_index, TH1* Hprompt, TH1* Hrandom);
	Bool_t 	FillMissingMassPair(Int_t particle_index, Int_t tagger_index, TH1* Hprompt, TH1* Hrandom);
	Double_t CalcMissingMass(Int_t particle_index, Int_t tagger_index);
	Double_t CalcMissingEnergy(Int_t particle_index, Int_t tagger_index);
    TLorentzVector CalcMissingP4(Int_t particle_index, Int_t tagger_index);
			
	void 	FillTimePDG(Int_t pdg, TH1* Htime);	
	void	ShowTimeCuts(TH1* timeH, TH1* cutsH, Double_t t1, Double_t t2, Double_t t3, Double_t t4, Double_t t5, Double_t t6);
	void	ShowTimeCuts(TH1* timeH, TH1* cutsH) {ShowTimeCuts(timeH, cutsH, Random_low1, Random_high1, Prompt_low, Prompt_high, Random_low2, Random_high2);}
	
	Bool_t 	IsPrompt(Double_t time, Double_t t_low, Double_t t_high);
	Bool_t 	IsPrompt(Double_t time) {return IsPrompt(time, Prompt_low, Prompt_high);}
	Bool_t 	IsRandom(Double_t time, Double_t t_low1, Double_t t_high1, Double_t t_low2, Double_t t_high2 );
	Bool_t 	IsRandom(Double_t time) {return IsRandom(time, Random_low1, Random_high1, Random_low2, Random_high2);}
	
	void	SetTarget(Double_t mass) {target = TLorentzVector(0.,0.,0.,mass);}
	TLorentzVector GetTarget() {return target;}
	
	void	SetPromptWindow( Double_t t1, Double_t t2) {Prompt_low  = t1; Prompt_high  = t2;}
	void	SetRandomWindow1(Double_t t1, Double_t t2) {Random_low1 = t1; Random_high1 = t2;}
	void	SetRandomWindow2(Double_t t1, Double_t t2) {Random_low2 = t1; Random_high2 = t2;}
	void 	SetPvRratio(Double_t value) {PvR_ratio = value;}
	void 	SetPvRratio() {PvR_ratio = (Prompt_high - Prompt_low)/((Random_high1 - Random_low1) + (Random_high2 - Random_low2));}
	
	void	RandomSubtraction(TH1* prompt, TH1* random, TH1* sub, Double_t ratio);
	void	RandomSubtraction(TH1* prompt, TH1* random, TH1* sub) {RandomSubtraction(prompt,random,sub,PvR_ratio);}
	
	void	RandomSubtraction(TH3* prompt, TH3* random, TH3* sub, Double_t ratio);
	void	RandomSubtraction(TH3* prompt, TH3* random, TH3* sub) {RandomSubtraction(prompt,random,sub,PvR_ratio);}

	TFile* 	HistFile;
	Bool_t 	OpenHistFile(const char* pfile, Option_t* option);
	Bool_t 	OpenHistFile(const char* pfile) { return OpenHistFile(pfile,"RECREATE");}
	Bool_t	CloseHistFile();	

		
};
#endif

#ifndef __PPi0_h__
#define __PPi0_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "PPhysics.h"

#define maxentries	1024

class	PPi0 : public PPhysics
{
private:

	Char_t* gfile;
	Char_t* tfile;
	Char_t* hfile;

	TFile* 	PhysTreeFile;
	TTree*	treePhysics;
	
	Bool_t	ReconstructPhysicsTree;
	Bool_t	FillHistograms;
	
	Double_t MMCut_low;
	Double_t MMCut_high;
	
	Double_t theta_bin_size;
	Double_t phi_bin_size;
	
	TH1* 	time_pi0;
	TH1* 	time_pi0_cuts;	

	TH1* 	TC_prompt;
	TH1* 	TC_random;
	TH1* 	TC_sub;

	TH1* 	E_prompt;
	TH1* 	E_random;
	TH1* 	E_sub;

	TH1* 	theta_prompt;
	TH1* 	theta_random;
	TH1* 	theta_sub;

	TH1* 	phi_prompt;
	TH1* 	phi_random;
	TH1* 	phi_sub;

	TH1* 	phi_prompt_0_10;
	TH1* 	phi_random_0_10;
	TH1* 	phi_sub_0_10;

	TH1* 	phi_prompt_10_20;
	TH1* 	phi_random_10_20;
	TH1* 	phi_sub_10_20;

	TH1* 	phi_prompt_20_30;
	TH1* 	phi_random_20_30;
	TH1* 	phi_sub_20_30;

	TH1* 	phi_prompt_30_40;
	TH1* 	phi_random_30_40;
	TH1* 	phi_sub_30_40;

	TH1* 	phi_prompt_40_50;
	TH1* 	phi_random_40_50;
	TH1* 	phi_sub_40_50;

	TH1* 	phi_prompt_50_60;
	TH1* 	phi_random_50_60;
	TH1* 	phi_sub_50_60;

	TH1* 	phi_prompt_60_70;
	TH1* 	phi_random_60_70;
	TH1* 	phi_sub_60_70;

	TH1* 	phi_prompt_70_80;
	TH1* 	phi_random_70_80;
	TH1* 	phi_sub_70_80;

	TH1* 	phi_prompt_80_90;
	TH1* 	phi_random_80_90;
	TH1* 	phi_sub_80_90;

	TH1* 	phi_prompt_90_100;
	TH1* 	phi_random_90_100;
	TH1* 	phi_sub_90_100;

	TH1* 	phi_prompt_100_110;
	TH1* 	phi_random_100_110;
	TH1* 	phi_sub_100_110;

	TH1* 	phi_prompt_110_120;
	TH1* 	phi_random_110_120;
	TH1* 	phi_sub_110_120;

	TH1* 	phi_prompt_120_130;
	TH1* 	phi_random_120_130;
	TH1* 	phi_sub_120_130;

	TH1* 	phi_prompt_130_140;
	TH1* 	phi_random_130_140;
	TH1* 	phi_sub_130_140;

	TH1* 	phi_prompt_140_150;
	TH1* 	phi_random_140_150;
	TH1* 	phi_sub_140_150;

	TH1* 	phi_prompt_150_160;
	TH1* 	phi_random_150_160;
	TH1* 	phi_sub_150_160;

	TH1* 	phi_prompt_160_170;
	TH1* 	phi_random_160_170;
	TH1* 	phi_sub_160_170;

	TH1* 	phi_prompt_170_180;
	TH1* 	phi_random_170_180;
	TH1* 	phi_sub_170_180;

	TH1* 	MM_prompt_pi0;
	TH1* 	MM_random_pi0;
	TH1* 	MM_sub_pi0;
	
	TH1* 	ME_prompt_pi0;
	TH1* 	ME_random_pi0;
	TH1* 	ME_sub_pi0;
	
	TH3*	TC_theta_phi_prompt;
	TH3*	TC_theta_phi_random;
	
	Int_t 	nentries;
	Int_t*	TC;
	Double_t* E;
	Double_t* time;
	Double_t* theta;
	Double_t* thetaCM;
	Double_t* phi;
	Double_t* MissMass;
	Double_t* MissE;	
	
	Bool_t 	Prompt;
	Bool_t 	Random;
	
protected:


public:
    PPi0();
    virtual ~PPi0();

    virtual Bool_t	Init(const char* configfile);
    virtual Bool_t	File(const char* gfile, const char* tfile, const char* hfile);
    virtual void 	Analyse();
	virtual void	Reconstruct();
	void	PostReconstruction();

	void	InitHistograms();
	Bool_t	WriteHistograms(TFile* hfile);
	Bool_t	WriteHistograms() {return WriteHistograms(HistFile);}
	
	Bool_t 	OpenPhysTreeFile(const char* pfile, Option_t* option);
	Bool_t 	OpenPhysTreeFile(const char* pfile) { return OpenPhysTreeFile(pfile,"RECREATE");}
	Bool_t	ClosePhysTreeFile();		
	Bool_t 	InitPhysicsTree(TFile* F);
	Bool_t	OpenPhysicsTree(TFile* F);
	Bool_t	OpenPhysicsTree() 	{return OpenPhysicsTree(PhysTreeFile);}	
	Bool_t 	WriteTrees(TFile* F);
	Bool_t 	WriteTrees()		{return WriteTrees(PhysTreeFile);}

};
#endif

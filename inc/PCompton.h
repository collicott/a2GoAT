#ifndef __PCompton_h__
#define __PCompton_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "PPhysics.h"

#define maxentries	1024

class	PCompton : public PPhysics
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
	
	Double_t OACut;
	
	Double_t theta_bin_size;
	Double_t phi_bin_size;

	TH1* 	neutral_theta;
	TH1*	neutral_phi;
	TH1*	charged_theta;
	TH1*	charged_phi;
	TH1* 	phi_diff;

	TH1* 	neutral_theta_cop;
	TH1*	neutral_phi_cop;
	TH1*	charged_theta_cop;
	TH1*	charged_phi_cop;
	TH1* 	phi_diff_cop;

	TH1* 	neutral_theta_cop_cth;
	TH1*	neutral_phi_cop_cth;
	TH1*	charged_theta_cop_cth;
	TH1*	charged_phi_cop_cth;
	TH1* 	phi_diff_cop_cth;
	
	TH1* 	phi_diff_cut;	
	TH1*	charged_theta_cut;
	TH1* 	opening_angle;
	TH1*	opening_angle_cut;
		
	TH1* 	time_compton;
	TH1* 	time_compton_cuts;	

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

	TH1* 	phi_prompt_70_90;
	TH1* 	phi_random_70_90;
	TH1* 	phi_sub_70_90;
	
	TH1* 	phi_prompt_90_110;
	TH1* 	phi_random_90_110;
	TH1* 	phi_sub_90_110;	

	TH1* 	phi_prompt_135_155;
	TH1* 	phi_random_135_155;
	TH1* 	phi_sub_135_155;
				
	TH1* 	MM_prompt_compton;
	TH1* 	MM_random_compton;
	TH1* 	MM_sub_compton;
	
	TH1* 	ME_prompt_compton;
	TH1* 	ME_random_compton;
	TH1* 	ME_sub_compton;
	
	TH3*	TC_theta_phi_prompt;
	TH3*	TC_theta_phi_random;

	TH1* 	opening_angle_prompt;
	TH1* 	opening_angle_random;
	TH1* 	opening_angle_sub;
		
	Int_t 	nentries;
	Int_t*	TC;
	Double_t* E;
	Double_t* time;
	Double_t* theta;
	Double_t* phi;
	Double_t* MissMass;
	Double_t* MissE;
	Double_t* OA;	
	
	Bool_t 	Prompt;
	Bool_t 	Random;
	
protected:


public:
    PCompton();
    virtual ~PCompton();

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

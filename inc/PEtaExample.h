#ifndef __PEta_h__
#define __PEta_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "PPhysics.h"

class	PEta : public PPhysics
{
private:

	Double_t time;
	TH1* 	time_eta;
	TH1* 	time_eta_cuts;	

	TH1* 	MM_prompt_eta;
	TH1* 	MM_random_eta;
	TH1* 	MM_eta;
	
	TH1* 	MM_prompt_eta_n;
	TH1* 	MM_random_eta_n;
	TH1* 	MM_eta_n;

	TH1* 	MM_prompt_eta_n_6g;
	TH1* 	MM_random_eta_n_6g;
	TH1* 	MM_eta_n_6g;

	TH1* 	MM_prompt_eta_n_2g;
	TH1* 	MM_random_eta_n_2g;
	TH1* 	MM_eta_n_2g;

	TH1* 	MM_prompt_eta_n_3ol;
	TH1* 	MM_random_eta_n_3ol;
	TH1* 	MM_eta_n_3ol;

	TH1* 	MM_prompt_eta_n_5om;
	TH1* 	MM_random_eta_n_5om;
	TH1* 	MM_eta_n_5om;

	TH1* 	MM_prompt_eta_c;
	TH1* 	MM_random_eta_c;
	TH1* 	MM_eta_c;
	
	TH1* 	MM_prompt_eta_c_4d;
	TH1* 	MM_random_eta_c_4d;
	TH1* 	MM_eta_c_4d;		

	TH1* 	MM_prompt_eta_c_4d_2pi2g;
	TH1* 	MM_random_eta_c_4d_2pi2g;
	TH1* 	MM_eta_c_4d_2pi2g;

	Int_t 	N_eta;
	Int_t	N_5omn;
	Int_t 	N_3oln;
	Int_t 	N_6g;
	Int_t 	N_2g;
	Int_t	N_2piX;
	Int_t	N_other;
		
protected:


public:
    PEta();
    virtual ~PEta();

    virtual Bool_t	Init(Char_t* file_config);	
    virtual void 	Analyse();
	virtual void	Reconstruct();
	void	PostReconstruction();

	void	DefineHistograms();
	Bool_t	WriteHistograms(TFile* pfile);
	Bool_t	WriteHistograms() {return WriteHistograms(HistFile);}
};
#endif

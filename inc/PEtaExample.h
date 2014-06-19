#ifndef __PEtaExample_h__
#define __PEtaExample_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string> 

#include "PPhysics.h"

class	PEtaExample : public PPhysics
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

	TH1* 	MM_prompt_eta_c;
	TH1* 	MM_random_eta_c;
	TH1* 	MM_eta_c;
	
	TH1* 	MM_prompt_eta_c_4d;
	TH1* 	MM_random_eta_c_4d;
	TH1* 	MM_eta_c_4d;		

	Int_t 	N_eta;

protected:
    virtual Bool_t  Start();
    
    virtual void    ProcessEvent();
			void	PostReconstruction();	
				
			void	DefineHistograms();
			Bool_t	WriteHistograms(TFile* pfile);
			Bool_t	WriteHistograms() {return WriteHistograms(HistFile);}
			
public:
    PEtaExample();
    virtual ~PEtaExample();

    virtual Bool_t	Init(const char* configfile);

};
#endif

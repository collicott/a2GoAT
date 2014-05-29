#ifndef __PPi0Example_h__
#define __PPi0Example_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string> 

#include "PPhysics.h"

class	PPi0Example : public PPhysics
{
private:

	Double_t time;
	TH1* 	time_pi0;
	TH1* 	time_pi0_cuts;	

	TH1* 	MM_prompt_pi0;
	TH1* 	MM_random_pi0;
	TH1* 	MM_pi0;
	
	TH1* 	MM_prompt_pi0_n_2g;
	TH1* 	MM_random_pi0_n_2g;
	TH1* 	MM_pi0_n_2g;		

	Int_t 	N_pi0;

		
protected:
    virtual void    ProcessEvent()  {}
    virtual Bool_t  Start()         {}

public:
    PPi0Example();
    virtual ~PPi0Example();

    virtual Bool_t	Init(const char* configfile);	
    virtual Bool_t	File(const char* file_in, const char* file_out);    
    virtual void 	Analyse();
	virtual void	Reconstruct();
	void	PostReconstruction();

	void	DefineHistograms();
	Bool_t	WriteHistograms(TFile* pfile);
	Bool_t	WriteHistograms() {return WriteHistograms(HistFile);}
};
#endif

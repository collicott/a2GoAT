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
    char 	file_in[256];
	char 	file_out[256];

	TH1* 	MM_prompt_pi0;
	TH1* 	MM_random_pi0;
	TH1* 	MM_pi0;
	
	TH1* 	MM_prompt_eta;
	TH1* 	MM_random_eta;
	TH1* 	MM_eta;
	
protected:


public:
    PPi0();
    virtual ~PPi0();

    virtual Bool_t	Init(Char_t* file_config);	
    virtual void 	Analyse();
	virtual void	Reconstruct();

	void	DefineHistograms();
	Bool_t	WriteHistograms(TFile* pfile);
	Bool_t	WriteHistograms() {return WriteHistograms(PhysFile);}
};
#endif

#ifndef __GoAT_h__
#define __GoAT_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "GParticleReconstruction.h"
#include "GTreeManager.h"

class	GoAT : public GParticleReconstruction
{
private:
    char* 	file_in;
	char* 	file_out;
	Bool_t 	UseParticleReconstruction;
	
	Int_t 	SortNumberParticles;	
	Int_t  	Sort_nParticles_total;
	Int_t  	Sort_nParticles_total_condition;
	Int_t  	Sort_nParticles_CB;
	Int_t  	Sort_nParticles_CB_condition;	
	Int_t  	Sort_nParticles_TAPS;
	Int_t  	Sort_nParticles_TAPS_condition;		

protected:


public:
    GoAT();
    virtual ~GoAT();

    virtual Bool_t	Init(const char* file_in, const char* file_out, Char_t* file_config);	
    virtual void 	Analyse();
	virtual void	Reconstruct();
    virtual Bool_t	Write();
    virtual Bool_t	Sort();
    
};
#endif

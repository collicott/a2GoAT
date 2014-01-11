#ifndef __GoAT_h__
#define __GoAT_h__

#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#include "GSort.h"
#include "GParticleReconstruction.h"
#include "GoATTreeManager.h"

class	GoAT : public GSort
{
private:
    char 	file_in[256];
	char 	file_out[256];
	Int_t	UsePeriodMacro;
	Int_t 	period;
	
	Bool_t 	UseParticleReconstruction;

protected:


public:
    GoAT();
    virtual ~GoAT();

    virtual Bool_t	Init(Char_t* file_config);	
    
    virtual void 	Analyse();
	virtual void	Reconstruct();
    virtual Bool_t	Write();
    
};
#endif

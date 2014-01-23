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
	Int_t	UsePeriodMacro;
	Int_t 	period;
	
	Bool_t 	UseParticleReconstruction;

protected:


public:
    GoAT();
    virtual ~GoAT();

    virtual Bool_t	Init(Char_t* configfile);	
    virtual Bool_t	File(Char_t* file_in, Char_t* file_out);
    
    virtual void 	Analyse();
    virtual void	Reconstruct();
    virtual Bool_t	Write();
    
};
#endif

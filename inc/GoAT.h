#ifndef __GoAT_h__
#define __GoAT_h__

#include <iostream>
#include <fstream>
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

	Int_t 	nEvents_written;
protected:


public:
    GoAT();
    virtual ~GoAT();

    virtual Bool_t	Init(const char* configfile);	
    virtual Bool_t	File(const char* file_in, const char* file_out);
    
    virtual void 	Analyse();
    virtual void	Reconstruct();
    virtual Bool_t	Write();
    
};
#endif

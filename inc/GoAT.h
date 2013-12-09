#ifndef __GoAT_h__
#define __GoAT_h__

#include <iostream>
#include <fstream>
using namespace std;

#include "GParticleReconstruction.h"
#include "GTreeManager.h"

class	GoAT : public GParticleReconstruction
{
private:
    char* file_in;
	char* file_out;
	Bool_t UseParticleReconstruction;

protected:


public:
    GoAT();
    virtual ~GoAT();

    virtual Bool_t	Init(const char* file_in, const char* file_out);	
    virtual void 	Analyse();
	virtual void	Reconstruct();
    virtual Bool_t	Write();
};
#endif

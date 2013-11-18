//*************************************************************************
//* Author: Patrik Ott
//*************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TA2RootTree                                                          //
//                                                                      //
// This class is organising the output to ROOT files                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__


#include "GTreeManager.h"


class	GParticleReconstruction : public GTreeManager
{
private:
    
public:
	GParticleReconstruction();
	~GParticleReconstruction();
	
	virtual void	Reconstruct();
};


#endif


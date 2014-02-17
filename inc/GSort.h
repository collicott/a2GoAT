
#ifndef __GSort_h__
#define __GSort_h__

#include <vector>

#include "GTreeParticleManager.h"


#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0

class	GSort : public GTreeParticleManager
{
private:

protected:
	    
public:
    GSort(TFile& TreeFile);
	~GSort();

    std::vector<UInt_t> MultiplicityList;

    virtual void	Analyse()       {GTreeParticleManager::Analyse();}
    virtual void	Reconstruct();
};


#endif


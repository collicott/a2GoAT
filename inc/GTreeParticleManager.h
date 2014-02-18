#ifndef __GTreeParticleManager_h__
#define __GTreeParticleManager_h__

#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "GAcquTreeManager.h"


class  GTreeParticleManager : public GAcquTreeManager
{
private:
    TTree  tree;

    TClonesArray	photons;		// reconstructed
    TClonesArray	protons;		// reconstructed

protected:

public:
    GTreeParticleManager(TFile& TreeFile);
    ~GTreeParticleManager();

    Bool_t	Write(TFile& TreeFile);

    virtual void    Reconstruct();
    virtual void 	Analyse();
};


#endif

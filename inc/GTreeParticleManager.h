#ifndef __GTreeParticleManager_h__
#define __GTreeParticleManager_h__

#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "GAcquTreeManager.h"


class  GTreeParticleManager : public GAcquTreeManager
{
private:
    TTree  tree;

    TClonesArray	rootino;    // reconstructed
    TClonesArray	photon;		// reconstructed
    TClonesArray	elektron;	// reconstructed
    TClonesArray	piplus;		// reconstructed
    TClonesArray	proton;		// reconstructed
    TClonesArray	neutron;	// reconstructed

protected:

public:
    GTreeParticleManager(TFile& TreeFile);
    ~GTreeParticleManager();

    Bool_t	Write(TFile& TreeFile);

    virtual void    Reconstruct();
    virtual void 	Analyse();
};


#endif

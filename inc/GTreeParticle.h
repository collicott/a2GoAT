#ifndef __GTreeParticle_h__
#define __GTreeParticle_h__


#include <iostream>


#include "GTree.h"



class  GTreeParticle    : public GTree
{
private:
    TClonesArray*	rootino;    // reconstructed
    TClonesArray*	photon;		// reconstructed
    TClonesArray*	elektron;	// reconstructed
    TClonesArray*	piplus;		// reconstructed
    TClonesArray*	proton;		// reconstructed
    TClonesArray*	neutron;	// reconstructed

    UInt_t		nTagged;
    UInt_t		tagged_ch[128];
    Double_t	tagged_t[128];
    Double_t	photonbeam_E[128];

protected:
    virtual void    SetBranchAdresses();

public:
    GTreeParticle();
    ~GTreeParticle();

    virtual void    Clear();

    virtual Bool_t  Init(const char* filename_input, const char* filename_output, const Bool_t override = kFALSE);
};


#endif

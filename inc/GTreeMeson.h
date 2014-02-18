#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include "GTreeParticle.h"


#define MASS_PI0    135
#define MASS_ETA    453
#define MASS_ETAP   958
#define MASS_PROTON 928

class  GTreeMeson   : public GTreeParticle
{
private:
    Double_t        pi0Width;
    Double_t        etaWidth;
    Double_t        etapWidth;
    TClonesArray*	pi0;		// reconstructed
    TClonesArray*	eta;		// reconstructed
    TClonesArray*	etap;		// reconstructed

    void    Reconstruct2g();
    void    Reconstruct3g();
    void    Reconstruct6g();
    void    Reconstruct7g();
    void    Reconstruct10g();
    void    Reconstruct11g();
protected:
    virtual void    SetBranchAdresses();

public:
    GTreeMeson();
    ~GTreeMeson();

    virtual void    Clear();

    virtual Bool_t  Init(const char* filename_input, const char* filename_output, const Bool_t override = kFALSE);

};


#endif

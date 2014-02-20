#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include "GTreeParticle.h"


#define MASS_PI0    135
#define MASS_ETA    453
#define MASS_ETAP   958
#define MASS_PROTON 928


class  GTreeMeson   : public GTreeParticle
{
public:
    enum    GMesonDecay
    {
        Decay_pi0_2g                = 0,
        Decay_eta_2g                = 1,
        Decay_etap_2g               = 2,
        Decay_eta_3pi0_6g           = 5,
        Decay_etap_2pi0eta_6g       = 6,
        Decay_etap_2pi0eta_5pi0_10g = 14
    };

private:
    Int_t           daughterPDG[512][3];
    Int_t           daughterIndices[512][3];

    static  int		perm6g[15][6];

    void    Reconstruct2g();
    void    Reconstruct3g();
    void    Reconstruct6g();
    void    Reconstruct7g();
    void    Reconstruct10g();
    void    Reconstruct11g();
protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(const TString& _Name);
    ~GTreeMeson();

    inline  void            AddParticle(const TLorentzVector& vec, const Int_t nDaughters = 0, const Int_t* PDGList = 0, const Int_t* Indices = 0);
};

void    GTreeMeson::AddParticle(const TLorentzVector& vec, const Int_t nDaughters , const Int_t* PDGList, const Int_t* Indices)
{
    daughters[nParticles] = nDaughters;
    new(particles[nParticles]) TLorentzVector(vec);
    for(int i=0; i<nDaughters; i++)
    {
        daughterPDG[nParticles][i]      = PDGList[i];
        daughterIndices[nParticles][i]  = Indices[i];
    }
    nParticles++;
}

#endif

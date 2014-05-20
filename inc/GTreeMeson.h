#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include "GTreeParticle.h"


#define MASS_PI0    134.9766
#define MASS_ETA    547.853
#define MASS_ETAP   957.78
#define MASS_PROTON 938.272046


#define GTreeMeson_NDaughterEntries  16


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
    UChar_t        daughter0PDG[GTreeMeson_NDaughterEntries];
    UChar_t        daughter1PDG[GTreeMeson_NDaughterEntries];
    UChar_t        daughter2PDG[GTreeMeson_NDaughterEntries];
    UChar_t        daughter0Indices[GTreeMeson_NDaughterEntries];
    UChar_t        daughter1Indices[GTreeMeson_NDaughterEntries];
    UChar_t        daughter2Indices[GTreeMeson_NDaughterEntries];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeMeson();

    inline  void            AddParticle(const TLorentzVector& vec, const Int_t nDaughters = 0, const Int_t* PDGList = 0, const Int_t* Indices = 0);
            UChar_t         GetDaughterIndex(const Int_t index, const Int_t part)    const       {if(part==0) return daughter0Indices[index]; if(part==1) return daughter1Indices[index]; return daughter2Indices[index];}
};

void    GTreeMeson::AddParticle(const TLorentzVector& vec, const Int_t nDaughters , const Int_t* PDGList, const Int_t* Indices)
{
    daughters[nParticles] = nDaughters;
    new((*particles)[nParticles]) TLorentzVector(vec);
    if(nDaughters>0)
    {
        daughter0PDG[nParticles]      = PDGList[0];
        daughter0Indices[nParticles]  = Indices[0];
    }
    if(nDaughters>1)
    {
        daughter1PDG[nParticles]      = PDGList[1];
        daughter1Indices[nParticles]  = Indices[1];
    }
    if(nDaughters>2)
    {
        daughter2PDG[nParticles]      = PDGList[2];
        daughter2Indices[nParticles]  = Indices[2];
    }
    nParticles++;
}

#endif

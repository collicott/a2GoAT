#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include "GTreeParticle.h"


#define MASS_PI0    134.9766
#define MASS_ETA    547.853
#define MASS_ETAP   957.78
#define MASS_PROTON 938.272046


#define GTreeMeson_MaxEntries  64


class  GTreeMeson   : public GTreeParticle
{
private:
    UChar_t        daughter0PDG[GTreeMeson_MaxEntries];
    UChar_t        daughter1PDG[GTreeMeson_MaxEntries];
    UChar_t        daughter2PDG[GTreeMeson_MaxEntries];
    UChar_t        daughter0Indices[GTreeMeson_MaxEntries];
    UChar_t        daughter1Indices[GTreeMeson_MaxEntries];
    UChar_t        daughter2Indices[GTreeMeson_MaxEntries];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeMeson();

    inline  void            AddParticle(const TLorentzVector& vec, const Int_t PDGDaughter0, const Int_t IndexDaughter0, const Int_t PDGDaughter1, const Int_t IndexDaughter1);
    inline  void            AddParticle(const TLorentzVector& vec, const Int_t PDGDaughter0, const Int_t IndexDaughter0, const Int_t PDGDaughter1, const Int_t IndexDaughter1, const Int_t PDGDaughter2, const Int_t IndexDaughter2);
    inline  void            AddParticle(const TLorentzVector& vec, const Int_t nDaughters = 0, const Int_t* PDGList = 0, const Int_t* Indices = 0);
            UChar_t         GetDaughterIndex(const Int_t index, const Int_t daugther_index)    const       {if(daugther_index==0) return daughter0Indices[index]; if(daugther_index==1) return daughter1Indices[index]; return daughter2Indices[index];}
            TLorentzVector& GetDaughter(const Int_t index, const Int_t daugther_index);
    const   TLorentzVector& GetDaughter(const Int_t index, const Int_t daugther_index) const;
};


void    GTreeMeson::AddParticle(const TLorentzVector& vec, const Int_t PDGDaughter0, const Int_t IndexDaughter0, const Int_t PDGDaughter1, const Int_t IndexDaughter1)
{
    daughters[nParticles]   = 2;
    new((*particles)[nParticles]) TLorentzVector(vec);
    daughter0PDG[nParticles]      = PDGDaughter0;
    daughter0Indices[nParticles]  = IndexDaughter0;
    daughter1PDG[nParticles]      = PDGDaughter1;
    daughter1Indices[nParticles]  = IndexDaughter1;
    daughter2PDG[nParticles]      = 0;
    daughter2Indices[nParticles]  = 0;
    nParticles++;
}
void    GTreeMeson::AddParticle(const TLorentzVector& vec, const Int_t PDGDaughter0, const Int_t IndexDaughter0, const Int_t PDGDaughter1, const Int_t IndexDaughter1, const Int_t PDGDaughter2, const Int_t IndexDaughter2)
{
    daughters[nParticles]   = 3;
    new((*particles)[nParticles]) TLorentzVector(vec);
    daughter0PDG[nParticles]      = PDGDaughter0;
    daughter0Indices[nParticles]  = IndexDaughter0;
    daughter1PDG[nParticles]      = PDGDaughter1;
    daughter1Indices[nParticles]  = IndexDaughter1;
    daughter2PDG[nParticles]      = PDGDaughter2;
    daughter2Indices[nParticles]  = PDGDaughter2;
    nParticles++;
}
void    GTreeMeson::AddParticle(const TLorentzVector& vec, const Int_t nDaughters , const Int_t* PDGList, const Int_t* Indices)
{
    daughters[nParticles]   = nDaughters;
    new((*particles)[nParticles]) TLorentzVector(vec);
    switch(nDaughters)
    {
    case 0:
        daughter0PDG[nParticles]      = 0;
        daughter0Indices[nParticles]  = 0;
        daughter1PDG[nParticles]      = 0;
        daughter1Indices[nParticles]  = 0;
        daughter2PDG[nParticles]      = 0;
        daughter2Indices[nParticles]  = 0;
        break;
    case 1:
        daughter0PDG[nParticles]      = PDGList[0];
        daughter0Indices[nParticles]  = Indices[0];
        daughter1PDG[nParticles]      = 0;
        daughter1Indices[nParticles]  = 0;
        daughter2PDG[nParticles]      = 0;
        daughter2Indices[nParticles]  = 0;
        break;
    case 2:
        daughter0PDG[nParticles]      = PDGList[0];
        daughter0Indices[nParticles]  = Indices[0];
        daughter1PDG[nParticles]      = PDGList[1];
        daughter1Indices[nParticles]  = Indices[1];
        daughter2PDG[nParticles]      = 0;
        daughter2Indices[nParticles]  = 0;
        break;
    case 3:
        daughter0PDG[nParticles]      = PDGList[0];
        daughter0Indices[nParticles]  = Indices[0];
        daughter1PDG[nParticles]      = PDGList[1];
        daughter1Indices[nParticles]  = Indices[1];
        daughter2PDG[nParticles]      = PDGList[2];
        daughter2Indices[nParticles]  = Indices[2];
        break;
    }
    nParticles++;
}

#endif

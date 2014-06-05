#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include "GTreeParticle.h"


#define MASS_PI0    134.9766
#define MASS_ETA    547.853
#define MASS_ETAP   957.78
#define MASS_PROTON 938.272046


#define GTreeMeson_MaxEntries  64

using namespace std;

class  GTreeMeson   : public GTreeParticle
{
public:
    enum GTreeMeson_DecayType
    {
        Decay_NONE                  = 0,
        Decay_2Gamma,                               //2 subParticles
        Decay_2ChargedPi,                           //2 subParticles
        Decay_2ChargedPi1Gamma,                     //3 subParticles
        Decay_3Pi0,                                 //6 subParticles
        Decay_2Pi01ChargedPi,                       //5 subParticles
        Decay_1Pi02ChargedPi,                       //4 subParticles
        Decay_1Pi02ChargedPi1Gamma,                 //5 subParticles
        Decay_2Pi01Eta,                             //6 subParticles
    };

private:
    //UChar_t             nDaughters[GTreeMeson_MaxEntries];
    UChar_t             decayType[GTreeMeson_MaxEntries];
    TClonesArray*       subParticles0;
    TClonesArray*       subParticles1;
    TClonesArray*       subParticles2;
    TClonesArray*       subParticles3;
    TClonesArray*       subParticles4;
    TClonesArray*       subParticles5;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeMeson();

    inline  void            AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1);
    inline  void            AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2);
    inline  void            AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2, const TLorentzVector& _SubParticle3);
    inline  void            AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2, const TLorentzVector& _SubParticle3, const TLorentzVector& _SubParticle4);
    inline  void            AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2, const TLorentzVector& _SubParticle3, const TLorentzVector& _SubParticle4, const TLorentzVector& _SubParticle5);
    virtual void            Clear()     {nParticles = 0; particles->Clear(); subParticles0->Clear(); subParticles1->Clear(); subParticles2->Clear(); subParticles3->Clear(); subParticles4->Clear(); subParticles5->Clear();}
};


void    GTreeMeson::AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1)
{
    if(type != Decay_2Gamma && type != Decay_2ChargedPi)
    {
        cout << "Given Wrong type or wrong # of subParticles in GTreeMeson::AddParticle" << endl;
        return;
    }

    decayType[nParticles]   = type;
    new((*particles)[nParticles]) TLorentzVector(_SubParticle0 + _SubParticle1);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle0);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle1);
    nParticles++;
}
void    GTreeMeson::AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2)
{
    if(type != Decay_2ChargedPi1Gamma)
    {
        cout << "Given Wrong type or wrong # of subParticles in GTreeMeson::AddParticle" << endl;
        return;
    }

    decayType[nParticles]   = type;
    new((*particles)[nParticles]) TLorentzVector(_SubParticle0 + _SubParticle1 + _SubParticle2);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle0);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle1);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle2);
    nParticles++;
}
void    GTreeMeson::AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2, const TLorentzVector& _SubParticle3)
{
    if(type != Decay_1Pi02ChargedPi)
    {
        cout << "Given Wrong type or wrong # of subParticles in GTreeMeson::AddParticle" << endl;
        return;
    }

    decayType[nParticles]   = type;
    new((*particles)[nParticles]) TLorentzVector(_SubParticle0 + _SubParticle1 + _SubParticle2 + _SubParticle3);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle0);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle1);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle2);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle3);
    nParticles++;
}
void    GTreeMeson::AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2, const TLorentzVector& _SubParticle3, const TLorentzVector& _SubParticle4)
{
    if(type != Decay_2Pi01ChargedPi && type != Decay_1Pi02ChargedPi1Gamma)
    {
        cout << "Given Wrong type or wrong # of subParticles in GTreeMeson::AddParticle" << endl;
        return;
    }

    decayType[nParticles]   = type;
    new((*particles)[nParticles]) TLorentzVector(_SubParticle0 + _SubParticle1 + _SubParticle2 + _SubParticle3 + _SubParticle4);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle0);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle1);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle2);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle3);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle4);
    nParticles++;
}
void    GTreeMeson::AddParticle(const GTreeMeson_DecayType type, const TLorentzVector& _SubParticle0, const TLorentzVector& _SubParticle1, const TLorentzVector& _SubParticle2, const TLorentzVector& _SubParticle3, const TLorentzVector& _SubParticle4, const TLorentzVector& _SubParticle5)
{
    if(type != Decay_3Pi0 && type != Decay_2Pi01Eta)
    {
        cout << "Given Wrong type or wrong # of subParticles in GTreeMeson::AddParticle" << endl;
        return;
    }

    decayType[nParticles]   = type;
    new((*particles)[nParticles]) TLorentzVector(_SubParticle0 + _SubParticle1 + _SubParticle2 + _SubParticle3 + _SubParticle4 + _SubParticle5);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle0);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle1);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle2);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle3);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle4);
    new((*subParticles0)[nParticles]) TLorentzVector(_SubParticle5);
    nParticles++;
}

/*
void    GTreeMeson::AddParticle(const TLorentzVector& vec, const Int_t PDGDaughter0, const Int_t IndexDaughter0, const Int_t PDGDaughter1, const Int_t IndexDaughter1, const Int_t PDGDaughter2, const Int_t IndexDaughter2)
{
    daughters[nParticles]   = 3;
    new((*particles)[nParticles]) TLorentzVector(vec);
    daughter0PDG[nParticles]      = PDGDaughter0;
    daughter0Indices[nParticles]  = IndexDaughter0;
    daughter1PDG[nParticles]      = PDGDaughter1;
    daughter1Indices[nParticles]  = IndexDaughter1;
    daughter2PDG[nParticles]      = PDGDaughter2;
    daughter2Indices[nParticles]  = IndexDaughter2;
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
}*/

#endif

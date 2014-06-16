#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "GTree.h"


#define MASS_PI0    134.9766
#define MASS_ETA    547.853
#define MASS_ETAP   957.78
#define MASS_PROTON 938.272046


#define GTreeMeson_MaxEntries       16
#define GTreeMeson_MaxSubEntries    16

using namespace std;

class  GTreeMeson   : public GTree
{
private:
    UInt_t              nParticles;
    TClonesArray*       particles;
    UChar_t             nPhotons[GTreeMeson_MaxEntries];
    UChar_t             nChargedPi[GTreeMeson_MaxEntries];
    TClonesArray*       subParticles;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeMeson();

            void            AddParticle(const TLorentzVector& subParticle0, const TLorentzVector& subParticle1, const Int_t pdg0, const Int_t pdg1);
            void            AddParticle(const Int_t nSubPhotons, TLorentzVector** subPhotons_list, const Int_t nSubChargedPi, TLorentzVector** subChargedPi_list);
    virtual void            Clear()     {nParticles = 0; particles->Clear(); subParticles->Clear();}
            UInt_t          GetNParticles()                const	{return nParticles;}
            TLorentzVector& Meson(const Int_t particle)             {return *((TLorentzVector*)particles->At(particle));}
    const   TLorentzVector& Meson(const Int_t particle) const       {return *((TLorentzVector*)particles->At(particle));}
            TLorentzVector& Particle(const Int_t particle)          {return Meson(particle);}
    const   TLorentzVector& Particle(const Int_t particle) const    {return Meson(particle);}
            TLorentzVector& SubParticle(const Int_t meson, const Int_t subParticle)       {return *((TLorentzVector*)(((TClonesArray*)subParticles->At(subParticle))->At(subParticle)));}
    const   TLorentzVector& SubParticle(const Int_t meson, const Int_t subParticle) const {return *((TLorentzVector*)(((TClonesArray*)subParticles->At(subParticle))->At(subParticle)));}
};



#endif

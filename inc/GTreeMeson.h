#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "GTreeParticle.h"


#define MASS_PI0    134.9766
#define MASS_ETA    547.853
#define MASS_ETAP   957.78
#define MASS_PROTON 938.272046


#define GTreeMeson_MaxSubEntries    16

using namespace std;

class  GTreeMeson   : public GTreeParticle
{
private:
    UChar_t             nSubParticles[GTreeParticle_MaxEntries];
    UChar_t             nSubPhotons[GTreeParticle_MaxEntries];
    UChar_t             nSubChargedPi[GTreeParticle_MaxEntries];
    TClonesArray*       subParticles;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeMeson();

    //        void            AddParticle(Int_t subParticle_index0, const TLorentzVector& subParticle0, const Int_t pdg0, Int_t subParticle_index1, const TLorentzVector& subParticle1, const Int_t pdg1);
            void            AddParticle(const Int_t _NSubPhotons, Int_t* subPhotons_index, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPi, Int_t* subChargedPi_index, TLorentzVector** subChargedPi_list);
    //        void            AddParticle(const TLorentzVector& subParticle0, const TLorentzVector& subParticle1, const Int_t pdg0, const Int_t pdg1);
    //        void            AddParticle(const Int_t _NSubPhotons, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPi, TLorentzVector** subChargedPi_list);
    virtual void            Clear()     {GTreeParticle::Clear(); subParticles->Clear();}
            UInt_t          GetNMesons()                            const	{return GetNParticles();}
            UInt_t          GetNSubParticles(const Int_t meson)     const	{return nSubParticles[meson];}
            UInt_t          GetNSubPhotons(const Int_t meson)       const	{return nSubPhotons[meson];}
            UInt_t          GetNSubChargedPi(const Int_t meson)     const	{return nSubChargedPi[meson];}
            TLorentzVector& Meson(const Int_t meson)             {return Particle(meson);}
    const   TLorentzVector& Meson(const Int_t meson) const       {return Particle(meson);}
            TLorentzVector& SubParticle(const Int_t meson, const Int_t subParticle)       {return *((TLorentzVector*)(((TClonesArray*)subParticles->At(meson))->At(subParticle)));}
    const   TLorentzVector& SubParticle(const Int_t meson, const Int_t subParticle) const {return *((TLorentzVector*)(((TClonesArray*)subParticles->At(meson))->At(subParticle)));}
};



#endif

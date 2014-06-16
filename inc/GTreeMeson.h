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
    UChar_t             nMesons;
    TClonesArray*       mesons;
    UChar_t             nSubParticles[GTreeMeson_MaxEntries];
    UChar_t             nSubPhotons[GTreeMeson_MaxEntries];
    UChar_t             nSubChargedPi[GTreeMeson_MaxEntries];
    TClonesArray*       subParticles;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeMeson(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeMeson();

            void            AddParticle(const TLorentzVector& subParticle0, const TLorentzVector& subParticle1, const Int_t pdg0, const Int_t pdg1);
            void            AddParticle(const Int_t _NSubPhotons, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPi, TLorentzVector** subChargedPi_list);
    virtual void            Clear()     {nMesons = 0; mesons->Clear(); subParticles->Clear();}
            UInt_t          GetNMesons()                const	{return nMesons;}
            UInt_t          GetNSubParticles(const Int_t meson)          const	{return nSubParticles[meson];}
            UInt_t          GetNSubPhotons(const Int_t meson)            const	{return nSubPhotons[meson];}
            UInt_t          GetNSubChargedPi(const Int_t meson)          const	{return nSubChargedPi[meson];}
            TLorentzVector& Meson(const Int_t meson)             {return *((TLorentzVector*)mesons->At(meson));}
    const   TLorentzVector& Meson(const Int_t meson) const       {return *((TLorentzVector*)mesons->At(meson));}
            TLorentzVector& SubParticle(const Int_t meson, const Int_t subParticle)       {return *((TLorentzVector*)(((TClonesArray*)subParticles->At(meson))->At(subParticle)));}
    const   TLorentzVector& SubParticle(const Int_t meson, const Int_t subParticle) const {return *((TLorentzVector*)(((TClonesArray*)subParticles->At(meson))->At(subParticle)));}
};



#endif

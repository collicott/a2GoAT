#ifndef __GTreeParticle_h__
#define __GTreeParticle_h__


#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "GTree.h"


class   GTreeMeson;

class  GTreeParticle    : public GTree
{
private:
    UInt_t          EventNumber;
    UInt_t          nParticles;
    TClonesArray	particles;		// reconstructed
    Int_t           daughters[512];  // nDaughters in GTreeMeson


protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeParticle(const TString& _Name);
    ~GTreeParticle();

    inline  void            AddParticle(const TLorentzVector& vec, const Int_t _RawIndex = -1);
    virtual void            Clear()     {nParticles = 0; particles.Clear();}
            Int_t           GetEventNumber()    const       {return EventNumber;}
            TLorentzVector& Particle(const Int_t particle) {return *(TLorentzVector*)particles[particle];}
    const   TLorentzVector& Particle(const Int_t particle) const {return *((TLorentzVector*)particles[particle]);}
            void            SetEventNumber(const Int_t num) {EventNumber = num;}

    friend  class GTreeMeson;
};

void    GTreeParticle::AddParticle(const TLorentzVector& vec, const Int_t _RawIndex)
{
    daughters[nParticles] = _RawIndex;
    new(particles[nParticles]) TLorentzVector(vec);
    nParticles++;
}

#endif

#ifndef __GTreeParticle_h__
#define __GTreeParticle_h__


#include <TClonesArray.h>
#include <TLorentzVector.h>

#include "GTree.h"

#define GTreeParticle_MaxEntries  64

class   GTreeMeson;

class  GTreeParticle    : public GTree
{
private:
    UInt_t              nParticles;
    TClonesArray*       particles;	// reconstructed
    UChar_t             Apparatus[GTreeParticle_MaxEntries];
    Double_t            time[GTreeParticle_MaxEntries];
    UChar_t             clusterSize[GTreeParticle_MaxEntries];
    //Charged detector energies
    Double_t            d_E[GTreeParticle_MaxEntries];
    Double_t            WC0_E[GTreeParticle_MaxEntries];
    Double_t            WC1_E[GTreeParticle_MaxEntries];


protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();
            void    PrintParticle(const Int_t i) const;

public:
    GTreeParticle(GTreeManager *Manager, const TString& _Name);
    virtual ~GTreeParticle();

            void            AddParticle(const TLorentzVector& vec, const UChar_t _Apparatus = 0, const Double_t _d_E = 0, const Double_t _WC0_E = 0, const Double_t _WC1_E = 0, const Double_t _Time = 0, const UChar_t _ClusterSize = 0);
    virtual void            Clear() {nParticles = 0; particles->Clear();}
            UChar_t         GetApparatus(const Int_t index)     const	{return Apparatus[index];}
            UChar_t         GetClusterSize(const Int_t index)   const 	{return clusterSize[index];}
            Double_t        Get_dE(const Int_t index)           const	{return d_E[index];}
            UInt_t          GetNParticles()                     const	{return nParticles;}
    const	Double_t*       GetTime()                           const	{return time;}
            Double_t        GetTime(const Int_t index)          const	{return time[index];}
    const	Double_t*       GetWC0_E()                          const	{return WC0_E;}
            Double_t        GetWC0_E(const Int_t index)         const	{return WC0_E[index];}
    const	Double_t*       GetWC1_E()                          const	{return WC1_E;}
            Double_t        GetWC1_E(const Int_t index)         const	{return WC1_E[index];}
    inline          TLorentzVector& Particle(const Int_t particle);
    inline  const   TLorentzVector& Particle(const Int_t particle) const;
    virtual void            Print() const;
            void            RemoveParticles(const Int_t nIndices, const Int_t* indices);
            void            RemoveAllParticles();
    virtual Bool_t          Write();


    friend  class GTreeMeson;
};


TLorentzVector&         GTreeParticle::Particle(const Int_t particle)
{
    if(particle>=nParticles)
    {
        std::cout << "ERROR: Try to access particle " << particle << " in " << GetName() << ". Only " << nParticles << " in tree." << std::endl;
        static  TLorentzVector  helpVectorUnity(0,0,0,0);
        helpVectorUnity.SetPxPyPzE(0,0,0,0);
        return helpVectorUnity;
    }
    return *((TLorentzVector*)particles->At(particle));
}

const   TLorentzVector& GTreeParticle::Particle(const Int_t particle) const
{
    if(particle>=nParticles)
    {
        std::cout << "ERROR: Try to access particle " << particle << " in " << GetName() << ". Only " << nParticles << " in tree." << std::endl;
        static  TLorentzVector  helpVectorUnity(0,0,0,0);
        helpVectorUnity.SetPxPyPzE(0,0,0,0);
        return helpVectorUnity;
    }
    return *((TLorentzVector*)particles->At(particle));
}


#endif

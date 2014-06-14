#ifndef __GTreeTagger_h__
#define __GTreeTagger_h__


#include <TLorentzVector.h>
#include <TClonesArray.h>


#include "GTree.h"


#define GTreeTagger_MAX 512

class  GTreeTagger : public GTree
{
private:
    Int_t           nTagged;
    Int_t           tagged_ch[GTreeTagger_MAX];
    Double_t        tagged_t[GTreeTagger_MAX];
    Double_t        photonbeam_E[GTreeTagger_MAX];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeTagger(GTreeManager *Manager);
    virtual ~GTreeTagger();

    virtual void    Clear()             {nTagged = 0;}

            Int_t           GetNTagged()                        const	{return nTagged;}
    const	Double_t*       GetPhotonBeam_E()                   const	{return photonbeam_E;}
            Double_t        GetPhotonBeam_E(const Int_t index)	const	{return photonbeam_E[index];}
    const	Int_t*          GetTagged_ch()                      const	{return tagged_ch;}
            Int_t           GetTagged_ch(const Int_t index)     const	{return tagged_ch[index];}
    const	Double_t*       GetTagged_t()                       const	{return tagged_t;}
            Double_t        GetTagged_t(const Int_t index)      const	{return tagged_t[index];}
    TLorentzVector          GetVector(const Int_t index)        const   {return TLorentzVector(0, 0, photonbeam_E[index], photonbeam_E[index]);}
};

#endif

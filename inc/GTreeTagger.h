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
    Char_t          nPrompt;
    Char_t          promptIndex[GTreeTagger_MAX];
    Char_t          nRand;
    Char_t          randIndex[GTreeTagger_MAX];
    TClonesArray*	missing;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeTagger();
    virtual ~GTreeTagger();

    virtual void    Clear()             {nTagged = 0; ClearPromptRand();}
            void    ClearPrompt()       {nPrompt = 0;}
            void    ClearRand()         {nRand = 0;}
            void    ClearPromptRand()   {ClearPrompt(); ClearRand();}

    const   TLorentzVector& GetMissingVector(const Int_t index) const   {return *((TLorentzVector*)missing->At(index));}
            Int_t           GetNPrompt()                        const   {return nPrompt;}
            Int_t           GetNRand()                          const   {return nRand;}
            Int_t           GetNTagged()                        const	{return nTagged;}
    const	Double_t*       GetPhotonBeam_E()                   const	{return photonbeam_E;}
            Double_t        GetPhotonBeam_E(const Int_t index)	const	{return photonbeam_E[index];}
            Int_t           GetPromptIndex(const Int_t index)   const   {return promptIndex[index];}
    const	Char_t*         GetPromptIndex()   					const   {return promptIndex;}
            Int_t           GetRandIndex(const Int_t index)     const   {return randIndex[index];}
    const   Char_t*         GetRandIndex()     					const   {return randIndex;}
    const	Int_t*          GetTagged_ch()                      const	{return tagged_ch;}
            Int_t           GetTagged_ch(const Int_t index)     const	{return tagged_ch[index];}
    const	Double_t*       GetTagged_t()                       const	{return tagged_t;}
            Double_t        GetTagged_t(const Int_t index)      const	{return tagged_t[index];}
    TLorentzVector          GetVector(const Int_t index)        const   {return TLorentzVector(0, 0, photonbeam_E[index], photonbeam_E[index]);}
            void            RemovePrompt(const Int_t index);
            void            RemoveRand(const Int_t index);
            void            SetTagger(const Int_t _NTagged, const Int_t* _Tagged_ch, const Double_t *_Tagged_t, const Double_t* _Photonbeam_E, const TLorentzVector *missingVector);
            void            SetPrompt(const Int_t index)   {promptIndex[nPrompt] = index; nPrompt++;}
            void            SetRand(const Int_t index)   {randIndex[nRand] = index; nRand++;}
};

#endif

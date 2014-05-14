#ifndef __GTreeTrigger_h__
#define __GTreeTrigger_h__


#include "GTree.h"

#define GTreeTrigger_MAX 128


class  GTreeTrigger : public GTree
{
private:
    Double_t 	ESum;
    Int_t 		Mult;
    Int_t 		nTriggerPattern;
    Int_t 		TriggerPattern[GTreeTrigger_MAX];
    UChar_t     helicityBit;
    Int_t 		nError;
    Int_t 		ErrModID[GTreeTrigger_MAX];
    Int_t 		ErrModIndex[GTreeTrigger_MAX];
    Int_t 		ErrCode[GTreeTrigger_MAX];

   protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeTrigger();
    virtual ~GTreeTrigger();


    virtual void        Clear()                         {nTriggerPattern = 0; nError = 0;}
            Int_t 		GetMult()        		const	{return Mult;}
            Double_t	GetESum()           	const	{return ESum;}
            UChar_t 	GetHelicityBit()    	const	{return helicityBit;}
            Int_t		GetNTriggerPattern()    const	{return	nTriggerPattern;}
    const   Int_t*		GetTriggerPattern()     const	{return	TriggerPattern;}
            Int_t		GetNError()             const {return nError;}
    const   Int_t*		GetErrModID()           const {return ErrModID;}
    const   Int_t*		GetErrModIndex()        const {return ErrModIndex;}
    const   Int_t*		GetErrCode()            const {return ErrCode;}

};

#endif

#ifndef __GTreeScaler_h__
#define __GTreeScaler_h__


#include <TLorentzVector.h>

#include "GTree.h"


#define GTreeScaler_MAX 4096

class  GTreeScaler : public GTree
{
private:
    Int_t		EventNumber;
    Int_t		EventID;
    UInt_t		Scaler[GTreeScaler_MAX];

    Int_t		NScaler;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeScaler(GTreeManager *Manager);
    virtual ~GTreeScaler();

    virtual void        Clear()     {}
            Int_t 		GetEventID()        		const	{return EventID;}
            Int_t 		GetEventNumber()        	const	{return EventNumber;}
            Int_t 		GetNScaler()    			const	{return NScaler;}
    const	UInt_t*		GetScaler()                 const	{return	Scaler;}
            UInt_t		GetScaler(const Int_t index)const	{return	Scaler[index];}
            UInt_t		GetScalerEntry(const Int_t event_number);
            void 		SetNScaler(const Int_t num);
    virtual void        Print(const Bool_t All = kFALSE) const;
};


#endif

#ifndef __GTreeEvent_h__
#define __GTreeEvent_h__


#include "GTree.h"


class  GTreeEvent    : public GTree
{
private:
    UInt_t          EventNumber;

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeEvent();
    virtual ~GTreeEvent();

    virtual void            Clear()                         {}
            UInt_t          GetEventNumber()    const       {return EventNumber;}
            void            SetEventNumber(const Int_t num) {EventNumber = num;}
};


#endif

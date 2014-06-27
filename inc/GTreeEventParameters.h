#ifndef __GTreeEventParameters_h__
#define __GTreeEventParameters_h__


#include "GTree.h"

#define GTreeEventParameters_MAX 128


class  GTreeEventParameters : public GTree
{
private:
    UInt_t 		EventNumber;
    UChar_t     nReconstructed;

   protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeEventParameters(GTreeManager *Manager);
    virtual ~GTreeEventParameters();


    virtual void        Clear()                         {nReconstructed = 0;}
            UInt_t      GetEventNumber()        const	{return EventNumber;}
            UChar_t 	GetNReconstructed()    	const	{return nReconstructed;}
            void        SetEventNumber(const UInt_t number)    {EventNumber = number;}
            void        SetNReconstructed(const UChar_t number)    {nReconstructed = number;}

};

#endif

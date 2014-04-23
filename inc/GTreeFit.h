#ifndef __GTreeFit_h__
#define __GTreeFit_h__


#include "GTree.h"


class  GTreeFit    : public GTree
{
private:
    Double_t        ConfidenceLevel;
    Double_t        ChiSq;
    Double_t        Pull[24];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeFit();
    virtual ~GTreeFit();

    virtual void            Clear()     {}
            Double_t        GetConfidenceLevel()    	const      			{return ConfidenceLevel;}
            Double_t        GetChiSq()    				const      			{return ChiSq;}
	const	Double_t*       GetPull()    				const      			{return Pull;}
			Double_t		GetPull(const Int_t index)	const      			{return Pull[index];}
            void            SetConfidenceLevel(const Double_t val) 			{ConfidenceLevel = val;}
            void            SetChiSq(const Double_t val) 					{ChiSq = val;}
            void            SetPull(const Int_t index, const Double_t val)	{Pull[index] = val;}
};


#endif

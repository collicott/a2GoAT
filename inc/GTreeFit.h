#ifndef __GTreeFit_h__
#define __GTreeFit_h__

#include <TLorentzVector.h>

#include "GTree.h"

#define GTreeFit_NPulls 24



class  GTreeFit    : public GTree
{
private:
    Double_t        ConfidenceLevel;
    Double_t        ChiSq;
    Double_t        Pull[GTreeFit_NPulls];
    TLorentzVector*	particle;		// fitted

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeFit(GTreeManager *Manager);
    virtual ~GTreeFit();

            void            AddParticle(const TLorentzVector& vec)			{*particle	= vec;}
    virtual void            Clear()                                         {}
            Double_t        GetConfidenceLevel()    	const      			{return ConfidenceLevel;}
            Double_t        GetChiSq()    				const      			{return ChiSq;}
	const	Double_t*       GetPull()    				const      			{return Pull;}
			Double_t		GetPull(const Int_t index)	const      			{return Pull[index];}
            void            SetConfidenceLevel(const Double_t val) 			{ConfidenceLevel = val;}
            void            SetChiSq(const Double_t val) 					{ChiSq = val;}
            void            SetPull(const Int_t index, const Double_t val)	{Pull[index] = val;}
    const   TLorentzVector& GetParticle()                                   {return *particle;}
};
#endif

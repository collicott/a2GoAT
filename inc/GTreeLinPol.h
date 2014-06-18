#ifndef __GTreeLinPol_h__
#define __GTreeLinPol_h__


#include <TLorentzVector.h>

#include "GTree.h"


#define GTreeLinPol_MAX 4096

class  GTreeLinPol : public GTree
{
private:
    Int_t		plane;
    Double_t	polTable[352];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeLinPol(GTreeManager *Manager);
    virtual ~GTreeLinPol();

    virtual void        Clear()     {}
            Int_t 		GetPolPlane() const	{return plane;}
     const  Double_t*	GetPolTable() const	{return polTable;}


};


#endif

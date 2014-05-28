#ifndef __GSetMesonMass_h__
#define __GSetMesonMass_h__


#include "GTreeManager.h"


class  GSetMesonMass  : public GTreeManager
{
private:
    static  TLorentzVector  SetMass(const TLorentzVector& vec, const Double_t mass);

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GSetMesonMass();
    virtual ~GSetMesonMass();
};





#endif

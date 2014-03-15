#ifndef __GSetMesonMass_h__
#define __GSetMesonMass_h__


#include "GTreeManager.h"


class  GSetMesonMass  : public GTreeManager
{
private:
    static  TLorentzVector  SetMass(const TLorentzVector& vec, const Double_t mass);

protected:

    virtual void    ProcessEvent();

public:
    GSetMesonMass();
    virtual ~GSetMesonMass();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);

};





#endif

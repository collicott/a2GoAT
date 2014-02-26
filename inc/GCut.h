#ifndef __GCut_h__
#define __GCut_h__


#include <vector>
#include <fstream>

#include "GTreeManager.h"


class  GCut  : public GTreeManager
{
private:
    Double_t    pi0InvMass[2];
    Double_t    etaInvMass[2];
    Double_t    etapInvMass[2];
    Double_t    MisMass[2];

protected:

    virtual void    ProcessEvent();

public:
    GCut();
    virtual ~GCut();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);

    void    SetPi0InvMassCut(const Double_t min, const Double_t max)    {pi0InvMass[0]=min; pi0InvMass[1]=max;}
    void    SetEtaInvMassCut(const Double_t min, const Double_t max)    {etaInvMass[0]=min; etaInvMass[1]=max;}
    void    SetEtapInvMassCut(const Double_t min, const Double_t max)   {etapInvMass[0]=min; etapInvMass[1]=max;}
    void    SetMisMassCut(const Double_t min, const Double_t max)       {MisMass[0]=min; MisMass[1]=max;}
};





#endif

#ifndef __GPlotInvMass_h__
#define __GPlotInvMass_h__



#include "GTreeManager.h"
#include "TH1D.h"




class  GPlotInvMass    : public GTreeManager
{
private:
    TH1D*   invMass;

protected:
    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GPlotInvMass();
    virtual ~GPlotInvMass();
};





#endif

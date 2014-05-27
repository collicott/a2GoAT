#ifndef __GPlotEnergyBins_h__
#define __GPlotEnergyBins_h__



#include "GTreeManager.h"
#include "GHist.h"


class  GPlotEnergyBins  : public GTreeManager
{
private:
    GHistD*    invMassEtap20[10];
    GHistD*    invMassEtap10[20];
    bool            withFit;
    

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GPlotEnergyBins();
    virtual ~GPlotEnergyBins();

    void            WorkWithFit()                                   {withFit = true;}
};





#endif

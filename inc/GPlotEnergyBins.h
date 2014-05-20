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

public:
    GPlotEnergyBins();
    virtual ~GPlotEnergyBins();

    virtual Bool_t  Process();

    void            WorkWithFit()                                   {withFit = true;}
};





#endif

#ifndef __GPlotEnergyBins_h__
#define __GPlotEnergyBins_h__



#include "GTreeManager.h"
#include "GHist.h"


class  GPlotEnergyBins  : public GTreeManager
{
private:
    GHistD*    invMassEtap20[10];
    GHistD*    invMassEtap10[20];
    

protected:

    virtual void    ProcessEvent();

public:
    GPlotEnergyBins();
    virtual ~GPlotEnergyBins();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

#ifndef __GPlotScalers_h__
#define __GPlotScalers_h__



#include "GTreeManager.h"


class  GPlotScalers  : public GTreeManager
{
private:
    TH1D*    scalerMain;
    TH1D*    scalerEPT;
    

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GPlotScalers();
    virtual ~GPlotScalers();
};





#endif

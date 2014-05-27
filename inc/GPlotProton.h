#ifndef __GPlotProton_h__
#define __GPlotProton_h__


#include <TH1D.h>

#include "GTreeManager.h"


class  GPlotProton  : public GTreeManager
{
private:
    TH1D*    protonAngleDiffPrompt;
    TH1D*    protonAngleDiffRand;
    TH1D*    phiDiff;

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GPlotProton();
    virtual ~GPlotProton();
};





#endif

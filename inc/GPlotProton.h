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

public:
    GPlotProton();
    virtual ~GPlotProton();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

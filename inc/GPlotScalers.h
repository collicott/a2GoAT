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

public:
    GPlotScalers();
    virtual ~GPlotScalers();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

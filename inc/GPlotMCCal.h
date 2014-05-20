#ifndef __GPlotMCCal_h__
#define __GPlotMCCal_h__



#include "GTreeManager.h"




class  GPlotMCCal    : public GTreeManager
{
private:


protected:
    virtual void    ProcessEvent();

public:
    GPlotMCCal();
    virtual ~GPlotMCCal();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

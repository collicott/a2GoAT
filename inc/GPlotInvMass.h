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

public:
    GPlotInvMass();
    virtual ~GPlotInvMass();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

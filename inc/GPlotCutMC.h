#ifndef __GPlotCutMC_h__
#define __GPlotCutMC_h__



#include "GTreeManager.h"
#include "TH1D.h"




class  GPlotCutMC    : public GTreeManager
{
private:
    struct
    {
        TH1D*   invMassPi0[3];
        TH1D*   invMassEta;
    }   h_eta;
    struct
    {
        TH1D*   invMassPi0[2];
        TH1D*   invMassEta;
        TH1D*   invMassEtap;
    }   h_etap;

protected:
    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GPlotCutMC();
    virtual ~GPlotCutMC();
};





#endif

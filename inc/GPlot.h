#ifndef __GPlot_h__
#define __GPlot_h__


#include <TH1D.h>
#include <TH1I.h>

#include "GTreeManager.h"
#include "GHistTaggedMeson.h"


class  GPlot    : public GTreeManager
{
private:
    TFile*  file;

    GHistTaggedPi0*  pi0Hist;
    GHistTagged3Pi0* _3pi0Hist;
    GHistTaggedEta*  etaHist;
    GHistTaggedEtap* etapHist;

protected:

    virtual void    ProcessEvent();

public:
    GPlot(const TString& _Name);
    virtual ~GPlot();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

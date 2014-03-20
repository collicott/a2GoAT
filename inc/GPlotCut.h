#ifndef __GPlotCut_h__
#define __GPlotCut_h__



#include "GTreeManager.h"
#include "GHistCut.h"




class  GPlotCut    : public GTreeManager
{
private:
    struct
    {
        GHistCutProton* h2gPi0;
        GHistCutProton* h2gEta;
        GHistCutProton* h2gEtap;
        GHistCutProton* h6gPi0;
        GHistCutProton* h6gEta;
        GHistCutProton* h6gEtap;
    } hProton;
    struct
    {
        GHistCut* h2gPi0;
        GHistCut* h2gEta;
        GHistCut* h2gEtap;
        GHistCut* h6gPi0;
        GHistCut* h6gEta;
        GHistCut* h6gEtap;
    } hNoProton;

protected:
    virtual void    ProcessEvent();

public:
    GPlotCut();
    virtual ~GPlotCut();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

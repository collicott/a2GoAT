#ifndef __GPlotCut_h__
#define __GPlotCut_h__



#include "GTreeManager.h"
#include "GHistCut.h"


struct  GHistCutStruct
{
    GHistCut* hPi0;
    GHistCut* hEta;
    GHistCut* hEtap;
};
struct  GHistCutProtonStruct
{
    GHistCutProton* hPi0;
    GHistCutProton* hEta;
    GHistCutProton* hEtap;
};



class  GPlotCut    : public GTreeManager
{
private:
    struct
    {
        GHistCutStruct    h2g;
        GHistCutStruct    h6g;
    }   hNoProton;
    struct
    {
        GHistCutProtonStruct    h2g;
        GHistCutProtonStruct    h6g;
    }   hProton;

    void    Init();

protected:
    virtual void    ProcessEvent();

public:
    GPlotCut();
    virtual ~GPlotCut();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

#ifndef __GFitEtap6g_h__
#define __GFitEtap6g_h__

#include <TH1D.h>

#include "GTreeManager.h"
#include "GKinFitter.h"


class  GFitEtap6g  : public GTreeManager
{
private:
    TH1D*           Pull[24];
    TH1D*           ConfidenceLevel;
    TH1D*           ChiSq;
    
    GKinFitter	fit;

protected:

    virtual void    ProcessEvent();

public:
    GFitEtap6g();
    virtual ~GFitEtap6g();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

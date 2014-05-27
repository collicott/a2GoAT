#ifndef __GFitEtap6g_h__
#define __GFitEtap6g_h__

#include <TH1D.h>
#include <TH2F.h>

#include "GTreeManager.h"
#include "GKinFitter.h"


class  GFitEtap6g  : public GTreeManager
{
private:
    TH1D*           Pull[24];
    TH1D*           ConfidenceLevel;
    TH1D*           ChiSq;
    
    GKinFitter	fit;

    TFile*  GammaResFile;
    TH2F*   GammaEloss;
    TH2F*   GammaERes;
    TH2F*   GammaThetaRes;
    TH2F*   GammaPhiRes;

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GFitEtap6g();
    virtual ~GFitEtap6g();
};





#endif

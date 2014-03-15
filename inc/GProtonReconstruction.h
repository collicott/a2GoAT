#ifndef __GProtonReconstruction_h__
#define __GProtonReconstruction_h__

#include <TH1D.h>

#include "GTreeManager.h"


class  GProtonReconstruction  : public GTreeManager
{
private:
    Double_t        angleDiff;
    Double_t        angleDiffCut;

    TH1D*           PhiDiffPi0;
    TH1D*           PhiDiffEta;
    TH1D*           PhiDiffEtap;
    Double_t        phiDiffCut[2];

    //TLorentzVector  foundProton;

protected:

    virtual void    ProcessEvent();

public:
    GProtonReconstruction();
    virtual ~GProtonReconstruction();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

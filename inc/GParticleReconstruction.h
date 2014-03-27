#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__

#include "GCorrectScalers.h"



class  GParticleReconstruction  : public GCorrectScalers
{
private:
    Bool_t          DoScalerCorrection;
    TH1D*           CBTime;
    TH1D*           TAPSTime;
    TH1D*           CBTimeAfterCut;
    TH1D*           TAPSTimeAfterCut;

    Double_t    CBTimeCut[2];
    Double_t    TAPSTimeCut[2];

protected:

    virtual void    ProcessEvent();

public:
    GParticleReconstruction();
    virtual ~GParticleReconstruction();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);

    void    SetCBTimeCut(const Double_t min, const Double_t max)    {CBTimeCut[0]=min; CBTimeCut[1]=max;}
    void    SetTAPSTimeCut(const Double_t min, const Double_t max)  {TAPSTimeCut[0]=min; TAPSTimeCut[1]=max;}
    void    SetScalerCorrection(const Bool_t value) {DoScalerCorrection = value;}
};

#endif

#ifndef __GTaggerReconstruction_h__
#define __GTaggerReconstruction_h__


#include "GTreeManager.h"


class  GTaggerReconstruction  : public GTreeManager
{
private:
    Double_t        randWindow[2][2];
    Double_t        promptWindow[2];

    Int_t           nTagged;
    Int_t           tagged_ch[GTreeTagger_MAX];
    Double_t        tagged_t[GTreeTagger_MAX];
    Double_t        photonbeam_E[GTreeTagger_MAX];
    TLorentzVector  missingVector[GTreeTagger_MAX];


protected:

    virtual void    ProcessEvent();

public:
    GTaggerReconstruction();
    virtual ~GTaggerReconstruction();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
    
    void	SetTaggerTimePrompt(const Double_t min, const Double_t max)	{promptWindow[0] = min; promptWindow[1] = max;}
    void	SetTaggerTimeRand0(const Double_t min, const Double_t max)	{randWindow[0][0] = min; randWindow[0][1] = max;}
    void	SetTaggerTimeRand1(const Double_t min, const Double_t max)	{randWindow[1][0] = min; randWindow[1][1] = max;}
};





#endif

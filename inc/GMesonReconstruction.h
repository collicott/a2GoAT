#ifndef __GMesonReconstruction_h__
#define __GMesonReconstruction_h__


#include "GTreeManager.h"


class  GMesonReconstruction  : public GTreeManager
{
private:
    Double_t    pi0Width;
    Double_t    etaWidth;
    Double_t    etapWidth;

    static  Int_t   perm6g[15][6];
    static  Int_t   perm10g[27][10];

    void    Reconstruct2g();
    void    Reconstruct6g();
    void    Reconstruct10g();

protected:

    virtual void    ProcessEvent();

public:
    GMesonReconstruction();
    virtual ~GMesonReconstruction();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

#ifndef __GRawCut_h__
#define __GRawCut_h__


#include <vector>
#include <fstream>

#include "GTreeManager.h"


class  GRawCut  : public GTreeManager
{
private:

protected:
	Int_t   nPhoton;
    Int_t   nProton;

    virtual void    ProcessEvent();

public:
    GRawCut();
    virtual ~GRawCut();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);

    void    SetNPhoton(const Int_t Multiplicity);
    void    SetNProton(const Int_t Multiplicity);

};





#endif

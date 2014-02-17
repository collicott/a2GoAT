#ifndef __GTreeMeson_h__
#define __GTreeMeson_h__


#include "GTreeParticle.h"




class  GTreeMeson   : public GTreeParticle
{
private:

protected:
    virtual void    SetBranchAdresses();

public:
    GTreeMeson();
    ~GTreeMeson();

    virtual void    Clear();

    virtual Bool_t  Init(const char* filename_input, const char* filename_output, const Bool_t override = kFALSE);

};


#endif

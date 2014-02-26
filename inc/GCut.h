#ifndef __GCut_h__
#define __GCut_h__


#include <vector>
#include <fstream>

#include "GTreeManager.h"


class  GCut  : public GTreeManager
{
private:
    ifstream configfile;

    std::vector<Int_t>  CutNPhoton;
    std::vector<Int_t>  CutNProton;
    std::vector<Int_t>  CutNPi0;
    std::vector<Int_t>  CutNEta;
    std::vector<Int_t>  CutNEtap;
    std::vector<Int_t>  CutNPrompt;
    std::vector<Int_t>  CutNRand;

protected:

    virtual void    ProcessEvent();

public:
    GCut(const char *configname);
    virtual ~GCut();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

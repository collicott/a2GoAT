#ifndef __GPlotTagger_h__
#define __GPlotTagger_h__


#include    <TH1D.h>

#include "GTreeManager.h"


class  GPlotTagger  : public GTreeManager
{
private:
    TH1D    taggerTime;

protected:

    virtual void    ProcessEvent();

public:
    GPlotTagger();
    virtual ~GPlotTagger();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

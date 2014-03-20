#ifndef __GPlotTime_h__
#define __GPlotTime_h__


#include <TH1D.h>
#include <TH1I.h>

#include "GTreeManager.h"
#include "GHistTaggedMeson.h"


class  GPlotTime    : public GTreeManager
{
private:
    TH1D*           taggerTime;
    TH1D*           CBTime;
    TH1D*           TAPSTime;

protected:
    virtual void    ProcessEvent();
            void    FillTaggerTime(const Double_t _TaggerTime)  {taggerTime->Fill(_TaggerTime);}
            void    FillCBTime(const Double_t _CBTime)          {CBTime->Fill(_CBTime);}
            void    FillTAPSTime(const Double_t _TAPSTime)      {TAPSTime->Fill(_TAPSTime);}

public:
    GPlotTime();
    virtual ~GPlotTime();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};

#endif

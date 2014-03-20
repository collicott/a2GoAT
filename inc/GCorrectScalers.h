#ifndef __GCorrectScalers_h__
#define __GCorrectScalers_h__

#include "GTreeManager.h"



class  GCorrectScalers  : public GTreeManager
{
private:
    UInt_t  EventAtFirstScalerRead;
    UInt_t  EventAtLastScalerRead;
    UInt_t  actualEvent;

    TH1D*           taggerTime;
    TH1I*           accepted;

protected:

    virtual void    ProcessEvent();



public:
    GCorrectScalers();
    virtual ~GCorrectScalers();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
            UInt_t  GetEventAtFirstScalerRead()     const {return EventAtFirstScalerRead;}
            UInt_t  GetEventAtLastScalerRead()      const {return EventAtLastScalerRead;}
};

#endif

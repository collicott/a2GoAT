#ifndef __GCorrectScalers_h__
#define __GCorrectScalers_h__

#include "GTreeManager.h"



class  GCorrectScalers  : virtual public GTreeManager
{
private:
    UInt_t  EventAtFirstScalerRead;
    UInt_t  EventAtLastScalerRead;
    UInt_t  actualEvent;

protected:
    TH1D*           taggerTime;
    TH1I*           accepted;

    virtual void    ProcessEvent();



public:
    GCorrectScalers();
    virtual ~GCorrectScalers();

    virtual Bool_t  Process();
            UInt_t  GetEventAtFirstScalerRead()     const {return EventAtFirstScalerRead;}
            UInt_t  GetEventAtLastScalerRead()      const {return EventAtLastScalerRead;}
};

#endif

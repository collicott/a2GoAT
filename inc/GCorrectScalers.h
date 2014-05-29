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
    TH1I*           accepted;

public:
    GCorrectScalers();
    virtual ~GCorrectScalers();

    Bool_t  FindValidEvents();
    Bool_t  FindValidEvents(UInt_t& firstValidEvent, UInt_t& lastValidEvent);
    UInt_t  GetEventAtFirstScalerRead() const {return EventAtFirstScalerRead;}
    UInt_t  GetEventAtLastScalerRead()  const {return EventAtLastScalerRead;}
    Bool_t  TraverseValidEvents();
};

#endif

#include "GCorrectScalers.h"


using namespace std;


GCorrectScalers::GCorrectScalers()  :
    EventAtFirstScalerRead(0),
    EventAtLastScalerRead(0),
    actualEvent(0),
    accepted(0)
{
}

GCorrectScalers::~GCorrectScalers()
{
    if(accepted)    delete  accepted;
}

Bool_t  GCorrectScalers::FindValidEvents()
{
    if(!scalers->IsOpenForInput())
    {
        if(!scalers->OpenForInput())
        {
            cout << "Can not check for valid events related to scaler. Now treeScaler available." << endl;
            return false;
        }
    }

    if(scalers->GetNEntries()<2)
    {
        std::cout << "Less than 2 scaler reads. Can not find events with correct scalers" <<std::endl;
        return kFALSE;
    }

    scalers->GetEntry(0);
    EventAtFirstScalerRead   = scalers->GetEventNumber();
    scalers->GetEntry(scalers->GetNEntries()-1);
    EventAtLastScalerRead       = scalers->GetEventNumber();

    file_out->cd();
    accepted    = new TH1I("Accepted", "Events with correct scalers (all=0,accepted=1,rejected=2)", 3, 0, 3);
    accepted->SetBinContent(1, rawEvent->GetNEntries());
    accepted->SetBinContent(2, EventAtLastScalerRead-EventAtFirstScalerRead);
    accepted->SetBinContent(3, (EventAtFirstScalerRead+1)+(rawEvent->GetNEntries()-EventAtLastScalerRead-1));

    if(!Write(accepted))  return kFALSE;
    return kTRUE;
}

Bool_t  GCorrectScalers::FindValidEvents(UInt_t& firstValidEvent, UInt_t& lastValidEvent)
{
    if(!FindValidEvents())
        return kFALSE;
    firstValidEvent = EventAtFirstScalerRead+1;
    lastValidEvent  = EventAtLastScalerRead;
    return kTRUE;
}

Bool_t  GCorrectScalers::TraverseValidEvents()
{
    if(!FindValidEvents())
        return kFALSE;
    TraverseEntries(EventAtFirstScalerRead+1, EventAtLastScalerRead);
}

#include "GCorrectScalers.h"


using namespace std;


GCorrectScalers::GCorrectScalers()  :
    taggerTime(0),
    accepted(0)
{
}

GCorrectScalers::~GCorrectScalers()
{
    if(taggerTime)  delete  taggerTime;
    if(accepted)    delete  accepted;
}


void  GCorrectScalers::ProcessEvent()
{
    for(int i=0; i<tagger->GetNTagged(); i++)
        taggerTime->Fill(tagger->GetTagged_t(i));
    eventFlags->SetEventNumber(actualEvent);

    eventFlags->Fill();
    tagger->Fill();
    trigger->Fill();
    actualEvent++;
}

Bool_t  GCorrectScalers::Process()
{
    if(!scalers->IsOpenForInput())
        scalers->OpenForInput();
    if(scalers->GetNEntries()<2)
    {
        std::cout << "Less than 2 scaler reads. Can not find events with correct scalers" <<std::endl;
        return kFALSE;
    }
    scalers->GetEntry(0);
    EventAtFirstScalerRead   = scalers->GetEventNumber();
    scalers->GetEntry(scalers->GetNEntries()-1);
    EventAtLastScalerRead       = scalers->GetEventNumber();

    scalers->Clone();

    file_out->cd();
    taggerTime  = new TH1D("TaggerTimeOR", "TaggerTimeOR", 10000, -1000, 1000);
    accepted    = new TH1I("Accepted", "Events with correct scalers (all=0,accepted=1,rejected=2)", 3, 0, 3);
    accepted->SetBinContent(1, rawEvent->GetNEntries());
    accepted->SetBinContent(2, EventAtLastScalerRead-EventAtFirstScalerRead);
    accepted->SetBinContent(3, (EventAtFirstScalerRead+1)+(rawEvent->GetNEntries()-EventAtLastScalerRead-1));

    actualEvent = EventAtFirstScalerRead;
    TraverseEntries(EventAtFirstScalerRead+1, EventAtLastScalerRead);

    if(!Write())    return kFALSE;
    if(!Write(taggerTime))  return kFALSE;
    if(!Write(accepted))  return kFALSE;
    return kTRUE;
}

#include "GPlotTime.h"


using namespace std;


GPlotTime::GPlotTime()  :
    taggerTime(0),
    CBTime(0),
    TAPSTime(0)
{

}

GPlotTime::~GPlotTime()
{
    if(taggerTime)  delete  taggerTime;
    if(CBTime)      delete  CBTime;
    if(TAPSTime)    delete  TAPSTime;
}

void  GPlotTime::ProcessEvent()
{
    for(int i=0; i<rawEvent->GetNParticles(); i++)
    {
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_CB)
            CBTime->Fill(rawEvent->GetTime(i));
        if(rawEvent->GetApparatus(i) == GTreeRawEvent::APPARATUS_TAPS)
            TAPSTime->Fill(rawEvent->GetTime(i));
    }
    for(int i=0; i<tagger->GetNTagged(); i++)
    {
        taggerTime->Fill(tagger->GetTagged_t(i));
    }
}

Bool_t  GPlotTime::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenRawEvent())    return kFALSE;
    if(!OpenTagger())    return kFALSE;

    if(!Create(output_filename))    return kFALSE;

    file_out->cd();
    taggerTime = new TH1D("TaggerTimeOR", "TaggerTimeOR", 10000, -1000, 1000);
    file_out->cd();
    CBTime = new TH1D("CBTimeOR", "CBTimeOR", 10000, -1000, 1000);
    file_out->cd();
    TAPSTime = new TH1D("TAPSTimeOR", "TAPSTimeOR", 10000, -1000, 1000);

    TraverseEntries(0, rawEvent->GetNEntries()+1);

    if(!Write(taggerTime))  return kFALSE;
    if(!Write(CBTime))      return kFALSE;
    if(!Write(TAPSTime))    return kFALSE;

    return kTRUE;
}


#include "GPlotTagger.h"


using namespace std;


GPlotTagger::GPlotTagger()  :
    taggerTime("Time", "Tagger Time", 1000, -100, 100)
{
}

GPlotTagger::~GPlotTagger()
{

}

void  GPlotTagger::ProcessEvent()
{
    for(int i=0; i<tagger->GetNTagged(); i++)
        taggerTime.Fill(tagger->GetTagged_t(i));
}

Bool_t  GPlotTagger::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenTagger())    return kFALSE;
    if(!Create(output_filename))    return kFALSE;

    TraverseEntries(0, tagger->GetNEntries()+1);

    Write(&taggerTime);

    return kTRUE;
}


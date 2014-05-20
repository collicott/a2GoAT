#include "GRawCut.h"
#include <string>

using namespace std;


GRawCut::GRawCut()
{
    nPhoton         = -1;
    nProton         = -1;
    
}

GRawCut::~GRawCut()
{

}

void  GRawCut::ProcessEvent()
{
    if(rawEvent->GetNCB() != nPhoton && nPhoton != -1)
        return;

    if(rawEvent->GetNTAPS() != nProton && nProton != -1)
        return;
            
    eventFlags->Fill();
    trigger->Fill();
    tagger->Fill();
}

Bool_t  GRawCut::Process()
{
    scalers->Clone();

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;

}

void    GRawCut::SetNPhoton(const Int_t Multiplicity)
{
    nPhoton = Multiplicity;
}
void    GRawCut::SetNProton(const Int_t Multiplicity)
{
    nProton = Multiplicity;
}


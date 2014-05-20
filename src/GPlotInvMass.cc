#include "GPlotInvMass.h"


using namespace std;


GPlotInvMass::GPlotInvMass()
{
    invMass	= 0;
}

GPlotInvMass::~GPlotInvMass()
{
    if(invMass)   delete  invMass;
}


    

void  GPlotInvMass::ProcessEvent()
{
        if(photons->GetNParticles() == 2)
        {
            invMass->Fill((photons->Particle(0)+photons->Particle(1)).M());
        }
}

Bool_t  GPlotInvMass::Process()
{
    invMass   = new TH1D("invMass", "invMass", 2000, 0, 2000);

    TraverseEntries(0, photons->GetNEntries()+1);
    
    Write(invMass);

    return kTRUE;
}


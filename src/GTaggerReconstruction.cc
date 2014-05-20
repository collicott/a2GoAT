#include "GTaggerReconstruction.h"


using namespace std;


GTaggerReconstruction::GTaggerReconstruction()
{
    randWindow[0][0]    = -510;
    randWindow[0][1]    = -10;
    promptWindow[0]     = -5;
    promptWindow[1]     = 5;
    randWindow[1][0]    = 10;
    randWindow[1][1]    = 510;
}

GTaggerReconstruction::~GTaggerReconstruction()
{

}

void  GTaggerReconstruction::ProcessEvent()
{	
    tagger->ClearPromptRand();
    nTagged = 0;
    for(int i=0; i<tagger->GetNTagged(); i++)
    {
        if((tagger->GetTagged_t(i)>randWindow[0][0] && tagger->GetTagged_t(i)<randWindow[0][1]) ||
           (tagger->GetTagged_t(i)>randWindow[1][0] && tagger->GetTagged_t(i)<randWindow[1][1]))
        {
            tagged_ch[nTagged]      = tagger->GetTagged_ch(i);
            tagged_t[nTagged]       = tagger->GetTagged_t(i);
            photonbeam_E[nTagged]   = tagger->GetPhotonBeam_E(i);
                      missingVector[nTagged].SetPxPyPzE(0,0,photonbeam_E[nTagged],photonbeam_E[nTagged] + MASS_PROTON);
            for(int p=0; p<photons->GetNParticles(); p++)
               missingVector[nTagged]   -= photons->Particle(p);

            tagger->SetRand(nTagged);
            nTagged++;
        }
        if(tagger->GetTagged_t(i)>promptWindow[0] && tagger->GetTagged_t(i)<promptWindow[1])
        {
            tagged_ch[nTagged]      = tagger->GetTagged_ch(i);
            tagged_t[nTagged]       = tagger->GetTagged_t(i);
            photonbeam_E[nTagged]   = tagger->GetPhotonBeam_E(i);
            missingVector[nTagged].SetPxPyPzE(0,0,photonbeam_E[nTagged],photonbeam_E[nTagged] + MASS_PROTON);
            for(int p=0; p<photons->GetNParticles(); p++)
               missingVector[nTagged]   -= photons->Particle(p);
            tagger->SetPrompt(nTagged);
            nTagged++;
        }
    }
    tagger->SetTagger(nTagged, tagged_ch, tagged_t, photonbeam_E, missingVector);
    //std::cout << tagger->GetNTagged() << "   " << tagger->GetNPrompt() << "   " << tagger->GetNRand() << std::endl;
    tagger->Fill();
}

Bool_t  GTaggerReconstruction::Process()
{
    etap->Clone();
    eta->Clone();
    pi0->Clone();
    photons->Clone();
    protons->Clone();
    eventFlags->Clone();
    trigger->Clone();
    scalers->Clone();

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;
}


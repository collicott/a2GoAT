#include "GProtonReconstruction.h"


using namespace std;


GProtonReconstruction::GProtonReconstruction()  :
    angleDiffCut(4)
{

}

GProtonReconstruction::~GProtonReconstruction()
{

}

void  GProtonReconstruction::ProcessEvent()
{
    if(protons->GetNParticles() == 0)
    {
        etap->Fill();
        eta->Fill();
        pi0->Fill();
        photons->Fill();
        protons->Fill();
        tagger->Fill();
        eventFlags->Fill();
    }
    else
    {
        for(int i=0; i<tagger->GetNPrompt(); i++)
        {
            for(int p=0; p<protons->GetNParticles(); p++)
            {
                angleDiff = protons->Particle(p).Angle(tagger->GetMissingVector(tagger->GetPromptIndex(i)).Vect());
                if(angleDiff < angleDiffCut)
                {

                }
                else
                {
                    protons->RemoveParticle(p);
                    p--;
                }
            }
        }
            if(tagger->GetNRand() == 1)
            {

            }

    }
}

Bool_t  GProtonReconstruction::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenEtap())    return kFALSE;
    if(!OpenEta())    return kFALSE;
    if(!OpenPi0())    return kFALSE;
    if(!OpenPhotons())    return kFALSE;
    if(!OpenProtons())    return kFALSE;
    if(!OpenTagger())    return kFALSE;
    if(!OpenScalers())    return kFALSE;
    if(!OpenEventFlags())    return kFALSE;


    if(!Create(output_filename))    return kFALSE;
    if(!CreateEtap())    return kFALSE;
    if(!CreateEta())    return kFALSE;
    if(!CreatePi0())    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;
    if(!CreateTagger())    return kFALSE;
    if(!CreateEventFlags())    return kFALSE;
    scalers->Clone(*file_out);

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;
}


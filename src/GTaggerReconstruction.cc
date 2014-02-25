#include "GTaggerReconstruction.h"


using namespace std;


GTaggerReconstruction::GTaggerReconstruction()
{
    randWindow[0][0]    = -15;
    randWindow[0][1]    = -10;
    promptWindow[0]     = -5;
    promptWindow[1]     = 5;
    randWindow[1][0]    = 10;
    randWindow[1][1]    = 15;
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
            tagger->SetRand(nTagged);
            nTagged++;
        }
        if(tagger->GetTagged_t(i)>promptWindow[0] && tagger->GetTagged_t(i)<promptWindow[1])
        {
            tagged_ch[nTagged]      = tagger->GetTagged_ch(i);
            tagged_t[nTagged]       = tagger->GetTagged_t(i);
            photonbeam_E[nTagged]   = tagger->GetPhotonBeam_E(i);
            tagger->SetPrompt(nTagged);
            nTagged++;
        }
    }
    tagger->SetTagger(nTagged, tagged_ch, tagged_t, photonbeam_E);
    //std::cout << tagger->GetNTagged() << "   " << tagger->GetNPrompt() << "   " << tagger->GetNRand() << std::endl;
    tagger->Fill();
}

Bool_t  GTaggerReconstruction::Process(const char* input_filename, const char* output_filename)
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
    etap->Clone(*file_out);
    eta->Clone(*file_out);
    pi0->Clone(*file_out);
    photons->Clone(*file_out);
    protons->Clone(*file_out);
    if(!CreateTagger())    return kFALSE;
    eventFlags->Clone(*file_out);
    scalers->Clone(*file_out);

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;
}


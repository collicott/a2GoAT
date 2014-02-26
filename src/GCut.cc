#include "GCut.h"
#include <string>

using namespace std;


GCut::GCut()
{
    pi0InvMass[0]   = 100;
    pi0InvMass[1]   = 170;
    etaInvMass[0]   = 500;
    etaInvMass[1]   = 590;
    etapInvMass[0]  = 900;
    etapInvMass[1]  = 1010;
    MisMass[0]      = 900;
    MisMass[1]      = 955;
}

GCut::~GCut()
{

}

void  GCut::ProcessEvent()
{
    Double_t help;
    for(int i=0; i<pi0->GetNParticles(); i++)
    {
        help    = pi0->Particle(i).M();
        if(help<pi0InvMass[0] || help>pi0InvMass[1])
            return;
    }
    for(int i=0; i<eta->GetNParticles(); i++)
    {
        help    = eta->Particle(i).M();
        if(help<etaInvMass[0] || help>etaInvMass[1])
            return;
    }
    for(int i=0; i<etap->GetNParticles(); i++)
    {
        help    = etap->Particle(i).M();
        if(help<etapInvMass[0] || help>etapInvMass[1])
            return;
    }

    if(tagger->GetNPrompt()>1 || tagger->GetNRand()>1)
        return;

    if(tagger->GetNPrompt()==1)
    {
        help    = tagger->GetMissingVector(tagger->GetPromptIndex(0)).M();
        if(help<MisMass[0] || help>MisMass[1])
            tagger->ClearPrompt();
    }
    if(tagger->GetNRand()==1)
    {
        help    = tagger->GetMissingVector(tagger->GetRandIndex(0)).M();
        if(help<MisMass[0] || help>MisMass[1])
            tagger->ClearRand();
    }

    if(tagger->GetNPrompt()==0 &&tagger->GetNRand()==0)
        return;

    eventFlags->Fill();
    tagger->Fill();
    photons->Fill();
    protons->Fill();
    pi0->Fill();
    eta->Fill();
    etap->Fill();
}

Bool_t  GCut::Process(const char* input_filename, const char* output_filename)
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

    //if (configfile.is_open())
        //+	{
        //+		while ( getline (configfile,str) )
        //+		{
}


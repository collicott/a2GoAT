#include "GCut.h"
#include <string>

using namespace std;


GCut::GCut()    :
    doMultiplicity(kFALSE),
    doInvMass(kFALSE),
    doMisMass(kFALSE)
{
    nPhoton         = -1;
    nProton         = -1;
    nPi0            = -1;
    nEta            = -1;
    nEtap           = -1;

    pi0InvMass[0]   = 0;
    pi0InvMass[1]   = 2500;
    etaInvMass[0]   = 0;
    etaInvMass[1]   = 2500;
    etapInvMass[0]  = 0;
    etapInvMass[1]  = 2500;

    MisMass[0]      = 0;
    MisMass[1]      = 2500;
}

GCut::~GCut()
{

}

Bool_t      GCut::DoMultiplicity()
{
    if(photons->GetNParticles() != nPhoton && nPhoton != -1)
        return kFALSE;

    if(protons->GetNParticles() != nProton && nProton != -1)
        return kFALSE;

    if(pi0->GetNParticles() != nPi0 && nPi0 != -1)
        return kFALSE;

    if(eta->GetNParticles() != nEta && nEta != -1)
        return kFALSE;

    if(etap->GetNParticles() != nEtap && nEtap != -1)
        return kFALSE;

    return kTRUE;
}

Bool_t      GCut::DoInvMass()
{
    Double_t help;
    for(int i=0; i<pi0->GetNParticles(); i++)
    {
        help    = pi0->Particle(i).M();
        if(help<pi0InvMass[0] || help>pi0InvMass[1])
            return kFALSE;
    }
    for(int i=0; i<eta->GetNParticles(); i++)
    {
        help    = eta->Particle(i).M();
        if(help<etaInvMass[0] || help>etaInvMass[1])
            return kFALSE;
    }
    for(int i=0; i<etap->GetNParticles(); i++)
    {
        help    = etap->Particle(i).M();
        if(help<etapInvMass[0] || help>etapInvMass[1])
            return kFALSE;
    }

    return kTRUE;
}

Bool_t      GCut::DoMisMass()
{
    if(tagger->GetNPrompt()>1 || tagger->GetNRand()>1)
        return kFALSE;

    Double_t help;
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

    if(tagger->GetNPrompt()==0 && tagger->GetNRand()==0)
        return kFALSE;

    return kTRUE;
}

void  GCut::ProcessEvent()
{
    if(doMultiplicity)
    {
        if(!DoMultiplicity())
            return;
    }
    if(doInvMass)
    {
        if(!DoInvMass())
            return;
    }
    if(doMisMass)
    {
        if(!DoMisMass())
            return;
    }

    eventFlags->Fill();
    tagger->Fill();
    trigger->Fill();
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
    if(!OpenTrigger())    return kFALSE;
    if(!OpenEventFlags())    return kFALSE;


    if(!Create(output_filename))    return kFALSE;
    if(!CreateEtap())    return kFALSE;
    if(!CreateEta())    return kFALSE;
    if(!CreatePi0())    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;
    if(!CreateTagger())    return kFALSE;
    if(!CreateTrigger())    return kFALSE;
    if(!CreateEventFlags())    return kFALSE;
    scalers->Clone(*file_out);

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;
}

void    GCut::SetNPhoton(const Int_t Multiplicity)
{
    doMultiplicity  = kTRUE;
    nPhoton = Multiplicity;
}
void    GCut::SetNProton(const Int_t Multiplicity)
{
    doMultiplicity  = kTRUE;
    nProton = Multiplicity;
}
void    GCut::SetNPi0(const Int_t Multiplicity)
{
    doMultiplicity  = kTRUE;
    nPi0 = Multiplicity;
}
void    GCut::SetNEta(const Int_t Multiplicity)
{
    doMultiplicity  = kTRUE;
    nEta = Multiplicity;
}
void    GCut::SetNEtap(const Int_t Multiplicity)
{
    doMultiplicity  = kTRUE;
    nEtap = Multiplicity;
}

void    GCut::SetPi0InvMassCut(const Double_t min, const Double_t max)
{
    doInvMass= kTRUE;
    pi0InvMass[0]=min;
    pi0InvMass[1]=max;
}
void    GCut::SetEtaInvMassCut(const Double_t min, const Double_t max)
{
    doInvMass= kTRUE;
    etaInvMass[0]=min;
    etaInvMass[1]=max;
}
void    GCut::SetEtapInvMassCut(const Double_t min, const Double_t max)
{
    doInvMass= kTRUE;
    etapInvMass[0]=min;
    etapInvMass[1]=max;
}
void    GCut::SetMisMassCut(const Double_t min, const Double_t max)
{
    doMisMass= kTRUE;
    MisMass[0]=min;
    MisMass[1]=max;
}

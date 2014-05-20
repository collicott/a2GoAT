#include "GProtonReconstruction.h"


using namespace std;


GProtonReconstruction::GProtonReconstruction()  :
    angleDiffCut(4),
    PhiDiffEtap(new TH1D("PhiDiffEtap", "Difference in Phi for proton and etap", 360, 0, 360)),
    PhiDiffEta(new TH1D("PhiDiffEta", "Difference in Phi for proton and eta", 360, 0, 360)),
    PhiDiffPi0(new TH1D("PhiDiffPi0", "Difference in Phi for proton and pi0", 360, 0, 360))
{
    phiDiffCut[0]   = 160;
    phiDiffCut[1]   = 200;
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
        trigger->Fill();
        tagger->Fill();
        eventFlags->Fill();
    }
    else if(protons->GetNParticles() == 1)
    {
        Bool_t  found   = kFALSE;
        for(int i=0; i<tagger->GetNPrompt(); i++)
        {
            angleDiff = protons->Particle(0).Angle(tagger->GetMissingVector(tagger->GetPromptIndex(i)).Vect());
            if(angleDiff < angleDiffCut)
            {
                found   = kTRUE;
            }
            else
            {
                tagger->RemovePrompt(i);
            }
        }
        for(int i=0; i<tagger->GetNRand(); i++)
        {
            angleDiff = protons->Particle(0).Angle(tagger->GetMissingVector(tagger->GetRandIndex(i)).Vect());
            if(angleDiff < angleDiffCut)
            {
                found   = kTRUE;
            }
            else
            {
                tagger->RemoveRand(i);
            }
        }

        if(found)
        {
            Double_t    phiDiff = 0;
            if(etap->GetNParticles() == 1)
            {
                phiDiff = TMath::RadToDeg()*TMath::Abs(protons->Particle(0).Phi() - etap->Particle(0).Phi());
                PhiDiffEtap->Fill(phiDiff);
            }
            else if(eta->GetNParticles() == 1)
            {
                phiDiff = TMath::RadToDeg()*TMath::Abs(protons->Particle(0).Phi() - eta->Particle(0).Phi());
                PhiDiffEta->Fill(phiDiff);
            }
            else if(pi0->GetNParticles() == 1)
            {
                phiDiff = TMath::RadToDeg()*TMath::Abs(protons->Particle(0).Phi() - pi0->Particle(0).Phi());
                PhiDiffPi0->Fill(phiDiff);
            }

            if(phiDiff<phiDiffCut[0] || phiDiff>phiDiffCut[1])
                return;

            eventFlags->Fill();
            tagger->Fill();
            trigger->Fill();
            photons->Fill();
            protons->Fill();
            pi0->Fill();
            eta->Fill();
            etap->Fill();
        }
    }
    /*else
    {
        etap->Fill();
        eta->Fill();
        pi0->Fill();
        photons->Fill();
        protons->Fill();
        trigger->Fill();
        tagger->Fill();
        eventFlags->Fill();
    }*/

        /*for(int i=0; i<tagger->GetNPrompt(); i++)
        {
            for(int p=0; p<protons->GetNParticles(); p++)
            {
                angleDiff = protons->Particle(p).Angle(tagger->GetMissingVector(tagger->GetPromptIndex(i)).Vect());
                if(angleDiff >= angleDiffCut)
                {
                    protons->RemoveParticle(p);
                    p--;
                }
            }
        }
        for(int i=0; i<tagger->GetNRand(); i++)
        {
            for(int p=0; p<protons->GetNParticles(); p++)
            {
                angleDiff = protons->Particle(p).Angle(tagger->GetMissingVector(tagger->GetRandIndex(i)).Vect());
                if(angleDiff >= angleDiffCut)
                {
                    protons->RemoveParticle(p);
                    p--;
                }
            }
        }
            if(tagger->GetNRand() == 1)
            {

            }

    }*/
}

Bool_t  GProtonReconstruction::Process()
{
    scalers->Clone();

    TraverseEntries(0, photons->GetNEntries()+1);

    Write(PhiDiffEtap);
    Write(PhiDiffEta);
    Write(PhiDiffPi0);
    TH1D    PhiDiff("PhiDiff", "Difference in Phi for proton and all mesons", 360, 0, 360);
    PhiDiff.Add(PhiDiffEtap);
    PhiDiff.Add(PhiDiffEta);
    PhiDiff.Add(PhiDiffPi0);
    Write(&PhiDiff);
    return kTRUE;
}


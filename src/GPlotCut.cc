#include "GPlotCut.h"


using namespace std;


GPlotCut::GPlotCut()    :
{
    file
    hProton.h2gPi0      = new GHistCutProton();
    hProton.h2gEta      = 0;
    hProton.h2gEtap     = 0;
    hProton.h6gPi0      = 0;
    hProton.h6gEta      = 0;
    hProton.h6gEtap     = 0;

    hNoProton.h2gPi0      = 0;
    hNoProton.h2gEta      = 0;
    hNoProton.h2gEtap     = 0;
    hNoProton.h6gPi0      = 0;
    hNoProton.h6gEta      = 0;
    hNoProton.h6gEtap     = 0;
}

GPlotCut::~GPlotCut()
{
}

void  GPlotCut::ProcessEvent()
{
    if(proton)
    {
    }
    else
    {
        if(photons->GetNParticles() == 2)
        {
            if(pi0->GetNParticles() == 1)
            {
                if(tagger->GetNPrompt() == 1)
                {
                    //pi0Hist->FillPromptTagger(tagger->GetMissingVector(tagger->GetPromptIndex(0)),tagger->GetTagged_t(tagger->GetPromptIndex(0)),tagger->GetPhotonBeam_E(tagger->GetPromptIndex(0)),tagger->GetTagged_ch(tagger->GetPromptIndex(0)));
                    //pi0Hist->FillPromptMeson(pi0->Particle(0));
                    //pi0Hist->FillPromptPhoton(photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                }
                if(tagger->GetNRand() == 1)
                {
                    //pi0Hist->FillRandTagger(tagger->GetMissingVector(tagger->GetRandIndex(0)),tagger->GetTagged_t(tagger->GetRandIndex(0)),tagger->GetPhotonBeam_E(tagger->GetRandIndex(0)),tagger->GetTagged_ch(tagger->GetRandIndex(0)));
                    //pi0Hist->FillRandMeson(pi0->Particle(0));
                    //pi0Hist->FillRandPhoton(photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                if(tagger->GetNPrompt() == 1)
                {
                    //etaHist->FillPromptTagger(tagger->GetMissingVector(tagger->GetPromptIndex(0)),tagger->GetTagged_t(tagger->GetPromptIndex(0)),tagger->GetPhotonBeam_E(tagger->GetPromptIndex(0)),tagger->GetTagged_ch(tagger->GetPromptIndex(0)));
                    //etaHist->FillPromptDaughterMeson(eta->Particle(0));
                    //etaHist->FillPromptDaughterPhoton(photons->Particle(eta->GetDaughterIndex(0,0)), photons->Particle(eta->GetDaughterIndex(0,1)));
                }
                if(tagger->GetNRand() == 1)
                {
                    //etaHist->FillRandTagger(tagger->GetMissingVector(tagger->GetRandIndex(0)),tagger->GetTagged_t(tagger->GetRandIndex(0)),tagger->GetPhotonBeam_E(tagger->GetRandIndex(0)),tagger->GetTagged_ch(tagger->GetRandIndex(0)));
                    //etaHist->FillRandDaughterMeson(eta->Particle(0));
                    //etaHist->FillRandDaughterPhoton(photons->Particle(eta->GetDaughterIndex(0,0)), photons->Particle(eta->GetDaughterIndex(0,1)));
                }
            }
            else if(etap->GetNParticles() == 1)
            {
                if(tagger->GetNPrompt() == 1)
                {
                    //etapHist->FillPromptTagger(tagger->GetMissingVector(tagger->GetPromptIndex(0)),tagger->GetTagged_t(tagger->GetPromptIndex(0)),tagger->GetPhotonBeam_E(tagger->GetPromptIndex(0)),tagger->GetTagged_ch(tagger->GetPromptIndex(0)));
                    //etapHist->FillPromptDaughterMeson(etap->Particle(0));
                    //etapHist->FillPromptDaughterPhoton(photons->Particle(etap->GetDaughterIndex(0,0)), photons->Particle(etap->GetDaughterIndex(0,1)));
                }
                if(tagger->GetNRand() == 1)
                {
                    //etapHist->FillRandTagger(tagger->GetMissingVector(tagger->GetRandIndex(0)),tagger->GetTagged_t(tagger->GetRandIndex(0)),tagger->GetPhotonBeam_E(tagger->GetRandIndex(0)),tagger->GetTagged_ch(tagger->GetRandIndex(0)));
                    //etapHist->FillRandDaughterMeson(etap->Particle(0));
                    //etapHist->FillRandDaughterPhoton(photons->Particle(etap->GetDaughterIndex(0,0)), photons->Particle(etap->GetDaughterIndex(0,1)));
                }
            }
        }

        else if(photons->GetNParticles() == 6)
        {
            if(etap->GetNParticles() == 1)
            {
                if(tagger->GetNPrompt() == 1)
                {
                    //etapHist->FillPromptTagger(tagger->GetMissingVector(tagger->GetPromptIndex(0)),tagger->GetTagged_t(tagger->GetPromptIndex(0)),tagger->GetPhotonBeam_E(tagger->GetPromptIndex(0)),tagger->GetTagged_ch(tagger->GetPromptIndex(0)));
                    //etapHist->FillPromptMeson(etap->Particle(0));
                    //etapHist->FillPromptDaughterMesons(pi0->Particle(0), pi0->Particle(1), eta->Particle(0));
                    //etapHist->FillPromptDaughterPhotons(0, photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                    //etapHist->FillPromptDaughterPhotons(1, photons->Particle(pi0->GetDaughterIndex(1,0)), photons->Particle(pi0->GetDaughterIndex(1,1)));
                    //etapHist->FillPromptDaughterPhotons(2, photons->Particle(eta->GetDaughterIndex(0,0)), photons->Particle(eta->GetDaughterIndex(0,1)));
                }
                if(tagger->GetNRand() == 1)
                {
                    //etapHist->FillRandTagger(tagger->GetMissingVector(tagger->GetRandIndex(0)),tagger->GetTagged_t(tagger->GetRandIndex(0)),tagger->GetPhotonBeam_E(tagger->GetRandIndex(0)),tagger->GetTagged_ch(tagger->GetRandIndex(0)));
                    //etapHist->FillRandMeson(etap->Particle(0));
                    //etapHist->FillRandDaughterMesons(pi0->Particle(0), pi0->Particle(1), eta->Particle(0));
                    //etapHist->FillRandDaughterPhotons(0, photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                    //etapHist->FillRandDaughterPhotons(1, photons->Particle(pi0->GetDaughterIndex(1,0)), photons->Particle(pi0->GetDaughterIndex(1,1)));
                    //etapHist->FillRandDaughterPhotons(2, photons->Particle(eta->GetDaughterIndex(0,0)), photons->Particle(eta->GetDaughterIndex(0,1)));
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                if(tagger->GetNPrompt() == 1)
                {
                    //etaHist->FillPromptTagger(tagger->GetMissingVector(tagger->GetPromptIndex(0)),tagger->GetTagged_t(tagger->GetPromptIndex(0)),tagger->GetPhotonBeam_E(tagger->GetPromptIndex(0)),tagger->GetTagged_ch(tagger->GetPromptIndex(0)));
                    //etaHist->FillPromptMeson(eta->Particle(0));
                    //etaHist->FillPromptDaughterMesons(pi0->Particle(0), pi0->Particle(1), pi0->Particle(2));
                    //etaHist->FillPromptDaughterPhotons(0, photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                    //etaHist->FillPromptDaughterPhotons(1, photons->Particle(pi0->GetDaughterIndex(1,0)), photons->Particle(pi0->GetDaughterIndex(1,1)));
                    //etaHist->FillPromptDaughterPhotons(2, photons->Particle(pi0->GetDaughterIndex(2,0)), photons->Particle(pi0->GetDaughterIndex(2,1)));
                }
                if(tagger->GetNRand() == 1)
                {
                    //etaHist->FillRandTagger(tagger->GetMissingVector(tagger->GetRandIndex(0)),tagger->GetTagged_t(tagger->GetRandIndex(0)),tagger->GetPhotonBeam_E(tagger->GetRandIndex(0)),tagger->GetTagged_ch(tagger->GetRandIndex(0)));
                    //etaHist->FillRandMeson(eta->Particle(0));
                    //etaHist->FillRandDaughterMesons(pi0->Particle(0), pi0->Particle(1), pi0->Particle(2));
                    //etaHist->FillRandDaughterPhotons(0, photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                    //etaHist->FillRandDaughterPhotons(1, photons->Particle(pi0->GetDaughterIndex(1,0)), photons->Particle(pi0->GetDaughterIndex(1,1)));
                    //etaHist->FillRandDaughterPhotons(2, photons->Particle(pi0->GetDaughterIndex(2,0)), photons->Particle(pi0->GetDaughterIndex(2,1)));
                }
            }
            else    //3pi0
            {
                if(tagger->GetNPrompt() == 1)
                {
                    //_3pi0Hist->FillPromptTagger(tagger->GetMissingVector(tagger->GetPromptIndex(0)),tagger->GetTagged_t(tagger->GetPromptIndex(0)),tagger->GetPhotonBeam_E(tagger->GetPromptIndex(0)),tagger->GetTagged_ch(tagger->GetPromptIndex(0)));
                    //_3pi0Hist->FillPromptMeson(pi0->Particle(0) + pi0->Particle(1) + pi0->Particle(2));
                    //_3pi0Hist->FillPromptDaughterMesons(pi0->Particle(0), pi0->Particle(1), pi0->Particle(2));
                    //_3pi0Hist->FillPromptDaughterPhotons(0, photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                    //_3pi0Hist->FillPromptDaughterPhotons(1, photons->Particle(pi0->GetDaughterIndex(1,0)), photons->Particle(pi0->GetDaughterIndex(1,1)));
                    //_3pi0Hist->FillPromptDaughterPhotons(2, photons->Particle(pi0->GetDaughterIndex(2,0)), photons->Particle(pi0->GetDaughterIndex(2,1)));
                }
                if(tagger->GetNRand() == 1)
                {
                    //_3pi0Hist->FillRandTagger(tagger->GetMissingVector(tagger->GetRandIndex(0)),tagger->GetTagged_t(tagger->GetRandIndex(0)),tagger->GetPhotonBeam_E(tagger->GetRandIndex(0)),tagger->GetTagged_ch(tagger->GetRandIndex(0)));
                    //_3pi0Hist->FillRandMeson(pi0->Particle(0) + pi0->Particle(1) + pi0->Particle(2));
                    //_3pi0Hist->FillRandDaughterMesons(pi0->Particle(0), pi0->Particle(1), pi0->Particle(2));
                    //_3pi0Hist->FillRandDaughterPhotons(0, photons->Particle(pi0->GetDaughterIndex(0,0)), photons->Particle(pi0->GetDaughterIndex(0,1)));
                    //_3pi0Hist->FillRandDaughterPhotons(1, photons->Particle(pi0->GetDaughterIndex(1,0)), photons->Particle(pi0->GetDaughterIndex(1,1)));
                    //_3pi0Hist->FillRandDaughterPhotons(2, photons->Particle(pi0->GetDaughterIndex(2,0)), photons->Particle(pi0->GetDaughterIndex(2,1)));
                }
            }
        }
    }
    else
}

Bool_t  GPlotCut::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenPhotons())    return kFALSE;
    if(!OpenEtap())    return kFALSE;
    if(!OpenEta())    return kFALSE;
    if(!OpenPi0())    return kFALSE;
    if(!OpenTagger())    return kFALSE;

    if(!Create(output_filename))    return kFALSE;

    file_out->cd();
    gDirectory->mkdir("pi0");
    file_out->cd();
    gDirectory->mkdir("eta");
    file_out->cd();
    gDirectory->mkdir("etap");

    file_out->cd();
    //pi0Hist = new GHistTaggedPi0(gDirectory->GetDirectory("pi0"));
    file_out->cd();
    //etaHist = new GHistTaggedEta(gDirectory->GetDirectory("eta"));
    file_out->cd();
    //etapHist = new GHistTaggedEtap(gDirectory->GetDirectory("etap"));

    TraverseEntries(0, pi0->GetNEntries()+1);

    //pi0Hist->Write();
    //etaHist->Write();
    //etapHist->Write();
    /*hist->Write(&taggerTime);
    TH1D    diff(protonAngleDiffPrompt);
    diff.SetNameTitle("protonAngleDiffPromptRandSubst", "Proton Angle Difference Prompt/Rand Substracted");
    diff.Add(&protonAngleDiffRand,-1);
    TH1D    diffNormed(protonAngleDiffPrompt);
    diffNormed.SetNameTitle("protonAngleDiffPromptRandSubstNorm", "Proton Angle Difference Prompt/Rand Substracted Normalised");
    diffNormed.Add(&protonAngleDiffRand,-protonAngleDiffPrompt.GetMaximum()/protonAngleDiffRand.GetMaximum());
    hist->Write(&protonAngleDiffPrompt);
    hist->Write(&protonAngleDiffRand);
    hist->Write(&diff);
    hist->Write(&diffNormed);*/

    return kTRUE;
}


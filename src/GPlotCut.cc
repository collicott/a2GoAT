#include "GPlotCut.h"


using namespace std;


GPlotCut::GPlotCut()
{
    hNoProton.h2g.hPi0  = 0;
    hNoProton.h2g.hEta  = 0;
    hNoProton.h2g.hEtap = 0;
    hNoProton.h6g.hPi0  = 0;
    hNoProton.h6g.hEta  = 0;
    hNoProton.h6g.hEtap = 0;

    hProton.h2g.hPi0  = 0;
    hProton.h2g.hEta  = 0;
    hProton.h2g.hEtap = 0;
    hProton.h6g.hPi0  = 0;
    hProton.h6g.hEta  = 0;
    hProton.h6g.hEtap = 0;
}

GPlotCut::~GPlotCut()
{
}

void    GPlotCut::Init()
{
    file_out->cd();
    gDirectory->mkdir("2g");
    file_out->cd();
    gDirectory->GetDirectory("2g")->cd();
    gDirectory->mkdir("pi0");
    file_out->cd();
    gDirectory->GetDirectory("2g")->cd();
    gDirectory->mkdir("eta");
    file_out->cd();
    gDirectory->GetDirectory("2g")->cd();
    gDirectory->mkdir("etap");
    file_out->cd();
    gDirectory->GetDirectory("2g")->cd();
    hNoProton.h2g.hPi0  = new GHistCut(gDirectory->GetDirectory("pi0"), GHistCut::FLAG_PI0, GHistCut::FLAG_2GAMMA);
    file_out->cd();
    gDirectory->GetDirectory("2g")->cd();
    hNoProton.h2g.hEta  = new GHistCut(gDirectory->GetDirectory("eta"), GHistCut::FLAG_ETA, GHistCut::FLAG_2GAMMA);
    file_out->cd();
    gDirectory->GetDirectory("2g")->cd();
    hNoProton.h2g.hEtap = new GHistCut(gDirectory->GetDirectory("etap"), GHistCut::FLAG_ETAP, GHistCut::FLAG_2GAMMA);

    file_out->cd();
    gDirectory->mkdir("6g");
    file_out->cd();
    gDirectory->GetDirectory("6g")->cd();
    gDirectory->mkdir("pi0");
    file_out->cd();
    gDirectory->GetDirectory("6g")->cd();
    gDirectory->mkdir("eta");
    file_out->cd();
    gDirectory->GetDirectory("6g")->cd();
    gDirectory->mkdir("etap");
    file_out->cd();
    gDirectory->GetDirectory("6g")->cd();
    hNoProton.h6g.hPi0  = new GHistCut(gDirectory->GetDirectory("pi0"), GHistCut::FLAG_PI0, GHistCut::FLAG_6GAMMA);
    file_out->cd();
    gDirectory->GetDirectory("6g")->cd();
    hNoProton.h6g.hEta  = new GHistCut(gDirectory->GetDirectory("eta"), GHistCut::FLAG_ETA, GHistCut::FLAG_6GAMMA);
    file_out->cd();
    gDirectory->GetDirectory("6g")->cd();
    hNoProton.h6g.hEtap = new GHistCut(gDirectory->GetDirectory("etap"), GHistCut::FLAG_ETAP, GHistCut::FLAG_6GAMMA);


    /*hProton.h2gEta      = 0;
    hProton.h2gEtap     = 0;
    hProton.h6gPi0      = 0;
    hProton.h6gEta      = 0;
    hProton.h6gEtap     = 0;

    hNoProton.h2gPi0      = 0;
    hNoProton.h2gEta      = 0;
    hNoProton.h2gEtap     = 0;
    hNoProton.h6gPi0      = 0;
    hNoProton.h6gEta      = 0;
    hNoProton.h6gEtap     = 0;*/
}


void  GPlotCut::ProcessEvent()
{
    if(protons)
    {
    }
    else
    {
        if(photons->GetNParticles() == 2)
        {
            if(pi0->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                    hNoProton.h2g.hPi0->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M(), tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                        hNoProton.h2g.hPi0->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    else
                        hNoProton.h2g.hPi0->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                    hNoProton.h2g.hEta->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, eta->Particle(0).M(), tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                        hNoProton.h2g.hEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, eta->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    else
                        hNoProton.h2g.hEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, eta->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                }
            }
            else if(etap->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                    hNoProton.h2g.hEtap->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, etap->Particle(0).M(), tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                        hNoProton.h2g.hEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, etap->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    else
                        hNoProton.h2g.hEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, etap->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                }
            }
        }

        else if(photons->GetNParticles() == 6)
        {
            if(etap->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                    hNoProton.h6g.hEtap->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M(), pi0->Particle(1).M(), eta->Particle(0).M(), etap->Particle(0).M(), tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                        hNoProton.h6g.hEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M(), pi0->Particle(1).M(), eta->Particle(0).M(), etap->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    else
                        hNoProton.h6g.hEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M(), pi0->Particle(1).M(), eta->Particle(0).M(), etap->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                    hNoProton.h6g.hEta->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M(), pi0->Particle(1).M(), pi0->Particle(2).M(), eta->Particle(0).M(), tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                        hNoProton.h6g.hEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M(), pi0->Particle(1).M(), pi0->Particle(2).M(), eta->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    else
                        hNoProton.h6g.hEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M(), pi0->Particle(1).M(), pi0->Particle(2).M(), eta->Particle(0).M(), tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                }
            }
        }
    }
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

    Init();

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


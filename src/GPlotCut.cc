#include "GPlotCut.h"


using namespace std;


GPlotCut::GPlotCut()
{
    hNoProton.pi0.invMass   = 0;
    hNoProton.pi0.misMass   = 0;
    hNoProton.eta.invMass   = 0;
    hNoProton.eta.misMass   = 0;
    hNoProton.etap.invMass   = 0;
    hNoProton.etap.misMass   = 0;

    hNoProton.eta.h2g.invMass   = 0;
    hNoProton.eta.h2g.misMass   = 0;
    hNoProton.etap.h2g.invMass   = 0;
    hNoProton.etap.h2g.misMass   = 0;

    hNoProton.eta.h6g.invMassEta    = 0;
    hNoProton.eta.h6g.invMassPi0[0] = 0;
    hNoProton.eta.h6g.invMassPi0[1] = 0;
    hNoProton.eta.h6g.invMassPi0[2] = 0;
    hNoProton.eta.h6g.misMass       = 0;
    hNoProton.etap.h6g.invMassEtap   = 0;
    hNoProton.etap.h6g.invMassPi0[0] = 0;
    hNoProton.etap.h6g.invMassPi0[1] = 0;
    hNoProton.etap.h6g.invMassEta    = 0;
    hNoProton.etap.h6g.misMass       = 0;

    hProton.pi0.invMass   = 0;
    hProton.pi0.misMass   = 0;
    hProton.eta.invMass   = 0;
    hProton.eta.misMass   = 0;
    hProton.etap.invMass   = 0;
    hProton.etap.misMass   = 0;

    hProton.eta.h2g.invMass   = 0;
    hProton.eta.h2g.misMass   = 0;
    hProton.etap.h2g.invMass   = 0;
    hProton.etap.h2g.misMass   = 0;

    hProton.eta.h6g.invMassEta    = 0;
    hProton.eta.h6g.invMassPi0[0] = 0;
    hProton.eta.h6g.invMassPi0[1] = 0;
    hProton.eta.h6g.invMassPi0[2] = 0;
    hProton.eta.h6g.misMass       = 0;
    hProton.etap.h6g.invMassEtap   = 0;
    hProton.etap.h6g.invMassPi0[0] = 0;
    hProton.etap.h6g.invMassPi0[1] = 0;
    hProton.etap.h6g.invMassEta    = 0;
    hProton.etap.h6g.misMass       = 0;
}

GPlotCut::~GPlotCut()
{
    if(hNoProton.pi0.invMass)   delete  hNoProton.pi0.invMass;
    if(hNoProton.pi0.misMass)   delete  hNoProton.pi0.misMass;
    if(hNoProton.eta.invMass)   delete  hNoProton.eta.invMass;
    if(hNoProton.eta.misMass)   delete  hNoProton.eta.misMass;
    if(hNoProton.etap.invMass)   delete  hNoProton.etap.invMass;
    if(hNoProton.etap.misMass)   delete  hNoProton.etap.misMass;

    if(hNoProton.eta.h2g.invMass)   delete  hNoProton.eta.h2g.invMass;
    if(hNoProton.eta.h2g.misMass)   delete  hNoProton.eta.h2g.misMass;
    if(hNoProton.etap.h2g.invMass)   delete  hNoProton.etap.h2g.invMass;
    if(hNoProton.etap.h2g.misMass)   delete  hNoProton.etap.h2g.misMass;

    if(hNoProton.eta.h6g.invMassEta)   delete  hNoProton.eta.h6g.invMassEta;
    if(hNoProton.eta.h6g.invMassPi0[0])   delete  hNoProton.eta.h6g.invMassPi0[0];
    if(hNoProton.eta.h6g.invMassPi0[1])   delete  hNoProton.eta.h6g.invMassPi0[1];
    if(hNoProton.eta.h6g.invMassPi0[2])   delete  hNoProton.eta.h6g.invMassPi0[2];
    if(hNoProton.eta.h6g.misMass)   delete  hNoProton.eta.h6g.misMass;
    if(hNoProton.etap.h6g.invMassEtap)   delete  hNoProton.etap.h6g.invMassEtap;
    if(hNoProton.etap.h6g.invMassPi0[0])   delete  hNoProton.etap.h6g.invMassPi0[0];
    if(hNoProton.etap.h6g.invMassPi0[1])   delete  hNoProton.etap.h6g.invMassPi0[1];
    if(hNoProton.etap.h6g.invMassEta)   delete  hNoProton.etap.h6g.invMassEta;
    if(hNoProton.etap.h6g.misMass)   delete  hNoProton.etap.h6g.misMass;

    if(hProton.pi0.invMass)   delete  hProton.pi0.invMass;
    if(hProton.pi0.misMass)   delete  hProton.pi0.misMass;
    if(hProton.eta.invMass)   delete  hProton.eta.invMass;
    if(hProton.eta.misMass)   delete  hProton.eta.misMass;
    if(hProton.etap.invMass)   delete  hProton.etap.invMass;
    if(hProton.etap.misMass)   delete  hProton.etap.misMass;

    if(hProton.eta.h2g.invMass)   delete  hProton.eta.h2g.invMass;
    if(hProton.eta.h2g.misMass)   delete  hProton.eta.h2g.misMass;
    if(hProton.etap.h2g.invMass)   delete  hProton.etap.h2g.invMass;
    if(hProton.etap.h2g.misMass)   delete  hProton.etap.h2g.misMass;

    if(hProton.eta.h6g.invMassEta)   delete  hProton.eta.h6g.invMassEta;
    if(hProton.eta.h6g.invMassPi0[0])   delete  hProton.eta.h6g.invMassPi0[0];
    if(hProton.eta.h6g.invMassPi0[1])   delete  hProton.eta.h6g.invMassPi0[1];
    if(hProton.eta.h6g.invMassPi0[2])   delete  hProton.eta.h6g.invMassPi0[2];
    if(hProton.eta.h6g.misMass)   delete  hProton.eta.h6g.misMass;
    if(hProton.etap.h6g.invMassEtap)   delete  hProton.etap.h6g.invMassEtap;
    if(hProton.etap.h6g.invMassPi0[0])   delete  hProton.etap.h6g.invMassPi0[0];
    if(hProton.etap.h6g.invMassPi0[1])   delete  hProton.etap.h6g.invMassPi0[1];
    if(hProton.etap.h6g.invMassEta)   delete  hProton.etap.h6g.invMassEta;
    if(hProton.etap.h6g.misMass)   delete  hProton.etap.h6g.misMass;
}

void    GPlotCut::Init()
{
    file_out->cd();
    gDirectory->mkdir("NoProton");

    file_out->GetDirectory("NoProton")->cd();
    gDirectory->mkdir("pi0");

    file_out->GetDirectory("NoProton")->cd();
    gDirectory->mkdir("eta");
    file_out->GetDirectory("NoProton")->GetDirectory("eta")->cd();
    gDirectory->mkdir("h2g");
    file_out->GetDirectory("NoProton")->GetDirectory("eta")->cd();
    gDirectory->mkdir("h6g");

    file_out->GetDirectory("NoProton")->cd();
    gDirectory->mkdir("etap");
    file_out->GetDirectory("NoProton")->GetDirectory("etap")->cd();
    gDirectory->mkdir("h2g");
    file_out->GetDirectory("NoProton")->GetDirectory("etap")->cd();
    gDirectory->mkdir("h6g");

    file_out->cd();
    gDirectory->mkdir("Proton");

    file_out->GetDirectory("Proton")->cd();
    gDirectory->mkdir("pi0");

    file_out->GetDirectory("Proton")->cd();
    gDirectory->mkdir("eta");
    file_out->GetDirectory("Proton")->GetDirectory("eta")->cd();
    gDirectory->mkdir("h2g");
    file_out->GetDirectory("Proton")->GetDirectory("eta")->cd();
    gDirectory->mkdir("h6g");

    file_out->GetDirectory("Proton")->cd();
    gDirectory->mkdir("etap");
    file_out->GetDirectory("Proton")->GetDirectory("etap")->cd();
    gDirectory->mkdir("h2g");
    file_out->GetDirectory("Proton")->GetDirectory("etap")->cd();
    gDirectory->mkdir("h6g");

    hNoProton.pi0.invMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("pi0"), TString("pi0_invMass"), TString("pi0_invMass"), 2000, 0, 2000);
    hNoProton.pi0.misMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("pi0"), TString("pi0_misMass"), TString("pi0_misMass"), 2000, 0, 2000);

    hNoProton.eta.invMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta"), TString("eta_invMass"), TString("eta_invMass"), 2000, 0, 2000);
    hNoProton.eta.misMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta"), TString("eta_misMass"), TString("eta_misMass"), 2000, 0, 2000);
    hNoProton.eta.h2g.invMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta")->GetDirectory("h2g"), TString("eta_2g_invMass"), TString("eta_2g_invMass"), 2000, 0, 2000);
    hNoProton.eta.h2g.misMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta")->GetDirectory("h2g"), TString("eta_2g_misMass"), TString("eta_2g_misMass"), 2000, 0, 2000);
    hNoProton.eta.h6g.invMassEta   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_invMass"), TString("eta_6g_invMass"), 2000, 0, 2000);
    hNoProton.eta.h6g.invMassPi0[0]= new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_pi0a_invMass"), TString("eta_6g_pi0a_invMass"), 2000, 0, 2000);
    hNoProton.eta.h6g.invMassPi0[1]= new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_pi0b_invMass"), TString("eta_6g_pi0b_invMass"), 2000, 0, 2000);
    hNoProton.eta.h6g.invMassPi0[2]= new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_pi0c_invMass"), TString("eta_6g_pi0c_invMass"), 2000, 0, 2000);
    hNoProton.eta.h6g.misMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_misMass"), TString("eta_6g_misMass"), 2000, 0, 2000);

    hNoProton.etap.invMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap"), TString("etap_p_invMass"), TString("etap_p_invMass"), 2000, 0, 2000);
    hNoProton.etap.misMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap"), TString("etap_p_misMass"), TString("etap_p_misMass"), 2000, 0, 2000);
    hNoProton.etap.h2g.invMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap")->GetDirectory("h2g"), TString("etap_2gp_invMass"), TString("etap_2gp_invMass"), 2000, 0, 2000);
    hNoProton.etap.h2g.misMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap")->GetDirectory("h2g"), TString("etap_2gp_misMass"), TString("etap_2gp_misMass"), 2000, 0, 2000);
    hNoProton.etap.h6g.invMassEtap = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_invMass"), TString("etap_6gp_invMass"), 2000, 0, 2000);
    hNoProton.etap.h6g.invMassPi0[0]= new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_pi0a_invMass"), TString("etap_6gp_pi0a_invMass"), 2000, 0, 2000);
    hNoProton.etap.h6g.invMassPi0[1]= new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_pi0b_invMass"), TString("etap_6gp_pi0b_invMass"), 2000, 0, 2000);
    hNoProton.etap.h6g.invMassEta   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_eta_invMass"), TString("etap_6gp_eta_invMass"), 2000, 0, 2000);
    hNoProton.etap.h6g.misMass   = new GHistD(file_out->GetDirectory("NoProton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_misMass"), TString("etap_6gp_misMass"), 2000, 0, 2000);



    hProton.pi0.invMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("pi0"), TString("pi0_invMass"), TString("pi0_invMass"), 2000, 0, 2000);
    hProton.pi0.misMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("pi0"), TString("pi0_misMass"), TString("pi0_misMass"), 2000, 0, 2000);

    hProton.eta.invMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta"), TString("eta_invMass"), TString("eta_invMass"), 2000, 0, 2000);
    hProton.eta.misMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta"), TString("eta_misMass"), TString("eta_misMass"), 2000, 0, 2000);
    hProton.eta.h2g.invMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta")->GetDirectory("h2g"), TString("eta_2g_invMass"), TString("eta_2g_invMass"), 2000, 0, 2000);
    hProton.eta.h2g.misMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta")->GetDirectory("h2g"), TString("eta_2g_misMass"), TString("eta_2g_misMass"), 2000, 0, 2000);
    hProton.eta.h6g.invMassEta   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_invMass"), TString("eta_6g_invMass"), 2000, 0, 2000);
    hProton.eta.h6g.invMassPi0[0]= new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_pi0a_invMass"), TString("eta_6g_pi0a_invMass"), 2000, 0, 2000);
    hProton.eta.h6g.invMassPi0[1]= new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_pi0b_invMass"), TString("eta_6g_pi0b_invMass"), 2000, 0, 2000);
    hProton.eta.h6g.invMassPi0[2]= new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_pi0c_invMass"), TString("eta_6g_pi0c_invMass"), 2000, 0, 2000);
    hProton.eta.h6g.misMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("eta")->GetDirectory("h6g"), TString("eta_6g_misMass"), TString("eta_6g_misMass"), 2000, 0, 2000);

    hProton.etap.invMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap"), TString("etap_p_invMass"), TString("etap_p_invMass"), 2000, 0, 2000);
    hProton.etap.misMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap"), TString("etap_p_misMass"), TString("etap_p_misMass"), 2000, 0, 2000);
    hProton.etap.h2g.invMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap")->GetDirectory("h2g"), TString("etap_2gp_invMass"), TString("etap_2gp_invMass"), 2000, 0, 2000);
    hProton.etap.h2g.misMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap")->GetDirectory("h2g"), TString("etap_2gp_misMass"), TString("etap_2gp_misMass"), 2000, 0, 2000);
    hProton.etap.h6g.invMassEtap = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_invMass"), TString("etap_6gp_invMass"), 2000, 0, 2000);
    hProton.etap.h6g.invMassPi0[0]= new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_pi0a_invMass"), TString("etap_6gp_pi0a_invMass"), 2000, 0, 2000);
    hProton.etap.h6g.invMassPi0[1]= new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_pi0b_invMass"), TString("etap_6gp_pi0b_invMass"), 2000, 0, 2000);
    hProton.etap.h6g.invMassEta   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_eta_invMass"), TString("etap_6gp_eta_invMass"), 2000, 0, 2000);
    hProton.etap.h6g.misMass   = new GHistD(file_out->GetDirectory("Proton")->GetDirectory("etap")->GetDirectory("h6g"), TString("etap_6gp_misMass"), TString("etap_6gp_misMass"), 2000, 0, 2000);

    file_out->cd();
}


void  GPlotCut::ProcessEvent()
{
    if(protons)
    {
        if(photons->GetNParticles() == 2)
        {
            if(pi0->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hProton.pi0.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M());
                    hProton.pi0.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hProton.pi0.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M());
                        hProton.pi0.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hProton.pi0.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M());
                        hProton.pi0.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hProton.eta.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, eta->Particle(0).M());
                    hProton.eta.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hProton.eta.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, eta->Particle(0).M());
                        hProton.eta.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hProton.eta.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, eta->Particle(0).M());
                        hProton.eta.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
            else if(etap->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hProton.etap.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, etap->Particle(0).M());
                    hProton.etap.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hProton.etap.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, etap->Particle(0).M());
                        hProton.etap.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hProton.etap.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, etap->Particle(0).M());
                        hProton.etap.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
        }

        else if(photons->GetNParticles() == 6)
        {
            if(etap->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hProton.etap.h6g.invMassEtap->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, etap->Particle(0).M());
                    hProton.etap.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M());
                    hProton.etap.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(1).M());
                    hProton.etap.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, eta->Particle(0).M());
                    hProton.etap.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hProton.etap.h6g.invMassEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, etap->Particle(0).M());
                        hProton.etap.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M());
                        hProton.etap.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(1).M());
                        hProton.etap.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, eta->Particle(0).M());
                        hProton.etap.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hProton.etap.h6g.invMassEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, etap->Particle(0).M());
                        hProton.etap.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M());
                        hProton.etap.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(1).M());
                        hProton.etap.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, eta->Particle(0).M());
                        hProton.etap.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hProton.eta.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, eta->Particle(0).M());
                    hProton.eta.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M());
                    hProton.eta.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(1).M());
                    hProton.eta.h6g.invMassPi0[2]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(2).M());
                    hProton.eta.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hProton.eta.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, eta->Particle(0).M());
                        hProton.eta.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M());
                        hProton.eta.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(1).M());
                        hProton.eta.h6g.invMassPi0[2]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(2).M());
                        hProton.eta.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hProton.eta.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, eta->Particle(0).M());
                        hProton.eta.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M());
                        hProton.eta.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(1).M());
                        hProton.eta.h6g.invMassPi0[2]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(2).M());
                        hProton.eta.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
        }
    }
    else
    {
        if(photons->GetNParticles() == 2)
        {
            if(pi0->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hNoProton.pi0.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M());
                    hNoProton.pi0.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hNoProton.pi0.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M());
                        hNoProton.pi0.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hNoProton.pi0.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M());
                        hNoProton.pi0.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hNoProton.eta.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, eta->Particle(0).M());
                    hNoProton.eta.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hNoProton.eta.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, eta->Particle(0).M());
                        hNoProton.eta.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hNoProton.eta.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, eta->Particle(0).M());
                        hNoProton.eta.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
            else if(etap->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hNoProton.etap.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, etap->Particle(0).M());
                    hNoProton.etap.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hNoProton.etap.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, etap->Particle(0).M());
                        hNoProton.etap.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hNoProton.etap.h2g.invMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, etap->Particle(0).M());
                        hNoProton.etap.h2g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
        }

        else if(photons->GetNParticles() == 6)
        {
            if(etap->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hNoProton.etap.h6g.invMassEtap->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, etap->Particle(0).M());
                    hNoProton.etap.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M());
                    hNoProton.etap.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(1).M());
                    hNoProton.etap.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, eta->Particle(0).M());
                    hNoProton.etap.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hNoProton.etap.h6g.invMassEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, etap->Particle(0).M());
                        hNoProton.etap.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M());
                        hNoProton.etap.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(1).M());
                        hNoProton.etap.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, eta->Particle(0).M());
                        hNoProton.etap.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hNoProton.etap.h6g.invMassEtap->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, etap->Particle(0).M());
                        hNoProton.etap.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M());
                        hNoProton.etap.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(1).M());
                        hNoProton.etap.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, eta->Particle(0).M());
                        hNoProton.etap.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                }
            }
            else if(eta->GetNParticles() == 1)
            {
                for(int i=0; i<tagger->GetNPrompt(); i++)
                {
                    hNoProton.eta.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, eta->Particle(0).M());
                    hNoProton.eta.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(0).M());
                    hNoProton.eta.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(1).M());
                    hNoProton.eta.h6g.invMassPi0[2]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, pi0->Particle(2).M());
                    hNoProton.eta.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, tagger->GetMissingVector(tagger->GetPromptIndex(i)).M());
                }
                for(int i=0; i<tagger->GetNRand(); i++)
                {
                    if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
                    {
                        hNoProton.eta.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, eta->Particle(0).M());
                        hNoProton.eta.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(0).M());
                        hNoProton.eta.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(1).M());
                        hNoProton.eta.h6g.invMassPi0[2]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, pi0->Particle(2).M());
                        hNoProton.eta.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
                    else
                    {
                        hNoProton.eta.h6g.invMassEta->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, eta->Particle(0).M());
                        hNoProton.eta.h6g.invMassPi0[0]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(0).M());
                        hNoProton.eta.h6g.invMassPi0[1]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(1).M());
                        hNoProton.eta.h6g.invMassPi0[2]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, pi0->Particle(2).M());
                        hNoProton.eta.h6g.misMass->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, tagger->GetMissingVector(tagger->GetRandIndex(i)).M());
                    }
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

    hNoProton.pi0.invMass->Write(0.01);
    hNoProton.pi0.misMass->Write(0.01);
    hNoProton.eta.h2g.invMass->Write(0.01);
    hNoProton.eta.h2g.misMass->Write(0.01);
    hNoProton.eta.invMass->Add(hNoProton.eta.h2g.invMass, 1);
    hNoProton.eta.misMass->Add(hNoProton.eta.h2g.misMass, 1);
    hNoProton.etap.h2g.invMass->Write(0.01);
    hNoProton.etap.h2g.misMass->Write(0.01);
    hNoProton.etap.invMass->Add(hNoProton.etap.h2g.invMass, 1);
    hNoProton.etap.misMass->Add(hNoProton.etap.h2g.misMass, 1);

    hNoProton.eta.h6g.invMassEta->Write(0.01);
    hNoProton.eta.h6g.invMassPi0[0]->Write(0.01);
    hNoProton.eta.h6g.invMassPi0[1]->Write(0.01);
    hNoProton.eta.h6g.invMassPi0[2]->Write(0.01);
    hNoProton.eta.h6g.misMass->Write(0.01);
    hNoProton.eta.invMass->Add(hNoProton.eta.h6g.invMassEta, 1);
    hNoProton.eta.misMass->Add(hNoProton.eta.h6g.misMass, 1);
    hNoProton.eta.invMass->Write(0.01);
    hNoProton.eta.misMass->Write(0.01);
    hNoProton.etap.h6g.invMassEtap->Write(0.01);
    hNoProton.etap.h6g.invMassPi0[0]->Write(0.01);
    hNoProton.etap.h6g.invMassPi0[1]->Write(0.01);
    hNoProton.etap.h6g.invMassEta->Write(0.01);
    hNoProton.etap.h6g.misMass->Write(0.01);
    hNoProton.etap.invMass->Add(hNoProton.etap.h6g.invMassEtap, 1);
    hNoProton.etap.misMass->Add(hNoProton.etap.h6g.misMass, 1);
    hNoProton.etap.invMass->Write(0.01);
    hNoProton.etap.misMass->Write(0.01);

    hProton.pi0.invMass->Write(0.01);
    hProton.pi0.misMass->Write(0.01);
    hProton.eta.h2g.invMass->Write(0.01);
    hProton.eta.h2g.misMass->Write(0.01);
    hProton.eta.invMass->Add(hProton.eta.h2g.invMass, 1);
    hProton.eta.misMass->Add(hProton.eta.h2g.misMass, 1);
    hProton.etap.h2g.invMass->Write(0.01);
    hProton.etap.h2g.misMass->Write(0.01);
    hProton.etap.invMass->Add(hProton.etap.h2g.invMass, 1);
    hProton.etap.misMass->Add(hProton.etap.h2g.misMass, 1);

    hProton.eta.h6g.invMassEta->Write(0.01);
    hProton.eta.h6g.invMassPi0[0]->Write(0.01);
    hProton.eta.h6g.invMassPi0[1]->Write(0.01);
    hProton.eta.h6g.invMassPi0[2]->Write(0.01);
    hProton.eta.h6g.misMass->Write(0.01);
    hProton.eta.invMass->Add(hProton.eta.h6g.invMassEta, 1);
    hProton.eta.misMass->Add(hProton.eta.h6g.misMass, 1);
    hProton.eta.invMass->Write(0.01);
    hProton.eta.misMass->Write(0.01);
    hProton.etap.h6g.invMassEtap->Write(0.01);
    hProton.etap.h6g.invMassPi0[0]->Write(0.01);
    hProton.etap.h6g.invMassPi0[1]->Write(0.01);
    hProton.etap.h6g.invMassEta->Write(0.01);
    hProton.etap.h6g.misMass->Write(0.01);
    hProton.etap.invMass->Add(hProton.etap.h6g.invMassEtap, 1);
    hProton.etap.misMass->Add(hProton.etap.h6g.misMass, 1);
    hProton.etap.invMass->Write(0.01);
    hProton.etap.misMass->Write(0.01);

    return kTRUE;
}


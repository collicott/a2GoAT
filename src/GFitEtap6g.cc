#include "GFitEtap6g.h"


using namespace std;


GFitEtap6g::GFitEtap6g()	:
	ConfidenceLevel(0),
    ChiSq(0),
    fit(6, 3, 0)
{
	for(int i=0; i<24; i++)
		Pull[i]	= 0;
}

GFitEtap6g::~GFitEtap6g()
{
	if(ConfidenceLevel)	delete ConfidenceLevel;
	if(ChiSq)			delete ChiSq;
	for(int i=0; i<24; i++)
	{
		if(Pull[i])		delete Pull[i];
	}
}

void  GFitEtap6g::ProcessEvent()
{
	if(photons->GetNParticles()!=6)
		return;
	
	GKinFitterParticle	pho[6];
	
    Int_t Ebin  = 0;
    Int_t Thbin = 0;
    Float_t resth = 0;
    Float_t resph = 0;
    Float_t resE  = 0;

	fit.Reset();
	for(int i=0; i<6; i++)
	{
        Ebin  = GammaEloss->GetXaxis()->FindFixBin(photons->Particle(i).E());
        Thbin = GammaEloss->GetYaxis()->FindFixBin(photons->Particle(i).Theta()*TMath::RadToDeg());
        // Get resolutions
        resth = GammaThetaRes->GetBinContent(Ebin, Thbin);
        resph = GammaPhiRes->GetBinContent(Ebin, Thbin);
        resE  = GammaERes->GetBinContent(Ebin, Thbin);
        if(resth==0 || resph==0 || resE==0 ) return; // If energy or angle is out of calibrated  range!
        // Now set particle parameters
        //                     LorentzVector
		pho[i].Set4Vector(photons->Particle(i));
        std::cout << "Res: " << resth << ", " << resph << ", " << photons->Particle(i).E()*resE << std::endl;
        pho[i].SetResolutions(resth, resph, 2 *photons->Particle(i).E()*resE);
		fit.AddPosKFParticle(pho[i]);
	}
	Int_t	sub[6];
	sub[0]	= pi0->GetDaughterIndex(0, 0);
	sub[1]	= pi0->GetDaughterIndex(0, 1);
	fit.AddSubInvMassConstraint(2, sub, MASS_PI0);
	sub[0]	= pi0->GetDaughterIndex(1, 0);
	sub[1]	= pi0->GetDaughterIndex(1, 1);
	fit.AddSubInvMassConstraint(2, sub, MASS_PI0);
	sub[0]	= eta->GetDaughterIndex(0, 0);
	sub[1]	= eta->GetDaughterIndex(0, 1);
    fit.AddSubInvMassConstraint(2, sub, MASS_ETA);
	//fit.AddInvMassConstraint(MASS_ETAP);
	
	if(fit.Solve()<0)
		return;
	
	fitData->SetConfidenceLevel(fit.ConfidenceLevel());
	ConfidenceLevel->Fill(fit.ConfidenceLevel());
	//printf("%lf\n", fit.ConfidenceLevel());
	ChiSq->Fill(fit.GetChi2());
	fitData->SetChiSq(fit.GetChi2());
	for(int i=0; i<24; i++)
	{
		Pull[i]->Fill(fit.Pull(i));
		fitData->SetPull(i, fit.Pull(i));
	}
	fitData->AddParticle(fit.GetTotalFitParticle().Get4Vector());
	
	/*for(int i=0; i<6; i++)
		sub[i]	= photons->GetDaughterIndex(i);
	photons->Clear();
	for(int i=0; i<6; i++)
		photons->AddParticle(fit.GetParticle(i).Get4Vector(), sub[i]);
	
	Int_t   daughter_pdg[3];
    daughter_pdg[0] = 22;
    daughter_pdg[1] = 22;
    Int_t   daughter_index0[3];
    Int_t   daughter_index1[2];
    daughter_index0[0] = pi0->GetDaughterIndex(0, 0);
    daughter_index0[1] = pi0->GetDaughterIndex(0, 1);
    daughter_index1[0] = pi0->GetDaughterIndex(1, 0);
    daughter_index1[1] = pi0->GetDaughterIndex(1, 1);
    pi0->Clear();
	pi0->AddParticle(photons->Particle(daughter_index0[0]) + photons->Particle(daughter_index0[1]), 2, daughter_pdg, daughter_index0);
	pi0->AddParticle(photons->Particle(daughter_index1[0]) + photons->Particle(daughter_index1[1]), 2, daughter_pdg, daughter_index1);
		
    daughter_index0[0] = eta->GetDaughterIndex(0, 0);
    daughter_index0[1] = eta->GetDaughterIndex(0, 1);
    eta->Clear();
	eta->AddParticle(photons->Particle(daughter_index0[0]) + photons->Particle(daughter_index0[1]), 2, daughter_pdg, daughter_index0);
	
    daughter_pdg[0] = 221;
    daughter_pdg[1] = 111;
    daughter_pdg[2] = 111;
    daughter_index0[0] = 0;
    daughter_index0[1] = 0;
    daughter_index0[2] = 1;
    //etap->Clear();    
	//etap->AddParticle(fit.GetTotalFitParticle().Get4Vector(), 3, daughter_pdg, daughter_index0);
    */
    //if(fit.ConfidenceLevel()<0.8 || fit.ConfidenceLevel()>1)
		//return;
    //if(fit.GetChi2()<0.33 || fit.GetChi2()>3)
		//return;
    
    eventFlags->Fill();
    tagger->Fill();
    trigger->Fill();
    photons->Fill();
    protons->Fill();
    pi0->Fill();
    eta->Fill();
    etap->Fill();
    fitData->Fill();
}

Bool_t  GFitEtap6g::Process()
{
    scalers->Clone();

    GammaResFile   = new TFile("~/GammaRes.root");
    GammaEloss     = (TH2F*)GammaResFile->Get("Eloss");
    GammaERes      = (TH2F*)GammaResFile->Get("EResIter");
    GammaThetaRes  = (TH2F*)GammaResFile->Get("ThetaRes;1");
    GammaPhiRes    = (TH2F*)GammaResFile->Get("PhiRes;1");

	ConfidenceLevel	= new TH1D("ConfidenceLevel", "ConfidenceLevel", 1000, 0, 1);
	ChiSq			= new TH1D("ChiSq", "ChiSq", 1000, 0, 100);
	char	str[10];
	for(int i=0; i<24; i++)
	{
		sprintf(str, "pull%d", i);
		Pull[i]		= new TH1D(str, str, 2000, -100, 100);
	}

    TraverseEntries(0, photons->GetNEntries()+1);

    Write(ConfidenceLevel);
    Write(ChiSq);
    for(int i=0; i<24; i++)
		Write(Pull[i]);
		
    return kTRUE;
}


#include "GFitEtap6g.h"


using namespace std;


GFitEtap6g::GFitEtap6g()	:
	ConfidenceLevel(0),
    ChiSq(0),
    fit(6, 4, 0)
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
	
	fit.Reset();
	for(int i=0; i<6; i++)
	{
		pho[i].Set4Vector(photons->Particle(i));
		pho[i].SetResolutions(3, 3, 60);
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
	fit.AddInvMassConstraint(MASS_ETAP);
	
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

Bool_t  GFitEtap6g::Process(const char* input_filename, const char* output_filename)
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
    if(!CreateFitData())    return kFALSE;
    if(!CreateEtap())    return kFALSE;
    if(!CreateEta())    return kFALSE;
    if(!CreatePi0())    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;
    if(!CreateTagger())    return kFALSE;
    if(!CreateTrigger())    return kFALSE;
    if(!CreateEventFlags())    return kFALSE;
    scalers->Clone(*file_out);

	ConfidenceLevel	= new TH1D("ConfidenceLevel", "ConfidenceLevel", 1000, 0, 1);
	ChiSq			= new TH1D("ChiSq", "ChiSq", 1000, 0, 100);
	char	str[10];
	for(int i=0; i<24; i++)
	{
		sprintf(str, "pull%d", i);
		Pull[i]		= new TH1D(str, str, 2000, -100, 100);
	}

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;

    Write(ConfidenceLevel);
    Write(ChiSq);
    for(int i=0; i<24; i++)
		Write(Pull[i]);
		
    return kTRUE;
}


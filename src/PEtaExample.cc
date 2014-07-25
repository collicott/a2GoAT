#include "PEtaExample.h"



PEtaExample::PEtaExample() 
{ 
}

PEtaExample::~PEtaExample()
{
}

Bool_t	PEtaExample::Init(const char* configfile)
{
	// Set by user in the future...
	SetTarget(938);
	
	Double_t Prompt_low 	=  -20;
	Double_t Prompt_high 	=   15;
	Double_t Random_low1 	= -100;
	Double_t Random_high1 	=  -40;
	Double_t Random_low2 	=   35;
	Double_t Random_high2 	=   95;
	
	SetPromptWindow(Prompt_low, Prompt_high);
	SetRandomWindow1(Random_low1, Random_high1);
	SetRandomWindow2(Random_low2, Random_high2);
	SetPvRratio();

	return kTRUE;
}

Bool_t	PEtaExample::Start()
{
    if(!IsGoATFile())
    {
        cout << "ERROR: Input File is not a GoAT file." << endl;
        return kFALSE;
    }
    SetAsPhysicsFile();

	DefineHistograms();

    TraverseValidEvents();
			
    PostReconstruction();
    WriteHistograms();
	return kTRUE;
}

void	PEtaExample::ProcessEvent()
{
	FillTimePDG(*eta,time_eta);
    MissingMassPDG(*eta, MM_prompt_eta, MM_random_eta);

    for (Int_t i = 0; i < eta->GetNParticles(); i++)
	{
		// Count total pi0s
        N_eta++;
		
        // All sub particles are photons (completely neutral)
        if(eta->GetNSubParticles(i) == eta->GetNSubPhotons(i))
        {
            FillMissingMass(*eta, i, MM_prompt_eta_n, MM_random_eta_n);

            //2 photon decay
            if(eta->GetNSubPhotons(i) == 2) FillMissingMass(*eta, i, MM_prompt_eta_n_2g, MM_random_eta_n_2g);

            //6 photon decay
            if(eta->GetNSubPhotons(i) == 6) FillMissingMass(*eta, i, MM_prompt_eta_n_6g, MM_random_eta_n_6g);
        }
        // else, eta is charged
        else
        {
            FillMissingMass(*eta, i, MM_prompt_eta_c, MM_random_eta_c);
            if(eta->GetNSubParticles(i) == 4)  FillMissingMass(*eta, i, MM_prompt_eta_c_4d, MM_random_eta_c_4d);
        }


	}

}

void  PEtaExample::PostReconstruction()
{
	cout << "Performing post reconstruction." << endl;

	RandomSubtraction(MM_prompt_eta,MM_random_eta, MM_eta);		
	
	RandomSubtraction(MM_prompt_eta_n,MM_random_eta_n, MM_eta_n);	
	RandomSubtraction(MM_prompt_eta_n_2g,MM_random_eta_n_2g, MM_eta_n_2g);	
	RandomSubtraction(MM_prompt_eta_n_6g,MM_random_eta_n_6g, MM_eta_n_6g);

	RandomSubtraction(MM_prompt_eta_c,MM_random_eta_c, MM_eta_c);	
	RandomSubtraction(MM_prompt_eta_c_4d,MM_random_eta_c_4d, MM_eta_c_4d);	
	
	ShowTimeCuts(time_eta, time_eta_cuts);

}

void	PEtaExample::DefineHistograms()
{
	gROOT->cd();
	
	time_eta		= new TH1D("time_eta",		"time_eta",		1000,-500,500);
	time_eta_cuts	= new TH1D("time_eta_cuts",	"time_eta_cuts",1000,-500,500);

	MM_prompt_eta 	= new TH1D("MM_prompt_eta",	"MM_prompt_eta",1500,0,1500);
	MM_random_eta 	= new TH1D("MM_random_eta",	"MM_random_eta",1500,0,1500);
	MM_eta			= new TH1D("MM_eta",		"MM_eta",		1500,0,1500);
	
	MM_prompt_eta_n = new TH1D("MM_prompt_eta_n","MM_prompt_eta_n",1500,0,1500);
	MM_random_eta_n = new TH1D("MM_random_eta_n","MM_random_eta_n",1500,0,1500);
	MM_eta_n		= new TH1D("MM_eta_n",		 "MM_eta_n",	   1500,0,1500);

	MM_prompt_eta_n_6g = new TH1D("MM_prompt_eta_n_6g","MM_prompt_eta_n_6g",1500,0,1500);
	MM_random_eta_n_6g = new TH1D("MM_random_eta_n_6g","MM_random_eta_n_6g",1500,0,1500);
	MM_eta_n_6g		  = new TH1D("MM_eta_n_6g",		 "MM_eta_n_6g",	   1500,0,1500);	

	MM_prompt_eta_n_2g = new TH1D("MM_prompt_eta_n_2g","MM_prompt_eta_n_2g",1500,0,1500);
	MM_random_eta_n_2g = new TH1D("MM_random_eta_n_2g","MM_random_eta_n_2g",1500,0,1500);
	MM_eta_n_2g		  = new TH1D("MM_eta_n_2g",		 "MM_eta_n_2g",	   1500,0,1500);	
	
	MM_prompt_eta_c = new TH1D("MM_prompt_eta_c","MM_prompt_eta_c",1500,0,1500);
	MM_random_eta_c = new TH1D("MM_random_eta_c","MM_random_eta_c",1500,0,1500);
	MM_eta_c		= new TH1D("MM_eta_c",		 "MM_eta_c",	   1500,0,1500);
	
	MM_prompt_eta_c_4d = new TH1D("MM_prompt_eta_c_4d","MM_prompt_eta_c_4d",1500,0,1500);
	MM_random_eta_c_4d = new TH1D("MM_random_eta_c_4d","MM_random_eta_c_4d",1500,0,1500);
	MM_eta_c_4d		= new TH1D("MM_eta_c_4d",		 "MM_eta_c_4d",	   1500,0,1500);	
}

Bool_t 	PEtaExample::WriteHistograms(TFile* pfile)
{
	cout << "Writing histograms." << endl;
		
	if(!pfile) return kFALSE;
	pfile->cd();

	gROOT->GetList()->Write();
	gROOT->GetList()->Delete();
		
	return kTRUE;
}

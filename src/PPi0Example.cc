#include "PPi0Example.h"



PPi0Example::PPi0Example() 
{ 
}

PPi0Example::~PPi0Example()
{
}

Bool_t	PPi0Example::Init(const char* configfile)
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

Bool_t	PPi0Example::Start()
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

void	PPi0Example::ProcessEvent()
{
	// Fill timing histogram (all PDG matching pi0)
    FillTimePDG(*pi0,time_pi0);
	
	// Fill missing mass (all PDG matching pi0)
    MissingMassPDG(*pi0, MM_prompt_pi0, MM_random_pi0);

	// Some neutral decays
    for (Int_t i = 0; i < pi0->GetNParticles(); i++)
	{
		// Count total pi0s
        N_pi0++;
		
        // Fill MM for 2 photon decay
        if ((pi0->GetNSubParticles(i) == 2) & (pi0->GetNSubPhotons(i) == 2))
        {
            FillMissingMass(*pi0, i, MM_prompt_pi0_n_2g, MM_random_pi0_n_2g);
        }

	}
}

void  PPi0Example::PostReconstruction()
{
	cout << "Performing post reconstruction." << endl;

	RandomSubtraction(MM_prompt_pi0,MM_random_pi0, MM_pi0);		
	RandomSubtraction(MM_prompt_pi0_n_2g,MM_random_pi0_n_2g, MM_pi0_n_2g);	
		
	ShowTimeCuts(time_pi0, time_pi0_cuts);

}

void	PPi0Example::DefineHistograms()
{
    gROOT->cd();

	time_pi0		= new TH1D("time_pi0",		"time_pi0",		1000,-500,500);
	time_pi0_cuts	= new TH1D("time_pi0_cuts",	"time_pi0_cuts",1000,-500,500);

	MM_prompt_pi0 	= new TH1D("MM_prompt_pi0",	"MM_prompt_pi0",1500,0,1500);
	MM_random_pi0 	= new TH1D("MM_random_pi0",	"MM_random_pi0",1500,0,1500);
	MM_pi0			= new TH1D("MM_pi0",		"MM_pi0",		1500,0,1500);
	
	MM_prompt_pi0_n_2g = new TH1D("MM_prompt_pi0_n_2g",	"MM_prompt_pi0_n_2g",1500,0,1500);
	MM_random_pi0_n_2g = new TH1D("MM_random_pi0_n_2g",	"MM_random_pi0_n_2g",1500,0,1500);
	MM_pi0_n_2g		  = new TH1D("MM_pi0_n_2g",		 	"MM_pi0_n_2g",	   	 1500,0,1500);		
}

Bool_t 	PPi0Example::WriteHistograms(TFile* pfile)
{
	cout << "Writing histograms." << endl;
    gROOT->cd();

    if(!file_out) return kFALSE;
    file_out->cd();

    gROOT->GetList()->Write();
    gROOT->GetList()->Delete();
		
	return kTRUE;
}


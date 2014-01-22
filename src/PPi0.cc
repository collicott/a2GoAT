#ifndef __CINT__

#include "PPi0.h"

int main(int argc, char *argv[])
{
	
	clock_t start, end;
	start = clock();

	// Associate 1st terminal input with config file
	Char_t* configfile;
	if(argv[1]) configfile = argv[1];
	else 
	{
		cout << "Please provide a config file" << endl;
		return 0;
	}
	
	// Check that file exists:
	ifstream ifile(configfile);
	if(!ifile)
	{
		cout << "Config file " << configfile << " could not be found." << endl;
		return 0;
	}	
	
	// Create instance of PPi0 class
	PPi0* ppi0 = new PPi0;

	// Perform full initialisation 
	if(!ppi0->Init(configfile)){
		cout << "ERROR: GoAT Init failed!" << endl;
		return 0;
	}
	
	ppi0->Analyse();
	
	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

	return 0;
}

PPi0::PPi0() 
{ 
}

PPi0::~PPi0()
{
}

Bool_t	PPi0::Init(Char_t* configfile)
{

	OpenGoATFile("AnalysisFiles/Pi0_GoAT_Compton_354.root", "READ");
	OpenPhysFile("AnalysisFiles/Pi0_PhysicsHistograms.root");
//	DefineHistograms();

	cout << "Setting up tree files:" << endl;
	if(!InitPhysicsTree(PhysFile)) 		return kFALSE;
	if(!OpenTreeParticles(GoATFile)) 	return kFALSE;
	if(!OpenTreeTagger(GoATFile))		return kFALSE;
	cout << endl;

	cout << "Detmining valid for analysis:" << endl;	
	if(!FindValidGoATEvents())			return kFALSE;	

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

void	PPi0::Analyse()
{
	cout << "Analysing ..." << endl;
	TraverseGoATEntries();
	
//	PostReconstruction();		
//	WriteHistograms();
	ClosePhysFile();	
}



void	PPi0::Reconstruct()
{
	if(GetGoATEvent() % 100000 == 0) printf("Event: %d\n",GetGoATEvent());

//	MissingMassPDG(1, MM_prompt_pi0, MM_random_pi0);
//	MissingMassPDG(2, MM_prompt_eta, MM_random_eta);

	for (Int_t i = 0; i < GoATTree_GetNParticles(); i++)
	{
		if (GoATTree_GetPDG(i) == 1) 
		{
			FillMissingMass(i, MM_prompt_pi0, MM_random_pi0);
			
			for (Int_t j = 0; j < GoATTree_GetNParticles(); j++)
			{		
				if (GoATTree_GetPDG(j) == 4) 
					FillMissingMass(i, MM_prompt_pi0_p, MM_random_pi0_p);
			}
		}
	}

	FillTimePDG(1,time_pi0);
	
}

void  PPi0::PostReconstruction()
{
/*	RandomSubtraction(MM_prompt_pi0,MM_random_pi0, MM_pi0);		
	RandomSubtraction(MM_prompt_pi0_p,MM_random_pi0_p, MM_pi0_p);	

	ShowTimeCuts(time_pi0, time_pi0_cuts);*/

}

Bool_t  PPi0::InitPhysicsTree(TFile* F)
{
	if(!F) return kFALSE;
	F->cd();
	
	treePhysics = new TTree("treePhysics", "treePhysics");
	if(!treePhysics) return kFALSE;
	cout << "treePhysics created." << endl;
	
	treePhysics->Branch("nentries",	&nentries,	"nentries/I");
	treePhysics->Branch("TC",		TC,			"TC[nentries]/I");
	treePhysics->Branch("E",		E,			"E[nentries]/D");	
	treePhysics->Branch("time",		time,		"time[nentries]/D");	
	treePhysics->Branch("theta",	theta,		"theta[nentries]/D");
	treePhysics->Branch("thetaCM",	thetaCM,	"thetaCM[nentries]/D");
	treePhysics->Branch("phi",		phi,		"phi[nentries]/D");
	treePhysics->Branch("phiCM",	phiCM,		"phiCM[nentries]/D");
	treePhysics->Branch("MissMass",	MissMass,	"MissMass[nentries]/D");
	treePhysics->Branch("MissE",	MissE,		"MissE[nentries]/D");
		
	return kTRUE;
}

void	PPi0::DefineHistograms()
{
/*	time_pi0		= new TH1D("time_pi0",		"time_pi0",		1000,-500,500);
	time_pi0_cuts	= new TH1D("time_pi0_cuts",	"time_pi0_cuts",1000,-500,500);

	MM_prompt_pi0 	= new TH1D("MM_prompt_pi0",	"MM_prompt_pi0",1500,0,1500);
	MM_random_pi0 	= new TH1D("MM_random_pi0",	"MM_random_pi0",1500,0,1500);
	MM_pi0			= new TH1D("MM_pi0",		"MM_pi0",		1500,0,1500);
	*/
}

Bool_t 	PPi0::WriteHistograms(TFile* pfile)
{
/*	if(!pfile) return kFALSE;
	pfile->cd();

	time_pi0->Write();
	time_pi0_cuts->Write();	
			
	MM_prompt_pi0->Write();
	MM_random_pi0->Write();
	MM_pi0->Write();
*/
	return kTRUE;
}

#endif

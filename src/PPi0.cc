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

	OpenGoATFile("/home/cristina/GoAT_Compton_354.root", "READ");
	OpenPhysFile("/home/cristina/Pi0_Compton_354.root");
	DefineHistograms();

	cout << "Setting up tree files:" << endl;
	if(!OpenTreeParticles(GoATFile)) 	return kFALSE;
	if(!OpenTreeTagger(GoATFile))		return kFALSE;
	cout << endl;

	cout << "Detmining valid for analysis:" << endl;	
	if(!FindValidGoATEvents())			return kFALSE;	

	// Set by user in the future...
	SetTarget(938);
	SetPromptWindow(-20, 20);
	SetRandomWindow1(-100,-40);
	SetRandomWindow1(40,100);
	SetPvRratio();

	return kTRUE;
}

void	PPi0::Analyse()
{
	cout << "Analysing ..." << endl;
	TraverseGoATEntries();
	
	RandomSubtraction(MM_prompt_pi0,MM_random_pi0, MM_pi0);		
	RandomSubtraction(MM_prompt_eta,MM_random_eta, MM_eta);		
		
	WriteHistograms();
	ClosePhysFile();	
}

void	PPi0::Reconstruct()
{
	if(GetGoATEvent() % 10000 == 0) printf("Event: %d\n",GetGoATEvent());

	MissingMass(1, MM_prompt_pi0, MM_random_pi0);
	MissingMass(2, MM_prompt_eta, MM_random_eta);

}

void	PPi0::DefineHistograms()
{

	MM_prompt_pi0 	= new TH1D("MM_prompt_pi0",	"MM_prompt_pi0",1500,0,1500);
	MM_random_pi0 	= new TH1D("MM_random_pi0",	"MM_random_pi0",1500,0,1500);
	MM_pi0			= new TH1D("MM_pi0",		"MM_pi0",		1500,0,1500);
	
	MM_prompt_eta 	= new TH1D("MM_prompt_eta",	"MM_prompt_eta",1500,0,1500);
	MM_random_eta 	= new TH1D("MM_random_eta",	"MM_random_eta",1500,0,1500);
	MM_eta			= new TH1D("MM_eta",		"MM_eta",		1500,0,1500);	
}

Bool_t 	PPi0::WriteHistograms(TFile* pfile)
{
	if(!pfile) return kFALSE;
	pfile->cd();
		
	MM_prompt_pi0->Write();
	MM_random_pi0->Write();
	MM_pi0->Write();
	
	MM_prompt_eta->Write();
	MM_random_eta->Write();
	MM_eta->Write();
	
	return kTRUE;
}

#endif

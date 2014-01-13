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

	cout << "Setting up tree files:" << endl;
	if(!OpenTreeParticles(GoATFile)) 	return kFALSE;
	if(!OpenTreeTagger(GoATFile))		return kFALSE;
	if(!OpenTreeTrigger(GoATFile))		return kFALSE;
	cout << endl;

	cout << "Detmining valid for analysis:" << endl;	
	if(!FindValidGoATEvents())		return kFALSE;	

	// Set by user in the future...
	targetmass = 938; 
	target 	= TLorentzVector(0.,0.,0.,targetmass);

	Prompt_low 		=  -20.0;
	Prompt_high 	=   20.0; 
	Random_low1   	= -100.0; 
	Random_high1  	=  -40.0;
	Random_low2   	=   40.0; 
	Random_high2  	=  100.0;
	
	PvR_ratio = (Prompt_high - Prompt_low)
		/((Random_high1 - Random_low1) + (Random_high2 - Random_low2));
		
	return kTRUE;
}

void	PPi0::Analyse()
{
	MM_prompt 	= new TH1D("MM_prompt",	"MM_prompt",1500,0,1500);
	MM_random 	= new TH1D("MM_random",	"MM_random",1500,0,1500);
	MM			= new TH1D("MM",		"MM",		1500,0,1500);
	
	cout << "Analysing ..." << endl;
	TraverseGoATEntries();	

	TFile *HistFile = new TFile("Hist_Compton_354.root", "RECREATE");
	
	MM->Add(MM_prompt,1);
	MM->Add(MM_random,-PvR_ratio);

	MM_prompt->Write();
	MM_random->Write();
	MM->Write();
	HistFile->Close();



}

void	PPi0::Reconstruct()
{
	
	// Calculate pi0 missing mass (current pdg_pi0 = 1 .. fix later)
	MissingMass(1);
	
	
}

void PPi0::MissingMass(Int_t pdg)
{
	for (Int_t i = 0; i < GoATTree_GetNParticles(); i++)
	{
		if (GoATTree_GetPDG(i) != pdg) continue; 
		
		// Get particle four vector
		particle = GetGoATVector(i);
		
		for (Int_t j = 0; j < GetNTagged(); j++)
		{

			if (!IsPrompt(GetTagged_t(j)) && !IsRandom(GetTagged_t(j))) continue;
			
			beam 	= TLorentzVector(0.,0.,GetPhotonBeam_E(j),GetPhotonBeam_E(j));
			missingp4 = beam + target - particle;


			if (IsPrompt(GetTagged_t(j))) MM_prompt->Fill(missingp4.M());
			if (IsRandom(GetTagged_t(j))) MM_random->Fill(missingp4.M());			

		}
	}
}	

Bool_t PPi0::IsPrompt(Double_t time)
{
	if ((time >= Prompt_low) && (time <= Prompt_high)) return kTRUE;
	
	return kFALSE;
}
	
Bool_t PPi0::IsRandom(Double_t time)
{

	if ((time >= Random_low1) && (time <= Random_high1)) return kTRUE;
	if ((time >= Random_low2) && (time <= Random_high2)) return kTRUE;
	
	return kFALSE;
}

Bool_t 	PPi0::Write()
{
	return kTRUE;
}

#endif

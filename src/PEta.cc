#ifndef __CINT__

#include "PEta.h"

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
	
	// Create instance of PEta class
	PEta* peta = new PEta;

	// Perform full initialisation 
	if(!peta->Init(configfile)){
		cout << "ERROR: GoAT Init failed!" << endl;
		return 0;
	}
	
	peta->Analyse();
	
	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

	return 0;
}

PEta::PEta() 
{ 
}

PEta::~PEta()
{
}

Bool_t	PEta::Init(Char_t* configfile)
{

	OpenGoATFile("/home/cristina/Open_GoAT_Compton_354.root", "READ");
	OpenPhysFile("Eta_PhysicsHistograms.root");
	DefineHistograms();

	cout << "Setting up tree files:" << endl;
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

void	PEta::Analyse()
{
	N_eta	= 0;
	N_5omn  = 0;
	N_3oln	= 0;
	N_6g 	= 0;
	N_2g 	= 0;
	N_2piX = 0;
	N_other = 0;

	cout << "Analysing ..." << endl;
	TraverseGoATEntries();
	
	PostReconstruction();		
	WriteHistograms();
	ClosePhysFile();	

	Double_t BR;
	
	cout << "Output branching ratios ---------------- " << endl << endl;
	cout << "Total Eta found: "<< N_eta << endl;

	Double_t BR_scale = 40.0/((double(N_2g)/double(N_eta))*100);

	BR = (double(N_2g)/double(N_eta))*100;

	cout << "BR (eta -> 2g)         " << BR << "%       " << (BR*BR_scale) << "% " <<endl;

	BR = (double(N_3oln)/double(N_eta))*100;
	cout << "BR (eta -> 3-g)        " << BR << "%       " << (BR*BR_scale) << "% " <<endl;
	
	BR = (double(N_6g)/double(N_eta))*100;
	cout << "BR (eta -> 6g)         " << BR << "%       " << (BR*BR_scale) << "% " <<endl;
	
	BR = (double(N_5omn)/double(N_eta))*100;
	cout << "BR (eta -> 5+g)        " << BR << "%       " << (BR*BR_scale) << "% " <<endl;

	BR = (double(N_2piX)/double(N_eta))*100;
	cout << "BR (eta -> pi+pi-X)    " << BR << "%       " << (BR*BR_scale) << "% " <<endl;
	

}

void	PEta::Reconstruct()
{
	if(GetGoATEvent() % 100000 == 0) printf("Event: %d  Total Etas found: %d \n",GetGoATEvent(), N_eta);

	FillTimePDG(2,time_eta);
	MissingMassPDG(2, MM_prompt_eta, MM_random_eta);

	// Some neutral decays
	for (Int_t i = 0; i < GoATTree_GetNParticles(); i++)
	{
		if(GoATTree_GetPDG(i) != 2) 	continue; // not eta -> ignore
		if(GoATTree_GetCharge(i) != 0) 	continue; // charged -> ignore

		FillMissingMass(i, MM_prompt_eta_n, MM_random_eta_n);
		if (GoATTree_GetNDaughters(i) == 2) FillMissingMass(i, MM_prompt_eta_n_2g, MM_random_eta_n_2g);
		if (GoATTree_GetNDaughters(i) == 6) FillMissingMass(i, MM_prompt_eta_n_6g, MM_random_eta_n_6g);
		if (GoATTree_GetNDaughters(i) <= 3) FillMissingMass(i, MM_prompt_eta_n_3ol, MM_random_eta_n_3ol);
		if (GoATTree_GetNDaughters(i) >= 5) FillMissingMass(i, MM_prompt_eta_n_5om, MM_random_eta_n_5om);
		
	}

	// Some charged decays
	for (Int_t i = 0; i < GoATTree_GetNParticles(); i++)
	{
		if(GoATTree_GetPDG(i) != 2) 	continue; // not eta -> ignore	
		if(GoATTree_GetCharge(i) == 0) 	continue; // neutral -> ignore

		FillMissingMass(i, MM_prompt_eta_c, MM_random_eta_c);

		if (GoATTree_GetNDaughters(i) != 4) continue; // only look at 4 daughters

		FillMissingMass(i, MM_prompt_eta_c_4d, MM_random_eta_c_4d);
		
		if(GoATTree_GetCharge(i) != 2) 	continue; // neutral -> ignore

		Int_t nchpi = 0; Int_t ngamm = 0;
		for (Int_t j = 0; j < GoATTree_GetNDaughterList(); j++)
		{

			if(GoATTree_GetDaughter_Index(j) != i) continue; // not a daughter of this eta
			
			if(GoATTree_GetDaughter_PDG(j) == 5) 		nchpi++;
			else if(GoATTree_GetDaughter_PDG(j) == 7) 	ngamm++;
		}
	
		if ((nchpi == 2) && (ngamm == 2)) 
		FillMissingMass(i, MM_prompt_eta_c_4d_2pi2g, MM_random_eta_c_4d_2pi2g);
		
	}	
	
	
	// Branching ratios?
	// Some charged decays
	for (Int_t i = 0; i < GoATTree_GetNParticles(); i++)
	{
		if(GoATTree_GetPDG(i) != 2) 	continue; // not eta -> ignore	

		Int_t nchpi = 0; 
		Int_t ngamm = 0;
		Int_t nroot = 0;
		Int_t nelec = 0;

		N_eta++;

		for (Int_t j = 0; j < GoATTree_GetNDaughterList(); j++)
		{
			if(GoATTree_GetDaughter_Index(j) != i) continue; // not a daughter of this eta

			if(GoATTree_GetDaughter_PDG(j) == 0) 		nroot++;
			else if(GoATTree_GetDaughter_PDG(j) == 5) 	nchpi++;
			else if(GoATTree_GetDaughter_PDG(j) == 6) 	nelec++;
			else if(GoATTree_GetDaughter_PDG(j) == 7) 	ngamm++;
			
			else cout << "wait a minute..." << endl;
		}
		
		if(GoATTree_GetCharge(i) == 0)
		{
			if ((GoATTree_GetNDaughters(i) == 6) && (ngamm == 6)) 	N_6g++;
			if ((GoATTree_GetNDaughters(i) == 2) && (ngamm == 2)) 	N_2g++;
			if (GoATTree_GetNDaughters(i) <= 3) 					N_3oln++;			
			if (GoATTree_GetNDaughters(i) >= 5) 					N_5omn++;	
		}
		
		else if(GoATTree_GetCharge(i) == 2)
		{
			if ((nchpi == 2)) 	N_2piX++;
		}		
			
	}	

}

void  PEta::PostReconstruction()
{
	RandomSubtraction(MM_prompt_eta,MM_random_eta, MM_eta);		
	
	RandomSubtraction(MM_prompt_eta_n,MM_random_eta_n, MM_eta_n);	
	RandomSubtraction(MM_prompt_eta_n_2g,MM_random_eta_n_2g, MM_eta_n_2g);	
	RandomSubtraction(MM_prompt_eta_n_6g,MM_random_eta_n_6g, MM_eta_n_6g);

	RandomSubtraction(MM_prompt_eta_n_3ol,MM_random_eta_n_3ol, MM_eta_n_3ol);
	RandomSubtraction(MM_prompt_eta_n_5om,MM_random_eta_n_5om, MM_eta_n_5om);

	RandomSubtraction(MM_prompt_eta_c,MM_random_eta_c, MM_eta_c);	
	RandomSubtraction(MM_prompt_eta_c_4d,MM_random_eta_c_4d, MM_eta_c_4d);	
	RandomSubtraction(MM_prompt_eta_c_4d_2pi2g,MM_random_eta_c_4d_2pi2g, MM_eta_c_4d_2pi2g);	
	
	ShowTimeCuts(time_eta, time_eta_cuts);

}

void	PEta::DefineHistograms()
{
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

	MM_prompt_eta_n_3ol = new TH1D("MM_prompt_eta_n_3ol","MM_prompt_eta_n_3ol",1500,0,1500);
	MM_random_eta_n_3ol = new TH1D("MM_random_eta_n_3ol","MM_random_eta_n_3ol",1500,0,1500);
	MM_eta_n_3ol		  = new TH1D("MM_eta_n_3ol",	 "MM_eta_n_3ol",	   1500,0,1500);	

	MM_prompt_eta_n_5om = new TH1D("MM_prompt_eta_n_5om","MM_prompt_eta_n_5om",1500,0,1500);
	MM_random_eta_n_5om = new TH1D("MM_prompt_eta_n_5om","MM_prompt_eta_n_5om",1500,0,1500);
	MM_eta_n_5om		  = new TH1D("MM_prompt_eta_n_5om",	 "MM_prompt_eta_n_5om",	   1500,0,1500);	
	
	MM_prompt_eta_c = new TH1D("MM_prompt_eta_c","MM_prompt_eta_c",1500,0,1500);
	MM_random_eta_c = new TH1D("MM_random_eta_c","MM_random_eta_c",1500,0,1500);
	MM_eta_c		= new TH1D("MM_eta_c",		 "MM_eta_c",	   1500,0,1500);
	
	MM_prompt_eta_c_4d = new TH1D("MM_prompt_eta_c_4d","MM_prompt_eta_c_4d",1500,0,1500);
	MM_random_eta_c_4d = new TH1D("MM_random_eta_c_4d","MM_random_eta_c_4d",1500,0,1500);
	MM_eta_c_4d		= new TH1D("MM_eta_c_4d",		 "MM_eta_c_4d",	   1500,0,1500);	

	MM_prompt_eta_c_4d_2pi2g = new TH1D("MM_prompt_eta_c_4d_2pi2g","MM_prompt_eta_c_4d_2pi2g",1500,0,1500);
	MM_random_eta_c_4d_2pi2g = new TH1D("MM_random_eta_c_4d_2pi2g","MM_random_eta_c_4d_2pi2g",1500,0,1500);
	MM_eta_c_4d_2pi2g		= new TH1D("MM_eta_c_4d_2pi2g",		 "MM_eta_c_4d_2pi2g",	   1500,0,1500);	
}

Bool_t 	PEta::WriteHistograms(TFile* pfile)
{
	if(!pfile) return kFALSE;
	pfile->cd();

	time_eta->Write();
	time_eta_cuts->Write();	
			
//	MM_prompt_eta->Write();
//	MM_random_eta->Write();
	MM_eta->Write();

//	MM_prompt_eta_n->Write();
//	MM_random_eta_n->Write();
	MM_eta_n->Write();

//	MM_prompt_eta_n_6g->Write();
//	MM_random_eta_n_6g->Write();
	MM_eta_n_6g->Write();
	
//	MM_prompt_eta_n_2g->Write();
//	MM_random_eta_n_2g->Write();
	MM_eta_n_2g->Write();	

//	MM_prompt_eta_n_3ol->Write();
//	MM_random_eta_n_3ol->Write();
	MM_eta_n_3ol->Write();	
	
//	MM_prompt_eta_n_5om->Write();
//	MM_random_eta_n_5om->Write();
	MM_eta_n_5om->Write();		
	
//	MM_prompt_eta_c->Write();
//	MM_random_eta_c->Write();
	MM_eta_c->Write();

//	MM_prompt_eta_c_4d->Write();
//	MM_random_eta_c_4d->Write();
	MM_eta_c_4d->Write();

//	MM_prompt_eta_c_4d_2pi2g->Write();
//	MM_random_eta_c_4d_2pi2g->Write();
	MM_eta_c_4d_2pi2g->Write();	
	
	
	return kTRUE;
}

#endif

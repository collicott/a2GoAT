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
	if(!ppi0->Init(configfile, 	"AnalysisFiles/Pi0_Compton_354.root",
								"AnalysisFiles/Pi0_Tree.root",
								"AnalysisFiles/Pi0_Hist.root"))
	{
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

PPi0::PPi0() :
			nentries(0),
			TC(0),
			E(0),
			time(0),
			theta(0),
			phi(0),
			MissMass(0),
			MissE(0)
{ 

	TC 		= new Int_t[maxentries];
	E		= new Double_t[maxentries];
	time	= new Double_t[maxentries];
	theta	= new Double_t[maxentries];
	phi		= new Double_t[maxentries];
	MissMass= new Double_t[maxentries];
	MissE	= new Double_t[maxentries];
}

PPi0::~PPi0()
{
}

Bool_t	PPi0::Init(Char_t* configfile, Char_t* gfile, Char_t* tfile, Char_t* hfile)
{
	// Set by user in the future...
	SetTarget(938);
	
	Double_t Prompt_low 	=  -20;
	Double_t Prompt_high 	=   15;
	Double_t Random_low1 	= -450;
	Double_t Random_high1 	=  -50;
	Double_t Random_low2 	=   50;
	Double_t Random_high2 	=  500;
	
	SetPromptWindow( Prompt_low,  Prompt_high);
	SetRandomWindow1(Random_low1, Random_high1);
	SetRandomWindow2(Random_low2, Random_high2);
	SetPvRratio();	
	
	MMCut_low 		= 900;
	MMCut_high 		= 1000;
	theta_bin_size 	= 20;
	phi_bin_size 	= 20;
	
	ReconstructPhysicsTree = kTRUE;
	FillHistograms = kTRUE;
	
	if(ReconstructPhysicsTree == kTRUE)
	{
		OpenGoATFile(gfile, "READ");
		OpenPhysTreeFile(tfile, "RECREATE");

		cout << "Setting up tree files:" << endl;
		if(!InitPhysicsTree(PhysTreeFile)) 	return kFALSE;
		if(!OpenTreeParticles(GoATFile)) 	return kFALSE;
		if(!OpenTreeTagger(GoATFile))		return kFALSE;
		cout << endl;

		cout << "Detmining valid for analysis:" << endl;	
		if(!FindValidGoATEvents())			return kFALSE;	

	}

	if(FillHistograms == kTRUE)
	{
		if(ReconstructPhysicsTree == kFALSE)
		{
			if(!OpenPhysTreeFile(tfile, "READ")) return kFALSE;
		}
		
		OpenHistFile(hfile,"RECREATE");
		InitHistograms();
	}
	
	return kTRUE;
}

void	PPi0::Analyse()
{
	if(ReconstructPhysicsTree == kTRUE)
	{	
		cout << "Analysing ..." << endl;
		TraverseGoATEntries();
		WriteTrees();
	}

	if(FillHistograms == kTRUE)
	{	

		if(!OpenPhysicsTree()) cout << "whoops" << endl;
		PostReconstruction();		
		WriteHistograms();
		CloseHistFile();
	}
	
	if((ReconstructPhysicsTree == kTRUE) || (FillHistograms == kTRUE))
	{
		ClosePhysTreeFile();
	}
		
}

void	PPi0::Reconstruct()
{
	if(GetGoATEvent() % 100000 == 0) printf("Event: %d\n",GetGoATEvent());

	nentries = 0;
	for (Int_t i = 0; i < GoATTree_GetNParticles(); i++)
	{
		if (GoATTree_GetPDG(i) != 1) continue;
		if (GoATTree_GetCharge(i) != 0) continue;
		if (GoATTree_GetNDaughters(i) != 2) continue;

		for (Int_t j = 0; j < GetNTagged(); j++)
		{
			TC[nentries] 		= GetTagged_ch(j);
			E[nentries] 		= GetPhotonBeam_E(j);
			time[nentries]		= GetTagged_t(j) - GoATTree_GetTime(i);
			theta[nentries]		= GoATTree_GetTheta(i);
			phi[nentries]		= GoATTree_GetPhi(i);
			MissMass[nentries] 	= CalcMissingMass(i,j);
			MissE[nentries]	 	= CalcMissingEnergy(i,j);
			nentries++;
		}
	}

	treePhysics->Fill();

}

void  PPi0::PostReconstruction()
{
	Int_t N = (Int_t)treePhysics->GetEntries();
	for (Int_t i=0;i<N;i++) {

		treePhysics->GetEntry(i);

		for (Int_t j = 0; j < nentries; j ++)
		{
			time_pi0->Fill(time[j]);
			
			Prompt = IsPrompt(time[j]); 
			Random = IsRandom(time[j]);
			
			if ((!Prompt) && (!Random)) continue;
			if (Prompt) 
			{
				// Fill 1D histograms
				TC_prompt->Fill(TC[j]);
				E_prompt->Fill(E[j]);
				theta_prompt->Fill(theta[j]);
				phi_prompt->Fill(phi[j]);
				MM_prompt_pi0->Fill(MissMass[j]);
				ME_prompt_pi0->Fill(MissE[j]);	
				
				// Fill 3D histograms according to cuts
				if((MissMass[j] >= MMCut_low) && (MissMass[j] <= MMCut_high))
				{
					TC_theta_phi_prompt->Fill(TC[j], theta[j], phi[j]);
				}
				
			}
			if (Random)
			{
				// Fill 1D histograms
				TC_random->Fill(TC[j]);
				E_random->Fill(E[j]);
				theta_random->Fill(theta[j]);
				phi_random->Fill(phi[j]);
				MM_random_pi0->Fill(MissMass[j]);
				ME_random_pi0->Fill(MissE[j]);	
				
				// Fill 3D histograms according to cuts
				if((MissMass[j] >= MMCut_low) && (MissMass[j] <= MMCut_high))
				{
					TC_theta_phi_random->Fill(TC[j], theta[j], phi[j]);
				}
			}
		}
	}

	RandomSubtraction(TC_prompt,TC_random, TC_sub);		
	RandomSubtraction(E_prompt,E_random, E_sub);		
	RandomSubtraction(theta_prompt,theta_random, theta_sub);		
	RandomSubtraction(phi_prompt,phi_random, phi_sub);		
	RandomSubtraction(MM_prompt_pi0,MM_random_pi0, MM_sub_pi0);		
	RandomSubtraction(ME_prompt_pi0,ME_random_pi0, ME_sub_pi0);		

	ShowTimeCuts(time_pi0, time_pi0_cuts);

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
	treePhysics->Branch("phi",		phi,		"phi[nentries]/D");
	treePhysics->Branch("MissMass",	MissMass,	"MissMass[nentries]/D");
	treePhysics->Branch("MissE",	MissE,		"MissE[nentries]/D");
		
	return kTRUE;
}

Bool_t  PPi0::OpenPhysicsTree(TFile* F)
{
	if(!F) {cout << "1" << endl;return kFALSE; }
	
	treePhysics = (TTree*)F->Get("treePhysics");
	if(!treePhysics) {cout << "2" << endl;return kFALSE; }
	cout << "treePhysics opened." << endl;
	
	treePhysics->SetBranchAddress("nentries",	&nentries);
	treePhysics->SetBranchAddress("TC",			TC);
	treePhysics->SetBranchAddress("E",			E);	
	treePhysics->SetBranchAddress("time",		time);	
	treePhysics->SetBranchAddress("theta",		theta);
	treePhysics->SetBranchAddress("phi",		phi);
	treePhysics->SetBranchAddress("MissMass",	MissMass);
	treePhysics->SetBranchAddress("MissE",		MissE);
		
	return kTRUE;
}

Bool_t  PPi0::WriteTrees(TFile* F)
{
	if(!F) return kFALSE;
	F->cd();
	
	if(treePhysics)				treePhysics->Write();
	
	return kTRUE;
}

void	PPi0::InitHistograms()
{

	// 1-D histograms

	time_pi0		= new TH1D("time_pi0",		"time_pi0",		1200,-600,600);
	time_pi0_cuts	= new TH1D("time_pi0_cuts",	"time_pi0_cuts",1200,-600,600);

	TC_prompt 		= new TH1D("TC_prompt",		"TC_prompt",	352,0,352);
	TC_random 		= new TH1D("TC_random",		"TC_random",	352,0,352);
	TC_sub			= new TH1D("TC subtracted",	"TC subtracted",352,0,352);	

	TC_prompt->Sumw2(); 
	TC_random->Sumw2();
	TC_sub->Sumw2();

	E_prompt 		= new TH1D("E_prompt",		"E_prompt",		1600,0,1600);
	E_random 		= new TH1D("E_random",		"E_random",		1600,0,1600);
	E_sub			= new TH1D("E subtracted",	"E subtracted",	1600,0,1600);

	E_prompt->Sumw2(); 
	E_random->Sumw2();
	E_sub->Sumw2();
	
	theta_prompt 	= new TH1D("theta_prompt",		"theta_prompt",		180,0,180);	
	theta_random 	= new TH1D("theta_random",		"theta_random",		180,0,180);
	theta_sub		= new TH1D("theta_subtracted",	"theta_subtracted",	180,0,180);
	
	theta_prompt->Sumw2(); 
	theta_random->Sumw2();
	theta_sub->Sumw2();	
	
	phi_prompt 		= new TH1D("phi_prompt",		"phi_prompt",		360,-180,180);
	phi_random 		= new TH1D("phi_random",		"phi_random",		360,-180,180);
	phi_sub				= new TH1D("phi_subtracted","phi_subtracted",	360,-180,180);	

	phi_prompt->Sumw2(); 
	phi_random->Sumw2();
	phi_sub->Sumw2();	

	MM_prompt_pi0 	= new TH1D("MM_prompt_pi0",		"MM_prompt_pi0",	1500,0,1500); 
	MM_random_pi0 	= new TH1D("MM_random_pi0",		"MM_random_pi0",	1500,0,1500); 
	MM_sub_pi0		= new TH1D("MM_subtracted_pi0",	"MM_subtracted_pi0",1500,0,1500); 

	MM_prompt_pi0->Sumw2(); 
	MM_random_pi0->Sumw2();
	MM_sub_pi0->Sumw2();

	ME_prompt_pi0 	= new TH1D("ME_prompt_pi0",		"ME_prompt_pi0",	1500,0,1500); 
	ME_random_pi0 	= new TH1D("ME_random_pi0",		"ME_random_pi0",	1500,0,1500); 
	ME_sub_pi0		= new TH1D("ME_subtracted_pi0",	"ME_subtracted_pi0",1500,0,1500); 

	ME_prompt_pi0->Sumw2(); 
	ME_random_pi0->Sumw2();
	ME_sub_pi0->Sumw2();


	// 3D histograms (for analysis)
	Int_t theta_bins = int(180/theta_bin_size) + 1;
	Double_t max_theta = (theta_bins)*theta_bin_size;

	Int_t phi_bins 	 = int(360/phi_bin_size) + 1;
	Double_t max_phi = (phi_bins)*phi_bin_size;	


	TC_theta_phi_prompt	= new TH3D("TC_theta_phi_prompt","TC_theta_phi_prompt",	352,0,352, theta_bins,0,max_theta, 	phi_bins,-180,max_phi);
	TC_theta_phi_random = new TH3D("TC_theta_phi_random","TC_theta_phi_random",	352,0,352, theta_bins,0,max_theta, 	phi_bins,-180,max_phi);

	TC_theta_phi_prompt->Sumw2(); 
	TC_theta_phi_random->Sumw2();

/*	E_theta_phi_prompt = new TH3D("E_theta_phi_prompt","E_theta_phi_prompt", 160,0,1600 	 theta_bins,0,180, 	phi_bins,-180,180);
	E_theta_phi_random = new TH3D("E_theta_phi_random","E_theta_phi_random", 160,0,1600, 	 theta_bins,0,180, 	phi_bins,-180,180);

	E_theta_phi_prompt->Sumw2(); 
	E_theta_phi_random->Sumw2();*/
}

Bool_t 	PPi0::WriteHistograms(TFile* hfile)
{
	if(!hfile) return kFALSE;
	hfile->cd();

	time_pi0->Write();
	time_pi0_cuts->Write();	

	TC_prompt->Write(); 
	TC_random->Write();
	TC_sub->Write();

	E_prompt->Write(); 
	E_random->Write();
	E_sub->Write();
	
	theta_prompt->Write(); 
	theta_random->Write();
	theta_sub->Write();		
	
	phi_prompt->Write(); 
	phi_random->Write();
	phi_sub->Write();	
	
	MM_prompt_pi0->Write();
	MM_random_pi0->Write();
	MM_sub_pi0->Write(); 
	
	ME_prompt_pi0->Write(); 
	ME_random_pi0->Write();
	ME_sub_pi0->Write();

	TC_theta_phi_prompt->Write(); 
	TC_theta_phi_random->Write();  
		
	return kTRUE;
}

Bool_t	PPi0::OpenPhysTreeFile(const char* tfile, Option_t* option)
{
	PhysTreeFile = new TFile(tfile, option);
	if(!PhysTreeFile) return kFALSE;
    if(PhysTreeFile->IsZombie()) return kFALSE;
    
	cout << "PhysTreeFile " << tfile << " opened (option = "<< option << ")." << endl;
	
	return kTRUE;
}

Bool_t 	PPi0::ClosePhysTreeFile()
{
	if(!PhysTreeFile) return kFALSE;
	PhysTreeFile->Close();
	
	return kTRUE;
}

#endif

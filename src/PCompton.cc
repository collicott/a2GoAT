#ifndef __CINT__

#include "PCompton.h"

int main(int argc, char *argv[])
{
	clock_t start, end;
	start = clock();

	// Initialise strings
	std::string configfile = "";
	std::string serverfile = "";
	std::string dir_in = "";
	std::string dir_out = "";
	std::string file_in = "";
	std::string tree_out = "";
	std::string hist_out = "";	
	std::string pre_in = "";
	std::string pre_tree = "ComptonTree";
	std::string pre_hist = "ComptonHist";

	Int_t length;
	std::string flag;

	if(argc == 1)
	{
		cout << "Please provide a config file" << endl;
		return 0;
	}
	else if(argc == 2) configfile = argv[1];
	else
	{
		for(int i=1; i<argc; i++)
		{
			flag = argv[i];
			if(flag.find_first_of("-") == 0)
			{
				i++;
				flag.erase(0,1);
				if(strcmp(flag.c_str(), "s") == 0) serverfile = argv[i];
				else if(strcmp(flag.c_str(), "d") == 0) dir_in = argv[i];
				else if(strcmp(flag.c_str(), "D") == 0) dir_out = argv[i];
				else if(strcmp(flag.c_str(), "f") == 0) file_in = argv[i];
				else if(strcmp(flag.c_str(), "p") == 0) pre_in = argv[i];
				else
				{
					cout << "Unknown flag " << flag << endl;
					return 0;
				}
			}
			else configfile = argv[i];
		}
	}

	// Check that config file exists:
	ifstream cfile(configfile.c_str());
	if(!cfile)
	{
		cout << "Config file '" << configfile << "' could not be found." << endl;
		return 0;
	}

	// If server file is specified, check that it exists
	if(serverfile.length() > 0)
	{
		// Check that file exists:
		ifstream sfile(serverfile.c_str());
		if(!sfile)
		{
			cout << "Server file '" << serverfile << "' could not be found" << endl;
			return 0;
		}
	}
	// If no server file is specified, allow for checking in the config file
	else serverfile = configfile;

	// Create instance of PCompton class
	PCompton* pcompton = new PCompton;

	// If unset, scan server or config file for file settings
	if(dir_in.length() == 0)
	{
		flag = pcompton->ReadConfig("Input-Directory",0,(Char_t*)serverfile.c_str());	
		flag.erase(0,flag.find_first_not_of(" "));
		if(strcmp(flag.c_str(),"nokey") != 0) dir_in = flag;
	}
	
	if(dir_out.length() == 0)
	{	
		flag = pcompton->ReadConfig("Output-Directory",0,(Char_t*)serverfile.c_str());	
		flag.erase(0,flag.find_first_not_of(" "));
		if(strcmp(flag.c_str(),"nokey") != 0) dir_out = flag;
	}
	
	if(file_in.length() == 0)
	{	
		flag = pcompton->ReadConfig("Input-File",0,(Char_t*)serverfile.c_str());	
		flag.erase(0,flag.find_first_not_of(" "));
		if(strcmp(flag.c_str(),"nokey") != 0) file_in = flag;
	}
	
	if(pre_in.length() == 0)
	{	
		flag = pcompton->ReadConfig("Input-Prefix",0,(Char_t*)serverfile.c_str());	
		flag.erase(0,flag.find_first_not_of(" "));
		if(strcmp(flag.c_str(),"nokey") != 0) pre_in = flag;
	}
	
	// Finished scanning for file settings
	
	// Fix directories to include final slash if not there
	if(dir_in.find_last_of("/") != (dir_in.length()-1)) dir_in += "/";
	if(dir_out.find_last_of("/") != (dir_out.length()-1)) dir_out += "/";

	// Output user settings (Set to defaults if still unspecified)
	cout << endl << "User inputs" << endl;
	cout << "Config file:      '" << configfile << "' chosen" << endl;
	if(dir_in.length() != 0)  	cout << "Input directory:  '" << dir_in << "' chosen" << endl;
	if(dir_out.length() != 0)  	cout << "Output directory: '" << dir_out << "' chosen" << endl;
	if(file_in.length() != 0)  	cout << "Input file:       '" << file_in << "' chosen" << endl;
	if(pre_in.length() != 0)  	cout << "Input prefix:     '" << pre_in << "' chosen" << endl;
	else { pre_in = "GoAT"; 	cout << "Input prefix:     '" << pre_in << "' chosen by default" << endl; }
	cout << endl;
	
	// Perform full initialisation 
	if(!pcompton->Init(configfile.c_str()))
	{
		cout << "ERROR: PCompton Init failed!" << endl;
		return 0;
	}

	std::string file;
	std::string prefix;
	std::string suffix;

	Int_t files_found = 0;
	// If input file is specified, use it
	if(file_in.length() > 0)
	{
		cout << "Searching for input file(s)" << endl;
		file = file_in;
		length = file.length();
		// File should at least have '.root' at the end
		if(length >= 5)
		{
			// Add input directory to it
			file_in = dir_in+file_in;
			cout << "Input file  '" << file_in << "' chosen" << endl;

			// If output file is specified, use it
			if(tree_out.length() > 0) tree_out = dir_out+tree_out;
			// If output file is not specified, build it
			else
			{
				// If tree output directory is not specified, build it
				if(dir_out.length() == 0)
				{
					prefix = file.substr(0,file.find_last_of("/")+1);
					dir_out = dir_in+prefix;
				}
				// If input prefix doesn't match, simply prepend output prefix to the file name
				if(file.find(pre_in)>file.length()) suffix = ("_"+file.substr(file.find_last_of("/")+1,length-(file.find_last_of("/")+1)));
				// If input prefix does match, switch prefixes
				else suffix = file.substr(file.find_last_of("/")+1+pre_in.length(),length-(file.find_last_of("/")+1+pre_in.length()));
				// Build output file name
				tree_out = dir_out+pre_tree+suffix;
			}

			// If hist output file is specified, use it
			if(hist_out.length() > 0) hist_out = dir_out+hist_out;
			// If output file is not specified, build it
			else
			{
				// If output directory is not specified, build it
				if(dir_out.length() == 0)
				{
					prefix = file.substr(0,file.find_last_of("/")+1);
					dir_out = dir_in+prefix;
				}
				// If input prefix doesn't match, simply prepend output prefix to the file name
				if(file.find(pre_in)>file.length()) suffix = ("_"+file.substr(file.find_last_of("/")+1,length-(file.find_last_of("/")+1)));
				// If input prefix does match, switch prefixes
				else suffix = file.substr(file.find_last_of("/")+1+pre_in.length(),length-(file.find_last_of("/")+1+pre_in.length()));
				// Build output file name
				hist_out = dir_out+pre_hist+suffix;
			}
			
			cout << "Output tree '" << tree_out << "' chosen" << endl;
			cout << "Output hist '" << hist_out << "' chosen" << endl << endl;			
			if(!pcompton->File(file_in.c_str(), tree_out.c_str(), hist_out.c_str())) 
					cout << "ERROR: PCompton failed on file " << file_in << "!" << endl;
			files_found++;
		}
	}
	// Otherwise scan input directory for matching files
	else
	{
		cout << "Searching input directory for files matching input prefix" << endl;
		cout << "Input prefix '" << pre_in << "' chosen" << endl << endl;
			
		// If output directory is not specified, use the input directory
		if(dir_in.length()  == 0) dir_in  = "./"; // Search in current directory
		if(dir_out.length() == 0) dir_out = dir_in;

		// Create list of files in input directory
		TSystemFile *sys_file;
		TSystemDirectory *sys_dir = new TSystemDirectory("files",dir_in.c_str());
		TList *file_list = sys_dir->GetListOfFiles();
		file_list->Sort();
		TIter file_iter(file_list);

		// Iterate over files
		while((sys_file=(TSystemFile*)file_iter()))
		{
			file = sys_file->GetName();
			length = file.length();
			// File should at least have '.root' at the end
			if(length >= 5)
			{
				//Check that prefixes and suffixes match
				prefix = file.substr(0,pre_in.length());
				suffix = file.substr(length-5,5);
				if(((strcmp(prefix.c_str(),pre_in.c_str()) == 0)) && (strcmp(suffix.c_str(),".root") == 0))
				{
					// Build input file name
					file_in = dir_in+file;
					// Build output file name
					suffix = file.substr(pre_in.length(),length-pre_in.length());
					tree_out = dir_out+pre_tree+suffix;					
					hist_out = dir_out+pre_hist+suffix;
					
					files_found++;
					// Run PCompton
					
					cout << "Output tree '" << tree_out << "' chosen" << endl;
					cout << "Output hist '" << hist_out << "' chosen" << endl << endl;						
					if(!pcompton->File(file_in.c_str(), tree_out.c_str(), hist_out.c_str())) 
						cout << "ERROR: PCompton failed on file " << file_in << "!" << endl;

				}
			}
		}
	}
	if (files_found == 0)
	{
		cout << "ERROR: No GoAT files found!" << endl;
		return 0;
	}

	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

	return 0;
}

PCompton::PCompton() :
			nentries(0),
			TC(0),
			E(0),
			time(0),
			theta(0),
			phi(0),
			MissMass(0),
			MissE(0),
			OA(0)
{ 

	TC 		= new Int_t[maxentries];
	E		= new Double_t[maxentries];
	time	= new Double_t[maxentries];
	theta	= new Double_t[maxentries];
	phi		= new Double_t[maxentries];
	MissMass= new Double_t[maxentries];
	MissE	= new Double_t[maxentries];
	OA		= new Double_t[maxentries];	
}

PCompton::~PCompton()
{
}

Bool_t	PCompton::Init(const char* configfile)
{
	// Set by user in the future...
	SetTarget(938);
	
	Double_t Random_low1 	= -450;
	Double_t Random_high1 	=  -50;
	Double_t Prompt_low 	=  -20;
	Double_t Prompt_high 	=   15;
	Double_t Random_low2 	=   45;
	Double_t Random_high2 	=  445;
	
	SetPromptWindow( Prompt_low,  Prompt_high);
	SetRandomWindow1(Random_low1, Random_high1);
	SetRandomWindow2(Random_low2, Random_high2);
	SetPvRratio();	
	
	OACut			= 10;
	
	MMCut_low 		= 900;
	MMCut_high 		= 1000;
	theta_bin_size 	= 20;
	phi_bin_size 	= 20;
	
	ReconstructPhysicsTree = kTRUE;
	FillHistograms = kTRUE;
	
	return kTRUE;
}

Bool_t	PCompton::File(const char* gfile, const char* tfile, const char* hfile)
{
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
	
	Analyse();	
	
	// Close the GoAT file before leaving.
	CloseGoATFile();
		
	return kTRUE;
}

void	PCompton::Analyse()
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

void	PCompton::Reconstruct()
{
	if(GetGoATEvent() % 100000 == 0) printf("Event: %d\n",GetGoATEvent());

	nentries = 0;
	Bool_t 	compton;
	Int_t 	neutral;
	Int_t 	charged;
	
	compton = kTRUE;
	
	// Perform event selection, fill physics tree for Compton events
	if(GoATTree_GetNParticles() == 2) 
	{
		// Check that event is one neutral + one charged
		if ((GoATTree_GetCharge(0) == 0) && (GoATTree_GetCharge(1) == 1))		{neutral = 0; charged = 1;}
		else if ((GoATTree_GetCharge(0) == 1) && (GoATTree_GetCharge(1) == 0))	{neutral = 1; charged = 0;}
		else compton = kFALSE;
		
		// Check that both are single particle reconstructions 
		if(GoATTree_GetNDaughters(0) != 0) compton = kFALSE;
		if(GoATTree_GetNDaughters(1) != 0) compton = kFALSE;
		
		// Fill Diagnostic histograms
		if (compton)
		{
			neutral_theta->Fill(GoATTree_GetTheta(neutral));			
			neutral_phi->Fill(GoATTree_GetPhi(neutral));
			
			charged_theta->Fill(GoATTree_GetTheta(charged));			
			charged_phi->Fill(GoATTree_GetPhi(charged));
			
			phi_diff->Fill(TMath::Abs(GoATTree_GetPhi(0) - GoATTree_GetPhi(1)));
		}
			
		// Check coplanarity
		if (compton)
		{
			Double_t phidiff = TMath::Abs(GoATTree_GetPhi(0) - GoATTree_GetPhi(1));
			if ((phidiff < 170) || (phidiff > 190)) compton = kFALSE;
			else 
			{
				// Fill diagnostic histograms post cop. cut
				neutral_theta_cop->Fill(GoATTree_GetTheta(neutral));			
				neutral_phi_cop->Fill(GoATTree_GetPhi(neutral));
				
				charged_theta_cop->Fill(GoATTree_GetTheta(charged));			
				charged_phi_cop->Fill(GoATTree_GetPhi(charged));
							
				phi_diff_cop->Fill(phidiff);
			}
		}
		
		// Require forward charged particle
		if (compton)
		{
			Double_t chargedtheta = GoATTree_GetTheta(charged);
			if (chargedtheta > 50) compton = kFALSE;
			else
			{
				// Fill diagnostic histograms post cop & ch. theta cut
				neutral_theta_cop_cth->Fill(GoATTree_GetTheta(neutral));			
				neutral_phi_cop_cth->Fill(GoATTree_GetPhi(neutral));
				
				charged_theta_cop_cth->Fill(GoATTree_GetTheta(charged));			
				charged_phi_cop_cth->Fill(GoATTree_GetPhi(charged));
				
				phi_diff_cop_cth->Fill(TMath::Abs(GoATTree_GetPhi(0) - GoATTree_GetPhi(1)));
			}			
		}
	}
	else compton = kFALSE;	

	if(compton)
	{
		for (Int_t j = 0; j < GetNTagged(); j++)
		{
			
			TC[nentries] 		= GetTagged_ch(j);
			E[nentries] 		= GetPhotonBeam_E(j);
			time[nentries]		= GetTagged_t(j) - GoATTree_GetTime(neutral);
			theta[nentries]		= GoATTree_GetTheta(neutral);
			phi[nentries]		= GoATTree_GetPhi(neutral);
			
			TLorentzVector p4 	= CalcMissingP4(neutral,j);
			
			MissMass[nentries] 	= p4.M();
			MissE[nentries]	 	= p4.T();
			OA[nentries] 		= p4.Vect().Angle(GetGoATVector(charged).Vect())*TMath::RadToDeg();
						
			nentries++;
		}
	}

	treePhysics->Fill();

}

void  PCompton::PostReconstruction()
{
	Int_t N = (Int_t)treePhysics->GetEntries();
	for (Int_t i=0;i<N;i++) {

		treePhysics->GetEntry(i);

		for (Int_t j = 0; j < nentries; j ++)
		{
			time_compton->Fill(time[j]);
			
			Prompt = IsPrompt(time[j]); 
			Random = IsRandom(time[j]);
			
			opening_angle->Fill(OA[j]);
			
			if(OA[j] <= OACut)
			{
				opening_angle_cut->Fill(OA[j]);
				
				if ((!Prompt) && (!Random)) continue;
				
				if(E[j] < 270.0) continue;
				if(E[j] > 290.0) continue;
				
				if (Prompt) 
				{
					// Fill 1D histograms
					MM_prompt_compton->Fill(MissMass[j]);
					if(MissMass[j] < 900) continue;
					if(MissMass[j] > 940) continue;										
					
					TC_prompt->Fill(TC[j]);
					E_prompt->Fill(E[j]);
					theta_prompt->Fill(theta[j]);
					if((theta[j] >=   0) && (theta[j] <  20)) phi_prompt_0_20->Fill(phi[j]);
					if((theta[j] >=  20) && (theta[j] <  40)) phi_prompt_20_40->Fill(phi[j]);
					if((theta[j] >=  40) && (theta[j] <  60)) phi_prompt_40_60->Fill(phi[j]);
					if((theta[j] >=  60) && (theta[j] <  80)) phi_prompt_60_80->Fill(phi[j]);								
					if((theta[j] >=  80) && (theta[j] < 100)) phi_prompt_80_100->Fill(phi[j]);								
					if((theta[j] >= 100) && (theta[j] < 120)) phi_prompt_100_120->Fill(phi[j]);
					if((theta[j] >= 120) && (theta[j] < 140)) phi_prompt_120_140->Fill(phi[j]);
					if((theta[j] >= 140) && (theta[j] < 160)) phi_prompt_140_160->Fill(phi[j]);
					if((theta[j] >= 160) && (theta[j] < 180)) phi_prompt_160_180->Fill(phi[j]);							
					phi_prompt->Fill(phi[j]);

					ME_prompt_compton->Fill(MissE[j]);	
					opening_angle_prompt->Fill(OA[j]);
									
					// Fill 3D histograms according to cuts
					if((MissMass[j] >= MMCut_low) && (MissMass[j] <= MMCut_high))
					{
						TC_theta_phi_prompt->Fill(TC[j], theta[j], phi[j]);
					}
					
				}
				if (Random)
				{
					// Fill 1D histograms
					MM_random_compton->Fill(MissMass[j]);
					if(MissMass[j] < 900) continue;
					if(MissMass[j] > 940) continue;	
										
					TC_random->Fill(TC[j]);
					E_random->Fill(E[j]);
					theta_random->Fill(theta[j]);
					if((theta[j] >=   0) && (theta[j] <  20)) phi_random_0_20->Fill(phi[j]);
					if((theta[j] >=  20) && (theta[j] <  40)) phi_random_20_40->Fill(phi[j]);
					if((theta[j] >=  40) && (theta[j] <  60)) phi_random_40_60->Fill(phi[j]);
					if((theta[j] >=  60) && (theta[j] <  80)) phi_random_60_80->Fill(phi[j]);								
					if((theta[j] >=  80) && (theta[j] < 100)) phi_random_80_100->Fill(phi[j]);								
					if((theta[j] >= 100) && (theta[j] < 120)) phi_random_100_120->Fill(phi[j]);
					if((theta[j] >= 120) && (theta[j] < 140)) phi_random_120_140->Fill(phi[j]);
					if((theta[j] >= 140) && (theta[j] < 160)) phi_random_140_160->Fill(phi[j]);
					if((theta[j] >= 160) && (theta[j] < 180)) phi_random_160_180->Fill(phi[j]);						
					phi_random->Fill(phi[j]);

					ME_random_compton->Fill(MissE[j]);	
					opening_angle_random->Fill(OA[j]);
					
					// Fill 3D histograms according to cuts
					if((MissMass[j] >= MMCut_low) && (MissMass[j] <= MMCut_high))
					{
						TC_theta_phi_random->Fill(TC[j], theta[j], phi[j]);
					}
				}
			}
		}
	}

	RandomSubtraction(TC_prompt,TC_random, TC_sub);		
	RandomSubtraction(E_prompt,E_random, E_sub);		
	RandomSubtraction(theta_prompt,theta_random, theta_sub);	
		
	RandomSubtraction(phi_prompt,phi_random, phi_sub);
	RandomSubtraction(phi_prompt_0_20,phi_random_0_20, phi_sub_0_20);		
	RandomSubtraction(phi_prompt_20_40,phi_random_20_40, phi_sub_20_40);
	RandomSubtraction(phi_prompt_40_60,phi_random_40_60, phi_sub_40_60);
	RandomSubtraction(phi_prompt_60_80,phi_random_60_80, phi_sub_60_80);
	RandomSubtraction(phi_prompt_80_100,phi_random_80_100, phi_sub_80_100);
	RandomSubtraction(phi_prompt_100_120,phi_random_100_120, phi_sub_100_120);
	RandomSubtraction(phi_prompt_120_140,phi_random_120_140, phi_sub_120_140);
	RandomSubtraction(phi_prompt_140_160,phi_random_140_160, phi_sub_140_160);
	RandomSubtraction(phi_prompt_160_180,phi_random_160_180, phi_sub_160_180);
		
	RandomSubtraction(MM_prompt_compton,MM_random_compton, MM_sub_compton);		
	RandomSubtraction(ME_prompt_compton,ME_random_compton, ME_sub_compton);		
	RandomSubtraction(opening_angle_prompt,opening_angle_random, opening_angle_sub);	
	
	ShowTimeCuts(time_compton, time_compton_cuts);

}

Bool_t  PCompton::InitPhysicsTree(TFile* F)
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
	treePhysics->Branch("OA",		OA,			"OA[nentries]/D");
		
	return kTRUE;
}

Bool_t  PCompton::OpenPhysicsTree(TFile* F)
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
	treePhysics->SetBranchAddress("OA",			OA);
		
	return kTRUE;
}

Bool_t  PCompton::WriteTrees(TFile* F)
{
	if(!F) return kFALSE;
	F->cd();
	
	if(treePhysics)				treePhysics->Write();
	
	return kTRUE;
}

void	PCompton::InitHistograms()
{
	gROOT->cd();
		
	// 1-D histograms for diagnostics
	neutral_theta 		= new TH1D("neutral_theta",	"neutral_theta",	180,0,180); 	
	neutral_phi 		= new TH1D("neutral_phi",	"neutral_phi",		18,-180,180); 
	charged_theta 		= new TH1D("charged_theta",	"charged_theta",	180,0,180); 	
	charged_phi 		= new TH1D("charged_phi",	"charged_phi",		18,-180,180); 	
	phi_diff 			= new TH1D("phi_diff",		"phi_diff",			360,0,360); 	

	// 1-D histogram after coplanarity condition
	neutral_theta_cop	= new TH1D("neutral_theta_cop",	"neutral_theta_cop",	180,0,180); 	
	neutral_phi_cop		= new TH1D("neutral_phi_cop",	"neutral_phi_cop",		18,-180,180);
	charged_theta_cop	= new TH1D("charged_theta_cop",	"charged_theta_cop",	180,0,180); 	
	charged_phi_cop		= new TH1D("charged_phi_cop",	"charged_phi_cop",		18,-180,180); 	
	phi_diff_cop		= new TH1D("phi_diff_cop",		"phi_diff_cop",			360,0,360); 	

	// 1-D histogram after coplanarity condition & charged theta
	neutral_theta_cop_cth	= new TH1D("neutral_theta_cop_cth",	"neutral_theta_cop_cth",	180,0,180); 	
	neutral_phi_cop_cth		= new TH1D("neutral_phi_cop_cth",	"neutral_phi_cop_cth",		18,-180,180); 
	charged_theta_cop_cth	= new TH1D("charged_theta_cop_cth",	"charged_theta_cop_cth",	180,0,180); 	
	charged_phi_cop_cth		= new TH1D("charged_phi_cop_cth",	"charged_phi_cop_cth",		18,-180,180);
	phi_diff_cop_cth		= new TH1D("phi_diff_cop_cth",		"phi_diff_cop_cth",			360,0,360); 
		
	// 1-D histograms of applied cuts
	phi_diff_cut 		= new TH1D("phi_diff_cut",	"phi_diff_cut",360,0,360);	
	charged_theta_cut 	= new TH1D("charged_theta_cut","charged_theta_cut",180,0,180); 
	
	time_compton		= new TH1D("time_compton",	"time_compton",		1200,-600,600);
	time_compton_cuts	= new TH1D("time_compton_cuts",	"time_compton_cuts",1200,-600,600);
	opening_angle 		= new TH1D("opening_angle",	"opening_angle",	100,0,100);		
	opening_angle_cut 	= new TH1D("opening_angle_cut","opening_angle_cut",100, 0, 100); 
		
	// Post Cut histos
	TC_prompt 		= new TH1D("TC_prompt",		"TC_prompt",	352,0,352);
	TC_random 		= new TH1D("TC_random",		"TC_random",	352,0,352);
	TC_sub			= new TH1D("TC subtracted",	"TC subtracted",352,0,352);	

	TC_prompt->Sumw2(); 
	TC_random->Sumw2();
	TC_sub->Sumw2();

	E_prompt 		= new TH1D("E_prompt",		"E_prompt",		5,250,350);
	E_random 		= new TH1D("E_random",		"E_random",		5,250,350);
	E_sub			= new TH1D("E subtracted",	"E subtracted",	5,250,350);

	E_prompt->Sumw2(); 
	E_random->Sumw2();
	E_sub->Sumw2();
	
	theta_prompt 	= new TH1D("theta_prompt",		"theta_prompt",		36,0,180);	
	theta_random 	= new TH1D("theta_random",		"theta_random",		36,0,180);
	theta_sub		= new TH1D("theta_subtracted",	"theta_subtracted",	36,0,180);
	
	theta_prompt->Sumw2(); 
	theta_random->Sumw2();
	theta_sub->Sumw2();	
	
	phi_prompt 		= new TH1D("phi_prompt",		"phi_prompt",		18,-180,180);
	phi_random 		= new TH1D("phi_random",		"phi_random",		18,-180,180);
	phi_sub			= new TH1D("phi_subtracted",	"phi_subtracted",	18,-180,180);	

	phi_prompt->Sumw2(); 
	phi_random->Sumw2();
	phi_sub->Sumw2();	

	phi_prompt_0_20	= new TH1D("phi_prompt_0_20",		"phi_prompt_0_20",		18,-180,180);
	phi_random_0_20	= new TH1D("phi_random_0_20",		"phi_random_0_20",		18,-180,180);
	phi_sub_0_20	= new TH1D("phi_subtracted_0_20",	"phi_subtracted_0_20",	18,-180,180);

	phi_prompt_0_20->Sumw2(); 
	phi_random_0_20->Sumw2();
	phi_sub_0_20->Sumw2();	

	phi_prompt_20_40	= new TH1D("phi_prompt_20_40",		"phi_prompt_20_40",		18,-180,180);
	phi_random_20_40	= new TH1D("phi_random_20_40",		"phi_random_20_40",		18,-180,180);
	phi_sub_20_40	= new TH1D("phi_subtracted_20_40",	"phi_subtracted_20_40",	18,-180,180);	

	phi_prompt_20_40->Sumw2(); 
	phi_random_20_40->Sumw2();
	phi_sub_20_40->Sumw2();	
	
	phi_prompt_40_60	= new TH1D("phi_prompt_40_60",		"phi_prompt_40_60",		18,-180,180);
	phi_random_40_60	= new TH1D("phi_random_40_60",		"phi_random_40_60",		18,-180,180);
	phi_sub_40_60	= new TH1D("phi_subtracted_40_60",	"phi_subtracted_40_60",	18,-180,180);	

	phi_prompt_40_60->Sumw2(); 
	phi_random_40_60->Sumw2();
	phi_sub_40_60->Sumw2();	
	
	phi_prompt_60_80	= new TH1D("phi_prompt_60_80",		"phi_prompt_60_80",		18,-180,180);
	phi_random_60_80	= new TH1D("phi_random_60_80",		"phi_random_60_80",		18,-180,180);
	phi_sub_60_80	= new TH1D("phi_subtracted_60_80",	"phi_subtracted_60_80",	18,-180,180);	

	phi_prompt_60_80->Sumw2(); 
	phi_random_60_80->Sumw2();
	phi_sub_60_80->Sumw2();	
	
	phi_prompt_80_100	= new TH1D("phi_prompt_80_100",		"phi_prompt_80_100",		18,-180,180);
	phi_random_80_100	= new TH1D("phi_random_80_100",		"phi_random_80_100",		18,-180,180);
	phi_sub_80_100	= new TH1D("phi_subtracted_80_100",	"phi_subtracted_80_100",	18,-180,180);	

	phi_prompt_80_100->Sumw2(); 
	phi_random_80_100->Sumw2();
	phi_sub_80_100->Sumw2();	

	phi_prompt_100_120	= new TH1D("phi_prompt_100_120",		"phi_prompt_100_120",		18,-180,180);
	phi_random_100_120	= new TH1D("phi_random_100_120",		"phi_random_100_120",		18,-180,180);
	phi_sub_100_120	= new TH1D("phi_subtracted_100_120",	"phi_subtracted_100_120",	18,-180,180);	

	phi_prompt_100_120->Sumw2(); 
	phi_random_100_120->Sumw2();
	phi_sub_100_120->Sumw2();	
	
	phi_prompt_120_140	= new TH1D("phi_prompt_120_140",		"phi_prompt_120_140",		18,-180,180);
	phi_random_120_140	= new TH1D("phi_random_120_140",		"phi_random_120_140",		18,-180,180);
	phi_sub_120_140	= new TH1D("phi_subtracted_120_140",	"phi_subtracted_120_140",	18,-180,180);	

	phi_prompt_120_140->Sumw2(); 
	phi_random_120_140->Sumw2();
	phi_sub_120_140->Sumw2();	
	
	phi_prompt_140_160	= new TH1D("phi_prompt_140_160",		"phi_prompt_140_160",		18,-180,180);
	phi_random_140_160	= new TH1D("phi_random_140_160",		"phi_random_140_160",		18,-180,180);
	phi_sub_140_160	= new TH1D("phi_subtracted_140_160",	"phi_subtracted_140_160",	18,-180,180);	

	phi_prompt_140_160->Sumw2(); 
	phi_random_140_160->Sumw2();
	phi_sub_140_160->Sumw2();	
	
	phi_prompt_160_180	= new TH1D("phi_prompt_160_180",		"phi_prompt_160_180",		18,-180,180);
	phi_random_160_180	= new TH1D("phi_random_160_180",		"phi_random_160_180",		18,-180,180);
	phi_sub_160_180	= new TH1D("phi_subtracted_160_180",	"phi_subtracted_160_180",	18,-180,180);	

	phi_prompt_160_180->Sumw2(); 
	phi_random_160_180->Sumw2();
	phi_sub_160_180->Sumw2();		

	MM_prompt_compton 	= new TH1D("MM_prompt_compton",		"MM_prompt_compton",	1500,0,1500); 
	MM_random_compton 	= new TH1D("MM_random_compton",		"MM_random_compton",	1500,0,1500); 
	MM_sub_compton		= new TH1D("MM_subtracted_compton",	"MM_subtracted_compton",1500,0,1500); 

	MM_prompt_compton->Sumw2(); 
	MM_random_compton->Sumw2();
	MM_sub_compton->Sumw2();

	ME_prompt_compton 	= new TH1D("ME_prompt_compton",		"ME_prompt_compton",	1500,0,1500); 
	ME_random_compton 	= new TH1D("ME_random_compton",		"ME_random_compton",	1500,0,1500); 
	ME_sub_compton		= new TH1D("ME_subtracted_compton",	"ME_subtracted_compton",1500,0,1500); 
	
	ME_prompt_compton->Sumw2(); 
	ME_random_compton->Sumw2();
	ME_sub_compton->Sumw2();
	
	opening_angle_prompt 	= new TH1D("opening_angle_prompt",		"opening_angle_prompt",500,0,50);
	opening_angle_random 	= new TH1D("opening_angle_random",		"opening_angle_random",500,0,50);
	opening_angle_sub		= new TH1D("opening_angle_sub",			"opening_angle_sub",500,0,50);
	
	opening_angle_prompt->Sumw2(); 
	opening_angle_random->Sumw2();
	opening_angle_sub->Sumw2();	
	
	// 3D histograms (for analysis)
	Int_t theta_bins = int(180/theta_bin_size) + 1;
	Double_t max_theta = (theta_bins)*theta_bin_size;

	Int_t phi_bins 	 = int(360/phi_bin_size) + 1;
	Double_t max_phi = (phi_bins)*phi_bin_size;	


	TC_theta_phi_prompt	= new TH3D("TC_theta_phi_prompt","TC_theta_phi_prompt",	352,0,352, theta_bins,0,max_theta, 	phi_bins,-180,max_phi);
	TC_theta_phi_random = new TH3D("TC_theta_phi_random","TC_theta_phi_random",	352,0,352, theta_bins,0,max_theta, 	phi_bins,-180,max_phi);

	TC_theta_phi_prompt->Sumw2(); 
	TC_theta_phi_random->Sumw2();

}

Bool_t 	PCompton::WriteHistograms(TFile* hfile)
{
	if(!hfile) return kFALSE;
	hfile->cd();
	gROOT->GetList()->Write();
	gROOT->GetList()->Delete();
		
	return kTRUE;
}

Bool_t	PCompton::OpenPhysTreeFile(const char* tfile, Option_t* option)
{
	PhysTreeFile = new TFile(tfile, option);
	if(!PhysTreeFile) return kFALSE;
    if(PhysTreeFile->IsZombie()) return kFALSE;
    
	cout << "PhysTreeFile " << tfile << " opened (option = "<< option << ")." << endl;
	
	return kTRUE;
}

Bool_t 	PCompton::ClosePhysTreeFile()
{
	if(!PhysTreeFile) return kFALSE;
	PhysTreeFile->Close();
	
	return kTRUE;
}

#endif

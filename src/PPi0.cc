#ifndef __CINT__

#include "PPi0.h"

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
	std::string pre_tree = "Pi0Tree";
	std::string pre_hist = "Pi0Hist";

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

	// Create instance of PPi0 class
	PPi0* ppi0 = new PPi0;

	// If unset, scan server or config file for file settings
	if(dir_in.length() == 0)
	{
		flag = ppi0->ReadConfig("Input-Directory",0,(Char_t*)serverfile.c_str());	
		flag.erase(0,flag.find_first_not_of(" "));
		if(strcmp(flag.c_str(),"nokey") != 0) dir_in = flag;
	}
	
	if(dir_out.length() == 0)
	{	
		flag = ppi0->ReadConfig("Output-Directory",0,(Char_t*)serverfile.c_str());	
		flag.erase(0,flag.find_first_not_of(" "));
		if(strcmp(flag.c_str(),"nokey") != 0) dir_out = flag;
	}
	
	if(file_in.length() == 0)
	{	
		flag = ppi0->ReadConfig("Input-File",0,(Char_t*)serverfile.c_str());	
		flag.erase(0,flag.find_first_not_of(" "));
		if(strcmp(flag.c_str(),"nokey") != 0) file_in = flag;
	}
	
	if(pre_in.length() == 0)
	{	
		flag = ppi0->ReadConfig("Input-Prefix",0,(Char_t*)serverfile.c_str());	
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
	if(!ppi0->Init(configfile.c_str()))
	{
		cout << "ERROR: PPi0 Init failed!" << endl;
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
			if(!ppi0->File(file_in.c_str(), tree_out.c_str(), hist_out.c_str())) 
					cout << "ERROR: PPi0 failed on file " << file_in << "!" << endl;
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
					// Run PPi0
					
					cout << "Output tree '" << tree_out << "' chosen" << endl;
					cout << "Output hist '" << hist_out << "' chosen" << endl << endl;						
					if(!ppi0->File(file_in.c_str(), tree_out.c_str(), hist_out.c_str())) 
						cout << "ERROR: PPi0 failed on file " << file_in << "!" << endl;

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

PPi0::PPi0() :
			nentries(0),
			TC(0),
			E(0),
			time(0),
			theta(0),
			thetaCM(0),
			phi(0),
			MissMass(0),
			MissE(0)
{ 

	TC 		= new Int_t[maxentries];
	E		= new Double_t[maxentries];
	time	= new Double_t[maxentries];
	theta	= new Double_t[maxentries];
	thetaCM = new Double_t[maxentries];
	phi		= new Double_t[maxentries];
	MissMass= new Double_t[maxentries];
	MissE	= new Double_t[maxentries];
}

PPi0::~PPi0()
{
}

Bool_t	PPi0::Init(const char* configfile)
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
	
	return kTRUE;
}

Bool_t	PPi0::File(const char* gfile, const char* tfile, const char* hfile)
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
			if(!OpenPhysicsTree(PhysTreeFile)) 	return kFALSE;
			
		}
		
		OpenHistFile(hfile,"RECREATE");
		InitHistograms();
	}
	
	Analyse();	
	
	// Close the GoAT file before leaving.
	CloseGoATFile();
	
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
	//	if (GoATTree_GetCharge(i) != 0) continue;
	//	if (GoATTree_GetNDaughters(i) != 2) continue;
	//	if (GoATTree_GetApparatus(i) != 1) continue;

		for (Int_t j = 0; j < GetNTagged(); j++)
		{
			TC[nentries] 		= GetTagged_ch(j);
			E[nentries] 		= GetPhotonBeam_E(j);
			time[nentries]		= GetTagged_t(j) - GoATTree_GetTime(i);
			
			//Calculate boost vector
			TVector3 CMBoost;
			TLorentzVector beam;
			beam = TLorentzVector(0.,0.,GetPhotonBeam_E(j),GetPhotonBeam_E(j));
			CMBoost = -1.0 * (GetTarget() + beam).BoostVector();

			//L-boost from Lab to CM frame
			TLorentzVector p4 = GetGoATVector(i);
			p4.Boost(CMBoost);			
			
			theta[nentries]		= GoATTree_GetTheta(i);
			thetaCM[nentries]   = p4.Theta() * TMath::RadToDeg();
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
			
			//if(E[j] < 270.0) continue;
			//if(E[j] > 280.0) continue;			
			
			if (Prompt) 
			{
				// Fill 1D histograms
				TC_prompt->Fill(TC[j]);
				E_prompt->Fill(E[j]);
				theta_prompt->Fill(thetaCM[j]);
				phi_prompt->Fill(phi[j]);
				if((thetaCM[j] >=   0) && (thetaCM[j] <  10)) phi_prompt_0_10->Fill(phi[j]);
				if((thetaCM[j] >=  10) && (thetaCM[j] <  20)) phi_prompt_10_20->Fill(phi[j]);		
				if((thetaCM[j] >=  20) && (thetaCM[j] <  30)) phi_prompt_20_30->Fill(phi[j]);
				if((thetaCM[j] >=  30) && (thetaCM[j] <  40)) phi_prompt_30_40->Fill(phi[j]);				
				if((thetaCM[j] >=  40) && (thetaCM[j] <  50)) phi_prompt_40_50->Fill(phi[j]);
				if((thetaCM[j] >=  50) && (thetaCM[j] <  60)) phi_prompt_50_60->Fill(phi[j]);				
				if((thetaCM[j] >=  60) && (thetaCM[j] <  70)) phi_prompt_60_70->Fill(phi[j]);				
				if((thetaCM[j] >=  70) && (thetaCM[j] <  80)) phi_prompt_70_80->Fill(phi[j]);				
				if((thetaCM[j] >=  80) && (thetaCM[j] <  90)) phi_prompt_80_90->Fill(phi[j]);				
				if((thetaCM[j] >=  90) && (thetaCM[j] < 100)) phi_prompt_90_100->Fill(phi[j]);				
				if((thetaCM[j] >= 100) && (thetaCM[j] < 110)) phi_prompt_100_110->Fill(phi[j]);						
				if((thetaCM[j] >= 110) && (thetaCM[j] < 120)) phi_prompt_110_120->Fill(phi[j]);						
				if((thetaCM[j] >= 120) && (thetaCM[j] < 130)) phi_prompt_120_130->Fill(phi[j]);						
				if((thetaCM[j] >= 130) && (thetaCM[j] < 140)) phi_prompt_130_140->Fill(phi[j]);						
				if((thetaCM[j] >= 140) && (thetaCM[j] < 150)) phi_prompt_140_150->Fill(phi[j]);						
				if((thetaCM[j] >= 150) && (thetaCM[j] < 160)) phi_prompt_150_160->Fill(phi[j]);						
				if((thetaCM[j] >= 160) && (thetaCM[j] < 170)) phi_prompt_160_170->Fill(phi[j]);						
				if((thetaCM[j] >= 170) && (thetaCM[j] < 180)) phi_prompt_170_180->Fill(phi[j]);						
																				
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
				theta_random->Fill(thetaCM[j]);
				phi_random->Fill(phi[j]);
				if((thetaCM[j] >=   0) && (thetaCM[j] <  10)) phi_random_0_10->Fill(phi[j]);
				if((thetaCM[j] >=  10) && (thetaCM[j] <  20)) phi_random_10_20->Fill(phi[j]);		
				if((thetaCM[j] >=  20) && (thetaCM[j] <  30)) phi_random_20_30->Fill(phi[j]);
				if((thetaCM[j] >=  30) && (thetaCM[j] <  40)) phi_random_30_40->Fill(phi[j]);				
				if((thetaCM[j] >=  40) && (thetaCM[j] <  50)) phi_random_40_50->Fill(phi[j]);
				if((thetaCM[j] >=  50) && (thetaCM[j] <  60)) phi_random_50_60->Fill(phi[j]);				
				if((thetaCM[j] >=  60) && (thetaCM[j] <  70)) phi_random_60_70->Fill(phi[j]);				
				if((thetaCM[j] >=  70) && (thetaCM[j] <  80)) phi_random_70_80->Fill(phi[j]);				
				if((thetaCM[j] >=  80) && (thetaCM[j] <  90)) phi_random_80_90->Fill(phi[j]);				
				if((thetaCM[j] >=  90) && (thetaCM[j] < 100)) phi_random_90_100->Fill(phi[j]);				
				if((thetaCM[j] >= 100) && (thetaCM[j] < 110)) phi_random_100_110->Fill(phi[j]);						
				if((thetaCM[j] >= 110) && (thetaCM[j] < 120)) phi_random_110_120->Fill(phi[j]);						
				if((thetaCM[j] >= 120) && (thetaCM[j] < 130)) phi_random_120_130->Fill(phi[j]);						
				if((thetaCM[j] >= 130) && (thetaCM[j] < 140)) phi_random_130_140->Fill(phi[j]);						
				if((thetaCM[j] >= 140) && (thetaCM[j] < 150)) phi_random_140_150->Fill(phi[j]);						
				if((thetaCM[j] >= 150) && (thetaCM[j] < 160)) phi_random_150_160->Fill(phi[j]);						
				if((thetaCM[j] >= 160) && (thetaCM[j] < 170)) phi_random_160_170->Fill(phi[j]);						
				if((thetaCM[j] >= 170) && (thetaCM[j] < 180)) phi_random_170_180->Fill(phi[j]);						
				
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
	RandomSubtraction(phi_prompt_0_10,		phi_random_0_10, 	phi_sub_0_10);	
	RandomSubtraction(phi_prompt_10_20,		phi_random_10_20, 	phi_sub_10_20);			
	RandomSubtraction(phi_prompt_20_30,		phi_random_20_30, 	phi_sub_20_30);	
	RandomSubtraction(phi_prompt_30_40,		phi_random_30_40, 	phi_sub_30_40);	
	RandomSubtraction(phi_prompt_40_50,		phi_random_40_50, 	phi_sub_40_50);	
	RandomSubtraction(phi_prompt_50_60,		phi_random_50_60, 	phi_sub_50_60);
	RandomSubtraction(phi_prompt_60_70,		phi_random_60_70, 	phi_sub_60_70);	
	RandomSubtraction(phi_prompt_70_80,		phi_random_70_80, 	phi_sub_70_80);	
	RandomSubtraction(phi_prompt_80_90,		phi_random_80_90, 	phi_sub_80_90);	
	RandomSubtraction(phi_prompt_90_100,	phi_random_90_100, 	phi_sub_90_100);	
	RandomSubtraction(phi_prompt_100_110,	phi_random_100_110, 	phi_sub_100_110);	
	RandomSubtraction(phi_prompt_110_120,	phi_random_110_120, 	phi_sub_110_120);	
	RandomSubtraction(phi_prompt_120_130,	phi_random_120_130, 	phi_sub_120_130);	
	RandomSubtraction(phi_prompt_130_140,	phi_random_130_140, 	phi_sub_130_140);	
	RandomSubtraction(phi_prompt_140_150,	phi_random_140_150, 	phi_sub_140_150);	
	RandomSubtraction(phi_prompt_150_160,	phi_random_150_160, 	phi_sub_150_160);	
	RandomSubtraction(phi_prompt_160_170,	phi_random_160_170, 	phi_sub_160_170);	
	RandomSubtraction(phi_prompt_170_180,	phi_random_170_180, 	phi_sub_170_180);		
	
	
	
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
	treePhysics->Branch("thetaCM",	thetaCM,	"thetaCM[nentries]/D");
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
	treePhysics->SetBranchAddress("thetaCM",	thetaCM);
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
	gROOT->cd();
			
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
	
	phi_prompt 		= new TH1D("phi_prompt",		"phi_prompt",		36,-180,180);
	phi_random 		= new TH1D("phi_random",		"phi_random",		36,-180,180);
	phi_sub				= new TH1D("phi_subtracted","phi_subtracted",	36,-180,180);	

	phi_prompt->Sumw2(); 
	phi_random->Sumw2();
	phi_sub->Sumw2();	

	phi_prompt_0_10	= new TH1D("phi_prompt_0_10",		"phi_prompt_0_10",		36,-180,180);
	phi_random_0_10	= new TH1D("phi_random_0_10",		"phi_random_0_10",		36,-180,180);
	phi_sub_0_10	= new TH1D("phi_subtracted_0_10",	"phi_subtracted_0_10",	36,-180,180);	

	phi_prompt_0_10->Sumw2(); 
	phi_random_0_10->Sumw2();
	phi_sub_0_10->Sumw2();
	
	phi_prompt_10_20	= new TH1D("phi_prompt_10_20",		"phi_prompt_10_20",		36,-180,180);
	phi_random_10_20	= new TH1D("phi_random_10_20",		"phi_random_10_20",		36,-180,180);
	phi_sub_10_20	= new TH1D("phi_subtracted_10_20",	"phi_subtracted_10_20",	36,-180,180);	

	phi_prompt_10_20->Sumw2(); 
	phi_random_10_20->Sumw2();
	phi_sub_10_20->Sumw2();		

	phi_prompt_20_30	= new TH1D("phi_prompt_20_30",		"phi_prompt_20_30",		36,-180,180);
	phi_random_20_30	= new TH1D("phi_random_20_30",		"phi_random_20_30",		36,-180,180);
	phi_sub_20_30	= new TH1D("phi_subtracted_20_30",	"phi_subtracted_20_30",	36,-180,180);	

	phi_prompt_20_30->Sumw2(); 
	phi_random_20_30->Sumw2();
	phi_sub_20_30->Sumw2();		

	phi_prompt_30_40	= new TH1D("phi_prompt_30_40",		"phi_prompt_30_40",		36,-180,180);
	phi_random_30_40	= new TH1D("phi_random_30_40",		"phi_random_30_40",		36,-180,180);
	phi_sub_30_40	= new TH1D("phi_subtracted_30_40",	"phi_subtracted_30_40",	36,-180,180);	

	phi_prompt_30_40->Sumw2(); 
	phi_random_30_40->Sumw2();
	phi_sub_30_40->Sumw2();	
	
	phi_prompt_40_50	= new TH1D("phi_prompt_40_50",		"phi_prompt_40_50",		36,-180,180);
	phi_random_40_50	= new TH1D("phi_random_40_50",		"phi_random_40_50",		36,-180,180);
	phi_sub_40_50	= new TH1D("phi_subtracted_40_50",	"phi_subtracted_40_50",	36,-180,180);	

	phi_prompt_40_50->Sumw2(); 
	phi_random_40_50->Sumw2();
	phi_sub_40_50->Sumw2();	
	
	phi_prompt_50_60	= new TH1D("phi_prompt_50_60",		"phi_prompt_50_60",		36,-180,180);
	phi_random_50_60	= new TH1D("phi_random_50_60",		"phi_random_50_60",		36,-180,180);
	phi_sub_50_60	= new TH1D("phi_subtracted_50_60",	"phi_subtracted_50_60",	36,-180,180);	

	phi_prompt_50_60->Sumw2(); 
	phi_random_50_60->Sumw2();
	phi_sub_50_60->Sumw2();		

	phi_prompt_60_70	= new TH1D("phi_prompt_60_70",		"phi_prompt_60_70",		36,-180,180);
	phi_random_60_70	= new TH1D("phi_random_60_70",		"phi_random_60_70",		36,-180,180);
	phi_sub_60_70	= new TH1D("phi_subtracted_60_70",	"phi_subtracted_60_70",	36,-180,180);	

	phi_prompt_60_70->Sumw2(); 
	phi_random_60_70->Sumw2();
	phi_sub_60_70->Sumw2();	


	phi_prompt_70_80	= new TH1D("phi_prompt_70_80",		"phi_prompt_70_80",		36,-180,180);
	phi_random_70_80	= new TH1D("phi_random_70_80",		"phi_random_70_80",		36,-180,180);
	phi_sub_70_80	= new TH1D("phi_subtracted_70_80",	"phi_subtracted_70_80",	36,-180,180);	

	phi_prompt_70_80->Sumw2(); 
	phi_random_70_80->Sumw2();
	phi_sub_70_80->Sumw2();	


	phi_prompt_80_90	= new TH1D("phi_prompt_80_90",		"phi_prompt_80_90",		36,-180,180);
	phi_random_80_90	= new TH1D("phi_random_80_90",		"phi_random_80_90",		36,-180,180);
	phi_sub_80_90	= new TH1D("phi_subtracted_80_90",	"phi_subtracted_80_90",	36,-180,180);	

	phi_prompt_80_90->Sumw2(); 
	phi_random_80_90->Sumw2();
	phi_sub_80_90->Sumw2();	


	phi_prompt_90_100	= new TH1D("phi_prompt_90_100",		"phi_prompt_90_100",		36,-180,180);
	phi_random_90_100	= new TH1D("phi_random_90_100",		"phi_random_90_100",		36,-180,180);
	phi_sub_90_100	= new TH1D("phi_subtracted_90_100",	"phi_subtracted_90_100",	36,-180,180);	

	phi_prompt_90_100->Sumw2(); 
	phi_random_90_100->Sumw2();
	phi_sub_90_100->Sumw2();	


	phi_prompt_100_110	= new TH1D("phi_prompt_100_110",		"phi_prompt_100_110",		36,-180,180);
	phi_random_100_110	= new TH1D("phi_random_100_110",		"phi_random_100_110",		36,-180,180);
	phi_sub_100_110	= new TH1D("phi_subtracted_100_110",	"phi_subtracted_100_110",	36,-180,180);	

	phi_prompt_100_110->Sumw2(); 
	phi_random_100_110->Sumw2();
	phi_sub_100_110->Sumw2();	


	phi_prompt_110_120	= new TH1D("phi_prompt_110_120",		"phi_prompt_110_120",		36,-180,180);
	phi_random_110_120	= new TH1D("phi_random_110_120",		"phi_random_110_120",		36,-180,180);
	phi_sub_110_120	= new TH1D("phi_subtracted_110_120",	"phi_subtracted_110_120",	36,-180,180);	

	phi_prompt_110_120->Sumw2(); 
	phi_random_110_120->Sumw2();
	phi_sub_110_120->Sumw2();	


	phi_prompt_120_130	= new TH1D("phi_prompt_120_130",		"phi_prompt_120_130",		36,-180,180);
	phi_random_120_130	= new TH1D("phi_random_120_130",		"phi_random_120_130",		36,-180,180);
	phi_sub_120_130	= new TH1D("phi_subtracted_120_130",	"phi_subtracted_120_130",	36,-180,180);	

	phi_prompt_120_130->Sumw2(); 
	phi_random_120_130->Sumw2();
	phi_sub_120_130->Sumw2();	

	phi_prompt_130_140	= new TH1D("phi_prompt_130_140",		"phi_prompt_130_140",		36,-180,180);
	phi_random_130_140	= new TH1D("phi_random_130_140",		"phi_random_130_140",		36,-180,180);
	phi_sub_130_140	= new TH1D("phi_subtracted_130_140",	"phi_subtracted_130_140",	36,-180,180);	

	phi_prompt_130_140->Sumw2(); 
	phi_random_130_140->Sumw2();
	phi_sub_130_140->Sumw2();	

	phi_prompt_140_150	= new TH1D("phi_prompt_140_150",		"phi_prompt_140_150",		36,-180,180);
	phi_random_140_150	= new TH1D("phi_random_140_150",		"phi_random_140_150",		36,-180,180);
	phi_sub_140_150	= new TH1D("phi_subtracted_140_150",	"phi_subtracted_140_150",	36,-180,180);	

	phi_prompt_140_150->Sumw2(); 
	phi_random_140_150->Sumw2();
	phi_sub_140_150->Sumw2();	
	
	phi_prompt_150_160	= new TH1D("phi_prompt_150_160",		"phi_prompt_150_160",		36,-180,180);
	phi_random_150_160	= new TH1D("phi_random_150_160",		"phi_random_150_160",		36,-180,180);
	phi_sub_150_160	= new TH1D("phi_subtracted_150_160",	"phi_subtracted_150_160",	36,-180,180);	

	phi_prompt_150_160->Sumw2(); 
	phi_random_150_160->Sumw2();
	phi_sub_150_160->Sumw2();	


	phi_prompt_160_170	= new TH1D("phi_prompt_160_170",		"phi_prompt_160_170",		36,-180,180);
	phi_random_160_170	= new TH1D("phi_random_160_170",		"phi_random_160_170",		36,-180,180);
	phi_sub_160_170	= new TH1D("phi_subtracted_160_170",	"phi_subtracted_160_170",	36,-180,180);	

	phi_prompt_160_170->Sumw2(); 
	phi_random_160_170->Sumw2();
	phi_sub_160_170->Sumw2();	


	phi_prompt_170_180	= new TH1D("phi_prompt_170_180",		"phi_prompt_170_180",		36,-180,180);
	phi_random_170_180	= new TH1D("phi_random_170_180",		"phi_random_170_180",		36,-180,180);
	phi_sub_170_180	= new TH1D("phi_subtracted_170_180",	"phi_subtracted_170_180",	36,-180,180);	

	phi_prompt_170_180->Sumw2(); 
	phi_random_170_180->Sumw2();
	phi_sub_170_180->Sumw2();	

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
	gROOT->GetList()->Write();
	gROOT->GetList()->Delete();
		
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

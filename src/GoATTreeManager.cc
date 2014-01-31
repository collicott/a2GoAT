
#include "GoATTreeManager.h"

GoATTreeManager::GoATTreeManager() :	
				GoATFile(0),
				treeParticles(0),
				nParticles(0),
				Charge(0),
				PDG(0),
				nDaughters(0),
				Px(0),
				Py(0),
				Pz(0),
				Ek(0),
				Theta(0),
				Phi(0),
				Mass(0),		
				time(0),
				clusterSize(0),
				Apparatus(0),
				d_E(0),
				WC0_E(0),
				WC1_E(0),
				WC_Vertex_X(0),
				WC_Vertex_Y(0),
				WC_Vertex_Z(0),	
				nDaughterList(0),
				daughter_index(0),	
   	          	daughter_E(0),	
   	          	daughter_Theta(0),	
              	daughter_Phi(0),	
   	            daughter_PDG(0) 
{   
	Charge			= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
	PDG				= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
	nDaughters 		= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];	
	Px				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    Py				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    Pz				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    Ek				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    Theta			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];    
    Phi				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];  
    Mass			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];      
    time			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    clusterSize		= new UChar_t[GAcquTREEMANAGER_MAX_PARTICLE];
    
    Apparatus		= new UChar_t[GAcquTREEMANAGER_MAX_PARTICLE];
    d_E				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    WC0_E			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    WC1_E			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];

    WC_Vertex_X		= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Y		= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Z		= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    
    daughter_index	= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
    daughter_E		= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    daughter_Theta	= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    daughter_Phi	= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    daughter_PDG	= new Int_t[GAcquTREEMANAGER_MAX_PARTICLE];
}

GoATTreeManager::~GoATTreeManager()
{
	Reset();
}

void	GoATTreeManager::Reset()
{
	if(GoATFile)        	delete GoATFile;
	if(treeParticles) 	delete treeParticles;
  
}

Bool_t	  GoATTreeManager::OpenGoATFile(const char* treefile, Option_t* option)
{
	GoATFile = TFile::Open(treefile, option);
    
	if(!GoATFile) return kFALSE;
	if(GoATFile->IsZombie()) return kFALSE;
    
	cout << "GoATFile " << treefile << " opened." << endl;
        
	return kTRUE;
}


Bool_t	  GoATTreeManager::CloseOutputFile(TFile* TreeFile)
{
	if(!TreeFile) 
	{
		cout << "CloseOutputFile called with no file open."<< endl;
		return kFALSE;
	}
	
	TreeFile->cd();
	WriteTrees();
		
	TreeFile->Close();
	cout << "closed output file."<< endl;
	return kTRUE;
}


Bool_t  GoATTreeManager::InitTreeParticles(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE;
	TreeFile->cd();
	
	treeParticles = new TTree("treeParticles", "treeParticles");
	if(!treeParticles) return kFALSE;
	cout << "treeParticles created." << endl;
	
	treeParticles->Branch("nParticles",&nParticles,"nParticles/I");
	treeParticles->Branch("Charge",Charge,"Charge[nParticles]/I");
	treeParticles->Branch("PDG",PDG,"PDG[nParticles]/I");
	treeParticles->Branch("nDaughters",	nDaughters,"nDaughters[nParticles]/I");
	treeParticles->Branch("Px", Px,"Px[nParticles]/D");
	treeParticles->Branch("Py", Py,"Py[nParticles]/D");
	treeParticles->Branch("Pz", Pz,"Pz[nParticles]/D");
	treeParticles->Branch("Ek",  Ek,"Ek[nParticles]/D");
	treeParticles->Branch("Mass",  Mass,"Mass[nParticles]/D");		
	treeParticles->Branch("Theta",  Theta,"Theta[nParticles]/D");	
	treeParticles->Branch("Phi",  Phi,"Phi[nParticles]/D");
	treeParticles->Branch("time", time,"time[nParticles]/D");
	treeParticles->Branch("clusterSize", clusterSize,"clusterSize[nParticles]/b");
	treeParticles->Branch("Apparatus", Apparatus,"Apparatus[nParticles]/b");
	treeParticles->Branch("d_E", d_E, "d_E[nParticles]/D");
	treeParticles->Branch("WC0_E", WC0_E, "WC0_E[nParticles]/D");
	treeParticles->Branch("WC1_E", WC1_E, "WC0_E[nParticles]/D");
	treeParticles->Branch("WC_Vertex_X", WC_Vertex_X, "WC_Vertex_X[nParticles]/D");
	treeParticles->Branch("WC_Vertex_Y", WC_Vertex_Y, "WC_Vertex_Y[nParticles]/D");
	treeParticles->Branch("WC_Vertex_Z", WC_Vertex_Z, "WC_Vertex_Z[nParticles]/D");
	treeParticles->Branch("nDaughterList",&nDaughterList,"nDaughterList/I");
	treeParticles->Branch("daughter_index", daughter_index,	"daughter_index[nDaughterList]/I");
	treeParticles->Branch("daughter_E", 	daughter_E,		"daughter_E[nDaughterList]/D");
	treeParticles->Branch("daughter_Theta", daughter_Theta,	"daughter_Theta[nDaughterList]/D");
	treeParticles->Branch("daughter_Phi", 	daughter_Phi,	"daughter_Phi[nDaughterList]/D");
	treeParticles->Branch("daughter_PDG", 	daughter_PDG,	"daughter_PDG[nDaughterList]/I");
	
	return kTRUE;
}

Bool_t    GoATTreeManager::OpenTreeParticles(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE; 
	treeParticles = (TTree*)TreeFile->Get("treeParticles");
	if(!treeParticles)	return kFALSE;
	
	treeParticles->SetBranchAddress("nParticles",&nParticles);
	treeParticles->SetBranchAddress("Charge",Charge);
	treeParticles->SetBranchAddress("PDG",PDG);
	treeParticles->SetBranchAddress("nDaughters",nDaughters);
	treeParticles->SetBranchAddress("Px", Px);
	treeParticles->SetBranchAddress("Py", Py);
	treeParticles->SetBranchAddress("Pz", Pz);
	treeParticles->SetBranchAddress("Ek",  Ek);
	treeParticles->SetBranchAddress("Mass",  Mass);		
	treeParticles->SetBranchAddress("Theta",  Theta);	
	treeParticles->SetBranchAddress("Phi",  Phi);
	treeParticles->SetBranchAddress("time", time);
	treeParticles->SetBranchAddress("clusterSize", clusterSize);
	treeParticles->SetBranchAddress("Apparatus", Apparatus);
	treeParticles->SetBranchAddress("d_E", d_E);
	treeParticles->SetBranchAddress("WC0_E", WC0_E);
	treeParticles->SetBranchAddress("WC1_E", WC1_E);
	treeParticles->SetBranchAddress("WC_Vertex_X", WC_Vertex_X);
	treeParticles->SetBranchAddress("WC_Vertex_Y", WC_Vertex_Y);
	treeParticles->SetBranchAddress("WC_Vertex_Z", WC_Vertex_Z);
	treeParticles->SetBranchAddress("nDaughterList",&nDaughterList);
	treeParticles->SetBranchAddress("daughter_index", daughter_index);
	treeParticles->SetBranchAddress("daughter_E", 	daughter_E);
	treeParticles->SetBranchAddress("daughter_Theta", daughter_Theta);
	treeParticles->SetBranchAddress("daughter_Phi", daughter_Phi);
	treeParticles->SetBranchAddress("daughter_PDG", daughter_PDG);
	
	cout << "treeParticles opened." << endl;
	return kTRUE;
}

void	GoATTreeManager::Reconstruct()
{
	printf("No Reconstruct method found in Parent\n");
}

Bool_t	GoATTreeManager::FillEvent()
{
	// Fill event into tree
	if(treeParticles)				treeParticles->Fill();
	else if(treeRawEvent_clone)		treeRawEvent_clone->Fill();

	if(treeTagger_clone) 			treeTagger_clone->Fill();
	if(treeTrigger_clone)			treeTrigger_clone->Fill();
	if(treeDetectorHits_clone)		treeDetectorHits_clone->Fill();

	return kTRUE;
}

Bool_t  GoATTreeManager::WriteTrees(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE;
	TreeFile->cd();
	
	// Write trees to file
	if(treeParticles)      			treeParticles->Write();
	else if(treeRawEvent_clone)		treeRawEvent_clone->Write();

	if(treeTagger_clone)			treeTagger_clone->Write();
	if(treeTrigger_clone)			treeTrigger_clone->Write();
	if(treeScaler_clone)			treeScaler_clone->Write();
	if(treeDetectorHits_clone)		treeDetectorHits_clone->Write();

	return kTRUE;
}

void	GoATTreeManager::Print()
{
	GAcquTreeManager::Print();

}

Bool_t	GoATTreeManager::FindValidGoATEvents()
{
	firstGoATEvent = 0;
	if (treeParticles)
	{
		lastGoATEvent = (Int_t)treeParticles->GetEntries();
		cout << "Total #Events deterimed from treeParticles" << endl;
		cout << "Analysing events from " << firstGoATEvent << 
				" to " << lastGoATEvent << "." << endl;		
		return kTRUE;
	}

	if (treeRawEvent_clone)
	{
		lastGoATEvent = (Int_t)treeRawEvent_clone->GetEntries();
		cout << "Total #Events deterimed from treeRawEvent" << endl;
		cout << "Analysing events from " << firstGoATEvent << 
				" to " << lastGoATEvent << "." << endl;			
		return kTRUE;
	}
	if (treeTagger_clone)
	{
		lastGoATEvent = (Int_t)treeTagger_clone->GetEntries();
		cout << "Total #Events deterimed from treeTagger" << endl;
		cout << "Analysing events from " << firstGoATEvent << 
				" to " << lastGoATEvent << "." << endl;		
		return kTRUE;
	}
	if (treeTrigger_clone)
	{
		lastGoATEvent = (Int_t)treeTrigger_clone->GetEntries();
		cout << "Total #Events deterimed from treeTrigger" << endl;
		cout << "Analysing events from " << firstGoATEvent << 
				" to " << lastGoATEvent << "." << endl;	
		return kTRUE;
	}
	if (treeDetectorHits_clone)
	{
		lastGoATEvent = (Int_t)treeDetectorHits_clone->GetEntries();
		cout << "Total #Events deterimed from treeDetectorHits" << endl;
		cout << "Analysing events from " << firstGoATEvent << 
				" to " << lastGoATEvent << "." << endl;			
		return kTRUE;
	}		

	return kFALSE;
}

void GoATTreeManager::GetGoATEntryFast()
{
	GoATEvent++;
	
	// Get GoAT produced trees
    if (treeParticles)		treeParticles->GetEntry(GoATEvent);

	// Get Acqu copied trees
	GetAcquEntry(GoATEvent);
}

void	GoATTreeManager::TraverseGoATEntries(const Int_t min, const Int_t max)
{

    GoATEvent = min-1;
    for(int i=min; i<=max; i++)
	{
		GetGoATEntryFast();
		Reconstruct();
	}
}
	string GoATTreeManager::ReadConfig(const std::string& key_in, Int_t instance, Char_t* configname)
{
	Int_t string_instance = 0;
	std::string key = key_in;
	std::transform(key.begin(), key.end(),key.begin(), ::toupper);
	
	std::string str;
	std::string values;
	
	ifstream configfile;

	configfile.open(configname);
		
	if (configfile.is_open())
	{
		while ( getline (configfile,str) ) 
		{
			std::string::size_type begin = str.find_first_not_of(" \f\t\v");
			if(begin == std::string::npos) continue;		
			if(std::string("#").find(str[begin]) != std::string::npos)	continue;
			if(std::string("//").find(str[begin]) != std::string::npos)	continue;
			
			std::string firstWord;
			
			try {
				firstWord = str.substr(0,str.find(":"));
			}
			catch(std::exception& e) {
				firstWord = str.erase(str.find_first_of(":"),str.find_first_of(":"));
			}
			std::transform(firstWord.begin(),firstWord.end(),firstWord.begin(), ::toupper);

			values = str.substr(str.find(":")+1,str.length());

			if (strcmp(firstWord.c_str(),key.c_str()) == 0) 
			{
				if (string_instance == instance) 
				{
					configfile.close();
					return values;			
				}
				else string_instance++;
			}
		}
		configfile.close();
	}

	return "nokey";
}

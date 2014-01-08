
#include "GTreeManager.h"

GTreeManager::GTreeManager() :	
				file(0),
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
	Charge			= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
	PDG				= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
	nDaughters 		= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];	
	Px				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Py				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Pz				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Ek				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Theta			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];    
    Phi				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];  
    Mass			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];      
    time			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    clusterSize		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    
    Apparatus		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    d_E				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC0_E			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC1_E			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];

    WC_Vertex_X		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Y		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Z		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    
    daughter_index	= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    daughter_E		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    daughter_Theta	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    daughter_Phi	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    daughter_PDG	= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
}

GTreeManager::~GTreeManager()
{
	Reset();
}

void	GTreeManager::Reset()
{
	if(file)        	delete file;
	if(treeParticles) 	delete treeParticles;
  
}

Bool_t	  GTreeManager::OpenOutputFile(const char* treefile)
{
    file = TFile::Open(treefile, "RECREATE");
    
	if(!file) return kFALSE;
    if(file->IsZombie()) return kFALSE;
    
	cout << "file " << treefile << " created." << endl;
	return kTRUE;
}


Bool_t	  GTreeManager::CloseOutputFile()
{
	if(!file) 
	{
		cout << "CloseOutputFile called with no file open."<< endl;
		return kFALSE;
	}
	
	file->cd();
	WriteTrees();
		
    file->Close();
	cout << "closed output file."<< endl;
	return kTRUE;
}


Bool_t  GTreeManager::InitTreeParticles()
{
	if(!file) return kFALSE;
	file->cd();
	
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

Bool_t    GTreeManager::OpenTreeParticles()
{
	if(!file) return kFALSE; 
	treeParticles = (TTree*)file->Get("treeParticles");
	if(!treeParticles)	return kFALSE;
	cout << "treeParticles opened." << endl;
	return kTRUE;
}

void	GTreeManager::Reconstruct()
{
	printf("No Reconstruct method found in Parent\n");
}

Bool_t	GTreeManager::FillEvent()
{
	// Fill event into tree
	if(treeParticles)				treeParticles->Fill();
	else 							treeRawEvent_clone->Fill();

	if(treeTagger_clone) 			treeTagger_clone->Fill();
	if(treeTrigger_clone)			treeTrigger_clone->Fill();
	if(treeScaler_clone)			treeScaler_clone->Fill();
	if(treeDetectorHits_clone)		treeDetectorHits_clone->Fill();
	
	return kTRUE;
}

Bool_t  GTreeManager::WriteTrees()
{
	if(!file) return kFALSE;
	file->cd();
	
	// Write trees to file
	if(treeParticles)				treeParticles->Write();
	else if(treeRawEvent_clone)		treeRawEvent_clone->Write();
	
	if(treeTagger_clone)			treeTagger_clone->Write();
	if(treeTrigger_clone)			treeTrigger_clone->Write();
	if(treeScaler_clone)			treeScaler_clone->Write();
	if(treeDetectorHits_clone)		treeDetectorHits_clone->Write();
	
	return kTRUE;
}

void	GTreeManager::Print()
{
	GInputTreeManager::Print();

}

	string GTreeManager::ReadConfig(const std::string& key_in, Int_t instance, Char_t* configname)
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

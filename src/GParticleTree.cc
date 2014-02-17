
#include "GParticleTree.h"

using namespace std;

GParticleTree::GParticleTree() :
                treeRootino(0),
                treePhoton(0),
                treeChargedPi(0),
                treeProton(0),
                treeNeutron(0),
                rootino(),
                photon(),
                chargedPi(),
                proton(),
                neutron()
{   
}

GParticleTree::~GParticleTree()
{
	Reset();
}

void	GParticleTree::Reset()
{
    if(treeRootino) 	delete treeRootino;
    if(treePhoton)      delete treePhoton;
    if(treeChargedPi) 	delete treeChargedPi;
    if(treeProton)      delete treeProton;
    if(treeNeutron) 	delete treeNeutron;
}

Bool_t  GParticleTree::InitTree(TTree*& tree, const structGParticleTree& struc, const char* treeName)
{
   	if(!file_out) return kFALSE;
    	file_out->cd();


    tree = new TTree(treeName,treeName);
    if(!tree) return kFALSE;
    cout << treeName << "created." << endl;
	
    tree->Branch("size",(void*)&struc.size,"size/I");
    tree->Branch("Px", (void*)struc.Px,"Px[size]/D");
    tree->Branch("Py", (void*)struc.Py,"Py[size]/D");
    tree->Branch("Pz", (void*)struc.Pz,"Pz[size]/D");
    tree->Branch("E",  (void*)struc.E,"E[size]/D");
	
	return kTRUE;
}


Bool_t    GParticleTree::OpenTree(TTree*& tree, TTree *&tree_clone, structGParticleTree &struc, const char *treeName)
{
    if(!file_in) return kFALSE;
    tree = (TTree*)file_in->Get(treeName);
    if(!tree)	return kFALSE;
	
    tree->SetBranchAddress("size",&struc.size);
    tree->SetBranchAddress("Px", struc.Px);
    tree->SetBranchAddress("Py", struc.Py);
    tree->SetBranchAddress("Pz", struc.Pz);
    tree->SetBranchAddress("Ek", struc.E);
	
    tree_clone  = tree->CloneTree(0);

    cout << treeName << "opened." << endl;
	return kTRUE;
}

void    GParticleTree::AddParticle(structGParticleTree& particle, const TLorentzVector vec)
{
    particle.Px[particle.size]   = vec.Px();
    particle.Py[particle.size]   = vec.Py();
    particle.Pz[particle.size]   = vec.Pz();
    particle.E[particle.size]    = vec.E();
    particle.size++;
}

void    GParticleTree::Clear()
{
    rootino.size    = 0;
    photon.size     = 0;
    chargedPi.size  = 0;
    proton.size     = 0;
    neutron.size    = 0;
}

void	GParticleTree::Reconstruct()
{
	printf("No Reconstruct method found in Parent\n");
}

Bool_t	GParticleTree::FillEvent()
{
    GAcquTree::FillEvent();

    if(treeRootino_clone)     treeRootino_clone->Fill();
    if(treePhoton_clone)      treePhoton_clone->Fill();
    if(treeChargedPi_clone)   treeChargedPi_clone->Fill();
    if(treeProton_clone)      treeProton_clone->Fill();
    if(treeNeutron_clone)     treeNeutron_clone->Fill();

	return kTRUE;
}

Bool_t  GParticleTree::WriteTrees()
{
    GAcquTree::WriteTrees();

    if(treeRootino_clone)     treeRootino_clone->Write();
    if(treePhoton_clone)      treePhoton_clone->Write();
    if(treeChargedPi_clone)   treeChargedPi_clone->Write();
    if(treeProton_clone)      treeProton_clone->Write();
    if(treeNeutron_clone)     treeNeutron_clone->Write();
	
	return kTRUE;
}

void	GParticleTree::Print()
{
    GAcquTree::Print();

}


void GParticleTree::GetEntryFast()
{
    // Get Acqu copied trees
    GAcquTree::GetEntryFast();

    // Get GoAT produced trees
    if(treeRootino)     treeRootino->GetEntry();
    if(treePhoton)      treePhoton->GetEntry();
    if(treeChargedPi)   treeChargedPi->GetEntry();
    if(treeProton)      treeProton->GetEntry();
    if(treeNeutron)     treeNeutron->GetEntry();
}


/*string GParticleTree::ReadConfig(const std::string& key_in, Int_t instance, Char_t* configname)
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
}*/

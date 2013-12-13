
#include "GTreeManager.h"

GTreeManager::GTreeManager() :	
				file(0),
				treeParticles(0),
				nParticles(0),
				PDG(0),
				Px(0),
				Py(0),
				Pz(0),
				E(0),
				time(0),
				clusterSize(0),
				Apparatus(0),
				d_E(0),
				WC0_E(0),
				WC1_E(0),
				WC_Vertex_X(0),
				WC_Vertex_Y(0),
				WC_Vertex_Z(0),	
				Meson_phot_Px(0),	
   	          	Meson_phot_Py(0),	
   	          	Meson_phot_Pz(0),	
              	Meson_phot_E(0),	
   	            Meson_phot_Index(0) 
{   
	PDG				= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
	Px				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Py				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Pz				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    E				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    time				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    clusterSize		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    
    Apparatus		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    d_E				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC0_E			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC1_E			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];

    WC_Vertex_X		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Y		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Z		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    
    Meson_phot_Px	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Meson_phot_Py	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Meson_phot_Pz	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Meson_phot_E	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Meson_phot_Index	= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
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
	if(treeParticles)	treeParticles->Write();
		
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
	
	treeParticles->Branch("nParticles",&nParticles);
	treeParticles->Branch("PDG",PDG);
	treeParticles->Branch("Px", Px);
	treeParticles->Branch("Py", Py);
	treeParticles->Branch("Pz", Pz);
	treeParticles->Branch("E",  E);	
	treeParticles->Branch("time", time);
	treeParticles->Branch("clusterSize", clusterSize);
	treeParticles->Branch("Apparatus", Apparatus);
	treeParticles->Branch("d_E", d_E);	
	treeParticles->Branch("WC0_E", WC0_E);	
	treeParticles->Branch("WC1_E", WC1_E);
	treeParticles->Branch("WC_Vertex_X", WC_Vertex_X);	
	treeParticles->Branch("WC_Vertex_Y", WC_Vertex_Y);	
	treeParticles->Branch("WC_Vertex_Z", WC_Vertex_Z);	
/*	treeParticles->Branch("Meson_phot_Px",Meson_phot_Px);
	treeParticles->Branch("Meson_phot_Py",Meson_phot_Py);
	treeParticles->Branch("Meson_phot_Pz",Meson_phot_Pz);
	treeParticles->Branch("Meson_phot_E", Meson_phot_E);
	treeParticles->Branch("Meson_phot_Index",Meson_phot_Index); */
	
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
	if(treeParticles)	treeParticles->Fill();

	return kTRUE;
}

void	GTreeManager::Print()
{
	GInputTreeManager::Print();

}

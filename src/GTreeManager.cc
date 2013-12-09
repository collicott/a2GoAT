
#include "GTreeManager.h"

GTreeManager::GTreeManager() :	
				file(0),
				treeParticles(0),
				gP_nParticles(0),
				gP_PDG(0),
				gP_Px(0),
				gP_Py(0),
				gP_Pz(0),
				gP_E(0),
				gP_time(0),
				gP_clusterSize(0),
				gP_Apparatus(0),
				gP_d_E(0),
				gP_WC0_E(0),
				gP_WC1_E(0),
				gP_WC_Vertex_X(0),
				gP_WC_Vertex_Y(0),
				gP_WC_Vertex_Z(0),	
				gP_Meson_phot_Px(0),	
   	          	gP_Meson_phot_Py(0),	
   	          	gP_Meson_phot_Pz(0),	
              	gP_Meson_phot_E(0),	
   	            gP_Meson_phot_Index(0) 
{   
	gP_Px				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_Py				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_Pz				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_E				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_time				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_clusterSize		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    
    gP_Apparatus		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_d_E				= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_WC0_E			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_WC1_E			= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];

    gP_WC_Vertex_X		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_WC_Vertex_Y		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_WC_Vertex_Z		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    
    gP_Meson_phot_Px	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_Meson_phot_Py	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_Meson_phot_Pz	= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_Meson_phot_E		= new Double_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    gP_Meson_phot_Index	= new Int_t[GINPUTTREEMANAGER_MAX_PARTICLE];
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
    file = TFile::Open(treefile, "UPDATE");
    
	if(!file) return kFALSE;
    if(file->IsZombie()) return kFALSE;
    
	cout << "file " << treefile << " created." << endl;
	return kTRUE;
}


Bool_t  GTreeManager::InitTreeParticles()
{
	if(!file) return kFALSE;
	file->cd();
	
	treeParticles = new TTree("treeParticles", "treeParticles");
	if(!treeParticles) return kFALSE;
	cout << "treeParticles created." << endl;
	
	treeParticles->Branch("nParticles",&gP_nParticles);
	treeParticles->Branch("Px", gP_Px);
	treeParticles->Branch("Py", gP_Py);
	treeParticles->Branch("Pz", gP_Pz);
	treeParticles->Branch("E",  gP_E);	
	treeParticles->Branch("time", gP_time);
	treeParticles->Branch("clusterSize", gP_clusterSize);
	treeParticles->Branch("Apparatus", gP_Apparatus);
	treeParticles->Branch("d_E", gP_d_E);	
	treeParticles->Branch("WC0_E", gP_WC0_E);	
	treeParticles->Branch("WC1_E", gP_WC1_E);
	treeParticles->Branch("WC_Vertex_X", gP_WC_Vertex_X);	
	treeParticles->Branch("WC_Vertex_Y", gP_WC_Vertex_Y);	
	treeParticles->Branch("WC_Vertex_Z", gP_WC_Vertex_Z);	
	treeParticles->Branch("Meson_phot_Px",gP_Meson_phot_Px);
	treeParticles->Branch("Meson_phot_Py",gP_Meson_phot_Py);
	treeParticles->Branch("Meson_phot_Pz",gP_Meson_phot_Pz);
	treeParticles->Branch("Meson_phot_E", gP_Meson_phot_E);
	treeParticles->Branch("Meson_phot_Index",gP_Meson_phot_Index);
	
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


Bool_t	GTreeManager::Write()
{
	if(!file)			return kFALSE;
	file->cd();
	if(treeParticles)	treeParticles->Write();

}

void	GTreeManager::Print()
{
	GInputTreeManager::Print();

}

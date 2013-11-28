
#include "GTreeManager.h"

GTreeManager::GTreeManager() :	
				file(0),
                treePi0(0),
                treeEta(0),
                treeEtap(0)
{   
	pi0.child1			= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE/2];
    pi0.child2			= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE/2];
    eta.child2g1		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE/2];
    eta.child2g2		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE/2];
    etap.child2g1		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE/2];
    etap.child2g2		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE/2];
}

GTreeManager::~GTreeManager()
{
	Reset();
}

void	GTreeManager::Reset()
{
    if(treePi0)             delete treePi0;
    if(treeEta)             delete treeEta;
    if(treeEtap)            delete treeEtap;
    if(file)                delete file;
}

Bool_t	  GTreeManager::OpenOutputFile(const char* treefile)
{
    file		= TFile::Open(treefile, "UPDATE");
	if(!file) return kFALSE;
    if(file->IsZombie()) return kFALSE;
	cout << "file " << treefile << " created." << endl;
	return kTRUE;
}


Bool_t  GTreeManager::InitTreePi0()
{
	if(!file) return kFALSE;
	file->cd();
	treePi0	= new TTree("treePi0", "treePi0");
	if(!treePi0) return kFALSE;
	cout << "treePi0 created." << endl;
	
	treePi0->Branch("rawEventNumber", &rawEventNumber, "rawEventNumber/i");
    treePi0->Branch("n", &pi0.n, "n/b");
    treePi0->Branch("child1", pi0.child1, "child1[n]/b");
    treePi0->Branch("child2", pi0.child2, "child2[n]/b");
	
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreePi0()
{
	if(!file) return kFALSE; 
	treePi0 = (TTree*)file->Get("treePi0");
	if(!treePi0)	return kFALSE;
	cout << "treePi0 opened." << endl;
	return kTRUE;
}

Bool_t    GTreeManager::InitTreeEta()
{
	if(!file) return kFALSE;
	file->cd();
	treeEta	= new TTree("treeEta", "treeEta");
	if(!treeEta) return kFALSE;
	cout << "treeEta created." << endl;
	
	treeEta->Branch("rawEventNumber", &rawEventNumber, "rawEventNumber/i");
    treeEta->Branch("n2g", &eta.n2g, "n2g/b");
    treeEta->Branch("child2g1", eta.child2g1, "child2g1[n2g]/b");
    treeEta->Branch("child2g2", eta.child2g2, "child2g2[n2g]/b");
	
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreeEta()
{
	if(!file) return kFALSE; 
	treeEta = (TTree*)file->Get("treeEta");
	if(!treeEta) return kFALSE;
	cout << "treeEta opened." << endl;
	return kTRUE;
}

Bool_t    GTreeManager::InitTreeEtap()
{
	if(!file) return kFALSE;
	file->cd();
	treeEtap	= new TTree("treeEtap", "treeEtap");
	if(!treeEtap) return kFALSE;
	cout << "treeEtap created." << endl;
	
	treeEtap->Branch("rawEventNumber", &rawEventNumber, "rawEventNumber/i");
    treeEtap->Branch("n2g", &etap.n2g, "n2g/b");
    treeEtap->Branch("child2g1", etap.child2g1, "child2g1[n2g]/b");
    treeEtap->Branch("child2g2", etap.child2g2, "child2g2[n2g]/b");
	
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreeEtap()
{
	if(!file) return kFALSE; 
	treeEtap = (TTree*)file->Get("treeEtap");
	if(!treeEtap) return kFALSE;
	cout << "treeEtap opened." << endl;
	return kTRUE;
}



void	GTreeManager::Reconstruct()
{
	printf("I'm in yo TreeManager");
	printf("No Reconstruct method found in Parent\n");
}


Bool_t	GTreeManager::Write()
{
	if(!file)		return kFALSE;
	file->cd();
	if(treePi0)		treePi0->Write();
	if(treeEta)		treeEta->Write();
	if(treeEtap)	treeEtap->Write();
}

void	GTreeManager::Print()
{
	GInputTreeManager::Print();
	cout << "nPi0: " << (int)pi0.n << "\tnEta: " << (int)eta.n2g << "\tnEtap: " << (int)etap.n2g << endl;
}

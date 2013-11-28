
#include "GTreeManager.h"

GTreeManager::GTreeManager() :	
				file(0),
                treePi0(0),
                treeEta(0),
                treeEtap(0)
{   
	Pi0Childs		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Eta2gChilds		= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
    Etap2gChilds	= new UChar_t[GINPUTTREEMANAGER_MAX_PARTICLE];
}

GTreeManager::~GTreeManager()
{
	Reset();
}

void	GTreeManager::Reset()
{
    if(treePi0) 	 delete treePi0;
    if(treeEta) 	 delete treeEta;
    if(treeEtap) 	 delete treeEtap;
    if(file)		 delete file;
}

Bool_t	  GTreeManager::OpenOutputFile(const char* treefile)
{
	file		= TFile::Open(treefile);
	if(file)
	{
		if(file->IsZombie()) return kFALSE;
		cout << "file " << treefile << " opened." << endl;
		return kTRUE;
	}
	
	file	= new TFile(treefile,"CREATE");
	if(!file) return kFALSE;
	cout << "file " << treefile << " created." << endl;
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreePi0()
{
	if(!file) return kFALSE; 
	
	treePi0 = (TTree*)file->Get("treePi0");
	if(treePi0)
	{
		cout << "treePi0 opened." << endl;
		return kTRUE;
	}
	
	treePi0	= new TTree("treePi0", "treePi0");
	if(!treePi0) return kFALSE;
	cout << "treePi0 created." << endl;
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreeEta()
{
	if(!file) return kFALSE; 
	
	treeEta = (TTree*)file->Get("treeEta");
	if(treeEta)
	{
		cout << "treeEta opened." << endl;
		return kTRUE;
	}
	
	treeEta	= new TTree("treeEta", "treeEta");
	if(!treeEta) return kFALSE;
	cout << "treeEta created." << endl;
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreeEtap()
{
	if(!file) return kFALSE; 
	
	treeEtap = (TTree*)file->Get("treeEtap");
	if(treeEtap)
	{
		cout << "treeEtap opened." << endl;
		return kTRUE;
	}
	
	treeEtap	= new TTree("treeEtap", "treeEtap");
	if(!treeEtap) return kFALSE;
	cout << "treeEtap created." << endl;
	return kTRUE;
}

Bool_t	GTreeManager::GetEntry()
{	
	if(actualEvent < firstValidEvent) actualEvent = firstValidEvent - 1;
	else if(actualEvent >= lastValidEvent) return kFALSE;
	actualEvent++;
	
	GInputTreeManager::GetEntry();
	
    if (treePi0) 	treePi0->GetEntry(actualEvent);
	if (treeEta) 	treeEta->GetEntry(actualEvent);
	if (treeEtap) 	treeEtap->GetEntry(actualEvent);

	return kTRUE;
}

Bool_t	GTreeManager::GetEntry(const Int_t index)
{
		printf("GTreeManager::GetEntry\n");
	if(index < firstValidEvent) return kFALSE;
	if(index > lastValidEvent)  return kFALSE;
	
	actualEvent = index;

	GInputTreeManager::GetEntry();
	
    if (treePi0) 	treePi0->GetEntry(actualEvent);
	if (treeEta) 	treeEta->GetEntry(actualEvent);
	if (treeEtap) 	treeEtap->GetEntry(actualEvent);

	return kTRUE;
}

void	GTreeManager::TraverseEntries(const Int_t min, const Int_t max)
{
	Int_t checkedmin = min;
	Int_t checkedmax = max;
	if(checkedmin < firstValidEvent) 	 checkedmin = firstValidEvent;
	if(checkedmin > lastValidEvent)  	 checkedmin = lastValidEvent;
	if(checkedmax < checkedmin) 	 	 checkedmax = checkedmin;
	if(checkedmax > lastValidEvent) 	 checkedmax = lastValidEvent;
	
	printf("checkedmin: %d\n", checkedmin);
	printf("checkedmax: %d\n", checkedmax);
	actualEvent = checkedmin;
	for(int i=checkedmin; i<=checkedmax; i++)
	{
		printf("TraverseEntries\n");
		GetEntry();
		Reconstruct();
	}
}


void    GTreeManager::Analysis(const char* inputtreefile, const char* outputfilename, const Int_t min, const Int_t max)
{
	if(!OpenInputFile(inputtreefile))	
    {
		printf("could not open input file");
		return;
	}
    if(!OpenOutputFile(outputfilename))	
    {
		printf("could not open output file");
		return;
	}

	OpenTreeDetectorHits();
	FindValidEvents();
	if(max<0)
		TraverseEntries(min, lastValidEvent);
	else
		TraverseEntries(min, max);
}


void	GTreeManager::Reconstruct()
{
	printf("I'm in yo TreeManager");
	printf("No reconstruction class found in Parent\n");
}



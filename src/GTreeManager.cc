
#include "GTreeManager.h"

GTreeManager::GTreeManager() :	
				file(0),
                treeParticle(0)
{   
}

GTreeManager::~GTreeManager()
{
	Reset();
}

void	GTreeManager::Reset()
{
    if(treeParticle) 	 delete treeParticle;
    if(file)			 delete file;
}

Bool_t	  GTreeManager::OpenOutputFile(const char* treefile)
{
	file	= TFile::Open(treefile);
	if(!file) return kFALSE;
	if(file->IsZombie()) return kFALSE;
	cout << "file " << treefile << " opened." << endl;
	
	return kTRUE;
}

Bool_t	GTreeManager::GetEntry()
{	
	if(actualEvent < firstValidEvent) actualEvent = firstValidEvent - 1;
	else if(actualEvent >= lastValidEvent) return kFALSE;
	actualEvent++;
	
    if (treeParticle) 	treeParticle->GetEntry(actualEvent);

    GInputTreeManager::GetEntry();
	
	return kTRUE;
}

Bool_t	GTreeManager::GetEntry(const Int_t index)
{
	if(index < firstValidEvent) return kFALSE;
	if(index > lastValidEvent)  return kFALSE;
	
	actualEvent = index;
	
    if (treeParticle) 	treeParticle->GetEntry(actualEvent);

    GInputTreeManager::GetEntry();
	
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
	for(int i=checkedmin; i<=checkedmax; i++)
	{
		actualEvent = i;
		GetEntry(i);
		Reconstruct();
	}
}



void    GTreeManager::Analysis(const char* inputtreefile, const char* outputfilename)
{
    if(outputfilename)
        OpenOutputFile(outputfilename);
    OpenInputFile(inputtreefile);

	OpenTreeDetectorHits();
	FindValidEvents();
	TraverseEntries();
}


void	GTreeManager::Reconstruct()
{
	printf("I'm in yo TreeManager");
	printf("No reconstruction class found in Parent\n");
}


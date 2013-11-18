//*************************************************************************
//* Author: Patrik Ott
//*************************************************************************

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// GTreeManager                                                          //
//                                                                      //
// This class is organising the output to ROOT files                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include "inc/GTreeManager.h"

GTreeManager::GTreeManager() 	: 	TA2AccessSQL(Name, Analysis),
									file(0),
									treeRawEvent(0),
									treeTagger(0),
									treeTrigger(0),
									treeDetectorHits(0),
									treeScaler(0),
									nParticles(0),
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
                                    nTagged(0),
                                    tagged_ch(0),
                                    tagged_t(0),
                                    nNaI_Hits(0),
                                    NaI_Hits(0),
                                    nPID_Hits(0),
                                    PID_Hits(0),
                                    nWC_Hits(0),
	                                WC_Hits(0),
	                                nBaF2_PbWO4_Hits(0), 
	                                BaF2_PbWO4_Hits(0),
                                    nVeto_Hits(0),
                                    Veto_Hits(0),
                                    ESum(0),
                                    Mult(0),
								    EventNumber(0),
							 	    EventID(0),
								    Scaler(0),
								    firstValidEvent(0),
								    lastValidEvent(0)
								    actualEvent(-1)
{
    Px		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    Py		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    Pz		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    E		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    time	= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    clusterSize	= new UChar_t[GTREEMANAGER_MAX_PARTICLE];
    
    tagged_ch	= new Int_t[GTREEMANAGER_MAX_TAGGER];
    tagged_t	= new Double_t[GTREEMANAGER_MAX_TAGGER];
    
    Apparatus	= new UChar_t[GTREEMANAGER_MAX_PARTICLE];
    d_E		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    WC0_E	= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    WC1_E	= new Double_t[GTREEMANAGER_MAX_PARTICLE];

    WC_Vertex_X	= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Y	= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    WC_Vertex_Z	= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    
    NaI_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    PID_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    WC_Hits		= new Int_t[GTREEMANAGER_MAX_HITS];
    BaF2_PbWO4_Hits = new Int_t[GTREEMANAGER_MAX_HITS];
    Veto_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
   
}

GTreeManager::~GTreeManager()
{
	Reset();
}

void	GTreeManager::Reset()
{
	if(treeRawEvent) 	 delete treeRawEvent;
	if(treeTagger)    	 delete treeTagger;
	if(treeTrigger)  	 delete treeTrigger;
	if(treeDetectorHits) delete treeDetectorHits;
	if(treeScaler) 	 	 delete treeScaler;
    if(file)			 delete file;
}

Bool_t	  GTreeManager::OpenFile(const char* treefile)
{
	file	= TFile::Open(treefile);
	if(!file) return kFALSE;
	cout << "file " << treefile << " opened." << endl;
	
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreeRawEvent()
{
	if(!file) return kFALSE; 
	
	treeRawEvent = (TTree*)file->Get("treeRawEvent");
	if(!treeRawEvent) return kFALSE;
	cout << "treeRawEvent opened." << endl;
	
	treeRawEvent->SetBranchAddress("nParticles",&nParticles);
	treeRawEvent->SetBranchAddress("Px", Px);
	treeRawEvent->SetBranchAddress("Py", Py);
	treeRawEvent->SetBranchAddress("Pz", Pz);
	treeRawEvent->SetBranchAddress("E",  E);	
	treeRawEvent->SetBranchAddress("time", time);
	treeRawEvent->SetBranchAddress("clusterSize", clusterSize);
	treeRawEvent->SetBranchAddress("Apparatus", Apparatus);
	treeRawEvent->SetBranchAddress("d_E", d_E);	
	treeRawEvent->SetBranchAddress("WC0_E", WC0_E);	
	treeRawEvent->SetBranchAddress("WC1_E", WC1_E);
	treeRawEvent->SetBranchAddress("WC_Vertex_X", WC_Vertex_X);	
	treeRawEvent->SetBranchAddress("WC_Vertex_Y", WC_Vertex_Y);	
	treeRawEvent->SetBranchAddress("WC_Vertex_Z", WC_Vertex_Z);	
	
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreeTagger()
{
	if(!file) return kFALSE;
	
	treeTagger = (TTree*)file->Get("treeTagger");
	if(!treeTagger) return kFALSE;
	cout << "treeTagger opened." << endl;
    
	treeTagger->SetBranchAddress("nTagged", &nTagged);
	treeTagger->SetBranchAddress("tagged_ch", tagged_ch);
	treeTagger->SetBranchAddress("tagged_t", tagged_t);
	
	return kTRUE;	
}

Bool_t    GTreeManager::OpenTreeTrigger()
{
	if(!file) return kFALSE;

	treeTrigger = (TTree*)file->Get("treeTrigger");
	if(!treeTrigger) return kFALSE;
	cout << "treeTrigger opened." << endl;

	treeTrigger->SetBranchAddress("ESum", &ESum);
	treeTrigger->SetBranchAddress("Mult", &Mult);
	
	return kTRUE;
}

Bool_t    GTreeManager::OpenTreeDetectorHits()
{
	if(!file) return kFALSE;

	treeDetectorHits = (TTree*)file->Get("treeDetectorHits");
	if(!treeDetectorHits) return kFALSE;
	cout << "treeDetectorHits opened." << endl;
	
	treeDetectorHits->SetBranchAddress("nNaI_Hits", &nNaI_Hits);
	treeDetectorHits->SetBranchAddress("NaI_Hits", NaI_Hits);
	treeDetectorHits->SetBranchAddress("nPID_Hits", &nPID_Hits);
	treeDetectorHits->SetBranchAddress("PID_Hits", PID_Hits);
	treeDetectorHits->SetBranchAddress("nWC_Hits", &nWC_Hits);
	treeDetectorHits->SetBranchAddress("WC_Hits", WC_Hits);
	treeDetectorHits->SetBranchAddress("nBaF2_PbWO4_Hits", &nBaF2_PbWO4_Hits);
	treeDetectorHits->SetBranchAddress("BaF2_PbWO4_Hits", BaF2_PbWO4_Hits);
	treeDetectorHits->SetBranchAddress("nVeto_Hits", &nVeto_Hits);
	treeDetectorHits->SetBranchAddress("Veto_Hits", Veto_Hits);
	
	return kTRUE;	
}

Bool_t    GTreeManager::OpenTreeScaler()
{
	if(!file) return kFALSE;

	treeScaler = (TTree*)file->Get("treeScaler");
	if(!treeScaler) return kFALSE;
	cout << "treeScaler opened." << endl;
	
	treeScaler->SetBranchAddress("eventNumber", &EventNumber);
	treeScaler->SetBranchAddress("eventID", &EventID);
	Scaler		= new UInt_t[treeScaler->GetLeaf("Scaler")->GetLen()];
	treeScaler->SetBranchAddress("Scaler", Scaler);
	
	return kTRUE;
}	

Bool_t	GTreeManager::FindValidEvents()
{
	if(!treeScaler) OpenTreeScaler();

	if(treeScaler)
	{
		treeScaler->GetEntry(0);
		firstValidEvent	= EventNumber;
		treeScaler->GetEntry(treeScaler->GetEntries()-1);
		lastValidEvent	= EventNumber-1;
		cout << "Valid events determined from scaler tree" << endl;
		cout << "Events from " << firstValidEvent << 
				" to " << lastValidEvent << " are valid." << endl;
		return kTRUE;	
	}
	
	cout << "Valid events count not be determined from scaler tree" << endl;
	
	firstValidEvent = 0;

	if (treeRawEvent)
	{
		lastValidEvent = (Int_t)treeRawEvent->GetEntries();
		cout << "Total #Events deterimed from treeRawEvent" << endl;
		return kTRUE;
	}
	if (treeTagger)
	{
		lastValidEvent = (Int_t)treeTagger->GetEntries();
		cout << "Total #Events deterimed from treeTagger" << endl;
		return kTRUE;
	}
	if (treeTrigger)
	{
		lastValidEvent = (Int_t)treeTrigger->GetEntries();
		cout << "Total #Events deterimed from treeTrigger" << endl;
		return kTRUE;
	}
	if (treeDetectorHits)
	{
		lastValidEvent = (Int_t)treeDetectorHits->GetEntries();
		cout << "Total #Events deterimed from treeDetectorHits" << endl;
		return kTRUE;
	}		

	return kFALSE;
}

Bool_t	GTreeManager::GetEntry()
{	
	if(!actualEvent) actualEvent = -1;
	
	if(actualEvent < firstValidEvent) actualEvent = firstValidEvent;
	else if(actualEvent < lastValidEvent) actualEvent++;
	else return kFALSE;
	
	if (treeRawEvent) 		treeRawEvent->GetEntry(actualEvent);
	if (treeTagger) 		treeTagger->GetEntry(actualEvent);
	if (treeTrigger) 		treeTrigger->GetEntry(actualEvent);
	if (treeDetectorHits) 	treeDetectorHits->GetEntry(actualEvent);
	if (treeScaler) 	 	treeScaler->GetEntry(actualEvent);
	
	return kTRUE;
}

Bool_t	GTreeManager::GetEntry(const Int_t index)
{
	if(index < firstValidEvent) return kFALSE;
	if(index > lastValidEvent)  return kFALSE;
	
	actualEvent = index;
	treeEvent->GetEntry(index);
	treeTrigger->GetEntry(index)
	return kTRUE;
}

void	GTreeManager::TraverseEntries()
{
	GTreeManager::GetEntry();
	Reconstruct();
}

void	GTreeManager::TraverseEntries(const Int_t min, const Int_t max)
{
	Int_t checkedmin = min;
	Int_t checkedmax = max;
	if(checkedmin < firstValidEvent) 	 checkedmin = firstValidEvent;
	if(checkedmin > lastValidEvent)  	 checkedmin = lastValidEvent;
	if(checkedmax < checkedmin) 	 	 checkedmax = checkedmin;
	else if(checkedmax > lastValidEvent) checkedmax = lastValidEvent;
	
	printf("checkedmin: %d\n", checkedmin);
	printf("checkedmax: %d\n", checkedmax);
	for(int i=checkedmin; i<=checkedmax; i++)
	{
		actualEvent = i;
		treeEvent->GetEntry(i);
		Reconstruct();
	}
}

void	GTreeManager::Reconstruct()
{
	printf("%d\n", actualEvent);
	//for(int i=0; i<1000; i++);
}

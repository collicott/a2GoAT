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

GTreeManager::GTreeManager() 										: 	TA2AccessSQL(Name, Analysis),
																			file(0),
																			treeEvent(0),
																			treeScaler(0),
																			nParticles(0),
																			Px(0),
																			Py(0),
																			Pz(0),
																			E(0),
																			time(0),
																			clusterSize(0),
																			nTagged(0),
																			tagged_ch(0),
																			tagged_t(0),
																			NaI_E(0),
																			BaF2_E(0),
																			PbWO4_E(0),
																			PID_E(0),
																			Veto_E(0),
																			WC0_E(0),
																			WC1_E(0),
																			nNaI_Hits(0),
																			NaI_Hits(0),
																			nBaF2_Hits(0),
																			BaF2_Hits(0),
																			nPbWO4_Hits(0),
																			PbWO4_Hits(0),
																			nPID_Hits(0),
																			PID_Hits(0),
																			nVeto_Hits(0),
																			Veto_Hits(0),
																			nWC0_Hits(0),
																			WC0_Hits(0),
																			nWC1_Hits(0),
																			WC1_Hits(0),
																			ESum(0),
																			CBMult(0),
																			TAPSMult(0),
																			EventNumber(0),
																			EventID(0),
																			Scaler(0),
																			firstValidEvent(0),
																			lastValidEvent(0)
																			actualEvent(-1)
{
    Px			= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    Py			= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    Pz			= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    E			= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    time		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    clusterSize	= new UChar_t[GTREEMANAGER_MAX_PARTICLE];
    
    tagged_ch	= new Int_t[GTREEMANAGER_MAX_TAGGER];
    tagged_t	= new Double_t[GTREEMANAGER_MAX_TAGGER];
    
    Apparatus	= new UChar_t[GTREEMANAGER_MAX_PARTICLE];
    d_E			= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    WC0_E		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    WC1_E		= new Double_t[GTREEMANAGER_MAX_PARTICLE];
    
    NaI_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    BaF2_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    PbWO4_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    PID_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    Veto_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    WC0_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
    WC1_Hits	= new Int_t[GTREEMANAGER_MAX_HITS];
   
}


GTreeManager::~GTreeManager()
{
	Reset();
}

void	GTreeManager::Reset()
{
	if(treeEvent)
		delete treeEvent;
	if(treeScaler)
		delete treeScaler;
    if(file)
		delete file;
}

Bool_t    GTreeManager::OpenTree(const char* treefile)
{
	Reset();
    file		= TFile::Open(treefile);
    if(!file)
		return kFALSE;
	cout << "file " << treefile << " opened." << endl;
	
	treeEvent	= (TTree*)file->Get("treeEvent");
	if(!treeEvent)
		return kFALSE;
	cout << "tree treeEvent opened." << endl;
	
	treeScaler	= (TTree*)file->Get("treeScaler");
	if(!treeScaler)
		return kFALSE;
	cout << "tree treeScaler opened." << endl;
	
	lastValidEvent = treeEvent->GetEntries() - 1;
	treeEvent->SetBranchAddress("nParticles",&nParticles);
	treeEvent->SetBranchAddress("Px", Px);
	treeEvent->SetBranchAddress("Py", Py);
	treeEvent->SetBranchAddress("Pz", Pz);
	treeEvent->SetBranchAddress("E",  E);	
	treeEvent->SetBranchAddress("time", time);
	treeEvent->SetBranchAddress("clusterSize", clusterSize);
    
	treeEvent->SetBranchAddress("nTagged", &nTagged);
	treeEvent->SetBranchAddress("tagged_ch", tagged_ch);
	treeEvent->SetBranchAddress("tagged_t", tagged_t);
    
	treeEvent->SetBranchAddress("Apparatus", Apparatus);
	treeEvent->SetBranchAddress("d_E", d_E);	
	treeEvent->SetBranchAddress("WC0_E", WC0_E);	
	treeEvent->SetBranchAddress("WC1_E", WC1_E);
	treeEvent->SetBranchAddress("WC_Vertex_X", WC_Vertex_X);	
	treeEvent->SetBranchAddress("WC_Vertex_Y", WC_Vertex_Y);	
	treeEvent->SetBranchAddress("WC_Vertex_Z", WC_Vertex_Z);	
	
	treeEvent->SetBranchAddress("nNaI_Hits", &nNaI_Hits);
	treeEvent->SetBranchAddress("NaI_Hits", NaI_Hits);
	treeEvent->SetBranchAddress("nBaF2_Hits", &nBaF2_Hits);
	treeEvent->SetBranchAddress("BaF2_Hits", BaF2_Hits);
	treeEvent->SetBranchAddress("nPbWO4_Hits", &nPbWO4_Hits);
	treeEvent->SetBranchAddress("PbWO4_Hits", PbWO4_Hits);
	treeEvent->SetBranchAddress("nPID_Hits", &nPID_Hits);
	treeEvent->SetBranchAddress("PID_Hits", PID_Hits);
	treeEvent->SetBranchAddress("nVeto_Hits", &nVeto_Hits);
	treeEvent->SetBranchAddress("Veto_Hits", Veto_Hits);
	treeEvent->SetBranchAddress("nWC0_Hits", &nWC0_Hits);
	treeEvent->SetBranchAddress("WC0_Hits", WC0_Hits);
	treeEvent->SetBranchAddress("nWC1_Hits", &nWC1_Hits);
	treeEvent->SetBranchAddress("WC1_Hits", WC1_Hits);
	
	treeEvent->SetBranchAddress("ESum", &ESum);
	treeEvent->SetBranchAddress("CBMult", &CBMult);
	treeEvent->SetBranchAddress("TAPSMult", &TAPSMult);
	
	treeScaler->SetBranchAddress("eventNumber", &EventNumber);
	treeScaler->SetBranchAddress("eventID", &EventID);
	Scaler		= new UInt_t[treeScaler->GetLeaf("Scaler")->GetLen()];
	treeScaler->SetBranchAddress("Scaler", Scaler);
	
	return FindValidEvents();
}

Bool_t	GTreeManager::FindValidEvents()
{
	treeScaler->GetEntry(0);
	firstValidEvent	= EventNumber;
	treeScaler->GetEntry(treeScaler->GetEntries()-1);
	lastValidEvent	= EventNumber-1;
	
	cout << "Events from " << firstValidEvent << " to " << lastValidEvent << " are valid." << endl;
	
	return kTRUE;
	
}

Bool_t	GTreeManager::GetEntry()
{
	if(actualEvent < firstValidEvent)
		actualEvent = firstValidEvent;
	else if(actualEvent < lastValidEvent)
		actualEvent++;
	else
		return kFALSE;
	
	treeEvent->GetEntry(actualEvent);
	return kTRUE;
}

Bool_t	GTreeManager::GetEntry(const Int_t index)
{
	if(index < firstValidEvent)
		return kFALSE;
	if(index > lastValidEvent)
		return kFALSE;
	
	actualEvent = index;
	treeEvent->GetEntry(index);
	return kTRUE;
}

void	GTreeManager::TraverseEntries(const Int_t min, const Int_t max)
{
	Int_t checkedmin = min;
	Int_t checkedmax = max;
	if(checkedmin < firstValidEvent)
		checkedmin = firstValidEvent;
	if(checkedmin > lastValidEvent)
		checkedmin = lastValidEvent;
	if(checkedmax < checkedmin)
		checkedmax = checkedmin;
	else if(checkedmax > lastValidEvent)
		checkedmax = lastValidEvent;
	
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

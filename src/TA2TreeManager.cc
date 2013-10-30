//*************************************************************************
//* Author: Patrik Ott
//*************************************************************************

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TA2TreeManager                                                          //
//                                                                      //
// This class is organising the output to ROOT files                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include "inc/TA2TreeManager.h"

ClassImp(TA2TreeManager)





TA2TreeManager::TA2TreeManager() 										: 	TA2AccessSQL(Name, Analysis),
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
																			WC1_E(0),
																			WC2_E(0),
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
																			nWC1_Hits(0),
																			WC1_Hits(0),
																			nWC2_Hits(0),
																			WC2_Hits(0),
																			ESum(0),
																			CBMult(0),
																			TAPSMult(0),
																			EventNumber(0),
																			EventID(0),
																			Scaler(0)
{
    Px			= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    Py			= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    Pz			= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    E			= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    time		= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    clusterSize	= new UChar_t[TA2TREEMANAGER_MAX_PARTICLE];
    
    tagged_ch	= new Int_t[TA2TREEMANAGER_MAX_TAGGER];
    tagged_t	= new Double_t[TA2TREEMANAGER_MAX_TAGGER];
    
    Apparatus	= new UChar_t[TA2TREEMANAGER_MAX_PARTICLE];
    d_E			= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    WC1_E		= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    WC2_E		= new Double_t[TA2TREEMANAGER_MAX_PARTICLE];
    
    NaI_Hits	= new Int_t[TA2TREEMANAGER_MAX_HITS];
    BaF2_Hits	= new Int_t[TA2TREEMANAGER_MAX_HITS];
    PbWO4_Hits	= new Int_t[TA2TREEMANAGER_MAX_HITS];
    PID_Hits	= new Int_t[TA2TREEMANAGER_MAX_HITS];
    Veto_Hits	= new Int_t[TA2TREEMANAGER_MAX_HITS];
    WC1_Hits	= new Int_t[TA2TREEMANAGER_MAX_HITS];
    WC2_Hits	= new Int_t[TA2TREEMANAGER_MAX_HITS];
}


TA2TreeManager::~TA2TreeManager()
{
	Reset();
}

void	TA2TreeManager::Reset()
{
	if(treeEvent)
		delete treeEvent;
	if(treeScaler)
		delete treeScaler;
    if(file)
		delete file;
}

Bool_t    TA2TreeManager::OpenTree(const char* treefile)
{
	Reset();
    file		= TFile::Open(treefile);
    if(!file)
		return kFALSE;
	treeEvent	= (TTree*)file->Get("treeEvent");
	if(!treeEvent)
		return kFALSE;
	treeScaler	= (TTree*)file->Get("treeScaler");
	if(!treeScaler)
		return kFALSE;
	
	treeEvent->SetBranchAddress("nParticles",&nParticles);
	treeEvent->SetBranchAddress("Px", &Px);
	treeEvent->SetBranchAddress("Py", &Py);
	treeEvent->SetBranchAddress("Pz", &Pz);
	treeEvent->SetBranchAddress("E",  &E);	
	treeEvent->SetBranchAddress("time", &time);
	treeEvent->SetBranchAddress("clusterSize", &clusterSize);
    
	treeEvent->SetBranchAddress("nTagged", &nTagged);
	treeEvent->SetBranchAddress("tagged_ch", &tagged_ch);
	treeEvent->SetBranchAddress("tagged_t", &tagged_t);
    
	treeEvent->SetBranchAddress("Apparatus", &Apparatus);
	treeEvent->SetBranchAddress("d_E", &d_E);	
	treeEvent->SetBranchAddress("WC1_E", &WC1_E);	
	treeEvent->SetBranchAddress("WC2_E", &WC2_E);
	treeEvent->SetBranchAddress("WC_Vertex_X", &WC_Vertex_X);	
	treeEvent->SetBranchAddress("WC_Vertex_Y", &WC_Vertex_Y);	
	treeEvent->SetBranchAddress("WC_Vertex_Z", &WC_Vertex_Z);	
	
	treeEvent->SetBranchAddress("nNaI_Hits", &nNaI_Hits);
	treeEvent->SetBranchAddress("NaI_Hits", &NaI_Hits);
	treeEvent->SetBranchAddress("nBaF2_Hits", &nBaF2_Hits);
	treeEvent->SetBranchAddress("BaF2_Hits", &BaF2_Hits);
	treeEvent->SetBranchAddress("nPbWO4_Hits", &nPbWO4_Hits);
	treeEvent->SetBranchAddress("PbWO4_Hits", &PbWO4_Hits);
	treeEvent->SetBranchAddress("nPID_Hits", &nPID_Hits);
	treeEvent->SetBranchAddress("PID_Hits", &PID_Hits);
	treeEvent->SetBranchAddress("nVeto_Hits", &nVeto_Hits);
	treeEvent->SetBranchAddress("Veto_Hits", &Veto_Hits);
	treeEvent->SetBranchAddress("nWC1_Hits", &nWC1_Hits);
	treeEvent->SetBranchAddress("WC1_Hits", &WC1_Hits);
	treeEvent->SetBranchAddress("nWC2_Hits", &nWC2_Hits);
	treeEvent->SetBranchAddress("WC2_Hits", &WC2_Hits);
	
	treeEvent->SetBranchAddress("ESum", &ESum);
	treeEvent->SetBranchAddress("CBMult", &CBMult);
	treeEvent->SetBranchAddress("TAPSMult", &TAPSMult);
	
	treeScaler->SetBranchAddress("eventNumber", &EventNumber);
	treeScaler->SetBranchAddress("eventID", &EventID);
	treeScaler->SetBranchAddress("Scaler", &Scaler);
}



#include "GAcquTree.h"

using namespace std;

GAcquTree::GAcquTree() :
                /*treeRawEvent(0),
				treeTagger(0),
				treeTrigger(0),
				treeDetectorHits(0),
                treeScaler(0),*/
				nParticles(0),
				Ek(0),
				Mass(0),
				Theta(0),
				Phi(0),
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
				photonbeam_E(0),
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
                NScaler(0)
{
        Ek				= new Double_t[GAcquTree_MAX_PARTICLE];
        Theta			= new Double_t[GAcquTree_MAX_PARTICLE];
        Phi				= new Double_t[GAcquTree_MAX_PARTICLE];
        time			= new Double_t[GAcquTree_MAX_PARTICLE];
        clusterSize		= new UChar_t[GAcquTree_MAX_PARTICLE];
        Mass			= new Double_t[GAcquTree_MAX_PARTICLE];
		
        tagged_ch		= new Int_t[GAcquTree_MAX_TAGGER];
        tagged_t		= new Double_t[GAcquTree_MAX_TAGGER];
        photonbeam_E	= new Double_t[GAcquTree_MAX_TAGGER];
        
    
        Apparatus		= new UChar_t[GAcquTree_MAX_PARTICLE];
        d_E				= new Double_t[GAcquTree_MAX_PARTICLE];
        WC0_E			= new Double_t[GAcquTree_MAX_PARTICLE];
        WC1_E			= new Double_t[GAcquTree_MAX_PARTICLE];

        WC_Vertex_X		= new Double_t[GAcquTree_MAX_PARTICLE];
        WC_Vertex_Y		= new Double_t[GAcquTree_MAX_PARTICLE];
        WC_Vertex_Z		= new Double_t[GAcquTree_MAX_PARTICLE];
    
        NaI_Hits		= new Int_t[GAcquTree_MAX_HITS];
        PID_Hits		= new Int_t[GAcquTree_MAX_HITS];
        WC_Hits			= new Int_t[GAcquTree_MAX_HITS];
        BaF2_PbWO4_Hits = new Int_t[GAcquTree_MAX_HITS];
        Veto_Hits		= new Int_t[GAcquTree_MAX_HITS];
   
}

GAcquTree::~GAcquTree()
{
	Reset();
}

/*void	GAcquTree::Reset()
{
	if(treeRawEvent) 	 delete treeRawEvent;
	if(treeTagger)    	 delete treeTagger;
	if(treeTrigger)  	 delete treeTrigger;
	if(treeDetectorHits) delete treeDetectorHits;
    if(treeScaler) 	 	 delete treeScaler;
}

Bool_t    GAcquTree::OpenTreeRawEvent()
{
    if(!file) return kFALSE;
	
    treeRawEvent = (TTree*)file->Get("treeRawEvent");
	if(!treeRawEvent) return kFALSE;
    cout << "treeRawEvent opened." << endl;
	
	treeRawEvent->SetBranchAddress("nParticles",&nParticles);
	treeRawEvent->SetBranchAddress("Ek",  Ek);	
	treeRawEvent->SetBranchAddress("Theta", Theta);
	treeRawEvent->SetBranchAddress("Phi",  Phi);		
	treeRawEvent->SetBranchAddress("time", time);
	treeRawEvent->SetBranchAddress("clusterSize", clusterSize);
	treeRawEvent->SetBranchAddress("Apparatus", Apparatus);
	treeRawEvent->SetBranchAddress("d_E", d_E);	
	treeRawEvent->SetBranchAddress("WC0_E", WC0_E);	
	treeRawEvent->SetBranchAddress("WC1_E", WC1_E);
	treeRawEvent->SetBranchAddress("WC_Vertex_X", WC_Vertex_X);	
	treeRawEvent->SetBranchAddress("WC_Vertex_Y", WC_Vertex_Y);	
	treeRawEvent->SetBranchAddress("WC_Vertex_Z", WC_Vertex_Z);	

	treeRawEvent_clone = treeRawEvent->CloneTree(0);
	
	return kTRUE;
}

Bool_t    GAcquTree::OpenTreeTagger()
{
    if(!file) return kFALSE;
	
    treeTagger = (TTree*)file->Get("treeTagger");
	if(!treeTagger) return kFALSE;
	cout << "treeTagger opened." << endl;
    
	treeTagger->SetBranchAddress("nTagged", 	&nTagged);
	treeTagger->SetBranchAddress("tagged_ch", 	tagged_ch);
	treeTagger->SetBranchAddress("tagged_t", 	tagged_t);
	treeTagger->SetBranchAddress("photonbeam_E", photonbeam_E);
	
	treeTagger_clone = treeTagger->CloneTree(0);
	
	return kTRUE;	
}

Bool_t    GAcquTree::OpenTreeTrigger()
{
    if(!file) return kFALSE;

    treeTrigger = (TTree*)file->Get("treeTrigger");
	if(!treeTrigger) return kFALSE;
	cout << "treeTrigger opened." << endl;

	treeTrigger->SetBranchAddress("ESum", &ESum);
	treeTrigger->SetBranchAddress("Mult", &Mult);

	treeTrigger_clone = treeTrigger->CloneTree(0);
	
	return kTRUE;
}

Bool_t    GAcquTree::OpenTreeDetectorHits()
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

	treeDetectorHits_clone = treeDetectorHits->CloneTree(0);	
	
	return kTRUE;	
}

Bool_t    GAcquTree::OpenTreeScaler()
{
    if(!file) return kFALSE;
	
    treeScaler = (TTree*)file->Get("treeScaler");
	if(!treeScaler) return kFALSE;
	cout << "treeScaler opened." << endl;
	
	treeScaler->SetBranchAddress("eventNumber", &EventNumber);
	treeScaler->SetBranchAddress("eventID", &EventID);
	treeScaler->SetBranchAddress("Scaler", Scaler);
	NScaler = treeScaler->GetLeaf("Scaler")->GetLen();

	treeScaler_clone = treeScaler->CloneTree(0);
	
	return kTRUE;
}	

Bool_t    GAcquTree::CloseTreeRawEvent()
{
    if(treeRawEvent)        delete treeRawEvent;
    if(treeRawEvent_clone)  delete treeRawEvent_clone;
}

Bool_t    GAcquTree::CloseTreeTagger()
{
    if(treeTagger)        delete treeTagger;
    if(treeTagger_clone)  delete treeTagger_clone;
}

Bool_t    GAcquTree::CloseTreeTrigger()
{
    if(treeTrigger)        delete treeTrigger;
    if(treeTrigger_clone)  delete treeTrigger_clone;
}

Bool_t    GAcquTree::CloseTreeDetectorHits()
{
    if(treeDetectorHits)        delete treeDetectorHits;
    if(treeDetectorHits_clone)  delete treeDetectorHits_clone;
}

Bool_t    GAcquTree::CloseTreeScaler()
{
    if(treeScaler)        delete treeScaler;
    if(treeScaler_clone)  delete treeScaler_clone;
}

Bool_t	GAcquTree::FindValidEvents()
{
	if(!treeScaler) OpenTreeScaler();

	if(treeScaler)
	{
		treeScaler->GetEntry(0);
        firstEvent	= EventNumber;
		treeScaler->GetEntry(treeScaler->GetEntries()-1);
        lastEvent	= EventNumber-1;
		cout << "Valid events determined from scaler tree" << endl;
        cout << "Events from " << firstEvent <<
                " to " << lastEvent << " are valid." << endl;
		return kTRUE;	
	}
	
	cout << "Valid events count not be determined from scaler tree" << endl;
	
    firstEvent = 0;

	if (treeRawEvent)
	{
        lastEvent = (Int_t)treeRawEvent->GetEntries();
		cout << "Total #Events deterimed from treeRawEvent" << endl;
        cout << "Events from " << firstEvent <<
                " to " << lastEvent << " are valid." << endl;
		return kTRUE;
	}
	if (treeTagger)
	{
        lastEvent = (Int_t)treeTagger->GetEntries();
		cout << "Total #Events deterimed from treeTagger" << endl;
        cout << "Events from " << firstEvent <<
                " to " << lastEvent << " are valid." << endl;
		return kTRUE;
	}
	if (treeTrigger)
	{
        lastEvent = (Int_t)treeTrigger->GetEntries();
		cout << "Total #Events deterimed from treeTrigger" << endl;
        cout << "Events from " << firstEvent <<
                " to " << lastEvent << " are valid." << endl;
		return kTRUE;
	}
	if (treeDetectorHits)
	{
        lastEvent = (Int_t)treeDetectorHits->GetEntries();
		cout << "Total #Events deterimed from treeDetectorHits" << endl;
        cout << "Events from " << firstEvent <<
                " to " << lastEvent << " are valid." << endl;
		return kTRUE;
	}		

	return kFALSE;
}

void GAcquTree::GetEntryFast()
{
    actualEvent++;
    if (treeRawEvent)       treeRawEvent->GetEntry(actualEvent);
    if (treeTagger)         treeTagger->GetEntry(actualEvent);
    if (treeTrigger)        treeTrigger->GetEntry(actualEvent);
    if (treeDetectorHits) 	treeDetectorHits->GetEntry(actualEvent);
}

Bool_t	GAcquTree::GetEntry()
{
    if(actualEvent < firstEvent) actualEvent = firstEvent - 1;
    else if(actualEvent >= lastEvent) return kFALSE;
    actualEvent++;
	
    if (treeRawEvent)       treeRawEvent->GetEntry(actualEvent);
    if (treeTagger)         treeTagger->GetEntry(actualEvent);
    if (treeTrigger)        treeTrigger->GetEntry(actualEvent);
    if (treeDetectorHits) 	treeDetectorHits->GetEntry(actualEvent);

	return kTRUE;
}

Bool_t	GAcquTree::GetEntry(const Int_t index)
{
	if (treeRawEvent)       treeRawEvent->GetEntry(index);
    if (treeTagger)         treeTagger->GetEntry(index);
    if (treeTrigger)        treeTrigger->GetEntry(index);
	if (treeDetectorHits) 	treeDetectorHits->GetEntry(index);

	return kTRUE;
}


Bool_t	GAcquTree::FillEvent()
{
    // Fill event into tree
    if(treeRawEvent_clone)			treeRawEvent_clone->Fill();

    if(treeTagger_clone) 			treeTagger_clone->Fill();
    if(treeTrigger_clone)			treeTrigger_clone->Fill();
    if(treeScaler_clone)			treeScaler_clone->Fill();
    if(treeDetectorHits_clone)		treeDetectorHits_clone->Fill();

    return kTRUE;
}

Bool_t  GAcquTree::WriteTrees()
{
    if(!file) return kFALSE;
    file->cd();

    // Write trees to file
    if(treeRawEvent_clone)          treeRawEvent_clone->Write();
    if(treeTagger_clone)			treeTagger_clone->Write();
    if(treeTrigger_clone)			treeTrigger_clone->Write();
    if(treeScaler_clone)			treeScaler_clone->Write();
    if(treeDetectorHits_clone)		treeDetectorHits_clone->Write();

    return kTRUE;
}

void	GAcquTree::Print()
{
    cout << "Event Number " << actualEvent << " with " << nParticles << " Hits" << endl;
}*/

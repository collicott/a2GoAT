
#include "GAcquTreeManager.h"

GAcquTreeManager::GAcquTreeManager() :
				AcquFile(0),
				treeRawEvent(0),
				treeTagger(0),
				treeTrigger(0),
				treeDetectorHits(0),
				treeScaler(0),
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
				NScaler(0),
				CheckCBStability(0),
				CBHitsThresh1(0),
				CBHitsThresh2(0),
				CBHitsThresh3(0),
				CBHitsThresh4(0),
				firstAcquEvent(0),
				lastAcquEvent(0),
				AcquEvent(-1)
{
        Ek				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
        Theta			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
        Phi				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];        
        time			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
        clusterSize		= new UChar_t[GAcquTREEMANAGER_MAX_PARTICLE];
		Mass			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];      
		
        tagged_ch		= new Int_t[GAcquTREEMANAGER_MAX_TAGGER];
        tagged_t		= new Double_t[GAcquTREEMANAGER_MAX_TAGGER];
        photonbeam_E	= new Double_t[GAcquTREEMANAGER_MAX_TAGGER];
        
    
        Apparatus		= new UChar_t[GAcquTREEMANAGER_MAX_PARTICLE];
        d_E				= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
        WC0_E			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
        WC1_E			= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];

        WC_Vertex_X		= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
        WC_Vertex_Y		= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
        WC_Vertex_Z		= new Double_t[GAcquTREEMANAGER_MAX_PARTICLE];
    
        NaI_Hits		= new Int_t[GAcquTREEMANAGER_MAX_HITS];
        PID_Hits		= new Int_t[GAcquTREEMANAGER_MAX_HITS];
        WC_Hits			= new Int_t[GAcquTREEMANAGER_MAX_HITS];
        BaF2_PbWO4_Hits = new Int_t[GAcquTREEMANAGER_MAX_HITS];
        Veto_Hits		= new Int_t[GAcquTREEMANAGER_MAX_HITS];
   
}

GAcquTreeManager::~GAcquTreeManager()
{
	Reset();
}

void	GAcquTreeManager::Reset()
{
	if(treeRawEvent) 	 delete treeRawEvent;
	if(treeTagger)    	 delete treeTagger;
	if(treeTrigger)  	 delete treeTrigger;
	if(treeDetectorHits) delete treeDetectorHits;
	if(treeScaler) 	 	 delete treeScaler;
    if(AcquFile)		 delete AcquFile;
}

Bool_t	  GAcquTreeManager::OpenAcquFile(const char* treefile)
{
	AcquFile	= TFile::Open(treefile);
	if(!AcquFile) return kFALSE;
	if(AcquFile->IsZombie()) return kFALSE;
	cout << "AcquFile " << treefile << " opened." << endl;
	
	return kTRUE;
}

Bool_t    GAcquTreeManager::OpenTreeRawEvent(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE; 
	
	treeRawEvent = (TTree*)TreeFile->Get("treeRawEvent");
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

Bool_t    GAcquTreeManager::OpenTreeTagger(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE; 
	
	treeTagger = (TTree*)TreeFile->Get("treeTagger");
	if(!treeTagger) return kFALSE;
	cout << "treeTagger opened." << endl;
    
	treeTagger->SetBranchAddress("nTagged", 	&nTagged);
	treeTagger->SetBranchAddress("tagged_ch", 	tagged_ch);
	treeTagger->SetBranchAddress("tagged_t", 	tagged_t);
	treeTagger->SetBranchAddress("photonbeam_E", photonbeam_E);
	
	treeTagger_clone = treeTagger->CloneTree(0);
	
	return kTRUE;	
}

Bool_t    GAcquTreeManager::OpenTreeTrigger(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE; 

	treeTrigger = (TTree*)TreeFile->Get("treeTrigger");
	if(!treeTrigger) return kFALSE;
	cout << "treeTrigger opened." << endl;

	treeTrigger->SetBranchAddress("ESum", &ESum);
	treeTrigger->SetBranchAddress("Mult", &Mult);

	treeTrigger_clone = treeTrigger->CloneTree(0);
	
	return kTRUE;
}

Bool_t    GAcquTreeManager::OpenTreeDetectorHits(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE; 

	treeDetectorHits = (TTree*)TreeFile->Get("treeDetectorHits");
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

Bool_t    GAcquTreeManager::OpenTreeScaler(TFile* TreeFile)
{
	if(!TreeFile) return kFALSE; 
	
	treeScaler = (TTree*)TreeFile->Get("treeScaler");
	if(!treeScaler) return kFALSE;
	cout << "treeScaler opened." << endl;
	
	treeScaler->SetBranchAddress("eventNumber", &EventNumber);
	treeScaler->SetBranchAddress("eventID", &EventID);
	treeScaler->SetBranchAddress("Scaler", Scaler);
	NScaler = treeScaler->GetLeaf("Scaler")->GetLen();

	treeScaler_clone = treeScaler->CloneTree(0);
	
	return kTRUE;
}	

Bool_t	GAcquTreeManager::FindValidAcquEvents()
{
	if(!treeScaler) OpenTreeScaler();

	if(treeScaler)
	{
		treeScaler->GetEntry(0);
		firstAcquEvent	= EventNumber;
		treeScaler->GetEntry(treeScaler->GetEntries()-1);
		lastAcquEvent	= EventNumber-1;
		cout << "Valid events determined from scaler tree" << endl;
		cout << "Events from " << firstAcquEvent << 
				" to " << lastAcquEvent << " are valid." << endl;
		return kTRUE;	
	}
	
	cout << "Valid events count not be determined from scaler tree" << endl;
	
	firstAcquEvent = 0;

	if (treeRawEvent)
	{
		lastAcquEvent = (Int_t)treeRawEvent->GetEntries();
		cout << "Total #Events deterimed from treeRawEvent" << endl;
		cout << "Events from " << firstAcquEvent << 
				" to " << lastAcquEvent << " are valid." << endl;		
		return kTRUE;
	}
	if (treeTagger)
	{
		lastAcquEvent = (Int_t)treeTagger->GetEntries();
		cout << "Total #Events deterimed from treeTagger" << endl;
		cout << "Events from " << firstAcquEvent << 
				" to " << lastAcquEvent << " are valid." << endl;		
		return kTRUE;
	}
	if (treeTrigger)
	{
		lastAcquEvent = (Int_t)treeTrigger->GetEntries();
		cout << "Total #Events deterimed from treeTrigger" << endl;
		cout << "Events from " << firstAcquEvent << 
				" to " << lastAcquEvent << " are valid." << endl;		
		return kTRUE;
	}
	if (treeDetectorHits)
	{
		lastAcquEvent = (Int_t)treeDetectorHits->GetEntries();
		cout << "Total #Events deterimed from treeDetectorHits" << endl;
		cout << "Events from " << firstAcquEvent << 
				" to " << lastAcquEvent << " are valid." << endl;		
		return kTRUE;
	}		

	return kFALSE;
}

void    GAcquTreeManager::CheckRange(Int_t& min, Int_t& max)
{
	if(min < firstAcquEvent) 	 min = firstAcquEvent;
    if(min > lastAcquEvent)  	 min = lastAcquEvent;
    if(max < 0)                  max = lastAcquEvent;
    if(max < min)                max = min;
    if(max > lastAcquEvent) 	 max = lastAcquEvent;
}

void GAcquTreeManager::GetAcquEntryFast()
{
	AcquEvent++;
    if (treeRawEvent)       treeRawEvent->GetEntry(AcquEvent);
    if (treeTagger)         treeTagger->GetEntry(AcquEvent);
    if (treeTrigger)        treeTrigger->GetEntry(AcquEvent);
	if (treeDetectorHits) 	treeDetectorHits->GetEntry(AcquEvent);
}

Bool_t	GAcquTreeManager::GetAcquEntry()
{
	if(AcquEvent < firstAcquEvent) AcquEvent = firstAcquEvent - 1;
	else if(AcquEvent >= lastAcquEvent) return kFALSE;
	AcquEvent++;
	
    if (treeRawEvent)       treeRawEvent->GetEntry(AcquEvent);
    if (treeTagger)         treeTagger->GetEntry(AcquEvent);
    if (treeTrigger)        treeTrigger->GetEntry(AcquEvent);
	if (treeDetectorHits) 	treeDetectorHits->GetEntry(AcquEvent);

	return kTRUE;
}

Bool_t	GAcquTreeManager::GetAcquEntry(const Int_t index)
{
	if (treeRawEvent)       treeRawEvent->GetEntry(index);
    if (treeTagger)         treeTagger->GetEntry(index);
    if (treeTrigger)        treeTrigger->GetEntry(index);
	if (treeDetectorHits) 	treeDetectorHits->GetEntry(index);

	return kTRUE;
}


void	GAcquTreeManager::TraverseAcquEntriesByScalerRead()
{
	if(treeScaler)
	{
		for (int i = 0; i < (treeScaler->GetEntries() - 1); i++)
		{
			// Get current analysis range
			treeScaler->GetEntry(i); 	int min	= EventNumber;
			treeScaler->GetEntry(i+1); 	int max	= EventNumber -1;
			
			// Check Common data issues
			bool analyze = kTRUE;
            try {
                DataChecks(min,max);
            } catch (...) {
                cout << "Entries " << min << " to " << max << "rejected (failed data checks)" << endl;
                analyze = kFALSE;
			}
			
			if(analyze)
			{
				treeScaler_clone->Fill();
				
				for(AcquEvent = min; AcquEvent<=max; AcquEvent++)
				{
					GetAcquEntry(AcquEvent);
					Reconstruct();
				}
			}

		}
	}
	else cout << "Scaler tree could not be found" << endl;
			
}

void 	GAcquTreeManager::DataChecks(const Int_t min, const Int_t max)
{
	if (CheckCBStability)
	{
		if(!CheckCBHits(min,max)) throw 1; 
	}
	
}

Bool_t 	GAcquTreeManager::CheckCBHits(const Int_t min, const Int_t max)
{
	// Check CB hits between scaler reads to eliminate data with CB hole problem 
	Int_t SumQ1 = 0;
	Int_t SumQ2 = 0;
	Int_t SumQ3 = 0;
	Int_t SumQ4 = 0;
	
    for(int i=min; i<=max; i++)
    {	
		if (treeDetectorHits) 	treeDetectorHits->GetEntry(i);
		
		for (int j=0; j<=nNaI_Hits; j++)
		{
			if  (NaI_Hits[j] <  180) SumQ1++;
			if ((NaI_Hits[j] >= 180) && (NaI_Hits[j] < 360)) SumQ2++;
			if ((NaI_Hits[j] >= 360) && (NaI_Hits[j] < 540)) SumQ3++;
			if ((NaI_Hits[j] >= 540) && (NaI_Hits[j] < 720)) SumQ4++;
		}
	}
		
	// Check if sum is above some threshold
	if (SumQ1 < CBHitsThresh1) return kFALSE;
	if (SumQ2 < CBHitsThresh2) return kFALSE;
	if (SumQ3 < CBHitsThresh3) return kFALSE;
	if (SumQ4 < CBHitsThresh4) return kFALSE;
	
	// Set new baseline
	CBHitsThresh1 = int(CBStabilityCutoff*SumQ1);
	CBHitsThresh2 = int(CBStabilityCutoff*SumQ2);
	CBHitsThresh3 = int(CBStabilityCutoff*SumQ3);
	CBHitsThresh4 = int(CBStabilityCutoff*SumQ4);
	
	//cout << min << " " << max << endl;
	return kTRUE;
	
}

void	GAcquTreeManager::Print()
{
	cout << "Event Number " << AcquEvent << " with " << nParticles << " Hits" << endl;
}

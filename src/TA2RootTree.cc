//*************************************************************************
//* Author: Patrik Ott
//*************************************************************************

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TA2RootTree                                                          //
//                                                                      //
// This class is organising the output to ROOT files                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include "TA2RootTree.h"

ClassImp(TA2RootTree)





TA2RootTree::TA2RootTree(const char* Name, TA2Analysis* Analysis) : TA2AccessSQL(Name, Analysis),
                                                                    file(0),
                                                                    tree(0),
                                                                    treeTagger(0),
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
                                                                    eventNumber(0),
                                                                    eventID(0),
                                                                    Scaler(0)
{
    strcpy(outputFolder,"~");
    strcpy(fileName,"RootTree");

    AddCmdList(RootTreeConfigKeys);
}


TA2RootTree::~TA2RootTree()
{
	if(treeEvent)
		delete treeEvent;
	if(treeScaler)
		delete treeScaler;
    if(file)
		delete file;
}


void    TA2RootTree::LoadVariable()
{
    TA2AccessSQL::LoadVariable();
}


void    TA2RootTree::SetConfig(Char_t* line, Int_t key)
{
    switch(key)
    {
    case ERT_OUTPUT_FOLDER:
        strcpy(outputFolder,line);
        while(outputFolder[strlen(outputFolder)-1]=='\n' || outputFolder[strlen(outputFolder)-1]=='\r')
			outputFolder[strlen(outputFolder)-1]='\0';
        return;
    case ERT_FILE_NAME:
        strcpy(fileName,line);
        while(fileName[strlen(fileName)-1]=='\n' || fileName[strlen(fileName)-1]=='\r')
			fileName[strlen(fileName)-1]='\0';
        return;
    default:
        TA2AccessSQL::SetConfig(line, key);
    }
}

void    TA2RootTree::PostInit()
{
    TA2AccessSQL::PostInit();
    
    Px			= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    Py			= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    Pz			= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    E			= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    time		= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    clusterSize	= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    
    tagged_ch	= new Int_t[TA2ROOTTREE_MAX_TAGGER];
    tagged_t	= new Double_t[TA2ROOTTREE_MAX_TAGGER];
    
    Apparatus	= new UChar_t[TA2ROOTTREE_MAX_PARTICLE];
    d_E			= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    WC1_E		= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    WC2_E		= new Double_t[TA2ROOTTREE_MAX_PARTICLE];
    
    NaI_Hits	= new Int_t[TA2ROOTTREE_MAX_HITS];
    BaF2_Hits	= new Int_t[TA2ROOTTREE_MAX_HITS];
    PbWO4_Hits	= new Int_t[TA2ROOTTREE_MAX_HITS];
    PID_Hits	= new Int_t[TA2ROOTTREE_MAX_HITS];
    Veto_Hits	= new Int_t[TA2ROOTTREE_MAX_HITS];
    WC1_Hits	= new Int_t[TA2ROOTTREE_MAX_HITS];
    WC2_Hits	= new Int_t[TA2ROOTTREE_MAX_HITS];
    
    printf("---------\n");
    printf("Init Tree\n");
    printf("---------\n");
    
    Char_t	str[256];
    sprintf(str, "%s/%s_%d.root", outputFolder, fileName, GetRunNumber());
    file		= new TFile(str,"RECREATE");
	treeEvent	= new TTree("treeEvent", "treeEvent");
	treeScaler	= new TTree("treeScaler", "treeScaler");
	
	treeEvent->Branch("nParticles",&nParticles,"nParticles/I");
	treeEvent->Branch("Px", Px, "Px[nParticles]/D");
	treeEvent->Branch("Py", Py, "Py[nParticles]/D");
	treeEvent->Branch("Pz", Pz, "Pz[nParticles]/D");
	treeEvent->Branch("E",  E,  "E[nParticles]/D");	
	treeEvent->Branch("time", time, "time[nParticles]/D");
	treeEvent->Branch("clusterSize", clusterSize, "clusterSize[nParticles]/D");
    
	treeEvent->Branch("nTagged", &nTagged,"nTagged/I");
	treeEvent->Branch("tagged_ch", tagged_ch, "tagged_ch[nTagged]/I");
	treeEvent->Branch("tagged_t", tagged_t, "tagged_t[nTagged]/D");
    
	treeEvent->Branch("Apparatus", Apparatus, "Apparatus[nParticles]/b");
	treeEvent->Branch("d_E", d_E, "d_E[nParticles]/D");	
	treeEvent->Branch("WC1_E", WC1_E, "WC1_E[nParticles]/D");	
	treeEvent->Branch("WC1_E", WC1_E, "WC1_E[nParticles]/D");
	
	treeEvent->Branch("nNaI_Hits", &nNaI_Hits, "nNaI_Hits/I");
	treeEvent->Branch("NaI_Hits", NaI_Hits, "NaI_Hits[nNaI_Hits]/I");
	treeEvent->Branch("nBaF2_Hits", &nBaF2_Hits, "nBaF2_Hits/I");
	treeEvent->Branch("BaF2_Hits", BaF2_Hits, "BaF2_Hits[nBaF2_Hits]/I");
	treeEvent->Branch("nPbWO4_Hits", &nPbWO4_Hits, "nPbWO4_Hits/I");
	treeEvent->Branch("PbWO4_Hits", PbWO4_Hits, "PbWO4_Hits[nPbWO4_Hits]/I");
	treeEvent->Branch("nPID_Hits", &nPID_Hits, "nPID_Hits/I");
	treeEvent->Branch("PID_Hits", PID_Hits, "PID_Hits[nPID_Hits]/I");
	treeEvent->Branch("nVeto_Hits", &nVeto_Hits, "nVeto_Hits/I");
	treeEvent->Branch("Veto_Hits", Veto_Hits, "Veto_Hits[nVeto_Hits]/I");
	treeEvent->Branch("nWC1_Hits", &nWC1_Hits, "nWC1_Hits/I");
	treeEvent->Branch("WC1_Hits", WC1_Hits, "WC1_Hits[nWC1_Hits]/I");
	treeEvent->Branch("nWC2_Hits", &nWC2_Hits, "nWC2_Hits/I");
	treeEvent->Branch("WC2_Hits", WC2_Hits, "WC2_Hits[nWC2_Hits]/I");
	
	treeEvent->Branch("ESum", &ESum, "ESum/D");
	treeEvent->Branch("CBMult", &CBMult, "CBMult/I");
	treeEvent->Branch("TAPSMult", &TAPSMult, "TAPSMult/I");
	
	treeScaler->Branch("eventNumber", &eventNumber, "eventNumber/I");
	treeScaler->Branch("eventID", &eventID, "eventID/I");
	treeScaler->Branch("Scaler", &Scaler, "Scaler/I");
}


void    TA2RootTree::Reconstruct()
{
	//Is Scaler Read
	if(gAR->IsScalerRead())
	{
	//treeScaler->Fill();		
	}
	
	// Collect Tagger M0 Hits
	nTagged	= fTagger->GetNhits();
	for(int i=0; i<nTagged; i++)
	{
		tagged_ch[i]	= fTagger->GetHits(i);
		tagged_t[i]		= (fTagger->GetTime())[i];
	}
	
	// Collect Tagger M0 Hits
	for(int m=1; m<GetNMultihit(); m++)
	{
		for(int i=0; i<fTagger->GetNhitsM(m); i++)
		{
			tagged_ch[nTagged+i]	= (fTagger->GetHitsM(m))[i];
			tagged_t[nTagged+i]		= (fTagger->GetTimeM(m))[i];
		}
		nTagged	+= fTagger->GetNhitsM(m);
	}
	
	// Collect CB Hits
    nParticles	= fCB->GetNParticle();      
    //printf("nCB_Hits: %d",nCB_Hits);
	for(int i=0; i<nParticles; i++)
	{
		Px[i]			= fCB->GetParticles(i).GetPx();
		Py[i]			= fCB->GetParticles(i).GetPy();
		Pz[i]			= fCB->GetParticles(i).GetPz();
		E[i]			= fCB->GetParticles(i).GetE();
		time[i]			= fCB->GetParticles(i).GetTime();
		
		NaI_E[i]		= fCB->GetParticles(i).GetE();
    	BaF2_E;
    	PbWO4_E;
    	PID_E;
    	Veto_E;
    	WC1_E;
    	WC2_E;
	}
	// Collect CB Hits
	for(int i=0; i<fCB->GetNParticle(); i++)
	{
		Px[nParticles+i]			= fTAPS->GetParticles(i).GetPx();
		Py[nParticles+i]			= fTAPS->GetParticles(i).GetPy();
		Pz[nParticles+i]			= fTAPS->GetParticles(i).GetPz();
		E[nParticles+i]				= fTAPS->GetParticles(i).GetE();
		time[nParticles+i]			= fTAPS->GetParticles(i).GetTime();
	}
	nParticles
	
	//treeEvent->Fill();
	
	
}

void    TA2RootTree::Finish()
{
	printf("------------------\n");
	printf("Write Tree to file\n");
	printf("------------------\n");
	
	file->cd();
	
	if(treeEvent) 
	{
		treeEvent->Write();	// Write	
		delete treeEvent; 	// Close and delete in memory
	}	
	if(treeScaler) 
	{
		treeScaler->Write();// Write	
		delete treeScaler; 	// Close and delete in memory
    }
    if(file) 
		delete file;		// Close and delete in memory

	
	TA2AccessSQL::Finish();
}

void    TA2RootTree::ParseMisc(char* line)
{
	TA2AccessSQL::ParseMisc(line);
}

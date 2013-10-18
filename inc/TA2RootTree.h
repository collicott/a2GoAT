//*************************************************************************
//* Author: Patrik Ott
//*************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TA2RootTree                                                          //
//                                                                      //
// This class is organising the output to ROOT files                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#ifndef __TA2RootTree_h__
#define __TA2RootTree_h__


#include "TFile.h"
#include "TTree.h"

#include "TA2AccessSQL.h"

#define TA2ROOTTREE_MAX_TAGGER		256
#define TA2ROOTTREE_MAX_PARTICLE	128
#define TA2ROOTTREE_MAX_HITS		512

enum {
    ERT_OUTPUT_FOLDER = 30250,
    ERT_FILE_NAME,
};

static const Map_t RootTreeConfigKeys[] = {
    // General keys
    {"RootTree-Output-Folder:"       	, ERT_OUTPUT_FOLDER},
    {"RootTree-File-Name:"           	, ERT_FILE_NAME},
    // Termination
    {NULL        , -1           }
};





class	TA2RootTree	: public TA2AccessSQL
{
private:
	TFile*		file;				// outFile
	TTree*		treeEvent;			// treeEvent
	TTree*		treeScaler; 		// treeScaler

    char        outputFolder[256];
    char        fileName[64];
    
    //Particles    
    Int_t			nParticles;		//
    Double_t*		Px;
    Double_t*		Py;
    Double_t*		Pz;
    Double_t*		E;
    Double_t*		time;
    UChar_t*		clusterSize;
    
    //Tagger
    Int_t			nTagger;
    Int_t*			tagged_ch;
    Double_t*		tagged_t;
    
    //Apparatus
    UChar_t*		Apparatus;
    
    // Charged detector energies
    Double_t*		d_E;
    Double_t*		WC1_E;
    Double_t*		WC2_E;
    
    //Hits
    Int_t			nNaI_Hits;
    Int_t*			NaI_Hits;
    Int_t			nBaF2_Hits;
    Int_t*			BaF2_Hits;
    Int_t			nPbWO4_Hits;
    Int_t*			PbWO4_Hits;
    Int_t			nPID_Hits;
    Int_t*			PID_Hits;
    Int_t			nVeto_Hits;
    Int_t*			Veto_Hits;
    Int_t			nWC1_Hits;
    Int_t*			WC1_Hits;
    Int_t			nWC2_Hits;
    Int_t*			WC2_Hits;
    
    // Trigger TBD
    Double_t 		ESum;
    Int_t 			CBMult; 	//or Detector Energies
	Int_t			TAPSMult;
    
    
    //Scalers
    Int_t			eventNumber;
    Int_t			eventID;
    Int_t			Scaler;
    
    //
    
public:
	TA2RootTree(const char*, TA2Analysis*);
	~TA2RootTree();
	
	virtual void LoadVariable();            //Creates histograms
    virtual void SetConfig(Char_t*, Int_t); //Parses general information from configuration file
    virtual void ParseMisc(char* line);     //Parses additional information from configuration file
    virtual void Reconstruct();             //Event reconstruction
    virtual void PostInit();                //Initialisation etc.
    virtual void Finish();                //Initialisation etc.

	ClassDef(TA2RootTree, 1)
};


#endif

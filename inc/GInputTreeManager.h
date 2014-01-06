#ifndef __GInputTreeManager_h__
#define __GInputTreeManager_h__


#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TCutG.h"

#include<iostream>
using namespace std;

#define GINPUTTREEMANAGER_MAX_TAGGER	1024
#define GINPUTTREEMANAGER_MAX_PARTICLE	128
#define GINPUTTREEMANAGER_MAX_HITS		860
#define EAppCB  1
#define EAppTAPS 2


class	GInputTreeManager
{
private:
	TFile*		file;				// outFile
	TTree*		treeRawEvent;		// Raw particle information (filled each event)
	TTree*		treeTagger;			// Tagger information (filled each event)
	TTree* 		treeTrigger;		// Trigger information (filled each event)
	TTree* 		treeDetectorHits;	// Detector system hit patterns (filled each event)
	TTree*		treeScaler; 		// Scaler read information (filled each scaler read)

    //Particles    
    Int_t		nParticles;
    Double_t*	Ek;
    Double_t* 	Theta;
    Double_t* 	Phi;
   	Double_t*	time;
    UChar_t*    clusterSize;
    
    //Tagger
    Int_t		nTagged;
    Int_t*		tagged_ch;
    Double_t*	tagged_t;
    
    //Apparatus
    UChar_t*	Apparatus;
    
    //Charged detector energies
    Double_t*	d_E;
    Double_t*	WC0_E;
    Double_t*	WC1_E;

	//Wire Chamber vertex reconstruction
   	Double_t* 	WC_Vertex_X;
   	Double_t* 	WC_Vertex_Y;
   	Double_t* 	WC_Vertex_Z;
    
   	//Hits
   	Int_t		nNaI_Hits;
   	Int_t*		NaI_Hits;
   	Int_t		nPID_Hits;
   	Int_t*		PID_Hits;
   	Int_t		nWC_Hits;
   	Int_t*		WC_Hits;
   	Int_t		nBaF2_PbWO4_Hits;
   	Int_t*		BaF2_PbWO4_Hits;
   	Int_t		nVeto_Hits;
   	Int_t*		Veto_Hits;
    
   	//Trigger
   	Double_t 	ESum;
   	Int_t 		Mult;
	
    //Scalers
    Int_t		EventNumber;
    Int_t		EventID;
    UInt_t*		Scaler;
    Int_t		NScaler;

	//protected members
    Int_t		firstValidEvent;
    Int_t		lastValidEvent;
    Int_t		actualEvent;
    
protected:
	void    CheckRange(Int_t& min, Int_t& max);
    void 	GetInputEntryFast();                	// without testing index
    void	TraverseInputEntries(const Int_t min, const Int_t max);
    void	TraverseInputEntries(const Int_t max) 	{TraverseInputEntries(firstValidEvent, max);}
    void	TraverseInputEntries()		 			{TraverseInputEntries(firstValidEvent, lastValidEvent);}

    Double_t* 	Mass;
	
public:

    GInputTreeManager();
    virtual ~GInputTreeManager();

	TTree*	treeRawEvent_clone;		// Raw particle information (filled when required)
	TTree*	treeTagger_clone;		// Tagger information (filled when required)
	TTree* 	treeTrigger_clone;		// Trigger information (filled when required)
	TTree* 	treeDetectorHits_clone;	// Detector system hit patterns (filled when required)
	TTree*	treeScaler_clone; 		// Scaler read information (filled when required)

    Bool_t	OpenInputFile(const char* treefile);
	Bool_t	OpenTreeRawEvent();
	Bool_t	OpenTreeTagger();
	Bool_t	OpenTreeTrigger();
	Bool_t	OpenTreeDetectorHits();
	Bool_t	OpenTreeScaler();
    Bool_t	FindValidEvents();
	Bool_t	GetInputEntry();
	Bool_t	GetInputEntry(const Int_t index);
    virtual void	Reset();
    virtual Bool_t	Init(const char* intreefile, const char* outtreefile) = 0;
    virtual void    Reconstruct() = 0;
    virtual void 	Analyse()=0;
    virtual	void	Print();
	
    		Int_t		GetNParticles()             const	{return nParticles;}
    const	Double_t*	GetEk()                      const	{return Ek;}
    		Double_t	GetEk(const Int_t index)		const	{return Ek[index];}    
    		    		
    const	Double_t*	GetTheta()                  	const	{return Theta;}
    		Double_t	GetTheta(const Int_t index)		const	{return Theta[index];}
    const	Double_t*	GetPhi()                  		const	{return Phi;}
    		Double_t	GetPhi(const Int_t index)		const	{return Phi[index];} 
    		
    		Double_t	GetThetaRad(const Int_t index)	const	{return Theta[index] * TMath::DegToRad();}
     		Double_t	GetPhiRad(const Int_t index)	const	{return Theta[index] * TMath::DegToRad();}
    		    
    const	Double_t*	GetTime()                   const	{return time;}
    		Double_t	GetTime(const Int_t index)	const	{return time[index];}
    		
    		UChar_t 	GetClusterSize(const Int_t index) const 	{return clusterSize[index];}
    
    		Int_t		GetNTagged()                    const	{return nTagged;}
    const	Int_t*		GetTagged_ch()               	const	{return tagged_ch;}
    		Int_t		GetTagged_ch(const Int_t index)	const	{return tagged_ch[index];}
    const	Double_t*	GetTagged_t()                   const	{return tagged_t;}
    		Double_t	GetTagged_t(const Int_t index)	const	{return tagged_t[index];}
    
    const	UChar_t*	GetApparatus()                  const	{return Apparatus;}
    		UChar_t		GetApparatus(const Int_t index)	const	{return Apparatus[index];}

    const	Double_t*	Get_dE()                    const	{return d_E;}
    		Double_t	Get_dE(const Int_t index)	const	{return d_E[index];}
    const	Double_t*	GetWC0_E()                  const	{return WC0_E;}
    		Double_t	GetWC0_E(const Int_t index)	const	{return WC0_E[index];}
    const	Double_t*	GetWC1_E()                  const	{return WC1_E;}
    		Double_t	GetWC1_E(const Int_t index)	const	{return WC1_E[index];}
    
    const	Double_t* 	GetWC_Vertex_X()                    const	{return WC_Vertex_X;}
   			Double_t 	GetWC_Vertex_X(const Int_t index)	const	{return WC_Vertex_X[index];}
    const	Double_t* 	GetWC_Vertex_Y()                    const	{return WC_Vertex_Y;}
    		Double_t 	GetWC_Vertex_Y(const Int_t index)	const	{return WC_Vertex_Y[index];}
    const	Double_t* 	GetWC_Vertex_Z()                    const	{return WC_Vertex_Z;}
    		Double_t 	GetWC_Vertex_Z(const Int_t index)	const	{return WC_Vertex_Z[index];}
    
			Double_t 	GetESum()	const	{return ESum;}
			Int_t	 	GetMult()	const	{return Mult;}	
    
    		Int_t 		GetNScaler()    			const	{return NScaler;}
    		Int_t 		GetEventID()        		const	{return EventID;}
    		Int_t 		GetEventNumber()        	const	{return EventNumber;}
    const	UInt_t*		GetScaler()                 const	{return	Scaler;}
    		UInt_t		GetScaler(const Int_t index)const	{return	Scaler[index];}

    		Int_t		GetNNaI_Hits()              	const	{return nNaI_Hits;}
    const	Int_t*		GetNaI_Hits()           		const	{return NaI_Hits;}
    		Int_t		GetNaI_Hits(const Int_t index)	const	{return NaI_Hits[index];}

    		Int_t		GetNPID_Hits()      			const	{return nPID_Hits;}
    const	Int_t*		GetPID_Hits()               	const	{return PID_Hits;}
    		Int_t		GetPID_Hits(const Int_t index)	const	{return PID_Hits[index];}

    		Int_t		GetNWC_Hits()       			const	{return nWC_Hits;}
    const	Int_t*		GetWC_Hits()                	const	{return WC_Hits;}
    		Int_t		GetWC_Hits(const Int_t index)	const	{return WC_Hits[index];}

    		Int_t		GetNBaF2_PbWO4_Hits()                   const	{return nBaF2_PbWO4_Hits;}
    const	Int_t*		GetBaF2_PbWO4_Hits()                    const	{return BaF2_PbWO4_Hits;}
    		Int_t		GetBaF2_PbWO4_Hits(const Int_t index)	const	{return BaF2_PbWO4_Hits[index];}

			Int_t		GetNVeto_Hits()                 const	{return nVeto_Hits;}
    const	Int_t*		GetVeto_Hits()                  const	{return Veto_Hits;}
    		Int_t		GetVeto_Hits(const Int_t index)	const	{return Veto_Hits[index];}
    		
			Int_t		GetActualEvent()	const	{return actualEvent;}

	void 	SetInputMass(Int_t index, Double_t value)	{Mass[index] 	= value;}

   TLorentzVector	GetVector(const Int_t index) const	
					{

						Double_t T 	= Ek[index];
						Double_t M  = Mass[index];
						Double_t th = Theta[index] * TMath::DegToRad();
						Double_t ph = Phi[index]   * TMath::DegToRad();
												
						Double_t E 	= T + M;
						Double_t P 	= TMath::Sqrt(E*E - M*M);
						Double_t Px = P* sin(th)*cos(ph);
						Double_t Py = P* sin(th)*sin(ph);						
						Double_t Pz = P* cos(th);
						
						return TLorentzVector(Px, Py, Pz, E);
					}			
					
    		Int_t		GetNCB()	const 
						{
							Int_t NCB = 0;
							for(Int_t i = 0; i < nParticles; i++) 
							{
								if (Apparatus[i] == EAppCB) NCB++;
							}
							return NCB;
						}
    		Int_t		GetNTAPS()	const 
						{
							Int_t NTAPS = 0;
							for(Int_t i = 0; i < nParticles; i++) 
							{
								if (Apparatus[i] == EAppTAPS) NTAPS++;
							}
							return NTAPS;
						}								
};


#endif

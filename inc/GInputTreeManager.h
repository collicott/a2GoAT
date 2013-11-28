#ifndef __GInputTreeManager_h__
#define __GInputTreeManager_h__


#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TLorentzVector.h"
#include<iostream>
using namespace std;

#define GINPUTTREEMANAGER_MAX_TAGGER		1024
#define GINPUTTREEMANAGER_MAX_PARTICLE	128
#define GINPUTTREEMANAGER_MAX_HITS		860


class	GInputTreeManager
{
private:
	TFile*		file;			// outFile
	TTree*		treeRawEvent;		// Raw particle information (filled each event)
	TTree*		treeTagger;		// Tagger information (filled each event)
	TTree* 		treeTrigger;		// Trigger information (filled each event)
	TTree* 		treeDetectorHits;	// Detector system hit patterns (filled each event)
	TTree*		treeScaler; 		// Scaler read information (filled each scaler read)

    //Particles    
    Int_t		nParticles;
    Double_t*	Px;
    Double_t*	Py;
   	Double_t*	Pz;
    Double_t*	E;
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

protected:
    //protected members
    Int_t		firstValidEvent;
    Int_t		lastValidEvent;
    Int_t		actualEvent;

    void GetEntry();
    void GetEntry(const Int_t index);
	
public:
    GInputTreeManager();
    virtual ~GInputTreeManager();

    Bool_t	OpenInputFile(const char* treefile);
	Bool_t	OpenTreeRawEvent();
	Bool_t	OpenTreeTagger();
	Bool_t	OpenTreeTrigger();
	Bool_t	OpenTreeDetectorHits();
	Bool_t	OpenTreeScaler();
    Bool_t	FindValidEvents();
    virtual void	Reset();
    virtual void    Reconstruct() = 0;
	
    Int_t		GetNParticles()             {return nParticles;}
    Double_t*	GetPx()                     {return Px;}
    Double_t	GetPx(const Int_t index)	{return Px[index];}
    Double_t*	GetPy()                     {return Py;}
    Double_t	GetPy(const Int_t index)	{return Py[index];}
    Double_t*	GetPz()                     {return Pz;}
    Double_t	GetPz(const Int_t index)	{return Pz[index];}
    Double_t*	GetE()                      {return E;}
    Double_t	GetE(const Int_t index)		{return E[index];}
    Double_t*	GetTime()                   {return time;}
    Double_t	GetTime(const Int_t index)	{return time[index];}
    
    TLorentzVector	GetVector(const Int_t index)	{return TLorentzVector(Px[index], Py[index], Pz[index], E[index]);}
    
    Int_t		GetNTagged()                    {return nTagged;}
    Int_t*		GetTagged_ch()               	{return tagged_ch;}
    Int_t		GetTagged_ch(const Int_t index)	{return tagged_ch[index];}
    Double_t*	GetTagged_t()                   {return tagged_t;}
    Double_t	GetTagged_t(const Int_t index)	{return tagged_t[index];}
    
    UChar_t*	GetApparatus()                  {return Apparatus;}
    UChar_t		GetApparatus(const Int_t index)	{return Apparatus[index];}

    Double_t*	Get_dE()                    {return d_E;}
    Double_t	Get_dE(const Int_t index)	{return d_E[index];}
    Double_t*	GetWC0_E()                  {return WC0_E;}
    Double_t	GetWC0_E(const Int_t index)	{return WC0_E[index];}
    Double_t*	GetWC1_E()                  {return WC1_E;}
    Double_t	GetWC1_E(const Int_t index)	{return WC1_E[index];}
    
    Double_t* 	GetWC_Vertex_X()                    {return WC_Vertex_X;}
   	Double_t 	GetWC_Vertex_X(const Int_t index)	{return WC_Vertex_X[index];}
    Double_t* 	GetWC_Vertex_Y()                    {return WC_Vertex_Y;}
    Double_t 	GetWC_Vertex_Y(const Int_t index)	{return WC_Vertex_Y[index];}
    Double_t* 	GetWC_Vertex_Z()                    {return WC_Vertex_Z;}
    Double_t 	GetWC_Vertex_Z(const Int_t index)	{return WC_Vertex_Z[index];}
    
	Double_t 	GetESum()	{return ESum;}
	Int_t	 	GetMult()	{return Mult;}	
    
    Int_t 		GetNScaler()    			{return NScaler;}
    Int_t 		GetEventID()        		{return EventID;}
    Int_t 		GetEventNumber()        	{return EventNumber;}
    UInt_t*		GetScaler()                 {return	Scaler;}
    UInt_t		GetScaler(const Int_t index){return	Scaler[index];}

    Int_t		GetNNaI_Hits()              	{return nNaI_Hits;}
    Int_t*		GetNaI_Hits()           		{return NaI_Hits;}
    Int_t		GetNaI_Hits(const Int_t index)	{return NaI_Hits[index];}

    Int_t		GetNPID_Hits()      			{return nPID_Hits;}
    Int_t*		GetPID_Hits()               	{return PID_Hits;}
    Int_t		GetPID_Hits(const Int_t index)	{return PID_Hits[index];}

    Int_t		GetNWC_Hits()       			{return nWC_Hits;}
    Int_t*		GetWC_Hits()                	{return WC_Hits;}
    Int_t		GetWC_Hits(const Int_t index)	{return WC_Hits[index];}

    Int_t		GetNBaF2_PbWO4_Hits()                   {return nBaF2_PbWO4_Hits;}
    Int_t*		GetBaF2_PbWO4_Hits()                    {return BaF2_PbWO4_Hits;}
    Int_t		GetBaF2_PbWO4_Hits(const Int_t index)	{return BaF2_PbWO4_Hits[index];}

    Int_t		GetNVeto_Hits()                 {return nVeto_Hits;}
    Int_t*		GetVeto_Hits()                  {return Veto_Hits;}
    Int_t		GetVeto_Hits(const Int_t index)	{return Veto_Hits[index];}
            
    Int_t		GetActualEvent()		{return actualEvent;}
    
    
};


#endif

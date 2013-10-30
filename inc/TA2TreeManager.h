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


#ifndef __TA2TreeManager_h__
#define __TA2TreeManager_h__


#include "TFile.h"
#include "TTree.h"

#define TA2TREEMANAGER_MAX_TAGGER		256
#define TA2TREEMANAGER_MAX_PARTICLE	128
#define TA2TREEMANAGER_MAX_HITS		512  // Why 512 ?


class	TA2TreeManager
{
private:
	TFile*		file;				// outFile
	TTree*		treeEvent;			// treeEvent
	TTree*		treeScaler; 		// treeScaler

    //Particles    
    Int_t			nParticles;		
    Double_t*		Px;
    Double_t*		Py;
    Double_t*		Pz;
    Double_t*		E;
    Double_t*		time;
    UChar_t*		clusterSize;
    
    //Tagger
    Int_t			nTagged;
    Int_t*			tagged_ch;
    Double_t*		tagged_t;
    
    //Apparatus
    UChar_t*		Apparatus;
    
    //Charged detector energies
    Double_t*		d_E;
    Double_t*		WC0_E;
    Double_t*		WC1_E;

	//Wire Chamber vertex reconstruction
    Double_t* 		WC_Vertex_X;
    Double_t* 		WC_Vertex_Y;
    Double_t* 		WC_Vertex_Z;
    
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
    Int_t			nWC0_Hits;
    Int_t*			WC0_Hits;
    Int_t			nWC1_Hits;
    Int_t*			WC1_Hits;
    
    //Trigger TBD
    Double_t 		ESum;
    Int_t 			CBMult; 	//or Detector Energies
	Int_t			TAPSMult;
    
    //Scalers
    Int_t			EventNumber;
    Int_t			EventID;
    UInt_t*			Scaler;
    
    
public:
	TA2TreeManager();
	~TA2TreeManager();
	
	void	Reset();
	Bool_t	OpenTree(const char* treefile);
	
	Int_t			GetNParticles()				{return nParticles;}		
    Double_t*		GetPx()						{return Px;}			
    Double_t		GetPx(const Int_t index)	{return Px[index];}		
    Double_t*		GetPy()						{return Py;}					
    Double_t		GetPy(const Int_t index)	{return Py[index];}	
    Double_t*		GetPz()						{return Pz;}				
    Double_t		GetPz(const Int_t index)	{return Pz[index];}	
    Double_t*		GetE()						{return E;}					
    Double_t		GetE(const Int_t index)		{return E[index];}	
    Double_t*		GetTime()					{return time;}			
    Double_t		GetTime(const Int_t index)	{return time[index];}	
    
    Int_t			GetNTagged()					{return nTagged;}
    Int_t*			GetTagged_ch()					{return tagged_ch;}
    Int_t			GetTagged_ch(const Int_t index)	{return tagged_ch[index];}
    Double_t*		GetTagged_t()					{return tagged_t;}
    Double_t		GetTagged_t(const Int_t index)	{return tagged_t[index];}
    
    UChar_t*		GetApparatus()					{return Apparatus;}
    UChar_t			GetApparatus(const Int_t index)	{return Apparatus[index];}
	
    Double_t*		Get_d_E()					{return d_E;}
    Double_t		Get_d_E(const Int_t index)	{return d_E[index];}
    Double_t*		GetWC0_E					{return WC0_E;}
    Double_t		GetWC0_E(const Int_t index)	{return WC0_E[index];}
    Double_t*		GetWC1_E					{return WC1_E;}
    Double_t		GetWC1_E(const Int_t index)	{return WC1_E[index];}
    
    Double_t* 		GetWC_Vertex_X()					{return WC_Vertex_X;}
    Double_t* 		GetWC_Vertex_X(const Int_t index)	{return WC_Vertex_X[index];}
    Double_t* 		GetWC_Vertex_Y()					{return WC_Vertex_Y;}
    Double_t* 		GetWC_Vertex_Y(const Int_t index)	{return WC_Vertex_Y[index];}
    Double_t* 		GetWC_Vertex_Z()					{return WC_Vertex_Z;}
    Double_t* 		GetWC_Vertex_Z(const Int_t index)	{return WC_Vertex_Z[index];}
    
	ClassDef(TA2TreeManager, 1)
};


#endif

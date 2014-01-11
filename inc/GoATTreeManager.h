#ifndef __GoATTreeManager_h__
#define __GoATTreeManager_h__

#include "GAcquTreeManager.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#define GoATTREEMANAGER_MAX_TAGGER		1024
#define GoATTREEMANAGER_MAX_PARTICLE	128
#define GoATTREEMANAGER_MAX_HITS		860

class	GoATTreeManager    : public GAcquTreeManager
{
private:
    TTree*		treeParticles;		// reconstructed

    //Reconstructed Particles
    UInt_t		rawEventNumber;
    
    //Particles    
    Int_t		nParticles;
    Int_t* 		Charge;
    Int_t* 		PDG;
    Double_t*	Px;
    Double_t*	Py;
   	Double_t*	Pz;
    Double_t*	Ek;
    Double_t*	Theta;
    Double_t*	Mass; 
    Double_t*	Phi; 
   	Double_t*	time;
    UChar_t*    clusterSize;
    UChar_t*	Apparatus;
    Double_t*	d_E;
    Double_t*	WC0_E;
    Double_t*	WC1_E;
   	Double_t* 	WC_Vertex_X;
   	Double_t* 	WC_Vertex_Y;
   	Double_t* 	WC_Vertex_Z;    

	Int_t*		nDaughters;
	Int_t 		nDaughterList;
   	Int_t*		daughter_index;   	
    Int_t*		daughter_PDG;
   	Double_t* 	daughter_E; 
   	Double_t*	daughter_Theta;
   	Double_t*	daughter_Phi;

    Int_t		firstGoATEvent;
    Int_t		lastGoATEvent;
    Int_t		GoATEvent;
 	
protected:
    Int_t       offsetToAcquTree;

 	Char_t*		global_config_file;
    void		GetEntryFast();
    void		TraverseEntries(const Int_t min, const Int_t max);
    void		TraverseEntries(const Int_t max) {TraverseEntries(0, max);}
	
public:

	TFile*		GoATFile;			// GoATFile

	GoATTreeManager();
    virtual ~GoATTreeManager();
	
    Bool_t	OpenGoATFile(const char* treefile, Option_t* option);
    Bool_t	OpenGoATFile(const char* treefile) {return OpenGoATFile(treefile,"RECREATE");}
    Bool_t  InitTreeParticles(TFile* TreeFile);
	Bool_t	InitTreeParticles() {return InitTreeParticles(GoATFile);}
    Bool_t  OpenTreeParticles(TFile* TreeFile);
	Bool_t	OpenTreeParticles() {return OpenTreeParticles(GoATFile);}    
    virtual Bool_t 	FillEvent();
    Bool_t	WriteTrees(TFile* TreeFile);
	Bool_t	WriteTrees() {return WriteTrees(GoATFile);}    
    Bool_t	CloseOutputFile(TFile* TreeFile); 
	Bool_t	CloseOutputFile() {return CloseOutputFile(GoATFile);}    
    
    
	Bool_t	FindValidGoATEvents();
    void 	GetGoATEntryFast(); // without testing index
    void	TraverseGoATEntries(const Int_t min, const Int_t max);
    void	TraverseGoATEntries(const Int_t max) {TraverseGoATEntries(firstGoATEvent, max);}
    void	TraverseGoATEntries()	{TraverseGoATEntries(firstGoATEvent, lastGoATEvent);}    
    
    void	Clear()	{;}
    virtual void	Reset();
    virtual void	Reconstruct();
	virtual void	Print();

	void	SetCharge(Int_t index, Int_t value)	{Charge[index] = value;}
	void	SetNParticles(Int_t value)   	{nParticles = value;}
	void	SetNDaughters(Int_t index, Int_t value) {nDaughters[index] = value;}
	
	void	SetPDG(Int_t index, Int_t value) {PDG[index] = value;}	
	void	SetPx(Int_t index, Double_t value)	{Px[index] 	= value;}
	void	SetPy(Int_t index, Double_t value)	{Py[index] 	= value;}
	void	SetPz(Int_t index, Double_t value)	{Pz[index] 	= value;}
	void	SetEk(Int_t index, Double_t value)		{Ek[index] 	= value;}
	void	SetTheta(Int_t index, Double_t value)	{Theta[index] 	= value;}
	void	SetPhi(Int_t index, Double_t value)		{Phi[index] 	= value;}		

	void	SetTime(Int_t index, Double_t value)	{time[index] = value;}

	void	SetClusterSize(Int_t index, Int_t value)	{clusterSize[index] = value;}
	void	SetApparatus(Int_t index, UChar_t value)	{Apparatus[index] = value;}
	
	void	Set_dE(Int_t index, Double_t value)		{d_E[index] = value;}
	void	SetWC0_E(Int_t index, Double_t value)	{WC0_E[index] = value;}
	void	SetWC1_E(Int_t index, Double_t value)	{WC1_E[index] = value;}
	
	void	SetWC_Vertex_X(Int_t index, Double_t value)	{WC_Vertex_X[index] = value;}
	void	SetWC_Vertex_Y(Int_t index, Double_t value)	{WC_Vertex_Y[index] = value;}
	void	SetWC_Vertex_Z(Int_t index, Double_t value)	{WC_Vertex_Z[index] = value;}
	
	void 	SetMass(Int_t index, Double_t value)		{Mass[index] 	= value;}

	void	SetNDaughterList(Int_t value)   	{nDaughterList = value;}
	void	SetDaughter_index(Int_t index, Int_t value)	{daughter_index[index] 	= value;}
	void	SetDaughter_E(Int_t index, Double_t value)		{daughter_E[index] 	= value;}
	void	SetDaughter_Theta(Int_t index, Double_t value)	{daughter_Theta[index] 	= value;}
	void	SetDaughter_Phi(Int_t index, Double_t value)	{daughter_Phi[index] 	= value;}
	void	SetDaughter_PDG(Int_t index, Int_t value)		{daughter_PDG[index] 	= value;}

	std::string config;	
	void 	SetConfigFile(Char_t* config_file)	{global_config_file = config_file;}
			Char_t* GetConfigFile()	{return global_config_file;}	

    string	ReadConfig(const std::string& key_in, Int_t instance, Char_t* configname);	
    string	ReadConfig(const std::string& key_in, Int_t instance) {return ReadConfig(key_in,instance,GetConfigFile());}
    string	ReadConfig(const std::string& key_in) {return ReadConfig(key_in,0,GetConfigFile());}

	// Make some things available for sorting/analysis
	Int_t 		GoATTree_GetNParticles()				const 	{return nParticles;}
	Int_t 		GoATTree_GetPDG(const Int_t index)		const	{return PDG[index];}
    Int_t 		GoATTree_GetCharge(const Int_t index) 	const 	{return Charge[index];}   
	Double_t	GoATTree_GetEk(const Int_t index)		const	{return Ek[index];}    
 	Double_t	GoATTree_GetTime(const Int_t index)		const	{return time[index];}
 	 		    		
	Double_t	GoATTree_GetTheta(const Int_t index)	const	{return Theta[index];}
	Double_t	GoATTree_GetPhi(const Int_t index)		const	{return Phi[index];} 
	Double_t	GoATTree_GetThetaRad(const Int_t index)	const	{return Theta[index] * TMath::DegToRad();}
	Double_t	GoATTree_GetPhiRad(const Int_t index)	const	{return Theta[index] * TMath::DegToRad();}
		
	UChar_t 	GoATTree_GetClusterSize(const Int_t index) 	const 	{return clusterSize[index];}
	UChar_t		GoATTree_GetApparatus(const Int_t index)	const	{return Apparatus[index];}
	Double_t	GoATTree_Get_dE(const Int_t index)			const	{return d_E[index];}
	Double_t	GoATTree_GetWC0_E(const Int_t index)		const	{return WC0_E[index];}
	Double_t	GoATTree_GetWC1_E(const Int_t index)		const	{return WC1_E[index];}

	Double_t 	GoATTree_GetWC_Vertex_X(const Int_t index)	const	{return WC_Vertex_X[index];}
	Double_t 	GoATTree_GetWC_Vertex_Y(const Int_t index)	const	{return WC_Vertex_Y[index];}
	Double_t 	GoATTree_GetWC_Vertex_Z(const Int_t index)	const	{return WC_Vertex_Z[index];}

   TLorentzVector	GetGoATVector(const Int_t index) const	
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
        
};


#endif

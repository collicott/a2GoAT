#ifndef __GTreeManager_h__
#define __GTreeManager_h__

#include "GInputTreeManager.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <cstdio>
#include <string> 

#define GTREEMANAGER_MAX_TAGGER		1024
#define GTREEMANAGER_MAX_PARTICLE	128
#define GTREEMANAGER_MAX_HITS		860

class	GTreeManager    : public GInputTreeManager
{
private:
	TFile*		file;				// outFile
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


 	
protected:
    Int_t       offsetToInputTree;

 	Char_t*		global_config_file;
    void		GetEntryFast();
    void		TraverseEntries(const Int_t min, const Int_t max);
    void		TraverseEntries(const Int_t max) {TraverseEntries(0, max);}
	
public:

	GTreeManager();
    virtual ~GTreeManager();
	
    Bool_t	OpenOutputFile(const char* treefile);
    Bool_t  InitTreeParticles();
    Bool_t  OpenTreeParticles();
    virtual Bool_t 	FillEvent();
    Bool_t	WriteTrees();     
    Bool_t	CloseOutputFile(); 
    
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

	// Make some things available for sorting
	Int_t 		GTree_GetNParticles()				const 	{return nParticles;}
	Int_t 		GTree_GetPDG(const Int_t index)		const	{return PDG[index];}
    Double_t	GTree_GetTheta(const Int_t index)	const	{return Theta[index];}
    Int_t 		GTree_GetCharge(const Int_t index) 	const 	{return Charge[index];}   
        
};


#endif

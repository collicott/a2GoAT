#ifndef __GTreeManager_h__
#define __GTreeManager_h__

#include "GInputTreeManager.h"

#define GTREEMANAGER_MAX_TAGGER		1024
#define GTREEMANAGER_MAX_PARTICLE	128
#define GTREEMANAGER_MAX_HITS		860

class	GTreeManager    : public GInputTreeManager
{
private:
	TFile*		file;					// outFile
    TTree*		treeParticles;			// reconstructed Pi0s

    //Reconstructed Particles
    UInt_t		rawEventNumber;
    
 	

protected:
    Int_t       offsetToInputTree;

    void	GetEntryFast();
    void	TraverseEntries(const Int_t min, const Int_t max);
    void	TraverseEntries(const Int_t max) 					{TraverseEntries(0, max);}
	void	Fill()		{rawEventNumber = GetActualEvent(); treeParticles->Fill();}
	
public:

    //Particles    
    Int_t		gP_nParticles;
    Int_t 		gP_PDG;
    Double_t*	gP_Px;
    Double_t*	gP_Py;
   	Double_t*	gP_Pz;
    Double_t*	gP_E;
   	Double_t*	gP_time;
    UChar_t*    gP_clusterSize;
        
    UChar_t*	gP_Apparatus;
    
    Double_t*	gP_d_E;
    Double_t*	gP_WC0_E;
    Double_t*	gP_WC1_E;
    
   	Double_t* 	gP_WC_Vertex_X;
   	Double_t* 	gP_WC_Vertex_Y;
   	Double_t* 	gP_WC_Vertex_Z;    
   	
   	Double_t* 	gP_Meson_phot_Px;
   	Double_t* 	gP_Meson_phot_Py;
   	Double_t* 	gP_Meson_phot_Pz;
   	Double_t* 	gP_Meson_phot_E; 
   	Int_t*		gP_Meson_phot_Index; 
   	
   	
	GTreeManager();
    virtual ~GTreeManager();
	
    Bool_t	OpenOutputFile(const char* treefile);
    Bool_t  InitTreeParticles();
    Bool_t  OpenTreeParticles();

    void	Clear()	{;}
    virtual void	Reset();
    virtual void	Reconstruct();
    virtual Bool_t	Write();

	virtual void	Print();
};


#endif

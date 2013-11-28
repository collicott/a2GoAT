#ifndef __GTreeManager_h__
#define __GTreeManager_h__


#include "GInputTreeManager.h"


#define GTREEMANAGER_MAX_TAGGER		1024
#define GTREEMANAGER_MAX_PARTICLE	128
#define GTREEMANAGER_MAX_HITS		860


class	GTreeManager    : public GInputTreeManager
{
private:
	TFile*		file;		// outFile
    TTree*		treePi0;	// reconstructed Pi0s
    TTree*		treeEta;	// reconstructed Etas
    TTree*		treeEtap;	// reconstructed Etaps

    //Reconstructed Particles
    //Pi0
    UChar_t		nPi0Childs;
    UChar_t*	Pi0Childs;
    //Eta
    UChar_t		nEta2gChilds;
    UChar_t*	Eta2gChilds;
    //Etap
    UChar_t		nEtap2gChilds;
    UChar_t*	Etap2gChilds;
    

protected:
	void	TraverseEntries(const Int_t min, const Int_t max);
	void	TraverseEntries(const Int_t max) {TraverseEntries(firstValidEvent, max);}
	void	TraverseEntries()		 {TraverseEntries(firstValidEvent, lastValidEvent);}
	
public:
	GTreeManager();
    virtual ~GTreeManager();
	
    Bool_t	OpenOutputFile(const char* treefile);
    Bool_t  OpenTreePi0();
    Bool_t  OpenTreeEta();
    Bool_t  OpenTreeEtap();
	Bool_t	GetEntry();
	Bool_t	GetEntry(const Int_t index);
    virtual void	Reset();
    virtual void	Analysis(const char* inputtreefile, const char* outputfilename, const Int_t min = -1, const Int_t max = -1);
	virtual void	Reconstruct();
};


#endif

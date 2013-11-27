#ifndef __GTreeManager_h__
#define __GTreeManager_h__


#include "GInputTreeManager.h"


#define GTREEMANAGER_MAX_TAGGER		1024
#define GTREEMANAGER_MAX_PARTICLE	128
#define GTREEMANAGER_MAX_HITS		860


class	GTreeManager    : public GInputTreeManager
{
private:
	TFile*		file;			// outFile
    TTree*		treeParticle;	// Raw particle information (filled each event)


protected:
	void	TraverseEntries(const Int_t min, const Int_t max);
	void	TraverseEntries(const Int_t max) {TraverseEntries(firstValidEvent, max);}
	void	TraverseEntries()		 {TraverseEntries(firstValidEvent, lastValidEvent);}
	
public:
	GTreeManager();
    virtual ~GTreeManager();
	
    Bool_t	OpenOutputFile(const char* treefile);
	Bool_t	GetEntry();
	Bool_t	GetEntry(const Int_t index);
    virtual void	Reset();
    virtual void	Analysis(const char* inputtreefile, const char* outputfilename = 0);
	virtual void	Reconstruct();
};


#endif

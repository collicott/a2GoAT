#ifndef __GTreeManager_h__
#define __GTreeManager_h__


#include "GInputTreeManager.h"


#define GTREEMANAGER_MAX_TAGGER		1024
#define GTREEMANAGER_MAX_PARTICLE	128
#define GTREEMANAGER_MAX_HITS		860

struct	SGTM_Pi0
{
	UChar_t		n;
    UChar_t*	child1;
    UChar_t*	child2;
};
struct	SGTM_Eta
{
	UChar_t		n2g;
    UChar_t*	child2g1;
    UChar_t*	child2g2;
};
struct	SGTM_Etap
{
	UChar_t		n2g;
    UChar_t*	child2g1;
    UChar_t*	child2g2;
};

class	GTreeManager    : public GInputTreeManager
{
private:
	TFile*		file;				// outFile
    TTree*		treePi0;			// reconstructed Pi0s
    TTree*		treeEta;			// reconstructed Etas
    TTree*		treeEtap;			// reconstructed Etaps

    //Reconstructed Particles
    UInt_t			rawEventNumber;
    SGTM_Pi0		pi0;
    SGTM_Eta		eta;
    SGTM_Etap		etap;
    

protected:
    Int_t       offsetToInputTree;

    void	GetEntryFast();
    void	TraverseEntries(const Int_t min, const Int_t max);
    void	TraverseEntries(const Int_t max) 					{TraverseEntries(0, max);}
    //void	TraverseEntries()		 							{TraverseEntries(firstValidEvent, lastValidEvent);}
    void	FillPi0(const UChar_t ParticleChild1, const UChar_t ParticleChild2)	{pi0.child1[pi0.n] = ParticleChild1; pi0.child2[pi0.n] = ParticleChild2; pi0.n++;}
    void	FillEta(const UChar_t ParticleChild1, const UChar_t ParticleChild2)	{eta.child2g1[eta.n2g] = ParticleChild1; eta.child2g2[eta.n2g] = ParticleChild2; eta.n2g++;}
    void	FillEtap(const UChar_t ParticleChild1, const UChar_t ParticleChild2){etap.child2g1[etap.n2g] = ParticleChild1; etap.child2g2[etap.n2g] = ParticleChild2; etap.n2g++;}
	void	FillPi0()	{rawEventNumber = GetActualEvent(); treePi0->Fill();}
	void	FillEta()	{rawEventNumber = GetActualEvent(); treeEta->Fill();}
	void	FillEtap()	{rawEventNumber = GetActualEvent(); treeEtap->Fill();}
	void	Fill()		{rawEventNumber = GetActualEvent(); treePi0->Fill(); treeEta->Fill(); treeEtap->Fill();}
	
public:
	GTreeManager();
    virtual ~GTreeManager();
	
    Bool_t	OpenOutputFile(const char* treefile);
    Bool_t  InitTreePi0();
    Bool_t  OpenTreePi0();
    Bool_t  InitTreeEta();
    Bool_t  OpenTreeEta();
    Bool_t  InitTreeEtap();
    Bool_t  OpenTreeEtap();
    void	Clear()			{pi0.n = 0; eta.n2g = 0; etap.n2g = 0;}
    virtual void	Reset();
    virtual void	Reconstruct();
    virtual Bool_t	Write();

	virtual void	Print();
};


#endif

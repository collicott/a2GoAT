#ifndef __GParticleTree_h__
#define __GParticleTree_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string> 

#include "GAcquTree.h"

#define GParticleTree_MAX_PARTICLE	16

struct structGParticleTree
{
    Int_t       size;
    Double_t    Px[GParticleTree_MAX_PARTICLE];
    Double_t    Py[GParticleTree_MAX_PARTICLE];
    Double_t    Pz[GParticleTree_MAX_PARTICLE];
    Double_t    E[GParticleTree_MAX_PARTICLE];
    structGParticleTree(): size(0)  {}
};



class	GParticleTree    : public GAcquTree
{
private:
    TTree*		treeRootino;		// reconstructed
    TTree*		treePhoton;		// reconstructed
    TTree*		treeChargedPi;		// reconstructed
    TTree*		treeProton;		// reconstructed
    TTree*		treeNeutron;		// reconstructed

    TTree*		treeRootino_clone;
    TTree*		treePhoton_clone;
    TTree*		treeChargedPi_clone;
    TTree*		treeProton_clone;
    TTree*		treeNeutron_clone;

    structGParticleTree rootino;
    structGParticleTree photon;
    structGParticleTree chargedPi;
    structGParticleTree proton;
    structGParticleTree neutron;

    Bool_t  InitTree(TTree*& tree, const structGParticleTree& struc, const char* treeName);
    Bool_t  OpenTree(TTree*& tree, TTree*& tree_clone, structGParticleTree& struc, const char* treeName);
    Bool_t  CloseTree(TTree*& tree)                                                          {if(tree) delete tree;}

    void    AddParticle(structGParticleTree& particle, const TLorentzVector vec);

protected:
 	Char_t*		global_config_file;
    void		GetEntryFast();      // without testing index
	
public:

    GParticleTree();
    virtual ~GParticleTree();

    Bool_t  InitTreeRootino()   {InitTree(treeRootino, rootino, "treeRootino");}
    Bool_t  InitTreePhoton()    {InitTree(treePhoton, photon, "treePhoton");}
    Bool_t  InitTreeChargedPi() {InitTree(treeChargedPi, chargedPi, "treeChargedPi");}
    Bool_t  InitTreeProton()    {InitTree(treeProton, proton, "treeProton");}
    Bool_t  InitTreeNeutron()   {InitTree(treeNeutron, neutron, "treeNeutron");}
    Bool_t  OpenTreeRootino()   {OpenTree(treeRootino, treeRootino_clone, rootino, "treeRootino");}
    Bool_t  OpenTreePhoton()    {OpenTree(treePhoton, treePhoton_clone, photon, "treePhoton");}
    Bool_t  OpenTreeChargedPi() {OpenTree(treeChargedPi, treeChargedPi_clone, chargedPi, "treeChargedPi");}
    Bool_t  OpenTreeProton()    {OpenTree(treeProton, treeProton_clone, proton, "treeProton");}
    Bool_t  OpenTreeNeutron()   {OpenTree(treeNeutron, treeNeutron_clone, neutron, "treeNeutron");}
    Bool_t  CloseTreeRootino()   {CloseTree(treeRootino);}
    Bool_t  CloseTreePhoton()    {CloseTree(treePhoton);}
    Bool_t  CloseTreeChargedPi() {CloseTree(treeChargedPi);}
    Bool_t  CloseTreeProton()    {CloseTree(treeProton);}
    Bool_t  CloseTreeNeutron()   {CloseTree(treeNeutron);}

    virtual Bool_t 	FillEvent();
    virtual Bool_t	WriteTrees();
    
            void	Clear();
    virtual void	Reset();
    virtual void	Reconstruct();
	virtual void	Print();

    void    AddRootino(const TLorentzVector& vec)    {AddParticle(rootino, vec);}
    void    AddPhoton(const TLorentzVector& vec)     {AddParticle(photon, vec);}
    void    AddChargedPi(const TLorentzVector& vec)  {AddParticle(chargedPi, vec);}
    void    AddProton(const TLorentzVector& vec)     {AddParticle(proton, vec);}
    void    AddNeutron(const TLorentzVector& vec)    {AddParticle(neutron, vec);}

};


#endif

#include "GTreeMeson.h"
#include "GTreeManager.h"


GTreeMeson::GTreeMeson(GTreeManager *Manager, const TString& _Name)    :
    GTreeParticle(Manager, _Name),
    subParticles0(new TClonesArray("TLorentzVector", 32)),
    subParticles1(new TClonesArray("TLorentzVector", 32)),
    subParticles2(new TClonesArray("TLorentzVector", 32)),
    subParticles3(new TClonesArray("TLorentzVector", 32)),
    subParticles4(new TClonesArray("TLorentzVector", 32)),
    subParticles5(new TClonesArray("TLorentzVector", 32))
{
    for(int i=0; i<GTreeMeson_MaxEntries; i++)
    {
        //nDaughters[i]   = 0;
        decayType[i]    = Decay_NONE;
    }
}

GTreeMeson::~GTreeMeson()
{
    if (subParticles0)  delete subParticles0;
    if (subParticles1)  delete subParticles1;
    if (subParticles2)  delete subParticles2;
    if (subParticles3)  delete subParticles3;
    if (subParticles4)  delete subParticles4;
    if (subParticles5)  delete subParticles5;
}

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    //tree_in->SetBranchAddress("nDaughters",nDaughters);
    tree_in->SetBranchAddress("subParticles0.",subParticles0);
    tree_in->SetBranchAddress("subParticles1.",subParticles1);
    tree_in->SetBranchAddress("subParticles2.",subParticles2);
    tree_in->SetBranchAddress("subParticles3.",subParticles3);
    tree_in->SetBranchAddress("subParticles4.",subParticles4);
    tree_in->SetBranchAddress("subParticles5.",subParticles5);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", particles, 32, 0);
    //tree_out->Branch("nDaughters",&nDaughters,"nDaughters[nParticles]/i");
    tree_out->Branch("subParticles0.", subParticles0, 32, 0);
    tree_out->Branch("subParticles1.", subParticles1, 32, 0);
    tree_out->Branch("subParticles2.", subParticles2, 32, 0);
    tree_out->Branch("subParticles3.", subParticles3, 32, 0);
    tree_out->Branch("subParticles4.", subParticles4, 32, 0);
    tree_out->Branch("subParticles5.", subParticles5, 32, 0);
}








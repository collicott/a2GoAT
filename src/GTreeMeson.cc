#include "GTreeMeson.h"
#include "GTreeManager.h"


GTreeMeson::GTreeMeson(GTreeManager *Manager, const TString& _Name)    :
    GTree(Manager, _Name),
    nParticles(0),
    particles(new TClonesArray("TLorentzVector", 32))
{
    subParticles[0] = new TClonesArray("TLorentzVector", 32);
    subParticles[1] = new TClonesArray("TLorentzVector", 32);
    subParticles[2] = new TClonesArray("TLorentzVector", 32);
    subParticles[3] = new TClonesArray("TLorentzVector", 32);
    subParticles[4] = new TClonesArray("TLorentzVector", 32);
    subParticles[5] = new TClonesArray("TLorentzVector", 32);

    for(int i=0; i<GTreeParticle_MaxEntries; i++)
    {
        //nDaughters[i]   = 0;
        decayType[i]    = Decay_NONE;
    }
}

GTreeMeson::~GTreeMeson()
{
    if (subParticles[0])  delete subParticles[0];
    if (subParticles[1])  delete subParticles[1];
    if (subParticles[2])  delete subParticles[2];
    if (subParticles[3])  delete subParticles[3];
    if (subParticles[4])  delete subParticles[4];
    if (subParticles[5])  delete subParticles[5];
}

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    //tree_in->SetBranchAddress("nDaughters",nDaughters);
    tree_in->SetBranchAddress("subParticles0.",subParticles[0]);
    tree_in->SetBranchAddress("subParticles1.",subParticles[1]);
    tree_in->SetBranchAddress("subParticles2.",subParticles[2]);
    tree_in->SetBranchAddress("subParticles3.",subParticles[3]);
    tree_in->SetBranchAddress("subParticles4.",subParticles[4]);
    tree_in->SetBranchAddress("subParticles5.",subParticles[5]);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", particles, 32, 0);
    //tree_out->Branch("nDaughters",&nDaughters,"nDaughters[nParticles]/i");
    tree_out->Branch("subParticles0.", subParticles[0], 32, 0);
    tree_out->Branch("subParticles1.", subParticles[1], 32, 0);
    tree_out->Branch("subParticles2.", subParticles[2], 32, 0);
    tree_out->Branch("subParticles3.", subParticles[3], 32, 0);
    tree_out->Branch("subParticles4.", subParticles[4], 32, 0);
    tree_out->Branch("subParticles5.", subParticles[5], 32, 0);
}








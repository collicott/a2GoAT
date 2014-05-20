#include "GTreeMeson.h"
#include "GTreeManager.h"


GTreeMeson::GTreeMeson(GTreeManager *Manager, const TString& _Name)    :
    GTreeParticle(Manager, _Name)
{
    for(int i=0; i<GTreeMeson_MaxEntries; i++)
    {
        daughter0PDG[i] = 0;
        daughter1PDG[i] = 0;
        daughter2PDG[i] = 0;
        daughter0Indices[i] = 0;
        daughter1Indices[i] = 0;
        daughter2Indices[i] = 0;
    }
}

GTreeMeson::~GTreeMeson()
{

}

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    tree_in->SetBranchAddress("nDaughters",daughters);
    tree_in->SetBranchAddress("Daughter0PDG",daughter0PDG);
    tree_in->SetBranchAddress("Daughter0Indices",daughter0Indices);
    tree_in->SetBranchAddress("Daughter1PDG",daughter1PDG);
    tree_in->SetBranchAddress("Daughter1Indices",daughter1Indices);
    tree_in->SetBranchAddress("Daughter2PDG",daughter2PDG);
    tree_in->SetBranchAddress("Daughter2Indices",daughter2Indices);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", particles, 32000, 0);
    tree_out->Branch("nDaughters",daughters,"nDaughters[nParticles]/I");
    tree_out->Branch("Daughter0PDG",daughter0PDG,"Daughter0PDG[nParticles]/b");
    tree_out->Branch("Daughter0Indices",daughter0Indices,"Daughter0Indices[nParticles]/b");
    tree_out->Branch("Daughter1PDG",daughter1PDG,"Daughter1PDG[nParticles]/b");
    tree_out->Branch("Daughter1Indices",daughter1Indices,"Daughter1Indices[nParticles]/b");
    tree_out->Branch("Daughter2PDG",daughter2PDG,"Daughter2PDG[nParticles]/b");
    tree_out->Branch("Daughter2Indices",daughter2Indices,"Daughter2Indices[nParticles]/b");
}

TLorentzVector& GTreeMeson::GetDaughter(const Int_t index, const Int_t daugther_index)
{
    UChar_t    daughter_pdg;
    UChar_t    daughter_index;
    switch(daugther_index)
    {
        case 0:
            daughter_pdg    = daughter0PDG[index];
            daughter_index  = daughter0Indices[index];
            break;
        case 1:
            daughter_pdg    = daughter1PDG[index];
            daughter_index  = daughter1Indices[index];
            break;
        case 2:
            daughter_pdg    = daughter2PDG[index];
            daughter_index  = daughter2Indices[index];
            break;
    }

    if(daughter_pdg == 22)
        return manager->photons->Particle(daughter_index);
    if(daughter_pdg == 111)
        return manager->pi0->Particle(daughter_index);
    if(daughter_pdg == 221)
        return manager->eta->Particle(daughter_index);
}

const   TLorentzVector& GTreeMeson::GetDaughter(const Int_t index, const Int_t daugther_index) const
{
    UChar_t    daughter_pdg;
    UChar_t    daughter_index;
    switch(daugther_index)
    {
        case 0:
            daughter_pdg    = daughter0PDG[index];
            daughter_index  = daughter0Indices[index];
            break;
        case 1:
            daughter_pdg    = daughter1PDG[index];
            daughter_index  = daughter1Indices[index];
            break;
        case 2:
            daughter_pdg    = daughter2PDG[index];
            daughter_index  = daughter2Indices[index];
            break;
    }

    if(daughter_pdg == 22)
        return manager->photons->Particle(daughter_index);
    if(daughter_pdg == 111)
        return manager->pi0->Particle(daughter_index);
    if(daughter_pdg == 221)
        return manager->eta->Particle(daughter_index);
}








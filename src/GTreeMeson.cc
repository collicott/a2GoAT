#include "GTreeMeson.h"


GTreeMeson::GTreeMeson(const TString& _Name)    :
    GTreeParticle(_Name)
{
    for(int i=0; i<GTreeMeson_NDaughterEntries; i++)
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

/*Bool_t  GTreeMeson::Init(const char* filename_input, const char* filename_output, const Bool_t override)
{
    if(!GTree::Init(filename_input, filename_output, override))
        return kFALSE;

    tree_out->Branch("pi0.", &pi0, sizeof(TLorentzVector)*32, 0);
    tree_out->Branch("eta.", &eta, sizeof(TLorentzVector)*32, 0);
    tree_out->Branch("etap.", &etap, sizeof(TLorentzVector)*32, 0);

    for(int i=0; i<tree_in->GetEntries(); i++)
    {
        pi0->Clear();
        eta->Clear();
        etap->Clear();
        GetEntry(i);
        switch(photons->GetEntriesFast())
        {
        case 2:
            //Reconstruct2g();
            break;
        case 3:
            Reconstruct3g();
            break;
        }
    }

    Write();
}*/








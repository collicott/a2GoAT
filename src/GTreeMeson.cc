#include "GTreeMeson.h"


GTreeMeson::GTreeMeson(const TString& _Name)    :
    GTreeParticle(_Name)
{

}

GTreeMeson::~GTreeMeson()
{

}

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    tree_in->SetBranchAddress("nDaughters",daughters);
    tree_in->SetBranchAddress("nDaughterPDG",daughterPDG);
    tree_in->SetBranchAddress("nDaughterIndices",daughterIndices);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", particles, 32000, 0);
    tree_out->Branch("nDaughters",daughters,"nDaughters[nParticles]/I");
    tree_out->Branch("nDaughterPDG",daughterPDG,"nDaughterPDG[nParticles][nDaughters]/I");
    tree_out->Branch("nDaughterIndices",daughterIndices,"nDaughterIndices[nParticles][nDaughters]/I");
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








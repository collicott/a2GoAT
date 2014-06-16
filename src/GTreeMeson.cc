#include "GTreeMeson.h"
#include "GTreeManager.h"


GTreeMeson::GTreeMeson(GTreeManager *Manager, const TString& _Name)    :
    GTree(Manager, _Name),
    nParticles(0),
    particles(new TClonesArray("TLorentzVector", 32))
{
    subParticles = new TClonesArray("TClonesArray", 32);

    for(int i=0; i<GTreeMeson_MaxEntries; i++)
    {
        nPhotons[i]    = 0;
        nChargedPi[i]  = 0;
    }
}

GTreeMeson::~GTreeMeson()
{
    if (particles)        delete particles;
    if (subParticles)  delete subParticles;
}

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    tree_in->SetBranchAddress("nPhotons",nPhotons);
    tree_in->SetBranchAddress("nChargedPi",nChargedPi);
    tree_in->SetBranchAddress("nPhotons",&nPhotons);
    tree_in->SetBranchAddress("nChargedPi",&nChargedPi);
    tree_in->SetBranchAddress("subParticles.",&subParticles);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", &particles, 32, 0);
    tree_out->Branch("nPhotons",nPhotons,"nParticles/b");
    tree_out->Branch("nChargedPi",nChargedPi,"nParticles/b");
    tree_out->Branch("subParticles.", &subParticles, 32, 0);
}

void    GTreeMeson::AddParticle(const TLorentzVector& subParticle0, const TLorentzVector& subParticle1, const Int_t pdg0, const Int_t pdg1)
{
    new((*subParticles)[nParticles]) TClonesArray("TLorentzVector", 32);

    nPhotons[nParticles]    = 0;
    nChargedPi[nParticles]  = 0;

    if(pdg0 == manager->pdgDB->GetParticle("gamma")->PdgCode())
    {
        if(pdg1 == manager->pdgDB->GetParticle("gamma")->PdgCode())
            nPhotons[nParticles]    += 2;
        else
        {
            nPhotons[nParticles]++;
            nChargedPi[nParticles]++;
        }
        new((*((TClonesArray*)subParticles->At(nParticles)))[0]) TLorentzVector(subParticle0);
        new((*((TClonesArray*)subParticles->At(nParticles)))[1]) TLorentzVector(subParticle1);
    }
    else
    {
        if(pdg1 == manager->pdgDB->GetParticle("gamma")->PdgCode())
        {
            nChargedPi[nParticles]++;
            nPhotons[nParticles]++;
            new((*((TClonesArray*)subParticles->At(nParticles)))[0]) TLorentzVector(subParticle1);
            new((*((TClonesArray*)subParticles->At(nParticles)))[1]) TLorentzVector(subParticle0);
        }
        else
        {
            nChargedPi[nParticles]  += 2;
            new((*((TClonesArray*)subParticles->At(nParticles)))[0]) TLorentzVector(subParticle0);
            new((*((TClonesArray*)subParticles->At(nParticles)))[1]) TLorentzVector(subParticle0);
        }
    }

    new((*particles)[nParticles]) TLorentzVector(subParticle0 + subParticle1);
    nParticles++;
}

void    GTreeMeson::AddParticle(const Int_t nSubPhotons, TLorentzVector** subPhotons_list, const Int_t nSubChargedPi, TLorentzVector** subChargedPi_list)
{
    new((*subParticles)[nParticles]) TClonesArray("TLorentzVector", 32);

    nPhotons[nParticles]    = nSubPhotons;
    nChargedPi[nParticles]  = nSubChargedPi;
    TLorentzVector  sum;
    for(int i=0; i<nSubPhotons; i++)
    {
        sum += *subPhotons_list[i];
        new((*((TClonesArray*)subParticles->At(nParticles)))[i]) TLorentzVector(*subPhotons_list[i]);
    }
    for(int i=nSubPhotons; i<nSubChargedPi + nSubPhotons; i++)
    {
        sum += *subChargedPi_list[i];
        new((*((TClonesArray*)subParticles->At(nParticles)))[i]) TLorentzVector(*subChargedPi_list[i]);
    }
    new((*particles)[nParticles]) TLorentzVector(sum);
    nParticles++;
}

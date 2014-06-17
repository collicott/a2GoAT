#include "GTreeMeson.h"
#include "GTreeManager.h"


GTreeMeson::GTreeMeson(GTreeManager *Manager, const TString& _Name)    :
    GTree(Manager, _Name),
    nMesons(0),
    mesons(new TClonesArray("TLorentzVector", 32))
{
    subParticles = new TClonesArray("TClonesArray", 32);

    for(int i=0; i<GTreeMeson_MaxEntries; i++)
    {
        nSubPhotons[i]    = 0;
        nSubChargedPi[i]  = 0;
    }
}

GTreeMeson::~GTreeMeson()
{
    if (mesons)        delete mesons;
    if (subParticles)  delete subParticles;
}

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nMesons",&nMesons);
    tree_in->SetBranchAddress("mesons.", &mesons);
    tree_in->SetBranchAddress("nSubParticles",nSubParticles);
    tree_in->SetBranchAddress("nSubPhotons",nSubPhotons);
    tree_in->SetBranchAddress("nSubChargedPi",nSubChargedPi);
    tree_in->SetBranchAddress("subParticles.",&subParticles);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("nMesons",&nMesons,"nMesons/b");
    tree_out->Branch("mesons.", &mesons, 32, 0);
    tree_out->Branch("nSubParticles",nSubParticles, "nSubParticles[nMesons]/b");
    tree_out->Branch("nSubPhotons",nSubPhotons,"nSubParticles[nMesons]/b");
    tree_out->Branch("nSubChargedPi",nSubChargedPi,"nSubParticles[nMesons]/b");
    tree_out->Branch("subParticles.", &subParticles, 32, 0);
}

void    GTreeMeson::AddParticle(const TLorentzVector& subParticle0, const TLorentzVector& subParticle1, const Int_t pdg0, const Int_t pdg1)
{
    new((*subParticles)[nMesons]) TClonesArray("TLorentzVector", 32);

    nSubParticles[nMesons]  = 2;
    nSubPhotons[nMesons]    = 0;
    nSubChargedPi[nMesons]  = 0;

    if(pdg0 == manager->pdgDB->GetParticle("gamma")->PdgCode())
    {
        if(pdg1 == manager->pdgDB->GetParticle("gamma")->PdgCode())
            nSubPhotons[nMesons]    += 2;
        else
        {
            nSubPhotons[nMesons]++;
            nSubChargedPi[nMesons]++;
        }
        new((*((TClonesArray*)subParticles->At(nMesons)))[0]) TLorentzVector(subParticle0);
        new((*((TClonesArray*)subParticles->At(nMesons)))[1]) TLorentzVector(subParticle1);
    }
    else
    {
        if(pdg1 == manager->pdgDB->GetParticle("gamma")->PdgCode())
        {
            nSubChargedPi[nMesons]++;
            nSubPhotons[nMesons]++;
            new((*((TClonesArray*)subParticles->At(nMesons)))[0]) TLorentzVector(subParticle1);
            new((*((TClonesArray*)subParticles->At(nMesons)))[1]) TLorentzVector(subParticle0);
        }
        else
        {
            nSubChargedPi[nMesons]  += 2;
            new((*((TClonesArray*)subParticles->At(nMesons)))[0]) TLorentzVector(subParticle0);
            new((*((TClonesArray*)subParticles->At(nMesons)))[1]) TLorentzVector(subParticle0);
        }
    }

    new((*mesons)[nMesons]) TLorentzVector(subParticle0 + subParticle1);
    nMesons++;
}

void    GTreeMeson::AddParticle(const Int_t _NSubPhotons, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPi, TLorentzVector** subChargedPi_list)
{
    new((*subParticles)[nMesons]) TClonesArray("TLorentzVector", 32);

    nSubParticles[nMesons]  = _NSubPhotons + _NSubChargedPi;
    nSubPhotons[nMesons]    = _NSubPhotons;
    nSubChargedPi[nMesons]  = _NSubChargedPi;
    TLorentzVector  sum;
    for(int i=0; i<_NSubPhotons; i++)
    {
        sum += *subPhotons_list[i];
        new((*((TClonesArray*)subParticles->At(nMesons)))[i]) TLorentzVector(*subPhotons_list[i]);
    }
    for(int i=0; i<_NSubChargedPi; i++)
    {
        sum += *subChargedPi_list[i];
        new((*((TClonesArray*)subParticles->At(nMesons)))[i+ _NSubPhotons]) TLorentzVector(*subChargedPi_list[i]);
    }
    new((*mesons)[nMesons]) TLorentzVector(sum);
    nMesons++;
}

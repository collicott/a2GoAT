#include "GTreeMeson.h"
#include "GTreeManager.h"


GTreeMeson::GTreeMeson(GTreeManager *Manager, const TString& _Name)    :
    GTreeParticle(Manager, _Name),
    subParticles(new TClonesArray("TClonesArray", 32))
{
    for(int i=0; i<GTreeParticle_MaxEntries; i++)
    {
        nSubParticles[i]  = 0;
        nSubPhotons[i]    = 0;
        nSubChargedPi[i]  = 0;
    }
}

GTreeMeson::~GTreeMeson()
{
    if (subParticles)  delete subParticles;
}

void    GTreeMeson::SetBranchAdresses()
{
    GTreeParticle::SetBranchAdresses();
    tree_in->SetBranchAddress("nSubParticles",nSubParticles);
    tree_in->SetBranchAddress("nSubPhotons",nSubPhotons);
    tree_in->SetBranchAddress("nSubChargedPi",nSubChargedPi);
    tree_in->SetBranchAddress("subParticles.",&subParticles);
}

void    GTreeMeson::SetBranches()
{
    GTreeParticle::SetBranches();
    tree_out->Branch("nSubParticles",nSubParticles, "nSubParticles[nParticles]/b");
    tree_out->Branch("nSubPhotons",nSubPhotons,"nSubParticles[nParticles]/b");
    tree_out->Branch("nSubChargedPi",nSubChargedPi,"nSubParticles[nParticles]/b");
    tree_out->Branch("subParticles.", &subParticles, 32, 0);
}

void    GTreeMeson::AddParticle(const Int_t _NSubPhotons, Int_t* subPhotons_index, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPi, Int_t* subChargedPi_index, TLorentzVector** subChargedPi_list)
{
    new((*subParticles)[nParticles]) TClonesArray("TLorentzVector", 32);

    nSubParticles[nParticles]  = _NSubPhotons + _NSubChargedPi;
    nSubPhotons[nParticles]    = _NSubPhotons;
    nSubChargedPi[nParticles]  = _NSubChargedPi;
    TLorentzVector  sum;
    for(int i=0; i<_NSubPhotons; i++)
    {
        sum += *subPhotons_list[i];
        new((*((TClonesArray*)subParticles->At(nParticles)))[i]) TLorentzVector(*subPhotons_list[i]);
        Apparatus[nParticles]    = Apparatus[nParticles] | manager->photons->GetApparatus(subPhotons_index[i]);
        time[nParticles]         += manager->photons->GetTime(subPhotons_index[i]);
        clusterSize[nParticles]  += manager->photons->GetClusterSize(subPhotons_index[i]);
        d_E[nParticles]          += manager->photons->Get_dE(subPhotons_index[i]);
        WC0_E[nParticles]        += manager->photons->GetWC0_E(subPhotons_index[i]);
        WC1_E[nParticles]        += manager->photons->GetWC1_E(subPhotons_index[i]);
    }
    for(int i=0; i<_NSubChargedPi; i++)
    {
        sum += *subChargedPi_list[i];
        new((*((TClonesArray*)subParticles->At(nParticles)))[i+ _NSubPhotons]) TLorentzVector(*subChargedPi_list[i]);
        Apparatus[nParticles]    = Apparatus[nParticles] | manager->chargedPi->GetApparatus(subPhotons_index[i]);
        time[nParticles]         += manager->chargedPi->GetTime(subPhotons_index[i]);
        clusterSize[nParticles]  += manager->chargedPi->GetClusterSize(subPhotons_index[i]);
        d_E[nParticles]          += manager->chargedPi->Get_dE(subPhotons_index[i]);
        WC0_E[nParticles]        += manager->chargedPi->GetWC0_E(subPhotons_index[i]);
        WC1_E[nParticles]        += manager->chargedPi->GetWC1_E(subPhotons_index[i]);
    }
    time[nParticles]         /= nSubParticles[nParticles];
    new((*particles)[nParticles]) TLorentzVector(sum);
    nParticles++;
}


/*void    GTreeMeson::AddParticle(const Int_t subParticle_index0, const TLorentzVector& subParticle0, const Int_t pdg0, const TLorentzVector& subParticle1, const Int_t pdg1)
{
    new((*subParticles)[nParticles]) TClonesArray("TLorentzVector", 32);

    nSubParticles[nParticles]  = 2;
    nSubPhotons[nParticles]    = 0;
    nSubChargedPi[nParticles]  = 0;

    if(pdg0 == manager->pdgDB->GetParticle("gamma")->PdgCode())
    {
        if(pdg1 == manager->pdgDB->GetParticle("gamma")->PdgCode())
        {
            nSubPhotons[nParticles]  += 2;
            Apparatus[nParticles]    = manager->photons->GetApparatus(subParticle_index0) | manager->photons->GetApparatus(subParticle_index1);
            time[nParticles]         = manager->photons->GetTime(subPhotons_index[i]);
            clusterSize[nParticles]  = manager->photons->GetClusterSize(subPhotons_index[i]);
            d_E[nParticles]          = manager->photons->Get_dE(subPhotons_index[i]);
            WC0_E[nParticles]        = manager->photons->GetWC0_E(subPhotons_index[i]);
            WC1_E[nParticles]        = manager->photons->GetWC1_E(subPhotons_index[i]);
        }
        else
        {
            nSubPhotons[nParticles]++;
            nSubChargedPi[nParticles]++;
        }
        new((*((TClonesArray*)subParticles->At(nParticles)))[0]) TLorentzVector(subParticle0);
        new((*((TClonesArray*)subParticles->At(nParticles)))[1]) TLorentzVector(subParticle1);
    }
    else
    {
        if(pdg1 == manager->pdgDB->GetParticle("gamma")->PdgCode())
        {
            nSubChargedPi[nParticles]++;
            nSubPhotons[nParticles]++;
            new((*((TClonesArray*)subParticles->At(nParticles)))[0]) TLorentzVector(subParticle1);
            new((*((TClonesArray*)subParticles->At(nParticles)))[1]) TLorentzVector(subParticle0);
        }
        else
        {
            nSubChargedPi[nParticles]  += 2;
            new((*((TClonesArray*)subParticles->At(nParticles)))[0]) TLorentzVector(subParticle0);
            new((*((TClonesArray*)subParticles->At(nParticles)))[1]) TLorentzVector(subParticle0);
        }
    }

    new((*particles)[nParticles]) TLorentzVector(subParticle0 + subParticle1);
    nParticles++;
}

/*void    GTreeMeson::AddParticle(const Int_t _NSubPhotons, TLorentzVector** subPhotons_list, const Int_t _NSubChargedPi, TLorentzVector** subChargedPi_list)
{
    new((*subParticles)[nParticles]) TClonesArray("TLorentzVector", 32);

    nSubParticles[nParticles]  = _NSubPhotons + _NSubChargedPi;
    nSubPhotons[nParticles]    = _NSubPhotons;
    nSubChargedPi[nParticles]  = _NSubChargedPi;
    TLorentzVector  sum;
    for(int i=0; i<_NSubPhotons; i++)
    {
        sum += *subPhotons_list[i];
        new((*((TClonesArray*)subParticles->At(nParticles)))[i]) TLorentzVector(*subPhotons_list[i]);
    }
    for(int i=0; i<_NSubChargedPi; i++)
    {
        sum += *subChargedPi_list[i];
        new((*((TClonesArray*)subParticles->At(nParticles)))[i+ _NSubPhotons]) TLorentzVector(*subChargedPi_list[i]);
    }
    new((*particles)[nParticles]) TLorentzVector(sum);
    nParticles++;
}*/

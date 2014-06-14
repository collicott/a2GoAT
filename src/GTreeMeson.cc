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

    pdg[0]  = new Int_t[GTreeMeson_MaxEntries];
    pdg[1]  = new Int_t[GTreeMeson_MaxEntries];
    pdg[2]  = new Int_t[GTreeMeson_MaxEntries];
    pdg[3]  = new Int_t[GTreeMeson_MaxEntries];
    pdg[4]  = new Int_t[GTreeMeson_MaxEntries];
    pdg[5]  = new Int_t[GTreeMeson_MaxEntries];

    for(int i=0; i<GTreeMeson_MaxEntries; i++)
    {
        pdg[0][i]         = 0;
        pdg[1][i]         = 0;
        pdg[2][i]         = 0;
        pdg[3][i]         = 0;
        pdg[4][i]         = 0;
        pdg[5][i]         = 0;
        nPhotons[i]    = 0;
        nChargedPi[i]  = 0;
    }
}

GTreeMeson::~GTreeMeson()
{
    if (particles)        delete particles;
    if (subParticles[0])  delete subParticles[0];
    if (subParticles[1])  delete subParticles[1];
    if (subParticles[2])  delete subParticles[2];
    if (subParticles[3])  delete subParticles[3];
    if (subParticles[4])  delete subParticles[4];
    if (subParticles[5])  delete subParticles[5];
    if (pdg[0])  delete pdg[0];
    if (pdg[1])  delete pdg[1];
    if (pdg[2])  delete pdg[2];
    if (pdg[3])  delete pdg[3];
    if (pdg[4])  delete pdg[4];
    if (pdg[5])  delete pdg[5];
}

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    tree_in->SetBranchAddress("nPhotons",nPhotons);
    tree_in->SetBranchAddress("nChargedPi",nChargedPi);
    tree_in->SetBranchAddress("nPhotons",&nPhotons);
    tree_in->SetBranchAddress("nChargedPi",&nChargedPi);
    tree_in->SetBranchAddress("subParticle0.",&subParticles[0]);
    tree_in->SetBranchAddress("subParticle1.",&subParticles[1]);
    tree_in->SetBranchAddress("subParticle2.",&subParticles[2]);
    tree_in->SetBranchAddress("subParticle3.",&subParticles[3]);
    tree_in->SetBranchAddress("subParticle4.",&subParticles[4]);
    tree_in->SetBranchAddress("subParticle5.",&subParticles[5]);
    tree_in->SetBranchAddress("pdgSubParticle0",pdg[0]);
    tree_in->SetBranchAddress("pdgSubParticle1",pdg[1]);
    tree_in->SetBranchAddress("pdgSubParticle2",pdg[2]);
    tree_in->SetBranchAddress("pdgSubParticle3",pdg[3]);
    tree_in->SetBranchAddress("pdgSubParticle4",pdg[4]);
    tree_in->SetBranchAddress("pdgSubParticle5",pdg[5]);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", &particles, 32, 0);
    tree_out->Branch("nPhotons",nPhotons,"nParticles/b");
    tree_out->Branch("nChargedPi",nChargedPi,"nParticles/b");
    tree_out->Branch("subParticle0.", &subParticles[0], 32, 0);
    tree_out->Branch("subParticle1.", &subParticles[1], 32, 0);
    tree_out->Branch("subParticle2.", &subParticles[2], 32, 0);
    tree_out->Branch("subParticle3.", &subParticles[3], 32, 0);
    tree_out->Branch("subParticle4.", &subParticles[4], 32, 0);
    tree_out->Branch("subParticle5.", &subParticles[5], 32, 0);
    tree_out->Branch("pdgSubParticle0",pdg[0],"pdgSubParticle0[nParticles]/i");
    tree_out->Branch("pdgSubParticle1",pdg[1],"pdgSubParticle1[nParticles]/i");
    tree_out->Branch("pdgSubParticle2",pdg[2],"pdgSubParticle2[nParticles]/i");
    tree_out->Branch("pdgSubParticle3",pdg[3],"pdgSubParticle3[nParticles]/i");
    tree_out->Branch("pdgSubParticle4",pdg[4],"pdgSubParticle4[nParticles]/i");
    tree_out->Branch("pdgSubParticle5",pdg[5],"pdgSubParticle5[nParticles]/i");
}

void    GTreeMeson::AddParticle(const Int_t nSubParticles, TLorentzVector** subParticle_list, const Int_t* pdg_list)
{
    nPhotons[nParticles]    = 0;
    nChargedPi[nParticles]  = 0;
    TLorentzVector  sum;
    for(int i=0; i<nSubParticles; i++)
    {
        if(pdg_list[i] == manager->pdgDB->GetParticle("gamma")->PdgCode())
        {
            nPhotons[nParticles]++;
            pdg[i][nParticles]  = manager->pdgDB->GetParticle("gamma")->PdgCode();
        }
        else
        {
            nChargedPi[nParticles]++;
            pdg[i][nParticles]  = manager->pdgDB->GetParticle("pi+")->PdgCode();
        }
        sum += *subParticle_list[i];
        new((*subParticles[i])[nParticles]) TLorentzVector(*subParticle_list[i]);
    }
    for(int i=nSubParticles; i<GTreeMeson_MaxSubEntries; i++)
    {
        pdg[i][nParticles]  = 0;
    }
    new((*particles)[nParticles]) TLorentzVector(sum);
    nParticles++;
}

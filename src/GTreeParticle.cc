#include "GTreeParticle.h"


using namespace std;


GTreeParticle::GTreeParticle(const TString& _Name)    :
    GTree(_Name),
    particles(new TClonesArray("TLorentzVector", 32000)),
    nParticles(0)
{
}

GTreeParticle::~GTreeParticle()
{
}

void    GTreeParticle::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    tree_in->SetBranchAddress("rawIndex",daughters);
}

void    GTreeParticle::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", &particles, 32000, 0);
    tree_out->Branch("rawIndex",daughters,"rawIndex[nParticles]/I");
}



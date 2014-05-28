#include "GTreeFit.h"


using namespace std;


GTreeFit::GTreeFit(GTreeManager *Manager)    :
    GTree(Manager, TString("treeFit")),
    ConfidenceLevel(0),
    ChiSq(0),
    particle(new TLorentzVector())
{
    for(int i=0; i<GTreeFit_NPulls; i++)
        Pull[i] = 0;
}

GTreeFit::~GTreeFit()
{
}

void    GTreeFit::SetBranchAdresses()
{
    tree_in->SetBranchAddress("ConfidenceLevel",&ConfidenceLevel);
    tree_in->SetBranchAddress("ChiSq",&ChiSq);
    tree_in->SetBranchAddress("Pull",Pull);
    tree_in->SetBranchAddress("particle.", &particle);
}

void    GTreeFit::SetBranches()
{
    tree_out->Branch("ConfidenceLevel",&ConfidenceLevel,"ConfidenceLevel/D");
    tree_out->Branch("ChiSq",&ChiSq,"ChiSq/D");
    tree_out->Branch("Pull",Pull,"Pull[24]/D");
    tree_out->Branch("particle.", particle, 32000, 0);
}



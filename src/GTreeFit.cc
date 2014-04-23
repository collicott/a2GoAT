#include "GTreeFit.h"


using namespace std;


GTreeFit::GTreeFit()    :
    GTree(TString("Fit"))
{
}

GTreeFit::~GTreeFit()
{
}

void    GTreeFit::SetBranchAdresses()
{
    tree_in->SetBranchAddress("ConfidenceLevel",&ConfidenceLevel);
    tree_in->SetBranchAddress("ChiSq",&ChiSq);
    tree_in->SetBranchAddress("Pull",Pull);
}

void    GTreeFit::SetBranches()
{
    tree_out->Branch("ConfidenceLevel",&ConfidenceLevel,"ConfidenceLevel/D");
    tree_out->Branch("ChiSq",&ChiSq,"ChiSq/D");
    tree_out->Branch("Pull",Pull,"Pull[24]/i");
}



#include "GTreeEventParameters.h"



GTreeEventParameters::GTreeEventParameters(GTreeManager* Manager)    :
    GTree(Manager, TString("treeEventParameters")),
    EventNumber(0),
    nReconstructed(0)
{

}

GTreeEventParameters::~GTreeEventParameters()
{

}

void    GTreeEventParameters::SetBranchAdresses()
{
    tree_in->SetBranchAddress("EventNumber", 	&EventNumber);
    tree_in->SetBranchAddress("nReconstructed", 	&nReconstructed);

}

void    GTreeEventParameters::SetBranches()
{
    tree_out->Branch("EventNumber", &EventNumber, "EventNumber/i");
    tree_out->Branch("nReconstructed", &nReconstructed, "nReconstructed/b");

  }



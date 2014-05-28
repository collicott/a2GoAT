#include "GTreeEvent.h"


GTreeEvent::GTreeEvent(GTreeManager *Manager)    :
    GTree(Manager, TString("EventFlags")),
    EventNumber(0)
{
}

GTreeEvent::~GTreeEvent()
{
}

void    GTreeEvent::SetBranchAdresses()
{
    tree_in->SetBranchAddress("EventNumber",&EventNumber);
}

void    GTreeEvent::SetBranches()
{
    tree_out->Branch("EventNumber",&EventNumber,"EventNumber/i");
}



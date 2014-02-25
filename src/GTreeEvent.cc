#include "GTreeEvent.h"


using namespace std;


GTreeEvent::GTreeEvent()    :
    GTree(TString("EventFlags"))
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



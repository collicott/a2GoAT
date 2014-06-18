#include "GTreeLinPol.h"

#include <TLeaf.h>


GTreeLinPol::GTreeLinPol(GTreeManager *Manager)    :
    GTree(Manager, TString("treeLinPol"), kTRUE),
    plane(0)
{
    for(int i=0; i<352; i++) polTable[i] = 0;
}

GTreeLinPol::~GTreeLinPol()
{

}

void    GTreeLinPol::SetBranchAdresses()
{
    tree_in->SetBranchAddress("plane", &plane);
    tree_in->SetBranchAddress("polTable", polTable);
}

void    GTreeLinPol::SetBranches()
{
    tree_out->Branch("plane", &plane, "plane/I");
    tree_out->Branch("polTable", polTable, "polTable[352]/D");
}

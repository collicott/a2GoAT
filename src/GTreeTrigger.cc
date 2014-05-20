#include "GTreeTrigger.h"



GTreeTrigger::GTreeTrigger(GTreeManager* Manager)    :
    GTree(Manager, TString("treeTrigger")),
    ESum(0),
    Mult(0),
    nTriggerPattern(0),
    helicityBit(0),
    nError(0)
{
    for(int i=0; i<GTreeTrigger_MAX; i++)
    {
        TriggerPattern[i] = 0;
        ErrModID[i] = 0;
        ErrModIndex[i] = 0;
        ErrCode[i] = 0;
    }
}

GTreeTrigger::~GTreeTrigger()
{

}

void    GTreeTrigger::SetBranchAdresses()
{
    tree_in->SetBranchAddress("ESum", 	&ESum);
    tree_in->SetBranchAddress("Mult", 	&Mult);
    tree_in->SetBranchAddress("nTriggerPattern", &nTriggerPattern);
    tree_in->SetBranchAddress("TriggerPattern", TriggerPattern);
    tree_in->SetBranchAddress("HelicityBit", 	&helicityBit);
    tree_in->SetBranchAddress("nError", 	&nError);
    tree_in->SetBranchAddress("ErrModID", ErrModID);
    tree_in->SetBranchAddress("ErrModIndex.", ErrModIndex);
    tree_in->SetBranchAddress("ErrCode.", ErrCode);

}

void    GTreeTrigger::SetBranches()
{
    tree_out->Branch("ESum", &ESum,"ESum/D");
    tree_out->Branch("Mult", &Mult, "Mult/I");
    tree_out->Branch("HelicityBit", &helicityBit, "HelicityBit/b");
    tree_out->Branch("nTriggerPattern", &nTriggerPattern, "nTriggerPattern/I");
    tree_out->Branch("TriggerPattern", TriggerPattern, "TriggerPattern[nTriggerPattern]/I");
    tree_out->Branch("nError", &nError, "nError/I");
    tree_out->Branch("ErrModID", ErrModID, "ErrModID[nError]/I");
    tree_out->Branch("ErrModIndex", ErrModIndex, "ErrModIndex[nError]/I");
    tree_out->Branch("ErrCode", ErrCode, "ErrCode[nError]/I");

  }



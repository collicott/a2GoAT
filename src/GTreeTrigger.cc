#include "GTreeTrigger.h"



GTreeTrigger::GTreeTrigger()    :
    GTree(TString("treeTrigger"))
{

}

GTreeTrigger::~GTreeTrigger()
{

}

void    GTreeTrigger::SetBranchAdresses()
{
    tree_in->SetBranchAddress("ESum", 	&ESum);
    tree_in->SetBranchAddress("Mult", 	&Mult);
    tree_in->SetBranchAddress("nTriggerPattern", &nTriggerPattern);
    tree_in->SetBranchAddress("TriggerPattern", &TriggerPattern);
    tree_in->SetBranchAddress("HelicityBit", 	&helicityBit);
    tree_in->SetBranchAddress("nError", 	&nError);
    tree_in->SetBranchAddress("ErrModID", ErrModID);
    tree_in->SetBranchAddress("ErrModIndex.", &ErrModIndex);
    tree_in->SetBranchAddress("ErrCode.", &ErrCode);

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



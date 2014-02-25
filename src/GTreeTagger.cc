#include "GTreeTagger.h"

GTreeTagger::GTreeTagger()    :
    GTree(TString("treeTagger")),
    nTagged(0)
{

}

GTreeTagger::~GTreeTagger()
{

}

void    GTreeTagger::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nTagged", 	&nTagged);
    tree_in->SetBranchAddress("tagged_ch", 	tagged_ch);
    tree_in->SetBranchAddress("tagged_t", 	tagged_t);
    tree_in->SetBranchAddress("photonbeam_E", photonbeam_E);
    tree_in->SetBranchAddress("nPrompt", 	&nPrompt);
    tree_in->SetBranchAddress("promptIndex", 	promptIndex);
    tree_in->SetBranchAddress("nRand", 	&nRand);
    tree_in->SetBranchAddress("randIndex", randIndex);
}

void    GTreeTagger::SetBranches()
{
    tree_out->Branch("nTagged", &nTagged,"nTagged/I");
    tree_out->Branch("photonbeam_E", photonbeam_E, "photonbeam_E[nTagged]/D");
    tree_out->Branch("tagged_ch", tagged_ch, "tagged_ch[nTagged]/I");
    tree_out->Branch("tagged_t", tagged_t, "tagged_t[nTagged]/D");
    tree_out->Branch("nPrompt", &nPrompt,"nPrompt/B");
    tree_out->Branch("promptIndex", promptIndex, "promptIndex[nPrompt]/B");
    tree_out->Branch("nRand", &nRand, "nRand/B");
    tree_out->Branch("randIndex", randIndex, "randIndex[nRand]/B");
}

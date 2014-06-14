#include "GTreeTagger.h"

GTreeTagger::GTreeTagger(GTreeManager *Manager)    :
    GTree(Manager, TString("treeTagger")),
    nTagged(0)
{
    for(int i=0; i<GTreeTagger_MAX; i++)
    {
        tagged_ch[i] = 0;
        tagged_t[i] = 0;
        photonbeam_E[i] = 0;
    }
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
}

void    GTreeTagger::SetBranches()
{
    tree_out->Branch("nTagged", &nTagged,"nTagged/I");
    tree_out->Branch("photonbeam_E", photonbeam_E, "photonbeam_E[nTagged]/D");
    tree_out->Branch("tagged_ch", tagged_ch, "tagged_ch[nTagged]/I");
    tree_out->Branch("tagged_t", tagged_t, "tagged_t[nTagged]/D");
}

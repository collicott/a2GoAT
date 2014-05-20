#include "GTreeTagger.h"

GTreeTagger::GTreeTagger(GTreeManager *Manager)    :
    GTree(Manager, TString("treeTagger")),
    nTagged(0),
    nPrompt(0),
    nRand(0),
    missing(new TClonesArray("TLorentzVector", 32000))
{
    for(int i=0; i<GTreeTagger_MAX; i++)
    {
        tagged_ch[i] = 0;
        tagged_t[i] = 0;
        photonbeam_E[i] = 0;
        promptIndex[i] = 0;
        randIndex[i] = 0;
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
    tree_in->SetBranchAddress("nPrompt", 	&nPrompt);
    tree_in->SetBranchAddress("promptIndex", 	promptIndex);
    tree_in->SetBranchAddress("nRand", 	&nRand);
    tree_in->SetBranchAddress("randIndex", randIndex);
    tree_in->SetBranchAddress("missing.", &missing);
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
    tree_out->Branch("missing.", &missing, 32000, 0);
}


void    GTreeTagger::SetTagger(const Int_t _NTagged, const Int_t* _Tagged_ch, const Double_t* _Tagged_t, const Double_t* _Photonbeam_E, const TLorentzVector* missingVector)
{
    nTagged = 0;
    for(int i=0; i<_NTagged; i++)
    {
        tagged_ch[nTagged]      = _Tagged_ch[nTagged];
        tagged_t[nTagged]       = _Tagged_t[nTagged];
        photonbeam_E[nTagged]   = _Photonbeam_E[nTagged];
        new((*missing)[nTagged]) TLorentzVector(missingVector[nTagged]);
        nTagged++;
    }
}

void    GTreeTagger::RemovePrompt(const Int_t index)
{
    for(int i=index+1; i<nPrompt; i++)
    {
        promptIndex[i-1]    = promptIndex[i];
    }
    nPrompt--;
}

void    GTreeTagger::RemoveRand(const Int_t index)
{
    for(int i=index+1; i<nRand; i++)
    {
        randIndex[i-1]    = randIndex[i];
    }
    nRand--;
}

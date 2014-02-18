#include "GTreeParticle.h"


using namespace std;


GTreeParticle::GTreeParticle()    :
    photons(new TClonesArray("TLorentzVector", 64)),
    protons(new TClonesArray("TLorentzVector", 64)),
    nTagged(0)
{

}

GTreeParticle::~GTreeParticle()
{
}

void    GTreeParticle::SetBranchAdresses()
{
    tree_in->SetBranchAddress("photons.", &photons);
    tree_in->SetBranchAddress("protons.", &protons);

    tree_in->SetBranchAddress("nTagged", &nTagged);
    tree_in->SetBranchAddress("tagged_ch", tagged_ch);
    tree_in->SetBranchAddress("tagged_t", tagged_t);
    tree_in->SetBranchAddress("photonbeam_E", photonbeam_E);
}

void    GTreeParticle::Clear()
{
    photons->Clear();
    protons->Clear();

    nTagged = 0;
}


Bool_t  GTreeParticle::Init(const char* filename_input, const char* filename_output, const Bool_t override)
{
    return  GTree::Init(filename_input, filename_output, override);
}


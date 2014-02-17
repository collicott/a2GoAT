#include "GTreeParticle.h"


using namespace std;


GTreeParticle::GTreeParticle()    :
    rootino(new TClonesArray("TLorentzVector", 64)),
    photon(new TClonesArray("TLorentzVector", 64)),
    elektron(new TClonesArray("TLorentzVector", 64)),
    piplus(new TClonesArray("TLorentzVector", 64)),
    proton(new TClonesArray("TLorentzVector", 64)),
    neutron(new TClonesArray("TLorentzVector", 64)),
    nTagged(0)
{
    /*file    = TFile::Open(filename);

   TreeFile.cd();
        tree.SetDirectory(dynamic_cast<TDirectory*>(&TreeFile));
        tree.Branch("rootino.", &rootino, sizeof(TLorentzVector)*32, 0);
        tree.Branch("photon.", &photon, sizeof(TLorentzVector)*32, 0);
        tree.Branch("elektron.", &elektron, sizeof(TLorentzVector)*32, 0);
        tree.Branch("piplus.", &piplus, sizeof(TLorentzVector)*32, 0);
        tree.Branch("proton.", &proton, sizeof(TLorentzVector)*32, 0);
        tree.Branch("neutron.", &neutron, sizeof(TLorentzVector)*32, 0);
    }*/
}

GTreeParticle::~GTreeParticle()
{
}

void    GTreeParticle::SetBranchAdresses()
{
    tree_in->SetBranchAddress("rootino.", &rootino);
    tree_in->SetBranchAddress("photon.", &photon);
    tree_in->SetBranchAddress("elektron.", &elektron);
    tree_in->SetBranchAddress("piplus.", &piplus);
    tree_in->SetBranchAddress("proton.", &proton);
    tree_in->SetBranchAddress("neutron.", &neutron);

    tree_in->SetBranchAddress("nTagged", &nTagged);
    tree_in->SetBranchAddress("tagged_ch", tagged_ch);
    tree_in->SetBranchAddress("tagged_t", tagged_t);
    tree_in->SetBranchAddress("photonbeam_E", photonbeam_E);
}

void    GTreeParticle::Clear()
{
    rootino->Clear();
    photon->Clear();
    elektron->Clear();
    piplus->Clear();
    proton->Clear();
    neutron->Clear();

    nTagged = 0;
}


Bool_t  GTreeParticle::Init(const char* filename_input, const char* filename_output, const Bool_t override)
{
    return  GTree::Init(filename_input, filename_output, override);
}


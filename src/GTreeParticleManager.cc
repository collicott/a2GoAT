#include "GTreeParticleManager.h"


GTreeParticleManager::GTreeParticleManager(TFile &TreeFile)    :
    tree("GoAT", "GoAT_tree"),
    rootino("TLorentzVector", 64),
    photon("TLorentzVector", 64),
    elektron("TLorentzVector", 64),
    piplus("TLorentzVector", 64),
    proton("TLorentzVector", 64),
    neutron("TLorentzVector", 64)
{
    TreeFile.cd();
    tree.SetDirectory(dynamic_cast<TDirectory*>(&TreeFile));
    tree.Branch("rootino.", &rootino, sizeof(TLorentzVector)*32, 0);
    tree.Branch("photon.", &photon, sizeof(TLorentzVector)*32, 0);
    tree.Branch("elektron.", &elektron, sizeof(TLorentzVector)*32, 0);
    tree.Branch("piplus.", &piplus, sizeof(TLorentzVector)*32, 0);
    tree.Branch("proton.", &proton, sizeof(TLorentzVector)*32, 0);
    tree.Branch("neutron.", &neutron, sizeof(TLorentzVector)*32, 0);

    tree.Branch("nTagged", &nTagged, "nTagged/i");
    tree.Branch("tagged_ch", tagged_ch, "tagged_ch[nTagged]/i");
    tree.Branch("tagged_t", tagged_t, "tagged_t[nTagged]/D");
    tree.Branch("photonbeam_E", photonbeam_E, "photonbeam_E[nTagged]/D");

}

GTreeParticleManager::~GTreeParticleManager()
{

}



void    GTreeParticleManager::Reconstruct()
{
    rootino.Clear();
    photon.Clear();
    elektron.Clear();
    piplus.Clear();
    proton.Clear();
    neutron.Clear();

    for(int i=0; i<GetNParticles(); i++)
    {
        new(rootino[i]) TLorentzVector(GetVector(i));
        //cout << "count" << rootino.GetEntriesFast() << endl;
    }

    tree.Fill();
}

void 	GTreeParticleManager::Analyse()
{
    FindValidAcquEvents();
    OpenTreeRawEvent();
    OpenTreeTagger();
    TraverseAcquEntries();
}


Bool_t	GTreeParticleManager::Write(TFile& TreeFile)
{
    TreeFile.cd();
    tree.SetDirectory(dynamic_cast<TDirectory*>(&TreeFile));
    tree.Write();
}


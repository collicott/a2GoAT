#include "GTreeParticleManager.h"


GTreeParticleManager::GTreeParticleManager(TFile &TreeFile)    :
    tree("GoAT", "GoAT_tree"),
    photons("TLorentzVector", 64),
    protons("TLorentzVector", 64)
{
    TreeFile.cd();
    tree.SetDirectory(dynamic_cast<TDirectory*>(&TreeFile));
    tree.Branch("photons.", &photons, sizeof(TLorentzVector)*32, 0);
    tree.Branch("protons.", &protons, sizeof(TLorentzVector)*32, 0);

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
    photons.Clear();

    for(int i=0; i<GetNParticles(); i++)
    {
        new(photons[i]) TLorentzVector(GetVector(i));
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


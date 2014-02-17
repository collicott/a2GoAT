#include "GTree.h"



GTree::GTree():
    file(0),
    tree(0)
{

    /*tree    = new TTree("GTree","GTree");
    tree->SetDirectory(file);

    tree->Branch("nParticle",&nParticle,"nParticle/i");
    tree->Branch("Px",Px,"Px[nParticle]/D");
    tree->Branch("Py",Py,"Py[nParticle]/D");
    tree->Branch("Pz",Pz,"Pz[nParticle]/D");
    tree->Branch("E",E,"E[nParticle]/D");

    tree->Branch("nTagged",&nTagged,"nTagged/i");
    tree->Branch("tagged_ch",tagged_ch,"tagged_ch[nTagged]/i");
    tree->Branch("photonbeam_E",photonbeam_E,"photonbeam_E[nTagged]/D");

    OpenAcquFile(infilename);
    OpenTreeRawEvent();
    OpenTreeTagger();
    FindValidAcquEvents();*/
}

GTree::~GTree()
{
    if(tree)
        delete tree;
    if(file)
        delete file;
}

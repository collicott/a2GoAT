#include "GTreeMeson.h"

using namespace std;


GTreeMeson::GTreeMeson(const TString& _Name)    :
    GTreeParticle(_Name)
{

}

GTreeMeson::~GTreeMeson()
{

}
/*
void    GTreeMeson::Reconstruct2g()
{
    TLorentzVector  meson(*(TLorentzVector*)photons->At(0) + *(TLorentzVector*)photons->At(1));
    Double_t        ChiSq[3];

    ChiSq[0]    = (MASS_PI0 - meson.M())/pi0Width;
    ChiSq[0]   *= ChiSq[0];
    ChiSq[1]    = (MASS_ETA - meson.M())/etaWidth;
    ChiSq[1]   *= ChiSq[1];
    ChiSq[2]    = (MASS_ETAP - meson.M())/etapWidth;
    ChiSq[2]   *= ChiSq[2];

    Double_t    minChiSq    = ChiSq[0];
    UInt_t      minIndex    = 0;
    if(ChiSq[1]<=minChiSq)
    {
        minChiSq    = ChiSq[1];
        minIndex    = 1;
    }
    if(ChiSq[2]<=minChiSq)
        minIndex    = 2;

    switch(minIndex)
    {
    case 0:
        new((*pi0)[0]) TLorentzVector(meson);
        break;
    case 1:
        new((*eta)[0]) TLorentzVector(meson);
        break;
    case 2:
        new((*etap)[0]) TLorentzVector(meson);
        break;
    }

    Fill();
}

void    GTreeMeson::Reconstruct3g()
{
    TLorentzVector  meson[3];
                    meson[0] = (*(TLorentzVector*)photons->At(1) + *(TLorentzVector*)photons->At(2));
                    meson[1] = (*(TLorentzVector*)photons->At(0) + *(TLorentzVector*)photons->At(2));
                    meson[2] = (*(TLorentzVector*)photons->At(0) + *(TLorentzVector*)photons->At(1));
                    Double_t        ChiSq[3][3];

    for(int i=0; i<3; i++)
    {
        ChiSq[i][0]    = (MASS_PI0 - meson[i].M())/pi0Width;
        ChiSq[i][0]   *= ChiSq[i][0];
        ChiSq[i][1]    = (MASS_ETA - meson[i].M())/etaWidth;
        ChiSq[i][1]   *= ChiSq[i][1];
        ChiSq[i][2]    = (MASS_ETAP - meson[i].M())/etapWidth;
        ChiSq[i][2]   *= ChiSq[i][2];
    }

    Double_t    minChiSq        = ChiSq[0][0];
    UInt_t      minIndex        = 0;
    UInt_t      minIndexPair    = 0;
    if(ChiSq[0][1]<=minChiSq)
    {
        minChiSq    = ChiSq[0][1];
        minIndex    = 1;
    }
    if(ChiSq[0][2]<=minChiSq)
    {
        minChiSq    = ChiSq[0][2];
        minIndex    = 2;
    }
    for(int i=1; i<3; i++)
    {
        if(ChiSq[i][0]<=minChiSq)
        {
            minChiSq    = ChiSq[i][0];
            minIndex    = 1;
            minIndexPair= i;
        }
        if(ChiSq[i][1]<=minChiSq)
        {
            minChiSq    = ChiSq[i][1];
            minIndex    = 1;
            minIndexPair= i;
        }
        if(ChiSq[i][2]<=minChiSq)
        {
            minChiSq    = ChiSq[i][2];
            minIndex    = 2;
            minIndexPair= i;
        }
    }
    TLorentzVector  p(*(TLorentzVector*)photons->At(minIndexPair));
    p.SetE(p.E()+MASS_PROTON);
    p.SetVect(TMath::Sqrt(p.E()*p.E() - MASS_PROTON*MASS_PROTON)*p.Vect().Unit());
    new((*protons)[0]) TLorentzVector(p);
    TLorentzVector  buf[2];
    int             help = 0;
    for(int i=0; i<3; i++)
    {
        if(i==minIndexPair)
            continue;
        buf[help]   = *((TLorentzVector*)photons->At(i));
        help++;
    }
    photons->Clear();
    new((*photons)[0]) TLorentzVector(buf[0]);
    new((*photons)[1]) TLorentzVector(buf[1]);

    switch(minIndex)
    {
    case 0:
        new((*pi0)[0]) TLorentzVector(meson[minIndexPair]);
        break;
    case 1:
        new((*eta)[0]) TLorentzVector(meson[minIndexPair]);
        break;
    case 2:
        new((*etap)[0]) TLorentzVector(meson[minIndexPair]);
        break;
    }

    Fill();
}

void    GTreeMeson::Reconstruct6g()
{

}

void    GTreeMeson::Reconstruct7g()
{

}

void    GTreeMeson::Reconstruct10g()
{

}

void    GTreeMeson::Reconstruct11g()
{

}

*/

void    GTreeMeson::SetBranchAdresses()
{
    tree_in->SetBranchAddress("EventNumber",&EventNumber);
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    tree_in->SetBranchAddress("nDaughters",daughters);
    tree_in->SetBranchAddress("nDaughterPDG",daughterPDG);
    tree_in->SetBranchAddress("nDaughterIndices",daughterIndices);
}

void    GTreeMeson::SetBranches()
{
    tree_out->Branch("EventNumber",&EventNumber,"EventNumber/i");
    tree_out->Branch("nParticles",&nParticles,"nParticles/i");
    tree_out->Branch("particles.", &particles, 32000, 0);
    tree_out->Branch("nDaughters",daughters,"nDaughters[nParticles]/I");
    tree_out->Branch("nDaughterPDG",daughterPDG,"nDaughterPDG[nParticles][nDaughters]/I");
    tree_out->Branch("nDaughterIndices",daughterIndices,"nDaughterIndices[nParticles][nDaughters]/I");
}

/*Bool_t  GTreeMeson::Init(const char* filename_input, const char* filename_output, const Bool_t override)
{
    if(!GTree::Init(filename_input, filename_output, override))
        return kFALSE;

    tree_out->Branch("pi0.", &pi0, sizeof(TLorentzVector)*32, 0);
    tree_out->Branch("eta.", &eta, sizeof(TLorentzVector)*32, 0);
    tree_out->Branch("etap.", &etap, sizeof(TLorentzVector)*32, 0);

    for(int i=0; i<tree_in->GetEntries(); i++)
    {
        pi0->Clear();
        eta->Clear();
        etap->Clear();
        GetEntry(i);
        switch(photons->GetEntriesFast())
        {
        case 2:
            //Reconstruct2g();
            break;
        case 3:
            Reconstruct3g();
            break;
        }
    }

    Write();
}*/







int		GTreeMeson::perm6g[15][6]=
{
    {0,1,2,3,4,5},
    {0,1,2,4,3,5},
    {0,1,2,5,4,3},

    {0,2,1,3,4,5},
    {0,2,1,4,3,5},
    {0,2,1,5,4,3},

    {0,3,2,1,4,5},
    {0,3,2,4,1,5},
    {0,3,2,5,4,1},

    {0,4,2,3,1,5},
    {0,4,2,1,3,5},
    {0,4,2,5,1,3},

    {0,5,2,3,4,1},
    {0,5,2,4,3,1},
    {0,5,2,1,4,3}
};

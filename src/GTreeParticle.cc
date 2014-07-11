#include "GTreeParticle.h"
#include "GTreeManager.h"

#include <TCanvas.h>

using namespace std;


GTreeParticle::GTreeParticle(GTreeManager *Manager, const TString& _Name)    :
    GTree(Manager,_Name),
    nParticles(0),
    particles(new TClonesArray("TLorentzVector", GTreeParticle_MaxEntries))
{
    for(int i=0; i<GTreeParticle_MaxEntries; i++)
    {
        Apparatus[i]    = 0;
        time[i]         = 0;
        clusterSize[i]  = 0;
        d_E[i]          = 0;
        WC0_E[i]        = 0;
        WC1_E[i]        = 0;
    }
}

GTreeParticle::~GTreeParticle()
{
    if (particles)  delete particles;
}

void    GTreeParticle::SetBranchAdresses()
{
    tree_in->SetBranchAddress("nParticles",&nParticles);
    tree_in->SetBranchAddress("particles.", &particles);
    tree_in->SetBranchAddress("Apparatus",Apparatus);
    tree_in->SetBranchAddress("time", time);
    tree_in->SetBranchAddress("clusterSize", clusterSize);
    tree_in->SetBranchAddress("d_E", d_E);
    tree_in->SetBranchAddress("WC0_E", WC0_E);
    tree_in->SetBranchAddress("WC1_E", WC1_E);
}

void    GTreeParticle::SetBranches()
{
    tree_out->Branch("nParticles",&nParticles, "nParticles/i");
    tree_out->Branch("particles.", &particles, 32000, 0);
    tree_out->Branch("Apparatus", Apparatus, "Apparatus[nParticles]/b");
    tree_out->Branch("time", time, "time[nParticles]/D");
    tree_out->Branch("clusterSize", clusterSize, "clusterSize[nParticles]/b");
    tree_out->Branch("d_E", d_E, "d_E[nParticles]/D");
    tree_out->Branch("WC0_E", WC0_E, "WC0_E[nParticles]/D");
    tree_out->Branch("WC1_E", WC1_E, "WC1_E[nParticles]/D");
}


Bool_t	GTreeParticle::Write()
{
    if(!manager->file_out)          return kFALSE;
    if(!tree_out)                   return kFALSE;
    if(!IsOpenForOutput())          return kFALSE;

    TCanvas c1("c1");
    c1.cd();
    tree_out->Draw("nParticles>>htmp(1,0,1)");
    TH1F* hist = (TH1F*)gDirectory->Get("htmp");
    //std::cout << hist->GetEntries()<< "\t" << hist->GetBinContent(hist->GetBin(1)) << std::endl;
    if(hist->GetEntries() == hist->GetBinContent(hist->GetBin(1)))
    {
        std::cout << "tree" << GetName() << " has not been written to disk. All Events have 0 " << GetName() << "." << std::endl;
        saveToFile  = false;
        return kTRUE;
    }

    return GTree::Write();
}

void    GTreeParticle::AddParticle(const TLorentzVector& vec, const UChar_t _Apparatus, const Double_t _d_E, const Double_t _WC0_E, const Double_t _WC1_E, const Double_t _Time, const UChar_t _ClusterSize)
{
    Apparatus[nParticles]   = _Apparatus;
    time[nParticles]        = _Time;
    clusterSize[nParticles] = _ClusterSize;
    d_E[nParticles]         = _d_E;
    WC0_E[nParticles]       = _WC0_E;
    WC0_E[nParticles]       = _WC1_E;
    new((*particles)[nParticles]) TLorentzVector(vec);
    nParticles++;
    manager->countReconstructed++;
}


void    GTreeParticle::RemoveAllParticles()
{
    manager->countReconstructed -= nParticles;
    Clear();
}


void    GTreeParticle::RemoveParticles(const Int_t nIndices, const Int_t* indices)
{
    Int_t*  sort    = new Int_t[nIndices];
    TMath::Sort(nIndices, indices, sort);
    for(int i=0; i<nIndices; i++)
    {
        nParticles--;
        if(sort[i] != nParticles)
        {
            Apparatus[sort[i]]  = Apparatus[nParticles];
            time[sort[i]]       = time[nParticles];
            clusterSize[sort[i]]= clusterSize[nParticles];
            d_E[sort[i]]        = d_E[nParticles];
            WC0_E[sort[i]]      = WC0_E[nParticles];
            WC1_E[sort[i]]      = WC1_E[nParticles];
            //particles->RemoveAt(sort[i]);
            new((*particles)[sort[i]]) TLorentzVector(*((TLorentzVector*)particles->At(nParticles)));
        }
        particles->RemoveAt(nParticles);
    }
    manager->countReconstructed -= nIndices;
}


void    GTreeParticle::PrintParticle(const Int_t i) const
{
    cout << "\tParticle " << i << ": " << endl;
    cout << "\tPx: " << Particle(i).Px() << "   Py: " << Particle(i).Py() << "   Pz: " << Particle(i).Pz() << "   E: " << Particle(i).E() << endl;
    cout << "\tApparatus: " << (Int_t)Apparatus[i] << "   clusterSize: " << (Int_t)clusterSize[i]  << endl;
    cout << "\td_E: " << d_E[i] << "   WC0_E: " << WC0_E[i] << "   WC1_E: " << WC1_E[i]  << endl;
}

void    GTreeParticle::Print() const
{
    GTree::Print();
    cout << "nParticles: " << nParticles << endl;
    for(int i=0; i<nParticles; i++)
        PrintParticle(i);
}

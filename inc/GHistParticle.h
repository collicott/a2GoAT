#ifndef __GHistParticle_h__
#define __GHistParticle_h__


#include <TDirectory.h>
#include <TH1D.h>
#include <TH1I.h>
#include <TLorentzVector.h>

class  GHistParticle
{
private:
    TDirectory* dir;

    TH1D*   Px;
    TH1D*   Py;
    TH1D*   Pz;
    TH1D*   E;
    TH1D*   M;
    TH1D*   Theta;
    TH1D*   Phi;
protected:

public:
    GHistParticle(TDirectory *_Dir);
    virtual ~GHistParticle();

            void    Add(const GHistParticle *hist, const Double_t scale);
    inline  void    Fill(const TLorentzVector& vec);
    virtual void    Write();
};

void    GHistParticle::Fill(const TLorentzVector& vec)
{
    Px->Fill(vec.Px());
    Py->Fill(vec.Py());
    Pz->Fill(vec.Pz());
    E->Fill(vec.E());
    M->Fill(vec.M());
    Theta->Fill(vec.Theta()*TMath::RadToDeg());
    Phi->Fill(vec.Phi()*TMath::RadToDeg());
}


#endif

#include "GHistTaggedMeson.h"




GHistTaggedMeson::GHistTaggedMeson(TDirectory* _Dir, const Int_t type):
    dir(_Dir),
    dice(kFALSE)
{
    dir->cd();
    if(type == FLAG_ETAP)
        gDirectory->mkdir("etap");
    else if(type == FLAG_ETA)
        gDirectory->mkdir("eta");
    else
        gDirectory->mkdir("pi0");
    dir->cd();
    gDirectory->mkdir("photon0");
    dir->cd();
    gDirectory->mkdir("photon1");
    dir->cd();
    if(type == FLAG_ETAP)
        meson    = new GHistTaggedParticle(gDirectory->GetDirectory("etap"));
    else if(type == FLAG_ETA)
        meson    = new GHistTaggedParticle(gDirectory->GetDirectory("eta"));
    else
        meson    = new GHistTaggedParticle(gDirectory->GetDirectory("pi0"));
    dir->cd();
    photon[0]= new GHistTaggedParticle(gDirectory->GetDirectory("photon0"));
    dir->cd();
    photon[1]= new GHistTaggedParticle(gDirectory->GetDirectory("photon1"));
    dir->cd();
}

GHistTaggedMeson::~GHistTaggedMeson()
{
    if(meson)  delete  meson;
    if(photon[0])  delete  photon[0];
    if(photon[1])  delete  photon[1];
}


void    GHistTaggedMeson::Write()
{
    meson->Write();
    photon[0]->Write();
    photon[1]->Write();
    dir->cd();

}

void    GHistTaggedMeson::Add(const GHistTaggedMeson *hist, const Double_t scale)
{
    meson->Add(hist->meson, scale);
    photon[0]->Add(hist->photon[0], scale);
    photon[1]->Add(hist->photon[1], scale);
}

void    GHistTaggedMeson::Divide(const GHistTaggedMeson *hist)
{
    meson->Divide(hist->meson);
    photon[0]->Divide(hist->photon[0]);
    photon[1]->Divide(hist->photon[1]);
}






GHistTagged3Meson::GHistTagged3Meson(TDirectory* _Dir, const Int_t _Type):
    dir(_Dir),
    type(_Type),
    dice(0)
{
    dir->cd();
    if(type == FLAG_ETAP)
        gDirectory->mkdir("etap");
    else
        gDirectory->mkdir("eta");
    dir->cd();
    gDirectory->mkdir("pi0_0");
    dir->cd();
    gDirectory->mkdir("pi0_1");
    dir->cd();
    if(type == FLAG_ETAP)
        gDirectory->mkdir("eta");
    else
        gDirectory->mkdir("pi0_2");

    dir->cd();
    if(type == FLAG_ETAP)
        meson = new GHistTaggedParticle(gDirectory->GetDirectory("etap"));
    else
        meson = new GHistTaggedParticle(gDirectory->GetDirectory("eta"));
    dir->cd();
    daughter[0] = new GHistTaggedMeson(gDirectory->GetDirectory("pi0_0"));
    dir->cd();
    daughter[1] = new GHistTaggedMeson(gDirectory->GetDirectory("pi0_1"));
    dir->cd();
    if(type == FLAG_ETAP)
        daughter[2] = new GHistTaggedMeson(gDirectory->GetDirectory("eta"));
    else
        daughter[2] = new GHistTaggedMeson(gDirectory->GetDirectory("pi0_2"));
    dir->cd();
}

GHistTagged3Meson::~GHistTagged3Meson()
{
    if(meson)   delete  meson;
    if(daughter[0])   delete  daughter[0];
    if(daughter[1])   delete  daughter[1];
    if(daughter[2])   delete  daughter[2];
}


void    GHistTagged3Meson::Write()
{
    meson->Write();
    daughter[0]->Write();
    daughter[1]->Write();
    daughter[2]->Write();
    dir->cd();

}







GHistTaggedEta::GHistTaggedEta(TDirectory* _Dir):
    dir(_Dir)
{
    dir->cd();
    gDirectory->mkdir("eta");
    dir->cd();
    gDirectory->mkdir("eta2g");
    dir->cd();
    gDirectory->mkdir("eta6g");

    dir->cd();
    eta = new GHistTaggedParticle(gDirectory->GetDirectory("eta"));
    dir->cd();
    eta2g = new GHistTaggedMeson(gDirectory->GetDirectory("eta2g"), GHistTaggedMeson::FLAG_ETA);
    dir->cd();
    eta6g = new GHistTagged3Meson(gDirectory->GetDirectory("eta6g"), GHistTagged3Meson::FLAG_ETA);
    dir->cd();
}

GHistTaggedEta::~GHistTaggedEta()
{
    if(eta)   delete  eta;
    if(eta2g)   delete  eta2g;
    if(eta6g)   delete  eta6g;
}


void    GHistTaggedEta::Write()
{
    eta2g->Write();
    eta6g->Write();
    dir->cd();
    eta->Add(eta2g->meson, 1);
    eta->Add(eta6g->meson, 1);
    eta->Write();
    dir->cd();
}





GHistTaggedEtap::GHistTaggedEtap(TDirectory* _Dir):
    dir(_Dir)
{
    dir->cd();
    gDirectory->mkdir("etap");
    dir->cd();
    gDirectory->mkdir("etap2g");
    dir->cd();
    gDirectory->mkdir("etap6g");

    dir->cd();
    etap = new GHistTaggedParticle(gDirectory->GetDirectory("etap"));
    dir->cd();
    etap2g = new GHistTaggedMeson(gDirectory->GetDirectory("etap2g"), GHistTaggedMeson::FLAG_ETAP);
    dir->cd();
    etap6g = new GHistTagged3Meson(gDirectory->GetDirectory("etap6g"), GHistTagged3Meson::FLAG_ETAP);
    dir->cd();
}

GHistTaggedEtap::~GHistTaggedEtap()
{
    if(etap)   delete  etap;
    if(etap2g)   delete  etap2g;
    if(etap6g)   delete  etap6g;
}


void    GHistTaggedEtap::Write()
{
    etap2g->Write();
    etap6g->Write();
    dir->cd();
    etap->Add(etap2g->meson, 1);
    etap->Add(etap6g->meson, 1);
    etap->Write();
    dir->cd();
}

#ifndef __GHistTaggedMeson_h__
#define __GHistTaggedMeson_h__


#include "GHistTaggedParticle.h"





class  GHistTaggedMeson
{
public:
    enum
    {
        FLAG_PI0    = 0,
        FLAG_ETA    = 1,
        FLAG_ETAP   = 2
    };
private:
    TDirectory*     dir;

    GHistTaggedParticle*    meson;
    GHistTaggedParticle*    photon[2];
    Bool_t                  dice;

protected:

public:
    GHistTaggedMeson(TDirectory* _Dir, const Int_t type = FLAG_PI0);
    virtual ~GHistTaggedMeson();

    inline  void    FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillPromptMeson(const TLorentzVector& vec)   {meson->FillPromptParticle(vec);}
    inline  void    FillRandMeson(const TLorentzVector& vec)     {meson->FillRandParticle(vec);}
    inline  void    FillPromptPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1);
    inline  void    FillRandPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1);
    virtual void    Write();
};

void    GHistTaggedMeson::FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    meson->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    photon[0]->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    photon[1]->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}
void    GHistTaggedMeson::FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    meson->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    photon[0]->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    photon[1]->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}
void    GHistTaggedMeson::FillPromptPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1)
{
    if(dice)
    {
        photon[0]->FillPromptParticle(vec0);
        photon[1]->FillPromptParticle(vec1);
        dice = kFALSE;
    }
    else
    {
        photon[0]->FillPromptParticle(vec1);
        photon[1]->FillPromptParticle(vec0);
        dice = kTRUE;
    }
}
void    GHistTaggedMeson::FillRandPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1)
{
    if(dice)
    {
        photon[0]->FillRandParticle(vec0);
        photon[1]->FillRandParticle(vec1);
        dice = kFALSE;
    }
    else
    {
        photon[0]->FillRandParticle(vec1);
        photon[1]->FillRandParticle(vec0);
        dice = kTRUE;
    }
}







class  GHistTagged3Meson
{
public:
    enum
    {
        FLAG_ETA  = 0,
        FLAG_ETAP = 1
    };
private:
    TDirectory*     dir;

    GHistTaggedParticle*    meson;
    GHistTaggedMeson*       daughter[3];
    Int_t                   type;
    Int_t                   dice;

protected:

public:
    GHistTagged3Meson(TDirectory* _Dir, const Int_t _Type = FLAG_ETA);
    virtual ~GHistTagged3Meson();

    inline  void    FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillPromptMeson(const TLorentzVector& vec)   {meson->FillPromptParticle(vec);}
    inline  void    FillRandMeson(const TLorentzVector& vec)     {meson->FillRandParticle(vec);}
    inline  void    FillPromptDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2);
    inline  void    FillRandDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2);
    inline  void    FillPromptDaughterPhotons(const Int_t daughterMeson, const TLorentzVector& vec0, const TLorentzVector& vec1){daughter[daughterMeson]->FillPromptPhoton(vec0, vec1);}
    inline  void    FillRandDaughterPhotons(const Int_t daughterMeson, const TLorentzVector& vec0, const TLorentzVector& vec1)  {daughter[daughterMeson]->FillRandPhoton(vec0, vec1);}

    virtual void    Write();
};

void    GHistTagged3Meson::FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    meson->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    daughter[0]->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    daughter[1]->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    daughter[2]->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}
void    GHistTagged3Meson::FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    meson->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    daughter[0]->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    daughter[1]->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    daughter[2]->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}
void    GHistTagged3Meson::FillPromptDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2)
{
    if(type == FLAG_ETA)
    {
        switch(dice)
        {
        case 0:
            daughter[0]->FillPromptMeson(vec0);
            daughter[1]->FillPromptMeson(vec1);
            daughter[2]->FillPromptMeson(vec2);
            dice=1;
            break;
        case 1:
            daughter[0]->FillPromptMeson(vec1);
            daughter[1]->FillPromptMeson(vec2);
            daughter[2]->FillPromptMeson(vec0);
            dice=2;
            break;
        case 2:
            daughter[0]->FillPromptMeson(vec2);
            daughter[1]->FillPromptMeson(vec0);
            daughter[2]->FillPromptMeson(vec1);
            dice=0;
            break;
        }
    }
    else
    {
        switch(dice)
        {
        case 2:
        case 0:
            daughter[0]->FillPromptMeson(vec0);
            daughter[1]->FillPromptMeson(vec1);
            dice=1;
            break;
        case 1:
            daughter[0]->FillPromptMeson(vec1);
            daughter[1]->FillPromptMeson(vec0);
            dice=2;
            break;
        }
        daughter[2]->FillPromptMeson(vec2);
    }
}
void    GHistTagged3Meson::FillRandDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2)
{
    if(type == FLAG_ETA)
    {
        switch(dice)
        {
        case 0:
            daughter[0]->FillRandMeson(vec0);
            daughter[1]->FillRandMeson(vec1);
            daughter[2]->FillRandMeson(vec2);
            dice=1;
            break;
        case 1:
            daughter[0]->FillRandMeson(vec1);
            daughter[1]->FillRandMeson(vec2);
            daughter[2]->FillRandMeson(vec0);
            dice=2;
            break;
        case 2:
            daughter[0]->FillRandMeson(vec2);
            daughter[1]->FillRandMeson(vec0);
            daughter[2]->FillRandMeson(vec1);
            dice=0;
            break;
        }
    }
    else
    {
        switch(dice)
        {
        case 2:
        case 0:
            daughter[0]->FillRandMeson(vec0);
            daughter[1]->FillRandMeson(vec1);
            dice=1;
            break;
        case 1:
            daughter[0]->FillRandMeson(vec1);
            daughter[1]->FillRandMeson(vec0);
            dice=2;
            break;
        }
        daughter[2]->FillRandMeson(vec2);
    }
}




class  GHistTaggedPi0   : public GHistTaggedMeson
{
public:
    GHistTaggedPi0(TDirectory* _Dir)    : GHistTaggedMeson(_Dir)    {}
    virtual ~GHistTaggedPi0()                                       {}
};


class  GHistTagged3Pi0   : public GHistTagged3Meson
{
public:
    GHistTagged3Pi0(TDirectory* _Dir)    : GHistTagged3Meson(_Dir)    {}
    virtual ~GHistTagged3Pi0()                                       {}
};




class  GHistTaggedEta
{
private:
    TDirectory*     dir;

    GHistTaggedParticle*    eta;
    GHistTaggedMeson*       eta2g;
    GHistTagged3Meson*      eta6g;

protected:

public:
    GHistTaggedEta(TDirectory* _Dir);
    virtual ~GHistTaggedEta();

    inline  void    FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillPromptMeson(const TLorentzVector& vec)   {eta6g->FillPromptMeson(vec);}
    inline  void    FillRandMeson(const TLorentzVector& vec)     {eta6g->FillRandMeson(vec);}
    inline  void    FillPromptDaughterMeson(const TLorentzVector& vec)   {eta2g->FillPromptMeson(vec);}
    inline  void    FillRandDaughterMeson(const TLorentzVector& vec)     {eta2g->FillRandMeson(vec);}
    inline  void    FillPromptDaughterPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1)    {eta2g->FillPromptPhoton(vec0, vec1);}
    inline  void    FillRandDaughterPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1)      {eta2g->FillPromptPhoton(vec0, vec1);}
    inline  void    FillPromptDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2){eta6g->FillPromptDaughterMesons(vec0, vec1, vec2);}
    inline  void    FillRandDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2)  {eta6g->FillRandDaughterMesons(vec0, vec1, vec2);}
    inline  void    FillPromptDaughterPhotons(const Int_t daughterMeson, const TLorentzVector& vec0, const TLorentzVector& vec1){eta6g->FillPromptDaughterPhotons(daughterMeson, vec0, vec1);}
    inline  void    FillRandDaughterPhotons(const Int_t daughterMeson, const TLorentzVector& vec0, const TLorentzVector& vec1)  {eta6g->FillRandDaughterPhotons(daughterMeson, vec0, vec1);}

    virtual void    Write();
};
void    GHistTaggedEta::FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    eta->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    eta2g->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    eta6g->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}
void    GHistTaggedEta::FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    eta->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    eta2g->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    eta6g->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}




class  GHistTaggedEtap
{
private:
    TDirectory*     dir;

    GHistTaggedParticle*    etap;
    GHistTaggedMeson*       etap2g;
    GHistTagged3Meson*      etap6g;

protected:

public:
    GHistTaggedEtap(TDirectory* _Dir);
    virtual ~GHistTaggedEtap();

    inline  void    FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillPromptMeson(const TLorentzVector& vec)   {etap6g->FillPromptMeson(vec);}
    inline  void    FillRandMeson(const TLorentzVector& vec)     {etap6g->FillRandMeson(vec);}
    inline  void    FillPromptDaughterMeson(const TLorentzVector& vec)   {etap2g->FillPromptMeson(vec);}
    inline  void    FillRandDaughterMeson(const TLorentzVector& vec)     {etap2g->FillRandMeson(vec);}
    inline  void    FillPromptDaughterPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1)    {etap2g->FillPromptPhoton(vec0, vec1);}
    inline  void    FillRandDaughterPhoton(const TLorentzVector& vec0, const TLorentzVector& vec1)      {etap2g->FillPromptPhoton(vec0, vec1);}
    inline  void    FillPromptDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2){etap6g->FillPromptDaughterMesons(vec0, vec1, vec2);}
    inline  void    FillRandDaughterMesons(const TLorentzVector& vec0, const TLorentzVector& vec1, const TLorentzVector& vec2)  {etap6g->FillRandDaughterMesons(vec0, vec1, vec2);}
    inline  void    FillPromptDaughterPhotons(const Int_t daughterMeson, const TLorentzVector& vec0, const TLorentzVector& vec1){etap6g->FillPromptDaughterPhotons(daughterMeson, vec0, vec1);}
    inline  void    FillRandDaughterPhotons(const Int_t daughterMeson, const TLorentzVector& vec0, const TLorentzVector& vec1)  {etap6g->FillRandDaughterPhotons(daughterMeson, vec0, vec1);}

    virtual void    Write();
};
void    GHistTaggedEtap::FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    etap->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    etap2g->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    etap6g->FillPromptTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}
void    GHistTaggedEtap::FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    etap->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    etap2g->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
    etap6g->FillRandTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}


#endif

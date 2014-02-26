#ifndef __GHistTaggedParticle_h__
#define __GHistTaggedParticle_h__


#include "GHistParticle.h"


class  GHistTaggedParticle;

class  GHistTaggedParticleWindow
{
private:
    TDirectory*     dir;

    TH1D*           taggerTime;
    TH1D*           taggerE;
    TH1I*           taggerCh;
    GHistParticle*  particle;
    GHistParticle*  missing;

protected:

public:
    GHistTaggedParticleWindow(TDirectory *_Dir);
    virtual ~GHistTaggedParticleWindow();

            void    Add(const GHistTaggedParticleWindow *hist, const Double_t scale);
    inline  void    FillTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillParticle(const TLorentzVector& vec) {particle->Fill(vec);}
    inline  void    Fill(const TLorentzVector& vec, const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)    {FillParticle(vec); FillTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);}
    virtual void    Write();

    friend class GHistTaggedParticle;
};

void    GHistTaggedParticleWindow::FillTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    missing->Fill(mis);
    taggerTime->Fill(_TaggerTime);
    taggerE->Fill(_TaggerEnergy);
    taggerCh->Fill(_TaggerChannel);
}






class  GHistTaggedParticle
{
private:
    TDirectory*     dir;

    GHistTaggedParticleWindow*  diff;
    GHistTaggedParticleWindow*  prompt;
    GHistTaggedParticleWindow*  rand;

protected:

public:
    GHistTaggedParticle(TDirectory* _Dir);
    virtual ~GHistTaggedParticle();

            void    Add(const GHistTaggedParticle *hist, const Double_t scale);
    inline  void    FillPromptTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)   {prompt->FillTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);}
    inline  void    FillRandTagger(const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)     {rand->FillTagger(mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);}
    inline  void    FillPromptParticle(const TLorentzVector& vec)   {prompt->FillParticle(vec);}
    inline  void    FillRandParticle(const TLorentzVector& vec)     {rand->FillParticle(vec);}
    inline  void    FillPrompt(const TLorentzVector& vec, const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    inline  void    FillRand(const TLorentzVector& vec, const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel);
    virtual void    Write();
};

void    GHistTaggedParticle::FillPrompt(const TLorentzVector& vec, const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    prompt->Fill(vec, mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}
void    GHistTaggedParticle::FillRand(const TLorentzVector& vec, const TLorentzVector& mis, const Double_t _TaggerTime, const Double_t _TaggerEnergy, const Int_t _TaggerChannel)
{
    rand->Fill(vec, mis, _TaggerTime, _TaggerEnergy, _TaggerChannel);
}


#endif

#ifndef __GHistCut_h__
#define __GHistCut_h__


#include <GHist.h>

class  GHistCut
{
public:
    enum    FLAG_MESON
    {
        FLAG_PI0,
        FLAG_ETA,
        FLAG_ETAP
    };
    enum    FLAG_DECAY
    {
        FLAG_2GAMMA,
        FLAG_6GAMMA
    };

private:
    TDirectory* dir;

    FLAG_MESON  mesonType;
    FLAG_DECAY  decayType;
    GHistD** invMass;
    GHistD*  misMass;

protected:

public:
    GHistCut(TDirectory *_Dir, const FLAG_MESON _MesonType, FLAG_DECAY _DecayType);
    virtual ~GHistCut();

            void    Add(const GHistCut *hist, const Double_t scale);
    inline  void    Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass, const Double_t _MisMass);
    inline  void    Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t* _InvMass, const Double_t _MisMass);
    inline  void    Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass0, const Double_t _InvMass1, const Double_t _InvMass2, const Double_t _InvMass3, const Double_t _MisMass);
            void    Write();

    FLAG_MESON  GetMesonType()  {return mesonType;}
    FLAG_DECAY  GetDecayType()  {return decayType;}
};









class  GHistCutProton   :   public GHistCut
{
private:
    TH1D*   deltaPhiProtonMeson;
    TH1D*   deltaAngleProtonMis4V;

protected:

public:
    GHistCutProton(TDirectory *_Dir, const FLAG_MESON _MesonType, FLAG_DECAY _DecayType);
    virtual ~GHistCutProton();

            void    Add(const GHistCutProton *hist, const Double_t scale);
    inline  void    Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass, const Double_t _MisMass, const Double_t _DeltaPhiProtonMeson, const Double_t _DeltaAngleProtonMis4V);
    inline  void    Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t* _InvMass, const Double_t _MisMass, const Double_t _DeltaPhiProtonMeson, const Double_t _DeltaAngleProtonMis4V);
    inline  void    Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass0, const Double_t _InvMass1, const Double_t _InvMass2, const Double_t _InvMass3, const Double_t _MisMass, const Double_t _DeltaPhiProtonMeson, const Double_t _DeltaAngleProtonMis4V);
            void    Write();
};










void    GHistCut::Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass, const Double_t _MisMass)
{
    invMass[0]->Fill(taggerWindow, _InvMass);
    misMass->Fill(taggerWindow, _MisMass);
}
void    GHistCut::Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t* _InvMass, const Double_t _MisMass)
{
    for(int i=0; i<4; i++)
        invMass[i]->Fill(taggerWindow, _InvMass[i]);
    misMass->Fill(taggerWindow, _MisMass);
}
void    GHistCut::Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass0, const Double_t _InvMass1, const Double_t _InvMass2, const Double_t _InvMass3, const Double_t _MisMass)
{
    invMass[0]->Fill(taggerWindow, _InvMass0);
    invMass[1]->Fill(taggerWindow, _InvMass1);
    invMass[2]->Fill(taggerWindow, _InvMass2);
    invMass[3]->Fill(taggerWindow, _InvMass3);
    misMass->Fill(taggerWindow, _MisMass);
}




void    GHistCutProton::Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass, const Double_t _MisMass, const Double_t _DeltaPhiProtonMeson, const Double_t _DeltaAngleProtonMis4V)
{
    GHistCut::Fill(taggerWindow, _InvMass, _MisMass);
    deltaPhiProtonMeson->Fill(taggerWindow, _DeltaPhiProtonMeson);
    deltaAngleProtonMis4V->Fill(taggerWindow, _DeltaAngleProtonMis4V);
}
void    GHistCutProton::Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t* _InvMass, const Double_t _MisMass, const Double_t _DeltaPhiProtonMeson, const Double_t _DeltaAngleProtonMis4V)
{
    GHistCut::Fill(taggerWindow, _InvMass, _MisMass);
    deltaPhiProtonMeson->Fill(taggerWindow, _DeltaPhiProtonMeson);
    deltaAngleProtonMis4V->Fill(taggerWindow, _DeltaAngleProtonMis4V);
}
void    GHistCutProton::Fill(const GHist::FLAG_TAGGER_WINDOW taggerWindow, const Double_t _InvMass0, const Double_t _InvMass1, const Double_t _InvMass2, const Double_t _InvMass3, const Double_t _MisMass, const Double_t _DeltaPhiProtonMeson, const Double_t _DeltaAngleProtonMis4V)
{
    GHistCut::Fill(taggerWindow, _InvMass0, _InvMass1, _InvMass2, _InvMass3, _MisMass);
    deltaPhiProtonMeson->Fill(taggerWindow, _DeltaPhiProtonMeson);
    deltaAngleProtonMis4V->Fill(taggerWindow, _DeltaAngleProtonMis4V);
}

#endif

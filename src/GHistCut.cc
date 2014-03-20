#include "GHistCut.h"


using namespace std;

GHistCut::GHistCut(TDirectory *_Dir, const FLAG_MESON _MesonType, FLAG_DECAY _DecayType)  :
    dir(_Dir),
    mesonType(_MesonType),
    decayType(_DecayType)
{
    switch(decayType)
    {
    case FLAG_2GAMMA:
        invMass = new GHistD*[1];
        break;
        switch(mesonType)
        {
        case FLAG_PI0:
            invMass[0]  = new GHistD(dir, "InvMassPi0", "inv. Mass 2g of pi0", 300, 0, 300);
            break;
        case FLAG_ETA:
            invMass[0]  = new GHistD(dir, "InvMassEta", "inv. Mass 2g of eta", 1000, 0, 1000);
            break;
        case FLAG_ETAP:
            invMass[0]  = new GHistD(dir, "InvMassEtap", "inv. Mass 2g of etap", 2000, 0, 2000);
            break;
        }
        break;
    case FLAG_6GAMMA:
        invMass = new GHistD*[4];
        invMass[0]  = new GHistD(dir, "InvMassPi0a", "inv. Mass 2g of 1. pi0", 300, 0, 300);
        invMass[1]  = new GHistD(dir, "InvMassPi0b", "inv. Mass 2g of 2. pi0", 300, 0, 300);
        switch(mesonType)
        {
        case FLAG_ETA:
            invMass[2]  = new GHistD(dir, "InvMassPi0c", "inv. Mass 2g of 3. pi0", 300, 0, 300);
            invMass[3]  = new GHistD(dir, "InvMassEta", "inv. Mass 3 pi0 of eta", 1000, 0, 1000);
            break;
        case FLAG_ETAP:
            invMass[2]  = new GHistD(dir, "InvMassEta", "inv. Mass 2g of eta", 1000, 0, 1000);
            invMass[3]  = new GHistD(dir, "InvMassEtap", "inv. Mass 3 pi0 of etap", 2000, 0, 2000);
            break;
        }
        break;
    }
}

GHistCut::~GHistCut()
{
    switch(decayType)
    {
    case FLAG_2GAMMA:
        if(invMass[0]) delete invMass[0];
        break;
    case FLAG_6GAMMA:
        for(int i=0; i<4; i++)
            if(invMass[i]) delete invMass[i];
        break;
    }
    if(invMass) delete invMass;
}

void    GHistCut::Add(const GHistCut *hist, const Double_t scale)
{
    switch(decayType)
    {
    case FLAG_2GAMMA:
        invMass[0]->Add(hist->invMass[0], scale);
        break;
    case FLAG_6GAMMA:
        for(int i=0; i<4; i++)
            invMass[i]->Add(hist->invMass[i], scale);
        break;
    }
    misMass->Add(hist->misMass, scale);
}

void    GHistCut::Write()
{

    switch(decayType)
    {
    case FLAG_2GAMMA:
        invMass[0]->Write();
        break;
    case FLAG_6GAMMA:
        for(int i=0; i<4; i++)
            invMass[i]->Write();
        break;
    }
    misMass->Write();
}







GHistCutProton::GHistCutProton(TDirectory *_Dir, const FLAG_MESON _MesonType, FLAG_DECAY _DecayType)   :
    GHistCut(_Dir, _MesonType, _DecayType)
{
    switch(GetMesonType())
    {
    case FLAG_PI0:
        deltaPhiProtonMeson = new TH1D("deltaPhiProtonMeson", "phi difference between proton and pi0", 3600, 0, 360);
        break;
    case FLAG_ETA:
        deltaPhiProtonMeson = new TH1D("deltaPhiProtonMeson", "phi difference between proton and eta", 3600, 0, 360);
        break;
    case FLAG_ETAP:
        deltaPhiProtonMeson = new TH1D("deltaPhiProtonMeson", "phi difference between proton and etap", 3600, 0, 360);
        break;
    }
    deltaAngleProtonMis4V   = new TH1D("deltaAngleProtonMis4V", "angle difference between proton and missing 4Vector", 1800, 0, 180);
}

GHistCutProton::~GHistCutProton()
{
    if(deltaPhiProtonMeson)     delete deltaPhiProtonMeson;
    if(deltaAngleProtonMis4V)   delete deltaAngleProtonMis4V;
}




void    GHistCutProton::Add(const GHistCutProton *hist, const Double_t scale)
{
    GHistCut::Add(hist, scale);
    deltaPhiProtonMeson->Add(hist->deltaPhiProtonMeson, scale);
    deltaAngleProtonMis4V->Add(hist->deltaAngleProtonMis4V, scale);
}

void    GHistCutProton::Write()
{
    GHistCut::Write();
    deltaPhiProtonMeson->Write();
    deltaAngleProtonMis4V->Write();
}

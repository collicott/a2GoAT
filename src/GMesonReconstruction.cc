#include "GMesonReconstruction.h"


using namespace std;


GMesonReconstruction::GMesonReconstruction()    :
    pi0Width(22),
    etaWidth(40),
    etapWidth(60)
{
}

GMesonReconstruction::~GMesonReconstruction()
{

}

void  GMesonReconstruction::ProcessEvent()
{
    if(photons->GetNParticles() == 2)
    {
        pi0->Clear();
        eta->Clear();
        etap->Clear();
        Reconstruct2g();
        eventFlags->Fill();
        tagger->Fill();
        trigger->Fill();
        photons->Fill();
        protons->Fill();
        pi0->Fill();
        eta->Fill();
        etap->Fill();
    }
    else if(photons->GetNParticles() == 6)
    {
        pi0->Clear();
        eta->Clear();
        etap->Clear();
        Reconstruct6g();
        eventFlags->Fill();
        tagger->Fill();
        trigger->Fill();
        photons->Fill();
        protons->Fill();
        pi0->Fill();
        eta->Fill();
        etap->Fill();
    }
    /*if(photons->GetNParticles() == 10)
    {
        pi0->Clear();
        eta->Clear();
        etap->Clear();
        Reconstruct10g();
        eventFlags->Fill();
        tagger->Fill();
        photons->Fill();
        protons->Fill();
        pi0->Fill();
        eta->Fill();
        etap->Fill();
    }*/
}

Bool_t  GMesonReconstruction::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;
    if(!OpenPhotons())    return kFALSE;
    if(!OpenProtons())    return kFALSE;
    if(!OpenTagger())    return kFALSE;
    if(!OpenScalers())    return kFALSE;
    if(!OpenTrigger())    return kFALSE;
    if(!OpenEventFlags())    return kFALSE;


    if(!Create(output_filename))    return kFALSE;
    if(!CreateEtap())    return kFALSE;
    if(!CreateEta())    return kFALSE;
    if(!CreatePi0())    return kFALSE;
    if(!CreatePhotons())    return kFALSE;
    if(!CreateProtons())    return kFALSE;
    if(!CreateTagger())    return kFALSE;
    if(!CreateEventFlags())    return kFALSE;
    if(!CreateTrigger())    return kFALSE;
    scalers->Clone(*file_out);

    TraverseEntries(0, photons->GetNEntries()+1);

    if(!Write())    return kFALSE;
    return kTRUE;
}


void    GMesonReconstruction::Reconstruct2g()
{
    TLorentzVector  meson(photons->Particle(0) + photons->Particle(1));
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

    Int_t   daughter_pdg[2];
    daughter_pdg[0] = 22;
    daughter_pdg[1] = 22;
    Int_t   daughter_index[2];
    daughter_index[0] = 0;
    daughter_index[1] = 1;
    switch(minIndex)
    {
    case 0:
        pi0->AddParticle(meson,2,daughter_pdg,daughter_index);
        break;
    case 1:
        eta->AddParticle(meson,2,daughter_pdg,daughter_index);
        break;
    case 2:
        etap->AddParticle(meson,2,daughter_pdg,daughter_index);
        break;
    }
}


void    GMesonReconstruction::Reconstruct6g()
{
    TLorentzVector  meson[15][3];
    Double_t        help[2][3];
    Double_t        ChiSq[15][4];

    for(int i=0; i<15; i++)
    {
        meson[i][0] = photons->Particle(perm6g[i][0]) + photons->Particle(perm6g[i][1]);
        meson[i][1] = photons->Particle(perm6g[i][2]) + photons->Particle(perm6g[i][3]);
        meson[i][2] = photons->Particle(perm6g[i][4]) + photons->Particle(perm6g[i][5]);
        help[0][0]     = (MASS_ETA - meson[i][0].M())/etaWidth;
        help[0][1]     = (MASS_ETA - meson[i][1].M())/etaWidth;
        help[0][2]     = (MASS_ETA - meson[i][2].M())/etaWidth;
        help[1][0]     = (MASS_PI0 - meson[i][0].M())/pi0Width;
        help[1][1]     = (MASS_PI0 - meson[i][1].M())/pi0Width;
        help[1][2]     = (MASS_PI0 - meson[i][2].M())/pi0Width;
        ChiSq[i][0] = (help[0][0]*help[0][0]) + (help[1][1]*help[1][1]) + (help[1][2]*help[1][2]);
        ChiSq[i][1] = (help[1][0]*help[1][0]) + (help[0][1]*help[0][1]) + (help[1][2]*help[1][2]);
        ChiSq[i][2] = (help[1][0]*help[1][0]) + (help[1][1]*help[1][1]) + (help[0][2]*help[0][2]);
        ChiSq[i][3] = (help[1][0]*help[1][0]) + (help[1][1]*help[1][1]) + (help[1][2]*help[1][2]);
    }

    Double_t    minChiSq        = ChiSq[0][0];
    UInt_t      minDecayIndex   = 0;
    UInt_t      minIndex        = 0;

    for(int i=0; i<15; i++)
    {
        for(int d=0; d<4; d++)
        {
            if(ChiSq[i][d]<=minChiSq)
            {
                minChiSq        = ChiSq[i][d];
                minIndex        = i;
                minDecayIndex   = d;
            }
        }
    }

    Int_t   daughter_pdg[3];
    Int_t   daughter_index[3];
    if(minDecayIndex == 3)      //found 3Pi0
    {
        daughter_pdg[0] = 22;
        daughter_pdg[1] = 22;
        daughter_index[0] = perm6g[minIndex][0];
        daughter_index[1] = perm6g[minIndex][1];
        pi0->AddParticle(meson[minIndex][0], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][2];
        daughter_index[1] = perm6g[minIndex][3];
        pi0->AddParticle(meson[minIndex][1], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][4];
        daughter_index[1] = perm6g[minIndex][5];
        pi0->AddParticle(meson[minIndex][2], 2, daughter_pdg, daughter_index);

        TLorentzVector  reconstructedEta(meson[minIndex][0] + meson[minIndex][1] + meson[minIndex][2]);
        daughter_pdg[0] = 111;
        daughter_pdg[1] = 111;
        daughter_pdg[2] = 111;
        daughter_index[0] = 0;
        daughter_index[1] = 1;
        daughter_index[2] = 2;
        eta->AddParticle(reconstructedEta, 3, daughter_pdg, daughter_index);
        return;
    }

    //found Eta2Pi0

    if(minDecayIndex == 0)  //Eta is meson[i][0]
    {
        daughter_pdg[0] = 22;
        daughter_pdg[1] = 22;
        daughter_index[0] = perm6g[minIndex][0];
        daughter_index[1] = perm6g[minIndex][1];
        eta->AddParticle(meson[minIndex][0], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][2];
        daughter_index[1] = perm6g[minIndex][3];
        pi0->AddParticle(meson[minIndex][1], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][4];
        daughter_index[1] = perm6g[minIndex][5];
        pi0->AddParticle(meson[minIndex][2], 2, daughter_pdg, daughter_index);
    }
    else if(minDecayIndex == 1)  //Eta is meson[i][1]
    {
        daughter_pdg[0] = 22;
        daughter_pdg[1] = 22;
        daughter_index[0] = perm6g[minIndex][0];
        daughter_index[1] = perm6g[minIndex][1];
        pi0->AddParticle(meson[minIndex][0], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][2];
        daughter_index[1] = perm6g[minIndex][3];
        eta->AddParticle(meson[minIndex][1], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][4];
        daughter_index[1] = perm6g[minIndex][5];
        pi0->AddParticle(meson[minIndex][2], 2, daughter_pdg, daughter_index);
    }
    else if(minDecayIndex == 2)  //Eta is meson[i][2]
    {
        daughter_pdg[0] = 22;
        daughter_pdg[1] = 22;
        daughter_index[0] = perm6g[minIndex][0];
        daughter_index[1] = perm6g[minIndex][1];
        pi0->AddParticle(meson[minIndex][0], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][2];
        daughter_index[1] = perm6g[minIndex][3];
        pi0->AddParticle(meson[minIndex][1], 2, daughter_pdg, daughter_index);
        daughter_index[0] = perm6g[minIndex][4];
        daughter_index[1] = perm6g[minIndex][5];
        eta->AddParticle(meson[minIndex][2], 2, daughter_pdg, daughter_index);
    }

    TLorentzVector  reconstructedEtap(meson[minIndex][0] + meson[minIndex][1] + meson[minIndex][2]);
    daughter_pdg[0] = 221;
    daughter_pdg[1] = 111;
    daughter_pdg[2] = 111;
    daughter_index[0] = 0;
    daughter_index[1] = 0;
    daughter_index[2] = 1;
    etap->AddParticle(reconstructedEtap, 3, daughter_pdg, daughter_index);
}


void    GMesonReconstruction::Reconstruct10g()
{

}


Int_t		GMesonReconstruction::perm6g[15][6]=
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

Int_t		GMesonReconstruction::perm10g[27][10]=
{
    {0,1,2,3,4,5,6,7,8,9},
    {0,1,2,3,4,5,6,8,7,9},
    {0,1,2,3,4,5,6,9,8,7},

    {0,2,1,3,4,5,6,7,8,9},
    {0,2,1,3,4,5,6,8,7,9},
    {0,2,1,3,4,5,6,9,8,7},

    {0,3,2,1,4,5,6,7,8,9},
    {0,3,2,1,4,5,6,8,7,9},
    {0,3,2,1,4,5,6,9,8,7},

    {0,4,2,3,1,5,6,7,8,9},
    {0,4,2,3,1,5,6,8,7,9},
    {0,4,2,3,1,5,6,9,8,7},

    {0,5,2,3,4,1,6,7,8,9},
    {0,5,2,3,4,1,6,8,7,9},
    {0,5,2,3,4,1,6,9,8,7},

    {0,6,2,3,4,5,1,7,8,9},
    {0,6,2,3,4,5,1,8,7,9},
    {0,6,2,3,4,5,1,9,8,7},

    {0,7,2,3,4,5,6,1,8,9},
    {0,7,2,3,4,5,6,8,1,9},
    {0,7,2,3,4,5,6,9,8,1},

    {0,8,2,3,4,5,6,7,1,9},
    {0,8,2,3,4,5,6,1,7,9},
    {0,8,2,3,4,5,6,9,1,7},

    {0,9,2,3,4,5,6,7,8,1},
    {0,9,2,3,4,5,6,8,7,1},
    {0,9,2,3,4,5,6,1,8,7},
};

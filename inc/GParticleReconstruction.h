#ifndef __GParticleReconstruction_h__
#define __GParticleReconstruction_h__

#include <TCutG.h>


#include "GDataChecks.h"
#include "GCorrectScalers.h"
#include "GConfigFile.h"

#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0

#define	pdg_rootino 0

class	GParticleReconstruction : public GDataChecks, public GCorrectScalers, public GConfigFile
{
public:
    enum ReconstructionType
    {
        ReconstructionType_AllPhotons,
        ReconstructionType_AllProtons,
        ReconstructionType_PID_VETO
    };

private:
    ReconstructionType  CB_type;
    ReconstructionType  TAPS_type;

    char 		cutfilename[256];
    char 		cutname[256];

    TFile* 		CutFile;
    TCutG* 		Cut;
    TCutG* 		Cut_CB_proton;
    TCutG* 		Cut_CB_pion;
    TCutG*		Cut_CB_electron;
    TCutG* 		Cut_TAPS_proton;
    TCutG* 		Cut_TAPS_pion;
    TCutG*		Cut_TAPS_electron;

    Int_t 		ReconstructChargedParticles;
    Double_t	charged_theta_min;
    Double_t	charged_theta_max;

    Int_t		Cut_CB_proton_active;
    Int_t		Cut_TAPS_proton_active;
    Int_t 		Cut_proton_active;

    Int_t		Cut_CB_pion_active;
    Int_t		Cut_TAPS_pion_active;
    Int_t 		Cut_pion_active;

    Int_t		Cut_CB_electron_active;
    Int_t		Cut_TAPS_electron_active;
    Int_t 		Cut_electron_active;

    TCutG* 		Cut_proton;
    TCutG*		Cut_pion;
    TCutG*		Cut_electron;

    Int_t		ReconstructMesons;
    Double_t	meson_theta_min;
    Double_t	meson_theta_max;

    Double_t	width_pi0;
    Double_t	width_eta;
    Double_t	width_etaP;

    Int_t* 		Identified;
    Int_t* 		Charge;

    Int_t 		nParticles;
    Int_t 		nDaughterList;
    Int_t 		i;

    Double_t    CBTimeCut[2];
    Double_t    TAPSTimeCut[2];

    Bool_t      DoScalerCorrection;
    Bool_t      DoTrigger;
    Double_t    E_Sum;
    Int_t       multiplicity;

    Bool_t      Trigger();

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GParticleReconstruction();
    virtual ~GParticleReconstruction();

    static  Int_t   InputNeeded()   {return GTreeManager::TreeFlag_RawEvent;}
    static  Int_t   OutputNeeded()  {}

    void    SetCBTimeCut(const Double_t min, const Double_t max)    {CBTimeCut[0]=min; CBTimeCut[1]=max;}
    void    SetTAPSTimeCut(const Double_t min, const Double_t max)  {TAPSTimeCut[0]=min; TAPSTimeCut[1]=max;}
    void    SetScalerCorrection(const Bool_t value)                 {DoScalerCorrection = value;}
    void    SetTrigger(const Double_t esum, const Int_t mult)       {DoTrigger = kTRUE; E_Sum = esum; multiplicity = mult;}
    void    SetCBType(const ReconstructionType type)                {CB_type = type;}
    void    SetTAPSType(const ReconstructionType type)              {TAPS_type = type;}

    Bool_t	PostInit();
    void	InitEvent();
    void	CheckNeutrality();
    void 	PhotonReconstruction();
    void 	ChargedReconstruction();
    void 	MesonReconstruction();
    void	AddParticle(Int_t pdg_code, Int_t nindex, Int_t index_list[]);
    void	AddParticle(Int_t pdg_code, Int_t i)                    {Int_t index_list[1]; index_list[0] = i; AddParticle(pdg_code, 1, index_list);}

    TCutG*	OpenCutFile(Char_t* filename, Char_t* cutname);
};

#endif

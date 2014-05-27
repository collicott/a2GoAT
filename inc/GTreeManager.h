#ifndef __GTreeManager_h__
#define __GTreeManager_h__


#include <TLorentzVector.h>
#include <TH1.h>
#include "GTreeRawEvent.h"
#include "GTreeTagger.h"
#include "GTreeScaler.h"
#include "GTreeEvent.h"
#include "GTreeParticle.h"
#include "GTreeMeson.h"
#include "GTreeTrigger.h" //Added by James
#include "GTreeFit.h"



class  GTreeManager
{
public:
    enum    TreeFlag
    {
        TreeFlag_RawEvent   =      1,
        TreeFlag_Tagger     =      2,
        TreeFlag_Trigger    =      4,
        TreeFlag_Scalers    =      8,
        TreeFlag_EventFlags =     16,
        TreeFlag_Photons    =     32,
        TreeFlag_Electrons  =     64,
        TreeFlag_ChargedPi  =    128,
        TreeFlag_Protons    =    256,
        TreeFlag_Neutrons   =    512,
        TreeFlag_Pi0        =   1024,
        TreeFlag_Eta        =   2048,
        TreeFlag_Etap       =   4096,
        TreeFlag_Fit        =   8192
    };

private:
    TFile*  file_in;
    Bool_t  isWritten;

    //Bool_t  EntryChecking(const GTree* tree);
    Bool_t  CreateMeson(GTreeMeson*& mesonTree, const TString& _Name);
    Bool_t  CreateParticle(GTreeParticle*& particleTree, const TString& _Name);
    Bool_t  OpenMeson(GTreeMeson*& mesonTree, const TString& _Name);
    Bool_t  OpenParticle(GTreeParticle*& particleTree, const TString& _Name);

protected:
    TFile*          file_out;

    GTreeRawEvent*  rawEvent;
    GTreeTagger*    tagger;
    GTreeTrigger*   trigger; //Added by James
    GTreeScaler*    scalers;
    GTreeEvent*     eventFlags;
    GTreeParticle*  photons;
    GTreeParticle*  electrons;
    GTreeParticle*  chargedPi;
    GTreeParticle*  protons;
    GTreeParticle*  neutrons;
    GTreeMeson*     pi0;
    GTreeMeson*     eta;
    GTreeMeson*     etap;
    GTreeFit*		fitData;

            void    CloseFiles();
    virtual void    ProcessEvent() = 0;
    virtual Bool_t  Start() = 0;
            Bool_t  TraverseEntries(const UInt_t min, const UInt_t max);
            Bool_t  TraverseScalerEntries(const UInt_t min, const UInt_t max);
            Bool_t  Write();
            Bool_t  Write(const TNamed* object);

public:
    GTreeManager();
    virtual ~GTreeManager();

    static  Int_t   CheckInput(const char* input_filename);
    Bool_t  Start(const char* input_filename, const char* output_filename);

    friend  class GTree;
    friend  class GTreeMeson;
};

#endif

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
private:
    TFile*  file_in;

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
    GTreeParticle*  protons;
    GTreeMeson*     pi0;
    GTreeMeson*     eta;
    GTreeMeson*     etap;
    GTreeFit*		fitData;

            void    CloseFiles();
    virtual void    ProcessEvent() = 0;
            //void    SetMinEntry(const UInt_t num)   {minEntry = num;}
            //void    SetNEntries(const UInt_t num)   {nEntries = num;}
            Bool_t  TraverseEntries(const UInt_t min, const UInt_t max);
            Bool_t  TraverseScalerEntries(const UInt_t min, const UInt_t max);
            Bool_t  Write();
            Bool_t  Write(const TNamed* object);

public:
    GTreeManager();
    virtual ~GTreeManager();

    virtual Bool_t  Process() = 0;
            Bool_t  Process(const char* input_filename, const char* output_filename);

    friend  class GTree;
};

#endif

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
#include "GHistFile.h"
#include "GTreeTrigger.h" //Added by James



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

            void    CloseFiles();
            Bool_t  Create(const char* filename);
            Bool_t  CreateEtap()    {return CreateMeson(etap, TString("Etap"));}
            Bool_t  CreateEta()     {return CreateMeson(eta, TString("Eta"));}
            Bool_t  CreatePi0()     {return CreateMeson(pi0, TString("Pi0"));}
            Bool_t  CreatePhotons() {return CreateParticle(photons, TString("Photons"));}
            Bool_t  CreateProtons() {return CreateParticle(protons, TString("Protons"));}
            Bool_t  CreateEventFlags();
            Bool_t  CreateRawEvent();
            Bool_t  CreateTagger();
            Bool_t  CreateTrigger(); //Added by James
            Bool_t  CreateScalers();
            Bool_t  Open(const char* filename);
            Bool_t  OpenEtap()      {return OpenMeson(etap, TString("Etap"));}
            Bool_t  OpenEta()       {return OpenMeson(eta, TString("Eta"));}
            Bool_t  OpenPi0()       {return OpenMeson(pi0, TString("Pi0"));}
            Bool_t  OpenPhotons()   {return OpenParticle(photons, TString("Photons"));}
            Bool_t  OpenProtons()   {return OpenParticle(protons, TString("Protons"));}
            Bool_t  OpenEventFlags();
            Bool_t  OpenRawEvent();
            Bool_t  OpenTagger();
            Bool_t  OpenTrigger(); //Added by James
            Bool_t  OpenScalers();
    virtual void    ProcessEvent() = 0;
            //void    SetMinEntry(const UInt_t num)   {minEntry = num;}
            //void    SetNEntries(const UInt_t num)   {nEntries = num;}
            Bool_t  TraverseEntries(const UInt_t min, const UInt_t max);
            Bool_t  Write();
            Bool_t  Write(const TNamed* object);

public:
    GTreeManager();
    virtual ~GTreeManager();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0) = 0;
            Bool_t  ProcessFolder(const char* input_foldername, const char* output_foldername, const char* filePrefix, const char* fileSuffix, const char* outfilePrefix);
};

#endif

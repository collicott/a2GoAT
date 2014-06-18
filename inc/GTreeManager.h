#ifndef __GTreeManager_h__
#define __GTreeManager_h__


#include <TLorentzVector.h>
#include <TH1.h>
#include <TDatabasePDG.h>

#include "GConfigFile.h"
#include "GTreeRawEvent.h"
#include "GTreeTagger.h"
#include "GTreeLinPol.h"
#include "GTreeScaler.h"
#include "GTreeParticle.h"
#include "GTreeMeson.h"
#include "GTreeTrigger.h"
#include "GTreeDetectorHits.h"



class  GTreeManager : public GConfigFile
{
private:
    TFile*      file_in;
    TObjArray   readList;
    Bool_t      isWritten;

    UInt_t  nValidScalerReads;
    UInt_t  validScalerRead[GTreeScaler_MAX];
    UInt_t  eventNumberValidScalerRead[GTreeScaler_MAX];
    UInt_t  eventNumberBeforeValidScalerRead[GTreeScaler_MAX];
    UInt_t  currentEvent;

protected:
    TFile*          file_out;

    GTreeRawEvent*      rawEvent;
    GTreeTagger*        tagger;
    GTreeLinPol*        linpol;
    GTreeTrigger*       trigger;
    GTreeScaler*        scalers;
    GTreeDetectorHits*  detectorHits;
    GTreeParticle*      photons;
    GTreeParticle*      electrons;
    GTreeParticle*      chargedPi;
    GTreeParticle*      protons;
    GTreeParticle*      neutrons;
    GTreeMeson*         pi0;
    GTreeMeson*         eta;
    GTreeMeson*         etap;

    TDatabasePDG *pdgDB;


            void    CloseFiles();
            void    FillReadList()      {for(int l=0; l<readList.GetEntriesFast(); l++) ((GTree*)readList[l])->Fill();}
    virtual void    ProcessEvent() = 0;
    virtual Bool_t  Start() = 0;
            Bool_t  TraverseEntries(const UInt_t min, const UInt_t max);
            Bool_t  TraverseScalerEntries(const UInt_t min, const UInt_t max);
            Bool_t  TraverseValidEvents();
            Bool_t  Write();
            Bool_t  Write(const TNamed* object);

public:
    GTreeManager();
    virtual ~GTreeManager();

    static  Int_t   CheckInput(const char* input_filename);
            UInt_t  GetEventNumber()    const   {return currentEvent;}
            UInt_t  GetNEntries()       const;
    virtual Bool_t  Init() {}
            Bool_t  StartFile(const char* input_filename, const char* output_filename);

    friend  class GTree;
    friend  class GTreeParticle;
    friend  class GTreeMeson;
};

#endif

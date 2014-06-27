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


#include <stdio.h>
#include <TSystem.h>


class  GTreeManager : public GConfigFile
{
private:
    TFile*      file_in;
    TObjArray   treeList;
    TObjArray   treeCorreleatedToScalerReadList;
    TObjArray   readList;
    TObjArray   readCorreleatedToScalerReadList;
    TObjArray   writeList;
    Bool_t      isWritten;

    FILE*   debugFile;

    UInt_t  currentEvent;
    UInt_t  currentScalerEntry;

    Int_t   countReconstructed;

protected:
    TFile*          file_out;

    GTreeRawEvent*      rawEvent;
    GTreeTagger*        tagger;
    GTreeLinPol*        linpol;
    GTreeTrigger*       trigger;
    GTreeScaler*        scalers;
    GTreeDetectorHits*  detectorHits;
    GTreeParticle*      rootinos;
    GTreeParticle*      photons;
    GTreeParticle*      electrons;
    GTreeParticle*      chargedPi;
    GTreeParticle*      protons;
    GTreeParticle*      neutrons;
    GTreeMeson*         pi0;
    GTreeMeson*         eta;
    GTreeMeson*         etap;

    TDatabasePDG *pdgDB;

            void    FillReadList()      {for(int l=0; l<readList.GetEntriesFast(); l++) ((GTree*)readList[l])->Fill();}
    const   TObjArray&  GetTreeList()    const   {return treeList;}
    virtual void    ProcessEvent() = 0;
    virtual void    ProcessScalerRead() {}
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
            UInt_t  GetNReconstructed() const   {return countReconstructed;}
            UInt_t  GetNScalerEntries() const;
    virtual Bool_t  Init() {}
            Bool_t  StartFile(const char* input_filename, const char* output_filename);

    friend  class GTree;
    friend  class GTreeParticle;
    friend  class GTreeMeson;
};

#endif

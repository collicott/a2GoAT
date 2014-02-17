#ifndef __GTree_h__
#define __GTree_h__


#include <iostream>


#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>



class  GTree
{
private:
    TFile*  file_in;
    TFile*  file_out;

    UInt_t   actualEntry;

protected:
    TTree*  tree_in;
    TTree*  tree_out;

    virtual void    SetBranchAdresses() = 0;

public:
    GTree();
    ~GTree();

            void    Reset();
    virtual void    Clear() = 0;
            void    Fill();

    virtual Bool_t  Init(const char* filename_input, const char* filename_output, const Bool_t override = kFALSE) = 0;

            Bool_t  GetEntry(const UInt_t index);
            Bool_t  GetEntry();

            UInt_t  GetActualEntry()                            {return actualEntry;}
            void    SetActualEntry(const UInt_t ActualEntry)    {actualEntry = ActualEntry;}

            Bool_t	Write();

};


#endif

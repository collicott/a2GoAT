#ifndef __GTree_h__
#define __GTree_h__


#include <iostream>


#include <TFile.h>
#include <TTree.h>



class   GTreeManager;

class  GTree
{
public:
    enum
    {
        FLAG_CLOSED           = 0,
        FLAG_OPENFORINPUT     = 1,
        FLAG_OPENFOROUTPUT    = 2
    };

    friend  class   GTreeManager;

private:
    TString name;
    Int_t   status;
    TFile*  file_in;
    TFile*  file_out;

    void    GetEntryFast(const UInt_t index)    {tree_in->GetEntry(index);}

protected:
    TTree*  tree_in;
    TTree*  tree_out;

    virtual void    SetBranchAdresses() = 0;
    virtual void    SetBranches() = 0;

public:
    GTree(const TString& _Name);
    virtual ~GTree();

    virtual void        Clear() = 0;
            void        Clone(TFile& outputFile);
            void        Fill()      {tree_out->Fill();}
    inline  Bool_t      GetEntry(const UInt_t index);
    const   TString&    GetName() const {return name;}
            UInt_t      GetNEntries()   const {return tree_in->GetEntries();}
            Bool_t      IsClosed()          {return !status;}
            Bool_t      IsOpenForInput()    {return status & FLAG_OPENFORINPUT;}
            Bool_t      IsOpenForOutput()   {return status & FLAG_OPENFOROUTPUT;}
            Bool_t      OpenForInput(TFile& inputFile);
            Bool_t      OpenForOutput(TFile& outputFile);
    virtual void        Print(const Bool_t All = kFALSE) const;
            Bool_t      Write();

};

Bool_t  GTree::GetEntry(const UInt_t index)
{
    if(index > tree_in->GetEntries())
        return kFALSE;
    tree_in->GetEntry(index);
}


#endif

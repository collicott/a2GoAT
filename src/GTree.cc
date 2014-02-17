#include "GTree.h"


using namespace std;


GTree::GTree()    :
    file_in(0),
    file_out(0),
    tree_in(0),
    tree_out(0),
    actualEntry(0)
{

}

GTree::~GTree()
{
    Reset();
}

void    GTree::Reset()
{
    if(tree_in)    delete tree_in;
    if(tree_out)   delete tree_out;
    if(file_in)    delete file_in;
    if(file_out)   delete file_out;
}

void    GTree::Clear()
{

}

void    GTree::Fill()
{
    tree_out->Fill();
}

Bool_t  GTree::Init(const char* filename_input, const char* filename_output, const Bool_t override)
{
    Reset();

    file_in    = TFile::Open(filename_input);
    if(!file_in)
    {
        cout << "#ERROR# GTree::Init(const char* filename_input, const char* filename_output): input file " << filename_input << " is not existing!" << endl;
        return kFALSE;
    }
    file_in->GetObject("GoAT", tree_in);
    if(!tree_in)
    {
        cout << "#ERROR# GTree::Init(const char* filename_input, const char* filename_output): could not find a tree called GoAT in input file " << filename_input << "!" << endl;
        return kFALSE;
    }
    cout << "opened input tree in file " << filename_input << "." << endl;

    SetBranchAdresses();

    if(override)
    {
        file_out    = TFile::Open(filename_output, "RECREATE");
        if(!file_out)
        {
            cout << "#ERROR# GTree::Init(const char* filename_input, const char* filename_output): can not create output file " << filename_output << "!" << endl;
            return kFALSE;
        }
    }
    else
    {
        file_out    = TFile::Open(filename_output, "NEW");
        if(!file_out)
        {
            cout << "#ERROR# GTree::Init(const char* filename_input, const char* filename_output): output file " << filename_output << " already exist! Use override Flag" << endl;
            return kFALSE;
        }
    }
    tree_out    = tree_in->CloneTree(0);
    if(!tree_out)
    {
        cout << "#ERROR# GTree::OpenNewTree(const char* filename): can not create output tree!" << endl;
        return kFALSE;
    }
    cout << "created new output tree in file " << filename_output << "." << endl;

    return kTRUE;
}

Bool_t  GTree::GetEntry(const UInt_t index)
{
    if(index > tree_in->GetEntries())
        return kFALSE;
    tree_in->GetEntry(index);
}

Bool_t  GTree::GetEntry()
{
    if(actualEntry > tree_in->GetEntries())
        return kFALSE;
    tree_in->GetEntry(actualEntry);
    actualEntry++;
}

Bool_t	GTree::Write()
{
    if(!file_out)   return kFALSE;
    if(!tree_out)   return kFALSE;
    file_out->cd();
    tree_out->Write();
    return kTRUE;
}


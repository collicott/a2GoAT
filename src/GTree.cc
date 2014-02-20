#include "GTree.h"


using namespace std;


GTree::GTree(const TString& _Name)    :
    name(_Name),
    status(FLAG_CLOSED),
    file_in(0),
    file_out(0),
    tree_in(0),
    tree_out(0)
{
}

GTree::~GTree()
{

}

void    GTree::Clone(TFile& outputFile)
{
    file_out = &outputFile;
    outputFile.cd();
    tree_out = tree_in->CloneTree();
}

Bool_t  GTree::OpenForInput(TFile& inputFile)
{
    file_in = &inputFile;

    inputFile.GetObject(name.Data(),tree_in);
    if(tree_in)
    {
        SetBranchAdresses();
        status  = status | FLAG_OPENFORINPUT;
        GetEntry(0);
        return kTRUE;
    }

    cout << "#ERROR# GTree::OpenForInput(TFile& inputFile): could not find a tree called " << name.Data() << " in input file " << inputFile.GetName() << "!" << endl;
    status = status & (~FLAG_OPENFORINPUT);
    return kFALSE;
}

Bool_t  GTree::OpenForOutput(TFile& outputFile)
{
    file_out = &outputFile;

    outputFile.cd();
    tree_out    = new TTree(name.Data(), name.Data());
    if(tree_out)
    {
        SetBranches();
        status  = status | FLAG_OPENFOROUTPUT;
        return kTRUE;
    }

    cout << "#ERROR# GTree::OpenForInput(TFile& inputFile): can not create output tree " << name.Data() << " in output file " << outputFile.GetName() << "!" << endl;
    status = status & (~FLAG_OPENFOROUTPUT);
    return kFALSE;

    /*
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
*/
    return kTRUE;
}

void    GTree::Print(const Bool_t All) const
{
    std::cout << "GTree: Name->" << name.Data() << " Status->";
    if(!status)
        std::cout << "Closed";
    if(status & FLAG_OPENFORINPUT)
        std::cout << "Input ";
    if(status & FLAG_OPENFOROUTPUT)
        std::cout << "Output";
    std::cout << std::endl;
}

Bool_t	GTree::Write()
{
    if(!file_out)   return kFALSE;
    if(!tree_out)   return kFALSE;
    file_out->cd();
    tree_out->Write();
    return kTRUE;
}


#include "GTree.h"
#include "GTreeManager.h"


using namespace std;


GTree::GTree(GTreeManager *Manager, const TString& _Name)    :
    name(_Name),
    status(FLAG_CLOSED),
    tree_in(0),
    tree_out(0),
    manager(Manager)
{
}

GTree::~GTree()
{
    if(tree_in) delete tree_in;
    if(tree_out) delete tree_out;
}

void    GTree::Clone()
{
    if(!IsOpenForInput())
    {
        if(!OpenForInput())
        {
            std::cout << "Can not open " << name << " in input file." << endl;
            return;
        }
    }
    if(!IsOpenForOutput())
    {
        if(!OpenForOutput())
        {
            std::cout << "Can not create " << name << " in output file." << endl;
            return;
        }
    }
    manager->file_out->cd();
    tree_out = tree_in->CloneTree();
}


void    GTree::Fill()
{
    if(!IsOpenForOutput())
    {
        if(!OpenForOutput())
        {
            std::cout << "Can not create " << name << " in output file." << endl;
            return;
        }
    }
    tree_out->Fill();
}

Bool_t  GTree::OpenForInput()
{
    manager->file_in->GetObject(name.Data(),tree_in);
    if(tree_in)
    {
        SetBranchAdresses();
        status  = status | FLAG_OPENFORINPUT;
        GetEntry(0);
        return kTRUE;
    }

    cout << "#ERROR# GTree::OpenForInput(TFile& inputFile): could not find a tree called " << name.Data() << " in input file " << manager->file_in->GetName() << "!" << endl;
    status = status & (~FLAG_OPENFORINPUT);
    return kFALSE;
}

Bool_t  GTree::OpenForOutput()
{
    manager->file_out->cd();
    tree_out    = new TTree(name.Data(), name.Data());
    if(tree_out)
    {
        SetBranches();
        status  = status | FLAG_OPENFOROUTPUT;
        return kTRUE;
    }

    cout << "#ERROR# GTree::OpenForInput(TFile& inputFile): can not create output tree " << name.Data() << " in output file " << manager->file_in->GetName() << "!" << endl;
    status = status & (~FLAG_OPENFOROUTPUT);
    return kFALSE;
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
    if(!manager->file_out)          return kFALSE;
    if(!tree_out)                   return kFALSE;
    if(!IsOpenForOutput())          return kFALSE;

    manager->file_out->cd();
    tree_out->Write();
    std::cout << "tree" << name << " has been written to disk." << std::endl;
    return kTRUE;
}


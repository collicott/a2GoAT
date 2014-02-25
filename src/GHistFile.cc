#include "GHistFile.h"


using namespace std;


GHistFile::GHistFile(const TString& _Name)    :
    file(TFile::Open(_Name.Data(), "UPDATE"))
{

}

GHistFile::~GHistFile()
{

}

Bool_t	GHistFile::Write(const TNamed* object)
{
    if(!file)   return kFALSE;
    file->cd();
    //TNamed*  test   = file->Get(object->GetName());
    //if(!test)
        object->Write();
    return kTRUE;
}


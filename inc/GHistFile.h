#ifndef __GHistFile_h__
#define __GHistFile_h__


#include <iostream>


#include <TFile.h>




class  GHistFile
{
private:
    TFile*  file;

protected:

public:
    GHistFile(const TString& _Name);
    virtual ~GHistFile();

    Bool_t      Write(const TNamed* object);
};



#endif

#ifndef __GTree_h__
#define __GTree_h__


#include "GAcquTreeManager.h"





class GTree    : GAcquTreeManager
{
private:
    TFile*      file;
    TTree*      tree;

public:
    GTree();
    ~GTree();
};



#endif

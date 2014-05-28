#ifndef __GMyGoAT_h__
#define __GMyGoAT_h__


#include <time.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include <TROOT.h>
#include <TSystem.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

using namespace std;



enum    FlagCuts
{
    FLAG_Cut_2g,
    FLAG_Cut_6g,
    FLAG_Cut_Pi0,
    FLAG_Cut_Eta,
    FLAG_Cut_Etap
};


struct  Arguments
{
    char        type[32];
    char        fileName_in[1024];
    char        fileName_out[1024];
    FlagCuts    cut;
    int         nValues;
    union
    {
        Double_t        value[32];
        struct
        {
            Double_t    CBTimeCut[2];
            Double_t    TAPSTimeCut[2];
        } time;
    };
};

#endif

#ifndef __CINT__


#include <time.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include <TROOT.h>
#include <TSystem.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

#include "GParticleReconstruction.h"
#include "GMesonReconstruction.h"

using namespace std;




struct  Arguments
{
    char        type[32];
    char        fileName_in[1024];
    char        fileName_out[1024];
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




void    PrintHelp()
{
    cout << "particle:  particle reconstruction" << endl;

    cout << endl;
    cout << "example:" << endl;
    cout << "MyGoAT particle <inputFile> <outputFile>" << endl;
}




void* start(void* arguments)
{	
    Arguments*   arg    = 0;
    arg = (Arguments*) arguments;

	clock_t start, end;
	start = clock();

    GTreeManager* tree;

    if(strcmp(arg->type, "particle") == 0 || strcmp(arg->type, "Particle") == 0 || strcmp(arg->type, "PARTICLE") == 0)
    {

        GParticleReconstruction*   help    = new GParticleReconstruction();

        if(arg->nValues>2)
        {
            cout << "Set CBTimeWindow from " << arg->time.CBTimeCut[0] << " to " << arg->time.CBTimeCut[1] << "." << endl;
            help->SetCBTimeCut(arg->time.CBTimeCut[0], arg->time.CBTimeCut[1]);
        }
        else if(arg->nValues>4)
        {
            cout << "Set CBTimeWindow from " << arg->time.CBTimeCut[0] << " to " << arg->time.CBTimeCut[1] << "." << endl;
            help->SetCBTimeCut(arg->time.CBTimeCut[0], arg->time.CBTimeCut[1]);
            cout << "Set TAPSTimeWindow from " << arg->time.TAPSTimeCut[0] << " to " << arg->time.TAPSTimeCut[1] << "." << endl;
            help->SetTAPSTimeCut(arg->time.TAPSTimeCut[0], arg->time.TAPSTimeCut[1]);
        }

        tree    = help;
    }
    else if(strcmp(arg->type, "meson") == 0 || strcmp(arg->type, "Meson") == 0 || strcmp(arg->type, "MESON") == 0)
    {
        cout << "Meson reconstruction started." << endl;
        tree    = new GMesonReconstruction();

    }
    else
    {
        cout << "Reconstruction type " << arg->type <<" is unknown." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }


    tree->Process(arg->fileName_in, arg->fileName_out);

    delete  tree;

	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    gSystem->Load("libPhysics.so");
    gSystem->Load("libHist.so");

    // Associate 1nd terminal input with the input file ----------------
    if(argc < 2)
    {
        cout << "No reconstruction type given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }
    Char_t* type;
    if(argv[1]) type = argv[1];
    else
    {
        cout << "No reconstruction type given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }

    // Associate 2nd terminal input with the input file ----------------
    if(argc < 3)
    {
        cout << "No input file given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }
    Char_t* fileName_in;
    if(argv[2]) fileName_in = argv[2];
    else
    {
        cout << "No input file given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }

    // Associate 3nd terminal input with the output file ----------------
        if(argc < 4)
        {
            cout << "No output file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        Char_t* fileName_out;
        if(argv[3]) fileName_out = argv[3];
        else
        {
            cout << "No output file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }

    TSystemFile* file_in   = new TSystemFile(fileName_in,".");
    TSystemFile* file_out  = new TSystemFile(fileName_out,".");
    if(file_in->IsZombie())
    {
        cout << "file or directory " << fileName_in << " is not existing." << endl;
        return 0;
    }
    if(file_in->IsDirectory())
    {
        if(!file_out->IsDirectory())
        {
            cout << "Output directory " << fileName_out << " is not existing." << endl;
            return 0;
        }
        delete file_in;
        delete file_out;

        if(argc < 7)
        {
            cout << "No prefix/suffix for file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        TString prefix_in;
        TString suffix;
        TString prefix_out;
        if(argv[4]) prefix_in = argv[4];
        else
        {
            cout << "No prefix for input file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        if(argv[5]) suffix = argv[5];
        else
        {
            cout << "No suffix for files given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        if(!suffix.EndsWith(".root"))
            suffix.Append(".root");
        if(argv[6]) prefix_out = argv[6];
        else
        {
            cout << "No prefix for output file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }

        TSystemDirectory    dir_in(fileName_in, ".");
        TSystemDirectory    dir_out(fileName_out, ".");

        TString currentInput;
        TString currentOutput;

        //TList*   files  = dir_in.GetListOfFiles();
        TIter   next(dir_in.GetListOfFiles());
        int     counter = 0;
        while(file_in = (TSystemFile*)next())
        {
            currentInput = file_in->GetName();
            if(!currentInput.BeginsWith(prefix_in))
                continue;
            if(!currentInput.EndsWith(suffix))
                continue;
            currentOutput   = currentInput(prefix_in.Length(), currentInput.Length() - prefix_in.Length() - suffix.Length());
            currentOutput.Prepend(prefix_out);
            currentOutput.Append(suffix);

            printf("process file %d\n", counter);
            counter++;

            pthread_t thread;
            Arguments   arguments;
            strcpy(arguments.type, type);
            strcpy(arguments.fileName_in, currentInput.Data());
            strcpy(arguments.fileName_out, currentOutput.Data());
            arguments.nValues   = 0;
            for(int i=7; i<argc; i++)
            {
                if(argv[i])
                {
                    sscanf(argv[i],"%lf", &arguments.value[i-7]);
                    arguments.nValues++;
                }
            }
            pthread_create( &thread, NULL, start, (void*)&arguments);
            pthread_join(thread,0);
        }
    }
    else
    {
        Arguments   arguments;
        strcpy(arguments.type, type);
        strcpy(arguments.fileName_in, fileName_in);
        strcpy(arguments.fileName_out, fileName_out);
        arguments.nValues   = 0;
        for(int i=4; i<argc; i++)
        {
            if(argv[i])
            {
                sscanf(argv[i],"%lf", &arguments.value[i-4]);
                arguments.nValues++;
            }
        }
        start((void*)&arguments);
    }

    return 0;
}

#endif

#ifndef __CINT__

#include <time.h>
#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TSystem.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

#include "GParticleReconstruction.h"
#include "GMesonReconstruction.h"

using namespace std;




/**
 * @brief the main routine
 * @param argc number of parameters
 * @param argv the parameters as strings
 * @return exit code
 */



void    PrintHelp()
{
    cout << "particle:  ParticleReconstruction" << endl;

    cout << endl;
    cout << "example:" << endl;
    cout << "MyGoat particle <inputFile> <outputFile>" << endl;
}




int main(int argc, char *argv[])
{	
	clock_t start, end;
	start = clock();

    gSystem->Load("libPhysics.so");
    gSystem->Load("libHist.so");


    GTreeManager* tree;

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




    if(strcmp(type, "particle") == 0 || strcmp(type, "Particle") == 0 || strcmp(type, "PARTICLE") == 0)
    {
        cout << "Particle reconstruction started." << endl;
        if(argc !=4 && argc !=6 && argc !=8)
        {
            cout << "No files given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        GParticleReconstruction*   help    = new GParticleReconstruction();

        Double_t    parameter[2];
        if(argc==6)
        {
            sscanf(argv[4], "%lf", &parameter[0]);
            sscanf(argv[5], "%lf", &parameter[1]);
            cout << "Set CBTimeWindow from " << parameter[0] << " to " << parameter[1] << "." << endl;
            help->SetCBTimeCut(parameter[0], parameter[1]);
        }
        else if(argc==8)
        {
            sscanf(argv[4], "%lf", &parameter[0]);
            sscanf(argv[5], "%lf", &parameter[1]);
            cout << "Set CBTimeWindow from " << parameter[0] << " to " << parameter[1] << "." << endl;
            help->SetCBTimeCut(parameter[0], parameter[1]);
            sscanf(argv[6], "%lf", &parameter[0]);
            sscanf(argv[7], "%lf", &parameter[1]);
            cout << "Set TAPSTimeWindow from " << parameter[0] << " to " << parameter[1] << "." << endl;
            help->SetTAPSTimeCut(parameter[0], parameter[1]);
        }

        tree    = help;
    }
    else if(strcmp(type, "meson") == 0 || strcmp(type, "Meson") == 0 || strcmp(type, "MESON") == 0)
    {
        cout << "Meson reconstruction started." << endl;
        if(argc !=4)
        {
            cout << "No files given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        tree    = new GMesonReconstruction();

    }
    else
    {
        cout << "Reconstruction type " << type <<" is unknown." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }


    // Associate 2nd terminal input with the input file ----------------
    Char_t* file_in;
    if(argv[2]) file_in = argv[2];
    else
    {
        cout << "Please provide an input file" << endl;
        return 0;
    }
        // Check that input file exists:
    ifstream ifile(file_in);
    if(!ifile)
    {
        cout << "Input file " << file_in << " could not be found." << endl;
        return 0;
    }

    // Associate 3rd terminal input with the output file ---------------
    Char_t* file_out;
    if(argv[3]) file_out = argv[3];
    else
    {
        cout << "Please provide an output file" << endl;
        return 0;
    }

    tree->Process(file_in, file_out);

	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

	return 0;
}

#endif

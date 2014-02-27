#ifndef __CINT__

#include <time.h>
#include <iostream>
#include <fstream>
#include <TSystem.h>

#include "GTaggerReconstruction.h"

using namespace std;

/**
 * @brief the main routine
 * @param argc number of parameters
 * @param argv the parameters as strings
 * @return exit code
 */
int main(int argc, char *argv[])
{
    clock_t start, end;
    start = clock();

    gSystem->Load("libPhysics.so");
    gSystem->Load("libHist.so");
    GTaggerReconstruction tree;

    if(argc == 3)
    {
        // Associate 1nd terminal input with the input file ----------------
        Char_t* file_in;
        if(argv[1]) file_in = argv[1];
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

        // Associate 2rd terminal input with the output file ---------------
        Char_t* file_out;
        if(argv[2]) file_out = argv[2];
        else
        {
            cout << "Please provide an output file" << endl;
            return 0;
        }

        tree.Process(file_in, file_out);
    }
    else
    {
        cout << "Please provide correct number of arguments!" << endl;
        cout << "tagger   <input filename> <output filename>" << endl;
    }



    end = clock();
    cout << "Time required for execution: "
    << (double)(end-start)/CLOCKS_PER_SEC
    << " seconds." << "\n\n";

    return 0;
}

#endif

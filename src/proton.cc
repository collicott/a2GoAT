#ifndef __CINT__

#include <time.h>
#include <iostream>
#include <fstream>
#include <TSystem.h>

#include "GProtonReconstruction.h"

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
    GProtonReconstruction tree;

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
    else if(argc == 6)
    {
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

        Char_t* prefix;
        if(argv[1]) prefix = argv[3];
        else
        {
            cout << "Please provide an input prefix" << endl;
            return 0;
        }

        Char_t* suffix;
        if(argv[1]) suffix = argv[4];
        else
        {
            cout << "Please provide an input suffix" << endl;
            return 0;
        }

        Char_t* prefix_out;
        if(argv[1]) prefix_out = argv[5];
        else
        {
            cout << "Please provide an output prefix" << endl;
            return 0;
        }

        TString in(file_in);
        if(in.BeginsWith("~"))
        {
            in = in(1,in.Length()-1);
            in.Prepend("$HOME");
        }
        else if(!in.BeginsWith("/"))
        {
            in = TString(gSystem->WorkingDirectory()).Append("/").Append(in).Data();
        }

        TString out(file_out);
        if(out.BeginsWith("~"))
        {
            out = out(1,out.Length()-1);
            out.Prepend("$HOME");
        }
        else if(!out.BeginsWith("/"))
        {
            out = TString(gSystem->WorkingDirectory()).Append("/").Append(out).Data();
        }

        tree.ProcessFolder(in, out, prefix, suffix, prefix_out);
    }
    else
    {
        cout << "Please provide correct number of arguments!" << endl;
        cout << "There are two possibilities." << endl;
        cout << "1:   <input filename> <output filename>" << endl;
        cout << "           To run one file." << endl;
        cout << "2:   <input folder>   <output folder>  <prefix input file><suffix file><prefix output file>" << endl;
        cout << "           To run a complete folder." << endl;
        cout << "           Every file with pattern <prefix input file><RunNumber><suffix file> is processed." << endl;
        cout << "           to output file with pattern <prefix output file><RunNumber><suffix file>." << endl;
    }

    end = clock();
    cout << "Time required for execution: "
    << (double)(end-start)/CLOCKS_PER_SEC
    << " seconds." << "\n\n";

    return 0;
}

#endif

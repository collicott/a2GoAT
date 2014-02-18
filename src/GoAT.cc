#ifndef __CINT__

#include <time.h>
#include <iostream>
#include <fstream>

#include "GSort.h"

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

	
	// Associate 2nd terminal input with the input file ----------------
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
	
	// Associate 3rd terminal input with the output file ---------------
	Char_t* file_out;
    if(argv[2]) file_out = argv[2];
	else 
	{
		cout << "Please provide an output file" << endl;
		return 0;
	}
	
    //gInterpreter->GenerateDictionary("GParticle","inc/GParticle.h");
	// Create instance of GoAT class
    TFile*  f = TFile::Open(file_out, "RECREATE");
    GSort   test(*f);

    test.MultiplicityList.push_back(2);
    test.MultiplicityList.push_back(3);
    test.MultiplicityList.push_back(6);
    test.MultiplicityList.push_back(7);
    test.MultiplicityList.push_back(10);
    test.MultiplicityList.push_back(11);
    test.OpenAcquFile(file_in);
    test.Analyse();

    test.Write(*f);
    delete f;

	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

	return 0;
}

#endif

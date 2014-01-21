#ifndef __CINT__

#include "GoAT.h"
#include <time.h>

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

	// Associate 1st terminal input with config file -------------------
	Char_t* configfile;
	if(argv[1]) configfile = argv[1];
	else 
	{
		cout << "Please provide a config file" << endl;
		return 0;
	}
	
	// Check that file exists:
	ifstream cfile(configfile);
	if(!cfile)
	{
		cout << "Config file " << configfile << " could not be found." << endl;
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
		cout << "Input file " << configfile << " could not be found." << endl;
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
	
	// Create instance of GoAT class
	GoAT* goat = new GoAT;

	// Perform full initialisation 
	if(!goat->Init(configfile, file_in, file_out)){
		cout << "ERROR: GoAT Init failed!" << endl;
		return 0;
	}
	
	goat->Analyse();

	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

	

	return 0;
}


GoAT::GoAT() :
				UseParticleReconstruction(0)
{ 
}

GoAT::~GoAT()
{
}

Bool_t	GoAT::Init(Char_t* configfile, Char_t* file_in, Char_t* file_out)
{
	cout << endl << "Initialising GoAT analysis:" << endl;
	cout << "==========================================================" << endl;	
	SetConfigFile(configfile);

	cout << "Opening files: " << endl;
	if(!OpenAcquFile(file_in))	return kFALSE;	
	if(!OpenGoATFile(file_out))	return kFALSE;	
	
	cout << endl;
	
	cout << "Setting up tree files:" << endl;
	if(!OpenTreeRawEvent())			return kFALSE;
	if(!OpenTreeTagger())			return kFALSE;
	if(!OpenTreeTrigger())			return kFALSE;
	cout << endl;
	
	cout << "Checking scaler reads for valid events:" << endl;	
	if(!FindValidAcquEvents())		return kFALSE;
	cout << endl;
		
	config = ReadConfig("Period-Macro");
	if( sscanf(config.c_str(),"%d\n", &period) == 1 ) UsePeriodMacro = 1;
		
	cout << "Setting up sorting criteria:" << endl;	
	cout << "==========================================================" << endl;	
	if(!GSort::PostInit()) 
	{
		cout << "GSort Init failed!" << endl; 
		return kFALSE;
	}
	
	cout << "Setting up analysis classes:" << endl;	
	cout << "==========================================================" << endl;	
    config = ReadConfig("DO-PARTICLE-RECONSTRUCTION");

    {
        int buffer=0;
        sscanf( config.c_str(), "%d\n", &buffer);
        UseParticleReconstruction = (buffer==1);
    }

	if(UseParticleReconstruction) 
	{
		if(!GParticleReconstruction::PostInit())
		{
			cout << "GParticleReconstruction Init failed!" << endl; 
			return kFALSE;
		}
	}			
	cout << endl;	

	cout << "Initialisation complete." << endl;
	cout << "==========================================================" << endl << endl;

  
	return kTRUE;
}

void	GoAT::Analyse()
{
	cout << "Analysing ..." << endl;
	TraverseAcquEntries();			
	CloseOutputFile();
//	OutputStatistics();
}

void	GoAT::Reconstruct()
{
	if(UsePeriodMacro == 1)
	{
		if(GetActualEvent() % period == 0) 
						printf("Event: %d\n",GetActualEvent());
	}

	if(SortAnalyseEvent())
	{
		if(UseParticleReconstruction) GParticleReconstruction::Reconstruct();
		
		if(SortFillEvent()) FillEvent();
	}
}

Bool_t 	GoAT::Write()
{
	return kTRUE;
}

#endif

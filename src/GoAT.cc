#ifndef __CINT__

#include "GoAT.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
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

	Char_t* configfile;
	char serverfile[256] = "";

	char dir_in[256] = "";
	char dir_out[256] = "";
	char file_in[256] = "";
	char file_out[256] = "";
	char pre_in[256] = "Acqu";
	char pre_out[256] = "GoAT";

	std::string str;
	std::string flag;
	std::string value;

	if(argc == 1)
	{
		cout << "Please provide a config file" << endl;
		return 0;
	}
	else if(argc == 2)
	{
		configfile = argv[1];
		cout << "Searching config file " << configfile << " for input and output root file names" << endl << "None found" << endl;
	}
	else
	{
		for(int i=1; i<argc; i++)
		{
			str = argv[i];
			if(str.find_first_of("-") == 0)
			{
				flag = str.substr(1,str.length()-1);
				i++;
				str = argv[i];
				value = str;
				if(strcmp(flag.c_str(), "s") == 0)
				{
					cout << "Server file '" << value << "' chosen" << endl;
					sprintf(serverfile, "%s", value.c_str());
				}
				else if(strcmp(flag.c_str(), "d") == 0)
				{
					cout << "Input directory '" << value << "' chosen" << endl;
					if(value.find_last_of("/") == (value.length()-1)) sprintf(dir_in,"%s",value.c_str());
					else sprintf(dir_in,"%s/",value.c_str());
				}
				else if(strcmp(flag.c_str(), "D") == 0)
				{
					cout << "Output directory '" << value << "' chosen" << endl;
					if(value.find_last_of("/") == (value.length()-1)) sprintf(dir_out,"%s",value.c_str());
					else sprintf(dir_out,"%s/",value.c_str());
				}
				else if(strcmp(flag.c_str(), "f") == 0)
				{
					cout << "Input file '" << value << "' chosen" << endl;
					sprintf(file_in, "%s", value.c_str());
				}
				else if(strcmp(flag.c_str(), "F") == 0)
				{
					cout << "Output file '" << value << "' chosen" << endl;
					sprintf(file_out, "%s", value.c_str());
				}
				else if(strcmp(flag.c_str(), "p") == 0)
				{
					cout << "Input prefix '" << value << "' chosen" << endl;
					sprintf(pre_in, "%s", value.c_str());
				}
				else if(strcmp(flag.c_str(), "P") == 0)
				{
					cout << "Output prefix '" << value << "' chosen" << endl;
					sprintf(pre_out, "%s", value.c_str());
				}
				else
				{
					cout << "Unknown flag" << flag << endl;
					return 0;
				}
			}
			else configfile = argv[i];
		}
	}
	// Check that file exists:
	ifstream cfile(configfile);
	if(!cfile)
	{
		cout << "Config file '" << configfile << "' could not be found." << endl;
		return 0;
	}

	// Create instance of GoAT class
	GoAT* goat = new GoAT;

	// Perform full initialisation 
	if(!goat->Init(configfile))
	{
		cout << "ERROR: GoAT Init failed!" << endl;
		return 0;
	}

	Int_t length;
	std::string file;
	std::string prefix;
	std::string suffix;

	// If input file is specified, use it
	if(strcmp(file_in,"") != 0)
	{
		file = file_in;
		length = file.length();
		// File should at least have '.root' at the end
		if(length >= 5)
		{
			// Add input directory to it
			sprintf(file_in,"%s%s",dir_in,file_in);					
			// If output file is specified, use it
			if(strcmp(file_out,"") != 0)
			{
				sprintf(file_out,"%s%s",dir_out,file_out);					
				if(!goat->File(file_in, file_out)) cout << "ERROR: GoAT failed on file " << file_in << "!" << endl;
			}
			// If output file is not specified, build it
			else
			{
				// If output directory is not specified, build it
				if(strcmp(dir_out,"") == 0)
				{
					prefix = file.substr(0,file.find_last_of("/")+1);
					sprintf(dir_out,"%s%s",dir_in,prefix.c_str());					
				}
				// If input prefix doesn't match, simply prepend output prefix to the file name
				if(file.find(pre_in)>file.length()) suffix = ("_"+file.substr(file.find_last_of("/")+1,length-(file.find_last_of("/")+1)));
				// If input prefix does match, switch prefixes
				else suffix = file.substr(file.find_last_of("/")+1+strlen(pre_in),length-(file.find_last_of("/")+1+strlen(pre_in)));
				// Build output file name
				sprintf(file_out,"%s%s%s",dir_out,pre_out,suffix.c_str());					
				// Run GoAT
				if(!goat->File(file_in, file_out)) cout << "ERROR: GoAT failed on file " << file_in << "!" << endl;
			}
		}
	}
	// Otherwise if server file is specified, scan it
	else if(strcmp(serverfile,"") != 0)
	{
		// Check that file exists:
		ifstream sfile(serverfile);
		if(!serverfile)
		{
			cout << "Server file '" << serverfile << "' could not be found" << endl;
			return 0;
		}
		else cout << "Using Server file '"<< serverfile << "' for all file settings" << endl; 
		value = goat->ReadConfig("Input-Directory",0,serverfile);	
		if(value.find_last_of("/") != (value.length()-1)) value += "/";
		if(strcmp(value.c_str(),"nokey") != 0) sscanf(value.c_str(), " %s\n", dir_in);
		value = goat->ReadConfig("Output-Directory",0,serverfile);	
		if(value.find_last_of("/") != (value.length()-1)) value += "/";
		if(strcmp(value.c_str(),"nokey") != 0) sscanf(value.c_str(), " %s\n", dir_out);
		value = goat->ReadConfig("Input-File",0,serverfile);	
		if(strcmp(value.c_str(),"nokey") != 0) sscanf(value.c_str(), " %s\n", file_in);
		value = goat->ReadConfig("Output-File",0,serverfile);	
		if(strcmp(value.c_str(),"nokey") != 0) sscanf(value.c_str(), " %s\n", file_out);
		value = goat->ReadConfig("Input-Prefix",0,serverfile);	
		if(strcmp(value.c_str(),"nokey") != 0) sscanf(value.c_str(), " %s\n", pre_in);
		value = goat->ReadConfig("Output-Prefix",0,serverfile);	
		if(strcmp(value.c_str(),"nokey") != 0) sscanf(value.c_str(), " %s\n", pre_out);

		cout << dir_in << endl;
		cout << dir_out << endl;
		cout << file_in << endl;
		cout << file_out << endl;
		cout << pre_in << endl;
		cout << pre_out << endl;

	}
	// Otherwise if input directory is specified, scan it
	else if(strcmp(dir_in,"") != 0)
	{
		// If output directory is not specified, use the input directory
		if(strcmp(dir_out,"") == 0) sprintf(dir_out,"%s",dir_in);

		TSystemFile *sys_file;
		
		TSystemDirectory *sys_dir = new TSystemDirectory("files",dir_in);
		TList *file_list = sys_dir->GetListOfFiles();
		file_list->Sort();
		TIter file_iter(file_list);
		
		while((sys_file=(TSystemFile*)file_iter()))
		{
			file = sys_file->GetName();
			length = file.length();
			if(length >= 5)
			{
				prefix = file.substr(0,strlen(pre_in));
				suffix = file.substr(length-5,5);
				if(((strcmp(prefix.c_str(),pre_in) == 0)) && (strcmp(suffix.c_str(),".root") == 0))
				{
					sprintf(file_in,"%s%s",dir_in,file.c_str());
					suffix = file.substr(strlen(pre_in),length-strlen(pre_in));
					sprintf(file_out,"%s%s%s",dir_out,pre_out,suffix.c_str());					
					if(!goat->File(file_in, file_out)) cout << "ERROR: GoAT failed on file " << file_in << "!" << endl;
				}
			}
		}
	}

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

Bool_t	GoAT::Init(Char_t* configfile)
{
	cout << endl << "Initialising GoAT analysis:" << endl;
	cout << "==========================================================" << endl;	
	SetConfigFile(configfile);
		
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

Bool_t	GoAT::File(Char_t* file_in, Char_t* file_out)
{
	cout << "Opening files: " << endl;
	if(!OpenAcquFile(file_in))	return kFALSE;	
	if(!OpenGoATFile(file_out))	return kFALSE;	
	
	cout << endl;

	cout << "Setting up tree files:" << endl;
	if(!OpenTreeRawEvent())			return kFALSE;
	if(!OpenTreeTagger())			return kFALSE;
	if(!OpenTreeTrigger())			return kFALSE;
	if(!OpenTreeScaler())			return kFALSE;
	cout << endl;
	
	cout << "Checking scaler reads for valid events:" << endl;	
	if(!FindValidAcquEvents())		return kFALSE;
	cout << endl;

	cout << "Opening particle reconstruction tree: ";	
	InitTreeParticles();
	cout << endl;
	
	Analyse();
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

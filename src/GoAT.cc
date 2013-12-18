#ifndef __CINT__

#include "GoAT.h"

int main(int argc, char *argv[])
{

	Char_t* configfile;
	if(argv[1]) configfile = argv[1];
	else 
	{
		cout << "Please provide an input file" << endl;
		return 0;
	}
	
	// Check that file exists:
	ifstream ifile(configfile);
	if(!ifile)
	{
		cout << "Input file " << configfile << " could not be found." << endl;
		return 0;
	}
	
	GoAT* goat = new GoAT;

	std::string config;	
	
	char in_filename[256]; char out_filename[256];
	
	sscanf( goat->ReadConfig("Input-File",configfile).c_str(), "%s\n", in_filename);
	sscanf( goat->ReadConfig("Output-File",configfile).c_str(), "%s\n", out_filename);

	goat->Init(in_filename,out_filename,configfile);
	goat->Analyse();

	return 0;
}


GoAT::GoAT() :
				file_in(0),
				file_out(0),
				UseParticleReconstruction(0),
				SortNumberParticles(0)
{ 
}

GoAT::~GoAT()
{
}

Bool_t	GoAT::Init(const char* file_in, const char* file_out, Char_t* configfile)
{
	cout << endl << "Initialising GoAT analysis:" << endl;
	cout << "==========================================================" << endl;	
	SetConfigFile(configfile);

	cout << "Opening files: " << endl;
	cout << "INPUT  ";  if(!OpenInputFile(file_in))		return kFALSE;	
	cout << "OUTPUT "; if(!OpenOutputFile(file_out))	return kFALSE;
	cout << endl;
	
	cout << "Setting up tree files:" << endl;
	if(!OpenTreeRawEvent())			return kFALSE;
	if(!OpenTreeTagger())			return kFALSE;
	if(!OpenTreeTrigger())			return kFALSE;
	cout << endl;
	
	cout << "Checking scaler reads for valid events:" << endl;	
	if(!FindValidEvents())			return kFALSE;
	cout << endl;
		
	cout << "Setting up sorting criteria:" << endl;	
	cout << "==========================================================" << endl;	
	std::string str;
	char str1[256], str2[256], str3[256];
	config = ReadConfig("Sort-Number-Particles",GetConfigFile());	
	if( sscanf( config.c_str(), "%d %s %d %s %d %s\n", 
		&Sort_nParticles_total, str1,
		&Sort_nParticles_CB, 	str2,
		&Sort_nParticles_TAPS, 	str3) == 6 )
	{		

		if(strcmp(str1,"+") == 0) 
		{
			str = " (or more)";
			Sort_nParticles_total_condition = 0;
		}
		else if (strcmp(str1,"-") == 0) 
		{
			str = " (or less)";
			Sort_nParticles_total_condition = 1;
		}		
		else if (strcmp(str1,"=") == 0) 
		{
			str = " (exactly)";
			Sort_nParticles_total_condition = 2;
		}			
		else 
		{
			cout << "Sort-Number-Particles cut set inproperly (turned off)" <<endl;
			// Add line to jump out of this condition
		}

		cout << "Sorting condition: Total # of Particles    " 
			 << Sort_nParticles_total << " "<< str << endl;
			 
		if(strcmp(str2,"+") == 0) 
		{
			str = " (or more)";
			Sort_nParticles_CB_condition = 0;
		}
		else if (strcmp(str2,"-") == 0) 
		{
			str = " (or less)";
			Sort_nParticles_CB_condition = 1;
		}		
		else if (strcmp(str2,"=") == 0) 
		{
			str = " (exactly)";
			Sort_nParticles_CB_condition = 2;
		}	
		else 
		{
			cout << "Sort-Number-Particles cut set inproperly (turned off)" <<endl;
			// Add line to jump out of this condition
		}

		cout << "Sorting condition: # of Particles in CB    " 
			 << Sort_nParticles_CB << " "<< str << endl;			 

		if(strcmp(str3,"+") == 0) 
		{
			str = " (or more)";
			Sort_nParticles_TAPS_condition = 0;
		}
		else if (strcmp(str3,"-") == 0) 
		{
			str = " (or less)";
			Sort_nParticles_TAPS_condition = 1;
		}		
		else if (strcmp(str3,"=") == 0) 
		{
			str = " (exactly)";
			Sort_nParticles_TAPS_condition = 2
			;
		}	
		else 
		{
			cout << "Sort-Number-Particles cut set inproperly (turned off)" <<endl;
			// Add line to jump out of this condition
		}

		cout << "Sorting condition: # of Particles in TAPS  " 
			 << Sort_nParticles_TAPS << " "<< str << endl;	
			 
		SortNumberParticles = 1;	
	}

	cout << endl;
	
	cout << "Setting up analysis classes:" << endl;	
	cout << "==========================================================" << endl;	
	config = ReadConfig("DO-PARTICLE-RECONSTRUCTION",GetConfigFile());	
	sscanf( config.c_str(), "%d\n", &UseParticleReconstruction);
	if(UseParticleReconstruction) GParticleReconstruction::PostInit();
	cout << endl;	

	cout << "Initialisation complete." << endl;
	cout << "==========================================================" << endl << endl;

  
	return kTRUE;
}

void	GoAT::Analyse()
{
	TraverseInputEntries();
	printf("nPi0 == %d  nEta == %d  nEtaP == %d  nProton == %d  nChPion == %d \n", 
			GetNPi0(),	GetNEta(),	GetNEtaP(),  GetNProton(),	GetNChPion());
			
	CloseOutputFile();
}

void	GoAT::Reconstruct()
{
	if(GetActualEvent() % 10000 == 0) printf("Event: %d\n",GetActualEvent());

	GParticleReconstruction::Reconstruct();
	
	if(Sort()) FillEvent();
}

Bool_t 	GoAT::Write()
{
	return kTRUE;
}

Bool_t GoAT::Sort()
{
	Int_t i;	

	// Check conditions
	if(SortNumberParticles == 1)
	{
			
		// Cut on Total number of particles
		i = Sort_nParticles_total_condition;

		if(i == 0) { if (GP_GetNParticles() < Sort_nParticles_total) {return kFALSE;}}
		else if(i == 1) {if (GP_GetNParticles() > Sort_nParticles_total) {return kFALSE;}}
		else if(i == 2) {if (GP_GetNParticles() != Sort_nParticles_total) {return kFALSE;	}}

/*		// Cut on number of particles in CB
		i = Sort_nParticles_CB_condition;

		if(i == 0) { if 	(GP_GetNParticles() < Sort_nParticles_CB) {return kFALSE;}}
		else if(i == 1) {if 	(GP_GetNParticles() > Sort_nParticles_CB){ return kFALSE;}}
		else if(i == 2) {if 	(GP_GetNParticles() != Sort_nParticles_CB){ return kFALSE;	}}

		// Cut on number of particles in TAPS
		i = Sort_nParticles_TAPS_condition;	

		if(i == 0) {if (GP_GetNParticles() < Sort_nParticles_TAPS) { return kFALSE;}}
		else if(i == 1){ if (GP_GetNParticles() > Sort_nParticles_TAPS) {return kFALSE;}}
		else if(i == 2) {if (GP_GetNParticles() != Sort_nParticles_TAPS) {return kFALSE;	}} */
	}
	return kTRUE;

}

#endif

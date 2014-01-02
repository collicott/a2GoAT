
#include "GSort.h"


GSort::GSort()
{

}

GSort::~GSort()
{
}

Bool_t	GSort::PostInit()
{

	std::string strA, strB, strC;
	char str1[256], str2[256], str3[256];
	config = ReadConfig("Sort-Raw-Number-Particles",GetConfigFile());
	if (strcmp(config.c_str(), "nokey") == 0) SortRawNumberParticles = 0;
	else if( sscanf( config.c_str(), "%d %s %d %s %d %s\n", 
		&Sort_raw_nParticles_total, str1,
		&Sort_raw_nParticles_CB,   	str2,
        &Sort_raw_nParticles_TAPS,  str3) == 6 )
	{		
		SortRawNumberParticles = 1;	

		// Total Number of particle tracks
		if(strcmp(str1,"+") == 0) 
		{
			strA = " (or more)";
			Sort_raw_nParticles_total_condition = 0;
		}
		else if (strcmp(str1,"-") == 0) 
		{
			strA = " (or less)";
			Sort_raw_nParticles_total_condition = 1;
		}		
		else if (strcmp(str1,"=") == 0) 
		{
			strA = " (exactly)";
			Sort_raw_nParticles_total_condition = 2;
		}			
		else 
		{
			cout << "Error: Sort-Raw-Number-Particles cut set improperly (turned off)" <<endl;
			SortRawNumberParticles = 0;	
		}
			 
		// Number of particle tracks in CB
		if(strcmp(str2,"+") == 0) 
		{
			strB = " (or more)";
			Sort_raw_nParticles_CB_condition = 0;
		}
		else if (strcmp(str2,"-") == 0) 
		{
			strB = " (or less)";
			Sort_raw_nParticles_CB_condition = 1;
		}		
		else if (strcmp(str2,"=") == 0) 
		{
			strB = " (exactly)";
			Sort_raw_nParticles_CB_condition = 2;
		}			
		else 
		{
			cout << "Error: Sort-Raw-Number-Particles cut set improperly (turned off)" <<endl;
			SortRawNumberParticles = 0;	
		}

		// Number of particle tracks in TAPS
		if(strcmp(str3,"+") == 0) 
		{
			strC = " (or more)";
			Sort_raw_nParticles_TAPS_condition = 0;
		}
		else if (strcmp(str3,"-") == 0) 
		{
			strC = " (or less)";
			Sort_raw_nParticles_TAPS_condition = 1;
		}		
		else if (strcmp(str3,"=") == 0) 
		{
			strC = " (exactly)";
			Sort_raw_nParticles_TAPS_condition = 2;
		}			
		else 
		{
			cout << "Error: Sort-Raw-Number-Particles cut set improperly (turned off)" <<endl;
			SortRawNumberParticles = 0;	
		}

		if(SortRawNumberParticles == 1)
		{
			cout << "Sort: Total # of Particles before reconstruction    " 
				 << Sort_raw_nParticles_total << " "<< strA << endl;
			cout << "Sort: # of Particles before reconstruction in CB    " 
				 << Sort_raw_nParticles_CB << " "<< strB << endl;
			cout << "Sort: # of Particles before reconstruction in TAPS  " 
				 << Sort_raw_nParticles_TAPS << " "<< strC << endl;
		 }
	}
	else {
		SortRawNumberParticles = 0;
	}
	
	config = ReadConfig("Sort-Proton",GetConfigFile());
	if (strcmp(config.c_str(), "nokey") == 0) SortProton = 0;
	else if( sscanf( config.c_str(), "%d\n", &Sort_nProton) == 1 )
	{
		cout << "Sort: Require " << Sort_nProton << " proton(s)" << endl;	
		SortProton = 1;
	}	
	else {
		SortProton = 0;
		cout << "Sort-Proton cut set improperly (turned off)" <<endl;
	}
	cout << endl;
	return kTRUE;
}

void	GSort::Reconstruct()
{
}

Bool_t GSort::SortAnalyseEvent()
{
	// Sort on raw variables before analysis (increases speed)
	
	if(SortRawNumberParticles == 1)
	{
		Int_t i;

		// Total number of particles
		i = Sort_raw_nParticles_total_condition;
		if(i == 0) { if (GetNParticles() < Sort_raw_nParticles_total) {return kFALSE;}}
		else if(i == 1) {if (GetNParticles() > Sort_raw_nParticles_total) {return kFALSE;}}
		else if(i == 2) {if (GetNParticles() != Sort_raw_nParticles_total) {return kFALSE;}}
		
		// Number of particles in CB
		i = Sort_raw_nParticles_CB_condition;
		if(i == 0) { if (GetNCB() < Sort_raw_nParticles_CB) {return kFALSE;}}
		else if(i == 1) {if (GetNCB() > Sort_raw_nParticles_CB) {return kFALSE;}}
		else if(i == 2) {if (GetNCB() != Sort_raw_nParticles_CB) {return kFALSE;}}
		
		// Number of particles in TAPS
		i = Sort_raw_nParticles_TAPS_condition;
		if(i == 0) { if (GetNTAPS() < Sort_raw_nParticles_TAPS) {return kFALSE;}}
		else if(i == 1) {if (GetNTAPS() > Sort_raw_nParticles_TAPS) {return kFALSE;}}
		else if(i == 2) {if (GetNTAPS() != Sort_raw_nParticles_TAPS) {return kFALSE;}}	

	}
	
	return kTRUE;

}


Bool_t GSort::SortFillEvent()
{
	
	if(SortProton == 1)
	{
		if (GetNProton() != Sort_nProton) return kFALSE;
	}

	return kTRUE;

}

/*
Bool_t	GSort::SortOnParticle(Int_t PDG, Int_t Num, Double_t ThetaMin, Double_t ThetaMax)
{
	Int_t NumberFound = 0;
	
	for (Int_t i = 0; i < GP_GetNParticles(); i++)
	{
		if (GetPDG(i) == PDG)
		{
			NumberFound++;
			//Check theta limits
			if ((GetTheta(i) < ThetaMin) || (GetTheta(i) > ThetaMax))
			return kFALSE;
		}
	}
	if (NumberFound != Num) return kFALSE;
			
	return kTRUE;
}
*/

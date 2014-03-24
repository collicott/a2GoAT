
#include "GDataChecks.h"

GDataChecks::GDataChecks()  :
				CheckCBStability(0),
				CBHitsThresh1(0),
				CBHitsThresh2(0),
				CBHitsThresh3(0),
				CBHitsThresh4(0)
{
}

GDataChecks::~GDataChecks()
{
}

Bool_t	GDataChecks::PostInit()
{
	config = ReadConfig("CheckCBStability");
	if( sscanf(config.c_str(),"%d %lf\n", &CheckCBStability, &CBStabilityCutoff) == 2 ) 
	{	
		if(CheckCBStability)
		{
			cout << "Data Check (CB Stability) turned on" << endl;
			cout << "Using cutoff ratio of " << CBStabilityCutoff << endl << endl;	
		}
	}
	else if( sscanf(config.c_str(),"%d\n", &CheckCBStability) == 1 ) 
	{	
		if(CheckCBStability)
		{
			cout << "Data Check (CB Stability) turned on" << endl;
			CBStabilityCutoff = 0.5;
			cout << "Using cutoff ratio of 0.5 (default)" << endl << endl;	
		}
	}
	else CheckCBStability = kFALSE;
	
	return kTRUE;
}

void	GDataChecks::ScalerByScalerChecks(const Int_t min, const Int_t max)
{
	if (CheckCBStability) 
	{
		if(!CheckCBHits(min,max)) throw 1; 
	}
}

void	GDataChecks::EventByEventChecks(const Int_t i)
{
}

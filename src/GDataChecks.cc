
#include "GDataChecks.h"


using namespace std;


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

Bool_t	GDataChecks::Init()
{
    std::string config = ReadConfig("CheckCBStability");
    if( sscanf(config.c_str(),"%d %lf\n", (int*)(&CheckCBStability), &CBStabilityCutoff) == 2 )
	{	
		if(CheckCBStability)
		{
			cout << "Data Check (CB Stability) turned on" << endl;
			cout << "Using cutoff ratio of " << CBStabilityCutoff << endl << endl;	
		}
	}
    else if( sscanf(config.c_str(),"%d\n", (int*)(&CheckCBStability)) == 1 )
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

inline Bool_t 	GDataChecks::CheckCBHits(const Int_t min, const Int_t max)
{
    // Check CB hits between scaler reads to eliminate data with CB hole problem
    Int_t SumQ1 = 0;
    Int_t SumQ2 = 0;
    Int_t SumQ3 = 0;
    Int_t SumQ4 = 0;

    if(!detectorHits->IsOpenForInput())
    {
        if(!detectorHits->OpenForInput())
        {
            cout << "Can not check CB Hits. Now treeDetectorHits available." << endl;
            return false;
        }
    }

    for(int i=min; i<=max; i++)
    {
        detectorHits->GetEntry(i);

        for (int j=0; j<=detectorHits->GetNNaI_Hits(); j++)
        {
            if  (detectorHits->GetNaI_Hits(j) <  180) SumQ1++;
            if ((detectorHits->GetNaI_Hits(j) >= 180) && (detectorHits->GetNaI_Hits(j) < 360)) SumQ2++;
            if ((detectorHits->GetNaI_Hits(j) >= 360) && (detectorHits->GetNaI_Hits(j) < 540)) SumQ3++;
            if ((detectorHits->GetNaI_Hits(j) >= 540) && (detectorHits->GetNaI_Hits(j) < 720)) SumQ4++;
        }
    }

    // Check if sum is above some threshold
    if (SumQ1 < CBHitsThresh1) return kFALSE;
    if (SumQ2 < CBHitsThresh2) return kFALSE;
    if (SumQ3 < CBHitsThresh3) return kFALSE;
    if (SumQ4 < CBHitsThresh4) return kFALSE;

    // Set new baseline
    CBHitsThresh1 = int(CBStabilityCutoff*SumQ1);
    CBHitsThresh2 = int(CBStabilityCutoff*SumQ2);
    CBHitsThresh3 = int(CBStabilityCutoff*SumQ3);
    CBHitsThresh4 = int(CBStabilityCutoff*SumQ4);

    return kTRUE;

}

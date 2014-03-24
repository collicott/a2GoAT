
#ifndef __GDataChecks_h__
#define __GDataChecks_h__

#include "GoATTreeManager.h"

class	GDataChecks :  public GoATTreeManager
{
private:

	// Data Handling tools
	Int_t 		CBHitsThresh1;
	Int_t 		CBHitsThresh2;
	Int_t 		CBHitsThresh3;
	Int_t 		CBHitsThresh4;	
    		    
protected:
	    
public:

	GDataChecks();
	~GDataChecks();

	virtual void	Analyse() {;}
	virtual void	Reconstruct() {;}
	Bool_t	PostInit();
	
	void ScalerByScalerChecks(const Int_t min, const Int_t max);
	void EventByEventChecks(const Int_t i);
	
	Bool_t	CheckCBHits(const Int_t min, const Int_t max);
	
	// Data handling
    Bool_t 		CheckCBStability;
    Double_t  	CBStabilityCutoff;   
    
};

// -----------------------------------------------------------------------

inline Bool_t 	GDataChecks::CheckCBHits(const Int_t min, const Int_t max)
{
	// Check CB hits between scaler reads to eliminate data with CB hole problem 
	Int_t SumQ1 = 0;
	Int_t SumQ2 = 0;
	Int_t SumQ3 = 0;
	Int_t SumQ4 = 0;
	
    for(int i=min; i<=max; i++)
    {	
		GetTreeDetectorHitsEntry(i);
		
		for (int j=0; j<=GetNNaI_Hits(); j++)
		{
			if  (GetNaI_Hits(j) <  180) SumQ1++;
			if ((GetNaI_Hits(j) >= 180) && (GetNaI_Hits(j) < 360)) SumQ2++;
			if ((GetNaI_Hits(j) >= 360) && (GetNaI_Hits(j) < 540)) SumQ3++;
			if ((GetNaI_Hits(j) >= 540) && (GetNaI_Hits(j) < 720)) SumQ4++;
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


#endif


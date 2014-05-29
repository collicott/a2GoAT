
#ifndef __GDataChecks_h__
#define __GDataChecks_h__

#include "GTreeManager.h"

class	GDataChecks : virtual public GTreeManager
{
private:

	// Data Handling tools
	Int_t 		CBHitsThresh1;
	Int_t 		CBHitsThresh2;
	Int_t 		CBHitsThresh3;
	Int_t 		CBHitsThresh4;	
    		    
    // Data handling
    Bool_t 		CheckCBStability;
    Double_t  	CBStabilityCutoff;

protected:
    Bool_t	Init();

public:

	GDataChecks();
	~GDataChecks();
	
	void ScalerByScalerChecks(const Int_t min, const Int_t max);
	void EventByEventChecks(const Int_t i);
	
	Bool_t	CheckCBHits(const Int_t min, const Int_t max);    
};


#endif


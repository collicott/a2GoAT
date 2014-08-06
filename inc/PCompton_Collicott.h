#ifndef __PCompton_Collicott_h__
#define __PCompton_Collicott_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string> 

#include "GTreeManager.h"
#include "PPhysics.h"

class	PCompton  : public PPhysics
{
private:
//    GH1*	phi[18];
    GH1* 	MM;
    GH1*	phi_diff;
    GH1*	charged_theta;
    
    GH1* 	MM_cut;
    GH1*	phi_diff_cut;
    GH1*	charged_theta_cut;
        
    GH1* 	MM_250_270;
    GH1* 	MM_270_290;
    GH1* 	MM_290_310;
    
	Double_t cop_cut_low;
	Double_t cop_cut_high;
	Bool_t 	 IsCoplanar;
	Double_t phiDiff;

	Double_t phot_theta;
	Double_t charg_theta;	
	Double_t phot_phi;
	Double_t charg_phi;
	
	Double_t charg_theta_cut;
	Bool_t 	 IsForwardCharged;
	    
protected:
    virtual Bool_t  Start();

    virtual void    ProcessEvent();
    virtual void	ProcessScalerRead();    
			
public:
    PCompton();
    virtual ~PCompton();

    //virtual Bool_t	Init(const char* configfile);

};
#endif

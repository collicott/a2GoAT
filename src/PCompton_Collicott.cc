#include "PCompton_Collicott.h"

PCompton::PCompton() :
	IsCoplanar(kFALSE),
	IsForwardCharged(kFALSE)
{ 
    GHistBGSub::InitCuts(-20, 15, -450, -50);
    GHistBGSub::AddRandCut(45, 445);
    
  	SetTarget(938); 

	cop_cut_low  = 170.0;
	cop_cut_high = 190.0;      
	charg_theta_cut = 50; 

/*	for (Int_t i = 1; i =< 18; i++)
	{
		Int_t j = i*10;
		Char_t* name = Form("phi_%d", j);
		phi[i] = new GH1(name,name, 18,-180,-180);
	}*/
   
    MM	= new GH1("MM", "MM", 400, 800, 1400);    
    MM_cut	= new GH1("MM_cut", "MM_cut", 400, 800, 1400);     

    phi_diff	= new GH1("phi_diff", "phi_diff", 360, 0, 360);
    phi_diff_cut= new GH1("phi_diff_cut", "phi_diff_cut", 360, 0, 360);
    
    charged_theta	= new GH1("charged_theta", "charged_theta", 180, 0, 180); 
    charged_theta_cut= new GH1("charged_theta_cut", "charged_theta_cut", 180, 0, 180); 
      
    MM_250_270 	= new GH1("MM_250_270", "MM_250_270", 400, 800, 1400);
    MM_270_290 	= new GH1("MM_270_290", "MM_270_290", 400, 800, 1400);
    MM_290_310 	= new GH1("MM_290_310", "MM_290_310", 400, 800, 1400);   	
    
}

PCompton::~PCompton()
{
}

Bool_t	PCompton::Start()
{
    if(!IsGoATFile())
    {
        cout << "ERROR: Input File is not a GoAT file." << endl;
        return kFALSE;
    }
    SetAsPhysicsFile();

    TraverseValidEvents();

	return kTRUE;
}

void	PCompton::ProcessEvent()
{
//	RETURN IF NOT Twp Parotocle
	
	// Check that 1 particle is gamma
	if (photons->GetNParticles() != 1) return;
	if ((photons->GetTime(0) < -50) || (photons->GetTime(0) > 50)) return;
	
	// Find other particle
	if (rootinos->GetNParticles() != 1) return;
	if ((rootinos->GetTime(0) < -50) || (rootinos->GetTime(0) > 50)) return;
		
	// grab particle kinematics (convert to degrees)
	phot_theta  = TMath::RadToDeg()*photons->Particle(0).Theta();
	phot_phi  	= TMath::RadToDeg()*photons->Particle(0).Phi();
	
	charg_theta = TMath::RadToDeg()*rootinos->Particle(0).Theta();
	charg_phi 	= TMath::RadToDeg()*rootinos->Particle(0).Phi();
	
	// Check coplanarity
	phiDiff = TMath::Abs(phot_phi - charg_phi);
	if ((phiDiff >= cop_cut_low) && (phiDiff <= cop_cut_high)) IsCoplanar = kTRUE;
	else IsCoplanar = kFALSE;
	phi_diff->Fill(phiDiff);
	
	// Check Forward charged
	if (charg_theta <= charg_theta_cut) IsForwardCharged = kTRUE;
	else IsForwardCharged = kFALSE;
	charged_theta->Fill(charg_theta);

	// Fill all 1 gamma photon MM
	FillMissingMass(*photons,0,MM);
		
	// Enforce cuts
	if ((!IsCoplanar) || (!IsForwardCharged)) return;


	// Okay, at this point, there is one neutral + one charged particle
	// They have passed a coplanarity cut (if on)
	// They have passed a forward charged particle cut (if on)
	phi_diff_cut->Fill(phiDiff);
	charged_theta_cut->Fill(charg_theta);
	FillMissingMass(*photons,0,MM_cut);	
	
	//for (Int_t i = 0; i < 18; i++) phi[i]->Fill(phot_phi);
	FillMissingMass(*photons,0,MM);
	
    for (Int_t i = 0; i < tagger->GetNTagged(); i++)
	{
		if((tagger->GetPhotonBeam_E(i) >= 250) 
		&& (tagger->GetPhotonBeam_E(i) <= 270)) 
					FillMissingMass(*photons,0, i, MM_250_270);

		if((tagger->GetPhotonBeam_E(i) >= 270) 
		&& (tagger->GetPhotonBeam_E(i) <= 290)) 
					FillMissingMass(*photons,0, i, MM_270_290);
					
		if((tagger->GetPhotonBeam_E(i) >= 290) 
		&& (tagger->GetPhotonBeam_E(i) <= 310)) 
					FillMissingMass(*photons,0, i, MM_290_310);								
	}	
	
}

void	PCompton::ProcessScalerRead()
{

    //time.ScalerReadCorrection(5);
}


#include "GSort.h"


GSort::GSort()
{

}

GSort::~GSort()
{
}

Bool_t	GSort::PostInit()
{
	// Cut on CB Energy Sum (raw data cut)
	config = ReadConfig("SortRaw-CBEnergySum");
	if (strcmp(config.c_str(), "nokey") == 0) SortRawCBESum = 0;
	else if( sscanf(config.c_str(),"%lf %s\n",&SR_CBESum, string_in1) == 2 )
	{
		CheckConfigCondition(string_in1, &SR_CBESum_condition, string_out1);
		if(SR_CBESum_condition == -1) SortRawCBESum = 0;
		else SortRawCBESum = 1;
		
		if(SortRawCBESum == 1)
			cout << "Sort: Crystal Ball Energy Sum " 
				 << SR_CBESum << " "<< string_out1 << endl;
		else 
		{
			cout << "SortRaw-CBEnergySum cut set improperly" <<endl;
			return kFALSE;
		 }
		 cout << endl;
	}	
	else {
		SortRawCBESum = 0;
	}	

	// Cut on raw number of particle tracks (raw data cut)
	config = ReadConfig("SortRaw-NParticles");
	if (strcmp(config.c_str(), "nokey") == 0) SortRawNParticles = 0;
	else if( sscanf( config.c_str(), "%d %s %d %s %d %s\n", 
		&SR_nPart_total, 	string_in1,
		&SR_nPart_CB,   	string_in2,
        &SR_nPart_TAPS,  	string_in3) == 6 )
	{		
		SortRawNParticles = 1;	

		// Total Number of particle tracks
		CheckConfigCondition(string_in1, &SR_nPart_total_condition, string_out1);
		if(SR_nPart_total_condition == -1) SortRawNParticles = 0;
		
		// Number of particle tracks in CB
		CheckConfigCondition(string_in2, &SR_nPart_CB_condition, string_out2);
		if(SR_nPart_CB_condition == -1) SortRawNParticles = 0;

		// Number of particle tracks in TAPS
		CheckConfigCondition(string_in3, &SR_nPart_TAPS_condition, string_out3);
		if(SR_nPart_TAPS_condition == -1) SortRawNParticles = 0;

		if(SortRawNParticles == 1)
		{
			cout << "Sort: Total # of Particles before reconstruction   " 
				 << SR_nPart_total << " "<< string_out1 << endl;
			cout << "Sort: # of Particles before reconstruction in CB   " 
				 << SR_nPart_CB << " "<< string_out2 << endl;
			cout << "Sort: # of Particles before reconstruction in TAPS " 
				 << SR_nPart_TAPS << " "<< string_out3 << endl;
		 }
		 else
		 {
			cout << "SortRaw-NParticles cut set improperly" <<endl;
			return kFALSE;
		 }
		 cout << endl;
	}
	else {
		SortRawNParticles = 0;
	}
	
	// Cut on reconstructed number of particles
	config = ReadConfig("Sort-NParticles");
	if (strcmp(config.c_str(), "nokey") == 0) SortNParticles = 0;
	else if( sscanf( config.c_str(), "%d %s\n", 
		&S_nParticles, string_in1) == 2 )
	{

		CheckConfigCondition(string_in1, &S_nParticles_condition, string_out1);
		if(S_nParticles_condition == -1) SortNParticles = 0;
		else SortNParticles = 1;
		
		if(SortNParticles == 1)
			cout << "Sort: Total # of Particles after reconstruction    " 
				 << S_nParticles << " "<< string_out1 << endl;
		else 
		{
			cout << "Sort-NParticles cut set improperly" <<endl;
			cout << "Continuing with this cut turned off!" << endl;
		 }
	}	
	else {
		SortNParticles = 0;
	}	
	
	SortProton 	= 0;
	SortChPion	= 0;
	SortPi0		= 0;
	SortEta		= 0;
	
	// Cut on individual particle properties
	Int_t instance = 0;
	do
	{
		char pdg[256], cond[256];	
		Int_t num, condition;
		Double_t th_min, th_max;

		config = ReadConfig("Sort-Particle",instance);
		if( sscanf( config.c_str(), "%s %d %s %lf %lf\n", 
			pdg, &num, cond, &th_min, &th_max) == 5 )
		{
			CheckConfigCondition(cond, &condition, string_out1);
			if(strcmp(pdg,"charged") == 0)
			{
				SortCharged 			= 1;
				S_nCharged				= num;
				S_nCharged_condition 	= condition;
				S_Charged_theta_min		= th_min;
				S_Charged_theta_max		= th_max;	
				
				cout << "Sort: Require " << S_nCharged << " charged particle(s) " 
					 << string_out1 << "within theta = [" 
					 << S_Charged_theta_min << "," 
					 << S_Charged_theta_max << "]" << endl;	
			}
			else if(strcmp(pdg,"neutral") == 0)
			{
				SortNeutral				= 1;
				S_nNeutral				= num;
				S_nNeutral_condition 	= condition;
				S_Neutral_theta_min		= th_min;
				S_Neutral_theta_max		= th_max;	
				
				cout << "Sort: Require " << S_nNeutral << " neutral particle(s) " 
					 << string_out1 << "within theta = [" 
					 << S_Neutral_theta_min << "," 
					 << S_Neutral_theta_max << "]" << endl;	
			}						
			else if((strcmp(pdg,"proton") == 0) || (atoi(pdg) == pdg_proton))
			{
				SortProton 			= 1;
				S_nProton			= num;
				S_nProton_condition = condition;
				S_Proton_theta_min	= th_min;
				S_Proton_theta_max	= th_max;	
				
				cout << "Sort: Require " << S_nProton << " proton(s) " 
					 << string_out1  << "within theta = [" 
					 << S_Proton_theta_min << "," 
					 << S_Proton_theta_max << "]" << endl;	
				
			}

			else if((strcmp(pdg,"chpion") == 0) || (atoi(pdg) == pdg_chpion))
			{
				SortChPion 			= 1;
				S_nChPion			= num;
				S_nChPion_condition = condition;
				S_ChPion_theta_min	= th_min;
				S_ChPion_theta_max	= th_max;	
				
				cout << "Sort: Require " << S_nChPion << " charged pion(s) " 
					 << string_out1 << "within theta = [" 
					 << S_ChPion_theta_min << "," 
					 << S_ChPion_theta_max << "]" << endl;	
			}
			
			else if((strcmp(pdg,"pi0") == 0) || (atoi(pdg) == pdg_pi0))
			{
				SortPi0 			= 1;
				S_nPi0				= num;
				S_nPi0_condition 	= condition;
				S_Pi0_theta_min		= th_min;
				S_Pi0_theta_max		= th_max;	
				
				cout << "Sort: Require " << S_nPi0 << " neutral pion(s) " 
					 << string_out1 << "within theta = [" 
					 << S_Pi0_theta_min << "," 
					 << S_Pi0_theta_max << "]" << endl;	
			}			

			else if((strcmp(pdg,"eta") == 0) || (atoi(pdg) == pdg_eta))
			{
				SortEta 			= 1;
				S_nEta				= num;
				S_nEta_condition 	= condition;
				S_Eta_theta_min		= th_min;
				S_Eta_theta_max		= th_max;	
				
				cout << "Sort: Require " << S_nEta << " eta(s) " 
					 << string_out1 << "within theta = [" 
					 << S_Eta_theta_min << "," 
					 << S_Eta_theta_max << "]" << endl;	
			}
			else if((strcmp(pdg,"eta'") == 0) || (atoi(pdg) == pdg_etaP)
				 || (strcmp(pdg,"etaprime") == 0) )
			{
				SortEtaP 			= 1;
				S_nEtaP				= num;
				S_nEtaP_condition 	= condition;
				S_EtaP_theta_min	= th_min;
				S_EtaP_theta_max	= th_max;	
				
				cout << "Sort: Require " << S_nEtaP << " eta(s) " 
					 << string_out1 << "within theta = [" 
					 << S_EtaP_theta_min << "," 
					 << S_EtaP_theta_max << "]" << endl;	
			}			
			else if((strcmp(pdg,"electron") == 0) || (atoi(pdg) == pdg_electron))
			{
				SortElectron 			= 1;
				S_nElectron				= num;
				S_nElectron_condition 	= condition;
				S_Electron_theta_min	= th_min;
				S_Electron_theta_max	= th_max;	
				
				cout << "Sort: Require " << S_nElectron << " electron(s) " 
					 << string_out1 << "within theta = [" 
					 << S_Electron_theta_min << "," 
					 << S_Electron_theta_max << "]" << endl;	
			}
			else{
				cout << endl << "ERROR unknown particle type ("  << pdg 
					 << ") set by Sort-Particle." << endl << endl;
				return kFALSE;
			}
		}	
		else if (strcmp(config.c_str(), "nokey") != 0)
		{
			cout << "Sort-Particle cut was set improperly" << endl;
			return kFALSE;		
		}	
		instance++;
	} while (strcmp(config.c_str(), "nokey") != 0);

	

	cout << endl;
	return kTRUE;
}

void	GSort::Reconstruct()
{
}

Bool_t GSort::SortAnalyseEvent()
{
	// Sort on raw variables before analysis (increases speed)
	if(SortRawNParticles == 1)
	{
		switch (SR_nPart_total_condition) 	// Total number of particles
		{
			case 0:
				if (GetNParticles() < SR_nPart_total) 	return kFALSE;
				break;
			case 1:
				if (GetNParticles() > SR_nPart_total) 	return kFALSE;
				break;
			case 2:
				if (GetNParticles() != SR_nPart_total) 	return kFALSE;
				break;
		}
		
		switch (SR_nPart_CB_condition) 	// Number of particles in CB
		{
			case 0:
				if (GetNCB() < SR_nPart_CB) 			return kFALSE;
				break;
			case 1:
				if (GetNCB() > SR_nPart_CB) 			return kFALSE;
				break;
			case 2:
				if (GetNCB() != SR_nPart_CB) 			return kFALSE;
				break;
		}
		
		switch (SR_nPart_TAPS_condition) 	// Number of particles in TAPS
		{
			case 0:
				if (GetNTAPS() < SR_nPart_TAPS) 		return kFALSE;
				break;
			case 1:
				if (GetNTAPS() > SR_nPart_TAPS) 		return kFALSE;
				break;
			case 2:
				if (GetNTAPS() != SR_nPart_TAPS)		return kFALSE;
				break;
		}
	}
	
	if(SortRawCBESum == 1)
	{
		switch (SR_CBESum_condition) 	// Crystal Ball Energy Sum
		{
			case 0:
				if (GetESum() < SR_CBESum) 				return kFALSE;
				break;
			case 1:
				if (GetESum() > SR_CBESum) 				return kFALSE;
				break;
			case 2:
				if (GetESum() != SR_CBESum)				return kFALSE;
				break;
		}
	}	
	
	return kTRUE;
}


Bool_t GSort::SortFillEvent()
{

	if(SortNParticles == 1)
	{
		switch (S_nParticles_condition) // Number of reconstructed part
		{
			case 0:
				if(GTree_GetNParticles() < S_nParticles)  return kFALSE;
				break;
			case 1:
				if(GTree_GetNParticles() > S_nParticles)  return kFALSE;
				break;
			case 2:
				if(GTree_GetNParticles() != S_nParticles) return kFALSE;
				break;
		}
	}

	if(SortCharged == 1)
	{
		if(!SortOnNeutrality(1,
							S_nCharged,
							S_nCharged_condition,
							S_Charged_theta_min,
							S_Charged_theta_max)) 	return kFALSE;
	}
	
	if(SortNeutral == 1)
	{
		if(!SortOnNeutrality(0,
							S_nNeutral,
							S_nNeutral_condition,
							S_Neutral_theta_min,
							S_Neutral_theta_max)) 	return kFALSE;
	}
			
	if(SortProton == 1)
	{
		if(!SortOnParticle(pdg_proton,
							S_nProton,
							S_nProton_condition,
							S_Proton_theta_min,
							S_Proton_theta_max)) 	return kFALSE;
	}

	if(SortChPion == 1)
	{
		if(!SortOnParticle(pdg_chpion,
							S_nChPion,
							S_nChPion_condition,
							S_ChPion_theta_min,
							S_ChPion_theta_max)) 	return kFALSE;
	}
		
	if(SortPi0 == 1)
	{
		if(!SortOnParticle(pdg_pi0,
							S_nPi0,
							S_nPi0_condition,
							S_Pi0_theta_min,
							S_Pi0_theta_max)) 		return kFALSE;
	}

	if(SortEta == 1)
	{
		if(!SortOnParticle(pdg_eta,
							S_nEta,
							S_nEta_condition,
							S_Eta_theta_min,
							S_Eta_theta_max)) 		return kFALSE;
	}
	
	if(SortEtaP == 1)
	{
		if(!SortOnParticle(pdg_etaP,
							S_nEtaP,
							S_nEtaP_condition,
							S_EtaP_theta_min,
							S_EtaP_theta_max)) 		return kFALSE;
	}	

	if(SortElectron == 1)
	{
		if(!SortOnParticle(pdg_electron,
							S_nElectron,
							S_nElectron_condition,
							S_Electron_theta_min,
							S_Electron_theta_max)) 	return kFALSE;
	}	
	return kTRUE;

}


Bool_t	GSort::SortOnParticle(Int_t PDG, Int_t Num, Int_t cond, Double_t ThetaMin, Double_t ThetaMax)
{
	Int_t NumberFound = 0;
	
	for (Int_t i = 0; i < GTree_GetNParticles(); i++)
	{
		if (GTree_GetPDG(i) == PDG)
		{
			// Check theta limits
			if ((GTree_GetTheta(i) <= ThetaMin) || 
				(GTree_GetTheta(i) >= ThetaMax))
			return kFALSE;
			NumberFound++;
		}
	}

	switch (cond)
	{
		case 0:
			if (NumberFound < Num) 	return kFALSE;
			break;
		case 1:
			if (NumberFound > Num) 	return kFALSE;
			break;
		case 2:
			if (NumberFound != Num)	return kFALSE;
			break;
	}
			
	return kTRUE;
}

Bool_t	GSort::SortOnNeutrality(Int_t charge, Int_t Num, Int_t cond, Double_t ThetaMin, Double_t ThetaMax)
{
	Int_t NumberFound = 0;
	
	switch (charge)
	{
		case 0: // Neutral sort
			for (Int_t i = 0; i < GTree_GetNParticles(); i++)
			{
				if (GTree_GetCharge(i) > 0)
				{
					//Check theta limits
					if ((GTree_GetTheta(i) <= ThetaMin) || 
						(GTree_GetTheta(i) >= ThetaMax))
					return kFALSE;
					NumberFound++;
				}
			}
			break;
			
		case 1: // Charged sort
			for (Int_t i = 0; i < GTree_GetNParticles(); i++)
			{
				if (GTree_GetCharge(i) != 0)
				{
					//Check theta limits
					if ((GTree_GetTheta(i) <= ThetaMin) || 
						(GTree_GetTheta(i) >= ThetaMax))
					return kFALSE;
					NumberFound++;
				}
			}
			break;
	}	

	switch (cond)
	{
		case 0:
			if (NumberFound < Num) 	return kFALSE;
			break;
		case 1:
			if (NumberFound > Num) 	return kFALSE;
			break;
		case 2:
			if (NumberFound != Num)	return kFALSE;
			break;
	}
			
	return kTRUE;
}

void GSort::CheckConfigCondition(char string[], int *condition, std::string& string_out)
{
		if(strcmp(string,"+") == 0) 
		{
			string_out = "or more ";
			(*condition) = 0;
		}
		else if (strcmp(string,"-") == 0) 
		{
			string_out = "or less ";
			(*condition) = 1;
		}		
		else if (strcmp(string,"=") == 0) 
		{
			string_out = "exactly ";
			(*condition) = 2;
		}
		else
		{
			string_out = "error ";
			(*condition) = -1;
		}

}

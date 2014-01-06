
#include "GSort.h"


GSort::GSort()
{

}

GSort::~GSort()
{
}

Bool_t	GSort::PostInit()
{

	config = ReadConfig("SortRaw-NParticles",GetConfigFile());
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
			cout << "Continuing with this cut turned off!" << endl;
		 }
		 cout << endl;
	}
	else {
		SortRawNParticles = 0;
	}
	
	// Cut on reconstructed number of particles
	config = ReadConfig("SortRaw-CBEnergySum",GetConfigFile());
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
			cout << "Continuing with this cut turned off!" << endl;
		 }
		 cout << endl;
	}	
	else {
		SortRawCBESum = 0;
	}	
	
	
	// Cut on reconstructed number of particles
	config = ReadConfig("Sort-NParticles",GetConfigFile());
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
		 cout << endl;
	}	
	else {
		SortNParticles = 0;
	}	

	// Cut on proton
	config = ReadConfig("Sort-Proton",GetConfigFile());
	if (strcmp(config.c_str(), "nokey") == 0) SortProton = 0;
	else if( sscanf( config.c_str(), "%d %s %lf %lf\n", 
		&S_nProton, string_in1, &S_Proton_theta_min, &S_Proton_theta_max) == 4 )
	{

		CheckConfigCondition(string_in1, &S_nProton_condition, string_out1);
		if(S_nProton_condition == -1) SortProton = 0;
		else SortProton = 1;
		
		if(SortProton == 1)
		cout << "Sort: Require " << S_nProton << " proton(s) " << string_out1 
		     << "within theta = [" << S_Proton_theta_min << "," 
		     << S_Proton_theta_max << "]" << endl;	
		else 
		{
			cout << "Sort-Proton cut set improperly" <<endl;
			cout << "Continuing with this cut turned off!" << endl;
		 }
	}	
	else {
		SortProton = 0;
	}

	// Cut on ChPion
	config = ReadConfig("Sort-ChPion",GetConfigFile());
	if (strcmp(config.c_str(), "nokey") == 0) SortChPion = 0;
	else if( sscanf( config.c_str(), "%d %s %lf %lf\n", 
		&S_nChPion, string_in1, &S_ChPion_theta_min, &S_ChPion_theta_max) == 4 )
	{

		CheckConfigCondition(string_in1, &S_nChPion_condition, string_out1);
		if(S_nChPion_condition == -1) SortChPion = 0;
		else SortChPion = 1;
		
		if(SortChPion == 1)
		cout << "Sort: Require " << S_nChPion << " charged pion(s) " << string_out1 
		     << "within theta = [" << S_ChPion_theta_min << "," 
		     << S_ChPion_theta_max << "]" << endl;	
		else 
		{
			cout << "Sort-ChPion cut set improperly" <<endl;
			cout << "Continuing with this cut turned off!" << endl;
		 }
	}	
	else {
		SortChPion = 0;
	}
	
	// Cut on pi0
	config = ReadConfig("Sort-Pi0",GetConfigFile());
	if (strcmp(config.c_str(), "nokey") == 0) SortPi0 = 0;
	else if( sscanf( config.c_str(), "%d %s %lf %lf\n", 
		&S_nPi0, string_in1, &S_Pi0_theta_min, &S_Pi0_theta_max) == 4 )
	{

		CheckConfigCondition(string_in1, &S_nPi0_condition, string_out1);
		if(S_nPi0_condition == -1) SortPi0 = 0;
		else SortPi0 = 1;
		
		if(SortPi0 == 1)
		cout << "Sort: Require " << S_nPi0 << " neutral pion(s) " << string_out1 
		     << "within theta = [" << S_Pi0_theta_min << "," 
		     << S_Pi0_theta_max << "]" << endl;	
		else 
		{
			cout << "Sort-Pi0 cut set improperly" <<endl;
			cout << "Continuing with this cut turned off!" << endl;
		 }
	}	
	else {
		SortPi0 = 0;
	}

	// Cut on eta
	config = ReadConfig("Sort-Eta",GetConfigFile());
	if (strcmp(config.c_str(), "nokey") == 0) SortEta = 0;
	else if( sscanf( config.c_str(), "%d %s %lf %lf\n", 
		&S_nEta, string_in1, &S_Eta_theta_min, &S_Eta_theta_max) == 4 )
	{

		CheckConfigCondition(string_in1, &S_nEta_condition, string_out1);
		if(S_nEta_condition == -1) SortEta = 0;
		else SortEta = 1;
		
		if(SortEta == 1)
		cout << "Sort: Require " << S_nEta << " eta(s) " << string_out1 
		     << "within theta = [" << S_Eta_theta_min << "," 
		     << S_Eta_theta_max << "]" << endl;	
		else 
		{
			cout << "Sort-Eta cut set improperly" <<endl;
			cout << "Continuing with this cut turned off!" << endl;
		 }
	}	
	else {
		SortEta = 0;
	}
	
	// Cut on eta-prime
	config = ReadConfig("Sort-Eta-Prime",GetConfigFile());
	if (strcmp(config.c_str(), "nokey") == 0) SortEtaP = 0;
	else if( sscanf( config.c_str(), "%d %s %lf %lf\n", 
		&S_nEtaP, string_in1, &S_EtaP_theta_min, &S_EtaP_theta_max) == 4 )
	{

		CheckConfigCondition(string_in1, &S_nEtaP_condition, string_out1);
		if(S_nEtaP_condition == -1) SortEtaP = 0;
		else SortEtaP = 1;
		
		if(SortEtaP == 1)
		cout << "Sort: Require " << S_nEtaP << " eta prime(s) " << string_out1 
		     << "within theta = [" << S_EtaP_theta_min << "," 
		     << S_EtaP_theta_max << "]" << endl;	
		else 
		{
			cout << "Sort-Eta-Prime cut set improperly" <<endl;
			cout << "Continuing with this cut turned off!" << endl;
		 }
	}	
	else {
		SortEtaP = 0;
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
	Int_t i;	
	if(SortRawNParticles == 1)
	{
		// Total number of particles
		i = SR_nPart_total_condition;
		if(i == 0) { if (GetNParticles() < SR_nPart_total) {return kFALSE;}}
		else if(i == 1) {if (GetNParticles() > SR_nPart_total) {return kFALSE;}}
		else if(i == 2) {if (GetNParticles() != SR_nPart_total) {return kFALSE;}}
		
		// Number of particles in CB
		i = SR_nPart_CB_condition;
		if(i == 0) { if (GetNCB() < SR_nPart_CB) {return kFALSE;}}
		else if(i == 1) {if (GetNCB() > SR_nPart_CB) {return kFALSE;}}
		else if(i == 2) {if (GetNCB() != SR_nPart_CB) {return kFALSE;}}
		
		// Number of particles in TAPS
		i = SR_nPart_TAPS_condition;
		if(i == 0) { if (GetNTAPS() < SR_nPart_TAPS) {return kFALSE;}}
		else if(i == 1) {if (GetNTAPS() > SR_nPart_TAPS) {return kFALSE;}}
		else if(i == 2) {if (GetNTAPS() != SR_nPart_TAPS) {return kFALSE;}}	
	}
	
	if(SortRawCBESum == 1)
	{
		// Crystal Ball Energy Sum
		i = SR_CBESum_condition;
		if(i == 0) { if (GetESum() < SR_CBESum) {return kFALSE;}}
		else if(i == 1) {if (GetESum() > SR_CBESum) {return kFALSE;}}
		else if(i == 2) {if (GetESum() != SR_CBESum) {return kFALSE;}}
	}	
	
	return kTRUE;
}


Bool_t GSort::SortFillEvent()
{

	if(SortNParticles == 1)
	{
		Int_t i = S_nParticles_condition;
		if(i == 0) { if (GTree_GetNParticles() < S_nParticles) {return kFALSE;}}
		else if(i == 1) {if (GTree_GetNParticles() > S_nParticles) {return kFALSE;}}
		else if(i == 2) {if (GTree_GetNParticles() != S_nParticles) {return kFALSE;}}
	}
	
	if(SortProton == 1)
	{
		if(!SortOnParticle(pdg_proton,
							S_nProton,
							S_nProton_condition,
							S_Proton_theta_min,
							S_Proton_theta_max)) return kFALSE;
	}

	if(SortChPion == 1)
	{
		if(!SortOnParticle(pdg_chpion,
							S_nChPion,
							S_nChPion_condition,
							S_ChPion_theta_min,
							S_ChPion_theta_max)) return kFALSE;
	}
		
	if(SortPi0 == 1)
	{
		if(!SortOnParticle(pdg_pi0,
							S_nPi0,
							S_nPi0_condition,
							S_Pi0_theta_min,
							S_Pi0_theta_max)) return kFALSE;
	}

	if(SortEta == 1)
	{
		if(!SortOnParticle(pdg_eta,
							S_nEta,
							S_nEta_condition,
							S_Eta_theta_min,
							S_Eta_theta_max)) return kFALSE;
	}
	
	if(SortEtaP == 1)
	{
		if(!SortOnParticle(pdg_etaP,
							S_nEtaP,
							S_nEtaP_condition,
							S_EtaP_theta_min,
							S_EtaP_theta_max)) return kFALSE;
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
			NumberFound++;
			
			//Check theta limits
			if ((GTree_GetTheta(i) <= ThetaMin) || 
				(GTree_GetTheta(i) >= ThetaMax))
			return kFALSE;
		}
	}

	if(cond == 0) { if (NumberFound < Num) {return kFALSE;}}
	else if(cond == 1) {if (NumberFound > Num) {return kFALSE;}}
	else if(cond == 2) {if (NumberFound != Num) {return kFALSE;}}	
	
//	if (NumberFound != Num) return kFALSE;
			
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

#ifndef __CINT__

#include "PPhysics.h"

PPhysics::PPhysics() 
{ 
}

PPhysics::~PPhysics()
{
}

Bool_t	PPhysics::Init(Char_t* configfile)
{
	
	return kTRUE;
}

void	PPhysics::Reconstruct()
{
}

void PPhysics::MissingMass(Int_t pdg, TH1* prompt, TH1* random)
{
	for (Int_t i = 0; i < GoATTree_GetNParticles(); i++)
	{
		if (GoATTree_GetPDG(i) != pdg) continue; 
		
		// Get particle four vector
		particle = GetGoATVector(i);
		
		for (Int_t j = 0; j < GetNTagged(); j++)
		{
			if (!IsPrompt(GetTagged_t(j)) && !IsRandom(GetTagged_t(j))) continue;
			
			beam 	= TLorentzVector(0.,0.,GetPhotonBeam_E(j),GetPhotonBeam_E(j));
			missingp4 = beam + target - particle;

			if (IsPrompt(GetTagged_t(j))) prompt->Fill(missingp4.M());
			if (IsRandom(GetTagged_t(j))) random->Fill(missingp4.M());			

		}
	}
}	

Bool_t PPhysics::IsPrompt(Double_t time, Double_t t_low, Double_t t_high)
{
	if ((time >= t_low) && (time <= t_high)) return kTRUE;
	
	return kFALSE;
}
	
Bool_t PPhysics::IsRandom(Double_t time, Double_t t_low1, Double_t t_high1, 
										 Double_t t_low2, Double_t t_high2 )
{

	if ((time >= t_low1) && (time <= t_high1)) return kTRUE;
	if ((time >= t_low2) && (time <= t_high2)) return kTRUE;
	
	return kFALSE;
}

Bool_t 	PPhysics::Write()
{
	return kTRUE;
}

void	PPhysics::RandomSubtraction(TH1* prompt, TH1* random, TH1* sub, Double_t ratio)
{
	sub->Add(prompt,1);
	sub->Add(random,-ratio);

}

Bool_t	PPhysics::OpenPhysFile(const char* pfile)
{
	PhysFile = new TFile(pfile, "RECREATE");
	if(!PhysFile) return kFALSE;
    if(PhysFile->IsZombie()) return kFALSE;
    
	cout << "PhysFile " << pfile << " opened." << endl;
	
	return kTRUE;
}

Bool_t 	PPhysics::ClosePhysFile()
{
	if(!PhysFile) return kFALSE;
	PhysFile->Close();
	
	return kTRUE;
}

#endif

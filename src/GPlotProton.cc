#include "GPlotProton.h"


using namespace std;


GPlotProton::GPlotProton()
{

}

GPlotProton::~GPlotProton()
{

}

void  GPlotProton::ProcessEvent()
{
	if(protons->GetNParticles()==0)
		return;
		
	if(etap->GetNParticles()==1)
	{
		phiDiff->Fill(TMath::RadToDeg()*(TMath::Abs(etap->Particle(0).Phi() - protons->Particle(0).Phi())));
	}
	else if(eta->GetNParticles()==1)
	{
		phiDiff->Fill(TMath::RadToDeg()*(TMath::Abs(eta->Particle(0).Phi() - protons->Particle(0).Phi())));
	}
	else if(pi0->GetNParticles()==1)
	{
		phiDiff->Fill(TMath::RadToDeg()*(TMath::Abs(pi0->Particle(0).Phi() - protons->Particle(0).Phi())));
	}
	
	for(int i=0; i<tagger->GetNPrompt(); i++)
	{
		protonAngleDiffPrompt->Fill(TMath::RadToDeg()*protons->Particle(0).Angle(tagger->GetMissingVector(tagger->GetPromptIndex(i)).Vect()));
	}
	for(int i=0; i<tagger->GetNRand(); i++)
	{
		protonAngleDiffRand->Fill(TMath::RadToDeg()*protons->Particle(0).Angle(tagger->GetMissingVector(tagger->GetRandIndex(i)).Vect()));
	}
}

Bool_t  GPlotProton::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;

    if(!OpenEtap())    return kFALSE;
    if(!OpenEta())    return kFALSE;
    if(!OpenPi0())    return kFALSE;
    if(!OpenProtons())    return kFALSE;
    if(!OpenTagger())    return kFALSE;

	if(!Create(output_filename))    return kFALSE;

	protonAngleDiffPrompt	= new TH1D("protonAngleDiffPrompt", "Proton Angle Difference Prompt", 1000, 0, 100);
    protonAngleDiffRand		= new TH1D("protonAngleDiffRand", "Proton Angle Difference Rand", 1000, 0, 100);
    phiDiff					= new TH1D("phiDiff", "Phi Difference Proton Meson", 3600, 0, 360);
    
    TraverseEntries(0, protons->GetNEntries()+1);

    TH1D    diff(*protonAngleDiffPrompt);
    diff.SetNameTitle("protonAngleDiffPromptRandSubst", "Proton Angle Difference Prompt/Rand Substracted");
    diff.Add(protonAngleDiffRand,-0.01);
    TH1D    diffNormed(*protonAngleDiffPrompt);
    diffNormed.SetNameTitle("protonAngleDiffPromptRandSubstNorm", "Proton Angle Difference Prompt/Rand Substracted Normalised");
    diffNormed.Add(protonAngleDiffRand,-protonAngleDiffPrompt->GetMaximum()/protonAngleDiffRand->GetMaximum());
    if(!Write(protonAngleDiffPrompt))	return kFALSE;
    if(!Write(protonAngleDiffRand))	return kFALSE;
    if(!Write(phiDiff))	return kFALSE;
    if(!Write(&diff))	return kFALSE;
    if(!Write(&diffNormed))	return kFALSE;

    return kTRUE;
}


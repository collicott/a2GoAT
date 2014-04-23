#include "GPlotEnergyBins.h"


using namespace std;


GPlotEnergyBins::GPlotEnergyBins()
{

}

GPlotEnergyBins::~GPlotEnergyBins()
{

}

void  GPlotEnergyBins::ProcessEvent()
{
	if(etap->GetNParticles()!=1)
		return;
		
	for(int i=0; i<tagger->GetNPrompt(); i++)
	{
		for(int l=0; l<18; l++)
		{
			if(tagger->GetPhotonBeam_E(tagger->GetPromptIndex(i))<((10*l)+1430))
			{
				invMassEtap10[l]->Fill(GHist::FLAG_TAGGER_WINDOW_PROMPT, etap->Particle(0).M());
				break;
			}
		}
	}
	for(int i=0; i<tagger->GetNRand(); i++)
	{
		for(int l=0; l<18; l++)
		{
			if(tagger->GetPhotonBeam_E(tagger->GetRandIndex(i))<((10*l)+1430))
			{
				if(tagger->GetTagged_t(tagger->GetRandIndex(i))<0)
					invMassEtap10[l]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND1, etap->Particle(0).M());
				else
					invMassEtap10[l]->Fill(GHist::FLAG_TAGGER_WINDOW_RAND2, etap->Particle(0).M());
				break;
			}
		}
	}
}

Bool_t  GPlotEnergyBins::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;

    if(!OpenEtap())    return kFALSE;
    if(!OpenTagger())    return kFALSE;

	if(!Create(output_filename))    return kFALSE;
	
	/*file_out->cd();
    gDirectory->mkdir("prompt");
    file_out->cd();
    gDirectory->mkdir("rand");*/
	file_out->cd();
	invMassEtap10[0]	= new GHistD(gDirectory, TString("invMassEtap1420_1430"), TString("invariant Mass Eta' (Photon energy from 1420 to 1430"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[1]	= new GHistD(gDirectory, TString("invMassEtap1430_1440"), TString("invariant Mass Eta' (Photon energy from 1430 to 1440"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[2]	= new GHistD(gDirectory, TString("invMassEtap1440_1450"), TString("invariant Mass Eta' (Photon energy from 1440 to 1450"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[3]	= new GHistD(gDirectory, TString("invMassEtap1450_1560"), TString("invariant Mass Eta' (Photon energy from 1450 to 1560"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[4]	= new GHistD(gDirectory, TString("invMassEtap1460_1470"), TString("invariant Mass Eta' (Photon energy from 1460 to 1470"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[5]	= new GHistD(gDirectory, TString("invMassEtap1470_1480"), TString("invariant Mass Eta' (Photon energy from 1470 to 1480"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[6]	= new GHistD(gDirectory, TString("invMassEtap1480_1490"), TString("invariant Mass Eta' (Photon energy from 1480 to 1490"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[7]	= new GHistD(gDirectory, TString("invMassEtap1490_1500"), TString("invariant Mass Eta' (Photon energy from 1490 to 1500"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[8]	= new GHistD(gDirectory, TString("invMassEtap1500_1510"), TString("invariant Mass Eta' (Photon energy from 1500 to 1510"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[9]	= new GHistD(gDirectory, TString("invMassEtap1510_1520"), TString("invariant Mass Eta' (Photon energy from 1510 to 1520"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[10]	= new GHistD(gDirectory, TString("invMassEtap1520_1530"), TString("invariant Mass Eta' (Photon energy from 1520 to 1530"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[11]	= new GHistD(gDirectory, TString("invMassEtap1530_1540"), TString("invariant Mass Eta' (Photon energy from 1530 to 1540"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[12]	= new GHistD(gDirectory, TString("invMassEtap1540_1550"), TString("invariant Mass Eta' (Photon energy from 1540 to 1550"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[13]	= new GHistD(gDirectory, TString("invMassEtap1550_1560"), TString("invariant Mass Eta' (Photon energy from 1550 to 1560"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[14]	= new GHistD(gDirectory, TString("invMassEtap1560_1570"), TString("invariant Mass Eta' (Photon energy from 1560 to 1570"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[15]	= new GHistD(gDirectory, TString("invMassEtap1570_1580"), TString("invariant Mass Eta' (Photon energy from 1570 to 1580"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[16]	= new GHistD(gDirectory, TString("invMassEtap1580_1590"), TString("invariant Mass Eta' (Photon energy from 1580 to 1590"), 2000, 0, 2000); file_out->cd();
	invMassEtap10[17]	= new GHistD(gDirectory, TString("invMassEtap1590_1600"), TString("invariant Mass Eta' (Photon energy from 1590 to 1600"), 2000, 0, 2000); file_out->cd();
    
    TraverseEntries(0, etap->GetNEntries()+1);
	
	for(int i=0; i<18; i++)
	{
		invMassEtap10[i]->Write(0.01);
	}

	invMassEtap20[0]	= new GHistD(gDirectory, TString("invMassEtap1410_1430"), TString("invariant Mass Eta' (Photon energy from 1410 to 1430"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[1]	= new GHistD(gDirectory, TString("invMassEtap1430_1450"), TString("invariant Mass Eta' (Photon energy from 1430 to 1450"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[2]	= new GHistD(gDirectory, TString("invMassEtap1450_1470"), TString("invariant Mass Eta' (Photon energy from 1450 to 1470"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[3]	= new GHistD(gDirectory, TString("invMassEtap1470_1490"), TString("invariant Mass Eta' (Photon energy from 1470 to 1590"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[4]	= new GHistD(gDirectory, TString("invMassEtap1490_1510"), TString("invariant Mass Eta' (Photon energy from 1490 to 1510"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[5]	= new GHistD(gDirectory, TString("invMassEtap1510_1530"), TString("invariant Mass Eta' (Photon energy from 1510 to 1530"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[6]	= new GHistD(gDirectory, TString("invMassEtap1530_1550"), TString("invariant Mass Eta' (Photon energy from 1530 to 1550"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[7]	= new GHistD(gDirectory, TString("invMassEtap1550_1570"), TString("invariant Mass Eta' (Photon energy from 1550 to 1570"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[8]	= new GHistD(gDirectory, TString("invMassEtap1570_1590"), TString("invariant Mass Eta' (Photon energy from 1570 to 1590"), 2000, 0, 2000); file_out->cd();
	invMassEtap20[9]	= new GHistD(gDirectory, TString("invMassEtap1590_1610"), TString("invariant Mass Eta' (Photon energy from 1590 to 1610"), 2000, 0, 2000); file_out->cd();
	
	invMassEtap20[0]->Add(invMassEtap10[0], 1);
	for(int i=1; i<9; i++)
	{
		invMassEtap20[i]->Add(invMassEtap10[(2*i)-1], 1);
		invMassEtap20[i]->Add(invMassEtap10[(2*i)], 1);
	}
	invMassEtap20[9]->Add(invMassEtap10[17], 1);
	for(int i=0; i<10; i++)
	{
		invMassEtap20[i]->Write(0.01);
	}
	
    return kTRUE;
}


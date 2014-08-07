#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

 TFile outFile("New_2012_Pi0_results.root", "recreate");

/*
TFile *fpara = new TFile("2012_Pi0_Para.root");
TFile *fperp = new TFile("2012_Pi0_Perp.root");
TFile *fsim  = new TFile("SimulatedPi0.root");
double scale = 2.35;
double scaleMC = 5.8;
*/

/*
TFile *fpara = new TFile("Pi0Para_noTAPS.root");
TFile *fperp = new TFile("Pi0Perp_noTAPS.root");
TFile *fsim  = new TFile("SimulatedPi0.root");
double scale = 1.83;
double scaleMC = 3.7;
*/

/*
TFile *fpara = new TFile("SmallCMPi0_Para.root");
TFile *fperp = new TFile("SmallCMPi0_Perp.root");
TFile *fsim  = new TFile("SimulatedPi0.root");
double scale = 1.8;
double scaleMC = 2.5;
*/

/*
TFile *fpara = new TFile("Full_Pi0_Para.root");
TFile *fperp = new TFile("Full_Pi0_Perp.root");
TFile *fsim  = new TFile("SimulatedPi0.root");
double scale = 2.085;
double scaleMC = 11.0;
*/


TFile *fpara = new TFile("Pi0CM_10degbins_Para.root");
TFile *fperp = new TFile("Pi0CM_10degbins_Perp.root");
TFile *fsim  = new TFile("SimulatedPi0.root");
double scale = 2.4;
double scaleMC = 9.5;


int E_gamma = 275;
int dE_gamma = 5;
double pol = 0.57;
double d_pol = 0.05;

double offset; // Determine offset from first (full theta) fit;

// Pi0 Sigma3 results for display purposes
int nMAID_bins = 37;
Double_t MAID_th[37]  = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180};
Double_t MAID_pi0_275[37] = {0,0.0083,0.0317,0.0669,0.1094,0.1548,0.1996,0.2415,0.2793,0.3122,0.3403,0.3637,0.3828,0.3979,0.4093,0.4174,0.4223,0.4242,0.4232,0.4193,0.4125,0.4028,0.3899,0.3738,0.3544,0.3313,0.3046,0.2742,0.2402,0.2032,0.1641,0.1243,0.0859,0.0515,0.024,0.0062,0};

Double_t pAsym;
Double_t d_pAsym;

void StoreAll()
{
	MissingMass();
	Asymmetry();
	outFile.Close();
}

void MissingMass()
{
	TH1D* para;
	TH1D* perp;
	TH1D* sim;

	para = (TH1D*) fpara->Get("MM_subtracted_pi0");
	perp = (TH1D*) fperp->Get("MM_subtracted_pi0");
	perp->Scale(scale);	
	sim  = (TH1D*) fsim->Get("MM_subtracted_pi0");
	sim->Scale(scaleMC);

	c1 = new TCanvas("Missing Mass comparison","Missing Mass Comparison");	
	Char_t* title = Form("Missing Mass comparison (E_{#gamma} = %d #pm %d MeV)", E_gamma, dE_gamma); 
	para->SetTitle(title);
	para->GetXaxis()->SetTitle("Missing Mass (MeV)");
	perp->SetTitle("");
	sim->SetTitle("");

	perp->SetLineColor(kRed);
	para->SetLineColor(kBlue);
	sim->SetLineColor(kGreen);

	para->SetStats(0);
	perp->SetStats(0);
	sim->SetStats(0);
	
	para->GetXaxis()->SetRange(850,1050);
	perp->GetXaxis()->SetRange(850,1050);
	sim->GetXaxis()->SetRange(850,1050);
	
	para->Draw();
	perp->Draw("same");
	sim->Draw("same");


	// draw the legend
	TLegend *legend=new TLegend(0.55,0.6,0.88,0.85);
	legend->SetTextFont(72);
	legend->SetTextSize(0.03);
	legend->AddEntry(para,"PARA data (Dec. 2012)","lpe");
	legend->AddEntry(perp,"PERP data (Dec. 2012)","lpe");
	legend->AddEntry(sim, "Simulated data (AcquMC)","lpe");
	legend->Draw();	

	outFile.cd();
	c1->Write();
}

void Asymmetry()
{
	c1 = new TCanvas("pi0 Beam Asymmetry (p*Sigma) over all theta","pi0 Beam Asymmetry (p*Sigma) over all theta");	
	c1->cd();
	GetAsymmetry();

	outFile.cd();
	c1->Write();
	
	cout << "Offset determined: " << offset << endl;
		
	// Check Asymmetry by theta bin (store result in arrays)
	Int_t nbins = 18;
	Double_t  th[18] = {	5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155, 165, 175};
	Double_t dth[18] = {	5,  5,  5,  5,  5,  5, 	5,  5,  5,  5,   5,   5,   5,   5,   5,   5,   5,   5};
	Double_t  pA[18];
	Double_t dpA[18];
	
	c2 = new TCanvas("pi0 Beam Asymmetry (p*Sigma), 10 deg. theta bins, 0 to 90","pi0 Beam Asymmetry (p*Sigma), 10 deg. theta bins, 0 to 90");
	c2->Divide(3,3);
	c2->cd(1); 	GetAsymmetry("0_10"); 		pA[0] = pAsym/pol; 	dpA[0] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[0]);
	c2->cd(2); 	GetAsymmetry("10_20"); 		pA[1] = pAsym/pol; 	dpA[1] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[1]);
	c2->cd(3); 	GetAsymmetry("20_30"); 		pA[2] = pAsym/pol; 	dpA[2] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[2]);
	c2->cd(4); 	GetAsymmetry("30_40"); 		pA[3] = pAsym/pol; 	dpA[3] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[3]);
	c2->cd(5); 	GetAsymmetry("40_50"); 		pA[4] = pAsym/pol; 	dpA[4] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[4]);
	c2->cd(6);  GetAsymmetry("50_60"); 		pA[5] = pAsym/pol; 	dpA[5] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[5]);
	c2->cd(7); 	GetAsymmetry("60_70"); 		pA[6] = pAsym/pol; 	dpA[6] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[6]);
	c2->cd(8); 	GetAsymmetry("70_80"); 		pA[7] = pAsym/pol; 	dpA[7] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[7]);
	c2->cd(9); 	GetAsymmetry("80_90"); 		pA[8] = pAsym/pol; 	dpA[8] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[8]);

	outFile.cd();
	c2->Write();

	c3 = new TCanvas("pi0 Beam Asymmetry (p*Sigma), 10 deg. theta bins, 90 to 180","pi0 Beam Asymmetry (p*Sigma), 10 deg. theta bins, 90 to 180");
	c3->Divide(3,3);
	c3->cd(1); 	GetAsymmetry("90_100"); 	pA[9] = pAsym/pol; 	dpA[9]  = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[9]);
	c3->cd(2); 	GetAsymmetry("100_110"); 	pA[10] = pAsym/pol; dpA[10] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[10]);
	c3->cd(3); 	GetAsymmetry("110_120"); 	pA[11] = pAsym/pol; dpA[11] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[11]);
	c3->cd(4); 	GetAsymmetry("120_130"); 	pA[12] = pAsym/pol; dpA[12] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[12]);
	c3->cd(5); 	GetAsymmetry("130_140"); 	pA[13] = pAsym/pol; dpA[13] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[13]);
	c3->cd(6);  GetAsymmetry("140_150"); 	pA[14] = pAsym/pol; dpA[14] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[14]);
	c3->cd(7); 	GetAsymmetry("150_160"); 	pA[15] = pAsym/pol; dpA[15] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[15]);
	c3->cd(8); 	GetAsymmetry("160_170"); 	pA[16] = pAsym/pol; dpA[16] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[16]);
	c3->cd(9); 	GetAsymmetry("170_180"); 	pA[17] = pAsym/pol; dpA[17] = TMath::Abs(((((d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[17]);
	outFile.cd();
	c3->Write();
	
	
	c4 = new TCanvas("pi0 Beam Asymmetry (Sigma) result","pi0 Beam Asymmetry (Sigma) result");
	
	TGraphErrors *results = new TGraphErrors(nbins,th,pA,dth,dpA);
	Char_t* title = Form("#pi^{0} Beam Asymmetry (E_{#gamma} = %d #pm %d MeV)", E_gamma, dE_gamma); 
	results->SetTitle(title);
	results->GetXaxis()->SetTitle("#theta #pi^{0} (CM frame)");
	results->SetMarkerColor(4);
	results->SetMarkerStyle(21);
	results->Draw("AP");
	
	TGraph *MAID = new TGraph(nMAID_bins,MAID_th,MAID_pi0_275);
	MAID->SetLineColor(kRed);
	MAID->SetLineWidth(4);
	MAID->Draw("L");
	
	// draw the legend
	TLegend *legend=new TLegend(0.65,0.7,0.88,0.85);
	legend->SetTextFont(72);
	legend->SetTextSize(0.03);
	legend->AddEntry(results,"#Sigma (Dec. 2012)","pl");
	legend->AddEntry(MAID,"MAID","l");
	legend->Draw();	
	
	c4->Update();
	
	outFile.cd();
	c4->Write();
		
}


void GetAsymmetry(Char_t* hist_suffix = "")
{
	TH1D* para;
	TH1D* perp;
	
	// Form histogram name
	Char_t* hist_name;
	if (strcmp(hist_suffix, "") == 0)  hist_name = "phi_subtracted";
	else hist_name = Form("phi_subtracted_%s",hist_suffix);

	para = (TH1D*) fpara->Get(hist_name);
	perp = (TH1D*) fperp->Get(hist_name);
	perp->Scale(scale);

	TH1D* asym;
	asym = (TH1D*) perp->GetAsymmetry(para);
	asym->Draw();
	asym->SetStats(0);
	asym->GetXaxis()->SetTitle("#phi #pi^{0} (CM frame)");
	asym->GetYaxis()->SetRangeUser(-0.35,0.35);	
	
	// if comparing over all theta, let offset be free parameter
	if (strcmp(hist_suffix, "") == 0)
	{	
		TF1 *f1 = new TF1( "f1", "[2] + [0]*cos((2*x*0.01745) + [1])", -180, 180);
		asym->Fit( "f1", "REMQ");
		
		pAsym 	= f1->GetParameter(0);
		d_pAsym = f1->GetParError(0);
		offset	= f1->GetParameter(1);
		
		Double_t scale_set = f1->GetParameter(2);
		cout << scale_set << endl;
		
		Char_t* title = Form("#splitline{#pi^{0} Beam Asymmetry (E_{#gamma} = %d #pm %d MeV)}{   #theta(0_180)_{CM}     p_{#gamma}#Sigma = %4.3f #pm %4.3f}", E_gamma, dE_gamma, pAsym, d_pAsym ); 

	}
	else
	{
		Char_t* fit_function = Form("[0]*cos(2*x*0.01745 + %f)",offset);		
		TF1 *f1 = new TF1( "f1", fit_function, -180, 180);
		asym->Fit( "f1", "REMQ");
		
		pAsym 	= f1->GetParameter(0);
		d_pAsym = f1->GetParError(0);
		
		Char_t* title = Form("#splitline{#pi^{0} Beam Asymmetry (E_{#gamma} = %d #pm %d MeV)}{   #theta(%s)_{CM}     p_{#gamma}#Sigma = %4.3f #pm %4.3f}", E_gamma, dE_gamma, hist_suffix, pAsym, d_pAsym ); 		
	}

	asym->SetTitle(title);

	f1->Draw("same");

	c = new TCanvas("pi0 Beam Asymmetry (Sigma) result","pi0 Beam Asymmetry (Sigma) result");	
	c->Divide(3,1);
	c->cd(1);	para->Draw();	para->SetStats(0);	para->GetXaxis()->SetTitle("PARA #phi distribution"); 		para->SetTitle("PARA"); para->GetYaxis()->SetRangeUser(30000,75000);
	c->cd(2);	perp->Draw();	perp->SetStats(0);	perp->GetXaxis()->SetTitle("PERP #phi distribution");		perp->SetTitle("PERP");	perp->GetYaxis()->SetRangeUser(30000,75000);
	c->cd(3);	asym->Draw();	asym->SetStats(0);	asym->GetXaxis()->SetTitle("(PERP - PARA)/(PERP + PARA)");
	
}

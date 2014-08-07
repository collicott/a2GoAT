#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

 TFile outFile("August_Compton_results.root", "recreate");

TFile *fpara = new TFile("/home/cristina/GoATFiles/Old-GoAT-Amor/ComptonHist_Compton_786.root");
TFile *fperp = new TFile("/home/cristina/GoATFiles/Old-GoAT-Amor/ComptonHist_Compton_783.root");
TFile *fsimcomp = new TFile("/home/cristina/a2GoAT/results/Sim_Compton_AnalysedAsCompton.root");
TFile *fsimpi0  = new TFile("/home/cristina/a2GoAT/results/Sim_Pi0_AnalysedAsCompton.root");
double scale = 2.085;

// Determine fitting offset from pi0 production fits
double offset = -1.52355;

int E_gamma = 280;
int dE_gamma = 10;
double pol = 0.485;
double d_pol = 0.04;
double pvr = -0.075;

// Compton results disp
int nDISP_bins = 37;
Double_t DISP_th[37]  = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180};
Double_t DISP_Comp_280[37] = {0,0.0016,0.0063,0.0142,0.0254,0.0399,0.0574,0.0778,0.1002,0.1238,0.1472,0.1689,0.1875,0.2016,0.2103,0.2131,0.2102,0.2023,0.1903,0.1754,0.1586,0.141,0.1232,0.106,0.0897,0.0747,0.061,0.0488,0.0381,0.0288,0.021,0.0144,0.0092,0.0051,0.0023,0.0006,0};

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
	TH1D* simcomp;
	TH1D* simpi0;
	TH1D* sim;
	
	// Gather real data
	para = (TH1D*) fpara->Get("MM_subtracted_compton");
	perp = (TH1D*) fperp->Get("MM_subtracted_compton");
	perp->Scale(scale);	

	// Gather simulation and combine background
	simcomp = (TH1D*) fsimcomp->Get("MM_subtracted_compton");
	simpi0  = (TH1D*) fsimpi0->Get("MM_subtracted_compton");
	sim = (TH1D*) simcomp->Clone("sim");
	sim->Add(simpi0,1.12);
	
	// Determine scaling factor
	Double_t para_910_950 = para->Integral(910,950);
	Double_t perp_910_950 = perp->Integral(910,950);
	Double_t sim_910_950  = sim->Integral(910,950);
	double scaleMC = (0.5)*((para_910_950 + perp_910_950)/sim_910_950);
	sim->Scale(scaleMC);

	// Display Missing Mass comparison
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
	
	para->GetXaxis()->SetRange(850,1100);
	perp->GetXaxis()->SetRange(850,1100);
	sim->GetXaxis()->SetRange(850,1100);
	
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

	c1 = new TCanvas("Compton Beam Asymmetry (p*Sigma) over all theta","Compton Beam Asymmetry (p*Sigma) over all theta");
	c1->cd();
	GetAsymmetry();
	outFile.cd();
	c1->Write();
	
	c2 = new TCanvas("Compton Beam Asymmetry (p*Sigma), 20 deg. theta bins","Compton Beam Asymmetry (p*Sigma), 20 deg. theta bins");
	c2->Divide(3,1);
	
	// Fill asymmetry histograms, if fit works, store in a list
	Int_t nbins = 0;
	Double_t  th[3]; Double_t dth[3];
	Double_t  pA[3]; Double_t dpA[3];
	
	c2->cd(1); 	GetAsymmetry("70_90"); 
	if((pAsym != 0) && (d_pAsym != 0)) 
	{ 
		th[nbins] = 80;
		dth[nbins] = 10;
		pA[nbins] = pAsym/pol; 
		dpA[nbins] = TMath::Abs(((((0.4*d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[nbins]);
		nbins++; 
	}
		
	c2->cd(2); 	GetAsymmetry("90_110"); 
	if((pAsym != 0) && (d_pAsym != 0)) 
	{ 
		th[nbins] = 100;
		dth[nbins] = 10;
		pA[nbins] = pAsym/pol; 
		dpA[nbins] = TMath::Abs(((((0.4*d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[nbins]);
		nbins++; 
	}	
	
	c2->cd(3); 	GetAsymmetry("135_155"); 
	if((pAsym != 0) && (d_pAsym != 0)) 
	{ 
		th[nbins] = 145;
		dth[nbins] = 10;
		pA[nbins] = pAsym/pol; 
		dpA[nbins] = TMath::Abs(((((0.4*d_pAsym/pAsym)**2) + ((d_pol/pol)**2))**(0.5))*pA[nbins]);
		nbins++; 
	}	
	
	outFile.cd();
	c2->Write();
	
	c3 = new TCanvas("Compton Beam Asymmetry (Sigma) result ","Compton Beam Asymmetry (Sigma) result");
	Char_t* title = Form("Compton scattering #Sigma_{3} Asymmetry (E_{#gamma} = %d #pm %d MeV)", E_gamma, dE_gamma); 
	
	TGraph *DISP = new TGraph(nDISP_bins,DISP_th,DISP_Comp_280);
	DISP->SetTitle(title);
	DISP->SetLineColor(kRed);
	DISP->SetLineWidth(4);
	DISP->Draw("AL");
	DISP->GetYaxis()->SetRangeUser(-0.15,0.4);
	DISP->GetXaxis()->SetRangeUser(0,180);
	DISP->GetXaxis()->SetTitle("#theta_{#gamma} (LAB)");	
		
	TGraphErrors *results = new TGraphErrors(nbins,th,pA,dth,dpA);
	results->SetTitle(title);
	results->SetMarkerColor(4);
	results->SetMarkerStyle(21);
	results->Draw("P");
	
	// draw the legend
	TLegend *legend=new TLegend(0.60,0.7,0.88,0.85);
	legend->SetTextFont(72);
	legend->SetTextSize(0.03);
	legend->AddEntry(results,"#Sigma (Dec. 2012)","pl");
	legend->AddEntry(DISP,"#splitline{Dispersion relations}{      (Pasquini)}","pl");
	legend->Draw();	
	
	c3->Update();
	outFile.cd();
	c3->Write();	
	
}


void GetAsymmetry(Char_t* hist_suffix = "")
{
	TH1D* para_p; TH1D* para_r; TH1D* para;
	TH1D* perp_p; TH1D* perp_r; TH1D* perp;

	// Form histogram name
	Char_t* hist_name;
	if (strcmp(hist_suffix, "") == 0)
	{
		Char_t* hist_p = "phi_prompt";
		Char_t* hist_r = "phi_random";
	}
	else
	{
		Char_t* hist_p = Form("phi_prompt_%s",hist_suffix);
		Char_t* hist_r = Form("phi_random_%s",hist_suffix);
	}
	
	para_p = (TH1D*) fpara->Get(hist_p);
	para_r = (TH1D*) fpara->Get(hist_r);	
	perp_p = (TH1D*) fperp->Get(hist_p);
	perp_r = (TH1D*) fperp->Get(hist_r);	
	
	// Perform random subtraction
	para = (TH1D*) para_p->Clone("para");
	para->Add(para_r,pvr);

	perp = (TH1D*) perp_p->Clone("perp");
	perp->Add(perp_r,pvr);
	
	perp->Scale(scale);

	TH1D* asym;
	asym = (TH1D*) perp->GetAsymmetry(para);
	asym->Draw();
	asym->SetStats(0);
	asym->GetXaxis()->SetTitle("#theta_{#gamma} (LAB)");
	asym->GetYaxis()->SetRangeUser(-0.5,0.5);	

	Char_t* fit_function = Form("[0]*cos(2*x*0.01745 + %f)",offset);
	TF1 *f1 = new TF1( "f1", fit_function, -180, 180);
	asym->Fit( "f1", "REMQ");
	
	pAsym 	= f1->GetParameter(0);
	d_pAsym = f1->GetParError(0);
	
	cout << hist_suffix << "  " << f1->GetParameter(1) << endl;
	
	// Set appropriate title, output fit results
	Char_t* title;
	if (strcmp(hist_suffix, "") == 0)
	{	
		title = Form("#splitline{Compton Beam Asymmetry (E_{#gamma} = %d #pm %d MeV)}{   #theta(0_180)_{CM}     p_{#gamma}#Sigma = %4.3f #pm %4.3f}", E_gamma, dE_gamma, pAsym, d_pAsym ); 
	}
	else
	{
		title = Form("#splitline{Compton Beam Asymmetry (E_{#gamma} = %d #pm %d MeV)}{   #theta(%s)_{CM}     p_{#gamma}#Sigma = %4.3f #pm %4.3f}", E_gamma, dE_gamma, hist_suffix, pAsym, d_pAsym ); 		
	}	
	asym->SetTitle(title);

	f1->Draw("same");

	c = new TCanvas("Compton Beam Asymmetry (Sigma) result","pi0 Beam Asymmetry (Sigma) result");	
	c->Divide(3,1);
	c->cd(1);	para->Draw();	para->SetStats(0);	para->GetXaxis()->SetTitle("PARA #phi distribution"); 		para->SetTitle("PARA"); //para->GetYaxis()->SetRangeUser(30000,75000);
	c->cd(2);	perp->Draw();	perp->SetStats(0);	perp->GetXaxis()->SetTitle("PERP #phi distribution");		perp->SetTitle("PERP");	//perp->GetYaxis()->SetRangeUser(30000,75000);
	c->cd(3);	asym->Draw();	asym->SetStats(0);	asym->GetXaxis()->SetTitle("(PERP - PARA)/(PERP + PARA)");

}

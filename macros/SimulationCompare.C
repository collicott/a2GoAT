#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"
#include "TLegend.h"

void Compare(double scale = 2.0) 
{
	TH1D* real;
	TH1D* pi0;

	TFile *freal = new TFile("Pi0All.root");
	real = (TH1D*) freal->Get("MM_subtracted_pi0");

	TFile *fpi0 = new TFile("Pi0HistMC_Pi0_g4_out_0.root");
	pi0  = (TH1D*) fpi0->Get("MM_subtracted_pi0");

	c1 = new TCanvas("MM Distribution","MM Distribution");

	real->SetLineColor(kBlue);
	pi0->SetLineColor(kRed);

	pi0->Scale(0.82);

	pi0->GetXaxis()->SetRange(850,1050);
	real->GetXaxis()->SetRange(850,1050);
	real->GetXaxis()->SetTitle("Missing Mass (MeV)");
	pi0->SetStats(0);
	real->SetStats(0);

	pi0->SetTitle("");
	real->SetTitle("#pi^{0} Missing Mass (Real and Simulated data)");

	real->Draw();
	pi0->Draw("same");


   // draw the legend
   TLegend *legend=new TLegend(0.55,0.6,0.88,0.85);
   legend->SetTextFont(72);
   legend->SetTextSize(0.03);
   legend->AddEntry(real,"Real data (Dec. 2012)","lpe");
   legend->AddEntry(pi0,"Simulated data (AcquMC)","lpe");
   legend->Draw();	
}

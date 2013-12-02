#ifndef __CINT__

#include "TCanvas.h"
#include "TChain.h"
#include "TF1.h"
#include "TGraph.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "GParticleReconstruction.h"

#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[])
{
  GParticleReconstruction* gP = new GParticleReconstruction;
  char* filename; char* filename2;

 printf("%s\n",argv[1]);
 
  if (strcmp(argv[1],"Patrik") == 0)
  {
	filename = Form("/media/Elements/daten/PhysTree_CB_41900.root");
	filename2 = Form("/media/Elements/daten/out_PhysTree_CB_41900.root");
  }
  else if (strcmp(argv[1],"Cristina") == 0)
 {
	filename = Form("/home/cristina/RootTree_Compton_354.root");
	filename2 = Form("/home/cristina/out_RootTree_Compton_354.root");
  }
  else
  {
	printf("Who are you?\n");
	return 0;
  }

  gP->Init(filename, filename2);

  printf("Mehhh\n");
  return 0;
}


#endif

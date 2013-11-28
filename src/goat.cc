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
  GParticleReconstruction* gTree = new GParticleReconstruction;
  //GTreeManager* gTree2 = new GTreeManager;

  char* filename = Form("/media/Elements/daten/PhysTree_CB_41900.root");
  char* filename2 = Form("/media/Elements/daten/out_PhysTree_CB_41900.root");
  
  GTreeManager* test = (GTreeManager*)gTree;
  //test->Analyse(filename, filename2, 0, 500);
  test->Analyse(filename, filename2);

  printf("Mehhh\n");
  return 0;
}


#endif

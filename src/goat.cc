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
#include "GTreeManager.h"

#include <iostream>
#include <fstream>
using namespace std;

class TreeTest : public GTreeManager
{
	public:
TreeTest();
void Reconstruct();
};


TreeTest::TreeTest() : GTreeManager()
{
}


void TreeTest::Reconstruct()
{
    printf("I'm in yo goat file\n");
}

int main(int argc, char *argv[])
{
  TreeTest* gTree = new TreeTest();
  //GInputTreeManager* ggg = new GInputTreeManager();

  char* filename = Form("/home/cristina/RootTree_Compton_354.root");
  //gTree->Analysis(filename);
  
  GTreeManager* test = (GTreeManager*)gTree;
  test->Analysis(filename);

  printf("Mehhh\n");
  return 0;
}


#endif

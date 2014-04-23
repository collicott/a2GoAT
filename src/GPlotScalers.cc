#include "GPlotScalers.h"


using namespace std;


GPlotScalers::GPlotScalers()
{

}

GPlotScalers::~GPlotScalers()
{

}

void  GPlotScalers::ProcessEvent()
{
    static Bool_t   start = kTRUE;
    if(start)
    {
        start   = kFALSE;
        printf("skip first one\n");
        return;
    }
    //printf("%d\n", l);
    //l++;
    //if(scalerMain->GetBinContent(2)<0)
    //    return;
    //printf("\n");
    for(Int_t i=0; i<12; i++)
    {
        //printf("%lf\n", scalerMain->GetBinContent(i+1));
        //printf("%lf\n", Double_t(scalers->GetScaler(i)));
        scalerMain->SetBinContent(i+1, Double_t(scalers->GetScaler(i)) + scalerMain->GetBinContent(i+1));
        //printf("%lf\n", scalerMain->GetBinContent(i+1));
    }
    for(Int_t i=0; i<48; i++)
    {
        scalerEPT->SetBinContent(i+1, Double_t(scalers->GetScaler(i+140)) + scalerEPT->GetBinContent(i+1));
    }
}

Bool_t  GPlotScalers::Process(const char* input_filename, const char* output_filename)
{
    if(!Open(input_filename))    return kFALSE;

    if(!OpenScalers())    return kFALSE;

	if(!Create(output_filename))    return kFALSE;
	
	/*file_out->cd();
    gDirectory->mkdir("prompt");
    file_out->cd();
    gDirectory->mkdir("rand");*/
	file_out->cd();
    scalerMain	= new TH1D("scalerMain", "Main Scalers", 12, 0, 12); file_out->cd();
    scalerEPT	= new TH1D("scalerEPT", "EPT Scalers", 48, 0, 48); file_out->cd();
    
    TraverseEntries(0, scalers->GetNEntries()+1);

    file_out->cd();
    scalerMain->Write();
    scalerEPT->Write();

    return kTRUE;
}


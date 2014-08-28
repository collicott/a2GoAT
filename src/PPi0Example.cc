#include "PPi0Example.h"

PPi0Example::PPi0Example()
{ 
    GHistBGSub::InitCuts(-20, 15, -100, -40);
    GHistBGSub::AddRandCut(35, 95);
    
  	SetTarget(938); 
        
    time 	= new GH1("time", 	"time", 	1400, -700, 700);
    time_cut 	= new GH1("time_cut", 	"time_cut", 	1400, -700, 700);

    time_2g 	= new GH1("time_2g",	"time_2g", 	1400, -700, 700);
    time_2g_cut = new GH1("time_2g_cut","time_2g_cut", 	1400, -700, 700);

    IM 		= new GH1("IM", 	"IM", 		400,   0, 400);
    IM_2g 	= new GH1("IM_2g", 	"IM_2g", 	400,   0, 400);
  
    MM		= new GH1("MM", 	"MM", 	 	400,   800, 1200);     
    MM_2g	= new GH1("MM_2g", 	"MM_2g", 	400,   800, 1200); 
}

PPi0Example::~PPi0Example()
{
}

Bool_t	PPi0Example::Start()
{
    if(!IsGoATFile())
    {
        cout << "ERROR: Input File is not a GoAT file." << endl;
        return kFALSE;
    }
    SetAsPhysicsFile();

    TraverseValidEvents();

	return kTRUE;
}

void	PPi0Example::ProcessEvent()
{
	// fill time diff (tagger - pi0), all pi0
	FillTime(*pi0,time);
	FillTimeCut(*pi0,time_cut);
	
	// fill missing mass, all pi0
	FillMissingMass(*pi0,MM);	
	
	// fill invariant mass, all pi0
	FillMass(*pi0,IM);
		
	// Some neutral decays
    for (Int_t i = 0; i < pi0->GetNParticles(); i++)
	{		
        // Fill MM for 2 photon decay
        if ((pi0->GetNSubParticles(i) == 2) & (pi0->GetNSubPhotons(i) == 2))
        {
		// fill time diff (tagger - pi0), this pi0
		FillTime(*pi0,i,time_2g);
		FillTimeCut(*pi0,i,time_2g_cut);
			
		// fill missing mass, this pi0
            	FillMissingMass(*pi0,i,MM_2g);
            
		// fill invariant mass, this pi0
        	FillMass(*pi0,i,IM_2g);
        }

	}
	
}

void	PPi0Example::ProcessScalerRead()
{

    //time.ScalerReadCorrection(5);
}

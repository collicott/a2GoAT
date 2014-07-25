#include "GH1Example.h"



GH1Example::GH1Example()    :
    test("test", "test", 1000, -500, 500)
{ 
    GHistBGSub::InitCuts(-20, 15, -100, -40);
    GHistBGSub::AddRandCut(35, 95);
}

GH1Example::~GH1Example()
{

}

Bool_t	GH1Example::Start()
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

void	GH1Example::ProcessEvent()
{
    test.Fill(pi0->Particle(0).Px());
}

void	GH1Example::ProcessScalerRead()
{
    test.ScalerReadCorrection(5);
}

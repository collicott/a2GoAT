#include "GH1Example.h"



GH1Example::GH1Example()    :
    test("test", "test", 1000, -500, 500)
{ 
    GHistTaggerBinning::InitTaggerBinning(5,10);
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
    if(eta->GetNParticles()>0)
        test.Fill(eta->Particle(0).Px(), *tagger, kTRUE);
}

void	GH1Example::ProcessScalerRead()
{
    //test.ScalerReadCorrection(5);
}

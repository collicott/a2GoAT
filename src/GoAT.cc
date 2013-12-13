#ifndef __CINT__

#include "GoAT.h"

int main(int argc, char *argv[])
{
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
	else if (strcmp(argv[1],"Collicot") == 0)
	{
        filename = Form("/home/collicot/RootTree_Compton_354.root");
        filename2 = Form("/home/collicot/out_RootTree_Compton_354.root");
	}	
	else
	{
        printf("Who are you?\n");
        return 0;
	}

	GoAT* goat = new GoAT;

	goat->Init(filename,filename2);
	goat->Analyse();
	return 0;
}


GoAT::GoAT() :
				file_in(0),
				file_out(0)
{ 
}

GoAT::~GoAT()
{
}

Bool_t	GoAT::Init(const char* file_in, const char* file_out)
{	
	
	if(!OpenInputFile(file_in))		return kFALSE;	
	if(!OpenOutputFile(file_out))	return kFALSE;

	if(!OpenTreeRawEvent())			return kFALSE;
	if(!OpenTreeTagger())			return kFALSE;
	if(!OpenTreeTrigger())			return kFALSE;

	if(!FindValidEvents())			return kFALSE;

	// Read Which reconstruction steps are desired perform post init
	Bool_t UseParticleReconstruction = kTRUE;
	GParticleReconstruction::PostInit();

	printf("Mehhh - Initialisation complete - Mehhh\n");
  
	return kTRUE;
}

void	GoAT::Analyse()
{
	TraverseInputEntries();
	printf("nPi0 == %d  nEta == %d  nEtaP == %d \n", 
			GetNPi0(),	GetNEta(),	GetNEtaP());
			
	CloseOutputFile();
}

void	GoAT::Reconstruct()
{
	if(GetActualEvent() % 10000 == 0) printf("Event: %d\n",GetActualEvent());

	GParticleReconstruction::Reconstruct();
	
	if(Sort()) FillEvent();
}

Bool_t 	GoAT::Write()
{
	return kTRUE;
}

Bool_t GoAT::Sort()
{
	
	// Check conditions
	if(GP_GetNParticles() != 1) return kFALSE;

	return kTRUE;

}


#endif

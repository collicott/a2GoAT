#include "GoAT.h"


GoAT::GoAT() :
    UseParticleReconstruction(0)
{ 
}

GoAT::~GoAT()
{
}

Bool_t	GoAT::Init()
{
    cout << endl << "Initialising GoAT analysis..." << endl << endl;
		
    std::string config = ReadConfig("Period-Macro");
	if( sscanf(config.c_str(),"%d\n", &period) == 1 ) UsePeriodMacro = 1;

	cout << "==========================================================" << endl;	
	cout << "Setting up Data Checks:" << endl;	
	cout << "==========================================================" << endl;	
    if(!GDataChecks::Init())
	{
		cout << "GDataChecks Init failed!" << endl; 
		return kFALSE;
	}

	cout << "==========================================================" << endl;	
	cout << "Setting up sorting criteria:" << endl;	
	cout << "==========================================================" << endl;	
    if(!GSort::Init())
	{
		cout << "GSort Init failed!" << endl; 
		return kFALSE;
	}
	
	cout << "==========================================================" << endl;		
	cout << "Setting up analysis classes:" << endl;	
	cout << "==========================================================" << endl;	
    config = ReadConfig("DO-PARTICLE-RECONSTRUCTION");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        int buffer=0;
        sscanf( config.c_str(), "%d\n", &buffer);
        UseParticleReconstruction = (buffer==1);
    }

	if(UseParticleReconstruction) 
	{
        if(!GParticleReconstruction::Init())
		{
			cout << "GParticleReconstruction Init failed!" << endl; 
			return kFALSE;
		}
    }

    config = ReadConfig("DO-MESON-RECONSTRUCTION");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        int buffer=0;
        sscanf( config.c_str(), "%d\n", &buffer);
        UseMesonReconstruction = (buffer==1);
    }

    if(UseMesonReconstruction)
    {
        if(!GMesonReconstruction::Init())
        {
            cout << "GParticleReconstruction Init failed!" << endl;
            return kFALSE;
        }
    }

	cout << endl;	

	cout << "Initialisation complete." << endl;
	cout << "==========================================================" << endl << endl;
  
	return kTRUE;
}

void	GoAT::ProcessEvent()
{
    if(UsePeriodMacro == 1)
    {
        if(GetEventNumber() % period == 0)
            cout << "Event: " << GetEventNumber() << "  Events Accepted: " << nEvents_written << endl;
    }

    if(SortAnalyseEvent())
    {
        if(UseParticleReconstruction)
        {
            if(UseMesonReconstruction)
            {
                if(!GParticleReconstruction::ProcessEventWithoutFilling())  return;
                if(!GMesonReconstruction::ProcessEventWithoutFilling())  return;
                if(!SortFillEvent())    return;
                electrons->Fill();
                protons->Fill();
                neutrons->Fill();
                pi0->Fill();
                eta->Fill();
                etap->Fill();
            }
            else
            {
                if(!GParticleReconstruction::ProcessEventWithoutFilling())  return;
                if(!SortFillEvent())    return;
                electrons->Fill();
                protons->Fill();
                neutrons->Fill();
            }
        }
        else if(UseMesonReconstruction)
        {
            GMesonReconstruction::ProcessEventWithoutFilling();
            if(!SortFillEvent())    return;
            pi0->Fill();
            eta->Fill();
            etap->Fill();
        }
        eventParameters->SetNReconstructed(GetNReconstructed());
        eventParameters->Fill();
		rootinos->Fill();
        photons->Fill();
        chargedPi->Fill();
        FillReadList();
        nEvents_written++;
    }
}

Bool_t	GoAT::Start()
{
    if(UseParticleReconstruction)
    {
        if(UseMesonReconstruction)
        {
			rootinos->CloseForInput();
            photons->CloseForInput();
            electrons->CloseForInput();
            chargedPi->CloseForInput();
            protons->CloseForInput();
            neutrons->CloseForInput();
            pi0->CloseForInput();
            eta->CloseForInput();
            etap->CloseForInput();
        }
        else
        {
			rootinos->CloseForInput();
            photons->CloseForInput();
            electrons->CloseForInput();
            chargedPi->CloseForInput();
            protons->CloseForInput();
            neutrons->CloseForInput();
        }
    }
    else if(UseMesonReconstruction)
    {
        pi0->CloseForInput();
        eta->CloseForInput();
        etap->CloseForInput();
    }

    if(!TraverseValidEvents())		return kFALSE;

    return kTRUE;
}

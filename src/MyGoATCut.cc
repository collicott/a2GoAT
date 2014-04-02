#ifndef __CINT__


#include "MyGoAT.h"
#include "GCut.h"

using namespace std;





void    PrintHelp()
{
    cout << "particle:  particle reconstruction" << endl;

    cout << endl;
    cout << "example:" << endl;
    cout << "MyGoAT particle <inputFile> <outputFile>" << endl;
}




void* start(void* arguments)
{	
    Arguments*   arg    = 0;
    arg = (Arguments*) arguments;

	clock_t start, end;
	start = clock();

    GTreeManager* tree;

    if(strcmp(arg->type, "raw") == 0 || strcmp(arg->type, "Raw") == 0 || strcmp(arg->type, "RAW") == 0 || strcmp(arg->type, "rawparticle") == 0 || strcmp(arg->type, "rawParticle") == 0 || strcmp(arg->type, "RawParticle") == 0)
    {
        GRawCut*   help    = new GRawCut();

        if(arg->nValues!=2)
        {
            cout << "To many or few Arguments given." << endl;
            PrintHelp();
            return 0;
        }
        cout << "Set Raw Photon number to " << arg->value[0] << " and Raw Proton number to " << arg->value[1] << "." << endl;
        help->SetNPhoton(arg->value[0]);
        help->SetNProton(arg->value[1]);

        tree    = help;
    }
    else if(strcmp(arg->type, "particle") == 0 || strcmp(arg->type, "Particle") == 0 || strcmp(arg->type, "PARTICLE") == 0)
    {
        GCut*   help    = new GCut();

        if(arg->nValues!=5)
        {
            cout << "To many or few Arguments given." << endl;
            PrintHelp();
            return 0;
        }
        cout << "Set Photon number to " << arg->value[0] << "." << endl;
        cout << "Set Proton number to " << arg->value[1] << "." << endl;
        cout << "Set Pi0 number to " << arg->value[2] << "." << endl;
        cout << "Set Eta number to " << arg->value[3] << "." << endl;
        cout << "Set Etap number to " << arg->value[4] << "." << endl;
        help->SetNPhoton(arg->value[0]);
        help->SetNProton(arg->value[1]);
        help->SetNPi0(arg->value[2]);
        help->SetNEta(arg->value[3]);
        help->SetNEtap(arg->value[4]);

        tree    = help;
    }
    else if(strcmp(arg->type, "invMass") == 0 || strcmp(arg->type, "InvMass") == 0 || strcmp(arg->type, "IM") == 0 || strcmp(arg->type, "im") == 0 || strcmp(arg->type, "invariantmass") == 0 || strcmp(arg->type, "invariantMass") == 0)
    {
        GCut*   help    = new GCut();

        if(arg->nValues!=6)
        {
            cout << "To many or few Arguments given." << endl;
            PrintHelp();
            return 0;
        }
        cout << "Set Pi0 invariant mass cut from " << arg->value[0] << " to " << arg->value[1] << "." << endl;
        cout << "Set Eta invariant mass cut from " << arg->value[2] << " to " << arg->value[3] << "." << endl;
        cout << "Set Etap invariant mass cut from " << arg->value[4] << " to " << arg->value[5] << "." << endl;
        help->SetPi0InvMassCut(arg->value[0],arg->value[1]);
        help->SetEtaInvMassCut(arg->value[2],arg->value[3]);
        help->SetEtapInvMassCut(arg->value[4],arg->value[5]);

        tree    = help;
    }
    else if(strcmp(arg->type, "misMass") == 0 || strcmp(arg->type, "MisMass") == 0 || strcmp(arg->type, "MM") == 0 || strcmp(arg->type, "mm") == 0 || strcmp(arg->type, "missingmass") == 0 || strcmp(arg->type, "missingMass") == 0)
    {
        GCut*   help    = new GCut();

        if(arg->nValues!=2)
        {
            cout << "To many or few Arguments given." << endl;
            PrintHelp();
            return 0;
        }
        cout << "Set missing mass cut from " << arg->value[0] << " to " << arg->value[1] << "." << endl;
        help->SetMisMassCut(arg->value[0],arg->value[1]);

        tree    = help;
    }
    else
    {
        cout << "Reconstruction type " << arg->type <<" is unknown." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }


    tree->Process(arg->fileName_in, arg->fileName_out);

    delete  tree;

	end = clock();
	cout << "Time required for execution: "
	<< (double)(end-start)/CLOCKS_PER_SEC
	<< " seconds." << "\n\n";

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    gSystem->Load("libPhysics.so");
    gSystem->Load("libHist.so");

    // Associate 1nd terminal input with the input file ----------------
    if(argc < 2)
    {
        cout << "No reconstruction type given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }
    Char_t* type;
    if(argv[1]) type = argv[1];
    else
    {
        cout << "No reconstruction type given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }

    // Associate 2nd terminal input with the input file ----------------
    if(argc < 3)
    {
        cout << "No input file given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }
    Char_t* fileName_in;
    if(argv[2]) fileName_in = argv[2];
    else
    {
        cout << "No input file given." << endl;
        cout << "Check Arguments!" << endl;
        cout << endl;
        PrintHelp();
        return 0;
    }

    // Associate 3nd terminal input with the output file ----------------
        if(argc < 4)
        {
            cout << "No output file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        Char_t* fileName_out;
        if(argv[3]) fileName_out = argv[3];
        else
        {
            cout << "No output file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }

    TSystemFile* file_in   = new TSystemFile(fileName_in,".");
    TSystemFile* file_out  = new TSystemFile(fileName_out,".");
    if(file_in->IsZombie())
    {
        cout << "file or directory " << fileName_in << " is not existing." << endl;
        return 0;
    }
    if(file_in->IsDirectory())
    {
        if(!file_out->IsDirectory())
        {
            cout << "Output directory " << fileName_out << " is not existing." << endl;
            return 0;
        }
        delete file_in;
        delete file_out;

        if(argc < 7)
        {
            cout << "No prefix/suffix for file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        TString prefix_in;
        TString suffix;
        TString prefix_out;
        if(argv[4]) prefix_in = argv[4];
        else
        {
            cout << "No prefix for input file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        if(argv[5]) suffix = argv[5];
        else
        {
            cout << "No suffix for files given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }
        if(!suffix.EndsWith(".root"))
            suffix.Append(".root");
        if(argv[6]) prefix_out = argv[6];
        else
        {
            cout << "No prefix for output file given." << endl;
            cout << "Check Arguments!" << endl;
            cout << endl;
            PrintHelp();
            return 0;
        }

        TSystemDirectory    dir_in(fileName_in, ".");
        TSystemDirectory    dir_out(fileName_out, ".");

        TString currentInput;
        TString currentOutput;

        //TList*   files  = dir_in.GetListOfFiles();
        TIter   next(dir_in.GetListOfFiles());
        int     counter = 0;
        while(file_in = (TSystemFile*)next())
        {
            currentInput = file_in->GetName();
            if(!currentInput.BeginsWith(prefix_in))
                continue;
            if(!currentInput.EndsWith(suffix))
                continue;
            currentOutput   = currentInput(prefix_in.Length(), currentInput.Length() - prefix_in.Length() - suffix.Length());
            currentOutput.Prepend(prefix_out);
            currentOutput.Append(suffix);

            printf("process file %d\n", counter);
            counter++;

            pthread_t thread;
            Arguments   arguments;
            strcpy(arguments.type, type);
            strcpy(arguments.fileName_in, currentInput.Data());
            strcpy(arguments.fileName_out, currentOutput.Data());
            arguments.nValues   = 0;
            for(int i=7; i<argc; i++)
            {
                if(argv[i])
                {
                    sscanf(argv[i],"%lf", &arguments.value[i-7]);
                    arguments.nValues++;
                }
            }
            pthread_create( &thread, NULL, start, (void*)&arguments);
            pthread_join(thread,0);
        }
    }
    else
    {
        Arguments   arguments;
        strcpy(arguments.type, type);
        strcpy(arguments.fileName_in, fileName_in);
        strcpy(arguments.fileName_out, fileName_out);
        arguments.nValues   = 0;
        for(int i=4; i<argc; i++)
        {
            if(argv[i])
            {
                sscanf(argv[i],"%lf", &arguments.value[i-4]);
                arguments.nValues++;
            }
        }
        start((void*)&arguments);
    }

    return 0;
}

#endif

#include "GTreeManager.h"

#include <TROOT.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

using namespace std;


GTreeManager::GTreeManager()    :
    file_in(0),
    file_out(0),
    //minEntry(0),
    //nEntries(0),
    rawEvent(0),
    tagger(0),
    trigger(0), //Added by James
    scalers(0),
    eventFlags(0),
    photons(0),
    protons(0),
    pi0(0),
    eta(0),
    etap(0),
    fitData(0)
{
    etap = new GTreeMeson(TString("Etap"));
    eta = new GTreeMeson(TString("Eta"));
    pi0 = new GTreeMeson(TString("Pi0"));
    photons = new GTreeParticle(TString("Photons"));
    protons = new GTreeParticle(TString("Protons"));
    eventFlags = new GTreeEvent();
    rawEvent = new GTreeRawEvent();
    tagger = new GTreeTagger();
    trigger = new GTreeTrigger();
    scalers = new GTreeScaler();
    fitData = new GTreeFit();
}

GTreeManager::~GTreeManager()
{
    CloseFiles();
}

void    GTreeManager::CloseFiles()
{
    if(file_in)     delete file_in;
    if(file_out)    delete file_out;
}

Bool_t  GTreeManager::TraverseEntries(const UInt_t min, const UInt_t max)
{
    TObjArray   readList;

    if(etap)
    {
        if(etap->IsOpenForInput())
            readList.Add(etap);
    }
    if(eta)
    {
        if(eta->IsOpenForInput())
            readList.Add(eta);
    }
    if(pi0)
    {
        if(pi0->IsOpenForInput())
            readList.Add(pi0);
    }

    if(photons)
    {
        if(photons->IsOpenForInput())
            readList.Add(photons);
    }
    if(protons)
    {
        if(protons->IsOpenForInput())
            readList.Add(protons);
    }

    if(rawEvent)
    {
        if(rawEvent->IsOpenForInput())
            readList.Add(rawEvent);
    }
    if(tagger)
    {
        if(tagger->IsOpenForInput())
            readList.Add(tagger);
    }
    if(eventFlags)
    {
        if(eventFlags->IsOpenForInput())
            readList.Add(eventFlags);
    }
    if(trigger)
    {
        if(trigger->IsOpenForInput())
            readList.Add(trigger);
    }
    if(fitData)
    {
        if(fitData->IsOpenForInput())
            readList.Add(fitData);
    }

    for(int i=min; i<=max; i++)
    {
        for(int l=0; l<readList.GetEntriesFast(); l++)
            ((GTree*)readList[l])->GetEntryFast(i);

        ProcessEvent();
    }
}

Bool_t   GTreeManager::Create(const char* filename)
{
    if(file_out) delete file_out;
    file_out = TFile::Open(filename, "RECREATE");
    if(!file_out)
    {
        cout << "#ERROR: Can not create output file " << filename << "!" << endl;
        return kFALSE;
    }
    cout << "Created output file " << file_out->GetName() << "!" << file_out->GetTitle() << endl;
    return kTRUE;
}

Bool_t  GTreeManager::CreateMeson(GTreeMeson*& mesonTree, const TString& _Name)
{
    if(!file_out) return kFALSE;
    if(!mesonTree)   mesonTree = new GTreeMeson(_Name);
    return mesonTree->OpenForOutput(*file_out);
}

Bool_t  GTreeManager::CreateParticle(GTreeParticle*& particleTree, const TString& _Name)
{
    if(!file_out) return kFALSE;
    if(!particleTree)   particleTree = new GTreeParticle(_Name);
    return particleTree->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateEventFlags()
{
    if(!file_out) return kFALSE;
    if(!eventFlags)   eventFlags = new GTreeEvent();
    return eventFlags->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateRawEvent()
{
    if(!file_out) return kFALSE;
    if(!rawEvent)   rawEvent = new GTreeRawEvent();
    return rawEvent->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateTagger()
{
    if(!file_out) return kFALSE;
    if(!tagger)   tagger = new GTreeTagger();
    return tagger->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateTrigger()
{
    if(!file_out)return kFALSE;
    if(!trigger)  trigger = new GTreeTrigger(); //Added by James
    return trigger->OpenForOutput(*file_out);
}


Bool_t   GTreeManager::CreateScalers()
{
    if(!file_out) return kFALSE;
    if(!scalers)   scalers = new GTreeScaler();
    return scalers->OpenForOutput(*file_out);
}

Bool_t   GTreeManager::CreateFitData()
{
    if(!file_out) return kFALSE;
    if(!fitData)   fitData = new GTreeFit();
    return fitData->OpenForOutput(*file_out);
}


Bool_t   GTreeManager::Open(const char* filename)
{
    if(file_in) delete file_in;
    file_in = TFile::Open(filename);
    if(!file_in)
    {
        cout << "#ERROR: Can not open input file " << filename << "!" << endl;
        return kFALSE;
    }
    cout << "Opened input file " << file_in->GetName() << "!" << file_in->GetTitle() << endl;
    return kTRUE;
}

Bool_t   GTreeManager::OpenMeson(GTreeMeson*& mesonTree, const TString& _Name)
{
    if(!file_in) return kFALSE;
    if(!mesonTree)   mesonTree = new GTreeMeson(_Name);
    if(!mesonTree->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(rawEvent);
    return kTRUE;
}

Bool_t   GTreeManager::OpenParticle(GTreeParticle*& particleTree, const TString& _Name)
{
    if(!file_in) return kFALSE;
    if(!particleTree)   particleTree = new GTreeParticle(_Name);
    if(!particleTree->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(rawEvent);
    return kTRUE;
}

Bool_t   GTreeManager::OpenEventFlags()
{
    if(!file_in) return kFALSE;
    if(!eventFlags)   eventFlags = new GTreeEvent();
    if(!eventFlags->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(rawEvent);
    return kTRUE;
}

Bool_t   GTreeManager::OpenRawEvent()
{
    if(!file_in) return kFALSE;
    if(!rawEvent)   rawEvent = new GTreeRawEvent();
    if(!rawEvent->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(rawEvent);
    return kTRUE;
}

Bool_t   GTreeManager::OpenTagger()
{
    if(!file_in) return kFALSE;
    if(!tagger)   tagger = new GTreeTagger();
    if(!tagger->OpenForInput(*file_in))   return kFALSE;
    //return EntryChecking(tagger);
    return kTRUE;
}

Bool_t   GTreeManager::OpenTrigger()
{
    if(!file_in)return kFALSE;
    if(!trigger)  trigger = new GTreeTrigger();          //Added by James
    if(!trigger->OpenForInput(*file_in)) return kFALSE;
    return kTRUE;
}

Bool_t   GTreeManager::OpenScalers()
{
    if(!file_in) return kFALSE;
    if(!scalers)   scalers = new GTreeScaler();
    return scalers->OpenForInput(*file_in);
}

Bool_t   GTreeManager::OpenFitData()
{
    if(!file_in) return kFALSE;
    if(!fitData)   fitData = new GTreeFit();
    return fitData->OpenForInput(*file_in);
}


Bool_t  GTreeManager::ProcessFolder(const char* input_foldername, const char* output_foldername, const char* filePrefix, const char* fileSuffix, const char* outfilePrefix)
{
    //open folders
    TSystemDirectory    folder_in("input_folder", input_foldername);
    if(!folder_in.IsFolder())   return kFALSE;
    std::cout << "Input folder: " << folder_in.GetTitle() <<  std::endl;
    std::cout << "File input patter: " << TString(filePrefix).Append("<RunNumber>").Append(fileSuffix) <<  std::endl;
    TSystemDirectory    folder_out("output_folder", output_foldername);
    if(!folder_out.IsFolder())  return kFALSE;
    std::cout << "Output folder: " << folder_out.GetName() <<  std::endl;
    std::cout << "File output patter: " << TString(outfilePrefix).Append("<RunNumber>").Append(fileSuffix) <<  std::endl;

    //run over folder
    TList*  files   = folder_in.GetListOfFiles();
    if (files)
    {
        TSystemFile *file;
        TString fname_in;
        TString fname_out;
        TString number;
        TString prefix(filePrefix);
        TString suffix(fileSuffix);
        if(!suffix.EndsWith(".root"))
            suffix.Append(".root");
        TIter next(files);
        while ((file=(TSystemFile*)next()))
        {
            fname_in    = file->GetName();
            if (!file->IsDirectory() && fname_in.EndsWith(TString(fileSuffix)) && fname_in.BeginsWith(filePrefix))
            {
                number  = fname_in(prefix.Length(),fname_in.Length()-prefix.Length());
                number  = number(0,number.Length()-prefix.Length()+2);
                fname_out = outfilePrefix;
                fname_out.Append(number).Append(suffix);
                std::cout << "Analysing file " << fname_in << ". Output to file " << fname_out << std::endl;
                if(!Process(fname_in.Data(), fname_out.Data()))
                {
                    CloseFiles();
                    return kFALSE;
                }
            }
        }
        return kTRUE;
    }
    return kFALSE;
}


Bool_t  GTreeManager::Write()
{
    if(!file_out)   return kFALSE;

    if(pi0)         pi0->Write();
    if(eta)         eta->Write();
    if(etap)        etap->Write();
    if(photons)     photons->Write();
    if(protons)     protons->Write();
    if(eventFlags)  eventFlags->Write();
    if(rawEvent)    rawEvent->Write();
    if(tagger)      tagger->Write();
    if(trigger)     trigger->Write(); //Added by James
    if(scalers)     scalers->Write();
    if(fitData)     fitData->Write();

    return kTRUE;
}

Bool_t  GTreeManager::Write(const TNamed* object)
{
    if(!file_out)   return kFALSE;
    file_out->cd();
    object->Write();
    return kTRUE;
}


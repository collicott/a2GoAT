#include "GHist.h"



GHist::GHist(TDirectory* _Dir)  :
    dir(_Dir)
{
    dir->cd();
}

GHist::~GHist()
{
    if(prompt)  delete  prompt;
    if(rand[0])  delete  rand[0];
    if(rand[1])  delete  rand[1];
}

void    GHist::Add(const GHist* hist, const Double_t scale)
{
    prompt->Add(hist->prompt, scale);
    rand[0]->Add(hist->rand[0], scale);
    rand[1]->Add(hist->rand[1], scale);
}

void    GHist::Write(const Double_t RandPromptFactor)
{
    TDirectory*  promptDir   = 0;
    promptDir   = dir->GetDirectory("prompt");
    if(!promptDir)
    {
        printf("#ERROR GHistD::Write: Can not get Directory prompt in %s\n", dir->GetTitle());
    }
    promptDir->cd();
    if(prompt->GetEntries())
        prompt->Write();

    TDirectory*  randDir    = 0;
    randDir   = dir->GetDirectory("rand");
    if(!randDir)
    {
       printf("#ERROR GHistD::GHistD: Can not get Directory rand in %s\n", dir->GetTitle());
    }
    for(int i=0; i<2; i++)
    {
        randDir->cd();
        if(rand[i]->GetEntries())
            rand[i]->Write();
    }

    randAll->Add(rand[0], 1);
    randAll->Add(rand[1], 1);
    randDir->cd();
    randAll->Write();

    result->Add(prompt, 1);
    result->Add(randAll, -TMath::Abs(RandPromptFactor));
    dir->cd();
    result->Write();
}







GHistD::GHistD(TDirectory* _Dir, const TString& name, const TString& title, const Int_t nBins, const Double_t min, const Double_t max)    :
    GHist(_Dir)
{
    TDirectory*  promptDir   = 0;
    promptDir   = dir->GetDirectory("prompt");
    if(!promptDir)
    {
        dir->cd();
        gDirectory->mkdir("prompt");
        dir->cd();
        promptDir   = dir->GetDirectory("prompt");
        if(!promptDir)
        {
            printf("#ERROR GHistD::GHistD: Can not create Directory prompt in %s\n", dir->GetTitle());
        }
    }
    promptDir->cd();
    prompt  = new TH1D((TString(name).Prepend("prompt_")).Data(), (TString(title).Append(" (prompt)")).Data(), nBins, min, max);

    TDirectory*  randDir    = 0;
    randDir   = dir->GetDirectory("rand");
    if(!randDir)
    {
        dir->cd();
        gDirectory->mkdir("rand");
        dir->cd();
        randDir   = dir->GetDirectory("rand");
        if(!randDir)
        {
            printf("#ERROR GHistD::GHistD: Can not create Directory rand in %s\n", dir->GetTitle());
        }
    }

    randDir->cd();
    randAll = new TH1D((TString(name).Prepend(TString("randAll_"))).Data(), (TString(title).Append(TString("randAll_"))).Data(), nBins, min, max);

    for(int i=0; i<2; i++)
    {
        randDir->cd();
        rand[i]  = new TH1D((TString(name).Prepend(TString("rand").Append(TString::UItoa(i,10)).Append("_"))).Data(), (TString(title).Append(TString("rand").Append(TString::UItoa(i,10)).Append("_"))).Data(), nBins, min, max);
    }

    dir->cd();
    result  = new TH1D(TString(name).Data(), TString(title).Data(), nBins, min, max);
}

GHistD::~GHistD()
{
}








GHistI::GHistI(TDirectory* _Dir, const TString& name, const TString& title, const Int_t nBins, const Int_t min, const Int_t max)    :
    GHist(_Dir)
{
    TDirectory*  promptDir   = 0;
    promptDir   = dir->GetDirectory("prompt");
    if(!promptDir)
    {
        dir->cd();
        gDirectory->mkdir("prompt");
        dir->cd();
        promptDir   = dir->GetDirectory("prompt");
        if(!promptDir)
        {
            printf("#ERROR GHistI::GHistI: Can not create Directory prompt in %s", dir->GetTitle());
        }
    }
    promptDir->cd();
    prompt  = new TH1I((TString(name).Prepend("prompt")).Data(), (TString(title).Append(" (prompt)")).Data(), nBins, min, max);

    TDirectory*  randDir    = 0;
    randDir   = dir->GetDirectory("rand");
    if(!randDir)
    {
        dir->cd();
        gDirectory->mkdir("rand");
        dir->cd();
        randDir   = dir->GetDirectory("rand");
        if(!randDir)
        {
            printf("#ERROR GHistI::GHistI: Can not create Directory rand in %s", dir->GetTitle());
            return;
        }
    }

    randDir->cd();
    randAll = new TH1I((TString(name).Prepend(TString("randAll_"))).Data(), (TString(title).Append(TString("randAll_"))).Data(), nBins, min, max);

    for(int i=0; i<2; i++)
    {
        randDir->cd();
        rand[i]  = new TH1I((TString(name).Prepend(TString("rand").Append(TString::UItoa(i,10)).Append("_"))).Data(), (TString(title).Append(TString("rand").Append(TString::UItoa(i,10)).Append("_"))).Data(), nBins, min, max);
    }

    dir->cd();
    result  = new TH1I(TString(name).Data(), TString(title).Data(), nBins, min, max);
}

GHistI::~GHistI()
{
}

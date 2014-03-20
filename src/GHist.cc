#include "GHist.h"



GHist::GHist(TDirectory* _Dir)  :
    dir(_Dir)
{
    dir->cd();
    //Px  = new TH1D(name.Prepend("prompt").Data(), title.Append(" (prompt)").Data(), 4000, -2000, 2000);
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

void    GHist::Write()
{
    TDirectory*  promptDir   = 0;
    promptDir   = dir->GetDirectory("prompt");
    if(!promptDir)
    {
        printf("#ERROR GHistD::Write: Can not get Directory prompt in %s", dir->GetTitle());
    }
    promptDir->cd();
    if(prompt->GetEntries())
        prompt->Write();

    TDirectory*  randDir[2]   = {0, 0};
    for(int i=0; i<2; i++)
    {
        randDir[i]   = dir->GetDirectory("rand");
        if(randDir[i])
        {
           printf("#ERROR GHistD::GHistD: Can not get Directory rand%d in %s", i, dir->GetTitle());
        }
        randDir[i]->cd();
        if(rand[i]->GetEntries())
            rand[i]->Write();
    }
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
            printf("#ERROR GHistD::GHistD: Can not create Directory prompt in %s", dir->GetTitle());
        }
    }
    promptDir->cd();
    prompt  = new TH1D((TString(name).Prepend("prompt")).Data(), (TString(title).Append(" (prompt)")).Data(), nBins, min, max);

    TDirectory*  randDir[2]   = {0, 0};
    for(int i=0; i<2; i++)
    {
        randDir[i]   = dir->GetDirectory("rand");
        if(!randDir[i])
        {
            dir->cd();
            gDirectory->mkdir("rand");
            dir->cd();
            randDir[i]   = dir->GetDirectory("rand");
            if(!randDir[i])
            {
                printf("#ERROR GHistD::GHistD: Can not create Directory rand%d in %s", i, dir->GetTitle());
            }
        }
        randDir[i]->cd();
        rand[i]  = new TH1D((TString(name).Prepend(TString("rand").Append(TString::UItoa(i,10)))).Data(), (TString(title).Append(TString("rand").Append(TString::UItoa(i,10)))).Data(), nBins, min, max);
    }
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

    TDirectory*  randDir[2]   = {0, 0};
    for(int i=0; i<2; i++)
    {
        randDir[i]   = dir->GetDirectory("rand");
        if(!randDir[i])
        {
            dir->cd();
            gDirectory->mkdir("rand");
            dir->cd();
            randDir[i]   = dir->GetDirectory("rand");
            if(!randDir[i])
            {
                printf("#ERROR GHistI::GHistI: Can not create Directory rand%d in %s", i, dir->GetTitle());
            }
        }
        randDir[i]->cd();
        rand[i]  = new TH1I((TString(name).Prepend(TString("rand").Append(TString::UItoa(i,10)))).Data(), (TString(title).Append(TString("rand").Append(TString::UItoa(i,10)))).Data(), nBins, min, max);
    }
}

GHistI::~GHistI()
{
}

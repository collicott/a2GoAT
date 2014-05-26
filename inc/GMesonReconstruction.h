#ifndef __GMesonReconstruction_h__
#define __GMesonReconstruction_h__


#include "GTreeManager.h"


class  GMesonReconstruction  : public GTreeManager
{
private:
    Double_t    pi0Width;
    Double_t    etaWidth;
    Double_t    etapWidth;

    static  Int_t   perm6g[15][6];
    static  Int_t   perm10g[27][10];

    struct
    {
        TH1D*   invMassPi0;
        TH1D*   invMassEta;
        TH1D*   invMassEtap;
    }   h2g;
    struct
    {
        struct
        {
            TH1D*   invMassPi0a;
            TH1D*   invMassPi0b;
            TH1D*   invMassPi0c;
            TH1D*   invMassEta;
        }   h3pi0;
        struct
        {
            TH1D*   invMassPi0a;
            TH1D*   invMassPi0b;
            TH1D*   invMassEta;
            TH1D*   invMassEtap;
        }   hetap;
    }   h6g;

    void    Reconstruct2g();
    void    Reconstruct6g();
    void    Reconstruct10g();

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Process();

public:
    GMesonReconstruction();
    virtual ~GMesonReconstruction();

    static  Int_t   InputNeeded()   {return GTreeManager::TreeFlag_Photons;}
    static  Int_t   OutputNeeded()  {}

    void    SetPi0Width(const Double_t width)   {pi0Width = width;}
    void    SetEtaWidth(const Double_t width)   {etaWidth = width;}
    void    SetEtapWidth(const Double_t width)  {etapWidth = width;}
};





#endif

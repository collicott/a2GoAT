#ifndef __GMesonReconstruction_h__
#define __GMesonReconstruction_h__


#include "GTreeManager.h"

#define DEFAULT_PI0_IM_WIDTH 20.0
#define DEFAULT_ETA_IM_WIDTH 44.0
#define DEFAULT_ETAP_IM_WIDTH 60.0


class  GMesonReconstruction  : virtual public GTreeManager
{
private:
    Double_t	width_pi0;
    Double_t	width_eta;
    Double_t	width_etap;

    Int_t		ReconstructMesons;
    Double_t	meson_theta_min;
    Double_t	meson_theta_max;

    Bool_t  Init();

protected:

    virtual void    ProcessEvent();
    virtual Bool_t  Start();

public:
    GMesonReconstruction();
    virtual ~GMesonReconstruction();

    static  Int_t   InputNeeded()   {return GTreeManager::TreeFlag_Photons;}
    static  Int_t   OutputNeeded()  {}
            void    SetPi0Width(const Double_t width)   {width_pi0 = width;}
            void    SetEtaWidth(const Double_t width)   {width_eta = width;}
            void    SetEtapWidth(const Double_t width)  {width_etap = width;}
};





#endif

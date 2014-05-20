#ifndef __GTreeRawEvent_h__
#define __GTreeRawEvent_h__


#include <TLorentzVector.h>

#include "GTree.h"


#define GTreeRawEvent_MAX 256

class  GTreeRawEvent : public GTree
{
public:
    enum
    {
        APPARATUS_NONE  = 0,
        APPARATUS_CB    = 1,
        APPARATUS_TAPS  = 2
    };
private:
    Int_t		nParticles;
    Double_t	Ek[GTreeRawEvent_MAX];
    Double_t 	Theta[GTreeRawEvent_MAX];
    Double_t 	Phi[GTreeRawEvent_MAX];
    Double_t	time[GTreeRawEvent_MAX];
    UChar_t     clusterSize[GTreeRawEvent_MAX];
    UChar_t 	Apparatus[GTreeRawEvent_MAX];
    //Charged detector energies
    Double_t	d_E[GTreeRawEvent_MAX];
    Double_t	WC0_E[GTreeRawEvent_MAX];
    Double_t	WC1_E[GTreeRawEvent_MAX];
    //Wire Chamber vertex reconstruction
    Double_t 	WC_Vertex_X[GTreeRawEvent_MAX];
    Double_t 	WC_Vertex_Y[GTreeRawEvent_MAX];
    Double_t 	WC_Vertex_Z[GTreeRawEvent_MAX];

protected:
    virtual void    SetBranchAdresses();
    virtual void    SetBranches();

public:
    GTreeRawEvent(GTreeManager *Manager);
    virtual ~GTreeRawEvent();

    virtual void    Clear()     {nParticles = 0;}

    const	UChar_t*        GetApparatus()                      const	{return Apparatus;}
            UChar_t         GetApparatus(const Int_t index)     const	{return Apparatus[index];}
            UChar_t         GetClusterSize(const Int_t index)   const 	{return clusterSize[index];}
    const	Double_t*       Get_dE()                            const	{return d_E;}
            Double_t        Get_dE(const Int_t index)           const	{return d_E[index];}
    const	Double_t*       GetEk()                             const	{return Ek;}
            Double_t        GetEk(const Int_t index)            const	{return Ek[index];}
    inline  Int_t           GetNCB()                            const;
            Int_t           GetNParticles()                     const	{return nParticles;}
    inline  Int_t           GetNTAPS()                          const;
    const	Double_t*       GetPhi()                            const	{return Phi;}
            Double_t        GetPhi(const Int_t index)           const	{return Phi[index];}
            Double_t        GetPhiRad(const Int_t index)        const	{return Theta[index] * TMath::DegToRad();}
    const	Double_t*       GetTheta()                          const	{return Theta;}
            Double_t        GetTheta(const Int_t index)         const	{return Theta[index];}
            Double_t        GetThetaRad(const Int_t index)      const	{return Theta[index] * TMath::DegToRad();}
    const	Double_t*       GetTime()                           const	{return time;}
            Double_t        GetTime(const Int_t index)          const	{return time[index];}
    inline  TLorentzVector	GetVector(const Int_t index)        const;
    inline  TLorentzVector	GetVector(const Int_t index, const Double_t mass)   const;
    const	Double_t*       GetWC0_E()                          const	{return WC0_E;}
            Double_t        GetWC0_E(const Int_t index)         const	{return WC0_E[index];}
    const	Double_t*       GetWC1_E()                          const	{return WC1_E;}
            Double_t        GetWC1_E(const Int_t index)         const	{return WC1_E[index];}
    const	Double_t*       GetWC_Vertex_X()                    const	{return WC_Vertex_X;}
            Double_t        GetWC_Vertex_X(const Int_t index)	const	{return WC_Vertex_X[index];}
    const	Double_t*       GetWC_Vertex_Y()                    const	{return WC_Vertex_Y;}
            Double_t        GetWC_Vertex_Y(const Int_t index)	const	{return WC_Vertex_Y[index];}
    const	Double_t*       GetWC_Vertex_Z()                    const	{return WC_Vertex_Z;}
            Double_t        GetWC_Vertex_Z(const Int_t index)	const	{return WC_Vertex_Z[index];}
    virtual void            Print(const Bool_t All = kFALSE)    const;
};

TLorentzVector	GTreeRawEvent::GetVector(const Int_t index) const
{
    Double_t th = Theta[index] * TMath::DegToRad();
    Double_t ph = Phi[index]   * TMath::DegToRad();

    Double_t Px = Ek[index]* sin(th)*cos(ph);
    Double_t Py = Ek[index]* sin(th)*sin(ph);
    Double_t Pz = Ek[index]* cos(th);

    return TLorentzVector(Px, Py, Pz, Ek[index]);
}

TLorentzVector	GTreeRawEvent::GetVector(const Int_t index, const Double_t mass) const
{
    Double_t th = Theta[index] * TMath::DegToRad();
    Double_t ph = Phi[index]   * TMath::DegToRad();

    Double_t E 	= Ek[index] + mass;
    Double_t P 	= TMath::Sqrt(E*E - mass*mass);
    Double_t Px = P* sin(th)*cos(ph);
    Double_t Py = P* sin(th)*sin(ph);
    Double_t Pz = P* cos(th);

    return TLorentzVector(Px, Py, Pz, E);
}

Int_t		GTreeRawEvent::GetNCB()	const
{
    Int_t NCB = 0;
    for(Int_t i = 0; i < nParticles; i++)
    {
        if (Apparatus[i] == APPARATUS_CB) NCB++;
    }
    return NCB;
}
Int_t		GTreeRawEvent::GetNTAPS()	const
{
    Int_t NTAPS = 0;
    for(Int_t i = 0; i < nParticles; i++)
    {
        if (Apparatus[i] == APPARATUS_TAPS) NTAPS++;
    }
    return NTAPS;
}
#endif

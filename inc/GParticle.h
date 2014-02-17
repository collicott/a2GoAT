#ifndef __GParticle_h__
#define __GParticle_h__


#include "TLorentzVector.h"





class  GParticle    : public TLorentzVector
{
public:
    enum    DetectorFlag
    {
        Detector_NONE   = 0,
        Detector_NaI    = 1,
        Detector_PID    = 2,
        Detector_WC0    = 4,
        Detector_WC1    = 8,
        Detector_BaFl   = 16,
        Detector_PbWO   = 32,
        Detector_VETO   = 64,
        Detector_CKOV   = 128
    };
    enum    ApparatusFlag
    {
        Apparatus_CB    = 1,
        Apparatus_TAPS  = 1
    };




private:
    Double_t        time;
    UChar_t         clusterSize;
    UChar_t         apparatus;

protected:

public:
    GParticle() :
        TLorentzVector(), time(0), clusterSize(0), apparatus(Detector_NONE)  {}
    GParticle(const TLorentzVector& _Vector, const Double_t _Time = 0, const UChar_t _ClusterSize = 0, const UChar_t _Apparatus = Detector_NONE) :
        TLorentzVector(_Vector), time(_Time), clusterSize(_ClusterSize), apparatus(_Apparatus)  {}
    GParticle(const GParticle& _Particle) :
        TLorentzVector(_Particle), time(_Particle.time), clusterSize(_Particle.clusterSize), apparatus(_Particle.apparatus)  {}
    ~GParticle()                                                                                                  {}

    //inline  GParticle&  operator = (const GParticle& Particle)  {vec = Particle.vec; time = Particle.time; clusterSize = Particle.clusterSize; apparatus = Particle.apparatus; return *this;}
    //inline  GParticle&  operator += (const GParticle& Particle)  {vec = Particle.vec; time = Particle.time; clusterSize = Particle.clusterSize; apparatus = Particle.apparatus; return *this;}

            UChar_t         Apparatus()     const   {return apparatus;}
            UChar_t         ClusterSize()   const   {return clusterSize;}
            Double_t        Time()          const   {return time;}

    ClassDef(GParticle,1)
};



#endif

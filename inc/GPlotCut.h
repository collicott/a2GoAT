#ifndef __GPlotCut_h__
#define __GPlotCut_h__



#include "GTreeManager.h"
#include "GHistCut.h"




class  GPlotCut    : public GTreeManager
{
private:
    struct
    {
        struct
        {
            GHistD*   invMass;
            GHistD*   misMass;
        }   pi0;
        struct
        {
            struct
            {
                GHistD*   invMass;
                GHistD*   misMass;
            }   h2g;
            struct
            {
                GHistD*   invMassPi0[3];
                GHistD*   invMassEta;
                GHistD*   misMass;
            }   h6g;
            GHistD*   invMass;
            GHistD*   misMass;
        }   eta;
        struct
        {
            struct
            {
                GHistD*   invMass;
                GHistD*   misMass;
            }   h2g;
            struct
            {
                GHistD*   invMassPi0[2];
                GHistD*   invMassEta;
                GHistD*   invMassEtap;
                GHistD*   misMass;
            }   h6g;
            GHistD*   invMass;
            GHistD*   misMass;
        }   etap;
    }   hNoProton;

    struct
    {
        struct
        {
            GHistD*   invMass;
            GHistD*   misMass;
            GHistD*   deltaAngleProtonMis4Vec;
            GHistD*   deltaPhiProtonMeson;
        }   pi0;
        struct
        {
            struct
            {
                GHistD*   invMass;
                GHistD*   misMass;
                GHistD*   deltaAngleProtonMis4Vec;
                GHistD*   deltaPhiProtonMeson;
            }   h2g;
            struct
            {
                GHistD*   invMassPi0[3];
                GHistD*   invMassEta;
                GHistD*   misMass;
                GHistD*   deltaAngleProtonMis4Vec;
                GHistD*   deltaPhiProtonMeson;
            }   h6g;
            GHistD*   invMass;
            GHistD*   misMass;
            GHistD*   deltaAngleProtonMis4Vec;
            GHistD*   deltaPhiProtonMeson;
        }   eta;
        struct
        {
            struct
            {
                GHistD*   invMass;
                GHistD*   misMass;
                GHistD*   deltaAngleProtonMis4Vec;
                GHistD*   deltaPhiProtonMeson;
            }   h2g;
            struct
            {
                GHistD*   invMassPi0[2];
                GHistD*   invMassEta;
                GHistD*   invMassEtap;
                GHistD*   misMass;
                GHistD*   deltaAngleProtonMis4Vec;
                GHistD*   deltaPhiProtonMeson;
            }   h6g;
            GHistD*   invMass;
            GHistD*   misMass;
            GHistD*   deltaAngleProtonMis4Vec;
            GHistD*   deltaPhiProtonMeson;
        }   etap;
    }   hProton;

    void    Init();

protected:
    virtual void    ProcessEvent();

public:
    GPlotCut();
    virtual ~GPlotCut();

    virtual Bool_t  Process(const char* input_filename, const char* output_filename = 0);
};





#endif

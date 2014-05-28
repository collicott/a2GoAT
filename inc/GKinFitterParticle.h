#ifndef _GKinFitterParticle_h
#define _GKinFitterParticle_h

#include "TMatrixD.h"
#include "TMath.h"
#include "TLorentzVector.h"

class GKinFitterParticle {

 public:
  GKinFitterParticle(){fNvar=4;fAlpha.ResizeTo(fNvar,1);fV_Alpha.ResizeTo(fNvar,fNvar);fT.ResizeTo(fNvar,fNvar-1);};
  GKinFitterParticle(TLorentzVector lv,Double_t sig_th,Double_t sig_ph,Double_t sig_e);
  GKinFitterParticle(TLorentzVector *lv);

  // GKinFitterParticle(GKinFitterParticle );
  virtual ~GKinFitterParticle(){};

  void Set4Vector(TLorentzVector lv){flv=lv;SetAlpha();};
  void SetAlpha();//Always call this via Set4Vector
  void SetVAlpha(TMatrixD V){fV_Alpha=V;};
  void SetResolutions(Double_t sig_th,Double_t sig_ph,Double_t sig_E){ Polar2Cartesian(sig_th,sig_ph,sig_E);};
  TMatrixD GetVAlpha(){return fV_Alpha;};
  TMatrixD GetAlpha(){return fAlpha;};
  TMatrixD GetT();
  TLorentzVector Get4Vector();
  Int_t GetNVar(){return fNvar;};

  GKinFitterParticle Add(GKinFitterParticle p1); //returns this+p1
  GKinFitterParticle Subtract(GKinFitterParticle p1);//returns this-p1

  void Polar2Cartesian(Double_t sig_th,Double_t sig_ph,Double_t sig_e);//Calculate the error matrix in cart. from sig_th etc.

 
 private:
  TMatrixD fAlpha;
  TMatrixD fV_Alpha;
  TMatrixD fT;  //Transformation matrix S. polar ->Cartesian
  TLorentzVector flv;
  Int_t fNvar; //Number of variables =4 for 4 vector
};

#endif

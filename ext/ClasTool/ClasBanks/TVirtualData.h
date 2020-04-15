////////////////////////////////////////////////////////////////////////
// File TVirtualData.h  
//
// Initial Author: Maurik Holtrop  UNH  11/28/01
//
// Vitual base class for TEVNTClass and TGSIMClass
//
////////////////////////////////////////////////////////////////////////

#ifndef _TVirtualData_ 
#define _TVirtualData_ 
#include <iostream>
using namespace std;
#include "TObject.h"
#include "TString.h"
#include "TVector3.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TMath.h"


class TVirtualData: public TObject{
  
 public:
  Int_t     Id;     //-> Particle Data Group ID (from SEB) 
  Char_t    Charge; //-> charge (from tracking)
  Float_t   Betta;  //-> Particle velocity in the units of c (=R_trk/TOF/c)
  Float_t   Px;     //-> Momentum Vector X component.
  Float_t   Py;     //-> Momentum Vector Y component.
  Float_t   Pz;     //-> Momentum Vector Z component.
  Float_t   X;      //-> "Vertex" Vector X component. The vertex is actually a projection onto a plane.
  Float_t   Y;      //-> "Vertex" Vector Y component. The vertex is actually a projection onto a plane.
  Float_t   Z;      //-> "Vertex" Vector Z component. The vertex is actually a projection onto a plane.
  Char_t    Dcstat; //-> Index into the TDCPBClass array.
  Char_t    Ccstat; //-> Index into the TCCPBClass array.
  Char_t    Scstat; //-> Index into the TSCPBClass array. 
  Char_t    Ecstat; //-> Index into the TECPBClass array.
  Char_t    Lcstat; //-> Index into the TLCPBClass array.
  Char_t    Ststat; //-> Index into the TSTPBClass array.
  Char_t    Status; //-> Status word (=0 for out of time particle)
 public:
  TVirtualData(){};
  TVirtualData(TVirtualData *TmpEVNT);
   ~TVirtualData(){};
   virtual inline Int_t  GetId(){return(Id);};
   virtual inline Char_t GetCharge(){return((Char_t)Charge);};
   virtual inline Float_t GetBeta() {return(Betta);};
   virtual inline Float_t GetPx(){return(Px);};
   virtual inline Float_t GetPy(){return(Py);};
   virtual inline Float_t GetPz(){return(Pz);};
   virtual inline Float_t GetX(){return(X);};
   virtual inline Float_t GetY(){return(Y);};
   virtual inline Float_t GetZ(){return(Z);};
   virtual inline TVector3 GetVertex(){return(TVector3(X,Y,Z));}
   virtual inline TVector3 GetMomVec(){return(TVector3(Px,Py,Pz));}
   virtual inline Float_t GetMomentum(){return(TMath::Sqrt(Px*Px+Py*Py+Pz*Pz));};
   virtual inline Char_t GetDCStat(){return((Char_t)Dcstat);};
   virtual inline Char_t GetCCStat(){return((Char_t)Ccstat);};
   virtual inline Char_t GetSCStat(){return((Char_t)Scstat);};
   virtual inline Char_t GetECStat(){return((Char_t)Ecstat);};
   virtual inline Char_t GetLCStat(){return((Char_t)Lcstat);};
   virtual inline Char_t GetSTStat(){return((Char_t)Ststat);};
   virtual inline Char_t GetStat()  {return((Char_t)Status);};
   virtual inline Char_t GetDCidx(){return((Char_t)Dcstat-1);};
   virtual inline Char_t GetCCidx(){return((Char_t)Ccstat-1);};
   virtual inline Char_t GetSCidx(){return((Char_t)Scstat-1);};
   virtual inline Char_t GetECidx(){return((Char_t)Ecstat-1);};
   virtual inline Char_t GetLCidx(){return((Char_t)Lcstat-1);};
   virtual inline Char_t GetSTidx(){return((Char_t)Ststat-1);};
   virtual inline Bool_t IsEVNT(){return(kFALSE);};
   virtual inline Bool_t IsGSIM(){return(kFALSE);};
   virtual Float_t GetMass();
   virtual void	 Print();
  //
  //
  //
  //
   ClassDef(TVirtualData,3) //Virtual base Class for accessing the EVNT bank: particle information. Version 3.
   };

#endif
    


////////////////////////////////////////////////////////////////////////
// File TECPBBank.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:21:47 EST 1999
//
////////////////////////////////////////////////////////////////////////
#ifndef _TECPBClass_ 
#define _TECPBClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TMath.h"
#include "TString.h"
#include "TVector3.h"


class TECPBClass: public TObject{
  
 public:
  Int_t     Scht;  // 100*sector+Whole_Hit_ID in ECHB 
  Float_t   Etot;  // Reconstructed total energy
  Float_t   Ein;  // Inner energy
  Float_t   Eout;  // Outer energy 
  Float_t   Time;  // Flight time relative to the evnt start time
  Float_t   Path;  // Path lenght from target
  Float_t   X;  // x coordinate of hit 
  Float_t   Y;  // y coordinate of hit
  Float_t   Z;  // z coordinate of hit
  Float_t   M2_hit;  // second moment of _hit pattern
  Float_t   M3_hit;  // third moment of  _hit pattern 
  Float_t   M4_hit;  // forth moment of  _hit pattern 
  Int_t     Innstr;  // 10000*UI+100*VI+WI 
  Int_t     Outstr;  // 10000*UO+100*VO+WO 
  Float_t   Chi2ec;  // Quality measure of geometrical matching
  Int_t     Status;  // Status word (not implemented yet)
 public:
  TECPBClass(){};
  TECPBClass(TECPBClass *TmpECPB);
  virtual ~TECPBClass(){};

  inline Int_t   GetScht()    { return Scht ; }
  inline Float_t GetEtot()    { return Etot ; }
  inline Float_t GetEin()     { return Ein ; }
  inline Float_t GetEout()    { return Eout ; }
  inline Float_t GetTime()    { return Time ; }
  inline Float_t GetPath()    { return Path ; }
  inline Float_t GetX()       { return X ; }
  inline Float_t GetY()       { return Y ; }
  inline Float_t GetZ()       { return Z ; }
  inline Float_t GetM2()      { return M2_hit; }
  inline Float_t GetM3()      { return M3_hit ; }
  inline Float_t GetM4()      { return M4_hit ; }
  inline Int_t   GetInnstr()  { return Innstr; }
  inline Int_t   GetOutstr()  { return Outstr; }
  inline Float_t GetChi2()    { return Chi2ec ; }
  inline Int_t   GetStatus()  { return Status ; }

  inline TVector3 GetHitPos() { return TVector3( X, Y, Z ); }
  inline Int_t    GetSector() { return Scht / 100 ; }
  inline Int_t    GetHitId()  { return Scht % 100 ; }

  void 	 Print();
  void GetUVW(Float_t* u, Float_t* v, Float_t* w,TVector3 Detco);
  void GetUVW(Float_t* u, Float_t* v, Float_t* w);

  //
  ClassDef(TECPBClass,1) // Class for accessing the ECPB bank: Calorimeter
};
#endif



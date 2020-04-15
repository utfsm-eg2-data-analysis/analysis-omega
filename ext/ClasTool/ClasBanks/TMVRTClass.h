////////////////////////////////////////////////////////////////////////
// File TMVRTBank.h  
//
// Initial Author: Gagik Gavalian  UNH  11/13/1999 
//
// This file is generated automatically by make_bank_class.pl 
//
// Generation DATE : Tue Nov 23 18:21:53 EST 1999
//
// Modified:
//           Maurik (2/3/00) Comments
//           Maurik (3/4/00) Changed the variables and comments according to 
//           the changes to the comments and var name in MVRT Stepan.
//
//           Maurik (6/15/00) Fix BIG WHOOPS! You can not change the name of
//                  of a variable, or else root puts a zero in it when reading
//                  a TTree. Instead, I added GetX_v() GetX_y() .... functions.
////////////////////////////////////////////////////////////////////////
#ifndef _TMVRTClass_ 
#define _TMVRTClass_ 
#include <iostream>
using namespace std;

#include "TObject.h"
#include "TString.h"
#include "TVector3.h"

class TMVRTClass: public TObject{
  
 public:

  Int_t   v_id;  // I   -1000    1000   ! info about track ids
  Float_t ntrk; // F   -100.    100.   ! number of tracks used to make vertex
  Float_t x;    // F  -1000.   1000.   ! x vector3_t vert{x,y,z}
  Float_t y;    // F  -1000.   1000.   ! y 
  Float_t z;    // F  -1000.   1000.   ! z
  Float_t chi2; // F  -1000.   1000.   ! chi2
  Float_t cxx;  // F  -1000.   1000.   ! Covariance matrix array element
  Float_t cxy;  // F  -1000.   1000.   ! Covariance matrix array element
  Float_t cxz;  // F  -1000.   1000.   ! Covariance matrix array element
  Float_t cyy;  // F  -1000.   1000.   ! Covariance matrix array element
  Float_t cyz;  // F  -1000.   1000.   ! Covariance matrix array element
  Float_t czz;  // F  -1000.   1000.   ! Covariance matrix array element
  Int_t   stat; // I  -1000.   1000.   ! status integer, not used yet

 public:
  TMVRTClass(){};
  TMVRTClass(TMVRTClass *TmpMVRT);
  virtual ~TMVRTClass(){};
  Int_t   GetVid(){return( (Int_t)v_id);}; // Return info on track ids.
  Int_t   GetNtrk(){return( (Int_t)ntrk);}; // Return number of tracks used.
  Float_t GetX(){return((Float_t)x);};  // Return x coord of vertex.
  Float_t GetY(){return((Float_t)y);};  // Return y coord of vertex.
  Float_t GetZ(){return((Float_t)z);};  // Return z coord of vertex.
  Float_t GetChi2(){return((Float_t)chi2);};  // Return chi2 of fit.

  Float_t GetCXX(){return((Float_t)cxx);};  // Return covariant matrix element.
  Float_t GetCXY(){return((Float_t)cxy);};  // Return covariant matrix element.
  Float_t GetCXZ(){return((Float_t)cxz);};  // Return covariant matrix element.
  Float_t GetCYY(){return((Float_t)cyy);};  // Return covariant matrix element.
  Float_t GetCYZ(){return((Float_t)cyz);};  // Return covariant matrix element.
  Float_t GetCZZ(){return((Float_t)czz);};  // Return covariant matrix element.
  
  Int_t   GetStatus(){return((Int_t)stat);}; // Return Status word.
  TVector3 GetV3Vertex(){return(TVector3(x,y,z));}; // Return Vertex as a 3 vector.


  void 	 Print();
  //
  ClassDef(TMVRTClass,1) // Class for accessing the MVRT bank: Fitted Vertex.
    };
#endif



////////////////////////////////////////////////////////////////////////
// File TDCPBBank.h  
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
//           the changes to the comments and var name in DCPB Stepan.
//
//           Maurik (6/15/00) Fix BIG WHOOPS! You can not change the name of
//                  of a variable, or else root puts a zero in it when reading
//                  a TTree. Instead, I added GetX_v() GetX_y() .... functions.
////////////////////////////////////////////////////////////////////////
#ifndef _TDCPBClass_ 
#define _TDCPBClass_ 
#include <iostream>
using namespace std;

#include "TObject.h"
#include "TString.h"
#include "TVector3.h"

class TDCPBClass: public TObject{
  
 public:
  Int_t     Sctr;  // 100*sector+track_ID in *BTR  
  Float_t   X_sc;  // x coordinate of track intersection with SC plane 
  Float_t   Y_sc;  // y coordinate of track intersection with SC plane
  Float_t   Z_sc;  // z coordinate of track intersection with SC plane
  Float_t   Cx_sc; // X dir cosine at (x_SC,y_SC,z_SC)
  Float_t   Cy_sc; // y dir cosine at (x_SC,y_SC,z_SC)
  Float_t   Cz_sc; // z dir cosine at (x_SC,y_SC,z_SC)
  Float_t   X_ec;   // vertex X after fiting to the beam position  (mod 3/4/00 MWH)
  Float_t   Y_ec;   // vertex Y after fiting to the beam position  (mod 3/4/00 MWH)
  Float_t   Z_ec;   // vertex Z after fiting to the beam position  (mod 3/4/00 MWH)  
  Float_t   Th_cc;   // distance from production vertex to the bemam. (mod 3/4/00 MWH) 
  Float_t   Chi2;  // Chisquare of track fitting
  Int_t     Status;  // Status word
 public:
  TDCPBClass(){};
  TDCPBClass(TDCPBClass *TmpDCPB);
  virtual ~TDCPBClass(){};
  Int_t   GetSector(){return( (Int_t)(Sctr/100));}; // Return Sector of hit.
  Int_t   GetTrackId(){return( (Int_t)(Sctr%100));}; // Return Track Id
  Float_t GetX_sc(){return(X_sc);};  // Return x coord at SC plane.
  Float_t GetY_sc(){return(Y_sc);};  // Return y coord at SC plane.
  Float_t GetZ_sc(){return(Z_sc);};  // Return z coord at SC plane.
  Float_t GetCosX_sc(){return(Cx_sc);};  // Return x dir cosine at SC plane.
  Float_t GetCosY_sc(){return(Cy_sc);};  // Return y dir cosine at SC plane.
  Float_t GetCosZ_sc(){return(Cz_sc);};  // Return z dir cosine at SC plane.
  Float_t GetX_v(){return(X_ec);};  // Return the X_v = X_ec value.
  Float_t GetY_v(){return(Y_ec);};  // Return the Y_v = Y_ec value.
  Float_t GetZ_v(){return(Z_ec);};  // Return the Z_v = Z_ec value.
  Float_t GetR_v(){return(Th_cc);};  // Return the R_v = Th_cc value.
  Float_t GetChi2(){return(Chi2);}; // Return chisqare of fit
  Int_t   GetStatus(){return(Status);}; // Return Status word.
  TVector3 GetV3Vertex(){return(TVector3(X_ec,Y_ec,Z_ec));}; // Return Vertex as a 3 vector.


  void 	 Print();
  //
  ClassDef(TDCPBClass,1) // Class for accessing the DCPB bank: Drift Chambers
    };
#endif



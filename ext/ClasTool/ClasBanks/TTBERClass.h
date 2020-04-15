////////////////////////////////////////////////////////////////////////
// File TTBERBank.h  
//
// Initial Author: Maurik Holtrop 8/1/2005 

////////////////////////////////////////////////////////////////////////
//!********************************************************************
//!       BANKname BANKtype      ! Comments
// TABLE  TBER  ! create write display delete ! Time Based Tracking ERror bank
//!  record_no=0
//!
//!  Fit parameter and Covariance matrix: (Cij)
//!
//!  Track# = row#  (cf. TBTR bank)
//!  	note these are in the sda tracking coordinate system 
//!           (x=beamline, y=radially outward, z=parallel to axial wires)
//!   ATTributes:
//!   -----------
//!COL ATT-name FMT    Min     Max   ! Comments
//!
//  1  q_over_p   F      0.    100.   ! q/p
//  2  lambda     F    -10.     10.   ! dip angle (pi/2 - theta)
//  3  phi        F    -60.     60.   ! phi
//  4  d0         F   -100.    100.   ! min.distance from (x=0,y=0,z=?)  [cm]
//  5  z0         F   -100.    100.   ! z position of starting point     [cm] 
//  6  c11        F    -10.     10.   ! element C{1,1}
//  7  c12        F    -10.     10.   ! element C{1,2}
//  8  c13        F    -10.     10.   ! element C{1,3}
//  9  c14        F    -10.     10.   ! element C{1,4}
// 10  c15        F    -10.     10.   ! element C{1,5}
// 11  c22        F    -10.     10.   ! element C{2,2}
// 12  c23        F    -10.     10.   ! element C{2,3}
// 13  c24        F    -10.     10.   ! element C{2,4}
// 14  c25        F    -10.     10.   ! element C{2,5}
// 15  c33        F    -10.     10.   ! element C{3,3}
// 16  c34        F    -10.     10.   ! element C{3,4}
// 17  c35        F    -10.     10.   ! element C{3,5}
// 18  c44        F    -10.     10.   ! element C{4,4}
// 19  c45        F    -10.     10.   ! element C{4,5}
// 20  c55        F    -10.     10.   ! element C{5,5}
// 21  chi2       F      0.     50.   ! Chisquare for this Track
// 22  layinfo1   I      0.      0.   ! layerhit info
// 23  layinfo2   I      0.      0.   ! layerhit info&sector&track#in hber
//! the layer hit info is stored in the following way
//! for layinfo1= sum over each layer used in track(layers 1-30) Of 2^(layer#-1)
//! for layinfo2 = sum of 2^(layer#-31) for (layers 31-36)
//!	 	+ 256 * track# in sector+256^2*track# in hber 
//!		+ 256^3 * sector
//!
//!RELations:
////!    ----------
//!COL RELname  RELtype INTbank  ! Comments
//!                     (COL)
//!  
//!
// END TABLE
//
//
//
#ifndef _TTBERClass_
#define _TTBERClass_

#include <iostream>
using namespace std;

#include "TObject.h"
#include "TString.h"
#include "TMatrix.h"

class TTBERClass: public TObject{

 public:
  Float_t  q_over_p; // q/p
  Float_t  lambda;   // dip angle (pi/2 - theta)
  Float_t  phi;      
  Float_t  d0;       // Min. distance from (x=0,y=0,z=?) [cm]
  Float_t  z0;       // z position of starting point     [cm]
  Float_t  chi2;     // ChiSquare
  Int_t    layinfo1; // layinfo1= sum over each layer used in track(layers 1-30) Of 2^(layer#-1)
  Int_t    layinfo2; //
//! for layinfo2 = sum of 2^(layer#-31) for (layers 31-36)
//!	 	+ 256 * track# in sector+256^2*track# in hber 
//!		+ 256^3 * sector
  

  // TMatrixF *c;       // 5x5 error matrix.
  //
  // Originally I tried to use a TMatrixF, but this took up a fair bit extra 
  // space. We store the Floats independently and then construct a TMatrixF when
  // requested. This could be an array, but that is confusing...

  Float_t  c11;
  Float_t  c12;
  Float_t  c13;
  Float_t  c14;  
  Float_t  c15;
  Float_t  c22;
  Float_t  c23;
  Float_t  c24;
  Float_t  c25;
  Float_t  c33;
  Float_t  c34;
  Float_t  c35;
  Float_t  c44;
  Float_t  c45;
  Float_t  c55;

 public:
  TTBERClass(){};
  ~TTBERClass(){};
  TTBERClass(TTBERClass *TmpTBER); // copy constructor.

  TMatrixF Get_ErrMatrix();
  void  Get_ErrMatrix(TMatrixF *f);
  void  Get_ErrMatrix(TMatrixF &f);


  void Print(void);   // Print info on class.


  ClassDef(TTBERClass,1) // Class for accessing the TBER bank: Tracking error information.
    ;
};



#endif

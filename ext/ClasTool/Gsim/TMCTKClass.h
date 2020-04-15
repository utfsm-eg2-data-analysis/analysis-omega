#ifndef _TMCTKClass_ 
#define _TMCTKClass_ 
#include <iostream>

#include "TObject.h"
#include "TString.h"
#include "TGsim.h"

//  1  cx       F    -1.   1.    ! x dir cosine at track origin
//  2  cy       F    -1.   1.    ! y dir cosine
//  3  cz       F    -1.   1.    ! z dir cosine
//  4  pmom     F     0.   20.   ! momentum
//  5  mass     F     0.   10.   ! mass
//  6  charge   F    -1.    1.   ! charge
//  7  id       I  -5000   5000  ! track Particle Data Group id
//  8  flag     I     0  0xFFFF  ! track flag
//  9  beg_vtx  I     0   65536  ! beginning vertex number 
// 10  end_vtx  I     0   65536  ! ending vertex number
// 11  parent   I     0   65536  ! parent track                    


class TMCTKClass: public TObject{

public:
  Float_t Cx;         // x dir cosine at track origin    
  Float_t Cy;	      // y dir cosine                    
  Float_t Cz;	      // z dir cosine                    
  Float_t Pmom;	      // momentum                        
  Float_t Mass;	      // mass                            
  Float_t Charge;     // charge                          
  Int_t   Id;	      // track Particle Data Group id    
  Int_t   Flag;	      // track flag                      
  Int_t   Beg_vtx;    // beginning vertex number         
  Int_t   End_vtx;    // ending vertex number            
  Int_t   Parent;     // parent track                    

public:
	 TMCTKClass(){};
	 TMCTKClass(TMCTKClass *Tmp);
	 TMCTKClass(void *Tmp,Int_t i=0); // Get bank #i, use with getBank()
	 virtual ~TMCTKClass(){};
	 void 	 Print(void);
//
	 ClassDef(TMCTKClass,1) // Class for accessing the MCTK bank: Monte Carlo particle vectors.
};
#endif

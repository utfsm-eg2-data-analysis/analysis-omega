////////////////////////////////////////////////////////////////////////
// File TVERTBank.h  
//
// Created: Maurik Holtrop   3/6/2005
//
//
// Modified:
//
////////////////////////////////////////////////////////////////////////
#ifndef _TVERTClass_ 
#define _TVERTClass_ 
#include <iostream>
using namespace std;

#include "TObject.h"
#include "TString.h"
#include "TVector3.h"

class TVERTClass: public TObject{
  
 public:
  Int_t vertex; //     I   -1000    1000   ! vertex id
  Int_t trk1;   //     I       0      10   ! track #1
  Int_t trk2;   //     I       0      10   ! track #2
  Float_t  x;   //     F  -1000.   1000.   ! x vector3_t vert{x,y,z}
  Float_t  y;   //     F  -1000.   1000.   ! y 
  Float_t  z;   //     F  -1000.   1000.   ! z
  Float_t sepd; //     F   -100.    100.   ! seperation distance

 public:
  TVERTClass(){};
  TVERTClass(TVERTClass *TmpVERT);
  virtual ~TVERTClass(){};
  Int_t   GetVertexId(){return( (Int_t)vertex);}; // Return Vertex ID.
  Int_t   GetTrack1Id(){return( (Int_t)trk1);}; // Return Track1 ID, points into TBTR bank.
  Int_t   GetTrack2Id(){return( (Int_t)trk2);}; // Return Track1 ID, points into TBTR bank.
  Float_t GetVertexX() {return( (Float_t)x);};  // Return X of vertex.
  Float_t GetVertexY() {return( (Float_t)y);};  // Return Y of vertex.
  Float_t GetVertexZ() {return( (Float_t)z);};  // Return Z of vertex.
  Float_t GetDOCA()    {return( (Float_t)sepd);}; // Return DOCA (dist. of Closest Approach) = separation distance.
  TVector3 GetV3Vertex(){return(TVector3(x,y,z));}; // Return Vertex as a 3 vector.
  void 	 Print();
  //
  ClassDef(TVERTClass,1) // Class for accessing the VERT bank, 2 track vertexes.
    };
#endif



/////////////////////////////////////////////////////////////////////////////////
//
//
//  This class presents is part of the ClasTool data analysis framework.
//
//-----------------------------------------------------------------------------
//
//  Documentation  : TPartSieve.html 
//                   (available also at http://www.physics.unh.edu/maurik/ClasTool)
//  Created on     :  2006 (UNH)
//  Initial Authors:  Maurik Holtrop (UNH) 
//
//  Updated        :  Will Morrison  (UNH) 2005
//  Updated        :  Maurik Holtrop (UNH) 2006
//
////////////////////////////////////////////////////////////////////////////////
//
//

#ifndef __TPartSieve__
#define __TPartSieve__

// Standart Includes 

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>

// ROOT includes 

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TString.h"
#include "TChain.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TRotation.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"

#ifdef __USE_MYSQL__
#include "TSQLServer.h"
#include "TSQLRow.h"
#include "TSQLResult.h"
#endif

//
// CLAS Banks Includes
//

#include "THEADERClass.h"
#include "TEVNTClass.h"
#include "TECPBClass.h"
#include "TSCPBClass.h"
#include "TDCPBClass.h"
#include "TCCPBClass.h"
#include "TLCPBClass.h"
#include "THEADClass.h"

// GSIM Bank 

#ifdef WRITE_GSIM
#include "TGSIMClass.h"
#endif

#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"

#include "TVirtualReader.h"
// #include "TDSTReader.h"
// #include "TNT10Reader.h"  Probably should never want this included...

#include "TClasTool.h"

//
// From the Standard Template Library.
//
#include <vector>
#include <algorithm>

#define MAXPARTS 10

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

class TPartSieve : public TObject{

 public:

  //
  // These parameters define the location of the various cuts.
  //

  Float_t fEC_U_Cut;
  Float_t fEC_V_Cut;
  Float_t fEC_W_Cut;
  Float_t fEC_U_Cut_width;
  Float_t fEC_V_Cut_width;
  Float_t fEC_W_Cut_width;

  Float_t fEC_Eio_slope;
  Float_t fEC_Eio_off;
  Float_t fEC_Ein_cut;
  Float_t fEC_Eout_cut;

  Float_t fCC_Phe_cut;
  Float_t fCC_Phe_width;

  Float_t fConf_Pim_DT_min;
  Float_t fConf_Pim_DT_max;
  Float_t fConf_Pip_DT_min;
  Float_t fConf_Pip_DT_max;

  Float_t fConf_Km_DT_min;
  Float_t fConf_Km_DT_max;
  Float_t fConf_Kp_DT_min;
  Float_t fConf_Kp_DT_max;

  Float_t fConf_Prot_DT_min;
  Float_t fConf_Prot_DT_max;

  Float_t fConf_Deut_DT_min;
  Float_t fConf_Deut_DT_max;

  Float_t fConf_He3_DT_min;
  Float_t fConf_He3_DT_max;

  Float_t fConf_He4_DT_min;
  Float_t fConf_He4_DT_max;

  Float_t fConf_Neut_DT_min;
  Float_t fConf_Neut_DT_max;

  Float_t fConf_El_DC_chi2;
  Float_t fConf_Prot_DC_chi2;
  Float_t fConf_Pim_DC_chi2;
  Float_t fConf_Pip_DC_chi2;
  Float_t fConf_Km_DC_chi2;
  Float_t fConf_Kp_DC_chi2;

  Float_t fConf_Deut_DC_chi2;
  Float_t fConf_He3_DC_chi2;
  Float_t fConf_He4_DC_chi2;

  Float_t fConf_El_DC_chi2_width;
  Float_t fConf_Prot_DC_chi2_width;
  Float_t fConf_Pim_DC_chi2_width;
  Float_t fConf_Pip_DC_chi2_width;
  Float_t fConf_Km_DC_chi2_width;
  Float_t fConf_Kp_DC_chi2_width;

  Float_t fConf_Deut_DC_chi2_width;
  Float_t fConf_He3_DC_chi2_width;
  Float_t fConf_He4_DC_chi2_width;

  vector<int> fvBadPaddles;


 public:

  TClasTool  *fCT; // This is a pointer to the actual reader used.
  UShort_t fSortFlag; // This flag controls the mode of the Sieve
  Int_t fDebug_Mode;        // Sets the verbosity of the code. 
  Int_t fIndexSave; //used by IDtoInd and IDtoIndQuick for faster use
  Float_t fRefConfidenceCut; //when Refining Id's parts with less than this confidence will be refined
  Float_t fConfidenceCut; //Minimum confidence for Sieve to store a particle

  //to be used as counters when filling arrays, then kept to be read later
  Int_t fNPart[kNParticleTypes]; //Stores the numbers of each type of particle in an event

  Int_t fIndex[kNParticleTypes][MAXPARTS];// Stores the particle index in the EVNT bank
  Float_t fConfidence[kNParticleTypes][MAXPARTS];  //Confidence level in particle id
  //structure of arrays fSieve[particle name][#]
  //eg. fIndex[kPion_Plus][2] gets the third pi+ in the event

  void IndexPart(Int_t Ind,Float_t confidence=1);//Save a particles CT index and confidence
                                                 // into the correct array
 public:
  
  TPartSieve();
  TPartSieve(TClasTool *clastool,Int_t runnum=0);
  virtual ~TPartSieve();

  //Set up the Sieve
  void SortOn(); //These 3 functions turn Sieve functions on
  void ConfidenceOn();
  void RefineIdOn();
  void SortOff();     //These three turn them off
  void ConfidenceOff();
  void RefineIdOff();
  void SetDebugMode(Int_t Mode); //set verbosity
  void SetConfidenceCut(Float_t conf); //set minimum confidence for parts saved in sieve
  void SetRefConfidenceCut(Float_t conf);//set minimum confidence for parts not refined

  Float_t GetPartConf(Int_t Ind);//Get the confidence that a particle is what ClasTool thinks it is
  void RefinePartId(Int_t Ind);//Refine the Id given by EVNT

  //Run the current event through the Sieve. Runs over every particle.
  Int_t SieveEvent();

  //Utilities for use during analysis

  inline Int_t GetNIdx(Int_t idx){return fNPart[idx];}; // Return num particle for index idx.
  Int_t GetNPid(Int_t pid); //get how many of a particle are in this event

  Int_t GetIndexIdx(Int_t idx, Int_t num); //get the TClasTool index of the numth idx
  Int_t GetIndexPid(Int_t pid, Int_t num); //get the TClasTool index of the numth pid

  TEVNTClass* GetEVNTIdx(Int_t idx, Int_t num); //get the EVNT bank of the numth idx
  TEVNTClass* GetEVNTPid(Int_t pid, Int_t num); //get the EVNT bank of the numth pid

  Float_t GetConfFast(Int_t pid, Int_t num); //get confidence from table
  void IndexConf(Float_t conf,Int_t pid,Int_t num);//If you wish to save a particle confidence you have got
                                      //independently of SieveEvent, this will save it in the numth slot of pid
  void Print(); //Prints the fNpart data

  //These functions are for calculating confidences for specific particles.
  //They are called automatically by SieveEvent() on the type of particle they
  //are named for if ConfidenceOn is called, or the user can select functions
  //to be called for any type of particle that they like. Use for example:
  //ConfEl(GetIndex(0,j)) to test the confidence that the jth Unknown is an e-.

  virtual Float_t ConfUnknown(Int_t Ind);
  virtual Float_t ConfPip(Int_t Ind);
  virtual Float_t ConfProt(Int_t Ind);
  virtual Float_t ConfEl(Int_t Ind,Float_t W=0.); 
  virtual Float_t ConfPhot(Int_t Ind); 
  virtual Float_t ConfPim(Int_t Ind); 
  virtual Float_t ConfNeut(Int_t Ind); 
  virtual Float_t ConfKp(Int_t Ind); 
  virtual Float_t ConfDeut(Int_t Ind); 
  virtual Float_t ConfKm(Int_t Ind); 
  virtual Float_t ConfHe4(Int_t Ind); 
  virtual Float_t ConfHe3(Int_t Ind); 
  virtual Float_t ConfPos(Int_t Ind); 
 
//These functions are for refining the ids of specific particles. They are 
//automatically called by SieveEvent() if the user calls RefineIdOn().

  virtual Int_t RefineIdUnknown(Int_t Ind); 
  virtual Int_t RefineIdPip(Int_t Ind);  //specific id
  virtual Int_t RefineIdProt(Int_t Ind); //another file.
  virtual Int_t RefineIdEl(Int_t Ind); 
  virtual Int_t RefineIdPhot(Int_t Ind); 
  virtual Int_t RefineIdPim(Int_t Ind); 
  virtual Int_t RefineIdNeut(Int_t Ind); 
  virtual Int_t RefineIdKp(Int_t Ind); 
  virtual Int_t RefineIdDeut(Int_t Ind); 
  virtual Int_t RefineIdKm(Int_t Ind); 
  virtual Int_t RefineIdHe4(Int_t Ind); 
  virtual Int_t RefineIdHe3(Int_t Ind); 
  virtual Int_t RefineIdPos(Int_t Ind); 

  //These are cuts to be used in the ConfPart functions

  virtual Float_t CutConfMax(Float_t x,Float_t cut,Float_t width);
  virtual Float_t CutConfMin(Float_t x,Float_t cut,Float_t width);

  virtual Float_t ECUVWCut(Int_t Ind,Float_t WidthMultiply=0.);
  virtual Float_t ECUVWCut(TEVNTClass *evnt,Float_t WidthMultiply=0.);

  virtual Float_t EC_Eio_Cut(Int_t Ind,Float_t WidthMultiply=0.);
  virtual Float_t EC_Eio_Cut(TEVNTClass *evnt,Float_t WidthMultiply=0.);

  virtual Float_t CC_Phe_Cut(Int_t Ind,Float_t WidthMultiply=0.);
  virtual Float_t CC_Phe_Cut(TEVNTClass *evnt,Float_t WidthMultiply=0.);

  virtual Float_t GetDeltaT(Int_t Ind);
  virtual Float_t GetDeltaT(TEVNTClass *evnt);
  virtual Float_t GetDeltaT(TSCPBClass *sc,Float_t p,Int_t ipart );
  virtual Float_t GetDeltaT_EC(TECPBClass *ec,Float_t p,Int_t ipart );

  virtual Float_t Get_DC_Qual(Int_t Ind,Float_t Chi2,Float_t Width=0.5); 

  virtual Float_t BetaBetaCut(Int_t Ind, Float_t mass, Float_t Wieght, Float_t MaxDiff);

  virtual Float_t NoCCCut(Int_t Ind,Float_t Weight);
  virtual Float_t NoECCut(Int_t Ind,Float_t Weight);
  virtual Float_t NoDCCut(Int_t Ind,Float_t Weight);
  virtual Float_t NoSCCut(Int_t Ind,Float_t Weight);

  //This function should be somewhere else (ie. the vertex class, but I 
  //need it for an analysis and this was the simplest place to put it.
  TVERTClass* GetVert(Int_t PID1, Int_t num1, Int_t PID2, Int_t num2);
  TVERTClass* Vert_Error_Handler(Int_t NRows,Int_t track1,Int_t track2);

  inline Float_t GetBetaP(Float_t p,Int_t ipart);
  inline Int_t IDtoInd(Int_t ID);
  inline Int_t IDtoIndQuick();
  Int_t IndtoID(Int_t Ind);

  Bool_t CheckSCPaddle(TSCPBClass *sc);
  Bool_t CheckSCPaddle(Int_t secidcode);
  Bool_t CheckSCPaddle(Int_t sector,Int_t paddle);

  Int_t  SetBadPaddle(Int_t sector,Int_t paddle); 

  virtual void ChangeID(Int_t Ind, Int_t ID); //This function changes the ID in the runfile

  enum E_SortFlag_state{ // Enumerate the various states.
    kSortFlag_SortOn = 0x100,
    kSortFlag_ConfidenceOn = 0x010,
    kSortFlag_RefineIdOn = 0x001
  };
    


  ClassDef(TPartSieve,2) // Package to sort particles and fix PID.
    
};


inline Float_t TPartSieve::GetBetaP(Float_t p,Int_t ipart){ 
    // return beta from momentum and mass (index).
  return(p/TMath::Sqrt(p*p + ClasTool::fgParticle_Mass[ipart]* ClasTool::fgParticle_Mass[ipart]));
}

    

//====================================================================================
inline Int_t TPartSieve::IDtoInd(Int_t PartId)
{
  //This transforms particle id to particle index.
  //This is a passthrough call to TClasTool::GetTypeFromPid, but in addition
  // stores the value in fIndexSave for later retrieval with IDtoIndQuick().
  // (inline function);
  return fIndexSave = ClasTool::GetTypeFromPid(PartId);
}
//==============================================================================
inline Int_t TPartSieve::IDtoIndQuick()
{
  //returns the last value found by IDtoInd. This avoids doing multiple searches.  
  return fIndexSave;
}


#endif


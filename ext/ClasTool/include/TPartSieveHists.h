/////////////////////////////////////////////////////////////////////////////////
//
//
//  This class presents is part of the ClasTool data analysis framework.
//
//-----------------------------------------------------------------------------
//
//  Documentation  : TPartSieveHistograms.html 
//                   (available also at http://www.physics.unh.edu/maurik/ClasTool)
//  Created on     :  2006 (UNH)
//  Initial Authors:  Maurik Holtrop (UNH) 
//
////////////////////////////////////////////////////////////////////////////////
//
//

#ifndef __TPartSieveHistograms__
#define __TPartSieveHistograms__


#include <iostream>

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"

#include "TClasTool.h"
#include "TPartSieve.h"
#include "TCounterCol.h"

#include <vector>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

enum EHistos_Control{
  kMain_Histos   = 0x01,
  kPaddle_Histos = 0x02,
  kDebug_Output  = 0x10 };


class TPartSieveHists : public TObject {

 public:
  UInt_t fControl; // Control Flag.
  
  TPartSieve  *fS;
  TClasTool   *fCT;
  TCounterCol fCuts; // Keep track of cuts.
  TObjArray   *fH;   // Stores the main histograms in directory Hists
  TObjArray   *fHP;  // Stores paddle histograms in directory Paddles;

  // Handles for direct access to the histograms.

  TH1F *APartCount;
  TH1F *AMassPos;
  TH1F *AMassNeg;

  TH1F *AElec_mom;
  TH2F *AElec_Q2W;
  TH2F *AElec_Q2Lc;
  TH1F *AElec_ec_u;
  TH1F *AElec_ec_v;
  TH1F *AElec_ec_w;
  TH2F *AElec_ec_xy;
  TH2F *AElec_ec_etot;
  TH2F *AElec_ec_eio;
  TH1F *AElec_cc;

  TH2F *ABetaPPos;
  TH2F *ABetaPNeg;

  TH1F *SPartCount;
  TH1F *SMassPos;
  TH1F *SMassNeg;

  TH1F *SElec_mom;
  TH2F *SElec_Q2W;
  TH2F *SElec_Q2Lc;
  TH1F *SElec_ec_u;
  TH1F *SElec_ec_v;
  TH1F *SElec_ec_w;
  TH2F *SElec_ec_xy;
  TH2F *SElec_ec_etot;
  TH2F *SElec_ec_eio;
  TH1F *SElec_cc;

  TH2F *SBetaPPos;
  TH2F *SBetaPNeg;

  vector<int> ABetaPIdx;
  vector<int> ADeltatPIdx;

  vector<int> SBetaPIdx;
  vector<int> SDeltatPIdx;

  vector< vector<int> > ASCBetaP; 
  vector< vector<int> > ASCDeltatP; 

 public:

  TPartSieveHists (){cerr << "Starting TPartSieveHistograms uninitialized.\n";};
  TPartSieveHists (TPartSieve *Sieve,UInt_t control=0x01){
    fS=Sieve;
    fControl=control;
    fCT=fS->fCT;
    Initialize();
  }
  
  virtual ~TPartSieveHists();
  void Initialize();
  void InitHists();
  void DeleteHists();
  void ClearHists();
  void Write();

  Int_t Fill();

  inline Float_t GetBetaP(Float_t p,Int_t ipart){return p/TMath::Sqrt(p*p + ClasTool::fgParticle_Mass[ipart]* ClasTool::fgParticle_Mass[ipart]);};

  ClassDef(TPartSieveHists,1) // A PartSieveHists class for simple statistics.
    ;
};

#endif

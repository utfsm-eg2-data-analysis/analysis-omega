/////////////////////////////////////////////////////////////////////////////////
//
//
//  This class presents framework for CLAS analysis
//  based on ROOT DST's.
//
//-----------------------------------------------------------------------------
//
//  Documentation  : TClasTool.html 
//                   (available also at http://www.physics.unh.edu/maurik/ClasTool)
//  Created on     :  04/2/2002 (UNH)
//  Initial Authors:  Maurik Holtrop (UNH) Gagik Gavalian (UNH) 
//
////////////////////////////////////////////////////////////////////////////////
//
//

#ifndef __TClasTool__
#define __TClasTool__

// Turns on or off safety checks and warnings at compile time.

#ifndef NOSAFE
#define READER_SAFE_CHECK    if(Check_Reader_Defined())
#else
#define READER_SAFE_CHECK
#endif


// GSIM bank wrinting enabled

#define WRITE_GSIM

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
#include "TFile.h"
#include "TGFileDialog.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TMatrix.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TRotation.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TMath.h"
#include "TH1.h"
#include "TRandom.h"
#include "TString.h"
#include "TObjString.h"

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
#include "TEPICClass.h"

// GSIM Bank 

#ifdef WRITE_GSIM
#include "TGSIMClass.h"
#endif

#include "TVERTClass.h"
#include "TMVRTClass.h"
#include "TTBERClass.h"


#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"

#include "TVirtualReader.h"
#include "TDSTReader.h"
// #include "TNT10Reader.h"  Probably should never want this included...

#include "TClasTool_Const.h"

//#include "TCounter.h"
//#include "TCounterCol.h"

///////////////////////////////////////////////////
//
///////////////////////////////////////////////////

namespace ClasTool{

  Int_t    GetTypeFromPid(Int_t pid);
  Int_t    GetPidFromType(Int_t type);
  Float_t  GetPartMassID(Int_t pid);
  Float_t  GetPartMassIdx(Int_t idx);
  Int_t    GetPartChargeID(Int_t pid);
  Int_t    GetPartChargeIdx(Int_t idx);
  const char *GetPartNameIdx(Int_t idx);
  const char *GetPartShortNameIdx(Int_t idx);
  const char *GetPartName(Int_t pid);
  const char *GetPartShortName(Int_t pid);
  const char *GetPartSymbol(Int_t pid);
  const char *GetPartSymbolIdx(Int_t idx);

  static const Float_t fgParticle_Mass[]=  // Masses of particles.
    {
      0.,               // kUnknown
      5.10998902e-04,	// kElectron 
      5.10998902e-04,	// kPositron 
      0.0,   	        // kPHOTON     
      0.13957018,	// kPion_Plus  
      0.13957018,	// kPion_Minus 
      0.493677,	        // kKaon_Plus  
      0.493677,	        // kKaon_Minus 
      0.93827200,	// kProton     
      0.93956533,	// kNeutron    
      1.875612762,	// kDeuteron   
      2.8092,	        // kHe3        
      3.7274            // kHe4       
    };

  static const Int_t fgParticle_Charge[]=  // Charges.
    {
      0,               // kUnknown
      -1,	// kElectron 
      +1,	// kPositron 
      0,   	        // kPHOTON     
      +1,	// kPion_Plus  
      -1,	// kPion_Minus 
      +1,	        // kKaon_Plus  
      -1,	        // kKaon_Minus 
      +1,	// kProton     
      0,	// kNeutron    
      +1,	// kDeuteron   
      +2,	        // kHe3        
      +2            // kHe4       
    };

  static const Int_t   fgParticle_Id[]=   // Id's of particles.
    {
      kUnknown_Id,
      kElectron_Id,
      kPositron_Id,
      kPhoton_Id,
      kPion_Plus_Id,
      kPion_Minus_Id,
      kKaon_Plus_Id,
      kKaon_Minus_Id,
      kProton_Id,
      kNeutron_Id,
      kDeuteron_Id,
      kHe3_Id,
      kHe4_Id};

  static const char fgParticle_Name[][13] =
    {
      "Unknown",
      "Electron",
      "Positron",
      "Photon",
      "Pion_Plus",
      "Pion_Minus",
      "Kaon_Plus",
      "Kaon_Minus",
      "Proton",
      "Neutron",
      "Deuteron",
      "Helium3",
      "Helium4" };      

  static const char fgParticle_ShortName[][13] =
    {
      "Unkn",
      "Elec",
      "Pos",
      "Phot",
      "Pip",
      "Pim",
      "Kp",
      "Km",
      "Prot",
      "Neut",
      "Deut",
      "He3",
      "He4" };      

  static const char fgParticle_Symbol[][13] =
    {
      "?",
      "e^{-}",
      "e^{+}",
      "#gamma",
      "#pi^{+}",
      "#pi^{-}",
      "K^{+}",
      "K^{-}",
      "P",
      "N",
      "D",
      "He^{3}",
      "He^{4}"};

}


class TClasTool : public TObject{
 public:
  
  TVirtualReader  *fReader; // This is a pointer to the actual reader used.
  Int_t fDebug_Mode;        // Sets the verbosity of the code. 

  
 public:
  
  TClasTool();
  virtual ~TClasTool();
                        
  Int_t          Add(const Char_t *filename); // Add files to the chain in the VirtualReader.
  Int_t          AddFile(const Char_t *filename); // Add a file to the chain in the VirtualReader.
  Int_t          AddEPICFile(const char *filename, Int_t nentries); //Add a file to the EPIC chain
  Int_t          Check_Reader_Defined();      // Check if Reader is ok.
  Int_t          Correct_ECPB_bank(TEVNTClass *e); // Correct erroneous ECPB entries.
  Int_t          Correct_ECPB_bank(TECPBClass *eco); // Correct erroneous ECPB entries.
  TObject       *GetBankRow(const Char_t *bankname,Int_t nrow);
  Int_t          GetCurrentEvent();
  Double_t       GetEntries();
  Double_t       GetEntriesFast();
  Float_t        GetEPICValue(const char* fName); //return EPIC value corresponding to fName
  TEPICClass    *GetEPICClass(); //return the current EPICClass. Only gets the currently selected EPIC, to ensure that this is the one corresponding to the current phys event call GetEPICValue
  Int_t          GetEntry(Int_t entry=-1,Int_t getall=0); 
  Int_t          GetEventNumber();
  THEADERClass   *GetHEADER();
  Int_t          GetHelicity();
  void           GetInvariants(Float_t *Q2, Float_t *W2);
  Int_t          GetNFiles();
  TObject       *GetNotify();
  Int_t          GetNPart();
  Int_t          GetNRows(const Char_t *bankname="EVNT"); // return number of items in bank.
  Int_t          GetPartID(Int_t indx);
  Int_t          GetPartCharge(Int_t indx);
  TVector3       GetPart3Vector(Int_t indx);
  TLorentzVector GetPart4Vector(Int_t indx);
  TVector3       GetPartVertex(Int_t indx);
  TVERTClass    *GetVert(Int_t part1,Int_t part2);
  TVirtualReader *GetReader(void);            // Get pointer to reader
  TChain        *GetTree(Char_t *treename="EVNT"); // Get the actual tree from reader
  Int_t          InitDSTReader(const Char_t *readertype="ROOTDSTR"); // init reader.
  Int_t          InitDSTReader(TVirtualReader *reader); // init reader.
  Int_t          Next();             // Get the next event.
  void           Print(Int_t full=0);            // Print information about the current reader.
  void           PrintEventStatus();
  void           PrintEPICPosition(); //Prints the position of the currently selected EPIC in terms of event and run numbers
  void           SetNotify(TObject *Notify);
  void           SetNoScalers();
  //
  //
  //  Local Functions
 
  void        SetBeamEnergy(Float_t fbm){fEBeam=fbm;};
  Float_t     GetBeamEnergy(){return(fEBeam);};

  // 
  // Inlines.
  //
  TEVNTClass    *GetEVNT(Int_t nrow){return (TEVNTClass *)GetBankRow("EVNT",nrow);}
  TDCPBClass    *GetDCPB(Int_t nrow){return (TDCPBClass *)GetBankRow("DCPB",nrow);}




 protected:

  Float_t     fEBeam;                  // Beam energy. Set with SetBeamEnergy().
  Int_t       isReaderDefined;         // True is reader is initialized.

  TVERTClass* Vert_Error_Handler(Int_t NRows,Int_t track1, Int_t track2);


  ClassDef(TClasTool,2) // Main class for ClasTool package, drives everything else.

};

#endif

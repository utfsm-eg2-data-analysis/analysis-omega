//=================================================================
//  TVirtualReader is a calss implements general functions for reading any DST
//  format. This class can be inherited.
// ________________________________________________________________
//
//   Author : G.Gavalian & Maurik Holtrop (UNH) 04/02/2002
//  
//

#ifndef __TVIRTUAL_READER__
#define __TVIRTUAL_READER__

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TString.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TFile.h"
#include "TGFileDialog.h"
#include "TTree.h"
#include "TClonesArray.h"
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
#include "TTGBIClass.h"
#include "TEPICClass.h"
#ifdef __USE_MYSQL__
#include "TSQLServer.h"
#include "TSQLRow.h"
#include "TSQLResult.h"
#endif

// How nice "they" changed their mind about this one.
//
// See http://root.cern.ch/root/html402/examples/V4.02.txt.html
// Entry: 2004-07-29 12:54  brun
#if ROOT_VERSION_CODE >= ROOT_VERSION(4,01,99)
#define GetEntries_return_t  Long64_t
#else
#define GetEntries_return_t  Double_t
#endif

// GSIM Bank 
#ifdef WRITE_GSIM
#include "TGSIMClass.h"
#endif

#include "TVirtualReader.h"

#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"



enum Reader_Return_Codes { kNextEvent = 1,  // Ok to get next event. 
		    kNOERR =  0,   // All error codes are < 0.
		    kERR   = -1,   // Generic error.
		    kERR_end_of_file = -2,  // Next reached end of file. 
		    kERR_No_Electron = -3,  // No electron in event.
		    kERR_File_Not_Found= -4,// Generic file not found.
		    kERR_Invalid_Runnum= -5,// No runnum available in data set.
		    kERR_Invalid_Evtnum= -6,// No evtnum available in data set.
		    kERR_End_Of_Scaler_Seq=-7,// End of scaler sequence, stop reading here.
		    kERR_Scaler_Seq_Skip=-8// Scaler skip, go forward to next file.
};


enum ReaderBits{   kBit0 = 1 << 0,  //   1
	      kBit1 = 1 << 1,  //   2
	      kBit2 = 1 << 2,  //   4
	      kBit3 = 1 << 3,  //   8
	      kBit4 = 1 << 4,  //  16
	      kBit5 = 1 << 5,  //  32
	      kBit6 = 1 << 6,  //  64
	      kBit7 = 1 << 7,  // 128
	      kBit8 = 1 << 8,  // 256
	      kBit9 = 1 << 9,  // 512
	      kBit10 = 1 << 10, // 1024
	      kBit11 = 1 << 11,
	      kBit12 = 1 << 12,
	      kBit13 = 1 << 13,
	      kBit14 = 1 << 14,
	      kBit15 = 1 << 15,
	      kBit16 = 1 << 16,
	      kBit17 = 1 << 17,
	      kBit18 = 1 << 18,
	      kBit19 = 1 << 19,
	      kBit20 = 1 << 20,
	      kBit21 = 1 << 21,
	      kBit22 = 1 << 22,
	      kBit23 = 1 << 23,
	      kBit24 = 1 << 24,
	      kBit25 = 1 << 25
};

enum Reader_DEBUG_Bits { kDBG_Error  = kBit0, // Error messages.
		  kDBG_Info   = kBit1, // Info messages.
		  kDBG_Debug  = kBit2, // Basic Debug messages= level 1 debug
		  kDBG_Debug1 = kBit2, // Basic Debug messages= level 1 debug
		  kDBG_Debug2 = kBit3,  // Basic Debug messages= level 2 debug
		  kDBG_Debug3 = kBit4   // Basic Debug messages= level 3 debug
};


class TVirtualReader : public TObject{

 public:

  Int_t   fDebug_Mode;  // Defines printout, Bit 0 = STD Messages, Bit 1 = Errors, Higherbits = Debug
  //
  Int_t   fCurrentEvent;  // Current Data Event (for use with Next() )
  Int_t   fCurrentScaler; // Current Scaler Event (for use with NextScaler() )
  Int_t   fScalerLastEvt; //to synchronize Event tree and Scaler tree this contain the event number of the last Physics Event. Set by SetBranchAddress
  Bool_t  fReadScaler;    // Turn on or off the automatic reading of scaler branch. Default is on.
  Bool_t  fReadMCHD;      // Turn on or off the reading of the MCHD bank.
  Bool_t  fReadGSIM;      // Turn on or off the reading of the GSIM bank.
  Bool_t  fUseGSIM;       // When set true, read the GSIM bank INSTEAD of the EVNT bank.

  static Int_t  fgInstanceCount; // Total instance count.
  Int_t fThisInstance;  // Instance count of this instance.

//========================================================================

 public:

  TVirtualReader();
  ~TVirtualReader();
                                                                                        
  virtual  Int_t     Add(const Char_t *filename); // Add a data file to the chain
  virtual  Int_t     AddFile(const Char_t *filename,Int_t nentries=TChain::kBigNumber);
                                                  // Add a data file to the chain
  virtual  Int_t     AddEPICFile(const Char_t *filename, Int_t nentries); //add an EPIC file to the chain
  virtual  void      Browse(TBrowser *b);
  virtual  Int_t     Draw(const char *varexp, const char *selection, Option_t *option="",Int_t nentries=1234567890, Int_t firstentry=0); // *MENU*
  virtual  TObject  *GetBankRow(const Char_t *bankname,Int_t nrow);
  virtual  Int_t     GetCurrentEvent();
  virtual  GetEntries_return_t  GetEntries() const;              // Return total number of entries in chain.
  virtual  GetEntries_return_t  GetEntriesFast() const;          // Return total number of entries in chain.
  virtual  Int_t     GetEntry(Int_t entry=-1,Int_t getall=0); // Get specific entry.
  virtual  Float_t   GetEPICValue(const Char_t *fName); //Get specified epic value
  virtual  TEPICClass *GetEPICClass();   //return current EPIC
  virtual  Int_t     GetEventNumber();
  virtual  TObjArray *GetFiles(void);
  virtual  THEADERClass *GetHEADER();    // return the HEADER class.
  virtual  Int_t     GetHelicity();
  virtual  Int_t     GetNFiles();                     // Return the number of files in the chain.
  virtual  TObject  *GetNotify(void){return NULL;}; // Get the notify class.
  virtual  Int_t     GetNPart();                      // Returns number of particles in event
  virtual  Int_t     GetNRows(const Char_t *bankname="EVNT");
  virtual  Int_t     GetNtrees(void);
  virtual  TVector3  GetPart3Vector(Int_t indx);        // Get 3 Vector of Particle in indx-th row
  virtual  Int_t     GetPartCharge(Int_t indx);             // Get Particle ID from indx-th row
  virtual  Int_t     GetPartID(Int_t indx);             // Get Particle ID from indx-th row
  virtual  TVector3  GetPartVertex(Int_t indx);         // Get Vertex vector (uncorrected)
  virtual  TString   GetReaderType();                 // Returns the reader type
  virtual  Int_t     GetRunNumber();    
  virtual  TChain   *GetTree(Char_t *treename="EVENT"); // return TChain pointer.
  virtual  Int_t     GetTreeNumber(void);  // Get current tree number.
  virtual  Int_t     Next();                          // Read next event from chain
  virtual Bool_t     Notify();      // Call the notify.
  virtual  void      Print(Int_t full=0); // Print information.
  virtual  void      PrintEventStatus();
  virtual  void      PrintEPICPosition();
  virtual  Int_t     ReadEvent(Int_t event,Int_t runnum=0); // Get a specific event.
  virtual  void      Reset();                         // Closes all files and resets all counters to 0
  virtual  void      SetNotify(TObject *obj);      // Set the notify class to be notified.

  inline   Int_t     SetDebugMode( Int_t mode ) { return ( fDebug_Mode = mode ); }

  ClassDef(TVirtualReader,1) // Virtual base class for all reader implementations.

};

#endif

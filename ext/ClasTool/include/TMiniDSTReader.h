//=================================================================
//  TDSTReader is a calss implements tools for Reading ROOT DST's
//  without any run group specific details. 
//  It will contain tools only to read EVENT and Scaller trees.
// 
// ________________________________________________________________
//
//   Author : G.Gavalian (UNH) 04/02/2002
//  
//

#ifndef __TMINIDST_READER__
#define __TMINIDST_READER__

//#define WRITE_GSIM

// Standart Includes 

#include <iostream>
using namespace std;

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
#include "TVector2.h"
#include "TVector3.h"
#include "TRegexp.h"
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

#include "TMiniHEADClass.h"
#include "TMiniDSTClass.h"

#include "TVirtualReader.h"


class TMiniDSTReader : public TVirtualReader{
  
 public:


  TChain        *fEventChain;    // Chain of files with data. TTree points to CLASEVENT 
  TMiniHEADClass  *fEvntHeader;    // Event Header pointer
  TMiniDSTClass *fPElectron;      // Electron
  TMiniDSTClass *fPProton;        // Proton
  TClonesArray  *fcaPARTStore;   // Clones Array for EVNT bank
  TClonesArray  *fcaGSIMStore;   // Clones Array for GSIM bank
  Int_t          fCurrentEvent;
  //=========================================================================================
  // Constructor and Distructor
  //=========================================================================================

  TMiniDSTReader();   // Default Constructor.
  virtual ~TMiniDSTReader(); // Default Destructor.

  //=========================================================================================
  // Initialization routines
  //=========================================================================================

  void  InitClones();         // Initialize the TClonesArray's for retreiving data.
  void  CleanEventClones();   // Clean the TClonesArray's before getting next event.
  void  InitBranches();       // Initialize the branch addresses for all the data members.

  //=========================================================================================
  // Initialization routines
  //=========================================================================================
  // Int_t    GetEventNumber();
 Int_t    GetRunNumber();
  virtual Int_t    Add(const Char_t *name);
  virtual Int_t AddFile(const Char_t *filename); // Add a data file to the chain
  virtual Int_t Next();                          // Read next event from chain
  virtual Int_t ReadNext();                      // Read next event from chain

  Int_t         ReadEvent(Int_t evtnum);         // Read Event number evtnum from the ROOT Tree.
  virtual Bool_t Notify();                       // Hook that will be notified when a new file is opened by the TChain.
  Int_t   GetNFiles();                           // Return the number of files in the chain.
  virtual void  Reset();
  TChain  *GetChain(char *which="Event"){return fEventChain;};
  Int_t     GetChainEntries();
  Int_t     GetEntries(){return GetChainEntries();};
  Int_t     GetNPart();                      // Returns number of particles in event
  TVector3  GetPart3Vector(int indx);        // Get 3 Vector of Particle in indx-th row
  TVector3  GetPartVertex(Int_t indx);
  Int_t     GetPartID(int indx);             // Get Particle ID from indx-th row
  Int_t     GetPartCharge(int indx);             // Get Particle ID from indx-th row
  TString   GetReaderType();                 // Returns the reader type
  Int_t     GetHelicity();
  //=========================================================================================
  //  Bank manipulation routines
  //=========================================================================================
  Int_t     GetEventNumber();
  Int_t     GetNRows(const Char_t *bankname="EVNT");
  TObject  *GetBankRow(const Char_t *bankname,Int_t nrow);
  
  //=========================================================================================
  //  Printout various statistics
  //=========================================================================================

  void  PrintEventStatus();   // Print the status of the current event.
  void  PrintSummary();       // Print a summary of the statistics for this run.  

  ClassDef(TMiniDSTReader,1) // Example of a limited DST that takes less space (reader).
};

inline Int_t TMiniDSTReader::GetNFiles(){
 return(((TObjArray *)fEventChain->GetListOfFiles())->GetEntries());
}

inline void TMiniDSTReader::Reset(){
  // Set the fCurrentEvent and the fCurrentScaler to 0.
  // Thus the next Next() call will start reading at the beginning of the 
  // current Chain of data files.
  fCurrentEvent=0;
}

#endif

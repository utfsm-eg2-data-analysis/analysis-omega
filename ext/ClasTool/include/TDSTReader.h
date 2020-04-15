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

#ifndef __TDST_READER__
#define __TDST_READER__

#define WRITE_MCHD
#define WRITE_GSIM
#define WRITE_PHOTON
#define WRITE_VERTEX
#define WRITE_TBER
#define WRITE_TGBI

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
#include "TRegexp.h"
#include "TChain.h"
#include "TFile.h"
#include "THashList.h"
#include "TGFileDialog.h"
#include "TTree.h"
#include "TClonesArray.h"
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
// Base class.
//
#include "TVirtualReader.h"
//
// CLAS Banks Includes
//

#include "THEADERClass.h"
#include "TEVNTClass.h"
#include "TECPBClass.h"
#include "TSCPBClass.h"
#include "TDCPBClass.h"
#include "TCCPBClass.h"
#include "TICPBClass.h"
#include "TICHBClass.h"
#include "TFBPMClass.h"
#include "TLCPBClass.h"
#include "THEADClass.h"
#include "TTGBIClass.h"
#include "TEPICClass.h"

// Photon Banks
#include "TSTPBClass.h"
#include "TTGPBClass.h"
#include "TTAGRClass.h"


// GSIM Bank 
#include "TMCHDClass.h"

#include "TGSIMClass.h"
#include "TVERTClass.h"
#include "TMVRTClass.h"
#include "TTBERClass.h"

//
// Scaler Banks
//
#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"

// Storage helper class.
#include "TStoreClone.h"

class TDSTReader : public TVirtualReader{
  
  private:

  // Data specific to a ROOT DST file.

  THEADERClass *fEvntHeader;   // Event Header pointer
  THEADClass   *fScalerHead;   // Scaler Event Header pointer
  TEPICClass   *fEPIC;         // EPICClass pointer

  THashList fClones;          // Store pointers to TClonesArray of main data
  THashList fScalerClones;    // Store pointers to TClonesArray of scalers.

  TChain *fEventChain;    // Chain of files with data. TTree points to CLASEVENT 
  TChain *fScalerChain;   // Chain of files with data. TTree points to SCALER
  TChain *fEPICChain;     // Chain of files with data. TTree points to CLASEPIC

  Int_t fCurrentEPIC;  // Keeps track of position in EPIC bank.Perhaps should be in TVirtualReader?
  TArrayI *EPICTable;   // Table storing the last physics event before each EPIC. Used in GetEPICValue

 public:

  TDSTReader();   // Default Constructor.
  ~TDSTReader(); // Default Destructor.
  TDSTReader( const TDSTReader& reader );  // Copy Constructor

  Int_t   Add( const Char_t *filename );     // Add data files to the chain, using wildcards.
  Int_t   AddFile(const Char_t *filename);   // Add a data file to the chain
  Int_t   AddFile(const Char_t *filename,Int_t nentries); // Add a data file to the chain
  Int_t   AddEPICFile(const Char_t *filename,Int_t nentries); // Add an Epics file to the EPICChain
  void    CleanEventClones();   // Clean the TClonesArray's before getting next event.
  void    CleanScalerClones();  // Clean the scalar TClonesArray's before getting next scalar event.
  void    InitClones();         // Initialize the TClonesArray's for retreiving data.
  void    InitBranches();       // Initialize the branch addresses for all the data members.
  void    InitEPICBranch();     // Initialize the branch address for the EPIC branch.

  void     MakeEPICTable();      //Builds the table used to reference which EPIC belongs with which Physics
  Float_t  GetEPICValue(const char* fName); //Return the EPIC value corresponding to fName
  TEPICClass *GetEPICClass(){return(fEPIC);}; //Return the current EPIC. This does not check to see if the current EPIC corresponds to the current physics event, to make sure it is the "right" EPIC call GetEPICValue before calling this.
  TObject  *GetBankRow(const Char_t *bankname,Int_t nrow);
  TChain  *GetChain(char *which="Event"); // Return the Chain requested ("Event"=default, "Scaler")
  Int_t    GetCurrentEvent();
  Int_t    GetEntry(Int_t entry=-1, Int_t getall=0); // Return entry numbered "entry".
  GetEntries_return_t GetEntries() const;                // Get the number of events in the chain.
  GetEntries_return_t GetEntriesFast() const;            // Same as GetEntries, but use previously stored value (much faster.)
  Int_t    GetEventNumber();
  THEADERClass *GetHEADER(){return(fEvntHeader);};            // Return the HEADER.
  Int_t    GetHelicity();               // Return the event helicity bit.
  Int_t    GetNFiles();                 // Return the number of files in the chain.
  Int_t    GetNPart(){ return ( fEvntHeader->GetNPGP() % 100 ); };     // Returns number of particles in event

  Int_t    GetNRows(const Char_t *bankname="EVNT");
  TVector3 GetPart3Vector(Int_t indx);    // Get 3 Vector of Particle in indx-th row
  Int_t    GetPartID(Int_t indx);         // Get Particle ID from indx-th row
  Int_t    GetPartCharge(Int_t indx);     // Get Particle ID from indx-th row
  TVector3 GetPartVertex(Int_t indx);     // Get the vertex vector for particle at indx-th row.
  TString  GetReaderType();             // Returns the reader type
  Int_t    GetRunNumber();

  TStoreClone *GetStoreClone(const Char_t *bankname);
  TClonesArray *GetClone(const Char_t *bankname);

  TChain   *GetTree(Char_t *treename="EVNT"); // Return the TTree.
  Int_t   GetTreeNumber(void){return(fEventChain->GetTreeNumber());}; // Return the number of the current tree.

  Int_t   Next();                          // Read next event from chain
  Bool_t  Notify();                    // Hook that will be notified when a new file is opened by the TChain.
  void    Print(Int_t full=0);  // Print information about the event. 
  void    PrintEventStatus();   // Print the status of the current event.
  void    PrintEPICPosition();    // Print the position of the current EPIC in terms of run and evt numbers
  void    Reset();                     // Reset everything

  ClassDef(TDSTReader,1) // A reader interface for ROOT files.
};

inline TStoreClone *TDSTReader::GetStoreClone(const Char_t *bankname){
  // Return a pointer to the requested TStoreClone object.
  
  TStoreClone *ptr=(TStoreClone *)fClones.FindObject(bankname);
  if(ptr == NULL){
    ptr=(TStoreClone *)fScalerClones.FindObject(bankname);
  }
  if(ptr == NULL){
    if(fDebug_Mode&kDBG_Error)cout << "TClasTool::GetStoreClone (ERROR): Bank \"" << bankname << "\" not found.."<< endl;
  }

  return(ptr);
}

inline TClonesArray *TDSTReader::GetClone(const Char_t *bankname){
  // Return a pointer to the requested TClonesArray object.  
  TStoreClone *ptr=(TStoreClone *)fClones.FindObject(bankname);
  if(ptr == NULL){
    ptr=(TStoreClone *)fScalerClones.FindObject(bankname);
  }
  if(ptr)return(*ptr->GetClonesArray());
  else{
    if(fDebug_Mode&kDBG_Error) cout << "TClasTool::GetClone (ERROR): Bank \"" << bankname << "\" not found.."<< endl;
    return(NULL);
  }
}

inline Int_t TDSTReader::GetNFiles(){
 return(((TObjArray *)fEventChain->GetListOfFiles())->GetEntries());
}

inline void TDSTReader::Reset(){
  // Set the fCurrentEvent and the fCurrentScaler to 0.
  // Thus the next Next() call will start reading at the beginning of the 
  // current Chain of data files.
  fCurrentEvent=0;
  fCurrentScaler=0;
  fCurrentEPIC=0;
}

inline TChain *TDSTReader::GetChain(char *which){
  if(which[0]=='S'){
    return(fScalerChain);
  }else{
    return(fEventChain);
  }
}
#endif

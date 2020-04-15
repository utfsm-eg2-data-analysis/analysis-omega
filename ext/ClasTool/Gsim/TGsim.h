/////////////////////////////////////////////////////////////////////////////////
//
//    Header File for TGsim Class 
//
//    Created: Maurik Holtrop UNH  Dec-7-2000
//
//  Modifications:
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __TGsim__
#define __TGsim__

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

// ROOT includes 

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TString.h"
#include "TVector2.h"
#include "TVector3.h"
#include "TRotation.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TMath.h"
#include "TH1.h"
#include "TRandom.h"

#define NBCS 700000         // Define the BOS space. This is a potential vulnerability. 
                            // See bosio/bcs.h and bosio/fpack.c

extern "C" {
#include "bos.h" // Include the bosio library function stubs etc.
#include "bosio.h"

/* bcs.h */
/* define a BOScommon data type */
 
  typedef struct {
    int junk[5];
    int iw[700000];
  } BOScommon;
  
  extern BOScommon bcs_;  /* The real thing is defined in bosio library. */
}  

// Define structures to interface with BOS.

#include "bosddl.h"
//
// Including TClasTool.h will include all the ClassBanks.
//
#include "TClasTool.h"
#include "TVirtualReader.h"
#include "TGSIMClass_const.h"

class TGsim : public TObject{

 public:
  static const Float_t fgGeant_Particle_Mass[kG_NParticleTypes];
  static const Int_t   fgGeant_Particle_Id[kG_NParticleTypes];
  static const char    *fgGeant_Particle_Label[kG_NParticleTypes];

  Int_t fDebug_Mode;
  Int_t fDesc_in;
  Int_t fDesc_out;
  TDatime fNow;

 public:
  TGsim();
  ~TGsim(){CloseFiles();};
  Int_t OpenFile(char *name,char *readwrite="r"); // Open a BOS file for reading "r" or writing "w".
  void CloseFiles(Int_t desc=0);  // Close all open BOS files, or file specified.
  Int_t WriteBOS(); // Write the current BOS array to file.
  Int_t ReadBOS();  // Read the next BOS array from file.
  void *CreateBank(char *name,Int_t nr,Int_t ncols=-1,Int_t nrows=1); // Create a named bank in the bos array.
  clasPART_t *FillPART(TGSIMClass *gsim, Int_t nr, Int_t nrow=0); // Fill PART at row nrow with the contends of TGSIMclass.
  clasPART_t *FillPART(TEVNTClass *evnt, Int_t nr, Int_t nrow=0); // Fill PART at row nrow with the contends of TEVNTclass.
  clasPART_t *FillPART(Int_t nr,Int_t nrow,Int_t pid,Int_t q,TVector3 *vert,TLorentzVector *mom,Float_t weight=1); // Fill PART
  void        FillMCTKPART(int  n_row, int  pid, int _charge,TVector3  _vrt, TLorentzVector _mom);

  clasHEAD_t *FillHEAD(THEADClass *head); // Fill HEAD bank from THEADClass.
  clasHEAD_t *FillHEAD(THEADERClass *head); // Fill HEAD bank from THEADERClass.
  clasHEAD_t *FillHEAD(Int_t runnum,Int_t evt_num); // Fill a new head bank with given params.
  Int_t CopyEvent(TVirtualReader *ea);  // Copy an event from ROOT to BOS (creates PART bank only).  
  Int_t BankFormat(const char *name,const char *format); // Define format of BOS bank.
  char *FixName(const char *name);
  void *GetBank(const char *name,Int_t nr); // Find a bank in the BOS array.

  Int_t GetEvtNum();
  Int_t GetRunNum();
  Int_t GetPartId(Int_t nr=0,Int_t nrow=0);
  Float_t GetPartQ(Int_t nr=0,Int_t nrow=0);
  TVector3 GetPartVert(Int_t nr=0,Int_t nrow=0);
  TLorentzVector GetPartP4(Int_t nr=0,Int_t nrow=0);

  Bool_t IsMCEvent(Int_t itype=0); // Return True if event is MC type of itype.
  Bool_t IsDataEvent(Int_t itype=2); // Return True if event is Data type of itype.

  void PrintHead(); // Print the head bank.
  void PrintPart(Int_t nr=0,Int_t ncol=-1); // Print PART bank.
  Int_t Geant_to_PDG(Int_t pid); // Convert a GEANT PID to a PDG PID.
  Int_t PDG_to_Geant(Int_t pid); // Convert a PDG PID to a GEANT ID.
  Float_t GetPartMassFromPid(Int_t pid); // Get the mass of particle given the PDG PID
  Float_t GetPartMassFromIndex(Int_t indx); // Get the mass of particle given the index=GEANT ID.
  ClassDef(TGsim,1) // A class for interfacing to the Monte Carlo.
};

#endif

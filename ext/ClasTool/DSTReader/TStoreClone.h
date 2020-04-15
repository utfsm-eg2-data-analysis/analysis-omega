// Helper Class for storing pointers to TClonesArray
// 
#ifndef __TStoreClone__
#define __TStoreClone__

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>

// ROOT includes 

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TObjString.h"
#include "TString.h"
#include "TRegexp.h"
#include "TChain.h"
#include "TFile.h"
#include "TGFileDialog.h"
#include "TTree.h"
#include "TClonesArray.h"


class TStoreClone : public TObjString {
  
 public:
  TClonesArray *fCloneArr;

 public:
  TStoreClone(){};
  ~TStoreClone(){
    // Clear and delete TClonesArray, then self.
    fCloneArr->Clear();delete fCloneArr;
  };

  TStoreClone(const char *name, const char *cl, Int_t num){
    // Create and initialize with a new TClonesArray.
    fCloneArr = new TClonesArray(cl,num);
    SetString(name);
  };

  TStoreClone(const char *name,TClonesArray *ptr){
    // Create and initialize with TClonesArray pointer.
    SetString(name);
    fCloneArr = ptr;
  };


  TStoreClone(TStoreClone& tc){
    // Copy Constructor.
    // NOTICE: This does NOT copy the contends of the TClonesArray, it only creates a 
    // new TClonesArray of the same type, which will be empty.
    //
    // fCloneArr = new TClonesArray( (*tc.fCloneArr) );
    fCloneArr = new TClonesArray(tc.fCloneArr->GetName(),tc.fCloneArr->GetSize());
    SetCloneName(  tc.GetCloneName() );
  };

  void  SetCloneName(const char *name){SetString(name);};
  const char* GetCloneName(){return String().Data(); };
  
  TClonesArray **GetClonesArray(){return &fCloneArr;};

  void Clear(){if(fCloneArr)fCloneArr->Clear();};
  void Delete(){if(fCloneArr)fCloneArr->Delete();};
  Int_t GetEntries(){if(fCloneArr)return(fCloneArr->GetEntries());
    else return(-1);};

  ClassDef(TStoreClone,1) // Small object to aid storing TClonesArray pointers in TObjArray
};

#endif

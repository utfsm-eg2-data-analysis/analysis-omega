#ifndef __TRUNINDEX__
#define  __TRUNINDEX__

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

// ROOT includes

#include "TROOT.h"
#include "TObject.h"
#include "TString.h"



class TRunIndex : public TObject{

public:

Int_t    fRunIndexId;
Int_t    fMinRun;
Int_t    fMaxRun;
Int_t    fItemId;
Int_t    fItemValueId;
TString  fOfficer;
TString  fTime;
TString  fComment;


TRunIndex();

TRunIndex(Int_t fpRunIndexId,Int_t    fpMinRun,
          Int_t    fpMaxRun,  
          Int_t    fpItemId,
          Int_t    fpItemValueId,
          const char *fpOfficer,
          const char *fpTime,
          const char *fpComment);

virtual ~TRunIndex();

void Set(Int_t fpRunIndexId,Int_t    fpMinRun,
         Int_t    fpMaxRun,  
         Int_t    fpItemId,
         Int_t    fpItemValueId,
         const char *fpOfficer,
         const char *fpTime,
         const char *fpComment);

void  Print(void){ 
  // Just say hello.
  cout << "TRunIndex .... ;-)\n";};

//
// This routines return lists of variables 
// to include in QUERYES
//

// const char *Value_List();
// const char *Equal_List();


ClassDef(TRunIndex,1) // Class for Map Item Value Description

};

#endif

#ifndef __TDBITEM__
#define  __TDBITEM__

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

// ROOT includes

#include "TROOT.h"
#include "TObject.h"
#include "TString.h"


class TDBItem : public TObject{

public:

 Int_t    fItemId; // Item ID corresponding to Subsystem ID
 TString  fItemName; // Item Name
 Int_t    fSubsystemId; // Subsystem ID
 Int_t    fLength;      // Item Array Length
 TString  fType;        // Item Type 
 TString  fDescription; // Item Description

 TDBItem();
 virtual ~TDBItem();

 void Print();

 ClassDef(TDBItem,1) // Class to keep Map Item information
};



#endif

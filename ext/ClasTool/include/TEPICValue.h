/////////////////////////////////////////////////////////////////
//
// Author: Will Morrison UNH
//         6/2005
//
// Container Class for TEPICClass
// This is meant to be a generic container for EPICs that can
// be stored in an array just as the EPICs are in the BOS file.
// TEPICValue's are sortable alphabetically by fName.
//
// Modified:
//
////////////////////////////////////////////////////////////////

#ifndef _TEPICValue_ 
#define _TEPICValue_ 
#include <iostream>
using namespace std;
#include "TObject.h"
#include "TString.h"
#include "TVector3.h"
#include "TMath.h"
#include "TList.h"


class TEPICValue:public TObject{

 public:  
  TString fName;
  Float_t fValue;
  
 public:

  TEPICValue(){};
  TEPICValue(const char* name,Float_t val){fName = name;
                                           fValue = val;};
  TEPICValue(TEPICValue *tmp);
  virtual ~TEPICValue(){};

  const char* GetName() const {return fName;};                            //neccesary for Compare(TObject)
  Float_t GetValue() const {return fValue;};
  void SetValue(Float_t val){fValue = val;};
  void SetName(const char* name){fName = name;};
  void Resize(Ssiz_t size){fName.Resize(size);};
  Int_t CompareTo(const char* member){return (fName.CompareTo(member));}; // returns 1 if greater, 0 if ==, -1 if less than
  Int_t Compare(const TObject* obj) const;                                // overrides Compare(TObject) from TObject
  Bool_t IsSortable() const { return kTRUE; }

  void Print();

  ClassDef(TEPICValue,1) // Container for TEPICClass
    };


#endif

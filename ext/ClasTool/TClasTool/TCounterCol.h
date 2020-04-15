/////////////////////////////////////////////////////////////////////////////////
//
//  Header File for TCounterCol Class 
//
//-----------------------------------------------------------------------------
//
//  Documentation  : TCounterCol.html 
//  Created on     : 1999
//  Initial Author : Maurik Holtrop (UNH)
//
////////////////////////////////////////////////////////////////////////////////
//
//
// Modifications:
//
#ifndef __TCounterCol__
#define __TCounterCol__

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TString.h"
#include "TMath.h"

#include "TCounter.h"

class TCounterCol : public TObjArray {

 public:
  TCounterCol(){};
  virtual ~TCounterCol(){};
  
  Int_t AddCounter(TCounter *cc,Int_t loc= -1){   // Add a new TCounter to end of list, return entry number.
    if(loc<0){
      AddLast(cc);
    }else{
      AddAt(cc,loc);
    }
    return(IndexOf(cc));
  }          

  Int_t AddCounter(const char *name,Int_t loc= -1){ // Create a new TCounter to end with name, return entry number.
    TCounter *cc=new TCounter(name);
    return( AddCounter(cc,loc));
  }


  Bool_t Test(Bool_t test,Int_t i){
    //
    // Count a specific test (true/false), and pass back test.
    //
    if((TCounter *)At(i)){
      return( ((TCounter *)At(i))->Test(test));
    }else{
      cerr << "Missing Counter no: " << i << endl;
      return(test);
    }
  };

  Bool_t TestInv(Bool_t test,Int_t i){
    // Count the opposite of test, and pass back test.
    if((TCounter *)At(i)){
      return( !((TCounter *)At(i))->Test(!test));
    }else{
      cerr << "Missing Counter no: " << i << endl;
      return(test);
    }
  };

  Bool_t True(Int_t i){
    if((TCounter *)At(i)){
      return( ((TCounter *)At(i))->True());
    }else{
      cerr << "Missing Counter no: " << i << endl;
      return(1);
    }

  }  
  Bool_t False(Int_t i){
    if((TCounter *)At(i)){
      return( ((TCounter *)At(i))->False());
    }else{
      cerr << "Missing Counter no: " << i << endl;
      return(0);
    }

  }  

  void Browse(TBrowser *b);
  virtual Bool_t IsFolder() const { return kTRUE; }

  void  Print(void);
  void  Reset(void);
  void  SetCounterTitles(void);
  Int_t Write(const char *name=0, Int_t option=0, Int_t bufsize=0){
    this->SetCounterTitles();
    return(TObjArray::Write(name,option,bufsize));
  }

  

  ClassDef(TCounterCol,1) // A ClonesArray of counters.
 
};

#endif

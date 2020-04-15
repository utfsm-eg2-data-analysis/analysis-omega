/////////////////////////////////////////////////////////////////////////////////
//
//  Header File for TCounter Class 
//
//-----------------------------------------------------------------------------
//
//  Documentation  : TCounter.html 
//  Created on     : 1999
//  Initial Author : Maurik Holtrop (UNH)
//
////////////////////////////////////////////////////////////////////////////////
//
//
// Modifications:
//

#ifndef __TCounter__
#define __TCounter__

#include <iostream>
using namespace std;
#include "TROOT.h"
#include "TSystem.h"
#include "TBrowser.h"
#include "TObject.h"
#include "TString.h"
#include "TMath.h"

class TCounter : public TNamed {

 public:

  Int_t  fNumtrue;
  Int_t  fNumfalse;

 public:

  TCounter (){fNumtrue=0;fNumfalse=0;};
  TCounter (const char *name){fNumtrue=0;fNumfalse=0; SetName(name);SetTitle();};
  virtual ~TCounter(){};

  void SetTitle(){
    char tmpstr[256];
    const char *tmp= &tmpstr[0];

    if((fNumtrue + fNumfalse)==0){
      sprintf(tmpstr,"%-50s  T: %8d (%7.2f%%) F: %8d (%7.2f%%) Tot: %8d",GetName(),
	      fNumtrue ,-1.,
	      fNumfalse,-1.,
	      fNumtrue+fNumfalse);
    }else{
      sprintf(tmpstr,"%-50s  T: %8d (%7.2f%%) F: %8d (%7.2f%%) Tot: %8d",GetName(),
	      fNumtrue ,100.*Double_t(fNumtrue )/Double_t(fNumtrue+fNumfalse),
	      fNumfalse,100.*Double_t(fNumfalse)/Double_t(fNumtrue+fNumfalse),
	      fNumtrue+fNumfalse);
    }
    TNamed::SetTitle(tmp);
  }

  const char* GetTitle(){
    SetTitle(); // Refresh contents first.
    return(TNamed::GetTitle());
  }

  void Reset(){fNumtrue=0;fNumfalse=0;};

  Bool_t Test(Bool_t test){
    if(test){
      fNumtrue++;
    }else{
      fNumfalse++;
    }
    return(test);
  }

  Bool_t True(){
    fNumtrue++;
    return(1);
  }
  Bool_t False(){
    fNumfalse++;
    return(0);
  }
  
  Int_t GetTrues(){
    return(fNumtrue);
  }

  Int_t GetFalse(){
    return(fNumfalse);
  }

  void SetTrues(Int_t count){
    fNumtrue=count;
  }

  void SetFalse(Int_t count){
    fNumfalse=count;
  }

  void Browse(TBrowser *b){
    this->Print();
  }

  void Print(){
    cout << GetTitle() << endl;
  };

  // Bool_t IsSortable() const { return kTRUE; };
  Bool_t IsEqual(TObject *obj){
    TCounter *cmp= (TCounter *)obj;
    return( fName == cmp->fName ); };

  //Int_t  Compare(TObject *obj){
  //  TCounter *cmp= (TCounter *)obj;
  //  if     ( fName == cmp->fName ) return(0);
  //  else if( fName <  cmp->fName ) return(-1);
  //  else return(1);
  //};

  ClassDef(TCounter,1) // A Counter class for simple statistics.

};

#endif

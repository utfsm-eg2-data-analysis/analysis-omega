////////////////////////////////////////////////////////////////////////
// File TTAGRBank.h  
//
// Initial Author: Maurik Holtrop 9/2004
//
////////////////////////////////////////////////////////////////////////
#ifndef _TTAGRClass_ 
#define _TTAGRClass_ 
#include <iostream>
using namespace std;


#include "TObject.h"
#include "TString.h"

class TTAGRClass: public TObject{
  
 public:
  Float_t ERG;  // Energy of the photon in GeV
  Float_t TTAG; // Time of the photon has reconstructed in the Tagger
  Float_t TPHO; // Time of the photon after RF correction
  Int_t   STAT; // Status ( 7 or 15 are Good) other values have problems (see tag_process_TAGR.F) 
  Int_t   T_id; // T counter Id
  Int_t   E_id; // E counter Id
 public:
  TTAGRClass(){};
  TTAGRClass(TTAGRClass *TmpSTPB);
  virtual ~TTAGRClass(){};

  inline  Float_t GetEnergy()   { return ERG ; }
  inline  Float_t GetTagTime()  { return TTAG ; }
  inline  Float_t GetTagRF()    { return TPHO ; }
  inline  Int_t   GetStat()     { return STAT ; } 
  inline  Int_t   GetTid()      { return T_id ; }
  inline  Int_t   GetEid()      { return E_id ; }

  void 	 Print();
  //
  ClassDef(TTAGRClass,1) // Class for accessing the TGPB bank: Tagger
    };
#endif



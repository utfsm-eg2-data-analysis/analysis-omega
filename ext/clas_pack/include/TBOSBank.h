/*************************************************************

  Analysis software for TJNAF-CLAS collaboration.
  
  Initial authors : 
            T.Auger   SPhN-CEA-Saclay    october 1998
            E.Anciant        \\            \\

  check out cvs history for changes log.

*************************************************************/

#ifndef TBOSBank_
#define TBOSBank_
/* standard C lib */

#include <iostream.h>

/* ROOT needed classes definitions */
#ifndef __CINT__
#include "TObject.h"
#include "TString.h"
#endif

/* CLAS bank definitions */
extern "C" {
#include "ROOTtypes.h"
#include "bostypes.h"
/* bosddl.h is included in bostypes.h */
}

/*CLAS ROOT bos wrapper */
#include "TClasBOS.h"

/* BOS BANK wrapper to use clas BOS banks within root */

/*BOS bank header class to access the bank headers definitions*/

struct BankHeader_t {
  int ncol;
  int nrow;
  char name[4];
  int nr;
  int nextIndex;
  int nwords;
};

class TBOSBankHeader {
  
 protected:
  Int_t head; // -1 = not attached to bank, >=0 attached to a bank in memory
  BankHeader_t *bankptr;
  void* GetDataPtr();
  Int_t format;
  
 public:
  TBOSBankHeader();
  TBOSBankHeader(void *);
  ~TBOSBankHeader();
  BankHeader_t* Set(void *);

//----- BOS related method
  Int_t GetNCol();
  Int_t GetNRow();
  TString GetName();
  Int_t GetNr();
  Bool_t IsThere() {if((void*)bankptr) return kTRUE;
                    else return kFALSE;}
  Bool_t IsNotThere() {if((void*)bankptr) return kFALSE;
                    else return kTRUE;}
  Int_t GetNextIndex();
  Int_t GetNWords();
  Int_t Format();

//-------------- iterators;

  int First(); // return 1 if OK, 0 if no entries;
  int Next(); // return 1 if OK, 0 if already at end;
  int Previous(); // return 1 if OK, 0 if already at beginning;
  int IterIsSet(); // return 1 if initialised, 0 otherwise;
  int Last(); // return 1 if OK, 0 if no entries;

};


/* Generic CLAS bank class, the template inherits from the ClasBankHeader
class, each instance of the class will be created based upon the BOS bank
structure */

template <class TBankStruc> class TBOSBank : public TBOSBankHeader {
  TBankStruc *fStrucPtr;

 public:
  TBOSBank();
  TBOSBank(void*); // intialise the object using Set method
  ~TBOSBank();

  void* Set(void*); // attached the Object to the bank the pointer is pointing to.
  void Print(); // print content of the bank
  TBankStruc* GetRow(int);  // returns a pointers to the i-th row of the bank
  TBankStruc* operator[](int); // alias for GetRow
  void* operator=(void*); // alias for Set

//-------------- iterator;

  TBankStruc* Get(); // returns a dummy pointer if the iterator is not initialised,
		    // a pointer to the row the iterator is pointing to, otherwise.
};

#endif

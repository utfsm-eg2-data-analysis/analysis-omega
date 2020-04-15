
/*************************************************************

  Analysis software for TJNAF-CLAS collaboration.
  
  Initial authors : 
            T.Auger   SPhN-CEA-Saclay    october 1998
            E.Anciant        \\            \\

  check out cvs history for changes log.

*************************************************************/

#ifndef ROOT_TClasBOS_
#define ROOT_TClasBOS_

#ifndef __CINT__
#include "TNamed.h"
#include "TObjArray.h"
#include "TString.h"
#endif

class TClasBOS : public TNamed {
	Int_t init;
	Int_t *iw;
        Int_t *wiw;
	Int_t desc_in;
	Int_t desc_out;
	TObjArray *fList;
	TString filename_In;
	TString filename_Out;
	Int_t findex;
	Int_t recordnum;
        TClasBOS *myaddress;

// static members only used while using bcs and wcs array
//
	static TClasBOS *gTClasBOS; // check if a TClasBOS object is already attached to bcs
	static TClasBOS *gWork_TClasBOS; // check if a TClasBOS object is already attached to wcs
	static int *gwork_iw; // check if wcs is already initialised

public:
//
// general object management
//
	void Status(); // print some info about current status
	Int_t Init();
        virtual void       Browse(TBrowser *b);
        Bool_t             IsFolder() {return kTRUE;}

// file list management
//
	Int_t Add(char *); // add a file to the list of input
	void Clear();
//      void FileUp();
//      void FileDown();
//      TList *GetFileList();

// current file management
//
	Int_t Connect(char *); // open a bos/fpack file
	Int_t Open(char *);  // open new file 
	Int_t CloseFile(char *);
	Int_t Write();
	void Rewind(); // Rewind current file

// BOS array related management
//
	void PrintBank(char *name);
	void PrintBank(char *name,Int_t);
	void *GetBank(char *,Int_t nr=0); // Get bank by name and number
	Int_t GetNBank(char *name);
	Int_t GetNBank(char *name,Int_t);
	Int_t FormatBank(char *,char *);
	Int_t MakeBank(char *,Int_t,Int_t,Int_t);
	void DropBank(char *,Int_t);
	void Garbage();
	void DropAllBank(); // drop'em all
	void Dump(); // Dump the whole bos array of named banks
	void DumpBos(); // Dump the management bos array
	void DumpBosSystem(); // Dump the system bos array
        Int_t SearchFor(char *,Int_t max=10000000);  // search a bos/fpack file for the first occurence of a named bank
        void Skip(Int_t); // skip the number of events specified as argument
	Bool_t Next(); // read in next logical record

	TClasBOS();
	TClasBOS(const char*);
	~TClasBOS();
	ClassDef(TClasBOS,1) // CLAS bosio wrapper Class
};

#endif


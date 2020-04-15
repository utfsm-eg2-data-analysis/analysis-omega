///////////////////////////////////////////////////////////////////////
//
//    File  Write_ROOT_Tree.cc
//
//  Author :  Gagik Gavalian   UNH  11/15/1999
//            Maurik Holtrop   UNH  11/15/1999
//
//
/////////////////////////////////////////////////////////////////////
//Begin_Html <!--
/* -->
<h2>On adding new banks:</h2>

<ol>
<li> You need to add a new class in ClasBanks that defines the container
   for your bank. To write this, use the packages/bankdefs definition 
   of the bank. You must create a TXXXXClass.cc a TXXXXClass.h and a 
   TXXXXClassLinkDef.h file.

<li> Write a Fill_NEWBANK.cc file to fill this new bank from the BOS contends.
   This resides in the FillBank directory. (Makefile there will pick up the new banks.)

<li> Include the header from 1) into this file at Bank Include Files.

<li> Add a TClonesArray for the bank, a TBranch and a counter. Then go to the storing
   section and make sure they get stored (Just copy what was done for other banks.)
   Also add the Branch to Initialize_Branches (again, like other banks.) and Init_Clones
   and Clear_Clones. Be carefull with the BOS filling banks which "sector" to use!
<br>
At this point you will be able to write the bank into the ROOT DST.
<br>
<li> You probably also want to READ the bank. You need to modify the DSTReader and
   add the banks there (just like all the other banks) to be read from the file
   and make it available and show up in a PrintEventStatus().
</ol>

<HR>
<h3>Performance tweaking parameters:</h3>
<pre>
A number of #define statements can be used to compile (or ommit) parts of the code:

#define WRITE_SCALERS // Turn Scaler writing on.
#define WRITE_PHOTON  // Turn on Photon beam banks writing.
#define WRITE_MCHD    // Turn MCHD bank writing on
#define WRITE_GSIM    // Turn GSIM bank writing on
#define WRITE_VERTEX  // Turn on the VERT and MVRT bank 
#define WRITE_TBER    // Turn on the TBER tracking error matrix bank.
//#define WRITE_TGBI  // Turn writing of TGBI bank on.

Note:  Some of these, when compiled in can be controlled with command line arguments.
Note2: The same defines occur in TDSTReader class header to control reading of these classes.
</pre>

<HR>
<h2>  Recent changes:</h2>
<pre>
   07/06/2000 : Gagik Gavalian
 
     GSIM Bank is added to store information of GSIM input (PART 1 Bank)
     Write_ROOT_Dst.cc is changed to create GSIM branch and fill it if there
     is PART 1 bank in BOS DST. In order to obtain GSIM Bank one should compile code
     with -DWRITE_GSIM.

   9/2004 : Maurik Holtrop

      Added Photon capabilities.

   6/2005 : Maurik Holtrop

      Make the GSIM and PHOTON banks switchable on the command line.
      Added VERTEX routine banks: VERT and MVRT

   b/2005 : Maurik Holtrop
      Added the TBER tracking error matrix bank.

</pre>      
<HR>
<pre>
<!-- */
// --> End_Html
//////////////////////////////////////////////////////////////


// Performance tweaking parameters:

#define WRITE_SCALERS // Turn Scaler writing on.
#define WRITE_PHOTON  // Turn on Photon beam banks writing.
#define WRITE_MCHD    // Turn GSIM bank writing on
#define WRITE_GSIM    // Turn GSIM bank writing on
#define WRITE_VERTEX  // Turn on VERTEX bank writing 
#define WRITE_TBER    // Turn on the TBER bank, write the tracking error matrix.
#define WRITE_TGBI   // Turn on the TGBI bank writing


#define __BUFSIZE__  16384
#define __SCALER_BUFSIZE__ 1024
#define __COMPRESS__ 9
#define __MAXFILESIZE__ 2000000000  // Max file is about 2Gig.
////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;
#include <stdlib.h>
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TTree.h"
#include "TObject.h"
#include "TString.h"
#include "TClonesArray.h"
//////////////////////////////////
//    Bank Include Files ...
//////////////////////////////////
#include "THEADERClass.h"
#include "TVirtualData.h"
#include "TEVNTClass.h"
#include "TECPBClass.h"
#include "TSCPBClass.h"
#include "TDCPBClass.h"
#include "TCCPBClass.h"
#include "TLCPBClass.h"
#include "TICPBClass.h"
#include "TICHBClass.h"
#include "TFBPMClass.h"
#include "THEADClass.h"
#include "TGSIMClass.h"
#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"
#include "TTGBIClass.h"
#include "TSTPBClass.h"
#include "TTGPBClass.h"
#include "TTAGRClass.h"
#include "TVERTClass.h"
#include "TMVRTClass.h"
#include "TTBERClass.h"
#include "TMCHDClass.h"

//////////////////////////////////
//    BOSIO Include Files ...
//////////////////////////////////

extern "C" {
#define NBCS  700000
#include "bosio.h"
#include "bosfun.h"
  typedef struct boscommon {
    int junk[5];
    int iw[NBCS];
  } BOScommon;
  extern BOScommon bcs_;
}
#include "clasbanks.h"  // Include file for bankdef Library

/////////////////////////////////
// Fillbanks
////////////////////////////////
#include "FillBank.h"


#define PHYSICEVNT 2
#define SCALEREVNT 3

///////////////////////////////////////////////
//    Inmodule Funciotn Prototypes ...
///////////////////////////////////////////////

void Init_Clones();
void Clear_Clones();
void Print_Usage();
void Parse_Args(int *argc, char **argv);
void Initialize_Branches(TTree *tree,TTree *scaler_tree);
Int_t Exclusive_Flag(TClonesArray *loc_EVNTStore,Int_t nRows);

////////////////////////////////////////////////
//    Clones Array For BANKS ...
/////////////////////////////////////////////////

extern TSystem *gSystem;

TClonesArray *EVNTStore;
static  TClonesArray *fgEVNTStore;
TClonesArray *ECPBStore;
static  TClonesArray *fgECPBStore;
TClonesArray *SCPBStore;
static  TClonesArray *fgSCPBStore;
TClonesArray *DCPBStore;
static  TClonesArray *fgDCPBStore;
TClonesArray *CCPBStore;
static  TClonesArray *fgCCPBStore;
TClonesArray *LCPBStore;
static  TClonesArray *fgLCPBStore;
TClonesArray *ICPBStore;
static  TClonesArray *fgICPBStore;
TClonesArray *ICHBStore;
static  TClonesArray *fgICHBStore;

#ifdef WRITE_PHOTON
TClonesArray *STPBStore;
static TClonesArray *fgSTPBStore;
TClonesArray *TGPBStore;
static TClonesArray *fgTGPBStore;
TClonesArray *TAGRStore;
static TClonesArray *fgTAGRStore;
#endif

#ifdef WRITE_VERTEX
TClonesArray *VERTStore;
static TClonesArray *fgVERTStore;
TClonesArray *MVRTStore;
static TClonesArray *fgMVRTStore;
#endif

#ifdef WRITE_TBER
TClonesArray *TBERStore;
static TClonesArray *fgTBERStore;
#endif

#ifdef WRITE_TGBI
TClonesArray *TGBIStore;
static  TClonesArray *fgTGBIStore;
#endif

#ifdef WRITE_MCHD
TClonesArray *MCHDStore;
static  TClonesArray *fgMCHDStore;
#endif

#ifdef WRITE_GSIM
//
// GSIM simulation Banks
// If flag is set then Clonearray will be open 
// to store PART Bank from GSIM input.
//

TClonesArray *GSIMStore;
static  TClonesArray *fgGSIMStore;

#endif


#ifdef WRITE_SCALERS
TClonesArray *Scaler_HLSStore;
static  TClonesArray *fgScaler_HLSStore;
TClonesArray *Scaler_S1STStore;
static  TClonesArray *fgScaler_S1STStore;
TClonesArray *Scaler_TRGSStore;
static  TClonesArray *fgScaler_TRGSStore;
#endif

//
//

////////////////////////////////////////////////
//    Branch Declaration ...
/////////////////////////////////////////////////

THEADERClass *hHEADER;
TBranch *HEADERBranch;

// TARGET_INCLUDE4
TBranch *EVNTBranch;
Int_t nEVNT_Store;

TBranch *ECPBBranch;
Int_t nECPB_Store;

TBranch *SCPBBranch;
Int_t nSCPB_Store;

TBranch *DCPBBranch;
Int_t nDCPB_Store;

TBranch *CCPBBranch;
Int_t nCCPB_Store;

TBranch *LCPBBranch;
Int_t nLCPB_Store;

TBranch *ICPBBranch;
Int_t nICPB_Store;

TBranch *ICHBBranch;
Int_t nICHB_Store;

#ifdef WRITE_PHOTON

TBranch *STPBBranch;
Int_t nSTPB_Store;

TBranch *TGPBBranch;
Int_t nTGPB_Store;

TBranch *TAGRBranch;
Int_t nTAGR_Store;

#endif

#ifdef WRITE_VERTEX
TBranch *VERTBranch;
Int_t nVERT_Store;

TBranch *MVRTBranch;
Int_t nMVRT_Store;

#endif

#ifdef WRITE_TBER
TBranch *TBERBranch;
Int_t nTBER_Store;
#endif

#ifdef WRITE_TGBI
//////////////////////////////////////////////////////
//  TGBI

TBranch *TGBIBranch;
Int_t nTGBI_Store;
#endif

#ifdef WRITE_MCHD
TBranch *MCHDBranch;
Int_t nMCHD_Store;
#endif

#ifdef WRITE_GSIM
//
// GSIM Branch Will contain PART Banks
// from simulations
//

TBranch *GSIMBranch;
Int_t nGSIM_Store;
#endif


Int_t        Last_Evt_Num=0;  // Hold the event number of the last Physics event, 
// to store with Scaler Event
Int_t        Last_Key_Num=0;  // Hold the key of the last Physics event.

#ifdef WRITE_SCALERS

THEADClass *hScaler_HEAD;

TBranch *Scaler_LastEvtNumBranch; // Store last Physics event number.

TBranch *Scaler_HEADBranch;

TBranch *Scaler_HLSBranch;
Int_t nScaler_HLS_Store;

TBranch *Scaler_S1STBranch;
Int_t nScaler_S1ST_Store;

TBranch *Scaler_TRGSBranch;
Int_t nScaler_TRGS_Store;
#endif

//////////////////////////////////////////////////////////////
// Options Globals
//////////////////////////////////////////////////////////////
Int_t event_selection_flag;
Int_t quiet_flag;
Int_t debug_flag;
char  pOutputFileName[128];
Int_t nEventsWrite;
Int_t DO_MCHD_flag;
Int_t DO_GSIM_flag;
Int_t DO_PHOTON_flag;
Int_t DO_VERTEX_flag;
Int_t DO_TBER_flag;

int main(int argc, char **argv)
{
  TROOT write_tree("WriteRootDst","Program for creating the root DST from BOS files.");
  
  //
  //
  
  Int_t        comp  = __COMPRESS__;
  int          iostatus;
  int          iCount  = 0;
  int          filenum;
  char     bosFileName[256];
  int      bosFileHandle;
  TFile        *hFile;
  TTree        *tree;

#ifdef WRITE_SCALERS
  TTree *scaler_tree;
#endif

  TString *SFileTitle;
  int EventType;
  int OutFileSequence=0;

  //
  //  strcpy(pOutputFileName,"outfile.root");nEventsWrite = 10000000;

  hHEADER = new THEADERClass();
#ifdef WRITE_SCALERS
  hScaler_HEAD= new THEADClass();
#endif

  pOutputFileName[0]=0;
  nEventsWrite = 100000000;
  
  if(argc < 2){
    Print_Usage();
    exit(1);
  }
  
  Parse_Args(&argc,argv);
  if(argc==0){
    cout << "Please specify input file.\n\n";
    Print_Usage();
    exit(1);
  }
#ifdef WRITE_MCHD
  cout << " This Version supports MCHD Input banks. Status:"<<DO_MCHD_flag << endl;
#endif 
#ifdef WRITE_GSIM
  cout << " This Version supports GSIM Input banks. Status:"<<DO_GSIM_flag << endl;
#endif  
#ifdef WRITE_PHOTON
  cout << " This Version supports PHOTON Input banks. Status: "<<DO_PHOTON_flag << endl;
#endif
#ifdef WRITE_VERTEX
  cout << " This Version supports VERTEX Input banks. Status: "<<DO_VERTEX_flag << endl;
#endif
#ifdef WRITE_TBER
  cout << " This Version supports TBER Input banks. Status: "<<DO_TBER_flag << endl;
#endif

  SFileTitle = new TString("Root DST for: ");
  for(filenum=1;filenum<argc;filenum++){
    SFileTitle->Append(argv[filenum]);
    SFileTitle->Append(" ");
  }

  if( SFileTitle->Length() >= 255 ){
    SFileTitle->Remove(252);
    SFileTitle->Append(" ...");
  }

  if(pOutputFileName[0]==0){
    strncpy(pOutputFileName,argv[1],120); // Copy a max of 122 chars from first file name
    strcat(pOutputFileName,".root");
    if(!quiet_flag)cout << "Output file : " << pOutputFileName << endl;
  }
  
  Init_Clones();//  Open Root File 
  if(debug_flag){
    cout << "Opening root file: " << pOutputFileName << " with title:\n " <<  SFileTitle->Data() << endl;
  }

  hFile = new TFile((const char *)pOutputFileName,"RECREATE",(const char *)SFileTitle->Data(),comp);
  if(hFile==NULL || !hFile->IsOpen()){
    cerr << "*** ERROR: Could not open root output file: " << pOutputFileName << endl;
    exit(1);
  }
  hFile->SetCompressionLevel(comp);

  //
  // Initialize Tree 
  tree = new TTree("CLASEVENT","CLAS Event Tree");
  tree->SetAutoSave(1024*1024*1024); // Save only once every 1Gig.

#ifdef WRITE_SCALERS
  scaler_tree = new TTree("SCALER","SCALERS Event Tree");
  scaler_tree->SetAutoSave(100000000);
#endif

  //////////////////////////////////////////////////////////////////////////////////////
  // Initialize Branches 
  //////////////////////////////////////////

#ifdef WRITE_SCALERS
  Initialize_Branches(tree,scaler_tree);
#else
  Initialize_Branches(tree,NULL);
#endif
  //
  //////////////////////////////////////////////////////////////////////////////////////
  //
  //
  // Initialize BOS file name, open BOS File and Read all events. 
  //
  //////////////////////////////////////////////////////////////////////////////////////
  
  bosInit(bcs_.iw,NBCS);
  
  for(filenum=1;filenum<argc;filenum++){
    // Print out event selection status
    if(event_selection_flag>0) {
      cout << endl << "************   WARNING  !!!!   **************" << endl << endl;
      cout << "  Event selection FLAG is active therefor not all PHYSEVENTS will " << endl
	   << "   appear in the output stream. BE AWARE !!! " << endl 
	   << endl << "*********************************************" << endl;
    }
    // Initialize BOS file name, open BOS File and Read all events.

    strcpy(bosFileName,argv[filenum]);
    if(gSystem->AccessPathName(bosFileName,kReadPermission)){
      cerr << "*** ERROR: The file " << bosFileName << " can not be read." <<endl;
      continue;
    }
    iostatus = bosOpen(bosFileName,"r",&bosFileHandle);
    if(iostatus){
      cout << "File " << bosFileName << " could not be opened. ";
      continue;
    }
    while((bosRead(bosFileHandle,bcs_.iw,"E")==0)&&(iCount<nEventsWrite)){
      //
      
      Clear_Clones();
      
      // TARGET_INCLUDE6
      nEVNT_Store = 0;
      nECPB_Store = 0;
      nSCPB_Store = 0;
      nDCPB_Store = 0;
      nCCPB_Store = 0;
      nLCPB_Store = 0;
      nICPB_Store = 0;
      nICHB_Store = 0;
#ifdef WRITE_PHOTON
      nSTPB_Store = 0;
      nTGPB_Store = 0;
      nTAGR_Store = 0;
#endif

#ifdef WRITE_VERTEX
      nVERT_Store = 0;
      nMVRT_Store = 0;
#endif

#ifdef WRITE_TBER
      nTBER_Store=0;
#endif

#ifdef WRITE_TGBI
      nTGBI_Store=0;
#endif

#ifdef WRITE_MCHD
      nMCHD_Store = 0;
#endif

#ifdef WRITE_GSIM
      nGSIM_Store = 0;
#endif

#ifdef WRITE_SCALERS
      nScaler_HLS_Store = 0;
      nScaler_S1ST_Store = 0;
      nScaler_TRGS_Store = 0;
#endif
      //////////////////////////////////////////////////////////////////////
      //
      //
      // Read each individal Bank and store it in Store Clone Arrays
      //
      //////////////////////////////////////////////////////////////////////
      EventType = 0;
      HEAD kfileHEADER(0);
      if(kfileHEADER.get_nrows() > 0){
	if((kfileHEADER.get_NRUN(0)==0)||(kfileHEADER.get_NRUN(0)==1)||(kfileHEADER.get_NRUN(0)==10)){
	  //
	  //  For Run Number 0 and 1 every event is cosidered to be PHYSICEVENT	  
	  //	  cout << "RUNNUMBER  "  << kfileHEADER.get_NRUN(0) << "  is reserved for simulation data" <<  endl
	  //     << "This file will be processed as GSIM simulation Data " << endl;
	  EventType = PHYSICEVNT;
	} else {
	  if((kfileHEADER.get_TYPE(0) == 1)||kfileHEADER.get_TYPE(0) == 2||kfileHEADER.get_TYPE(0) == 4){
	    EventType = PHYSICEVNT;
	  }else if(kfileHEADER.get_TYPE(0) == 10){
	    EventType = SCALEREVNT;
	  }else{
	    //	    cerr << "Unknown event type. Not processing " << kfileHEADER.get_TYPE(0) << " " << kfileHEADER.get_NEVENT(0) << endl;
	         // Clean Garbage
	    bosLdrop(bcs_.iw,"E");
	    bosNgarbage(bcs_.iw);
	    continue;
	  }
	}
      }else{
	cout << "No HEAD bank for Physics event.\n";
      }
      //
      //
     //-------------------   Storing Bank HEADER --------------------
     //
     if((EventType == PHYSICEVNT)){
       
       Fill_HEADER_Bank(hHEADER);
       Last_Evt_Num = hHEADER->NEvent;

      if(debug_flag>1){
	cout << "Event " << iCount << " Ph Event: " << hHEADER->NEvent <<endl<<endl;
      }
       
       //
       //-------------------   Storing Bank EVNT --------------------
       //
       
       EVNT    kEVNT(0);
       TEVNTClass   *EVNT_p = new TEVNTClass();
       
       if(kEVNT.get_nrows() > 0){
	 for(int j = 0; j < kEVNT.get_nrows(); j++){
	   Fill_EVNT_Bank(EVNT_p, &kEVNT, j);
	   if(debug_flag>1){
	     cout << "\nEVNT Row: "<< j << endl;
	     EVNT_p->Print();
	   }
	   TClonesArray &tEVNTbank = *EVNTStore;
	   new(tEVNTbank[nEVNT_Store++]) TEVNTClass(EVNT_p);
	 }
       }

       delete EVNT_p;

#ifdef WRITE_MCHD
       if(DO_MCHD_flag) {
	 //
	 //-------------------   Storing Bank MCHD --------------------
	 //
	 
	 MCHD   kMCHD(0);
	 TMCHDClass   *MCHD_p = new TMCHDClass();
	 
	 if( kMCHD.get_nrows() > 0 ) {
	   for( int j = 0; j < kMCHD.get_nrows(); j++ ) {
	     Fill_MCHD_Bank( MCHD_p, &kMCHD, j );
	     if( debug_flag > 1 ) {
	       cout << "\nMCHD Row: "<< j << endl;
	       MCHD_p->Print();
	     }
	     TClonesArray &tMCHDbank = *MCHDStore;
	     new( tMCHDbank[nMCHD_Store++] ) TMCHDClass( MCHD_p );
	   }
	 }
	 delete MCHD_p;
       }
#endif
	 

#ifdef WRITE_GSIM
       if(DO_GSIM_flag){
	 //
	 //-------------------   Storing Bank GSIM --------------------
	 //
	 
	 PART    kPART(0);
	 MCTK    kMCTK(0);
	 MCVX    kMCVX(0);
	 
	 TGSIMClass   *GSIM_p = new TGSIMClass();
	 
	 if(kPART.get_nrows() > 0){
	   for(int j = 0; j < kPART.get_nrows(); j++){
	     Fill_GSIM_Bank(GSIM_p, &kPART, j);
	     if(debug_flag>1){
	       cout << "\nGSIM Row: "<< j << endl;
	       GSIM_p->Print();
	     }
	     TClonesArray &tGSIMbank = *GSIMStore;
	     new(tGSIMbank[nGSIM_Store++]) TGSIMClass(GSIM_p);
	   }
	 }else if(kMCTK.get_nrows() > 0){
	   for(int j = 0; j < kMCTK.get_nrows(); j++){
	     Fill_GSIM_Bank(GSIM_p, &kMCTK, &kMCVX, j);
	     if(debug_flag>1){
	       cout << "\nGSIM Row: "<< j << endl;
	       GSIM_p->Print();
	     }
	     TClonesArray &tGSIMbank = *GSIMStore;
	     new(tGSIMbank[nGSIM_Store++]) TGSIMClass(GSIM_p);
	   }
	 }
	 
	 
	 delete GSIM_p;
       }
#endif
	 
       //
       //-------------------   Storing Bank ECPB --------------------
       //
       
       ECPB    kECPB(0);
       TECPBClass   *ECPB_p = new TECPBClass();
       if(kECPB.get_nrows() > 0){
	 for(int j = 0; j < kECPB.get_nrows(); j++){
	   Fill_ECPB_Bank(ECPB_p, &kECPB, j);
	   TClonesArray &tECPBbank = *ECPBStore;
	   new(tECPBbank[nECPB_Store++]) TECPBClass(ECPB_p);
	 }
       }

       delete ECPB_p;
       
       //
       //-------------------   Storing Bank SCPB --------------------
       //
       
       SCPB    kSCPB(0);
       TSCPBClass   *SCPB_p = new TSCPBClass();
       if(kSCPB.get_nrows() > 0){
	 for(int j = 0; j < kSCPB.get_nrows(); j++){
	   Fill_SCPB_Bank(SCPB_p, &kSCPB, j);
	   TClonesArray &tSCPBbank = *SCPBStore;
	   new(tSCPBbank[nSCPB_Store++]) TSCPBClass(SCPB_p);
	 }
       }
       
       delete SCPB_p;
       //
       //-------------------   Storing Bank DCPB --------------------
       //
       
       DCPB    kDCPB(0);
       TDCPBClass   *DCPB_p = new TDCPBClass();
       if(kDCPB.get_nrows() > 0){
	 for(int j = 0; j < kDCPB.get_nrows(); j++){
	   Fill_DCPB_Bank(DCPB_p, &kDCPB, j);
	   TClonesArray &tDCPBbank = *DCPBStore;
	   new(tDCPBbank[nDCPB_Store++]) TDCPBClass(DCPB_p);
	 }
       }
       
       delete DCPB_p;
       //
       //-------------------   Storing Bank CCPB --------------------
       //
       
       CCPB    kCCPB(0);
       TCCPBClass   *CCPB_p = new TCCPBClass();
       if(kCCPB.get_nrows() > 0){
	 for(int j = 0; j < kCCPB.get_nrows(); j++){
	   Fill_CCPB_Bank(CCPB_p, &kCCPB, j);
	   TClonesArray &tCCPBbank = *CCPBStore;
	   new(tCCPBbank[nCCPB_Store++]) TCCPBClass(CCPB_p);
	 }
       }
       
       delete CCPB_p;
       //
       //-------------------   Storing Bank LCPB --------------------
       //
       
       LCPB    kLCPB(0);
       TLCPBClass   *LCPB_p = new TLCPBClass();
       if(kLCPB.get_nrows() > 0){
	 for(int j = 0; j < kLCPB.get_nrows(); j++){
	   Fill_LCPB_Bank(LCPB_p, &kLCPB, j);
	   TClonesArray &tLCPBbank = *LCPBStore;
	   new(tLCPBbank[nLCPB_Store++]) TLCPBClass(LCPB_p);
	 }
       }
       delete LCPB_p;
       //     }

       //
       //-------------------   Storing Bank ICPB --------------------
       //
       
       ICPB    kICPB(0);
       TICPBClass   *ICPB_p = new TICPBClass();
       if(kICPB.get_nrows() > 0){
	 for(int j = 0; j < kICPB.get_nrows(); j++){
	   Fill_ICPB_Bank(ICPB_p, &kICPB, j);
	   TClonesArray &tICPBbank = *ICPBStore;
	   new(tICPBbank[nICPB_Store++]) TICPBClass(ICPB_p);
	 }
       }
       delete ICPB_p;

       //
       //-------------------   Storing Bank ICHB --------------------
       //
       
       ICHB    kICHB(0);
       TICHBClass   *ICHB_p = new TICHBClass();
       if(kICHB.get_nrows() > 0){
	 for(int j = 0; j < kICHB.get_nrows(); j++){
	   Fill_ICHB_Bank(ICHB_p, &kICHB, j);
	   TClonesArray &tICHBbank = *ICHBStore;
	   new(tICHBbank[nICHB_Store++]) TICHBClass(ICHB_p);
	 }
       }
       delete ICHB_p;

#ifdef WRITE_PHOTON
       if(DO_PHOTON_flag){
	 //
	 //-------------------   Storing Bank STPB --------------------
	 //
	 
	 STPB    kSTPB(0);
	 TSTPBClass   *STPB_p = new TSTPBClass();
	 if(kSTPB.get_nrows() > 0){
	   for(int j = 0; j < kSTPB.get_nrows(); j++){
	     Fill_STPB_Bank(STPB_p, &kSTPB, j);
	     TClonesArray &tSTPBbank = *STPBStore;
	     new(tSTPBbank[nSTPB_Store++]) TSTPBClass(STPB_p);
	   }
	 }
	 delete STPB_p;
	 
	 //
	 //-------------------   Storing Bank TGPB --------------------
	 //
	 
	 TGPB    kTGPB(0);
	 TTGPBClass   *TGPB_p = new TTGPBClass();
	 if(kTGPB.get_nrows() > 0){
	   for(int j = 0; j < kTGPB.get_nrows(); j++){
	     Fill_TGPB_Bank(TGPB_p, &kTGPB, j);
	     TClonesArray &tTGPBbank = *TGPBStore;
	     new(tTGPBbank[nTGPB_Store++]) TTGPBClass(TGPB_p);
	   }
	 }
	 delete TGPB_p;
	 
	 //
	 //-------------------   Storing Bank TAGR --------------------
	 //
	 
	 TAGR    kTAGR(1);
	 TTAGRClass   *TAGR_p = new TTAGRClass();
	 
	 if(kTAGR.get_nrows() > 0){
	   for(int j = 0; j < kTAGR.get_nrows(); j++){
	     Fill_TAGR_Bank(TAGR_p, &kTAGR, j);
	     TClonesArray &tTAGRbank = *TAGRStore;
	     new(tTAGRbank[nTAGR_Store++]) TTAGRClass(TAGR_p);
	   }
	 }
	 delete TAGR_p;
       }

#endif

#ifdef WRITE_VERTEX
       if(DO_VERTEX_flag){
	 //
	 //-------------------   Storing Bank VERT --------------------
	 //
	 
	 VERT    kVERT(1);   /// FIST store the ones with respect to the BEAM
	 TVERTClass   *VERT_p = new TVERTClass();
	 
	 if(kVERT.get_nrows() > 0){
	   for(int j = 0; j < kVERT.get_nrows(); j++){
	     Fill_VERT_Bank(VERT_p, &kVERT, j);
	     TClonesArray &tVERTbank = *VERTStore;
	     new(tVERTbank[nVERT_Store++]) TVERTClass(VERT_p);
	   }
	 }
 //	 delete VERT_p;

	 VERT    kVERT2(2);   /// FIST store the ones with respect to each other.
 //	 TVERTClass   *VERT_p = new TVERTClass();
	 
	 if(kVERT2.get_nrows() > 0){
	   for(int j = 0; j < kVERT2.get_nrows(); j++){
	     Fill_VERT_Bank(VERT_p, &kVERT2, j);
	     TClonesArray &tVERTbank = *VERTStore;
	     new(tVERTbank[nVERT_Store++]) TVERTClass(VERT_p);
	   }
	 }
	 delete VERT_p;
	 
	 
	 //
	 //-------------------   Storing Bank MVRT --------------------
	 //
	 
	 MVRT    kMVRT(1);
	 TMVRTClass   *MVRT_p = new TMVRTClass();
	 
	 if(kMVRT.get_nrows() > 0){
	   for(int j = 0; j < kMVRT.get_nrows(); j++){
	     Fill_MVRT_Bank(MVRT_p, &kMVRT, j);
	     TClonesArray &tMVRTbank = *MVRTStore;
	     new(tMVRTbank[nMVRT_Store++]) TMVRTClass(MVRT_p);
	   }
	 }
	 delete MVRT_p;
       }

    
#endif

#ifdef WRITE_TBER
       if(DO_TBER_flag){
	 //
	 //-------------------   Storing Bank TBER --------------------
	 //
	 
	 TBER    kTBER(0);
	 TTBERClass   *TBER_p = new TTBERClass();
	 
	 if(kTBER.get_nrows() > 0){
	   for(int j = 0; j < kTBER.get_nrows(); j++){
	     Fill_TBER_Bank(TBER_p, &kTBER, j);
	     TClonesArray &tTBERbank = *TBERStore;
	     new(tTBERbank[nTBER_Store++]) TTBERClass(TBER_p);
	   }
	 }
	 delete TBER_p;
       }
#endif




     //-------------------   Storing Bank TGBI --------------------
     //
#ifdef WRITE_TGBI     
     TGBI    kTGBI(0);
     TTGBIClass   *TGBI_p = new TTGBIClass();
     if(kTGBI.get_nrows() > 0){
       for(int j = 0; j < kTGBI.get_nrows(); j++){
	 Fill_TGBI_Bank(TGBI_p, &kTGBI, j);
	 TClonesArray &tTGBIbank = *TGBIStore;
	 new(tTGBIbank[nTGBI_Store++]) TTGBIClass(TGBI_p);
       }
     }
     delete TGBI_p;
#endif
    }
    


#ifdef WRITE_SCALERS
     if(EventType == SCALEREVNT){

       //
       //
       //-------------------   Storing Bank HEAD --------------------
       //
       HEAD    kScaler_HEAD(0);
       
       if(kScaler_HEAD.get_nrows() > 0){
	 Fill_HEAD_Bank(hScaler_HEAD, &kScaler_HEAD, 0);
       }else{
	 cerr << "No HEAD bank for scaler event. \n";
       }
       //
       //
       //-------------------   Storing Bank HLS --------------------
       //
       HLS    kScaler_HLS(0);
       THLSClass   *HLS_psc = new THLSClass();
       if(kScaler_HLS.get_nrows() > 0){
	 for(int j = 0; j < kScaler_HLS.get_nrows(); j++){
	   Fill_HLS_Bank(HLS_psc, &kScaler_HLS, j);
	   TClonesArray &tScaler_HLSbank = *Scaler_HLSStore;
	   new(tScaler_HLSbank[nScaler_HLS_Store++]) THLSClass(HLS_psc);
	 }
       }

       delete HLS_psc;

       //
       //
       //-------------------   Storing Bank S1ST --------------------
       //
       S1ST    kScaler_S1ST(0);
       TS1STClass   *S1ST_psc = new TS1STClass();
       if(kScaler_S1ST.get_nrows() > 0){
	 for(int j = 0; j < kScaler_S1ST.get_nrows(); j++){
	   Fill_S1ST_Bank(S1ST_psc, &kScaler_S1ST, j);
	   TClonesArray &tScaler_S1STbank = *Scaler_S1STStore;
	   new(tScaler_S1STbank[nScaler_S1ST_Store++]) TS1STClass(S1ST_psc);
	 }
       }

       delete S1ST_psc;
       //
       //
       //-------------------   Storing Bank TRGS --------------------
       //
       TRGS    kScaler_TRGS(0);
       TTRGSClass   *TRGS_psc = new TTRGSClass();
       if(kScaler_TRGS.get_nrows() > 0){
	 for(int j = 0; j < kScaler_TRGS.get_nrows(); j++){
	   Fill_TRGS_Bank(TRGS_psc, &kScaler_TRGS, j);
	   TClonesArray &tScaler_TRGSbank = *Scaler_TRGSStore;
	   new(tScaler_TRGSbank[nScaler_TRGS_Store++]) TTRGSClass(TRGS_psc);
	 }
       }
       delete TRGS_psc;
     }

#endif

     /////////////////////////////////////////////////////////////////////////
     // Fill Event  Tree
     //Int_t flag_write_status = 1;

     //====================================================================================================
     // This part of code is only executed if event_selection_flag is set to 1 (Use -s option to do that)
     //if(event_selection_flag > 0) flag_write_status = Exclusive_Flag(EVNTStore,nEVNT_Store);
     //====================================================================================================

     if((EventType == PHYSICEVNT)){ 
       tree->Fill();
       Last_Key_Num++;  // Each Fill call increased Key by one.
     }

#ifdef WRITE_SCALERS
     if(EventType == SCALEREVNT && !quiet_flag){ 
       cout << " Filling Scaler Tree, last evt= " << Last_Evt_Num << endl;
       scaler_tree->Fill();
     }
#endif

     //
     // If we reached maximum file size...
     //

     if(hFile->GetBytesWritten() > __MAXFILESIZE__ ){
       char tmpstr[128];
       hFile->Write();
       if(debug_flag)hFile->Print();       
       hFile->Close();
        OutFileSequence++;
       sprintf(tmpstr,"%s.%02d",pOutputFileName,OutFileSequence);
       if(debug_flag){
	 cout << "Opening root file: " << tmpstr << " with title:\n " <<  SFileTitle->Data() << endl;
       }
       
       if(!quiet_flag){
	 cout << "Output file too large. Opening new file: " << tmpstr <<endl;
	 cout << "Title: " << SFileTitle->Data() <<endl;
       }
       hFile = new TFile(tmpstr,"RECREATE",SFileTitle->Data(),comp);
       if(debug_flag)cout << "File open?\n";

       if(hFile == NULL || !hFile->IsOpen()){
	 cerr << "*** ERROR: Could not open root output file: " << tmpstr << endl;
	 exit(1);
       }
       hFile->SetCompressionLevel(comp);

       tree = new TTree("CLASEVENT","CLAS Event Tree");
       tree->SetAutoSave(1024*1024*1024); // Save only once every 1Gig.

#ifdef WRITE_SCALERS
       scaler_tree = new TTree("SCALER","SCALERS Event Tree");
       scaler_tree->SetAutoSave(100000000);
       Initialize_Branches(tree,scaler_tree);
#else
       Initialize_Branches(tree,NULL);

#endif


       //
     }
     
     // Clean Garbage
     bosLdrop(bcs_.iw,"E");
     bosNgarbage(bcs_.iw);
     //
     iCount++;
     if(iCount%2000 == 0 && !quiet_flag){
       cout << iCount << " Events processed " << endl;
     }
    }
    //
    if(debug_flag)cout << "Close BOS \n";
    bosClose(bosFileHandle);
    if(debug_flag)cout << "BOS Close ok\n";
  }
  //  Write File and Close it
  hFile->Write();
  if(debug_flag)hFile->Print();
  hFile->Close();
  cout << endl << "***********************************" << endl << "   Finished ...." << endl << endl;
  return 1;
}


//////////////////////////////////////////////////////////////////
// End OF Main 
/////////////////////////////////////////////////////////////////

void Initialize_Branches(TTree *tree,TTree *scaler_tree){
  //////////////////////////////////////////////////////////////////////////////////////
  // Initialize Branches 
  //////////////////////////////////////////
  int bufsize = __BUFSIZE__;
  int split   = 1;

  //
  // Initialize Tree 
  //  tree = new TTree("CLASEVENT","CLAS Event Tree");
  //tree->SetAutoSave(1024*1024*1024); // Save only once every 1Gig.

  HEADERBranch = tree->Branch("HEADER","THEADERClass",&hHEADER,bufsize,split);
  tree->SetBranchStatus("HEADER",1);
  
  EVNTBranch = tree->Branch("EVNT",&fgEVNTStore,bufsize,split);
  
  //  tree->SetBranchStatus("EVNT",1);
  
  ECPBBranch = tree->Branch("ECPB",&fgECPBStore,bufsize,split);
  //tree->SetBranchStatus("ECPB",1);
  
  SCPBBranch = tree->Branch("SCPB",&fgSCPBStore,bufsize,split);
  //tree->SetBranchStatus("SCPB",1);
  
  DCPBBranch = tree->Branch("DCPB",&fgDCPBStore,bufsize,split);
  //tree->SetBranchStatus("DCPB",1);
  
  CCPBBranch = tree->Branch("CCPB",&fgCCPBStore,bufsize,split);
  //tree->SetBranchStatus("CCPB",1);
  
  LCPBBranch = tree->Branch("LCPB",&fgLCPBStore,bufsize,split);
  //tree->SetBranchStatus("LCPB",1);

  ICPBBranch = tree->Branch("ICPB",&fgICPBStore,bufsize,split);
  //tree->SetBranchStatus("ICPB",1);

  ICHBBranch = tree->Branch("ICHB",&fgICHBStore,bufsize,split);
  //tree->SetBranchStatus("ICHB",1);

#ifdef WRITE_PHOTON
  if(DO_PHOTON_flag){
    STPBBranch = tree->Branch("STPB",&fgSTPBStore,bufsize,split);
    TGPBBranch = tree->Branch("TGPB",&fgTGPBStore,bufsize,split);
    TAGRBranch = tree->Branch("TAGR",&fgTAGRStore,bufsize,split);
  }
#endif

#ifdef WRITE_VERTEX
  if(DO_VERTEX_flag){
    VERTBranch = tree->Branch("VERT",&fgVERTStore,bufsize,split);
    MVRTBranch = tree->Branch("MVRT",&fgMVRTStore,bufsize,split);
  }
#endif

#ifdef WRITE_TBER
  if(DO_TBER_flag){
    TBERBranch = tree->Branch("TBER",&fgTBERStore,bufsize,split);
  }
#endif


#ifdef WRITE_TGBI
  TGBIBranch = tree->Branch("TGBI",&fgTGBIStore,bufsize,split);
#endif

#ifdef WRITE_MCHD
  if(DO_MCHD_flag){
  // Initialize MCHD branch is Flag is set 
    cout << "Initializing MCHD Branch ......." << endl;
    MCHDBranch = tree->Branch("MCHD",&fgMCHDStore,bufsize,split);
  //  tree->SetBranchStatus("MCHD",1);
  }
#endif

#ifdef WRITE_GSIM
  if(DO_GSIM_flag){
  // Initialize GSIM branch is Flag is set 
    cout << "Initializing GSIM Branch ......." << endl;
    GSIMBranch = tree->Branch("GSIM",&fgGSIMStore,bufsize,split);
  //  tree->SetBranchStatus("GSIM",1);
  }
#endif

  tree->SetBranchStatus("*",1);

#ifdef WRITE_SCALERS
  
  //scaler_tree = new TTree("SCALER","SCALERS Event Tree");
  //scaler_tree->SetAutoSave(100000000);

  bufsize = __SCALER_BUFSIZE__;
  Scaler_LastEvtNumBranch = scaler_tree->Branch("Last_Evt_Num",&Last_Evt_Num,"Last_Evt_Num/I",bufsize);
  //scaler_tree->SetBranchStatus("Last_Evt_Num",1);
  
  Scaler_HEADBranch = scaler_tree->Branch("SC_HEAD","THEADClass",&hScaler_HEAD,bufsize,split);
  //scaler_tree->SetBranchStatus("SC_HEAD",1);
  
  Scaler_HLSBranch = scaler_tree->Branch("SC_HLS",&fgScaler_HLSStore,bufsize,split);
  //scaler_tree->SetBranchStatus("SC_HLS",1);
  
  Scaler_S1STBranch = scaler_tree->Branch("SC_S1ST",&fgScaler_S1STStore,bufsize,split);
  //scaler_tree->SetBranchStatus("SC_S1ST",1);
  //
  Scaler_TRGSBranch = scaler_tree->Branch("SC_TRGS",&fgScaler_TRGSStore,bufsize,split);
  //scaler_tree->SetBranchStatus("SC_TRGS",1);
  scaler_tree->SetBranchStatus("*",1);
#endif



}

//***********************************************************************************
// Initialize CloneArrays
//***********************************************************************************
void Init_Clones()
{
  
  // TARGET_INCLUDE8
  if(!fgEVNTStore) fgEVNTStore = new TClonesArray("TEVNTClass",1);
  EVNTStore  = fgEVNTStore;
  
  if(!fgECPBStore) fgECPBStore = new TClonesArray("TECPBClass",1);
  ECPBStore  = fgECPBStore;
  
  if(!fgSCPBStore) fgSCPBStore = new TClonesArray("TSCPBClass",1);
  SCPBStore  = fgSCPBStore;
  
  if(!fgDCPBStore) fgDCPBStore = new TClonesArray("TDCPBClass",1);
  DCPBStore  = fgDCPBStore;
  
  if(!fgCCPBStore) fgCCPBStore = new TClonesArray("TCCPBClass",1);
  CCPBStore  = fgCCPBStore;
  
  if(!fgLCPBStore) fgLCPBStore = new TClonesArray("TLCPBClass",1);
  LCPBStore  = fgLCPBStore;

  if(!fgICPBStore) fgICPBStore = new TClonesArray("TICPBClass",1);
  ICPBStore  = fgICPBStore;

  if(!fgICHBStore) fgICHBStore = new TClonesArray("TICHBClass",1);
  ICHBStore  = fgICHBStore;

#ifdef WRITE_PHOTON
  if(DO_PHOTON_flag){
    if(!fgSTPBStore) fgSTPBStore = new TClonesArray("TSTPBClass",1);
    STPBStore  = fgSTPBStore;

    if(!fgTGPBStore) fgTGPBStore = new TClonesArray("TTGPBClass",1);
    TGPBStore  = fgTGPBStore;

    if(!fgTAGRStore) fgTAGRStore = new TClonesArray("TTAGRClass",1);
    TAGRStore  = fgTAGRStore;
  }

#endif

#ifdef WRITE_VERTEX
  if(DO_VERTEX_flag){
    if(!fgVERTStore) fgVERTStore = new TClonesArray("TVERTClass",1);
    VERTStore  = fgVERTStore;

    if(!fgMVRTStore) fgMVRTStore = new TClonesArray("TMVRTClass",1);
    MVRTStore  = fgMVRTStore;
  }
#endif

#ifdef WRITE_TBER
  if(DO_TBER_flag){
    if(!fgTBERStore) fgTBERStore = new TClonesArray("TTBERClass",1);
    TBERStore  = fgTBERStore;
  }
#endif



#ifdef WRITE_TGBI
  if(!fgTGBIStore) fgTGBIStore = new TClonesArray("TTGBIClass",1);
  TGBIStore  = fgTGBIStore;
#endif

#ifdef WRITE_MCHD
  if( DO_MCHD_flag ) {
    if(!fgMCHDStore) fgMCHDStore = new TClonesArray("TMCHDClass",1);
    MCHDStore  = fgMCHDStore;
  }
#endif

#ifdef WRITE_GSIM
  if(DO_GSIM_flag){
    if(!fgGSIMStore) fgGSIMStore = new TClonesArray("TGSIMClass",1);
    GSIMStore  = fgGSIMStore;
  }
#endif

#ifdef WRITE_SCALERS  
  
  if(!fgScaler_HLSStore) fgScaler_HLSStore = new TClonesArray("THLSClass",1);
  Scaler_HLSStore  = fgScaler_HLSStore;
  
  if(!fgScaler_S1STStore) fgScaler_S1STStore = new TClonesArray("TS1STClass",1);
  Scaler_S1STStore  = fgScaler_S1STStore;
  
  if(!fgScaler_TRGSStore) fgScaler_TRGSStore = new TClonesArray("TTRGSClass",1);
  Scaler_TRGSStore  = fgScaler_TRGSStore;
#endif
}

//***********************************************************************************
//  Clear  CloneArrays
//***********************************************************************************
void Clear_Clones()
{
  // TARGET_INCLUDE9
  if(fgEVNTStore) EVNTStore->Clear();
  if(fgECPBStore) ECPBStore->Clear();
  if(fgSCPBStore) SCPBStore->Clear();
  if(fgDCPBStore) DCPBStore->Clear();
  if(fgCCPBStore) CCPBStore->Clear();
  if(fgLCPBStore) LCPBStore->Clear();
  if(fgICPBStore) ICPBStore->Clear();
  if(fgICHBStore) ICHBStore->Clear();
#ifdef WRITE_PHOTON
  if(DO_PHOTON_flag){
    if(fgSTPBStore) STPBStore->Clear();
    if(fgTGPBStore) TGPBStore->Clear();
    if(fgTAGRStore) TAGRStore->Clear();
  }
#endif

#ifdef WRITE_VERTEX
  if(DO_VERTEX_flag){
    if(fgVERTStore) VERTStore->Clear();
    if(fgVERTStore) VERTStore->Clear();
  }
#endif

#ifdef WRITE_TGBI
  if(fgTGBIStore) TGBIStore->Clear();
#endif

#ifdef WRITE_MCHD
  if(DO_MCHD_flag){
    if(fgMCHDStore) MCHDStore->Clear();
  }
#endif

#ifdef WRITE_GSIM
  if(DO_GSIM_flag){
    if(fgGSIMStore) GSIMStore->Clear();
  }
#endif
#ifdef WRITE_SCALERS
  if(fgScaler_HLSStore) Scaler_HLSStore->Clear();
  if(fgScaler_S1STStore) Scaler_S1STStore->Clear();
  if(fgScaler_TRGSStore) Scaler_TRGSStore->Clear();
#endif
}


//***********************************************************************************
//  Parse arguments 
//***********************************************************************************
void Parse_Args(int *argc, char **argv){
  // Read and parse all the options, leaving only input files in the
  // argv array.
  // This version, all options flags are globals.
#define REMOVE_ONE {(*argc)--;for(j=i;j<(*argc);j++)argv[j]=argv[j+1];i--;}
#define I_PLUS_PLUS if((i+1)<(*argc)){i++;}else{break;}
  int  i,j;
  quiet_flag = 0;
  event_selection_flag = 0;
  DO_MCHD_flag=0;           // Default is to NOT write the MCHD banks.
  DO_GSIM_flag=0;           // Default is to NOT write the GSIM banks.
  DO_PHOTON_flag=1;         // Default is to write the PHOTON banks.
  DO_VERTEX_flag=1;         // Default is to write the VERTEX banks.
  DO_TBER_flag = 1;         // Default is to write the TBER  banks.

  for(i=1;i<(*argc);i++)  
    {
      if(argv[i][0]=='-')
	{
       if(strcmp(argv[i],"-quiet")==0 || strcmp(argv[i],"-q")==0)  
	 {
	   quiet_flag = 1;
	 }
       else if(strcmp(argv[i],"-debug")==0 || strcmp(argv[i],"-d")==0)
	 { 
	   debug_flag++;
	 }
       else if(strcmp(argv[i],"-MCHD")==0 || strcmp(argv[i],"-M")==0)
	 { 
	   DO_MCHD_flag=1;
	 }
       else if(strcmp(argv[i],"-NOMCHD")==0 || strcmp(argv[i],"-NM")==0)
	 { 
	   DO_MCHD_flag=0;
	 }       
       else if(strcmp(argv[i],"-GSIM")==0 || strcmp(argv[i],"-G")==0)
	 { 
	   DO_GSIM_flag=1;
	 }
       else if(strcmp(argv[i],"-NOGSIM")==0 || strcmp(argv[i],"-NG")==0)
	 { 
	   DO_GSIM_flag=0;
	 }
       else if(strcmp(argv[i],"-PHOTON")==0 || strcmp(argv[i],"-P")==0)
	 { 
	   DO_PHOTON_flag=1;
	 }
       else if(strcmp(argv[i],"-NOPHOTON")==0 || strcmp(argv[i],"-NP")==0)
	 { 
	   DO_PHOTON_flag=0;
	 }
       else if(strcmp(argv[i],"-VERTEX")==0 || strcmp(argv[i],"-V")==0)
	 { 
	   DO_VERTEX_flag=1;
	 }
       else if(strcmp(argv[i],"-NOVERTEX")==0 || strcmp(argv[i],"-NV")==0)
	 { 
	   DO_VERTEX_flag=0;
	 }
       else if(strcmp(argv[i],"-TBER")==0 || strcmp(argv[i],"-TB")==0)
	 { 
	   DO_TBER_flag=1;
	 }
       else if(strcmp(argv[i],"-NOTBER")==0 || strcmp(argv[i],"-NTB")==0)
	 { 
	   DO_TBER_flag=0;
	 }
       else if(strcmp(argv[i],"-n")==0 || strcmp(argv[i],"-numevt")==0)
	 {
	   I_PLUS_PLUS;
	   sscanf(argv[i],"%d",&nEventsWrite);
	   REMOVE_ONE;
	 }
       //else if(strcmp(argv[i],"-s")==0 )
       // {
       //	   event_selection_flag = 1;
       //	 }
       else if(strcmp(argv[i],"-o")==0 || strcmp(argv[i],"-outfile")==0)
	 {
	   I_PLUS_PLUS;
           strcpy(pOutputFileName,argv[i]);
	   REMOVE_ONE;
	 }
       else if(strcmp(argv[i],"-help")==0||strcmp(argv[i],"-h")==0)  
	 {
	   Print_Usage();
	   exit(1);
	 }
       else
	 {
	   fprintf(stderr,"\nI did not understand the option : %s\n",argv[i]);
	   Print_Usage();
	   exit(1);
	 }
       /* KILL the option from list */
       REMOVE_ONE;
	}
    }
}

//***********************************************************************************
//  Print Usage 
//***********************************************************************************

void Print_Usage(){
  cout << " WriteRootDst : This Program converts a BOS output file to a ROOT Tree\n";  
  cout << " Usage: WriteRootDst [-o outputfile] [-n events] infile1 infile2 ...\n";  
  cout << "     infile1 infile2 - a string of one or more input files\n";  
  cout << "     -o outputfile   - output ROOT file name  (default = dst.root)\n";  
  cout << "     -n      nevent  -\n";  
  cout << "     -numevt nevent  - limit the output to nevents.\n";  
  cout << "     -quiet or -q    - Be quiet about it. \n";  
  cout << "     -debug or -d    - Be verbose, more verbose for more -d s\n";
#ifdef WRITE_MCHD
  cout << "     -NOMCHD         - Do NOT write MCHD bank (save space) [DEFAULT]\n";
  cout << "     -MCHD           - Write the MCHD bank (for MC data.)\n";
#endif
#ifdef WRITE_GSIM
  cout << "     -NOGSIM         - Do NOT write GSIM bank (save space) [DEFAULT]\n";
  cout << "     -GSIM           - Write the GSIM bank (for MC data.)\n";
#endif
#ifdef WRITE_PHOTON
  cout << "     -NOPHOTON       - Do NOT write Photon beam banks (STPB,TGPB,TAGR)\n";
  cout << "     -PHOTON         - Write Photon beam banks (STPB,TGPB,TAGR) [DEFAULT]\n";
#endif
#ifdef WRITE_VERTEX
  cout << "     -NOVERTEX       - Do NOT write the VERTEX banks (VERT and MVRT).\n";
  cout << "     -VERTEX         - Write the VERTEX banks (VERT and MVRT) [DEFAULT].\n";
#endif
#ifdef WRITE_TBER
  cout << "     -TBER           - Write out the TBER tracking error matrix [DEFAULT].\n";
  cout << "     -NOTBER         - DO NOT Write out the TBER tracking error matrix.\n";
#endif

  cout << " --- \n\n";
}

////////////////////////////////////////////////////////////////////
//
//  This function returns flag=1 if there is only 1-electron and
//  1-proton and no other charged particles present in the event
//  otherwise it returms 0. You do not have to use it.
//  Written for e1d specific analyses.
//
//  Author : Gagik Gavalian
//  Date   : 01/30/2002 (yes exactly on my birthday) 
//******************************************************************

Int_t Exclusive_Flag(TClonesArray *loc_EVNTStore,Int_t nRows)
{
  int fNum_Electron = 0;
  int fNum_Proton   = 0;
  int fNum_X        = 0;

  Int_t status = 0;

  for(int part=0; part < nRows; part++)
    {
      TEVNTClass *EVNT_dp = (TEVNTClass *) loc_EVNTStore->At(part);
      if(EVNT_dp->GetId()==11) fNum_Electron++;
      if(EVNT_dp->GetId()==2212) fNum_Proton++;
      if(EVNT_dp->GetCharge()!=0) fNum_X++;
    }

  if(fNum_Electron==1&&fNum_Proton==1&&fNum_X==2) status = 1;
  return status;
}



//***********************************************************************************
//  End Of File Write_ROOT_Tree.cc   Generated on : Mon Nov 22 20:47:42 EST 1999 
//***********************************************************************************


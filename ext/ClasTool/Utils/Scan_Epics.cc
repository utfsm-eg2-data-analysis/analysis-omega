///////////////////////////////////////////////////////////////////////
//
//    File  Scan Epics
//
//  Author :  Will Morrison    UNH  6/2005
//            Maurik Holtrop   UNH  6/2005
//
//  This program will read the EPIC events from a BOS file and save them 
//  in a class named TEPICClass that can be read in ROOT.
//  Note that the tree that this creates is not as easily manipulated
//  as most trees. Refer to the examples in /net/home/wzm/EPICexamples
//  for some examples of macros that can be run on the command line
//  in ROOT.
//
//////////////////////////////////////////////////////////////////////

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
#include "TEPICClass.h"
#include "TEPICValue.h"

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

////////////////////////////////
// Fillbanks
////////////////////////////////
#include "FillEPIC.h"

/////////////////////////////
// From Header File Event_Type
/////////////////////

#define PHYSICEVNT 2
#define SCALEREVNT 3
#define EPICSEVNT  104

///////////////////////////////////////////////
//    Inmodule Function Prototypes ...
///////////////////////////////////////////////

void Print_Usage();
void Parse_Args(int *argc, char **argv);
void Initialize_Branches(TTree *tree);

////////////////////////////////////////////////
//    System Interface
/////////////////////////////////////////////////

extern TSystem *gSystem;

////////////////////////////////////////////////
//    Branch Declaration ...
/////////////////////////////////////////////////

TEPICClass   *hEPIC;
TBranch *EPICBranch;

//////////////////////////////////////////////////////////////
// Options Globals
//////////////////////////////////////////////////////////////

Int_t event_selection_flag;
Int_t quiet_flag;
Int_t debug_flag;    //=1 for debug mode
char  pOutputFileName[128];
Int_t nEventsWrite;
Int_t DO_GSIM_flag;
Int_t DO_PHOTON_flag;
Int_t DO_VERTEX_flag;

extern int get_bos_index(int array_key, char *bankname, int bank_index);

int main(int argc, char **argv)
{

  TROOT write_epics("Scan_Epics","Program for scanning the EPICS events in BOS files.");
  
  ///////  
  Int_t        comp  = __COMPRESS__;
  int          iostatus;
  int          iCount  = 0;
  int          filenum;
  int RecordFirstPhysFlag=1;
  char     bosFileName[256];
  int      bosFileHandle;
  Int_t        First_Phys=0; // Hold the event number of the first Physics event after the last EPIC event
  Int_t        Last_Phys=0;  // Hold the event number of the last Physics event,  
  Int_t        First_Phys_time=0;
  Int_t        Last_Phys_time=0;
  TFile        *hFile;
  TTree        *tree;

  TString *SFileTitle;
  int EventType;
  
  ///Initialize pointers  
  hEPIC = new TEPICClass();  
  
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
  
  SFileTitle = new TString("Epics DST for: ");
  for(filenum=1;filenum<argc;filenum++){
    SFileTitle->Append(argv[filenum]);
    SFileTitle->Append(" ");
  }
  
  if(pOutputFileName[0]==0){
    strncpy(pOutputFileName,argv[1],120); // Copy a max of 122 chars from first file name
    strcat(pOutputFileName,".root");
    if(!quiet_flag)cout << "Output file : " << pOutputFileName << endl;
  }
  
  hFile = new TFile((const char *)pOutputFileName,"RECREATE",(const char *)SFileTitle->Data(),comp);
  if(hFile==NULL || !hFile->IsOpen()){
    cerr << "*** ERROR: Could not open root output file: " << pOutputFileName << endl;
    exit(1);
  }
  if(debug_flag){
    cout << "Opening root file: " << pOutputFileName << " with title:\n " <<  SFileTitle->Data() << endl;
  }
  
  hFile->SetCompressionLevel(comp);
  
  
  //////////////////////////////  Create a TTree.
  
  tree = new TTree("CLASEPIC","CLAS EPIC Tree");
  tree->SetAutoSave(1024*1024*1024); // Save only once every 1Gig.


  //////////////////////////////////////////////////////////////////////////////////////
  // Initialize Branches 
  //////////////////////////////////////////
  
  Initialize_Branches(tree);

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

    ////////////////////////////////////////
    //Begin looping over events
    ////////////////////////////////////

    while((bosRead(bosFileHandle,bcs_.iw,"E")==0)&&(iCount<nEventsWrite)){  
      
      hEPIC->Clear();              //Clear hEPIC to avoid memory leak
      

      //////////////////////////////////////////////////////////////////////
      // Read each individal Bank and store it in Store Clone Arrays
      //////////////////////////////////////////////////////////////////////

      EventType = 0;
      HEAD kfileHEADER(0);
      
      if(kfileHEADER.get_nrows() > 0){
	if((kfileHEADER.get_TYPE(0) == 1)||kfileHEADER.get_TYPE(0) == 2||kfileHEADER.get_TYPE(0) == 4){
	  EventType = PHYSICEVNT;
	}else if(kfileHEADER.get_TYPE(0) == 10){
	  EventType = SCALEREVNT;
	}else if(kfileHEADER.get_TYPE(0) == 104){
	  EventType = EPICSEVNT;
	}else{
	  cerr << "Unknown event type. Not processing " << kfileHEADER.get_TYPE(0) << endl;
	  continue;
	}
      }else{        
	cout << "No HEAD bank for Physics event.\n";
      }
                      
      if(EventType == PHYSICEVNT){
	if(RecordFirstPhysFlag){     //Records the first Physics event after an EPIC
	  First_Phys = kfileHEADER.get_NEVENT(0);
	  First_Phys_time = kfileHEADER.get_TIME(0);
	  RecordFirstPhysFlag = 0;
	}
	Last_Phys_time = kfileHEADER.get_TIME(0);
	Last_Phys = kfileHEADER.get_NEVENT(0);          //Records the last Physics event before an EPIC
      }
      
      //
      //
      
      
      //
      //
      //-------------------   Storing Bank EPIC --------------------
      //
      if((EventType == EPICSEVNT)){
	EPIC kEpics(0);       
	
	Int_t nFields = kEpics.get_nrows();      // call get_nrows only once
	if(nFields > 0){
	  Fill_EPIC_Bank(hEPIC, &kEpics, nFields);
	  Fill_EPIC_Nums(hEPIC, First_Phys, Last_Phys, kfileHEADER.get_NRUN(0), First_Phys_time,Last_Phys_time,kfileHEADER.get_TIME(0)); //Careful on order of arguements
	  if(debug_flag>1){
	    hEPIC->Print();
	  }
	  tree->Fill();              //Only fills tree with non-empty EPIC events
	  RecordFirstPhysFlag = 1;
	}

	//------------------------------------------------------------
	
	// Clean Garbage
	
      }                     ///// End Event type == EPIC

     bosLdrop(bcs_.iw,"E");
     bosNgarbage(bcs_.iw);
     //
     iCount++;
     if(iCount%5000 == 0 && !quiet_flag){
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


//***********************************************************************************
// Initialize Branches 
//***********************************************************************************

void Initialize_Branches(TTree *tree){
  int bufsize = __BUFSIZE__;
  int split   = 1;

  EPICBranch = tree->Branch("EPICBranch","TEPICClass",&hEPIC,bufsize,split);

  //  tree->SetBranchStatus("EPIC",1);

  tree->SetBranchStatus("*",1);

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
  DO_GSIM_flag=0;           // Default is to NOT write the GSIM banks.
  DO_PHOTON_flag=1;         // Default is to write the PHOTON banks.
  DO_VERTEX_flag=1;         // Default is to write the VERTEX banks.

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
  cout << " Scan_Epics : This Program scans a BOS file.\n";  
  cout << " Usage: Scan_Epics [-o outputfile] [-n events] infile1 infile2 ...\n";  
  cout << "     infile1 infile2 - a string of one or more input files\n";  
  cout << "     -o outputfile   - output ROOT file name  (default = dst.root)\n";  
  cout << "     -n      nevent  -\n";  
  cout << "     -numevt nevent  - limit the output to nevents.\n";  
  cout << "     -quiet or -q    - Be quiet about it. \n";  
  cout << "     -debug or -d    - Be verbose, more verbose for more -d s\n";
  cout << " --- \n\n";
}

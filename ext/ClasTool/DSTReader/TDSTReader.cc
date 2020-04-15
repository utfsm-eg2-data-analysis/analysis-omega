// @(#)ClasTool/TDSTReader:$Name:  $:$Id: TDSTReader.cc,v 1.27 2009/09/28 20:26:43 gavalian Exp $

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all. *
 *                                                                          *
 * Documentation  : TDSTReader.html                                         *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  04/2/2002 (UNH)                                        *
 * Initial Authors:  Maurik Holtrop (UNH) Gagik Gavalian (UNH)              *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TDSTReader</h1>
<pre>
   Modified:   6/2005   Maurik Holtrop UNH
             Add in the PHOTON functionality.
</pre>
<p>
This class is a sub-class of TClasTool. It implements an interface to the ROOT 
based DST that is created by the WriteRootDST program. It can be used directly
for analysis, but <b><emph>I highly recommend</emph></b> that you use TClasTool
for your analysis instead. This will give you all the power of this class and more
and in addition provide you with more flexibility. </p>
<p>
The class implements two chains, one for the data events and one for the scaler events.
The scaler events are optional, and can be turned off. 
The actual scaler event implementation is minimal and does not seem to be used much. </p>
<p>
More detailed documentation would be useful.</p>
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////////////////////////////

#include "TDSTReader.h"

ClassImp(TStoreClone) 

ClassImp(TDSTReader) 

TDSTReader::TDSTReader()
{
  //  Default Constructor.
  //  Default Debug mode is 1
  //  To change it use SetDebugMode(debugmode)
 
  //  fDebug_Mode   = kDBG_Error+kDBG_Info;

  fDebug_Mode = kDBG_Error;

  //  fDebug_Mode   = 0;
  fEventChain   = new TChain("CLASEVENT");
  fScalerChain  = new TChain("SCALER");
  fEPICChain    = new TChain("CLASEPIC");

  fEvntHeader   = new THEADERClass();
  fScalerHead   = new THEADClass();
  fEPIC         = new TEPICClass();

  fCurrentEvent  = -1;
  fCurrentScaler = -1;
  fCurrentEPIC   =  0;
 
  fScalerLastEvt = -1;       // Will be set using SetBranch Address

  fReadScaler    = kTRUE;
  fReadMCHD      = kTRUE;
  //  fReadGSIM      = kFALSE;
  fReadGSIM      = kTRUE;

  InitClones();
  if(fDebug_Mode & kDBG_Info)cout << "TDSTReader:: Initialized \n";
}

//=======================================================================
TDSTReader::~TDSTReader()
{
  // Default Destructor
  //  Destroys Chains
  //

  if ( fEvntHeader != 0 ) 
    delete fEvntHeader ;
  if ( fScalerHead != 0 )
    delete fScalerHead ;
  if ( fEPIC != 0 )
    delete fEPIC;

  //
  // Clean and Destroy ClonesArrays
  // 
  fClones.Delete();
  fScalerClones.Delete();
  
  if ( fEventChain != 0 )  delete fEventChain;
  if ( fScalerChain != 0 ) delete fScalerChain;
  if ( fEPICChain != 0 )   delete fEPICChain;

  fEventChain  = NULL;
  fScalerChain = NULL;
  fEPICChain   = NULL;

}


//
// Copy constructor 
//
TDSTReader::TDSTReader( const TDSTReader& reader ) : 
  TVirtualReader( reader ),  
  fCurrentEPIC( reader.fCurrentEPIC )
{
  // Copy Constructor. Note that this should not be used, since it is not reliable and
  // does not necessairily do what you think it should.
  //

  // 
  // Messages to warn users about possible problems while calling copy constructor.
  //
  static unsigned short nWarns = 0;
  if( nWarns < 20 ) {
    cerr << "You called copy contructor for TDSTReader." << endl;
    cerr << "This feature may not be fully implemented yet." << endl;
    cerr << "Make sure you know what you are doing when calling copy constructor." << endl;
    nWarns++;
  }
  //
  // When TChain class has a copy contructor this message can be removed 
  //

  fEventChain= new TChain("CLASEVENT");
  fScalerChain= new TChain("SCALER");
  fEPICChain = new TChain("CLASEPIC");

  fEvntHeader   = new THEADERClass();
  fScalerHead   = new THEADClass();
  fEPIC         = new TEPICClass();

  InitClones();

  if( reader.EPICTable != 0 )
    EPICTable = new TArrayI( *(reader.EPICTable) );
  else EPICTable = 0;

  TObjArray* dataFileList = reader.fEventChain->GetListOfFiles();
  TIter dataIter( dataFileList );
  TChainElement* dataFile = 0;
  while( ( dataFile = dynamic_cast<TChainElement*>( dataIter.Next() ) ) ) {
    this->AddFile( dataFile->GetTitle() );
  }
 
  TObjArray* epicFileList = reader.fEPICChain->GetListOfFiles();
  TIter epicIter( epicFileList );
  TChainElement* epicFile = 0;
  while( ( epicFile = dynamic_cast<TChainElement*>( epicIter.Next() ) ) ) {
    this->AddEPICFile( epicFile->GetTitle(), TChain::kBigNumber );
  }

  fEventChain->GetEntry( reader.fEventChain->GetChainEntryNumber( reader.fEventChain->GetReadEntry() ) );
  fScalerChain->GetEntry( reader.fScalerChain->GetChainEntryNumber( reader.fScalerChain->GetReadEntry() ) );
  fEPICChain->GetEntry( reader.fEPICChain->GetChainEntryNumber( reader.fEPICChain->GetReadEntry() ) );

  if(fDebug_Mode & kDBG_Info)cout << "TDSTReader:: Initialized \n";
}


//=======================================================================
Int_t TDSTReader::Add(const Char_t *name){
// Add new files to the reader.
//
// The file name may use the wildcarding notation, eg "xxx*.root" means all files
// starting with xxx in the current file system directory.
//
// This method will return with the number of files that were actually added to
// the list of files. So 0 (zero) means the files were not found.
//
   // case with one single file
   if (!TString(name).MaybeWildcard()) {
      return AddFile(name);
   }

   // wildcarding used in name
   Int_t nf = 0;
   TString basename(name);

   Int_t dotslashpos = basename.Index(".root/");
   TString behind_dot_root;
   if (dotslashpos>=0) {
      // Copy the tree name specification
      behind_dot_root = basename(dotslashpos+6,basename.Length()-dotslashpos+6);
      // and remove it from basename
      basename.Remove(dotslashpos+5);
   }

   Int_t slashpos = basename.Last('/');
   TString directory;
   if (slashpos>=0) {
      directory = basename(0,slashpos); // Copy the directory name
      basename.Remove(0,slashpos+1);      // and remove it from basename
   } else {
      directory = gSystem->WorkingDirectory();
   }

   const char *file;
   void *dir = gSystem->OpenDirectory(gSystem->ExpandPathName(directory.Data()));

   if (dir) {
      //create a TList to store the file names (not yet sorted)
      TList l;
      TRegexp re(basename,kTRUE);
      while ((file = gSystem->GetDirEntry(dir))) {
         if (!strcmp(file,".") || !strcmp(file,"..")) continue;
         TString s = file;
         if ( (basename!=file) && s.Index(re) == kNPOS) continue;
         l.Add(new TObjString(file));
      }
      gSystem->FreeDirectory(dir);
      //sort the files in alphanumeric order
      l.Sort();
      TIter next(&l);
      TObjString *obj;
      while ((obj = (TObjString*)next())) {
         file = obj->GetName();
         if (behind_dot_root.Length() != 0){
	   if(AddFile(Form("%s/%s/%s",directory.Data(),file,behind_dot_root.Data()))==kNOERR)nf++;
	 }else{
           if(AddFile(Form("%s/%s",directory.Data(),file)) == kNOERR)nf++;
	 }
      }
      l.Delete();
   }
   return nf;
}


//=======================================================================
Int_t TDSTReader::AddFile( const Char_t *filename ) {
  Int_t n_entries = TChain::kBigNumber;
  return this->AddFile( filename, n_entries );
}

//=======================================================================
Int_t TDSTReader::AddFile(const Char_t *filename,Int_t nentries) {
//  This method adds a single new file into list of files
//  to be analysed. This list is stored in the TChain *fEventChain
//  and separately in TChain *fScalerChain (for the scalers.)
//  (These chains can be accessed directly with the GetChain(char *which) )
//
//  The AddFile method checks if the file requested can actually be read 
//  (unlike TChain::AddFile) and will return kERR_File_Not_Found on error.
//
//  If the branches on the chain are not yet initialized, a call to AddFile
//  will call InitBranches().
//
//  Use the TDSTReader::Add() or TDSTReader::AddListOfFiles() to add
//  multiple files at once.
//
//  For nentries see the TChain::Add() method. (default works fine, so don't specify.)
//
//  Returns a negative number when there was a problem adding the file,
//  returns 0 (zero) if the file was added succesfully.
//
  if(fDebug_Mode&kDBG_Info)cout << "Looking for file " << filename << endl;
  if(access(filename,R_OK) == 0){
    if(fDebug_Mode&kDBG_Info)cout << "File " << filename << "  found" << endl;
    if((fDebug_Mode&kDBG_Debug1) >0){
      cout << "TClasTool::AddFile : File \"" << filename << "\" is added to Chain" << endl;
    }

    if(!fEventChain->Add(filename,nentries) || fEventChain->GetNtrees() == 0){
      if(fDebug_Mode & kDBG_Error){
	cerr << "Could not properly add the file " << filename << " to event chain.\n";
	return(kERR_File_Not_Found);
      }
    }

    if(fReadScaler){
      if((fDebug_Mode&kDBG_Debug1)>0)cout << "TClasTool::AddFile : Adding scaler tree." << endl;
      if(!fScalerChain->Add(filename,nentries) || fScalerChain->GetNtrees() == 0){
	cerr << "Could not properly add the file " << filename << " to scaler chain.\n";	
	cerr << "WARNING: fReadScaler is now set to zero.\n";	
	fReadScaler =0;
      }
    }

    if( GetNFiles() == 1 ) {
      // One File in the chain, so this is first time we added one.
       if(fDebug_Mode&kDBG_Info)cout << "TClasTool::AddFile (INFO): First file added. Initializing Branches" << endl;
      if((fDebug_Mode & kDBG_Debug1) > 0)cout << "TClasTool::AddFile (INFO): First file added. Initializing Branches" << endl;
       InitBranches();
    }

    return kNOERR;

  } else {

    if(fDebug_Mode & kDBG_Error){
      cout << "TClasTool::AddFile (ERROR): Cannot access \"" << filename << "\" file for reading" << endl;
    }
    return kERR_File_Not_Found;
  }

}
//===========================================================================

Int_t TDSTReader::AddEPICFile(const char* filename, Int_t nentries)

// This adds a single EPIC file into the fEPICChain. If the function fails
// to add the filename, or if it contains no trees, then the function returns
// kERR_File_Not_Found. If InitEPICBranches has not yet been called the function 
// calls InitEPICBranches. On a successful add the function returns kNOERR.
//
// The run numbers must be added in order, otherwise if GetEPICValue is called
// it will most likely become confused and bounce back and forth between the 
// out of order runs and never return a value.

{
   
  if(!fEPICChain->Add(filename,nentries) || fEPICChain->GetNtrees() == 0){
    if(fDebug_Mode & kDBG_Error){
      cerr << "Could not properly add the file " << filename << " to EPIC chain.n";
      return(kERR_File_Not_Found);
    }
      }
           
  if( ((TObjArray *)fEPICChain->GetListOfFiles())->GetEntries() == 1 ) {
    // One File in the chain, so this is first time we added one.
    // This is the only place the address is set, so if this doesnt happen EPICs
    // capabilities will not work.
    if(fDebug_Mode&kDBG_Info)cout << "TClasTool::AddEPICFile (INFO): First file added. Initializing Branches" << endl;
    if((fDebug_Mode & kDBG_Debug1) > 0)cout << "TClasTool::AddEPICFile (INFO): First file added. Initializing Branches" << endl;
    InitEPICBranch();
  }
  
  return (kNOERR);
  
}

// Int_t TDSTReader::ReadEvent(Int_t evtnum){
  // Read a specific event from the run with runnum.
  // THIS IS EXPENSIVE! We need to SEARCH for that specific event. 
  // Usually you want to use Next() or GetEntry() which are both quite a bit faster.
  //
  // Returns the event number of the event actually read. Since it is possible the 
  // event is not found

//  cout << "TDSTReader::ReadEvent: this function is not implemented yet." << endl;
//  return 0;
// }

//=======================================================================
Int_t TDSTReader::GetEntry(Int_t entry,Int_t getall){
  //
  // Get an event entry from the file(s) and load it.
  // Returns the number of bytes read.
  //
  // NOTE: This WILL affect the fCurrentEvent which is set to entry.
  //
  if(entry < 0){
    return(fEventChain->GetEntry(fCurrentEvent,getall));
  }else{
    fCurrentEvent=entry;
    return(fEventChain->GetEntry(entry,getall));
  }
    
}

//=======================================================================
Int_t TDSTReader::Next(){
  // Next() reads next available Entry in TREE into 
  // Clone Arrays. On success returns 0 otherwise -1 will
  // be returned..
  //  fCurrentEvent = 17;
  Int_t status = kNOERR;
  if(fCurrentEvent >= fEventChain->GetEntriesFast()-1){
    if(fDebug_Mode& (kDBG_Info | kDBG_Error))
       cout << "TDSTReader::Next : End of Event Entries Reached !" << endl;

    status = kERR_end_of_file;
  } else {
    //    cout  << "Reading next event " <<  fEventChain->GetEntries() << endl;
    CleanEventClones();
    fEventChain->GetEntry(++fCurrentEvent);
    //    PrintEventStatus();
  }
  return status;
}


//=======================================================================
Bool_t TDSTReader::Notify(){
  // This is a virtual stub. The code does nothing, but is intended to be
  // replaced by your own code. You point to your own code with the SetNotify() method.
  //  
  if(fDebug_Mode&kDBG_Info)  cout << "DSTReader: File in chain has changed..." << endl;
  return kTRUE;
}


//=======================================================================
void TDSTReader::InitClones(){
  //  InitClones Initializes Clone Arrays for all Banks.
  //  This should only be called once. 

  if(fClones.GetEntries()){
    cerr << "Clones Arrays are not empty. You cannot initialize twice!\n";
    return;
  }

  
  fClones.Add(new TStoreClone("EVNT","TEVNTClass",10));
  fClones.Add(new TStoreClone("SCPB","TSCPBClass",10));
  fClones.Add(new TStoreClone("ECPB","TECPBClass",10));
  fClones.Add(new TStoreClone("DCPB","TDCPBClass",10));
  fClones.Add(new TStoreClone("CCPB","TCCPBClass",10));
  fClones.Add(new TStoreClone("ICPB","TICPBClass",10));
  fClones.Add(new TStoreClone("ICHB","TICHBClass",10));
  fClones.Add(new TStoreClone("FBPM","TFBPMClass",10));
  fClones.Add(new TStoreClone("LCPB","TLCPBClass",10));
  fClones.Add(new TStoreClone("TGBI","TTGBIClass",10));
  fClones.Add(new TStoreClone("STPB","TSTPBClass",10));
  fClones.Add(new TStoreClone("TGPB","TTGPBClass",10));
  fClones.Add(new TStoreClone("TAGR","TTAGRClass",10));
  fClones.Add(new TStoreClone("VERT","TVERTClass",10));
  fClones.Add(new TStoreClone("MVRT","TMVRTClass",10));
  fClones.Add(new TStoreClone("TBER","TTBERClass",10));
  fClones.Add(new TStoreClone("MCHD","TMCHDClass",10));
  fClones.Add(new TStoreClone("GSIM","TGSIMClass",10));

  // Scaler Clones.

  fScalerClones.Add(new TStoreClone("HLS","THLSClass",624));
  fScalerClones.Add(new TStoreClone("TRGS","TTRGSClass",1));
  fScalerClones.Add(new TStoreClone("S1ST","TS1STClass",1));

}

//=======================================================================
void TDSTReader::CleanEventClones(){
  //  CleanClones Cleans Clone arrays to Read new 
  //  Entry from the tree.
  //  Calls Clear() which is faster than Delete(),
  //  according to TClonesArray documentation Clear() should be faster.
  //

  TIter next(&fClones);
  TStoreClone *this_clone;
  while( (this_clone=(TStoreClone *)next() ) ){
    this_clone->Clear();
  }
}

//=======================================================================
void TDSTReader::CleanScalerClones(){
  //delete all scaler clone arrays

  TIter next(&fScalerClones);
  TClonesArray *this_clone;
  while( (this_clone=(TClonesArray *)next() ) ){
    this_clone->Clear();
  }
}

//=======================================================================
void TDSTReader::InitBranches(){
  //  InitBranches Initialize Branches 
  //
  // Setup Event Branches and set branch addresses
  // to  ClonesArrays
  //
  // Not every file is always going to contain all branches.
  // We test the presence of the branch before setting the BranchAddress,
  // since setting the address on a branch that is not in the file causes a fault.
  //

  //  fEventChain->SetBranchStatus("*",1);

  if(fDebug_Mode&kDBG_Info)cout << "Initializing branches..." << endl;
  if(fEventChain->GetBranchStatus("HEADER")){
    fEventChain->SetBranchAddress("HEADER",&fEvntHeader);
  }else{
    printf("SEVERE WARNING: NO HEADER BANK IN FILE.\n");
  }

  TIter next(&fClones);
  TStoreClone *this_clone;
  while( (this_clone=(TStoreClone *)next() ) ){
    TClonesArray** ptr2ptr = this_clone->GetClonesArray();

    if(fEventChain->GetBranchStatus(this_clone->GetCloneName())){
      fEventChain->SetBranchAddress(this_clone->GetCloneName(),ptr2ptr);
    }
    else if(fDebug_Mode&kDBG_Info){
      cout << "WARNING: NO " << this_clone->GetCloneName() << " BANK IN FILE.\n";
    }    
  }
  
  // Setup Scaler Branches
  if(fReadScaler){
    if(fScalerChain){
      fScalerChain->SetBranchStatus("*",1);
      
      if(fScalerChain->GetBranchStatus("Last_Evt_Num")){
 	fScalerChain->SetBranchAddress("Last_Evt_Num",&fScalerLastEvt);
      }else{
 	if(fDebug_Mode&kDBG_Info)cout << "WARNING: NO Last_Evt_Num IN FILE.\n";
      }

      if(fScalerChain->GetBranchStatus("SC_HEAD")){
 	fScalerChain->SetBranchAddress("SC_HEAD",&fScalerHead);
      }else{
 	if(fDebug_Mode&kDBG_Info)cout << "WARNING: NO SC_HEAD BANK IN FILE.\n";
      }
      
      next=(&fScalerClones);
      while( (this_clone=(TStoreClone *)next() ) ){
	TClonesArray** ptr2ptr = this_clone->GetClonesArray();
	
	if(fScalerChain->GetBranchStatus(this_clone->GetCloneName())){
	  fScalerChain->SetBranchAddress(this_clone->GetCloneName(), ptr2ptr);
	}
	else if(fDebug_Mode&kDBG_Info){
	  cout << "WARNING: NO " << this_clone->GetCloneName() << " BANK IN FILE.\n";
	}    
      }

      
    } else {
      if(fDebug_Mode & kDBG_Error){
 	cout << "TDSTReader::InitBranches (ERROR): The SCALER Chain is not initialized..." << endl;
      }
    }  
  }
}

//=======================================================================
void TDSTReader::Print(Int_t full){
  // Print information about this reader. 
  // With argument full=1 print even more information.

  
  cout << "OBJ: TDSTReader   -- Reads root files created with WriteRootDST. \n\n";
  cout << "Currently contains: " <<  fEventChain->GetNtrees() << " files with ";
  cout << fEventChain->GetEntries() << " physics events and ";
  if(fScalerChain){
    cout << fScalerChain->GetEntries();
  }else{
    cout << "0";
  }
  cout << " scaler events.\n";

  PrintEventStatus();

  if(full){
    fEventChain->Print();
  }


}

//======================================================================

void TDSTReader::InitEPICBranch()
  //
// Set the Branch Address for the fEPIC pointer.
{
  if(fEPICChain){
    if(fDebug_Mode&kDBG_Info)cout << "Initializing branches..." << endl;
    if(fEPICChain->GetBranchStatus("EPICBranch")){
      fEPICChain->SetBranchAddress("EPICBranch",&fEPIC);
    } else{
      cout << "WARNING: FILE CONTAINS NO EPIC BRANCH!!" <<endl;
    }
  }
}

//=====================================================================

void TDSTReader::MakeEPICTable()
  //
// Makes a table containing the last physics event number before each
// Epic. The table is used in GetValue to search for the EPIC entry 
// corresponding to the current physics event.
{
  Int_t Entries = fEPICChain->GetEntries(); //avoid multiple calls
  EPICTable = new TArrayI(Entries);

  for(Int_t i=0; i<Entries&&fEPICChain->GetEntry(i); i++){
    EPICTable->AddAt(fEPIC->Last_Phys,i);
  }
  fEPICChain->GetEntry(fCurrentEPIC); //reset fEPICChain
}

//=======================================================================
void TDSTReader::PrintEventStatus(){
//
// For Debugging ETC, print usefull information on this event.
// (To be extended )
//
  if (fCurrentEvent < 0) {
    cout << "No Current Event to Display! Make sure you have some event read in!" << endl;
  } else {
    cout << endl << "Status on Run # " << fEvntHeader->NRun <<" Event #" << fEvntHeader->NEvent << endl;
    cout << " Bank    |  # entries  " << endl;
    cout << "---------+-------------" << endl;

    TIter next(&fClones);
    TStoreClone *this_clone;
    while( (this_clone=(TStoreClone *)next() ) ){
      TClonesArray *ptr = *(this_clone->GetClonesArray());
      cout << this_clone->GetCloneName() << "    |       " << ptr->GetEntries() << endl;
    }
  }
}

//=======================================================================

void TDSTReader::PrintEPICPosition(){
  //Print out the run number and the range of event numbers for the
  //current EPIC. Useful for debugging purposes.
 
  cout << "fCurrentEPIC is " << fCurrentEPIC << endl; 
  cout << "The current EPIC run number is " << fEPIC->runno <<" ." << endl;
  cout << "The current HEADER run number is " << GetRunNumber() <<" ." << endl;
  if(fCurrentEPIC<fEPICChain->GetEntries()&&fCurrentEPIC>=0&&EPICTable){
    cout << "The range of the current EPIC is from event number " << EPICTable->At(fCurrentEPIC);
    if((fCurrentEPIC+1)<EPICTable->GetSize()){
      cout << " to " << EPICTable->At(fCurrentEPIC+1) << " ." << endl;}
    else cout << " to end of file." << endl;
  }else cout << "The current epic is not in range. " << endl;
  cout << "The current HEADER event number is " << GetEventNumber() << endl;

}

//=======================================================================

Float_t TDSTReader::GetEPICValue(const char *fName)
  //
  // Return the EPIC value corresponding to name for the current EPIC event
  // Changes fCurrentEPIC to the Entry corresponding to the current physics
  // event#. Leave this as a sequential search because it is unlikely that 
  // the relevant EPIC will change rapidly enough in between calls to make 
  // a binary search more effiecient. Right now this is done the "safe" way, 
  // that is GetEntry is called each time fCurrentEPIC is updated. The table
  // could allow you to find the right event without this call but using this
  // call allows us to check the run number each time.
{
 
  if(!EPICTable||EPICTable->GetSize()<fEPICChain->GetEntries()) {
    MakeEPICTable();
    if(fDebug_Mode&kDBG_Info) cout << "EPIC Table Made " << endl;
  } //If table is not made, make it
  if(fCurrentEPIC<fEPICChain->GetEntries()&&fCurrentEPIC>=0){
    if((fCurrentEPIC+1)<EPICTable->GetSize()){
      if(GetRunNumber() == fEPIC->runno){
	//first check against current EPIC
	if((GetEventNumber()>EPICTable->At(fCurrentEPIC))&&
	   (GetEventNumber()<=EPICTable->At(fCurrentEPIC+1))){
	  fEPICChain->GetEntry(fCurrentEPIC);
	  return(fEPIC->GetValue(fName));
	}//otherwise scan up or down to find the correct EPIC
	else if(EPICTable->At(fCurrentEPIC)>EPICTable->At(fCurrentEPIC+1)){
	  //special condition for last epic in run
	  fEPICChain->GetEntry(fCurrentEPIC);
	  return(fEPIC->GetValue(fName));
	}else if(GetEventNumber()>EPICTable->At(fCurrentEPIC+1)){
	  fEPICChain->GetEntry(fCurrentEPIC++);
	  return (GetEPICValue(fName));
	} else{
	  fEPICChain->GetEntry(fCurrentEPIC--);
	  return (GetEPICValue(fName));
	}
      }else if(GetRunNumber()>fEPIC->runno){
	fEPICChain->GetEntry(fCurrentEPIC++);
	return (GetEPICValue(fName));
      }
      else{
	fEPICChain->GetEntry(fCurrentEPIC--);
	return (GetEPICValue(fName));
      }
    }else{///special case for last EPIC, in which case there is no next one
      fEPICChain->GetEntry(fCurrentEPIC);
      return(fEPIC->GetValue(fName));
    }
  }
  else{
    cout << "Error: fCurrentEPIC is out of bounds." << endl;
    cout << "Resetting fCurrentEPIC to zero." << endl;
    fCurrentEPIC = 0; 
  }
  return (0.);
}



//=======================================================================
Int_t TDSTReader::GetNRows(const Char_t *bankname){
//   This Function returns number of rows (number of 
// entries) of specified Bank (Clones Array). The string
// argument passed to function is the name of bank.
// EVNT,ECPB,SCPB,DCPB,CCPB or LCPB.
// Any other string passed to function will return -1 
// indicating that there is no bank with that name...
//
  TClonesArray *ptr = GetClone(bankname);
  if(ptr)  return ptr->GetEntries();
  else return -1;
}

//=======================================================================
Int_t     TDSTReader::GetCurrentEvent(){
  // Returns the number of the current event in the Next() sequence.
  // This is not the "Physics event" number, which you get from the header class.

  return fCurrentEvent;
}

//=======================================================================
Int_t     TDSTReader::GetEventNumber(){
  // Return the current event number.
  // This is the "Physics event" number, which you get from the header class.

  return(fEvntHeader->NEvent);
}

//=======================================================================
Int_t     TDSTReader::GetRunNumber(){
  // Return the current run number.

  return(fEvntHeader->NRun);
}

//=======================================================================
TObject  *TDSTReader::GetBankRow(const Char_t *bankname,Int_t nrow){
  //
  // Get a specific bank given the bankname at a specific row given the row name  

  TClonesArray *BankStore = GetClone(bankname);
  
  if(BankStore == NULL){
    if(fDebug_Mode& kDBG_Error) cout << "TClasTool::GetBankRow (ERROR): Can not find Bank \"" << bankname <<"\" " << endl;
    return NULL;
  } else {
    if(nrow<0 || nrow >= BankStore->GetEntries()){
      if(fDebug_Mode& kDBG_Error) cout << "TClasTool::GetBankRow (ERROR): Bank \"" << bankname <<"\" has only " << BankStore->GetEntries() << " entries "<< endl << "Can not get row  # " << nrow << endl << "Use rows from 0 to " << BankStore->GetEntries() << endl;
      return NULL;
    } else {
      return (TObject *) BankStore->At(nrow);
    }
  }
}

//=======================================================================
GetEntries_return_t   TDSTReader::GetEntries() const{
  // Return the number of entries in the total chain.
  return fEventChain->GetEntries();
}

//=======================================================================
GetEntries_return_t   TDSTReader::GetEntriesFast() const{
  // Return the number of entries faster. Not always
  // correct, if a call to GetEntries() has not been
  // done since the last file was added.
  return fEventChain->GetEntriesFast();
}

//=======================================================================
TVector3  TDSTReader::GetPart3Vector(Int_t indx){
  TVector3 v3vect(0,0,0);
  if(indx>=0 && indx<GetNPart()){
    TEVNTClass *cEvnt = (TEVNTClass *) GetBankRow("EVNT",indx);
    if(cEvnt!=NULL){ 
      v3vect.SetXYZ(cEvnt->GetPx(),cEvnt->GetPy(),cEvnt->GetPz()); 
    } else if(fDebug_Mode&kDBG_Error) cout << "GetPart3Vector: Particle does not exist.." << endl;
  } else if(fDebug_Mode&kDBG_Error) cout << "GetPart3Vector: Cannot find particle at row " << indx 
	      << "  there are only " << GetNPart() << "  particle in the event" << endl;
  return v3vect;
}

//=======================================================================
TVector3  TDSTReader::GetPartVertex(Int_t indx){
  TVector3 v3vect(0,0,0);
  if(indx>=0 && indx<GetNPart()){
    TEVNTClass *cEvnt = (TEVNTClass *) GetBankRow("EVNT",indx);
    if(cEvnt!=NULL){ 
      v3vect.SetXYZ(cEvnt->GetX(),cEvnt->GetY(),cEvnt->GetZ()); 
    } else if(fDebug_Mode&kDBG_Error) cout << "GetPart3Vector: Particle does not exist.." << endl;
  } else if(fDebug_Mode&kDBG_Error) cout << "GetPart3Vector: Cannot find particle at row " << indx 
	      << "  there are only " << GetNPart() << "  particle in the event" << endl;
  return v3vect;
}
      
//=======================================================================
Int_t     TDSTReader::GetPartID(Int_t indx){
  Int_t  p_id = 0;
  if(indx>=0 && indx<GetNPart()){
    TEVNTClass *cEvnt = (TEVNTClass *) GetBankRow("EVNT",indx);
    if(cEvnt!=NULL){ 
      p_id = cEvnt->GetId();
    } else if(fDebug_Mode&kDBG_Error)  cout << "GetPartID: Particle does not exist.." << endl;
  } else if(fDebug_Mode&kDBG_Error) cout << "GetPartID: Cannot find particle at row " << indx 
	      << "  there are only " << GetNPart() << "  particle in the event" << endl;
  return p_id;
}

//=======================================================================
Int_t     TDSTReader::GetPartCharge(Int_t indx){
  Int_t  p_ch = 0;
  if(indx>=0 && indx<GetNPart()){
    TEVNTClass *cEvnt = (TEVNTClass *) GetBankRow("EVNT",indx);
    if(cEvnt!=NULL){ 
      p_ch = cEvnt->GetCharge();
    } else if(fDebug_Mode&kDBG_Error) cout << "GetPartCharge: Particle does not exist.." << endl;
  } else if(fDebug_Mode&kDBG_Error) cout << "GetPartCharge: Cannot find particle at row " << indx 
	      << "  there are only " << GetNPart() << "  particle in the event" << endl;
  return p_ch;
}

//=======================================================================
TString   TDSTReader::GetReaderType(){
  TString rtype("ROOTDSTR2.0");
  return rtype;
}

//=======================================================================
TChain *TDSTReader::GetTree(Char_t *treename){
  // Returns the TTree opened by this reader.
  // For the SCALER TTree the argument must start with an S
  // Note that this actually passes a TChain * (a type of TTree *).
  if(treename[0]=='S'){
    return(fScalerChain);
  }else{
    return(fEventChain);
  }
}

//=======================================================================
Int_t     TDSTReader::GetHelicity()
{
  return  fEvntHeader->Latch1;
}

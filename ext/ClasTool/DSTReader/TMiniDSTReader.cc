// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>
//____________________ 
//  TMiniDSTReader is a calls implements tools for Reading ROOT DST's
//  without any run group specific details. 
//  It will contain tools only to read EVENT and Scaller trees.
// 
// ________________________________________________________________
//
//   Author : G.Gavalian (UNH) 04/02/2002
//  
//


#include "TMiniDSTReader.h"


ClassImp(TMiniDSTReader)

TMiniDSTReader::TMiniDSTReader()
{
  //  Default Constructor.
  //  Default Debug mode is 1
  //  To change it use SetDebugMode(debugmode)
 
  //  fDebug_Mode   = kDBG_Error+kDBG_Info;

  //  fDebug_Mode = kDBG_Error+kDBG_Info;

  //  fDebug_Mode   = 0;

  fEventChain   = new TChain("MINI_EVNT");
  fEvntHeader   = new TMiniHEADClass();
  fPElectron    = new TMiniDSTClass();
  fPProton      = new TMiniDSTClass();
  
  fCurrentEvent  = -1;

  // Initialize Clone Arrays
  fcaPARTStore = NULL;
  fcaGSIMStore = NULL;
  InitClones();

  //  fEventChain->SetNotify(this);
}

TMiniDSTReader::~TMiniDSTReader()
{
  // Default Destructor
  //  Destroys Chains
  //

  delete fEventChain;
}

Int_t     TMiniDSTReader::GetEventNumber(){
  // Return the current event number.
  // This is the "Physics event" number, which you get from the header class.

  return(fEvntHeader->NEvent);
}
Int_t     TMiniDSTReader::GetRunNumber(){
  // Return the current run number.

  return(fEvntHeader->NRun);
}

Int_t TMiniDSTReader::Add(const Char_t *name){
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


Int_t TMiniDSTReader::AddFile(const Char_t *filename)
{
//   AddFile(const Char_t *filename)
//  
//   This Method Adds new File into Chain of
//  files to be analysed. Changes Value of 
// variable nFilesinChain 
//
//  cout << "Looking for file File " << filename << endl;
  if(access(filename,R_OK) == 0){
    //  cout << "TClasTool::AddFile : File \"" << filename << "\" is added to Chain" << endl;
    if(!fEventChain->Add(filename) || fEventChain->GetNtrees() == 0){
      cerr << "Could not properly add the file " << filename << " to event chain.\n";
    }
    
    if( GetNFiles() == 1 ) {
      // One File in the chain, so this is first time we added one.
      cout << "TClasTool::AddFile (INFO): First file added. Initializing Branches" << endl;
      InitBranches();
    }
    
    return 0;
    
  } else {
    
    cout << "TClasTool::AddFile (ERROR): Cannot access \"" << filename << "\" file for reading" << endl;
    return -1;
  }
  
}

Int_t TMiniDSTReader::ReadNext(){
  return Next();
}

Int_t TMiniDSTReader::ReadEvent(Int_t evtnum){
  cout << "TMiniDSTReader::ReadEvent: this function is not implemented yet." << endl;
  return 0;
}


Int_t TMiniDSTReader::Next(){
  // Next() reads next available Entry in TREE into 
  // Clone Arrays. On success returns 0 otherwise -1 will
  // be returned..
  //  fCurrentEvent = 17;
  Int_t status = 0;
  if(fCurrentEvent >= fEventChain->GetEntries()-1){
    cout << "TMiniDSTReader::Next : End of Event Entries Reached !" << endl;
    status = -1;
  } else {
    //    cout  << "Reading next event " <<  fEventChain->GetEntries() << endl;
    CleanEventClones();
    fEventChain->GetEntry(++fCurrentEvent);
    //    PrintEventStatus();
  }
  return status;
}


Bool_t TMiniDSTReader::Notify(){
  // This is a virtual stub. The code does nothing, but is intended to be
  // overwriten by your own code. It will be called by ReadScaler() 
  // every time a new scaler was read. 
  cout << "DSTReader: File in chain has changed..." << endl;
  return kTRUE;
}



void TMiniDSTReader::InitClones(){
  //   InitClones Initializes Clone Arrays for Banks if they are 
  //  not initialized.  
  // Initialize EVNT Clones Array 

  if(fcaPARTStore==NULL){ 
    fcaPARTStore = new TClonesArray("TMiniDSTClass",10,kTRUE);
    cout << "TMiniDSTReader::InitClones : Initializing EVNT Clones Array" << endl;
  }
  if(fcaGSIMStore==NULL){ 
    fcaGSIMStore = new TClonesArray("TGSIMClass",10,kTRUE);
    cout << "TMiniDSTReader::InitClones : Initializing GSIM Clones Array" << endl;
  }

  // Initialize SCPB Clones Array 
}

//--------------------------------------------------------------------------------
void TMiniDSTReader::CleanEventClones(){
  //  CleanClones Cleans Clone arrays to Read new 
  //  Entry from the tree.
  //  Calls Clear() which is faster than Delete(),
  //  according to TClonesArray documentation Clear() should be faster.
  //
    if(fcaPARTStore != NULL) fcaPARTStore->Clear(); 
    if(fcaGSIMStore != NULL) fcaGSIMStore->Clear(); 
}

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
void TMiniDSTReader::InitBranches(){
  //  InitBranches Initialize Branches 
  //
  // Setup Event Branches and set branch addresses
  // to  ClonesArrays
  //

  if(fEventChain){
    fEventChain->SetBranchAddress("HEADER",&fEvntHeader);
    //    fEventChain->SetBranchAddress("ELECTRON",&fPElectron);
    //    fEventChain->SetBranchAddress("PROTON",&fPProton);
    fEventChain->SetBranchAddress("EVNT",&fcaPARTStore);
    fEventChain->SetBranchAddress("GSIM",&fcaGSIMStore);

  }
  fEventChain->SetBranchStatus("*",1);
}


void TMiniDSTReader::PrintSummary(){
  // Print the counters to the standard output.

  cout << "Summary of statistics:  \n\n";
  //  fCounters.Print();
}

//--------------------------------------------------------------------------------
void TMiniDSTReader::PrintEventStatus(){
//
// For Debugging ETC, print usefull information on this event.
// (To be extended )
//
  if (fCurrentEvent < 0) {
    cout << "No Current Event to Display! Make sure you have some event read in!" << endl;
  } else {
    cout << endl << "Status on Run # " << fEvntHeader->NRun <<" Event #" << fEvntHeader->NEvent 
	 << " NROWS : " << GetNRows("PART") << endl;
  }
}

//--------------------------------------------------------------------------------

Int_t TMiniDSTReader::GetNRows(const Char_t *bankname){
//   This Function returns number of rows (number of 
// entries) of specified Bank (Clones Array). The string
// argument passed to function is the name of bank.
// EVNT,ECPB,SCPB,DCPB,CCPB or LCPB.
// Any other string passed to function will return -1 
// indicating that there is no bank with that name...
//
  Int_t nRows = fcaPARTStore->GetEntries();

  if(strcmp(bankname,"GSIM")==0) nRows = fcaGSIMStore->GetEntries();

  return nRows;
}

// Int_t     TMiniDSTReader::GetEventNumber()
// {
//   return fCurrentEvent;
// }
TObject  *TMiniDSTReader::GetBankRow(const Char_t *bankname,Int_t nrow){
  //
  // Get a specific bank given the bankname at a specific row given the row name  

  //  if(nrow==0) return fPElectron;
  //  if(nrow==1) return fPProton;
  if(strcmp(bankname,"HEADER")==0) return fEvntHeader;

  if(strcmp(bankname,"GSIM")==0){
    if(nrow>=0&&nrow<GetNRows("GSIM")) return fcaGSIMStore->At(nrow);
    else return NULL;
  }

  if(nrow>=0&&nrow<GetNPart()){
    return fcaPARTStore->At(nrow);
  }

  return NULL;
}


Int_t   TMiniDSTReader::GetChainEntries()
{
  return (Int_t) fEventChain->GetEntries();
}

Int_t  TMiniDSTReader::GetNPart(){
  return GetNRows("EVNT");
}

TVector3  TMiniDSTReader::GetPart3Vector(int indx){
  TVector3 v3vect(0,0,0);
  if(indx>GetNPart()) return v3vect;
    
  //  if(indx==0||indx==1){
  //    if(indx==0){
  //      v3vect.SetXYZ(fPElectron->GetPx(),fPElectron->GetPy(),fPElectron->GetPz());
  //    } else {
  //      v3vect.SetXYZ(fPProton->GetPx(),fPProton->GetPy(),fPProton->GetPz());
  //    }
  //  } else {
    TMiniDSTClass *mdst = (TMiniDSTClass *) GetBankRow("PART",indx);
    v3vect.SetXYZ(mdst->GetPx(),mdst->GetPy(),mdst->GetPz());
    //  }
  return v3vect;
}
      
TVector3  TMiniDSTReader::GetPartVertex(Int_t indx){
  TVector3 v3vect(0,0,0);
  if(indx>GetNPart()) return v3vect;
  TMiniDSTClass *mdst = (TMiniDSTClass *) GetBankRow("PART",indx);
  v3vect.SetXYZ(mdst->GetVxp(),mdst->GetVyp(),mdst->GetVzp());
  return v3vect;
}

Int_t     TMiniDSTReader::GetPartID(int indx){
  Int_t  p_id = 2212;
  //  if(indx==0) p_id = 11;
  //  if(indx >1) p_id = 22;
  TMiniDSTClass *mdst = (TMiniDSTClass *) GetBankRow("PART",indx);
  p_id = mdst->GetPartID();
  return p_id;
}

Int_t     TMiniDSTReader::GetPartCharge(int indx){
  Int_t p_ch = 1;
  if(indx>1) p_ch  = 0;
  if(indx==0) p_ch = -1;
  TMiniDSTClass *mdst = (TMiniDSTClass *) GetBankRow("PART",indx);
  return (int) mdst->GetPq();
}

TString   TMiniDSTReader::GetReaderType(){
  TString rtype = "ROOTMINIDSTR2.0";
  return rtype;
}

Int_t     TMiniDSTReader::GetHelicity()
{
  return  fEvntHeader->Helicity;
}

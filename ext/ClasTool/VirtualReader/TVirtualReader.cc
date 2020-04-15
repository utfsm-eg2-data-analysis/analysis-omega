// @(#)VirtualReader/TVirtualReader:$Name:  $:$Id: TVirtualReader.cc,v 1.12 2007/03/01 22:27:00 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all.            *
 *                                                                          *
 * Documentation  : TVirtualReader.html                                     *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  04/2/2002 (UNH)                                        *
 * Initial Authors:  Maurik Holtrop (UNH) Gagik Gavalian (UNH)              *
 ***************************************************************************/

//____________________ 
//Begin_Html <!--
/* -->
<h1>TVirtualReader</h1>
<p>
TVirtualReader is the underlying class from which all reader implementations
in ClasTool must inherit. 
Many of the methods of this class are dummies that must be overridden by the
real function of the reader class that inherits from TVirtualReader.
</p><p>
Some functions will be implemented in this class rather than in TClasTool if they
are "closer to the data", in other words, these functions would be useful for 
different readers (general enough) yet are specific enough that some DST formats
would need an alternate implementation.
</p><p>
Note that to be useful, each method that is relevant for physics analysis (i.e. all 
the public methods) must have a call implementation in TClasTool. Otherwise calls to 
that method must be done on the pointer to the reader, which is highly in elegant. 
That is the "price we pay" for a design that allows different readers using a pointer
to the reader instead of inheriting from the reader.
</p>
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////////////////////////////////////

#include "TVirtualReader.h"

Int_t  TVirtualReader::fgInstanceCount =0;

ClassImp(TVirtualReader)

TVirtualReader::TVirtualReader(){
  fThisInstance= ++fgInstanceCount; // Counts how many copies we got.

}
TVirtualReader::~TVirtualReader(){
  fgInstanceCount--;
  if(fgInstanceCount==0){

  }

}

Int_t TVirtualReader::Add(const Char_t *filename){
  // Add new files to the list of files to be analyzed.
  // The filename may use wildcards to add multiple files all at once.
  // returns the actual number of files added or zero.
  // Actually adds files by repeated calls to AddFile().
  cout << "TVirtualReader::Addfile(filename) is not implemented in this class: " << GetReaderType() << endl;
  return 0;
}

Int_t TVirtualReader::AddFile(const Char_t *filename,Int_t nentries){
  // Add a single file to the list of files to be analyzed.
  // Returns a negative number if the files could not be opened.
  // On first file opened, must initialize the reader.
  cout << "TVirtualReader::Addfile(filename) is not implemented in this class: " << GetReaderType() << endl;
  return -1;
}

Int_t TVirtualReader::AddEPICFile(const Char_t *filename, Int_t nentries){
  // Add a single file to the list of epic files to be analyzed.
  // Returns a negative number if the files could not be opened.
  // On first file opened, must initialize the reader.
  cout << "TVirtualReader::AddEPICFile(filename) is not implemented in this class: " << GetReaderType() << endl;
  return -1;
}

Int_t TVirtualReader::Next(){
  // Read the next event and make the contends available.
  cout << "TVirtualReader::Next() is not implemented in this class: " << GetReaderType() << endl;
  return 0;
}

Int_t TVirtualReader::GetNFiles(){
  // Returns the number of files in the current list of files to be analyzed.
  cout << "TVirtualReader::GetNFiles() is not implemented in this class: " << GetReaderType() << endl;
  return 0;
}

void TVirtualReader::Reset(){
  // Main reset of class. Clean up and return to reading the very first event.
  cout << "TVirtualReader::Reset() is not implemented in this class: " << GetReaderType() << endl;
}

Int_t TVirtualReader::ReadEvent(Int_t event,Int_t runnum){
  // Read a specific event from the run with runnum.
  // THIS IS EXPENSIVE! We need to SEARCH for that specific event. 
  // Usually you want to use Next() or GetEntry() which are both quite a bit faster.
  //
  // Returns the event number of the event actually read. Since it is possible the 
  // event is not found
  //
  // Specify runnum if you want to search for a runnum other than the current one.
  //
  // This is the "generic" version you may which to override.
  // This is currently the stupid way to do this, should be a binary search.
  // It is the user's responsibility to load files with different runnumbers in 
  // sequential order.

  Int_t current_event = GetEventNumber();
  Int_t current_run   = GetRunNumber();

  if(runnum != 0){
    if(runnum < current_run ){ 
      GetEntry(1);             // go to top of file
      current_run = GetRunNumber();
      if(runnum < current_run) return(0);
    }

    while(runnum > current_run){
      Next();                        
      current_run = GetRunNumber();
    }
  }else{ 
    runnum = current_run; 
  }

  while(event < current_event && runnum >= current_run ){
    fCurrentEvent = fCurrentEvent - 1000;
    if(current_event>0){
      GetEntry(fCurrentEvent);
      current_event = GetEventNumber();
      current_run   = GetRunNumber();
    }else {
      GetEntry(0);
      current_event = GetEventNumber();
      current_run   = GetRunNumber();
      if(event<current_event || runnum<current_run)return(0);
    }
  }

  return(0);
}

Int_t  TVirtualReader::GetEntry(Int_t entry,Int_t getall){
  // Find a specific event in the list of events. The n-th event is returned,
  // not the event with event_number = entry! For that use the ReadEvent() method.
  cout << "TVirtualReader::GetEntry() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}

GetEntries_return_t  TVirtualReader::GetEntries() const{
  // Return total number of entries in the chain.
  cout << "TVirtualReader::GetEntries() is not implemented in this class. " << endl;
  return((GetEntries_return_t)-999.);
}


GetEntries_return_t  TVirtualReader::GetEntriesFast() const {
  // Fast way to return the number of entries in the chain by regurgitating a
  // stored value. This value may not be accurate. (See TChain::GetEntriesFast )
  cout << "TVirtualReader::GetEntriesFast() is not implemented in this class: " << endl;
  return((GetEntries_return_t)-999.);
}

Float_t TVirtualReader::GetEPICValue(const Char_t *fName){
  //Returns the EPIC value associated with fName
  cout << "TVirtualReader::GetEPICValue(const Char_t* fName) is not implemented in this class: " << endl;
  return (0.);
}

void   TVirtualReader::Browse(TBrowser *B){
  // Browse the class with Browser b.
  cout << "TVirtualReader::Browse() is not implemented in this class: " << GetReaderType() << endl;
  return;
}


Int_t    TVirtualReader::Draw(const char *varexp, const char *selection, Option_t *option
			      ,Int_t nentries, Int_t firstentry){
  // Same as the TChain::Draw command, allows you to make instant plots of variables in the 
  // files. This is harder to implement and so not all readers will support this!
  cout << "TVirtualReader::Draw() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}

TObjArray *TVirtualReader::GetFiles(void){
  // Return a TObjArray containing a list of the currently attached files. See TChain::GetFiles()
  cout << "TVirtualReader::GetFiles() is not implemented in this class: " << GetReaderType() << endl;
  return(NULL);
}

Int_t     TVirtualReader::GetNtrees(void){
  // Return the number of trees attached. See TChain::GetNtrees()
  cout << "TVirtualReader::GetNtrees() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}

Int_t     TVirtualReader::GetTreeNumber(void){
  // Return the number of the current tree being read. See TChain::GetTreeNum()
  cout << "TVirtualReader::GetTreeNum() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}

Bool_t   TVirtualReader::Notify(){
  // Routine that will call the Notify set by SetNotify.
  if(GetNotify()){ 
    return(GetNotify()->Notify());
  }else{
    cout << "TVirtualReader::Notify() did nothing for class: " << GetReaderType() << endl;
    return(kFALSE);
  }
}

void   TVirtualReader::SetNotify(TObject *obj){
  // This cannot be implemented here, it must be implemented in the
  // actual reader.  
  // The argument must be a class that is derived from TObject and has
  // a sensible Notify() method.
  // The SetNotify call will set a hook to call the Notify() of your 
  // class whenever a new file is opened. I.e. the first file, or when
  // you go from the first to the second, etc. This is useful for 
  // initializations that depend on the file being there already, and 
  // it is useful for detecting runnumber changes.
  cout << "Cannot set notify in TVirtualReader class: " << GetReaderType()<< endl;
}

Int_t  TVirtualReader::GetNPart(){
  // Get the number of particles in this event. Calls GetNRows("EVNT")
  return GetNRows("EVNT");
}

TVector3  TVirtualReader::GetPart3Vector(Int_t indx){
  // Return the momentum 3 vector for a particle at index indx, for this event.
  TVector3 v3vec(0,0,0);
  cout << "TVirtualReader::GetPart3Vector() is not implemented in this class: " << GetReaderType() << endl;
  return v3vec;
}

TVector3  TVirtualReader::GetPartVertex(Int_t indx){
  // Return the vertex 3 vector for a particle at index indx, for this event.
  TVector3 v3vec(0,0,0);
  cout << "TVirtualReader::GetPartVertex() is not implemented in this class: " << GetReaderType() << endl;
  return v3vec;
}

Int_t     TVirtualReader::GetPartID(Int_t indx){
  // Return the particle ID (SEB style) for the particle at index indx for this event.
  cout << "TVirtualReader::GetPartID() is not implemented in this class: " << GetReaderType() << endl;
  return(-9999);
}

Int_t     TVirtualReader::GetPartCharge(Int_t indx){
  // Return the charge of the particle at index indx for this event.
  cout << "TVirtualReader::GetPartID() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}


TString   TVirtualReader::GetReaderType(){
  // Return the type of the reader that is implemented.
  TString rtype("VIRTUAL");
  return rtype;
}

TEPICClass *TVirtualReader::GetEPICClass(){
  //Return current EPIC
  cout <<"GetEPICClass() not implemented in this class " << GetReaderType() << endl;
  return NULL;
}

THEADERClass *TVirtualReader::GetHEADER(){
  // Return the HEADER bank for the current event.
  cout << "TVirtualReader::GetHead() is not implemented in this class: " << GetReaderType() << endl;
  return NULL;
}

Int_t   TVirtualReader::GetHelicity(){
  // Return the helicity of the current event: -1 or 1 for proper helicity, 0 for error.
  Int_t helicity = 0;
  cout << "TVirtualReader::GetHelicity() is not implemented in this class: " << GetReaderType() << endl;
  return helicity;
}

TChain *TVirtualReader::GetTree(char *treename){
  // Return a pointer to the TChain. 
  // If reader is not capable of returning a TChain, it will return NULL.
  return NULL;
}

void  TVirtualReader::Print(Int_t full){
  // Print to the screen a summary of the status for this event. Useful for debugging.
  cout << "TVirtualReader::Print() is not implemented correctly in this class: " << GetReaderType() << endl;
}

void  TVirtualReader::PrintEventStatus(){
  // Print to the screen a summary of the status for this event. Useful for debugging.
  cout << "TVirtualReader::PrintEventStatus() is not implemented in this class: " << GetReaderType() << endl;
}

void  TVirtualReader::PrintEPICPosition(){
  //Print the position of current EPIC
  cout << "TVirtualReader::PrintEPICPosition() notimplemented in this class: " << GetReaderType() << endl;
}

Int_t     TVirtualReader::GetNRows(const Char_t *bankname){
  // Return the number of rows for the bank with "bankname" for this event.
  cout << "TVirtualReader::GetNRows() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}

TObject  *TVirtualReader::GetBankRow(const Char_t *bankname,Int_t nrow){
  // Return a pointer to the ClasBank bank object with name "bankname" at row nrow.
  cout << "TVirtualReader::GetBankRow() is not implemented in this class: " << GetReaderType() << endl;
  return NULL;
}

Int_t     TVirtualReader::GetEventNumber(){
  // Return the current number of the event from the HEADER. I.e. the actual event number.
  cout << "TVirtualReader::GetEventNumber() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}

Int_t   TVirtualReader::GetRunNumber(){
  // Return the current run number of the event from the HEADER. 
  cout << "TVirtualReader::GetEventNumber() is not implemented in this class: " << GetReaderType() << endl;
  return(0);
}

Int_t     TVirtualReader::GetCurrentEvent(){
  // Return the current number of the event in the sequence, i.e. the n-th event number.
  cout << "TVirtualReader::GetEventNumber() is not implemented in this class: " << GetReaderType() << endl;
  return(-999);
}


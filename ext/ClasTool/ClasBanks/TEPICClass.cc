// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TEPICClass.cc,v 1.3 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TEPICClass</h1>
<pre>
Modifications:
           Maurik (7/05) Comments.
</pre>
<p>This class is part of the sytem to access the EPIC data stored in the
(RAW only!) BOS file. </p>
<H3>What is EPIC?</H3>
<p>The on-line system has a large number of slow control (beam position, torus current etc) 
values that get occasionally collected and stored in BOS bank and put in the data stream.
This BOS bank is called "EPIC". It contains pairs of a name and a value. What is actually
in the bank (and what name is given to the item in the bank) depends on the setup during the run.
Mostly you can guess at what is what.</p>
<h3>Making an input file</h3>
<p>A raw BOS file is scanned by Scan_EPICS (see Utils/Scan_Epics.cc)
to produce an EPICS root file. This file will contain a TEPICClass which in turn
contains a TClonesArray of TEPICValue objects. <br>
Note that a "cooked" BOS file will not contain the EPIC bank, so you probably want to run
the Scan_EPIC program when you are cooking the raw files. This is also why we create a 
separate root file for this information.</p>
<h3>Usage:</h3>
<p>The most convenient usage of this class is while doing date analysis using the TDSTReader. 
There is already code included in that reader to get the EPIC data you may want to use in your
analysis.</P>
<p>To make a plot of the EPIC value (see one of the example scripts), you need to
open the file (with TFile) then get the TTree containing the TEPICClass object from the file and run 
through the tree for each of the EPIC events. 
<pre>
<!-- ______________________________________________________________________*/ 
// --> End_Html

//
// This class is used to access the EPICS bank data written into
// the ROOT DST by Scan_EPICS.cc. The EPICS bank contains beam information
// not found in other banks. 
// 
//
////////////////////////////////////////////////////////


#include "TEPICValue.h"
#include "TEPICClass.h"

ClassImp(TEPICClass)

TEPICClass::TEPICClass(TEPICClass *TmpEPIC)
  // Copy Constructor.
{

  Last_Phys = TmpEPIC->Last_Phys;
  runno = TmpEPIC->runno;
  First_Phys = TmpEPIC->First_Phys;
  Last_Phys_time = TmpEPIC->Last_Phys_time;
  Evt_time = TmpEPIC->Evt_time;
  First_Phys_time = TmpEPIC->First_Phys_time;

  Int_t Max=TmpEPIC->EPIC->GetEntries();  // This way we call GetEntries only once!

  EPIC=new TClonesArray("TEPICValue",Max);

  TClonesArray &tEPIC= *EPIC; // Pointer de-reference trick.

  for(Int_t i=0; i<=Max; i++){
    new(tEPIC[i]) TEPICValue( (TEPICValue *)TmpEPIC->EPIC->At(i) );
  }
}

void TEPICClass::AddEPIC(TEPICValue *ep)
//Add a TEPICValue at the end of the EPIC TClonesArray
{
  Int_t i=EPIC->GetLast()+1;
  TClonesArray &tEPIC= *EPIC; // Pointer de-reference trick.
  new(tEPIC[i]) TEPICValue(ep);
}


void TEPICClass::AddEPICAt(TEPICValue *ep,Int_t place)
//Add a TEPICValue at a specific place in the EPIC TClonesArray
{
  TClonesArray &tEPIC= *EPIC; // Pointer de-reference trick.
  new(tEPIC[place]) TEPICValue(ep);
}


void TEPICClass::Print()
  // Print information for this particular class. Useful for debugging.
{
  TEPICValue *ep;
  TObjArrayIter it(EPIC);
  while( (ep=(TEPICValue *)it.Next()) ){
    ep->Print();
  }
  cout << "First_Phys = " << First_Phys << endl;
  cout << "Last_Phys = " << Last_Phys << endl;
  cout << "runno = " << runno << endl;
  cout << "First_Phys_time = " << First_Phys_time << endl;
  cout << "Last_Phys_time = " << Last_Phys_time << endl;
  cout << "Evt_time = " << Evt_time << endl;
}


Int_t TEPICClass::GetValueIndex(TString member)
 // This returns the index of the TEPICValue with the name member. If you are repeatedly
  //getting a member with the same index in a loop then using this outside the loop and
  //GetValue(Int_t) inside should be faster than the binary search. Use the TString search if you
  //think the index will change.
  // Return -1 if not found.
{ 
  TEPICValue *ep;
  member.Resize(32);    //This assumes all fNames are 32 chars long, otherwise this step should be performed in the loop. It is crucial that the strings be the same length when using CompareTo()
 
  Int_t result;
  Int_t base = 0;
  Int_t last = EPIC->GetEntries();

  while (last >= base) {
    Int_t position = (base + last) / 2;
    ep = (TEPICValue *)EPIC->At(position);
    if ((result = ep->CompareTo(member)) == 0)
      return (position);
    if (result > 0)
      last = position - 1;
    else
      base = position + 1;
  }
  cout << "Binary Search failed. Check your spelling." << endl;

  ////////// Member by member search

  Int_t ind = 0;

  
  TObjArrayIter it(EPIC);
  while( (ep=(TEPICValue *)it.Next()) ){
    if( ep->CompareTo(member)==0){
      return (ind);
    }
    ind++;
  }

  cout << member << " not found. Check your spelling." << endl;
  return -1;
}



Float_t TEPICClass::GetValue(TString member)
//Returns the value associated with the TEPICValue that has name "member". Uses a binary search.
{
  TEPICValue *ep;
  member.Resize(32);    //This assumes all fNames are 32 chars long, otherwisethis step should be performed in the loop. It is crucial that the strings be the same length when using CompareTo()


  Int_t result;
  Int_t base = 0;
  Int_t last = EPIC->GetEntries();

  while (last >= base) {
    Int_t position = (base + last) / 2;
    ep = (TEPICValue *)EPIC->At(position);
    if ((result = ep->CompareTo(member)) == 0)
      return (ep->fValue);
    if (result > 0)
      last = position - 1;
    else
      base = position + 1;
  }

  cout << "Binary Search failed " << endl;

  //catches errors in binary by doing a member by member search
  TObjArrayIter it(EPIC);
  while( (ep=(TEPICValue *)it.Next()) ){
    if( ep->fName.CompareTo(member)==0){
      return (ep->fValue);
    }
  }

  cout << member << "not found. Check your spelling."  << endl;
  return 0.;
}


Float_t TEPICClass::GetValue(Int_t ind)
//Returns the value of the TEPICValue in TClonesArray EPIC at index ind
{
  TEPICValue *ep;
  if( (ep = (TEPICValue *)EPIC->At(ind)) ){
    return (ep->fValue);
  }
  cout << "Function unsuccessful." << endl;
  return 0.;
}


TString TEPICClass::GetName(Int_t ind)
//Returns the name of the TEPICValue in TClonesArray EPIC at index ind
{
  TEPICValue *ep;
  if( (ep = (TEPICValue *)EPIC->At(ind)) ){
    return (ep->fName);
  }
  return ("");
}

//////////////////////////////////////////////////////////////////
//
//  End of FIle TEPICClass.cc
//////////////////////////////////////////////////////////////////

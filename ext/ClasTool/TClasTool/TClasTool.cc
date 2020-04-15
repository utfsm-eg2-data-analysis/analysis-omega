// @(#)ClasTool/TClasTool:$Name:  $:$Id: TClasTool.cc,v 1.15 2007/03/01 22:27:00 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all. *
 *                                                                          *
 * Documentation  : TClasTool.html                                          *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  04/2/2002 (UNH)                                        *
 * Initial Authors:  Maurik Holtrop (UNH) Gagik Gavalian (UNH)              *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//BEGIN_HTML <!--
/* -->
</pre><H1> TClasTool </H1>
<H2>A framework for ROOT based analysis of CLAS data.</H2>
<p>Created at UNH by <b><i><a href="http://www.physics.unh.edu/~maurik">Maurik Holtrop</a></b></i> 
and <b><i>Gagik Gavalian</b></i>
<p>
This class provides a flexible way to analyze CLAS data using the ROOT system.
It was originally intended to read ROOT based DST files created by the
<i>WriteRootDST</i> utility, but has since then been expanded to handle other
data formats as well. See the TNT10Reader class for a reader of <i>ntuple-10</i>
hbook files.</p>
<H3>Implementation Philosophy</H3>
I have doubted for quite some time whether the layered approach of TClasTool is the 
best way to implement an analysis. Why not put everything in the reader, and so have
only one class to deal with? In the end I stuck to this segmented approach for
several reasons: 
<ol>
<li> It gives more flexibility to write readers for different data
formats. </li>
<li> Methods that are useful for all data formats can be implemented in TClasTool, those
that apply only to specific data formats go in to the reader.</li>
<li> If you don't like this implementation of TClasTool, you can create your own.
<li> You can always revert to using only the reader, by passing the TClasTool. </li>
</ol> 
<p> The penalty is an additional layer of classes, and the overhead (very slight) in passing
calls from one layer to the underlying layer. </p>
<p>Note that in general this framework is <strong>not</strong> build to be the fastest 
code with the smallest DST. The idea is to have something that is <strong>reliable, 
understandable and comprehensive.</strong></p>
<H3>Implementation</H3>
<p>The TClasTool class acts as an interface to the data through a DST reader class.
You start by connecting to a <emphasis>reader</emphasis>
with a call to InitDSTReader(). Then you open one or more DST files with Add().
After this you can loop through the data (with Next()) and retreive the relevant
physics 3 and 4 vectors with various other methods. </p>
<p>I hope that eventually this class can be expanded to also connect to a TFiducialCut class
to provide CLAS fiducial cuts, a TMomentumCorrection class to provide momentum
corrections and perhaps even particle id corrections, kinematic fitting
any other common tasks that form a complete analysis.</p>

<h3>ClasTool Namespace</h3>
The implementation of TClasTool also includes a ClasTool namespace which currently includes some
general use arrays and some functions:
<ol>
<li>  Int_t    GetTypeFromPid(Int_t pid); // Finds the index (internally used type) from PDG PID</li>
<li>  Int_t    GetPidFromType(Int_t type);// Finds the PDG PID from the index. </li>
<li>  Float_t  GetPartMassID(Int_t pid);  // Finds the mass of a particle with PDG PID. </li>
<li>  const char * GetPartName(Int_t pid); // Finds the name of a particle with PDG PID. </li>
<li>  const char * GetShortPartName(Int_t pid); // Same, but get the short name. </li>

<li>  static const Float_t fgParticle_Mass[]=  // Masses of particles, indexed by internal type. </li>
<li>  static const Int_t   fgParticle_Id[]=   // Id's of particles.  , indexed by internal type.  </li>
<li>  static const char   *fgParticle_Name[]= // Names of the particles.
<li>  static const char   *fgParticle_ShortName[]= // Short Names (abbreviations) of the particles, 4 chars or less each.
<li>  static const char   *fgParticle_Symbol[]= // Symbols (as in "#pi^{+}" for pi+.

</ol>

<p>
Additional information about this package, including an overview, can be found at the
<a href="http://www.physics.unh.edu/~maurik/ClasTool">ClasTool Documentation</a> web pages.
</p>
<pre> 
<!-- */ 
// --> End_Html   


#include "TClasTool.h"

//======================================================================
// ClasTool Namespace
//=======================================================================

const char *ClasTool::GetPartName(Int_t pid){
  Int_t type;
  type = ClasTool::GetTypeFromPid(pid);
  if(type>=0) return(ClasTool::fgParticle_Name[type]);
  else return("Error");
}  

const char *ClasTool::GetPartShortName(Int_t pid){
  Int_t type;
  type = ClasTool::GetTypeFromPid(pid);
  if(type>=0) return(ClasTool::fgParticle_ShortName[type]);
  else return("Err");
}  

const char *ClasTool::GetPartSymbol(Int_t pid){
  Int_t type;
  type = ClasTool::GetTypeFromPid(pid);
  if(type>=0) return(ClasTool::fgParticle_Symbol[type]);
  else return("Error");
}  

const char *ClasTool::GetPartNameIdx(Int_t idx){
  if(idx>=0 && idx<kNParticleTypes) return(ClasTool::fgParticle_Name[idx]);
  else return("Error");
}  

const char *ClasTool::GetPartShortNameIdx(Int_t idx){
  if(idx>=0 && idx<kNParticleTypes) return(ClasTool::fgParticle_ShortName[idx]);
  else return("Error");
}  

const char *ClasTool::GetPartSymbolIdx(Int_t idx){
  if(idx>=0 && idx<kNParticleTypes) return(ClasTool::fgParticle_Symbol[idx]);
  else return("Error");
}  


Float_t ClasTool::GetPartMassIdx(Int_t idx){
  // Returns the mass of the particle from the index, using
  // a lookup table in fgParticle_Mass.
  if(idx>=0 && idx<kNParticleTypes) return(ClasTool::fgParticle_Mass[idx]);
  else return((Float_t)kERR);
}


Float_t ClasTool::GetPartMassID(Int_t pid){
  // Returns the mass of the particle from the particle id, using
  // a lookup table in fgParticle_Mass.
  Int_t type;
  type = ClasTool::GetTypeFromPid(pid);
  if(type>=0) return(ClasTool::fgParticle_Mass[type]);
  else return((Float_t)kERR);
}

Int_t ClasTool::GetPartChargeIdx(Int_t idx){
  // Returns the charge of the particle from the index, using
  // a lookup table in fgParticle_Mass.
  if(idx>=0 && idx<kNParticleTypes) return(ClasTool::fgParticle_Charge[idx]);
  else return(kERR);
}


Int_t ClasTool::GetPartChargeID(Int_t pid){
  // Returns the charge of the particle from the particle id, using
  // a lookup table in fgParticle_Mass.
  Int_t type;
  type = ClasTool::GetTypeFromPid(pid);
  if(type>=0) return(ClasTool::fgParticle_Charge[type]);
  else return(kERR);
}

//=======================================================================
Int_t ClasTool::GetTypeFromPid(Int_t pid){
  // Find the type (index) of the particle given the PDG PID.
  // i.e. return 1 for the PID of 11.
  // 
  // Current implementation is a large ordered "switch" rather than
  // a loop. The "switch" is slightly faster. The switch is ordered
  // so that the most frequently occurring particles occur early,
  // reducing the average number of comparisons.
  // 
  switch(pid) {
  case kUnknown_Id:
    return kUnknown;
  case kPion_Plus_Id:
    return kPion_Plus;
  case kProton_Id:
    return kProton;
  case kElectron_Id:
    return kElectron;
  case kPhoton_Id:
    return kPhoton;
  case kPion_Minus_Id:
    return kPion_Minus;
  case kNeutron_Id:
    return kNeutron;
  case kKaon_Plus_Id:
    return kKaon_Plus;
 case kDeuteron_Id:
    return kDeuteron;
  case kKaon_Minus_Id:
    return kKaon_Minus;
  case kHe4_Id:
    return kHe4;
  case kHe3_Id:
    return kHe3;
  case kPositron_Id:
    return kPositron;
  default:
    return kERR;
  }

  //
  // Old loop implementation:
  //
  // for(Int_t i=0;i<kNParticleTypes;i++){
  //   if(fgParticle_Id[i] == pid ){
  //     return(i);
  //   }
  // }  
  // return(kERR);
}

//=======================================================================
Int_t ClasTool::GetPidFromType(Int_t type){
  // Returns the PID type of a particle from the internally used
  // index (type) of the particle. i.e. returns PID 11 for index 1.

  if(type>=0 && type<kNParticleTypes){
    return( ClasTool::fgParticle_Id[type]);
  }else{
    return( kERR );
  }

}

//////////////////////////////////////////////////////////////////////////// 



using namespace ClasTool;   // So we don't need to specify ClasTool:: here.



ClassImp(TClasTool) // Main class for ClasTool package, drives everything else.


//=======================================================================
TClasTool::TClasTool(){
  //
  // Class default constructor.
  //
   if(fDebug_Mode&kDBG_Info)cout << "TCLASTOOL: Initializing TClasTool class.." << endl;
  isReaderDefined = 0; 
  fEBeam          = 0.0;
}
//=======================================================================
TClasTool::~TClasTool()
{
  // Class default destructor.
  if ( isReaderDefined != 0 ) 
    delete fReader;
}

//=======================================================================
Int_t  TClasTool::InitDSTReader(const Char_t *readertype)
{
//
// Initialize the DST reader if not already defined.
//
// Argument can be:
//    ROOTDSTR   -- start a TDSTReader [default]
//
//
  if(isReaderDefined==0){
    if(strncmp(readertype,"ROOT",4)==0){
      isReaderDefined = 1;
      fReader = new TDSTReader();
      return(1);
    }
  }else{
    if(fDebug_Mode&kDBG_Error) cout << "TCLASTOOL: ERROR The DSTReader is already defined." << endl;
    return(0);
  }
  return(0);
}

//=======================================================================
Int_t  TClasTool::InitDSTReader(TVirtualReader *reader){
// Set the current DST reader to reader.
// Argument can be any DST class derived from TVirtualReader
// 
// Example:
// TClasTool *ct=new TClasTool();
// TNT10Reader *nt=new TNT10Reader();
// ct->InitDSTReader(nt);
// ct->Add("myfile.hbook");
// ....
//
  if(isReaderDefined==0){
    if(reader){
      fReader = reader;
      isReaderDefined = 1;
      return(1);
    }else{
      fReader=NULL;
      return(0);
    }
  }else{
    if(fDebug_Mode&kDBG_Error) cout << "TCLASTOOL: ERROR The DSTReader is already defined." << endl;
    return(0);
  }
  return(0);
}

//=======================================================================
Int_t  TClasTool::Add(const Char_t *filename){
// Add one or more files to the chain of files to be analyzed, using
// wildcard format.
// This filename is passed on to the DST reader that is 
// currently initialized.
//
  if(Check_Reader_Defined()){
    return(fReader->Add(filename));
  } else return(0);
}
//=======================================================================
Int_t  TClasTool::AddFile(const Char_t *filename){
// Add a single file to the chain of files to be analyzed. 
// This filename is passed on to the DST reader that is 
// currently initialized.
//
  if(Check_Reader_Defined()){
    return(fReader->AddFile(filename));
  }else return(0);
}

//=======================================================================
Int_t TClasTool::AddEPICFile(const Char_t *filename, Int_t nentries){
  //Add a single file to the EPIC chain of files.
  //Files must be added in order of run number for
  //GetEPICValue to work correctly. Only for use with TDSTReader
//
  if(strcmp(fReader->ClassName(),"TDSTReader")==0){
    return(fReader->AddEPICFile(filename,nentries));
  } else{
    cout << "Error: MUST USE TDSTReader!" << endl << endl;
    return(0);
  }
}

//=======================================================================
Int_t TClasTool::Check_Reader_Defined(){
  //
  // Internal function that checks if the reader is ok.
  //
  if(isReaderDefined > 0 && fReader!= NULL ){
    return(1);
  }else{
    cerr << "ERROR -- No DST Reader is defined. Init with InitDSTReader() \n";
    return(0);
  }
}


//=======================================================================
Int_t  TClasTool::Next()
{
  // Read the next event from the currently attached file.
  READER_SAFE_CHECK{return(fReader->Next());}
  return(0);
}

//=======================================================================
TObject *TClasTool::GetBankRow(const Char_t *bankname,Int_t nrow){
  // Return the bank with bankname (i.e. "EVNT") at row nrow.
  READER_SAFE_CHECK{return(fReader->GetBankRow(bankname,nrow));}
  return(NULL);
}

//=======================================================================
Int_t TClasTool::GetCurrentEvent(){
  // Return the sequence number of the current event.
  READER_SAFE_CHECK{return(fReader->GetCurrentEvent());}
  return(0);
}

//=======================================================================
Double_t TClasTool::GetEntries(){
  // Return the number of events (entries) in all files loaded.
  READER_SAFE_CHECK{return(fReader->GetEntries());}
  return(0.);
}

//=======================================================================
Double_t TClasTool::GetEntriesFast(){
  // Return the number of events (entries) in all files,
  // without checking. This is faster, but could return
  // the wrong number is GetEntries() was not called
  // earlier.
  READER_SAFE_CHECK{return(fReader->GetEntriesFast());}
  return(0.);
}

//=======================================================================
Int_t TClasTool::GetEntry(Int_t entry, Int_t getall){
  // Get a specific entry from the file with sequence number entry.
  READER_SAFE_CHECK{return(fReader->GetEntry(entry,getall));}
  return(0);
}

THEADERClass *TClasTool::GetHEADER(){
  // Return a pointer to the current HEADER bank.
  READER_SAFE_CHECK{return(fReader->GetHEADER());}
  return(NULL);
}

//=======================================================================

Float_t TClasTool::GetEPICValue(const char* fName){
  //Get the EPIC value corresponding to fName
  READER_SAFE_CHECK{return(fReader->GetEPICValue(fName));}
  return(0.);
}
//=======================================================================

TEPICClass *TClasTool::GetEPICClass(){
  // Return a pointer to the current EPIC bank.
  // Returns the current EPIC without checking to see 
  // if it corresponds to the current physics event.
  // Calling GETEPICValue first will ensure the EPIC bank
  // corresponds to the physics bank.
  READER_SAFE_CHECK{return(fReader->GetEPICClass());}
  return(NULL);
}
//=======================================================================
Int_t TClasTool::GetEventNumber(){
  // Return the (physics) event number for current event.
  READER_SAFE_CHECK{
    return(fReader->GetEventNumber());
  }
  return(0);
}

//=======================================================================
Int_t TClasTool::GetNFiles(){
  // Return the number of files currently loaded.
  READER_SAFE_CHECK{
    return(fReader->GetNFiles());
  }
  return(0);
}

//=======================================================================
 TObject *TClasTool::GetNotify(){
  // Return a pointer to the Notify class.
  READER_SAFE_CHECK{
    return(fReader->GetNotify());
  }
  return(NULL);
}

//=======================================================================
Int_t  TClasTool::GetNPart()
{
  // Calls GetNPart on the attached DST Reader, which should return
  // the number of particles that this event contains.
  READER_SAFE_CHECK{return(fReader->GetNPart());}
  return(0);
}

//=======================================================================
Int_t TClasTool::GetNRows(const Char_t *bankname){
  // Get the number of rows for the bank in bankname.
  READER_SAFE_CHECK{return(fReader->GetNRows(bankname));}
  return(0);
}

//=======================================================================
Int_t  TClasTool::GetPartID(Int_t indx)
{
  // Calls the GetPartID on the attached DST Reader, which should return
  // the particle id of the the particle at index indx.
  READER_SAFE_CHECK{return(fReader->GetPartID(indx));}
  return(0);
}

//=======================================================================
Int_t TClasTool::GetPartCharge(Int_t indx)
{
  // Calls the GetPartCharge on the attached DST Reader, which should return
  // the charge of the particle at index indx.
  READER_SAFE_CHECK{return(fReader->GetPartID(indx));}
  return(0); 
}

//=======================================================================
TVector3  TClasTool::GetPart3Vector(Int_t indx)
{
  // Call the GetPart3Vector on the attached DST Reader, which should return
  // the TVector3 momentum vector of the particle.
  READER_SAFE_CHECK{return(fReader->GetPart3Vector(indx));}
  return TVector3(0,0,0); 
}

//=======================================================================
TLorentzVector TClasTool::GetPart4Vector(Int_t indx)
{
  //
  // Returns the TLorentzVector (4-vector) of the particle's 4-momentum.
  // Calls GetPart3Vector and GetPartMassID(GetPartID(indx)) to construct
  // the 4-momentum from the 3-momentum and the mass. 
  // 
  TVector3 vect3 = GetPart3Vector(indx);
  Int_t    id    = GetPartID(indx);
  TLorentzVector vect4;
  vect4.SetXYZM(vect3.X(),vect3.Y(),vect3.Z(),GetPartMassID(id));
  return vect4;
}

//=======================================================================
TVector3  TClasTool::GetPartVertex(Int_t indx)
{
  // Call the GetPartVertex on the attached DST Reader, which should return
  // the TVector3 vertex vector of the particle.
  READER_SAFE_CHECK{return(fReader->GetPartVertex(indx));}
  return TVector3(0,0,0); 
}



//=======================================================================
Int_t TClasTool::Correct_ECPB_bank(TEVNTClass *e){
  //
  // See TClasTool::Correct_ECPB_bank(TECPBClass *eco)
  //

  Int_t ec_orig_idx = e->GetECidx();  // Original index to ECPB.
  TECPBClass *eco = (TECPBClass *)GetBankRow("ECPB",ec_orig_idx);
  return(Correct_ECPB_bank(eco));
}

Int_t TClasTool::Correct_ECPB_bank(TECPBClass *eco){
  //
  // Correct the incorrect values for Ein or Eout (or both) in the ECPB bank for the
  // particle stored in the TEVNTClass bank given. 
  //
  // This routine is needed because of an error in the ECPB bank construction which
  // occasionally has multiple copies for the same EC hit, but some of these copies
  // are missing Ein or Eout or both. They WILL have Innstr and Outstr, which indicates
  // that there SHOULD be a non zero entry for Ein and Eout.
  //
  // Further documentation can be found at:
  // http://clasweb.jlab.org/cgi-bin/ENOTE/enote.pl?nb=eg2&action=view&page=84
  //
  // So before using Ein and/or Eout from the ECPB you want to make the following
  // lines of code, assuming *evnt is your TEVNTClass object for the event, and 
  // *ec is the TECPBObject for that event:
  //
  // if( ( (ec->Ein ==0 && ec->Innstr>0) || (ec->Eout == 0 && ec->Outstr>0) ) && ec->Etot>0.){
  //     Int_t stat = cltool->Correct_ECPB_bank(evnt);
  // }  
  //
  // Returns in stat whether 0, 1 or 2 corrections were made to the ECPB banks values.
  //
  // (Created by Maurik Holtrop, UNH, 2006-03-24 )
  //
  Int_t stat=0;

  for(Int_t i=0; i< GetNRows("ECPB"); i++){
    TECPBClass *ec = (TECPBClass *)GetBankRow("ECPB",i);
    if(ec == eco) continue;  // Skip the ECPB bank we are trying to correct.
    if( (int)(eco->Scht/100) == (int)(ec->Scht/100) ){      // Same sector
      if( eco->Innstr == ec->Innstr &&  // Same inner cal strips.
	  eco->Ein < ec->Ein )         // Other bank has higher value (i.e. not zero).
	{
	  eco->Ein = ec->Ein;            // Fix the original banks contends.
	  stat++;
	}

      if(eco->Outstr == ec->Outstr &&  // Same outer cal strips.
	 eco->Eout < ec->Eout )         // Other bank has higher value (i.e. not zero).
      {
	eco->Eout = ec->Eout;            // Fix the original banks contends.
	stat++;
      }
    }
  }

  return(stat);
  
}


//=======================================================================
void   TClasTool::GetInvariants(Float_t *Q2, Float_t *W2)
{
  // Returns four momentum square and the invariant mass square in *Q2 and *W2.
  // Begin_Html
  /* </pre> 
The routines calculates the Q<sup>2</sup> as 2 P<sub>e</sub> E<sub>beam</sub> (1 - cos <font face="Symbol">q</font>)
and the invariant mass W<sup>2</sup> as M<sub>p</sub><sup>2</sup>+ 2 M<sub>p</sub> (E<sub>beam</sub>-P<sub>e</sub> ) - Q<sup>2</sup>,
where P<sub>e</sub> is the momentum of the scattered electron and <font face="Symbol">q</font> is the angle with respect to the beam,
and E<sub>beam</sub> is the beam energy, M<sub>p</sub> is the mass of the proton. </p>
<p><strong>Note:</strong> To get meaningful results from this routine you must have set the beam energy correctly with SetBeamEnergy.<br>
The code assumes that the zero-index particle is the electron.
  <pre>
  */
  // End_Html
  READER_SAFE_CHECK{
    if(fReader->GetNPart()>0){
      TVector3 elec_mom = fReader->GetPart3Vector(0);
      float    cos_z    = elec_mom.Z()/elec_mom.Mag();
      Float_t l_Q2 = 2.0*elec_mom.Mag()*fEBeam*(1-cos_z);
      Float_t l_W2 = fgParticle_Mass[kProton]*fgParticle_Mass[kProton] + 2 * fgParticle_Mass[kProton] * (fEBeam - elec_mom.Mag()) - l_Q2;
      //      Float_t l_W2 = 56;
      *Q2 = l_Q2;
      *W2 = l_W2;
    } else {
      if(fDebug_Mode&kDBG_Error) cout << "GetInvariants: There are no particles in this event.." << endl;
    }
  }

}

//=======================================================================
TVERTClass* TClasTool::GetVert(Int_t part1, Int_t part2)
{
    //
    // This function will return a pointer to the correct TVERTClass bank 
    // that is associated with the two tracks that are pointed to 
    // by the integer indexes into the EVNT bank, part1 and part2.
    //
    // Among other methods, you can locate the correct indexes 
    // for particle type X, using the TPartSieve::GetIndex()
    //


    TDCPBClass *fDCPB;  
    TEVNTClass *fEVNT;
    TVERTClass *fVERT; 
    Int_t track1=-1,track2=-1;
    Int_t holder; 
    Int_t NumTracks;
    Int_t Sigma;
    Int_t Vertidx;
    Int_t NRows=0;

    // Get the TrackId from the DCPB Bank
    // for each particle


    if ( (fEVNT = GetEVNT(part1)) ) {
        if (fEVNT->GetDCStat()>0) {
            fDCPB = GetDCPB((Int_t) (fEVNT->GetDCidx()));
            track1 = fDCPB->GetTrackId();

            if ( (fEVNT = GetEVNT(part2)) ) {
                if (fEVNT->GetDCStat() > 0) {
                    fDCPB = GetDCPB((Int_t) (fEVNT->GetDCidx()));
                    track2 = fDCPB->GetTrackId();

                    if (track2<track1) {;           // Track1 must be < Track2 to properly index into
                        holder = track1;              // the VERT Bank    
                        track1 = track2;
                        track2 = holder;
                    }

                    // This table calculates the number of tracks
                    // in the VERT bank based on the number of
                    // rows in the vert bank 


                    NRows = GetNRows("VERT");
                    if (NRows == 0)
                        return NULL;
                    else if (NRows == 1)
                        return NULL;
                    else if (NRows == 3)
                        NumTracks = 2;
                    else if (NRows == 6)
                        NumTracks = 3;
                    else if (NRows == 10)
                        NumTracks = 4;
                    else if (NRows == 15)
                    NumTracks = 5;
                    else if (NRows == 21)
                        NumTracks = 6;
                    else if (NRows == 28)
                    NumTracks = 7;
                    else if (NRows == 36)
                        NumTracks = 8;
                    else if (NRows == 45)
                        NumTracks = 9;
                    else if (NRows == 55)
                        NumTracks = 10;
                    else if (NRows == 66)
                    NumTracks = 11;
                    else if (NRows == 78)
                        NumTracks = 12;
                    else if (NRows == 91)
                        NumTracks = 13;
                    else if (NRows == 105)
                        NumTracks = 14;
                    else if (NRows == 120)
                        NumTracks = 15;
                    else {
                        cout << "Bad Track Finder!!" << endl;
                        return (Vert_Error_Handler(NRows,track1,track2));
                    }
	  
	  
                    // Vertidx is based on the VERT Bank having rows in the order
                    // (example)     (0)01 (1)02 (2)03 (3)12 (4)13 (5)23
                    // where in a group the number in () is the row number in the VERT Bank,
                    // the next number is track1index and the last number is track2index 

//                    Sigma = 0;
//                    sig = NumTracks - track1;
//                    while (sig > 0) {
//                        Sigma += sig;
//                        sig--;
//                    }

                    // This table replaces this Sigma loop

                    if ((NumTracks - track1) < 0)
                        return(Vert_Error_Handler(NRows,track1,track2));
                    else if ((NumTracks - track1) == 0)
                        Sigma = 0;
                    else if ((NumTracks - track1) == 1)
                        Sigma = 1;
                    else if ((NumTracks - track1) == 2)
                        Sigma = 3;
                    else if ((NumTracks - track1) == 3)
                        Sigma = 6;
                    else if ((NumTracks - track1) == 4)
                        Sigma = 10;
                    else if ((NumTracks - track1) == 5)
                        Sigma = 15;
                    else if ((NumTracks - track1) == 6)
                        Sigma = 21;
                    else if ((NumTracks - track1) == 7)
                        Sigma = 28;
                    else if ((NumTracks - track1) == 8)
                        Sigma = 36;
                    else if ((NumTracks - track1) == 9)
                        Sigma = 45;
                    else if ((NumTracks - track1) == 10)
                        Sigma = 55;
                    else if ((NumTracks - track1) == 11)
                        Sigma = 66;
                    else if ((NumTracks - track1) == 12)
                        Sigma = 78;
                    else if ((NumTracks - track1) == 13)
                        Sigma = 91;
                    else if ((NumTracks - track1) == 14)
                        Sigma = 105;
                    else{
                        cout << "Bad Sigma!! Numtraks = " << NumTracks << " Track 1 = " << track1<<endl;
                        return (Vert_Error_Handler(NRows,track1,track2));
                    }
	  
                    Vertidx = NRows - Sigma + track2 - track1 -1;
                    if (Vertidx < NRows) {
                        fVERT=(TVERTClass *) GetBankRow("VERT",Vertidx);
                        if (fVERT) {
                            if (fVERT->GetTrack1Id() == track1 && fVERT->GetTrack2Id() == track2) {
//                                cout<<"TVERT function successful"<<endl;
                                return (fVERT);
                            }
                            else return (Vert_Error_Handler(NRows,track1,track2)); 
                        } else return (Vert_Error_Handler(NRows,track1,track2)); 
                    } else return (Vert_Error_Handler(NRows,track1,track2)); 
                } else return NULL; 
            } else return NULL; 
        } else return NULL;
    } else return NULL;
}
//================================================================================

TVERTClass* TClasTool::Vert_Error_Handler(Int_t NRows,Int_t track1, Int_t track2)
{

  // This routine is part of the GetVert call to facilitate returning a
  // vertex pointer or NULL.
  //
  //Should this be called in the case that no DC bank exists, NRows will be zero.
  //As a precaution in GetVert track 1&2 are initialized to -1.

  TVERTClass *fVERT;
  
  Int_t found = 0;
  
  for(Int_t i = 0;i<NRows;i++){
    
    fVERT = (TVERTClass *)GetBankRow("VERT",i);

    if(fVERT->GetTrack1Id() == track1 && fVERT->GetTrack2Id() == track2){
      found = 1;
      break;
    }
  }

  if(found) return (fVERT);
  else{
    if(fDebug_Mode>0){
      cout<<"Track not saved in VERT database"<<endl;
    }
      return (NULL);
  }
}

//=======================================================================
Int_t  TClasTool::GetHelicity()
{
  // A simple interface to read the helicity. This routine will NOT work for
  // experiments with delayed helicity reporting.
  // Calls the DST Readers GetHelicity() function.
  Int_t helicity = 0;
  READER_SAFE_CHECK{
    helicity = fReader->GetHelicity();
  }
  return helicity;
}

//=======================================================================
TVirtualReader *TClasTool::GetReader(void){
  // Returns a pointer to the reader.
  // Usefull for directly manipulating the reader.
  //
  return(fReader);
}

//=======================================================================
TChain *TClasTool::GetTree(Char_t *treename){
  // Returns a pointer to the actual tree that was created by the reader.
  // If the reader is incapable of returning a TTree, it will return NULL.
  READER_SAFE_CHECK{
    return(fReader->GetTree(treename));
  }
  return(NULL);
}

//=======================================================================
void  TClasTool::Print(Int_t full)
{
  // Overrides the standard print with a bit more information.
  // Set full=1 to get even more information.
  //
  cout << "OBJ: TClasTool  - Main class for ClasTool package.\n\n";
  if(Check_Reader_Defined()){
    fReader->Print(full);
  }else{
    cout << "No reader defined.";
  }
  
}


//=======================================================================
void   TClasTool::PrintEventStatus()
{
  // Print the event status to the terminal. (Useful for debugging.)
  // Calls the DST Readers PrintEventStatus().
  READER_SAFE_CHECK{
    fReader->PrintEventStatus();
  }
}
//=======================================================================
void TClasTool::PrintEPICPosition()
{
  // Print the position of the current EPIC in terms of its range of
  // event numbers and run number
  READER_SAFE_CHECK{
    fReader->PrintEPICPosition();
  }
}
//=======================================================================
void  TClasTool::SetNotify(TObject *Notify){
  // Set the Notify() class to Notify.
  // This is a class that contains a routine called Notify()
  // This method of this call will be called when the Reader loads the
  // next file of the chain. This allows you to perform certain tasks,
  // like loading new constants, when the file changes.
  READER_SAFE_CHECK{
    fReader->SetNotify(Notify);
  }
}

//=======================================================================
void TClasTool::SetNoScalers(){
  // Tell the reader (TDSTReader) that you don't want to read the
  // scaler chain, even if it exists.
  // This is useful when filtering on data.
  // You can only call this after the reader has been initialized.
  if(fReader){
    fReader->fReadScaler=false;
  }else{
    cout << "No reader defined yet. Please call InitDSTReader() first.\n";
  }
}

// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TNT10Reader.cc,v 1.10 2007/03/01 22:27:00 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>TNT10Reader</h1>                                                        
<p>
This clas mimicks the behavior of a TChain object, but is capable  
of reading the NTuple-10 format instead of native root formats.    
</p>                                                                   
<b>Huge Wopping Warning:</b><br>
When used for certain operations without an output file open, 
this class will read the ENTIRE set of HBOOK files and stick all
of its contents into one Huge Wopping TChain. The result is that
the root.exe will eat a serious amount of memory (~1.2 Gb for 2 nt files) 
This will cause your system to start swapping and everything will stop
to a crawl (especially X) leaving your system "hung" for a long time.
<b>You want to have a TFile open for writing to prevent this.</b> It will
be MUCH MUCH faster, and when you close the file, you have a root version
of the ntuple.
A different version of an NT10Reader could NOT make a TTree, would not
allow you to write a file, but it would read an ntuple faster without
having a file open. This would be faster.... (Let me know if you write one.)
</p>
<b>Important Note:</b>
<p>
Since the NT10 ntuple is NOT a stable definition, you (someone)
will need to adopt this class for each run period (cooking code version).
The adoption is fairly straight forward.
The version is in the include file NT10_E2b.h in I_VERSION and will be
reported to you with a GetReaderType() call.
Adoptiong to a different NT10 version requires modification of NT10_E2b.h
see instructions in that file.
</p><p>                                                                   
<b>WARNING:</b><br>
Since the clas inherits from TChain all the calls to TChain methods
will exist, however they may not function! Quite a few should be   
over-written to function, some *may* work just as is....           
As I put more effort into this clas, more and more of it will.     
</p><p>
This class "borrows" heavily from THbookFile and THbookTree        
</p><p>
<h3>Improvements needed:</h3>
<ol>
<li> Get the runnumber from the file name and store it.</li>
<li> TESTING </li>
</ol>
<pre> 
<!-- */ 
// --> End_Html   
//////////////////////////////////////////////////////////////////////////

#ifdef NTUPLEMAKER
#include "NT10_NtupleMaker.h"
#else
#include "NT10_E2b.h"
// #include "NT10_commons.h"
#endif
#include "TNT10Reader.h"


#include "Hbook_interface.h"

Bool_t TNT10Reader::fgPawInit = kFALSE;
Int_t  *TNT10Reader::fgLuns   = 0;

TNT10Reader::TNT10Reader(const char *name,const char *title): TChain(name,title){
  //
  // Create a new TNT10Reader with a TChain name of "name".
  // Usually you would want that to be "CLASEVENT", so you
  // may as well use TNT10Reader();
  //  
  fNtNum = 10;  
  fNRun=0;
  fHbookLun = 0;// LUN used for opening fortran file.
  fDebug_Mode=0x0;
  fReadSequential = kTRUE;
  fNtLastRead=-1;

  fCurrentEvent = -1;

  fEvntHeader = NULL;
  fcaEVNTStore=NULL;
  fcaECPBStore=NULL;
  fcaSCPBStore=NULL;
  fcaDCPBStore=NULL;
  fcaCCPBStore=NULL;
  fcaLCPBStore=NULL;
  fEVNT =  NULL;
  fDCPB =  NULL;
  fECPB =  NULL;
  fSCPB =  NULL;
  fCCPB =  NULL;
  fLCPB =  NULL;

  fTree = new TTree(this->TChain::GetName(),this->TChain::GetTitle());

  fTree->SetMaxTreeSize(21474836480ULL); // Allow 20 Gbyte files.

  gROOT->GetListOfBrowsables()->Add((TChain *)(this),this->TChain::GetName());

  //
  // These calls are needed then the class is used as stand alone
  // .i.e. no calls to SetBranchAddress are made.
  // If you are using SetBranchAddress, this memory will be wasted,
  // but it does not hurt too much.
  //
  InitBanks();
  InitClones();
  InitBranches();

  if(!fgPawInit){  // We NEVER want to init PAW twice by accident.
    Int_t pawc_size = PAWC_SIZE;
    hlimit(pawc_size);
    fgPawInit = kTRUE;

    fgLuns = new Int_t[10];
    for (Int_t i=0;i<10;i++) fgLuns[i] = 0;
    cerr << "PAW Space initialized.\n";

  }

  cerr << "TNT10Reader init ok.\n";

}

TNT10Reader::~TNT10Reader(){
//*-*-*-*-*-*Default destructor for a HBookReader*-*-*-*-*-*-*-*-*-*-*-*
//*-*        ==============================

  if(fEvntHeader)   delete fEvntHeader;
  if(fcaEVNTStore)delete fcaEVNTStore;
  if(fEVNT)     delete fEVNT;
  if(fcaDCPBStore)delete fcaDCPBStore;
  if(fDCPB)     delete fDCPB;
  if(fcaECPBStore)delete fcaECPBStore;
  if(fECPB)     delete fECPB;
  if(fcaSCPBStore)delete fcaSCPBStore;
  if(fSCPB)     delete fSCPB;
  if(fcaCCPBStore)delete fcaCCPBStore;
  if(fCCPB)     delete fCCPB;
  if(fcaLCPBStore)delete fcaLCPBStore;
  if(fLCPB)     delete fLCPB;

  if(fTree){
    fTree->Delete(""); // Delete from memory, not disk.
    cerr << "Tree deleted.\n";
    //    delete fTree; // This is not needed, in fact it cause sigfault!.
    fTree=NULL;
  }

  if(fgInstanceCount==0){

  }
}

TString TNT10Reader::GetReaderType(){
  // Returns the type of reader and the I_VERSION.
  // The I_VERSION is a string that should contain
  // which run period cookings this reader is good for.
  // For more info see NT10_commons.h
  //
  return( TString("NT10Reader ")+TString(I_VERSION));
}


Int_t TNT10Reader::Add(const char *name,Int_t nentries){
// Add an HBook file containing an Ntuple-10 ntuple to the list of
// files that will be itterated over.
// Similar to TChain::Add()
//
// Argument name may have the following format:
//   //machine/file_name.root/subdir/tree_name
// machine, subdir and tree_name are optional. If tree_name is missing,
// the chain name will be assumed.
// Name may use the wildcarding notation, eg "xxx*.root" means all files
// starting with xxx in the current file system directory.
// NB. To add all the files of a TChain to a chain, use Add(TChain *chain).
//
//    A- if nentries <= 0, the file is connected and the tree header read
//       in memory to get the number of entries.
//
//    B- if (nentries > 0, the file is not connected, nentries is assumed to be
//       the number of entries in the file. In this case, no check is made that
//       the file exists and the Tree existing in the file. This second mode
//       is interesting in case the number of entries in the file is already stored
//       in a run data base for example.
//
//    C- if (nentries == kBigNumber) (default), the file is not connected.
//       the number of entries in each file will be read only when the file
//       will need to be connected to read an entry.
//       This option is the default and very efficient if one process
//       the chain sequentially. Note that in case TChain::GetEntry(entry)
//       is called and entry refers to an entry in the 3rd file, for example,
//       this forces the Tree headers in the first and second file
//       to be read to find the number of entries in these files.
//       Note that if one calls TChain::GetEntriesFast() after having created
//       a chain with this default, GetEntriesFast will return kBigNumber!
//       TChain::GetEntries will force of the Tree headers in the chain to be
//       read to read the number of entries in each Tree.

   // case with one single file
   if (strchr(name,'*') == 0) {
      return AddFile(name,nentries);
   }

   // wildcarding used in name
   Int_t nf = 0;
   char aname[2048]; //files may have very long names, eg AFS
   strcpy(aname,name);
   char *dot = (char*)strstr(aname,".hbook");

   const char *behind_dot_root = 0;

   if (dot) {
      if (dot[5] == '/') behind_dot_root = dot + 6;
      *dot = 0;
   }

   char *slash = strrchr(aname,'/');
   if (slash) {
      *slash = 0;
      slash++;
      strcat(slash,".hbook");
   } else {
      strcpy(aname,gSystem->WorkingDirectory());
      slash = (char*)name;
   }

   const char *file;
   void *dir = gSystem->OpenDirectory(gSystem->ExpandPathName(aname));

   if (dir) {
      TRegexp re(slash,kTRUE);
      while ((file = gSystem->GetDirEntry(dir))) {
         if (!strcmp(file,".") || !strcmp(file,"..")) continue;
         //if (IsDirectory(file)) continue;
         TString s = file;
         if (strcmp(slash,file) && s.Index(re) == kNPOS) continue;
         if (behind_dot_root != 0 && *behind_dot_root != 0)
            nf += AddFile(Form("%s/%s/%s",aname,file,behind_dot_root),TChain::kBigNumber);
         else
            nf += AddFile(Form("%s/%s",aname,file),TChain::kBigNumber);
      }
      gSystem->FreeDirectory(dir);
   }
   return nf;
}


Int_t TNT10Reader::AddFile(const char *name,Int_t nentries){
//       Add a new file to this HBOOK chain.
//
//    A- if nentries <= 0, the file is connected and the tree header read
//       in memory to get the number of entries.
//
//    B- if (nentries > 0, the file is not connected, nentries is assumed to be
//       the number of entries in the file. In this case, no check is made that
//       the file exists and the Tree existing in the file. This second mode
//       is interesting in case the number of entries in the file is already stored
//       in a run data base for example.
//
//    C- if (nentries == kBigNumber) (default), the file is not connected.
//       the number of entries in each file will be read only when the file
//       will need to be connected to read an entry.
//       This option is the default and very efficient if one process
//       the chain sequentially. Note that in case TChain::GetEntry(entry)
//       is called and entry refers to an entry in the 3rd file, for example,
//       this forces the Tree headers in the first and second file
//       to be read to find the number of entries in these files.
//       Note that if one calls TChain::GetEntriesFast() after having created
//       a chain with this default, GetEntriesFast will return kBigNumber!
//       TChain::GetEntries will force of the Tree headers in the chain to be
//       read to read the number of entries in each Tree.

   char *treename = (char*)TChain::GetName();

   //the ".hbook" is mandatory only if one wants to specify a treename
   //if (!dot) {
   //   Error("AddFile","a chain element name must contain the string .root");
   //   return 0;
   //}

   //Check enough space in fTreeOffset
   if (fNtrees+1 >= fTreeOffsetLen) {
      fTreeOffsetLen *= 2;
      Long64_t *trees = new Long64_t[fTreeOffsetLen];
      for (Int_t i=0;i<=fNtrees;i++) trees[i] = fTreeOffset[i];
      delete [] fTreeOffset;
      fTreeOffset = trees;
   }

   //Search for a a slash between the .hbook and the end
   Int_t nch = strlen(name) + strlen(treename);
   char *filename = new char[nch+1];
   strcpy(filename,name);

   //Connect the file to get the number of entries
   Int_t pksize = 0;
   if (nentries <= 0) {
      Open(filename);
      if (IsZombie()) {
         delete [] filename;
         return 0;
      }
      nentries = GetNTEntries();
      pksize   = TChain::kBigNumber;
   }
   
   if (nentries > 0) {
      if (nentries < TChain::kBigNumber) {
         fTreeOffset[fNtrees+1] = fTreeOffset[fNtrees] + nentries;
         fEntries += nentries;
      } else {
         fTreeOffset[fNtrees+1] = TChain::kBigNumber;
         fEntries = nentries;
      }
      fNtrees++;

      TChainElement *element = new TChainElement(treename,filename);
      element->SetPacketSize(pksize);
      element->SetNumberEntries(nentries);
      fFiles->Add(element);
   } else {
      TChain::Warning("Add","Adding Tree with no entries from file: %s",filename);
   }

   delete [] filename;
   return 1;
}

Double_t TNT10Reader::Compute_Entries(){
  //
  // Computes the number of entries and fills the 
  // Offsets.

  TChainElement *file;
  fTreeOffset[0]=0;
  fEntries=0;
  for(Int_t i=0;i<fFiles->GetEntries();i++){
    file = (TChainElement*)fFiles->At(i);
    if(file->GetEntries()>=TChain::kBigNumber){  // not yet computed.
      if(Open(file->GetTitle())){
	file->SetNumberEntries(fNevents);
	Close();	
      }
    }
    fTreeOffset[i+1]= fTreeOffset[i]+fNevents;
    fEntries += fNevents;
  }   
  return(fEntries);

}

Int_t TNT10Reader::Draw(const char *varexp, const char *selection, Option_t *option,Int_t nentries, Int_t firstentry)
{
  // Process all entries in this chain and draw histogram
  // corresponding to expression varexp.
  
  if (LoadTree(firstentry) < 0) return 0;
  return TTree::Draw(varexp,selection,option,nentries,firstentry);
}


GetEntries_return_t TNT10Reader::GetEntries() const{
// return the total number of entries in the chain.
// In case the number of entries in each tree is not yet known,
// the offset table is computed
  if (fEntries >= (Stat_t)TChain::kBigNumber) {
    ((TNT10Reader *)this)->Compute_Entries();
  }
  return(fEntries);
}

GetEntries_return_t TNT10Reader::GetEntriesFast() const{
  // Return the number of events fast.
  // Fast, because it uses the result of the GetEntries()
  // call when the file was opened.
  return(fEntries);
}

Int_t TNT10Reader::GetEntry(Int_t entry, Int_t getall){
// 
// Override of the GetEntry function from the TChain.
// Call this function to load one event into the TTree.
//
  Int_t local_entry;
  if(entry<0){
    local_entry = fReadEntry+1;
  }else{
    local_entry = entry;
  }

  if(LoadTree(local_entry)<0)return(0);
  return(fTree->GetEntry(fReadEntry,getall));
}

Int_t TNT10Reader::Next(){
  // Get the next event in the sequence after fCurrentEvent.

  Int_t status = kNOERR;
  if(fCurrentEvent >= GetEntriesFast()-1){
    if(fDebug_Mode&kDBG_Info)    cout << "TNT10Reader::Next : End of Event Entries Reached !" << endl;
    if(fDebug_Mode & kDBG_Error)cout << "TNT10Reader::Next : End of Event Entries Reached !" << endl;
    status = kERR_end_of_file;
  } else {
    //    cout  << "Reading next event " <<  fEventChain->GetEntries() << endl;
    CleanEventClones();
    GetEntry(++fCurrentEvent);
    //    PrintEventStatus();
  }
  return status;

}

Int_t TNT10Reader::Fill_Tree_from_Paw(){
  //
  // Fills the Tree object (this) with the information
  // from the PAW ntuple. 
  // This is mostly a copy operation.
  // It finishes with a TChain::Fill() call to fill the
  // baskets associated with the tree also.
  // returns the number of bytes stored.
  //
  // At some future time, perhaps we can add code to only
  // read those items that are needed, instead of all of it...
  Fill_HEADER();
  Fill_EVNT();
  Fill_DCPB();
  Fill_ECPB();
  Fill_SCPB();
  Fill_CCPB();
  Fill_LCPB();


  Int_t nbytes = fTree->Fill(); // fill the tree.
  if(fDebug_Mode>10){
    cerr << "Tree stored " << nbytes << " bytes into baskets.\n";
  }
  return(nbytes);
}

void TNT10Reader::Fill_HEADER(void){
  // This function will fill the HEADER class.
  // For Ntuples that deviate from the "standard"
  // this routine needs to be over-written.


  fEvntHeader->NRun     = fNRun;
  fEvntHeader->NEvent   = nt10.evntid;
  fEvntHeader->Time     = 0;
  fEvntHeader->Type     = nt10.evntype; //nt10.evntype;
  fEvntHeader->ROC      = 0;
  fEvntHeader->EvtClas  = nt10.evntclas;
  fEvntHeader->TrigBits = 0;
  
  fEvntHeader->EStatus = nt10.evstat;
  fEvntHeader->TrgPrs  = nt10.evntclas;
  fEvntHeader->NPGP    = nt10.gpart + 100*nt10.npart;
  fEvntHeader->FC      = nt10.q_l;
  fEvntHeader->FCG     = nt10.q_l;
  fEvntHeader->TG      = nt10.t_l;
  fEvntHeader->STT     = nt10.tr_time;
#ifdef NT10_MAKER
  fEvntHeader->RF1     = nt10.rf_time1;
  fEvntHeader->RF2     = nt10.rf_time2; //nt10.rf_time2;
#else
  fEvntHeader->RF1     = nt10.rf_time;
  fEvntHeader->RF2     = nt10.rf_time;
#endif

  fEvntHeader->Latch1  = 0;
#ifdef NT10_E2b
  fEvntHeader->Helicity_Scaler = nt10.hlsc;
  fEvntHeader->Interrupt_Time  = nt10.intt;
  fEvntHeader->Level2  = nt10.l2bit;
  fEvntHeader->Level3  = nt10.l3bit;
#else
  fEvntHeader->Helicity_Scaler = 0;
  fEvntHeader->Interrupt_Time  = 0;
  fEvntHeader->Level2  = 0;
  fEvntHeader->Level3  = 0;
#endif
}

void TNT10Reader::Fill_EVNT(void){
  // This function will fill the EVNT class.
  // For Ntuples that deviate from the "standard"
  // this routine needs to be over-written.


  for(Int_t ievnt=0;ievnt< nt10.gpart; ievnt++){

    if(fDebug_Mode>10){
      cerr << "Storing EVNT entry number " << ievnt << endl;
    }

    fEVNT->Id      = nt10.id[ievnt];
    fEVNT->Charge  = (UChar_t) nt10.q[ievnt];
    fEVNT->Betta   = nt10.b[ievnt];
    fEVNT->Px      = nt10.p[ievnt]*nt10.cx[ievnt];
    fEVNT->Py      = nt10.p[ievnt]*nt10.cy[ievnt];
    fEVNT->Pz      = nt10.p[ievnt]*nt10.cz[ievnt];
    fEVNT->X       = nt10.vx[ievnt];
    fEVNT->Y       = nt10.vy[ievnt];
    fEVNT->Z       = nt10.vz[ievnt];
    fEVNT->Dcstat  = (UChar_t)nt10.dc[ievnt];
    fEVNT->Ccstat  = (UChar_t)nt10.cc[ievnt];
    fEVNT->Scstat  = (UChar_t)nt10.sc[ievnt];
    fEVNT->Ecstat  = (UChar_t)nt10.ec[ievnt];
    fEVNT->Lcstat  = (UChar_t)nt10.lec[ievnt];
    fEVNT->Status  = (UChar_t)nt10.stat[ievnt];
    
    TClonesArray &tEVNTBank = *fcaEVNTStore;
    new(tEVNTBank[fnEVNT_Store++]) TEVNTClass(fEVNT);
  }
}

void TNT10Reader::Fill_DCPB(void){
  // This function will fill the DCPB class.
  // For Ntuples that deviate from the "standard"
  // this routine needs to be over-written.

  for(Int_t idc=0;idc< nt10.dc_part; idc++){
    if(fDebug_Mode>10){
      cerr << "Storing DC entry number " << idc << endl;
    }
    fDCPB->Sctr = nt10.dc_sect[idc]*100 + nt10.dc_trk[idc];
    fDCPB->X_sc = (Float_t)nt10.dc_xsc[idc];
    fDCPB->Y_sc = (Float_t)nt10.dc_ysc[idc];
    fDCPB->Z_sc = (Float_t)nt10.dc_zsc[idc];
    fDCPB->Cx_sc = (Float_t)nt10.dc_cxsc[idc];
    fDCPB->Cy_sc = (Float_t)nt10.dc_cysc[idc];
    fDCPB->Cz_sc = (Float_t)nt10.dc_czsc[idc];
#ifdef NT10_E2b
    fDCPB->X_ec = (Float_t)nt10.dc_vx[idc];
    fDCPB->Y_ec = (Float_t)nt10.dc_vy[idc];
    fDCPB->Z_ec = (Float_t)nt10.dc_vz[idc];
    fDCPB->Th_cc =(Float_t)nt10.dc_vr[idc]; ;
#else
    fDCPB->X_ec = (Float_t)nt10.dc_xec[idc];
    fDCPB->Y_ec = (Float_t)nt10.dc_yec[idc];
    fDCPB->Z_ec = (Float_t)nt10.dc_zec[idc];
    fDCPB->Th_cc =(Float_t)nt10.dc_thcc[idc]; ;
#endif

    fDCPB->Chi2 = (Float_t)nt10.dc_c2[idc];
    fDCPB->Status = (Int_t)nt10.dc_stat[idc];

    TClonesArray &tDCPBBank = *fcaDCPBStore;
    new(tDCPBBank[fnDCPB_Store++]) TDCPBClass(fDCPB);

  }
}

void TNT10Reader::Fill_ECPB(void){
  // This function will fill the ECPB class.
  // For Ntuples that deviate from the "standard"
  // this routine needs to be over-written.

  for(Int_t iec=0;iec< nt10.ec_part; iec++){
    if(fDebug_Mode>10){
      cerr << "Storing EC entry number " << iec << endl;
    }

    fECPB->Scht=(Int_t)(nt10.ec_sect[iec]*100+nt10.ec_whol[iec]);// 100*sector+Whole_Hit_ID in ECHB 
    fECPB->Etot=(Float_t)nt10.etot[iec];    // Reconstructed total energy
    fECPB->Ein =(Float_t)nt10.ec_ei[iec];    // Inner energy
    fECPB->Eout=(Float_t)nt10.ec_eo[iec];    // Outer energy 
    fECPB->Time=(Float_t)nt10.ec_t[iec];   // Flight time relative to the evnt start time
    fECPB->Path=(Float_t)nt10.ec_r[iec];   // Path lenght from target
    fECPB->X   =(Float_t)nt10.ech_x[iec];    // x coordinate of hit 
    fECPB->Y   =(Float_t)nt10.ech_y[iec];   // y coordinate of hit
    fECPB->Z   =(Float_t)nt10.ech_z[iec];    // z coordinate of hit
    fECPB->M2_hit=(Float_t)nt10.ec_m2[iec];    // second moment of _hit pattern
    fECPB->M3_hit=(Float_t)nt10.ec_m3[iec];    // third moment of  _hit pattern 
    fECPB->M4_hit=(Float_t)nt10.ec_m4[iec];    // forth moment of  _hit pattern 
    fECPB->Innstr=(Int_t)nt10.ec_inst[iec];      // 10000*UI+100*VI+WI 
    fECPB->Outstr=(Int_t)nt10.ec_oust[iec];      // 10000*UO+100*VO+WO
    fECPB->Chi2ec=(Float_t)nt10.ec_c2[iec];    // Quality measure of geometrical matching
    fECPB->Status=(Int_t)nt10.ec_stat[iec];      // Status word (not implemented yet)

    TClonesArray &tECPBBank = *fcaECPBStore;
    new(tECPBBank[fnECPB_Store++]) TECPBClass(fECPB);
  }
}

void TNT10Reader::Fill_SCPB(void){
  // This function will fill the SCPB class.
  // For Ntuples that deviate from the "standard"
  // this routine needs to be over-written.
  for(Int_t isc=0;isc< nt10.sc_part; isc++){
    if(fDebug_Mode>10){
      cerr << "Storing SC entry number " << isc << endl;
    }

    fSCPB->Scpdht=(Int_t)  (nt10.sc_sect[isc]*10000+
			    nt10.sc_pd[isc]  *100+
			    nt10.sc_hit[isc]); // 10000*sector+100*SC_PD_ID+Hit_ID in SCR 
    fSCPB->Edep=  (Float_t) nt10.edep[isc];  // Deposited energy (dE/dX)
    fSCPB->Time=  (Float_t) nt10.sc_t[isc];  // Flight time relative to the evnt start time
    fSCPB->Path=  (Float_t) nt10.sc_r[isc];  // Path lenght from target
    fSCPB->Chi2sc=(Float_t) nt10.sc_c2[isc];  // Quality measure of geometrical matching
    fSCPB->Status=(Int_t  ) nt10.sc_stat[isc];  // Status word (not defined yet)

    TClonesArray &tSCPBBank = *fcaSCPBStore;
    new(tSCPBBank[fnSCPB_Store++]) TSCPBClass(fSCPB);

  }


}

void TNT10Reader::Fill_CCPB(void){
  // This function will fill the DCPB class.
  // For Ntuples that deviate from the "standard"
  // this routine needs to be over-written.
  for(Int_t icc=0;icc< nt10.cc_part; icc++){
    if(fDebug_Mode>0){
      cerr << "Storing DC entry number " << icc << endl;
    }

   fCCPB->Scsght=(Int_t  )(nt10.cc_sect[icc]*1000+
			   nt10.cc_segm[icc]*100+
			   nt10.cc_hit[icc]); // 1000*sector+100*CC_segm_ID+Hit_ID in CCRC
   fCCPB->Nphe=  (Float_t) nt10.nphe[icc];   // Number of photo-electrons
   fCCPB->Time=  (Float_t) nt10.cc_t[icc]; // Flight time relative to the evnt start time
   fCCPB->Path=  (Float_t) nt10.cc_r[icc]; // Path lenght from target
   fCCPB->Chi2cc=(Float_t) nt10.cc_c2[icc]; // Quality measure of geometrical matching
   fCCPB->Status=(Int_t  ) 1.; // Status word (not defined yet)

   TClonesArray &tCCPBBank = *fcaCCPBStore;
   new(tCCPBBank[fnCCPB_Store++]) TCCPBClass(fCCPB);
   
  }

}

void TNT10Reader::Fill_LCPB(void){
  // This function will fill the LCPB class.
  // For Ntuples that deviate from the "standard"
  // this routine needs to be over-written.
  for(Int_t ilc=0;ilc< nt10.lac_part; ilc++){
    if(fDebug_Mode>0){
      cerr << "Storing LAC entry number " << ilc << endl;
    }

    fLCPB->Scht=   (Int_t  )(nt10.lec_sect[ilc]*100+
			     nt10.lec_hit[ilc]); // 100*sector+Hit_ID in EC1R
    fLCPB->Etot=   (Float_t) nt10.lec_etot[ilc];  // Reconstructed total energy 
    fLCPB->Time=   (Float_t) nt10.lec_t[ilc];  // Flight time relative to the evnt start time
    fLCPB->Path=   (Float_t) nt10.lec_r[ilc];  // Path lenght from target
    fLCPB->X=      (Float_t) nt10.lec_x[ilc];  // x coordinate of the hit
    fLCPB->Y=      (Float_t) nt10.lec_y[ilc];  // y coordinate of the hit
    fLCPB->Z=      (Float_t) nt10.lec_z[ilc];  // z coordinate of the hit
    fLCPB->Chi2lc= (Float_t) nt10.lec_c2[ilc];  // Quality measure of geometrical matching
    fLCPB->Status= (Int_t  ) nt10.lec_stat[ilc];  // Status word
#ifdef NT10_E2b
    fLCPB->Ein=    (Float_t) nt10.lec_ein[ilc];  // Reconstructed energy in the inner part
#else
    fLCPB->Ein=    (Float_t) 0.;
#endif

    TClonesArray &tLCPBBank = *fcaLCPBStore;
    new(tLCPBBank[fnLCPB_Store++]) TLCPBClass(fLCPB);

  }

}


void TNT10Reader::InitBanks(void){
//
// Allocates one copy for each class for
// the BANK data.
//
  if(!fEvntHeader) fEvntHeader = new THEADERClass();
  if(!fEVNT)   fEVNT = new TEVNTClass();
  if(!fDCPB)   fDCPB = new TDCPBClass();
  if(!fECPB)   fECPB = new TECPBClass();
  if(!fSCPB)   fSCPB = new TSCPBClass();
  if(!fCCPB)   fCCPB = new TCCPBClass();
  if(!fLCPB)   fLCPB = new TLCPBClass();
}

void TNT10Reader::InitClones(){
  // Internal funtion to initialize the TClonesArray objects so we
  // can store classes in them. These TClonesArray-s are stored in 
  // the branches of the TTree.

  if(!fcaEVNTStore) fcaEVNTStore = new TClonesArray("TEVNTClass",1);
  if(!fcaECPBStore) fcaECPBStore = new TClonesArray("TECPBClass",1);
  if(!fcaSCPBStore) fcaSCPBStore = new TClonesArray("TSCPBClass",1);
  if(!fcaDCPBStore) fcaDCPBStore = new TClonesArray("TDCPBClass",1);
  if(!fcaCCPBStore) fcaCCPBStore = new TClonesArray("TCCPBClass",1);
  if(!fcaLCPBStore) fcaLCPBStore = new TClonesArray("TLCPBClass",1);
}

Int_t TNT10Reader::InitBranches(){
  //
  // Initialize the branches of the TTree.
  // Used internally in the code. 
  //

  Int_t bufsize = k__BUFSIZE__;
  Int_t split   = 1;

  if(fDebug_Mode>0){
    cerr << "Initializing Branches ... \n";
  }

  fEvntHeaderBranch = fTree->Branch("HEADER","THEADERClass",&fEvntHeader,bufsize,split);
  if(fDebug_Mode>0)cerr << "Header done... \n";  

  fTree->SetBranchStatus("HEADER",1);
  
  fEVNTBranch = fTree->Branch("EVNT",&fcaEVNTStore,bufsize,split);
  if(fDebug_Mode>0)cerr << "EVNT done... \n";  
  fECPBBranch = fTree->Branch("ECPB",&fcaECPBStore,bufsize,split);
  if(fDebug_Mode>0)cerr << "ECPB done... \n";  
  fSCPBBranch = fTree->Branch("SCPB",&fcaSCPBStore,bufsize,split);
  if(fDebug_Mode>0)cerr << "SCPB done... \n";  
  fDCPBBranch = fTree->Branch("DCPB",&fcaDCPBStore,bufsize,split);
  if(fDebug_Mode>0)cerr << "DCPB done... \n";  
  fCCPBBranch = fTree->Branch("CCPB",&fcaCCPBStore,bufsize,split);
  if(fDebug_Mode>0)cerr << "CCPB done... \n";  
  fLCPBBranch = fTree->Branch("LCPB",&fcaLCPBStore,bufsize,split);
  if(fDebug_Mode>0)cerr << "LCPB done... \n";  
  fTree->SetBranchStatus("*",1);
  return(1);

}

void TNT10Reader::SetBranchAddress(const char *bname, void **add){
  // 
  // We have to override this, since the branches are special.
  // They do not exist yet! Instead of just "setting" the branch,
  // we need to create it. 
  // The branches are created with fTree->Branch().
  // We need the pointer so that they can be filled from the file.

  Int_t bufsize = k__BUFSIZE__;
  Int_t split   = 1;

  if( strcmp(bname,"HEADER") == 0){
    fEvntHeaderBranch = fTree->Branch("HEADER","THEADERClass",add,bufsize,split);
    fEvntHeader =(THEADERClass *) (*add);
  }else if( strcmp(bname,"EVNT") == 0){
    fEVNTBranch  = fTree->Branch("EVNT",add,bufsize,split);
    fcaEVNTStore =(TClonesArray *)(*add);
  }else if( strcmp(bname,"ECPB") == 0){
    fECPBBranch  = fTree->Branch("ECPB",add,bufsize,split);
    fcaECPBStore =(TClonesArray *)(*add);
  }else if( strcmp(bname,"SCPB") == 0){
    fSCPBBranch  = fTree->Branch("SCPB",add,bufsize,split);
    fcaSCPBStore =(TClonesArray *)(*add);
  }else if( strcmp(bname,"DCPB") == 0){
    fDCPBBranch  = fTree->Branch("DCPB",add,bufsize,split);
    fcaDCPBStore =(TClonesArray *)(*add);
  }else if( strcmp(bname,"CCPB") == 0){
    fCCPBBranch  = fTree->Branch("CCPB",add,bufsize,split);
    fcaCCPBStore =(TClonesArray *)(*add);
  }else if( strcmp(bname,"LCPB") == 0){
    fLCPBBranch  = fTree->Branch("LCPB",add,bufsize,split);
    fcaLCPBStore =(TClonesArray *)(*add);
  }else{
    cerr << "WARNING -- This clas does not know about the " << bname << " bank.\n";
    cerr << "           Please make sure you are using the correct version. \n";
  }


}

Double_t TNT10Reader::LoadAll(void){
// This calls LoadTree() with as argument the last entry in the
// HBook file, thus forcing the entire HBook file to be read.
//
  Int_t totent=(Int_t)GetEntries()-1;
  LoadTree(totent);
  return(fEntries);
}

Int_t TNT10Reader::LoadTree(Int_t entry){
  //
  // The input argument entry is the serial number of the whole chain.
  // The function finds the corresponding Tree and reads and returns the
  // corresponding entry in this Tree.
  //
  // Since we are not reading Trees but HBook files, there is the additional
  // complication that we don't want to read the same event from the HBook 
  // file into the Tree twice. This is prevented by first checking if the 
  // requested event is already in the TTree. 
  // Such a mechanism only works if the NTUPLE is read sequentially! So
  // unless fReadSequential is set to kFALSE, a sequential read from the
  // ntuple is enforced.
  //
  // Also, with multiple files, we'd like to keep the Trees around, so we don't
  // need to read the HBook file again. As a result, this "chain" actually 
  // has only one giant tree. I hope we don't run out of memory.
  //
  Int_t iret=0;

  if(!fNtrees) return -1;
  if(entry < 0 || entry >= fEntries) return -2;
  if(!fTree){
    fTree = new TTree(this->TChain::GetName(),this->TChain::GetTitle());
    InitClones();
    InitBranches();
  }

  // See if this is an entry that was already read at some previous call.
  // Only possible with sequential reads.
  //
  Int_t n_found_local=-1;
  if(fReadSequential){
    n_found_local=fTree->GetEntry(entry);   
  }

  // Find which tree this entry belongs to
  Int_t t;
  if (fTreeNumber!=-1 &&
      (entry >= fTreeOffset[fTreeNumber] && entry < fTreeOffset[fTreeNumber+1])){
    t = fTreeNumber;
  }
  else {
    for (t=0;t<fNtrees;t++) {
      if (entry < fTreeOffset[t+1]) break;
    }
  }
  
  fReadEntry = entry - fTreeOffset[t];
  
  if(n_found_local>0){ // BUT, we already got it from the tree in memory.
    return(fReadEntry);
  }

   // If entry belongs to the current tree return entry

  // Detect whether the events are being read out of sequence.
  // If they ARE then the mechanisms to look up in the TTree first are
  // not possible, in fact, the TTree can get out of sequence, and can
  // then contain the same event more than once. We detect a non, sequential 
  // request, and then choose to read all events in between, or only the new
  // event, depending on the setting of fReadSequential.

  if( (entry > fNtLastRead + 1) && fReadSequential){
    // Read all the events in between the requested event and last read event.
    for(Int_t ievt=fNtLastRead;ievt<=entry;ievt++){
      LoadTree(ievt);
    }
    return(fReadEntry);
  }

  if (t == fTreeNumber) {
    // First try to get the entry from our current tree.

    CleanEventClones();        // Cleanup from any previous call.

    hgnt(fNtNum,fReadEntry+1,iret);
    if(fDebug_Mode>10){
      printf("Event: %5d %5d %6d \n",nt10.evntid,nt10.npart,nt10.evntclas);
    }
    if(iret){
      return(0);
    }
    Fill_Tree_from_Paw(); // Fill it.
    fNtLastRead = entry;

    return(fReadEntry);
  }

   if(fDebug_Mode>10)cerr << "Need new file.\n";

   if (!IsZombie()) {    // Close the file.
     Close();
   }

   TChainElement *element = (TChainElement*)fFiles->At(t);
   if (!element) return -4;

   Open(element->GetTitle());
   if (IsZombie()) {
     if(fDebug_Mode)cerr << "ZOMBIE \n";
     Close();
     return -3;
   }

   fTreeNumber = t;

   //check if fTreeOffset has really been set
   Int_t nentries = GetNTEntries();

   if (fTreeOffset[fTreeNumber+1] != fTreeOffset[fTreeNumber] + nentries) {
      fTreeOffset[fTreeNumber+1] = fTreeOffset[fTreeNumber] + nentries;
      fEntries = fTreeOffset[fNtrees];
      element->SetNumberEntries(nentries);
      //below, we must test >= in case the Tree has no entries
      if (entry >= fTreeOffset[fTreeNumber+1]) {
	if (fTreeNumber < fNtrees && entry < fTreeOffset[fTreeNumber+2]) return LoadTree(entry);
	else  fReadEntry = -2;
      }
   }

   //Set the branches status and address for the newly connected file
   SetChainOffset(fTreeOffset[t]);

   //update list of leaves in all TTreeFormula of the TTreePlayer (if any)
   if (fPlayer) fPlayer->UpdateFormulaLeaves();

   //Notify user if requested
   if (fNotify) fNotify->Notify();

   LoadTree(fReadEntry);  //Recurse now you got the right file.
   return fReadEntry;



}

void TNT10Reader::CleanEventClones(){
  //
  // Clears all the TCloneArray object to get ready for next event.
  //
  if(fDebug_Mode>10){
    cerr << "Clearing Clones arrays.\n";
  }
  if(fcaEVNTStore)  fcaEVNTStore->Clear();
  if(fcaECPBStore)  fcaECPBStore->Clear();
  if(fcaSCPBStore)  fcaSCPBStore->Clear();
  if(fcaDCPBStore)  fcaDCPBStore->Clear();
  if(fcaCCPBStore)  fcaCCPBStore->Clear();
  if(fcaLCPBStore)  fcaLCPBStore->Clear();

  // Reset the counters as well.

  fnEVNT_Store=0;
  fnECPB_Store=0;
  fnSCPB_Store=0;
  fnDCPB_Store=0;
  fnCCPB_Store=0;
  fnLCPB_Store=0;
  
}

Int_t TNT10Reader::Close(void){
  if(fgLuns) fgLuns[fHbookLun-10]=0;  // Release the lun.
  hrend(PASSCHAR("NT10"),4);

  return(0);
};

Int_t TNT10Reader::Open(const char *name){
//
// Open an HBOOK file for reading.
// Return 1 on failure, 0 on success.

Int_t iret=0,recsiz=0;
Int_t bignum=9999,zero=0;

  if(fHbookLun>0){
    if(fDebug_Mode>4)cerr << "Forgot to close lun?\n";
    Close();         // Forgot to close?
  }
  
  //find a free logical unit (max 10)
  fHbookLun=0;
  for (Int_t i=0;i<10;i++) {
    if (fgLuns[i] == 0) {
      fHbookLun = 10+i;
      fgLuns[i] = 1;
      break;
    }
  }

  if (fHbookLun == 0) {
    TChain::Error("THbookFile","Too many HbookFiles\n");
    return(0);
  }

  if(fDebug_Mode>4)cerr << "Opening file: " << name << endl;

  hropen(fHbookLun,PASSCHAR("NT10"),PASSCHAR(name),PASSCHAR("p"),recsiz,iret,4,strlen(name),1);
  if(iret){
    fHbookLun = 0;
    fgLuns[fHbookLun-10]=0;
    cerr << "Could not open file. Iret = " << iret << endl;

    return(0);
  }

  hrin(fNtNum,bignum,zero);
  fNevents = (Int_t)GetNTEntries();
  if(fNevents == 0){
    cerr << "ERROR reading NT10 ntuple.\n";
    Close();
    return(0);
  }

  if(fDebug_Mode > 0){
    Dir();
    NTPrint();
    cerr << "Number of events: " << fNevents << endl;
  }

  hbname(fNtNum,PASSCHAR(" "),zero,PASSCHAR("$CLEAR"),1,6);
  hbname(fNtNum,PASSCHAR("HEVT"),nt10.npart,PASSCHAR("$SET"),4,4);
  hbname(fNtNum,PASSCHAR("EVNT"),nt10.gpart,PASSCHAR("$SET"),4,4);
  hbname(fNtNum,PASSCHAR("DCPB"),nt10.dc_part,PASSCHAR("$SET"),4,4);
  hbname(fNtNum,PASSCHAR("ECPB"),nt10.ec_part,PASSCHAR("$SET"),4,4);
  hbname(fNtNum,PASSCHAR("SCPB"),nt10.sc_part,PASSCHAR("$SET"),4,4);
  hbname(fNtNum,PASSCHAR("CCPB"),nt10.cc_part,PASSCHAR("$SET"),4,4);

  SetTitle("NT10");
  SetName(name);
  gROOT->GetListOfBrowsables()->Add((TChain *)this,name);

  fList = new TList();
  fKeys = new TList();
  for (Int_t key=1;key<1000000;key++) {
     Int_t z0 = 0;
     rzink(key,z0,"S",1);
     if (quest[0]) break;
     if (quest[13] & 8) continue;
     Int_t id = quest[20];
     THbookKey *akey = new THbookKey(id,(THbookFile *)this);
     fKeys->Add(akey);
  }

  return(1);  
}

void TNT10Reader::PrintEventStatus(){
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
    cout << " EVNT    |       " << fcaEVNTStore->GetEntries() << endl;
    cout << " ECPB    |       " << fcaECPBStore->GetEntries() << endl;
    cout << " SCPB    |       " << fcaSCPBStore->GetEntries() << endl;
    cout << " DCPB    |       " << fcaDCPBStore->GetEntries() << endl;
    cout << " CCPB    |       " << fcaCCPBStore->GetEntries() << endl;
    cout << " LCPB    |       " << fcaLCPBStore->GetEntries() << endl;
    cout << " TGBI    |       " << fcaTGBIStore->GetEntries() << endl;

#ifdef WRITE_GSIM
    cout << " GSIM    |       " << fcaGSIMStore->GetEntries() << endl; 
#endif
    cout << "---------+-------------"  << endl << endl;
  }
}




void TNT10Reader::Browse(TBrowser *b){
  // Allow for browsing of the TTree. Note that you will 
  // only be browsing the events that have already been loaded!
  // To make sure you read all the events, manually
  // call LoadAll() first.

 if(b){
   b->Add(fTree);
   // b->Add(this);
   b->Add(fList,"memory");
   b->Add(fKeys,"IDs on disk");
  }
}

void TNT10Reader::Dir(void){
//  HBOOK directory listing of the hbook file.
  hldir(PASSCHAR("//"),PASSCHAR("T"),2,1);
}


Int_t TNT10Reader::GetNTEntries() const{
// This gets the number of entries in the currently attached HBook file.
  Int_t noent;
  hnoent(fNtNum,noent);
  return(noent);
}


void TNT10Reader::NTPrint(void){
// HBook style print of the contends of the current ntuple.
  hprnt(fNtNum);
}

Int_t TNT10Reader::SetNtNum(Int_t ntnum){
// Set the number of the ntuple to use. Default =10.
  if(ntnum>0)fNtNum=ntnum;

  return(fNtNum);
}

Int_t TNT10Reader::GetNRows(const Char_t *bankname){
//   This Function returns number of rows (number of 
// entries) of specified Bank (Clones Array). The string
// argument passed to function is the name of bank.
// EVNT,ECPB,SCPB,DCPB,CCPB or LCPB.
// Any other string passed to function will return -1 
// indicating that there is no bank with that name...
//
  Int_t nRows = -1;

  if(strncmp(bankname,"EVNT",4) == 0){
    nRows = fcaEVNTStore->GetEntries();
  }
  if(strncmp(bankname,"ECPB",4) == 0){
    nRows = fcaECPBStore->GetEntries();
  }

  if(strncmp(bankname,"SCPB",4) == 0){
    nRows = fcaSCPBStore->GetEntries();
  }
  if(strncmp(bankname,"DCPB",4) == 0){
    nRows = fcaDCPBStore->GetEntries();
  }
  if(strncmp(bankname,"CCPB",4) == 0){
    nRows = fcaCCPBStore->GetEntries();
  }
  if(strncmp(bankname,"LCPB",4) == 0){
    nRows = fcaLCPBStore->GetEntries();
  }
  if(strncmp(bankname,"TGBI",4) == 0){
    nRows = fcaTGBIStore->GetEntries();
  }
  if(fDebug_Mode & kDBG_Error){
    if(nRows == -1){
      cout << "TClasTool::NBankRows (ERROR): Bank \"" << bankname << "\" not found.."<< endl;
    }
  }

  return nRows;
}

TVector3  TNT10Reader::GetPart3Vector(Int_t indx){
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
TVector3  TNT10Reader::GetPartVertex(Int_t indx){
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

      
Int_t  TNT10Reader::GetPartID(Int_t indx){
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

Int_t  TNT10Reader::GetPartCharge(Int_t indx){
  Int_t  p_ch = 0;
  if(indx>=0 && indx<GetNPart()){
    TEVNTClass *cEvnt = (TEVNTClass *) GetBankRow("EVNT",indx);
    if(cEvnt!=NULL){ 
      p_ch = cEvnt->GetCharge();
    } else if(fDebug_Mode&kDBG_Error) cout << "GetPartID: Particle does not exist.." << endl;
  } else if(fDebug_Mode&kDBG_Error) cout << "GetPartID: Cannot find particle at row " << indx 
	      << "  there are only " << GetNPart() << "  particle in the event" << endl;
  return p_ch;
}



Int_t  TNT10Reader::GetEventNumber(){
  // Return the physics event number from the HEADER bank
  return(fEvntHeader->NEvent);
}

Int_t  TNT10Reader::GetRunNumber(){
  // Return the run number.
  // This is currently not properly implemented, it will
  // always return 0, since we need to modify the Open
  // command to find out the runnumber from the file name.
  return(fNRun);
}

Int_t  TNT10Reader::GetCurrentEvent(){
  // Returns the number of the current event in the Next() sequence.
  // This is not the "Physics event" number, which you get from the header class.
  return fCurrentEvent;
}


TObject  *TNT10Reader::GetBankRow(const Char_t *bankname,Int_t nrow){
  //
  // Get a specific bank given the bankname at a specific row given the row name  

  TClonesArray *BankStore = 0;


  if(strncmp(bankname,"EVNT",4) == 0){
    BankStore  =  fcaEVNTStore;
    if((fDebug_Mode& kDBG_Debug2) > 0) cout << "TClasTool::GetBankRow : Set Pointer to fcaDataPointer " << endl;
  }

  if(strncmp(bankname,"ECPB",4) == 0){
    BankStore  =  fcaECPBStore;
    if((fDebug_Mode&kDBG_Debug2) > 0) cout << "TClasTool::GetBankRow : Set Pointer to fcaECPBStore " << endl;
  }
  if(strncmp(bankname,"SCPB",4) == 0){
    BankStore  =  fcaSCPBStore;
    if((fDebug_Mode&kDBG_Debug2) > 0) cout << "TClasTool::GetBankRow : Set Pointer to fcaSCPBStore " << endl;
  }
  if(strncmp(bankname,"DCPB",4) == 0){
    BankStore  =  fcaDCPBStore;
    if((fDebug_Mode&kDBG_Debug2) > 0) cout << "TClasTool::GetBankRow : Set Pointer to fcaDCPBStore " << endl;
  }
  if(strncmp(bankname,"CCPB",4) == 0){
    BankStore  =  fcaCCPBStore;
    if((fDebug_Mode&kDBG_Debug2) > 0) cout << "TClasTool::GetBankRow : Set Pointer to fcaCCPBStore " << endl;
  }
  if(strncmp(bankname,"LCPB",4) == 0){
    BankStore  =  fcaLCPBStore;
    if((fDebug_Mode&kDBG_Debug2) > 0) cout << "TClasTool::GetBankRow : Set Pointer to fcaLCPBStore " << endl;
  }
  
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

TChain *TNT10Reader::GetTree(Char_t *treename){
  // Return the TChain that underlies this reader.
  // Since we inherit from TChain, this reader IS the chain
  // so we return ourselves.
  //
  return(this);
}


ClassImp(TNT10Reader)

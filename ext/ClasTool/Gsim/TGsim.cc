// @(#)ClasTool/ClasBanks:$Name:  $:$Id: TGsim.cc,v 1.7 2008/03/19 18:02:47 gavalian Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>
//____________________ 
//Begin_Html <!--
/* -->
</pre><H1> TGsim </H1>
<H2> A <b>GSIM</b> interface class.</H2>
<p>Created by initial Author:  Maurik Holtrop (UNH) Dec-7-2000 <p>
<p>
This class defines an interface to the GSIM code, the Monte Carlo 
simulation of the CLAS detector. <p>
More about GSIM can be found in the GSIM web pages: <A HREF="HTTP://improv.unh.edu/Maurik/gsim_info.shtml">
HTTP://improv.unh.edu/Maurik/gsim_info.shtml</A>.<p>
Most of this class deals with interfacing to BOS. This implementation is
quite limited, just enough for GSIM purposes. It would be easy to extend,
and can in principle be used for any BOS bank, and yes, be my guest and
make a nice template class, now that ROOT supports templates...
Some of this code will work only when compiled, since there are limitatons 
to the incorporation of C structures in CINT. These can all be overcome
by writing little classes like the TMCTKClass example.<p>
Why did I not use the "pre-made" clasbanks.h implementation of BOS classes?<p>
The main reason for that was that it did not seem to work well with ROOT, and
so using the structures was easier. The classbanks.h implementation depends on 
the clasbanks.cc/libbankdefs.a code, which I did not want to crank through CINT.<p>
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////////////////////////////

#include "TGsim.h"

ClassImp(TGsim)

//------------------------------------------------------------------------------
//
// Masses of commonly used particles.
//
const Float_t TGsim::fgGeant_Particle_Mass[kG_NParticleTypes]= {
  0.0,          // kG_Unknown
  0.0,   	// kG_Photon     
  0.00051099906,// kG_Positron 
  0.00051099906,// kG_Electron 
  0.0,          // kG_Neutrino
  0.105658389,  // kG_Muon_Plus
  0.105658389,  // kG_Muon_Minus
  0.1349764,    // kG_Pion_Neutral
  0.1395700,	// kG_Pion_Plus  
  0.1395700,	// kG_Pion_Minus 
  0.497672,     // kG_Kaon_Long
  0.493677,	// kG_Kaon_Plus  
  0.493677,	// kG_Kaon_Minus 
  0.93956563,	// kG_Neutron    
  0.93827231,	// kG_Proton     
  0.93827231,	// kG_AntiProton     
  0.497672,     // kG_Kaon_Short,           
  0.54745,	// kG_Eta,                  
  1.115684,	// kG_Lambda,               
  1.18937,	// kG_Sigma_Plus,           
  1.19255,	// kG_Sigma_Neutral, //20   
  1.197436,	// kG_Sigma_Minus,          
  1.3149,	// kG_Cascade_Neut,         
  1.32132,	// kG_Cascade_Minus,        
  1.67245,	// kG_Omega,                
  0.93956563,	// kG_Anti_Neutron,         
  1.115684,	// kG_Anti_Lambda,          
  1.18937,	// kG_Anti_Sigma_Minus,     
  1.19255,	// kG_Anti_Sigma_Zero,      
  1.197436,	// kG_Anti_Sigma_Plus,      
  1.3149,	// kG_Anti_Cascade_Neut,  //
  1.32132,	// kG_Anti_Cascade_Plus,    
  1.67245,	// kG_Anti_Omega,         //
  0,		// kG_Undef_33,             
  0,		// kG_Undef_34,             
  0,		// kG_Undef_35,             
  0,		// kG_Undef_36,             
  0,		// kG_Undef_37,             
  0,		// kG_Undef_38,             
  0,		// kG_Undef_39,             
  0,		// kG_Undef_40,             
  0,		// kG_Undef_41,             
  0,		// kG_Undef_42,             
  0,            // kG_Undef_43,             
  0,            // kG_Undef_44,             
  1.875613,     // kG_Deuteron   	
  2.80925,      // kG_Tritium,
  3.7274,	// kG_He4       
  0.0,          // kG_Geantino,             
  2.8092};	// kG_He3

// Particle Types according to the PDG, with extensions for 2H,3He,4He.
//
const Int_t TGsim::fgGeant_Particle_Id[kG_NParticleTypes]={ 
  kG_Unknown_Id,
  kG_Photon_Id,
  kG_Positron_Id,
  kG_Electron_Id,
  kG_Neutrino_Id,
  kG_Muon_Plus_Id,
  kG_Muon_Minus_Id,
  kG_Pion_Neutral_Id,
  kG_Pion_Plus_Id,
  kG_Pion_Minus_Id,
  kG_Kaon_Long_Id,
  kG_Kaon_Plus_Id,
  kG_Kaon_Minus_Id,
  kG_Neutron_Id,
  kG_Proton_Id,
  kG_AntiProton_Id,
  kG_Kaon_Short_Id,
  kG_Eta_Id,
  kG_Lambda_Id,
  kG_Sigma_Plus_Id,
  kG_Sigma_Neutral_Id,
  kG_Sigma_Minus_Id,
  kG_Cascade_Neut_Id,
  kG_Cascade_Minus_Id,
  kG_Omega_Id,
  kG_Anti_Neutron_Id,
  kG_Anti_Lambda_Id,
  kG_Anti_Sigma_Minus_Id,
  kG_Anti_Sigma_Zero_Id,
  kG_Anti_Sigma_Plus_Id,
  kG_Anti_Cascade_Neut_Id,
  kG_Anti_Cascade_Plus_Id,
  kG_Anti_Omega_Id,
  kG_Anti_Tau_Id, //33
  kG_Tau_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Unknown_Id,
  kG_Deuteron_Id,
  kG_Tritium_Id,
  kG_He4_Id,
  kG_Geantino_Id,
  kG_He3_Id};
//
// Particle Id Label
//
const char *TGsim::fgGeant_Particle_Label[kG_NParticleTypes]={ 
  "Unkn",
  "Phot", // 1
  "Posi", // 2 
  "Elec", // 3
  "Ntro", // 4
  "Mu+ ", // 5
  "Mu- ", // 6
  "Pi0 ", // 7
  "Pi+ ", // 8
  "Pi- ", // 9
  "Klon", // 10
  "K+  ", // 11
  "K-  ", // 12
  "Neut", // 13
  "Prot", // 14
  "APro", // 15
  "Ksho", // 16
  "Eta ", // 17
  "Lamb", // 18
  "Sig+", // 19
  "Sig0", // 20
  "Sig-", // 21
  "Cas0", // 22
  "Cas-", // 23
  "Omeg", // 24
  "ANeu", // 25
  "ALam",
  "ASg-",
  "ASg0",
  "ASg+",
  "ACs0",
  "ACs+",
  "AOme",
  "U33 ",
  "U34 ",
  "U35 ",
  "U36 ",
  "U37 ",
  "U38 ",
  "U39 ",
  "U40 ",
  "U41 ",
  "U42 ",
  "U43 ",
  "U44 ",
  "Deut",
  "Trit",
  "He4 ",
  "Gean",
  "He3 "
  };


//------------------------------------------------------------------------------
TGsim::TGsim(){
//
// The default constructor will initialize BOS, and also provide the FORMAT
// of a number of common BOS banks. Other formats can be found in the appropriate
// *.ddl files in packages/clasbanks
//
  cerr << "TGsim Initializing BOS.\n";

  fDesc_in=0;
  fDesc_out=0;
  fDebug_Mode=0;
    

  bosInit(bcs_.iw,NBCS);

  BankFormat("HEAD","8I");           // You can find these definition in bankdefs
  BankFormat("PART","I,8F,I,2F,I");  // or in c_bos_io/configure_banks.c
  BankFormat("GPAR","F,I,5A");
  BankFormat("MCTK","6F,5I");
  BankFormat("MCVX","4F,I");
  BankFormat("MCEV","2I");
  BankFormat("TAGR","3F,3I");
  BankFormat("DCH ","10F,3I");
  BankFormat("EC  ","B16");
  BankFormat("EC1 ","B16");
  BankFormat("SC  ","B16");
  BankFormat("CC  ","B16");  
  BankFormat("DC0 ","B16");  
  BankFormat("DOCA","B16");  
  BankFormat("ECH ","7F,I,3F");
  BankFormat("SCH ","7F,2I");
  BankFormat("CCH ","6I,6F");
  BankFormat("DCH ","10F,3I");

}

//------------------------------------------------------------------------------
Int_t TGsim::BankFormat(const char *name,const char *format){
  // "Format" a bank, look up in the BOS manual why.
  Int_t status;
  char  nam[5];
  char *fm=(char *)malloc(strlen(format)+1);
  strcpy(nam,name);
  strcpy(fm,format);
  status=bosNformat(bcs_.iw,(void *)nam,fm);
  free(fm);
  return(status);	 
}



//------------------------------------------------------------------------------
Int_t TGsim::OpenFile(char *name,char *readwrite){
  // Open a BOS/fpack file for reading or writing. 
  // If readwrite="r" the file is opened for reading,
  // if readwrite="w" the file is opened for writing.
  // NOTE: Only one input file and one output file are allowed.

 Int_t status;

  if(strncmp(readwrite,"r",1)==0){ // Open for reading
    status= bosOpen(name,"r",&fDesc_in);
  }else{
    status= bosOpen(name,"w",&fDesc_out);
  }

  return(status);
}

//------------------------------------------------------------------------------
Int_t TGsim::WriteBOS(){
  // Write the current BOS array to the file.
  // A return status of 0 means all was ok.

  Int_t status;
  if(fDesc_out){
    status=bosWrite(fDesc_out,bcs_.iw,"HEADMCTKMCVXMCEVPART");
    // status=bosWrite(fDesc_out,bcs_.iw,"0");
    bosLdrop(bcs_.iw,"E");
    bosLdrop(bcs_.iw,"E");  // This might by now be folklore, I don't have time to check
    bosWgarbage(bcs_.iw);   // but at some point the working knowledge was to drop and
    bosWgarbage(bcs_.iw);   // garbage collect twice....
    return(status);
  }else{
    cerr << "TGsim::WriteBOS() -- No file opened for writing\n";
    return(-1);
  }
}

//------------------------------------------------------------------------------
Int_t TGsim::ReadBOS(){
  // Read a new event into the BOS array from the file.
  // Return 0 when reading went ok.
  
  bosLdrop(bcs_.iw,"E");
  bosLdrop(bcs_.iw,"E");  // This might by now be folklore, I don't have time to check
  bosWgarbage(bcs_.iw);   // but at some point the working knowledge was to drop and
  bosWgarbage(bcs_.iw);   // garbage collect twice....

  if(fDesc_in)return(bosRead(fDesc_in,bcs_.iw,"E"));
  else{
    cerr << "TGsim::ReadBOS() -- No file opened for reading\n";
    return(-1);
  }
}



//------------------------------------------------------------------------------
void TGsim::CloseFiles(Int_t desc){
  // Close all open BOS files.
  // This must be called to flush the buffers, else the file may be missing events!

  if(desc==0){
    if(fDesc_out){
      bosWrite(fDesc_out,bcs_.iw,"0"); // Flush the buffers.
      bosClose(fDesc_out);
    }
    if(fDesc_in )bosClose(fDesc_in);
  }else{
    bosClose(desc);
  }
  
}
  
//------------------------------------------------------------------------------
Int_t TGsim::CopyEvent(TVirtualReader *ea){
  // Copy an event from the ROOT file into the HEAD and PART banks of the BOS file.
  // DOES NOT WRITE IT OUT, call WriteBOS() after.

  CreateBank("HEAD",0);
  FillHEAD(ea->GetHEADER());

  Int_t npart=ea->GetNRows("EVNT");

  CreateBank("PART",0,-1,npart);
  for(Int_t i=0;i<npart;i++){
    TEVNTClass *part=(TEVNTClass *)ea->GetBankRow("EVNT",i);
    if(part!= NULL){
      FillPART(part,0,i);
    }else{
      cerr << "TGsim::CopyEvent - found NULL part bank.\n";
    }
  }
  return(0);
}
      
//------------------------------------------------------------------------------
clasPART_t *TGsim::FillPART(TGSIMClass *gsim,Int_t nr, Int_t nrow){
// Fill PART bank from the TGSIMClass class.
  clasPART_t *part=(clasPART_t *)GetBank("PART",nr);
  if(part==NULL){
    cerr << "TGsim::FillPART -- PART bank not found in BOS array, please create before filling.\n";
    return(NULL);
  }
  
  Float_t Mass=GetPartMassFromIndex(gsim->Id);
  part->part[nrow].pid = gsim->Id;
  part->part[nrow].q   = gsim->Charge;
  part->part[nrow].vert.x  = gsim->X;
  part->part[nrow].vert.y  = gsim->Y;
  part->part[nrow].vert.z  = gsim->Z;  
  part->part[nrow].p.space.x = gsim->Px;
  part->part[nrow].p.space.y = gsim->Py;
  part->part[nrow].p.space.z = gsim->Pz;
  part->part[nrow].p.t = TMath::Sqrt( gsim->Px*gsim->Px + 
				      gsim->Py*gsim->Py + 
				      gsim->Pz*gsim->Pz +
				      Mass*Mass);
  part->part[nrow].trkid=0;
  part->part[nrow].qpid=1;
  part->part[nrow].qtrk=1;
  part->part[nrow].flags=0;
				      
  return(part);
}

//------------------------------------------------------------------------------
clasPART_t *TGsim::FillPART(TEVNTClass *evnt,Int_t nr,Int_t nrow){
// Fill PART bank from the TGSIMClass class.
// 
  clasPART_t *part=(clasPART_t *)GetBank("PART",nr);
  if(part==NULL){
    cerr << "TGsim::FillPART -- PART bank not found in BOS array, please create before filling.\n";
    return(NULL);
  }
  
  Int_t index=PDG_to_Geant(evnt->Id);
  Float_t Mass=GetPartMassFromIndex(index);
  part->part[nrow].pid = index;
  part->part[nrow].q   = evnt->Charge;
  part->part[nrow].vert.x  = evnt->X;
  part->part[nrow].vert.y  = evnt->Y;
  part->part[nrow].vert.z  = evnt->Z;  
  part->part[nrow].p.space.x = evnt->Px;
  part->part[nrow].p.space.y = evnt->Py;
  part->part[nrow].p.space.z = evnt->Pz;
  part->part[nrow].p.t = TMath::Sqrt( evnt->Px*evnt->Px + 
				      evnt->Py*evnt->Py + 
				      evnt->Pz*evnt->Pz +
				      Mass*Mass);
  part->part[nrow].trkid=0;
  part->part[nrow].qpid=1;
  part->part[nrow].qtrk=1;
  part->part[nrow].flags=0;
				      
// 

  return(part);
}

//------------------------------------------------------------------------------
void        TGsim::FillMCTKPART(int  n_row, int  pid, int _charge, TVector3  _vrt, TLorentzVector _mom)
{
  clasMCTK_t  *mctk_p = (clasMCTK_t *) GetBank("MCTK",0);
  clasMCVX_t  *mcvx_p = (clasMCVX_t *) GetBank("MCVX",0);
 
  if(mctk_p==NULL){
    cerr << "TGsim::FillMCTKPart -- MCTK Bank does not exist. Create it first" << endl;
    return;
  }

  if(mcvx_p==NULL){
    cerr << "TGsim::FillMCTKPart -- MCVX Bank does not exist. Create it first" << endl;
    return;
  }

  mctk_p->mctk[n_row].cx   = _mom.Px()/_mom.P();
  mctk_p->mctk[n_row].cy   = _mom.Py()/_mom.P();
  mctk_p->mctk[n_row].cz   = _mom.Pz()/_mom.P();
  mctk_p->mctk[n_row].pmom = _mom.P();
  mctk_p->mctk[n_row].mass = _mom.M();
  mctk_p->mctk[n_row].id   = pid;
  mctk_p->mctk[n_row].charge = (float ) _charge;
  mctk_p->mctk[n_row].flag = n_row+1;
  mctk_p->mctk[n_row].beg_vtx = n_row+1;
  mctk_p->mctk[n_row].end_vtx = 0;
  mctk_p->mctk[n_row].parent = 0;

  mcvx_p->mcvx[n_row].x = _vrt.X();
  mcvx_p->mcvx[n_row].y = _vrt.Y();
  mcvx_p->mcvx[n_row].z = _vrt.Z();
  mcvx_p->mcvx[n_row].flag = 1;
  mcvx_p->mcvx[n_row].tof = 0.0;
}

clasPART_t *TGsim::FillPART(Int_t nr,Int_t nrow,Int_t pid,Int_t q,TVector3 *vert,TLorentzVector *mom,Float_t weight){
// Fill PART bank from the input.
// NOTE: PID is the GEANT PID !!!
  clasPART_t *part=(clasPART_t *)GetBank("PART",nr);
  if(part==NULL){
    cerr << "TGsim::FillPART -- PART bank not found in BOS array, please create before filling.\n";
    return(NULL);
  }
  part->part[nrow].pid = pid;
  part->part[nrow].q   = q;
  part->part[nrow].vert.x = vert->X();
  part->part[nrow].vert.y  = vert->Y();
  part->part[nrow].vert.z  = vert->Z();  
  part->part[nrow].p.space.x = mom->X();
  part->part[nrow].p.space.y = mom->Y();
  part->part[nrow].p.space.z = mom->Z();
  part->part[nrow].p.t = mom->T();
  part->part[nrow].trkid=0;
  part->part[nrow].qpid=1;
  part->part[nrow].qtrk=weight;
  part->part[nrow].flags=0;
				      
// 

  return(part);
}

//------------------------------------------------------------------------------
clasHEAD_t *TGsim::FillHEAD(THEADClass *head){
// Fill HEAD bank from the THEAD Class.
// 
  clasHEAD_t *hbank=(clasHEAD_t *)GetBank("HEAD",0);
  if(hbank==NULL){
    hbank=(clasHEAD_t *)CreateBank("HEAD",0);
  }

  hbank->head[0].version=head->Version;
  hbank->head[0].nrun   =head->Nrun;
  hbank->head[0].nevent =head->Nevent;
  hbank->head[0].time   =head->Time;
  hbank->head[0].type   =head->Type;
  hbank->head[0].roc    =head->Roc;
  hbank->head[0].evtclass   =head->Evtclass;
  hbank->head[0].trigbits   =head->Trigbits;

  return(hbank);
}

//------------------------------------------------------------------------------
clasHEAD_t *TGsim::FillHEAD(THEADERClass *head){
// Fill HEAD bank from the THEADERClass.
// 
  clasHEAD_t *hbank=(clasHEAD_t *)GetBank("HEAD",0);
  if(hbank==NULL){
    hbank=(clasHEAD_t *)CreateBank("HEAD",0);
  }

  hbank->head[0].version=2;
  hbank->head[0].nrun   =head->NRun;
  hbank->head[0].nevent =head->NEvent;
  hbank->head[0].time   =head->Time;
  hbank->head[0].type   =head->Type;
  hbank->head[0].roc    =head->ROC;
  hbank->head[0].evtclass   =head->EvtClas;
  hbank->head[0].trigbits   =head->TrigBits;

  return(hbank);
}

//------------------------------------------------------------------------------
clasHEAD_t *TGsim::FillHEAD(Int_t runnum, Int_t evt_num){
// Fill HEAD bank from the nums given.
// 
  clasHEAD_t *hbank=(clasHEAD_t *)GetBank("HEAD",0);
  if(hbank==NULL){
    hbank=(clasHEAD_t *)CreateBank("HEAD",0);
  }

  hbank->head[0].version=2;
  hbank->head[0].nrun   =runnum;
  hbank->head[0].nevent =evt_num;
  hbank->head[0].time   = fNow.Get();
  hbank->head[0].type   = -4;
  hbank->head[0].roc    = 0;
  hbank->head[0].evtclass = 15; // Physics event.
  hbank->head[0].trigbits = 0;

  return(hbank);
}

//------------------------------------------------------------------------------
Float_t TGsim::GetPartMassFromPid(Int_t pid){
// Get the Mass of a particle given the PDG pid.
  Int_t index= PDG_to_Geant(pid);
  return(GetPartMassFromIndex(index));
}

//------------------------------------------------------------------------------
Float_t TGsim::GetPartMassFromIndex(Int_t index){
// Get the Mass of a particle given the GEANT index.
  if(index<0 || index>=kG_NParticleTypes)return(0);
  return(fgGeant_Particle_Mass[index]);
}

//------------------------------------------------------------------------------
void * TGsim::CreateBank(char *name,Int_t nr,Int_t ncols,Int_t nrows){
  // Create a named bank in the bos array.
  // Unfortunately you have to look up somewhere the defined size of the bank and put this in
  // "ncols". The "nr" is the bank number, for "sector" banks, 1-6, otherwise 0 is fine.
  // The "nrows" indicated how many copies you require.
  // An pointer  into the IW array is returned for access to the banks.
  //
  // For HEAD and PART bank you can set ncols to -1.
  // Note, "name" is send through FixName, thus affecting previous fixname returned vars.

  Int_t ind;
  Int_t lncols=ncols;

  if(ncols== -1){ // User asks us to look up size.
    if(strcmp(name,"HEAD")==0){
      lncols = sizeof(head_t)/4;
    }else if(strcmp(name,"PART")==0){
      lncols = sizeof(part_t)/4;
    }else{
      cerr << "I do not know the size of bank " << name << endl;
      return(NULL);
    }
  }


  ind =  bosNcreate(bcs_.iw,FixName(name),nr,lncols,nrows);
  if(ind==0)return(NULL);
  else return((void *) &bcs_.iw[ind-6]);
}

//------------------------------------------------------------------------------
void * TGsim::GetBank(const char *name,Int_t nr){
  // Find a BOS bank in the array and return a pointer to it.
  Int_t ind;
  ind = bosNlink(bcs_.iw,FixName(name),nr);
  if(ind==0)return(NULL);
  return(&bcs_.iw[ind-6]);
}

//------------------------------------------------------------------------------
Int_t TGsim::GetEvtNum(){
// Return the event number from the HEAD bank.
  clasHEAD_t *head=(clasHEAD_t *)GetBank("HEAD",0);
  return(head->head[0].nevent);
}
  
//------------------------------------------------------------------------------
Int_t TGsim::GetRunNum(){
// Return the run number from the HEAD bank.
  clasHEAD_t *head=(clasHEAD_t *)GetBank("HEAD",0);
  return(head->head[0].nrun);
}

//------------------------------------------------------------------------------
Int_t TGsim::GetPartId(Int_t nr,Int_t nrow){
// Return the particle id for PART at nr, nrow
  clasPART_t *pp=(clasPART_t *)GetBank("PART",nr);
  return(pp->part[nrow].pid);
}

//------------------------------------------------------------------------------
Float_t TGsim::GetPartQ(Int_t nr,Int_t nrow){
// Return the particle charge for PART at nr, nrow
  clasPART_t *pp=(clasPART_t *)GetBank("PART",nr);
  return(pp->part[nrow].q);
}
//------------------------------------------------------------------------------
TVector3 TGsim::GetPartVert(Int_t nr,Int_t nrow){
// Return the particle vertex as TVector3 for PART at nr, nrow
  clasPART_t *pp=(clasPART_t *)GetBank("PART",nr);
  TVector3 ans(pp->part[nrow].vert.x,pp->part[nrow].vert.y,pp->part[nrow].vert.z);
  return(ans);
}

//------------------------------------------------------------------------------
TLorentzVector  TGsim::GetPartP4(Int_t nr,Int_t nrow){
// Return the particle 4 momentum as TLorentzVector for PART at nr, nrow
  clasPART_t *pp=(clasPART_t *)GetBank("PART",nr);
  TLorentzVector ans(pp->part[nrow].p.space.x,
		     pp->part[nrow].p.space.y,
		     pp->part[nrow].p.space.z,
		     pp->part[nrow].p.t);
  return(ans);
}

//------------------------------------------------------------------------------
Bool_t TGsim::IsMCEvent(Int_t itype){
//
// Test if event is an MC event. 
// All events with type < 0 should be MC events.
// If itype is not equal to zero, test for itype MC events only.
// Supposedly: type == -1 -- SDA event.
//             type == -2 -- GEANT event.
//             type == -3 -- ClasSim event.
//
    clasHEAD_t *ph=(clasHEAD_t *)GetBank("HEAD",0);
    if(itype == 0 && ph->head[0].type < 0 )return(kTRUE);
    else if( itype != 0 && ph->head[0].type == -TMath::Abs(itype))return(kTRUE);
    else return(kFALSE);
}
//------------------------------------------------------------------------------
Bool_t TGsim::IsDataEvent(Int_t itype){
//
// Test if event is a Data event. 
// If itype is not specified it defaults to 2.
// If itype == 0, test for type=2 or type=4
//
// Data events have 1 <= type <= 10
//  2 == Physics Event
//  4 == Level2 Late Fail
// 10 == Scaler event.
//
    clasHEAD_t *ph=(clasHEAD_t *)GetBank("HEAD",0);
    if(itype == 0 && ( ph->head[0].type == 2 || ph->head[0].type == 4) )return(kTRUE);
    else if( itype != 0 && ph->head[0].type == itype)return(kTRUE);
    else return(kFALSE);
}

//------------------------------------------------------------------------------
char gTmpname[5];
char *TGsim::FixName(const char *name){
  // Fixes length problems in BOS names. 
  // All BOS names must be exactly 4 characters (duh, it's fortran).
  // NOTE: this can only be used once, the next time it is used all the 
  // previous pointers returned are overwritten.
  Int_t length = strlen(name);

  if (length>4) {
    cout<<"TRootBosio WARNING : BOS names have a maximum of 4 characters  "<<name<<endl;
    strncpy(gTmpname,name,4);
  }
  else if (length<=4) {
    strncpy(gTmpname,name,length);
    for(Int_t i=length;i<4;i++) gTmpname[i]=' ';
  }
  gTmpname[4]=0;
  return(gTmpname);
}

//------------------------------------------------------------------------------
void TGsim::PrintHead(){
//
// Print out the most relevant part of the HEAD BOS bank.
//
  clasHEAD_t *head=(clasHEAD_t *)GetBank("HEAD",0);
  cout << "Version " << head->head[0].version << endl;
  cout << "Nrun    " << head->head[0].nrun << endl;
  cout << "Nevent  " << head->head[0].nevent << endl;
  cout << "Time    " << head->head[0].time << endl;
  cout << "Type    " << head->head[0].type << endl;
}

//------------------------------------------------------------------------------
void TGsim::PrintPart(Int_t nr,Int_t nrow){
//
// Print out the PART bank requested, or all part banks.
//
  clasPART_t *pp=(clasPART_t *)GetBank("PART",nr);

  if(nrow== -1){
    for(Int_t i=0;i<pp->bank.nrow;i++){
      cout << "Particle No: " << i << endl;
      PrintPart(nr,i);
    }
  }else{
    if(nrow>pp->bank.nrow-1){
      cerr << "TGsim::PrintPart ERROR, index out of bounds. \n";
      return;
    }
    cout << "PID      " << pp->part[nrow].pid << "(" << PDG_to_Geant(pp->part[nrow].pid) <<")"<< endl;
    cout << "Vertex:  (" << pp->part[nrow].vert.x << "," <<
      pp->part[nrow].vert.y << ","  << pp->part[nrow].vert.z << ")\n" ;
    cout << "Momentum:[" << pp->part[nrow].p.t << "::" <<
      pp->part[nrow].p.space.x << ","  << pp->part[nrow].p.space.y << ","  << pp->part[nrow].p.space.z << "]\n";
    cout << "Charge   " << pp->part[nrow].q << endl;
    cout << "Trkid    " << pp->part[nrow].trkid << endl;
    cout << "qpid     " << pp->part[nrow].qpid << endl;
    cout << "qtrk     " << pp->part[nrow].qtrk << endl;
    cout << "flags    " << pp->part[nrow].flags << endl;
  }
}

//------------------------------------------------------------------------------
Int_t TGsim::Geant_to_PDG(Int_t pid){
// Convert a GEANT MC particle ID to the Particle Data Group PID.
// This is needed since GSIM and PART banks store id in GEANT
// format, while EVNT stores it in PDG.
//  
  if(pid<0)return(0);
  
  if(pid<kG_NParticleTypes)return(fgGeant_Particle_Id[pid]);
  else      return(0);
}

//------------------------------------------------------------------------------
Int_t TGsim::PDG_to_Geant(Int_t pid){
// Convert a PDGT MC particle ID to the GEANT PID.
// This is needed since GSIM and PART banks store id in GEANT
// format, while EVNT stores it in PDG.
//  

  if(pid>= 1000000) return(pid%1000000);
  
  for(Int_t i=0;i<kG_NParticleTypes;i++){
    if(pid == fgGeant_Particle_Id[i])return(i);
  }

// No translation found.
  return(0);
}


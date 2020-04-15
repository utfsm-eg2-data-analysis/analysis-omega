// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>
//____________________ 
//   TMiniDSTWriter class provides tools for generating
//  Mini DSTs.
//
//
//  Author : G.Gavalian (UNH)
//  Date   : 04/12/2002
//
//=========================================================

#include "TMiniDSTWriter.h"

ClassImp(TMiniDSTWriter)


//=================================================================================
TMiniDSTWriter::TMiniDSTWriter()
{
  nPARTStore   = 0;
  fCompression = 1;
  fEventHeader = NULL;
  fcaPARTStore = NULL;
  fcaGSIMStore = NULL;
  fbElectron   = NULL;
  fbProton     = NULL;
 
}
//=================================================================================
TMiniDSTWriter::~TMiniDSTWriter()
{

}
//=================================================================================
void   TMiniDSTWriter::SetCompression(Int_t level)
{
  fCompression = level;
}
//=================================================================================
Int_t  TMiniDSTWriter::OpenFile(const char *filename, const char *title)
{
  fDSTFile = new TFile(filename,"RECREATE",title,fCompression);
  if(fDSTFile==NULL || !fDSTFile->IsOpen()){
    cout << "TMiniDSTWriter: ERROR failed to open file " << filename << endl;
    return -1;
  }

  fEventTree = new TTree("MINI_EVNT","CLAS MiniDST Event Tree");
  fEventTree->SetAutoSave(1024*1024*512);

  Init_Clones();
  Init_Branches();

  return 1;
}
//=================================================================================
void   TMiniDSTWriter::WriteEvent()
{
  fEventTree->Fill();
}
//=================================================================================
void   TMiniDSTWriter::ClearEvent()
{
  ClearClones();
}
//=================================================================================
void   TMiniDSTWriter::CloseFile()
{
  fDSTFile->Write();
  fDSTFile->Close();
}
//=================================================================================
void   TMiniDSTWriter::Init_Clones()
{

  nPARTStore = 0;
  nGSIMStore = 0;

  if(!fEventHeader){
    cout << "TMiniDSTClass :  Initializing Header class.." << endl;
    fEventHeader = new TMiniHEADClass();
  } else {
    cout << "TMiniDSTClass : WARNING Event header storage is already initialized" << endl;
  }

//   if(!fbElectron){
//     cout << "TMiniDSTClass :  Initializing Electron class.." << endl;
//     fbElectron = new TMiniDSTClass();
//   }  

//   if(!fbProton){
//     cout << "TMiniDSTClass :  Initializing Proton class.." << endl;
//     fbProton = new TMiniDSTClass();
//   }  

  if(!fcaPARTStore){
    cout << "TMiniDSTClass :  Initializing clone array.." << endl;
    fcaPARTStore  = new TClonesArray("TMiniDSTClass",4);
  }
  if(!fcaGSIMStore){
    cout << "TMiniDSTClass :  Initializing clone array.." << endl;
    fcaGSIMStore  = new TClonesArray("TGSIMClass",4);
  }

  
}
//=================================================================================

void   TMiniDSTWriter::ClearClones(){
  if(fcaPARTStore) fcaPARTStore->Clear();
  if(fcaGSIMStore) fcaGSIMStore->Clear();
  nPARTStore = 0;
  nGSIMStore = 0;
}

//=================================================================================
void   TMiniDSTWriter::Init_Branches()
{

  Int_t  buffsize = __BUFFSIZE__;
  Int_t  split    = 1;

   brHeader = fEventTree->Branch("HEADER","TMiniHEADClass",&fEventHeader,buffsize,split);
   fEventTree->SetBranchStatus("HEADER",1);
   //   brElectron = fEventTree->Branch("ELECTRON","TMiniDSTClass",&fbElectron,buffsize,split);
   //   fEventTree->SetBranchStatus("ELECTRON",1);
   //   brProton   = fEventTree->Branch("PROTON","TMiniDSTClass",&fbProton,buffsize,split);
   //   fEventTree->SetBranchStatus("PROTON",1);
   brPART     = fEventTree->Branch("EVNT",&fcaPARTStore,buffsize,split);
   brGSIM     = fEventTree->Branch("GSIM",&fcaGSIMStore,buffsize,split);
   //   fEventTree->SetBranchStatus("NTPART",1);
  fEventTree->SetBranchStatus("*",1);
}
//=================================================================================
void   TMiniDSTWriter::SetHeader(TMiniHEADClass *tc_header)
{
  fEventHeader->NRun   = tc_header->NRun;
  fEventHeader->NEvent = tc_header->NEvent;
  fEventHeader->Beam_E = tc_header->Beam_E;
  fEventHeader->Beam_EID = tc_header->Beam_EID;
  fEventHeader->Beam_DT = tc_header->Beam_DT;
  fEventHeader->FC = tc_header->FC;
  fEventHeader->FCG = tc_header->FCG;
  fEventHeader->Helicity = tc_header->Helicity;
}
//=================================================================================
void   TMiniDSTWriter::SetElectron(TMiniDSTClass *tc_elec)
{
  fbElectron->CopyFrom(tc_elec);
}
//=================================================================================
void   TMiniDSTWriter::SetProton(TMiniDSTClass *tc_prot)
{
  fbProton->CopyFrom(tc_prot);
}
//=================================================================================
void   TMiniDSTWriter::AddParticle(TMiniDSTClass *tc_part)
{
  TClonesArray &tPARTbank = *fcaPARTStore;
  new(tPARTbank[nPARTStore++]) TMiniDSTClass(tc_part);
}
//=========================================================
void   TMiniDSTWriter::AddGSIMParticle(TGSIMClass *tc_part)
{
  TClonesArray &tGSIMbank = *fcaGSIMStore;
  new(tGSIMbank[nGSIMStore++]) TGSIMClass(tc_part);
}

//=========================================================
void   TMiniDSTWriter::Print()
{
  cout << "TMiniDSTWriter::Print >>>>>>>>>" << endl;
  fEventHeader->Print();
  fbElectron->Print();
  fbProton->Print();
  cout << "Other === " << fcaPARTStore->GetEntries() << endl;
  for(int j=0;j<fcaPARTStore->GetEntries();j++)
    {
      TMiniDSTClass *bank = (TMiniDSTClass *)  fcaPARTStore->At(j);
      bank->Print();
    }
  cout << "TMiniDSTWriter:: <<<<<<<<<<<<<<<<< end of print" << endl;
}


void   TMiniDSTWriter::PrintStat()
{
  cout << fEventHeader->NRun << ":" <<  fEventHeader->NEvent << ":" 
       << fEventHeader->FCG  << " :  NEUT >>> " << fcaPARTStore->GetEntries() << endl;
}


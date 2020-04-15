//=========================================================
//
//
//  Author : G.Gavalian (ODU)
//  Date   : 01/07/2008
//
//=========================================================

#include "TDSTWriter.h"

ClassImp(TDSTWriter)


//=================================================================================
TDSTWriter::TDSTWriter()
{
  nPARTStore   = 0;
  fCompression = 1;
  //  fEventHeader = NULL;
  //  fcaPARTStore = NULL;
  //  fbElectron   = NULL;
  //  fbProton     = NULL;
  hHEADER = new THEADERClass();
}
//=================================================================================
TDSTWriter::~TDSTWriter()
{

}
//=================================================================================
void   TDSTWriter::SetCompression(Int_t level)
{
  fCompression = level;
}
//=================================================================================
Int_t  TDSTWriter::OpenFile(const char *filename, const char *title)
{
  fDSTFile = new TFile(filename,"RECREATE",title,fCompression);
  if(fDSTFile==NULL || !fDSTFile->IsOpen()){
    cout << "TDSTWriter: ERROR failed to open file " << filename << endl;
    return -1;
  }

  fEventTree = new TTree("CLASEVENT","CLAS MiniDST Event Tree");
  fEventTree->SetAutoSave(1024*1024*512);

  Init_Clones();
  Init_Branches();
  ClearClones();
  return 1;
}
//=================================================================================
void   TDSTWriter::WriteEvent()
{
  fEventTree->Fill();
  ClearEvent();
}
//=================================================================================
void   TDSTWriter::ClearEvent()
{
  ClearClones();
}
//=================================================================================
void   TDSTWriter::CloseFile()
{
  fDSTFile->Write();
  fDSTFile->Close();
}
//=================================================================================
void   TDSTWriter::AddBankName(const char *_bnkname)
{
  TString  fClassName;
  fClassName = "T";
  fClassName += _bnkname;
  fClassName += "Class";
  fClones.Add(new TStoreClone(_bnkname,fClassName.Data(),10));
}
//=================================================================================
void   TDSTWriter::AddBankList(const char *_bnkname)
{
  TString  fTmpBuff  = _bnkname;
  TString  fBankName = _bnkname;
  while(fTmpBuff.Length()>=4)
    {
      fBankName.Remove(4,fBankName.Length()-4);
      fTmpBuff.Remove(0,4);
      cout << "Next Bank : [" << fBankName.Data() << "]" << endl;
      AddBankName(fBankName.Data());
      fBankName = fTmpBuff.Data();
    }
}
//=================================================================================
void   TDSTWriter::ShowBanks()
{
  TIter next(&fClones);
  TStoreClone *this_clone;
  while( (this_clone=(TStoreClone *)next() ) ){
    TClonesArray *ptr = *(this_clone->GetClonesArray());
    cout << this_clone->GetCloneName() << "    |       " << ptr->GetEntries() << endl;
  }
}
//=================================================================================
void   TDSTWriter::Init_Clones()
{

//  if(!EVNTStore&&BankStatus("EVNT")>0) EVNTStore = new TClonesArray("TEVNTClass",1);
//  if(!GSIMStore&&BankStatus("GSIM")>0) GSIMStore = new TClonesArray("TGSIMClass",1);
//  if(!ECPBStore&&BankStatus("ECPB")>0) ECPBStore = new TClonesArray("TECPBClass",1);
//  if(!SCPBStore&&BankStatus("SCPB")>0) SCPBStore = new TClonesArray("TSCPBClass",1);
//  if(!DCPBStore&&BankStatus("DCPB")>0) DCPBStore = new TClonesArray("TDCPBClass",1);
//  if(!CCPBStore&&BankStatus("CCPB")>0) CCPBStore = new TClonesArray("TCCPBClass",1);
//  if(!LCPBStore&&BankStatus("LCPB")>0) LCPBStore = new TClonesArray("TLCPBClass",1);
//  if(!TGPBStore&&BankStatus("TGPB")>0) TGPBStore = new TClonesArray("TTGPBClass",1);
//  if(!TAGRStore&&BankStatus("TAGR")>0) TAGRStore = new TClonesArray("TTAGRClass",1);
//  if(!TGBIStore&&BankStatus("TGBI")>0) TGBIStore = new TClonesArray("TTGBIClass",1);
//  if(!VERTStore&&BankStatus("VERT")>0) VERTStore = new TClonesArray("TVERTClass",1);

  if(BankStatus("EVNT")>0) EVNTStore = new TClonesArray("TEVNTClass",1);
  if(BankStatus("GSIM")>0) GSIMStore = new TClonesArray("TGSIMClass",1);
  if(BankStatus("ECPB")>0) ECPBStore = new TClonesArray("TECPBClass",1);
  if(BankStatus("SCPB")>0) SCPBStore = new TClonesArray("TSCPBClass",1);
  if(BankStatus("DCPB")>0) DCPBStore = new TClonesArray("TDCPBClass",1);
  if(BankStatus("CCPB")>0) CCPBStore = new TClonesArray("TCCPBClass",1);
  if(BankStatus("LCPB")>0) LCPBStore = new TClonesArray("TLCPBClass",1);
  if(BankStatus("TGPB")>0) TGPBStore = new TClonesArray("TTGPBClass",1);
  if(BankStatus("TAGR")>0) TAGRStore = new TClonesArray("TTAGRClass",1);
  if(BankStatus("TGBI")>0) TGBIStore = new TClonesArray("TTGBIClass",1);
  if(BankStatus("VERT")>0) VERTStore = new TClonesArray("TVERTClass",1);
  if(BankStatus("ICPB")>0) ICPBStore = new TClonesArray("TICPBClass",1);
  if(BankStatus("ICHB")>0) ICHBStore = new TClonesArray("TICHBClass",1);
  if(BankStatus("FBPM")>0) FBPMStore = new TClonesArray("TFBPMClass",1);

  //  nPARTStore = 0;
  //   if(!fEventHeader){
  //     cout << "TMiniDSTClass :  Initializing Header class.." << endl;
  //     fEventHeader = new TMiniHEADClass();
  //   } else {
  //     cout << "TMiniDSTClass : WARNING Event header storage is already initialized" << endl;
  //   }
  //   if(!fcaPARTStore){
  //     cout << "TMiniDSTClass :  Initializing clone array.." << endl;
  //     fcaPARTStore  = new TClonesArray("TMiniDSTClass",4);
  //   }
  
}
//=================================================================================

void   TDSTWriter::ClearClones(){
//  if(fcaPARTStore) fcaPARTStore->Clear();
//   nPARTStore = 0;
   if(BankStatus("EVNT")>0) if(EVNTStore) EVNTStore->Clear();
   if(BankStatus("ECPB")>0) if(ECPBStore) ECPBStore->Clear();
   if(BankStatus("SCPB")>0) if(SCPBStore) SCPBStore->Clear();
   if(BankStatus("DCPB")>0) if(DCPBStore) DCPBStore->Clear();
   if(BankStatus("CCPB")>0) if(CCPBStore) CCPBStore->Clear();
   if(BankStatus("ICPB")>0) if(ICPBStore) ICPBStore->Clear();
   if(BankStatus("ICHB")>0) if(ICHBStore) ICHBStore->Clear();
   if(BankStatus("FBPM")>0) if(FBPMStore) FBPMStore->Clear();
   if(BankStatus("LCPB")>0) if(LCPBStore) LCPBStore->Clear();
   if(BankStatus("STPB")>0) if(STPBStore) STPBStore->Clear();
   if(BankStatus("TGPB")>0) if(TGPBStore) TGPBStore->Clear();
   if(BankStatus("TAGR")>0) if(TAGRStore) TAGRStore->Clear();
   if(BankStatus("VERT")>0) if(VERTStore) VERTStore->Clear();
   if(BankStatus("VERT")>0) if(VERTStore) VERTStore->Clear(); 
   if(BankStatus("TGBI")>0) if(TGBIStore) TGBIStore->Clear();
   if(BankStatus("GSIM")>0) if(GSIMStore) GSIMStore->Clear();
  nEVNT_Store = 0;
  nECPB_Store = 0;
  nSCPB_Store = 0;
  nDCPB_Store = 0;
  nCCPB_Store = 0;
  nICPB_Store = 0;
  nICHB_Store = 0;
  nFBPM_Store = 0;
  nLCPB_Store = 0;
  nSTPB_Store = 0;
  nTGPB_Store = 0;
  nVERT_Store = 0;
  nTAGR_Store = 0;
  nTGBI_Store = 0;
  nGSIM_Store = 0;

}

void   TDSTWriter::SetHeader(THEADERClass  *_fHeader)
{
  *hHEADER = (*_fHeader); 
}
//=================================================================================
void   TDSTWriter::Init_Branches()
{
  Int_t  bufsize = __BUFFSIZE__;
  Int_t  split    = 1;

  HEADERBranch = fEventTree->Branch("HEADER","THEADERClass",&hHEADER,bufsize,split);
  fEventTree->SetBranchStatus("HEADER",1);

//  return;

  if(BankStatus("EVNT")>0) EVNTBranch = fEventTree->Branch("EVNT",&EVNTStore,bufsize,split);
  if(BankStatus("ECPB")>0) ECPBBranch = fEventTree->Branch("ECPB",&ECPBStore,bufsize,split);
  if(BankStatus("SCPB")>0) SCPBBranch = fEventTree->Branch("SCPB",&SCPBStore,bufsize,split);
  if(BankStatus("DCPB")>0) DCPBBranch = fEventTree->Branch("DCPB",&DCPBStore,bufsize,split);
  if(BankStatus("CCPB")>0) CCPBBranch = fEventTree->Branch("CCPB",&CCPBStore,bufsize,split);
  if(BankStatus("LCPB")>0) LCPBBranch = fEventTree->Branch("LCPB",&LCPBStore,bufsize,split);
  if(BankStatus("TGPB")>0) TGPBBranch = fEventTree->Branch("TGPB",&TGPBStore,bufsize,split);
  if(BankStatus("TAGR")>0) TAGRBranch = fEventTree->Branch("TAGR",&TAGRStore,bufsize,split);
  if(BankStatus("TGBI")>0) TGBIBranch = fEventTree->Branch("TGBI",&TGBIStore,bufsize,split);
  if(BankStatus("VERT")>0) VERTBranch = fEventTree->Branch("VERT",&VERTStore,bufsize,split);
  if(BankStatus("GSIM")>0) GSIMBranch = fEventTree->Branch("GSIM",&GSIMStore,bufsize,split);
  if(BankStatus("ICPB")>0) ICPBBranch = fEventTree->Branch("ICPB",&ICPBStore,bufsize,split); 
  if(BankStatus("ICHB")>0) ICHBBranch = fEventTree->Branch("ICHB",&ICHBStore,bufsize,split); 
  if(BankStatus("FBPM")>0) FBPMBranch = fEventTree->Branch("FBPM",&FBPMStore,bufsize,split); 

}
//=================================================================================
void   TDSTWriter::CopyBanks(TVirtualReader *fReader)
{
  TDSTReader *_fR = static_cast<TDSTReader*> (fReader);
  THEADERClass *_p_HEAD = _fR->GetHEADER();
  SetHeader(_p_HEAD);

  //
  // ----- Fill EVNT Buffer from the Reader --------
  //
  if(BankStatus("EVNT")>0){
    int  n_EVNT_rows = fReader->GetNRows("EVNT");
    for(int i=0;i<n_EVNT_rows;i++){
      TObject *_ptr = fReader->GetBankRow("EVNT",i);
      AddBank("EVNT",_ptr);
    }
  }

  //
  // ----- Fill ECPB Buffer from the Reader --------
  //
  if(BankStatus("ECPB")>0){
    int  n_SCPB_rows = fReader->GetNRows("ECPB");
    for(int i=0;i<n_SCPB_rows;i++){
      TObject *_ptr = fReader->GetBankRow("ECPB",i);
      AddBank("ECPB",_ptr);
    }
  }
  //
  // ----- Fill SCPB Buffer from the Reader --------
  //
  if(BankStatus("SCPB")>0){
    int  n_SCPB_rows = fReader->GetNRows("SCPB");
    for(int i=0;i<n_SCPB_rows;i++){
      TObject *_ptr = fReader->GetBankRow("SCPB",i);
      AddBank("SCPB",_ptr);
    }
  }


  //
  // ----- Fill DCPB Buffer from the Reader --------
  //
  if(BankStatus("DCPB")>0){
    int  n_DCPB_rows = fReader->GetNRows("DCPB");
    for(int i=0;i<n_DCPB_rows;i++){
      TObject *_ptr = fReader->GetBankRow("DCPB",i);
      AddBank("DCPB",_ptr);
    }
  }


  //
  // ----- Fill CCPB Buffer from the Reader --------
  //
  if(BankStatus("CCPB")>0){
    int  n_CCPB_rows = fReader->GetNRows("CCPB");
    for(int i=0;i<n_CCPB_rows;i++){
      TObject *_ptr = fReader->GetBankRow("CCPB",i);
      AddBank("CCPB",_ptr);
    }
  }


  //
  // ----- Fill LCPB Buffer from the Reader --------
  //
  if(BankStatus("LCPB")>0){
    int  n_LCPB_rows = fReader->GetNRows("LCPB");
    for(int i=0;i<n_LCPB_rows;i++){
      TObject *_ptr = fReader->GetBankRow("LCPB",i);
      AddBank("LCPB",_ptr);
    }
  }


  //
  // ----- Fill TGPB Buffer from the Reader --------
  //
  if(BankStatus("TGPB")>0){
    int  n_TGPB_rows = fReader->GetNRows("TGPB");
    for(int i=0;i<n_TGPB_rows;i++){
      TObject *_ptr = fReader->GetBankRow("TGPB",i);
      AddBank("TGPB",_ptr);
    }
  }


  //
  // ----- Fill TGBI Buffer from the Reader --------
  //
  if(BankStatus("TGBI")>0){
    int  n_TGBI_rows = fReader->GetNRows("TGBI");
    for(int i=0;i<n_TGBI_rows;i++){
      TObject *_ptr = fReader->GetBankRow("TGBI",i);
      AddBank("TGBI",_ptr);
    }
  }


  //
  // ----- Fill TAGR Buffer from the Reader --------
  //
  if(BankStatus("TAGR")>0){
    int  n_TAGR_rows = fReader->GetNRows("TAGR");
    for(int i=0;i<n_TAGR_rows;i++){
      TObject *_ptr = fReader->GetBankRow("TAGR",i);
      AddBank("TAGR",_ptr);
    }
  }


  //
  // ----- Fill VERT Buffer from the Reader --------
  //
  if(BankStatus("VERT")>0){
    int  n_VERT_rows = fReader->GetNRows("VERT");
    for(int i=0;i<n_VERT_rows;i++){
      TObject *_ptr = fReader->GetBankRow("VERT",i);
      AddBank("VERT",_ptr);
    }
  }


  //
  // ----- Fill GSIM Buffer from the Reader --------
  //
  if(BankStatus("GSIM")>0){
    int  n_GSIM_rows = fReader->GetNRows("GSIM");
    for(int i=0;i<n_GSIM_rows;i++){
      TObject *_ptr = fReader->GetBankRow("GSIM",i);
      AddBank("GSIM",_ptr);
    }
  }


}
//=================================================================================
void   TDSTWriter::AddBank(const char *_bnkname,TObject *_bnkptr)
{

  TString  fBnkName = _bnkname;

  if(fBnkName.CompareTo("EVNT")==0){
//	printf("Adding EVNT Bank  %d\n",nEVNT_Store);
    TEVNTClass  *EVNT_p = static_cast<TEVNTClass*> (_bnkptr);
    TClonesArray &tEVNTbank = *EVNTStore;
    new(tEVNTbank[nEVNT_Store++]) TEVNTClass(EVNT_p);
//	printf("done....\n");
  }

  if(fBnkName.CompareTo("ECPB")==0){
//	printf("Adding SCPB Bank\n");
    TECPBClass  *ECPB_p = static_cast<TECPBClass*> (_bnkptr);
    TClonesArray &tECPBbank = *ECPBStore;
    new(tECPBbank[nECPB_Store++]) TECPBClass(ECPB_p);
  }
 if(fBnkName.CompareTo("SCPB")==0){
//	printf("Adding SCPB Bank\n");
    TSCPBClass  *SCPB_p = static_cast<TSCPBClass*> (_bnkptr);
    TClonesArray &tSCPBbank = *SCPBStore;
    new(tSCPBbank[nSCPB_Store++]) TSCPBClass(SCPB_p);
  }


  if(fBnkName.CompareTo("DCPB")==0){
    //	printf("Adding DCPB Bank\n");
    TDCPBClass  *DCPB_p = static_cast<TDCPBClass*> (_bnkptr);
    TClonesArray &tDCPBbank = *DCPBStore;
    new(tDCPBbank[nDCPB_Store++]) TDCPBClass(DCPB_p);
  }


  if(fBnkName.CompareTo("CCPB")==0){
    TCCPBClass  *CCPB_p = static_cast<TCCPBClass*> (_bnkptr);
    TClonesArray &tCCPBbank = *CCPBStore;
    new(tCCPBbank[nCCPB_Store++]) TCCPBClass(CCPB_p);
  }

  if(fBnkName.CompareTo("ICPB")==0){
    TICPBClass  *ICPB_p = static_cast<TICPBClass*> (_bnkptr);
    TClonesArray &tICPBbank = *ICPBStore;
    new(tICPBbank[nICPB_Store++]) TICPBClass(ICPB_p);
  }

  if(fBnkName.CompareTo("ICHB")==0){
    TICHBClass  *ICHB_p = static_cast<TICHBClass*> (_bnkptr);
    TClonesArray &tICHBbank = *ICHBStore;
    new(tICHBbank[nICHB_Store++]) TICHBClass(ICHB_p);
  }

  if(fBnkName.CompareTo("FBPM")==0){
    TFBPMClass  *FBPM_p = static_cast<TFBPMClass*> (_bnkptr);
    TClonesArray &tFBPMbank = *FBPMStore;
    new(tFBPMbank[nFBPM_Store++]) TFBPMClass(FBPM_p);
  }


  if(fBnkName.CompareTo("LCPB")==0){
    TLCPBClass  *LCPB_p = static_cast<TLCPBClass*> (_bnkptr);
    TClonesArray &tLCPBbank = *LCPBStore;
    new(tLCPBbank[nLCPB_Store++]) TLCPBClass(LCPB_p);
  }


  if(fBnkName.CompareTo("TGPB")==0){
    TTGPBClass  *TGPB_p = static_cast<TTGPBClass*> (_bnkptr);
    TClonesArray &tTGPBbank = *TGPBStore;
    new(tTGPBbank[nTGPB_Store++]) TTGPBClass(TGPB_p);
  }


  if(fBnkName.CompareTo("TGBI")==0){
    TTGBIClass  *TGBI_p = static_cast<TTGBIClass*> (_bnkptr);
    TClonesArray &tTGBIbank = *TGBIStore;
    new(tTGBIbank[nTGBI_Store++]) TTGBIClass(TGBI_p);
  }


  if(fBnkName.CompareTo("TAGR")==0){
    TTAGRClass  *TAGR_p = static_cast<TTAGRClass*> (_bnkptr);
    TClonesArray &tTAGRbank = *TAGRStore;
    new(tTAGRbank[nTAGR_Store++]) TTAGRClass(TAGR_p);
  }


  if(fBnkName.CompareTo("VERT")==0){
    TVERTClass  *VERT_p = static_cast<TVERTClass*> (_bnkptr);
    TClonesArray &tVERTbank = *VERTStore;
    new(tVERTbank[nVERT_Store++]) TVERTClass(VERT_p);
  }


  if(fBnkName.CompareTo("GSIM")==0){
    TGSIMClass  *GSIM_p = static_cast<TGSIMClass*> (_bnkptr);
    TClonesArray &tGSIMbank = *GSIMStore;
    new(tGSIMbank[nGSIM_Store++]) TGSIMClass(GSIM_p);
  }


}

//=================================================================================
Int_t  TDSTWriter::BankStatus(const char *_bnk_name)
{
  TObject *ptr = fClones.FindObject(_bnk_name);
  if(ptr==NULL) return -1;
  return 1;
}
//=================================================================================

void   TDSTWriter::Print()
{
//   cout << "TDSTWriter::Print >>>>>>>>>" << endl;
//   fEventHeader->Print();
//   fbElectron->Print();
//   fbProton->Print();
//   cout << "Other === " << fcaPARTStore->GetEntries() << endl;
//   for(int j=0;j<fcaPARTStore->GetEntries();j++)
//     {
//       TMiniDSTClass *bank = (TMiniDSTClass *)  fcaPARTStore->At(j);
//       bank->Print();
//     }
//   cout << "TDSTWriter:: <<<<<<<<<<<<<<<<< end of print" << endl;
}


void   TDSTWriter::PrintStat()
{
//   cout << fEventHeader->NRun << ":" <<  fEventHeader->NEvent << ":" 
//        << fEventHeader->FCG  << " :  NEUT >>> " << fcaPARTStore->GetEntries() << endl;
}


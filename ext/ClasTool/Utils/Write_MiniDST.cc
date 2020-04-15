#include <iostream>
#include <string>

using namespace std;

#include "THEADERClass.h"
#include "TVirtualData.h"
#include "TEVNTClass.h"
#include "TECPBClass.h"
#include "TSCPBClass.h"
#include "TDCPBClass.h"
#include "TCCPBClass.h"
#include "TICPBClass.h"
#include "TICHBClass.h"
#include "TFBPMClass.h"
#include "TLCPBClass.h"
#include "THEADClass.h"
#include "TGSIMClass.h"
#include "THLSClass.h"
#include "TS1STClass.h"
#include "TTRGSClass.h"
#include "TTGBIClass.h"
#include "TSTPBClass.h"
#include "TTGPBClass.h"
#include "TTAGRClass.h"
#include "TVERTClass.h"
#include "TMVRTClass.h"
#include "TTBERClass.h"
#include "TMCHDClass.h"

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
#include "FillBank.h"
#include "TDSTWriter.h"

char    fRootFileName[256];
char    fBosFileName[256];
string  fOutputFileName;
string  bosFileName;
int     nEventsToWrite;

THEADERClass  hHEADER;
TEVNTClass    hEVNT;
TECPBClass    hECPB;
TDCPBClass    hDCPB;
TSCPBClass    hSCPB;
TCCPBClass    hCCPB;
TICPBClass    hICPB;
TICHBClass    hICHB;
TFBPMClass    hFBPM;
TTGBIClass    hTGBI;
TTGPBClass    hTGPB;
TTAGRClass    hTAGR;


int main(int argc, char **argv){

  int         bosFileHandle;
  int         iCount;
  int         EventType;

  nEventsToWrite = 2000000;

  sprintf(fRootFileName,"%s",argv[1]);
  sprintf(fBosFileName, "%s",argv[2]);

  TDSTWriter  fWriter;

  fWriter.AddBankName("EVNT");
  fWriter.AddBankName("TAGR");
  fWriter.AddBankName("ECPB");
  fWriter.AddBankName("DCPB");
  fWriter.AddBankName("SCPB");
  fWriter.AddBankName("CCPB");
  fWriter.AddBankName("ICPB");
  fWriter.AddBankName("ICHB");
  fWriter.AddBankName("FBPM");
  fWriter.AddBankName("TGBI");
  fWriter.AddBankName("TGPB");
  fWriter.AddBankName("TAGR");
  
  fWriter.OpenFile(fRootFileName);

  bosInit(bcs_.iw,NBCS);

  int iostatus = bosOpen(fBosFileName,"r",&bosFileHandle);
  if(iostatus){
    cout << "File " << fBosFileName << " could not be opened. ";
    return 1;
  }

  iCount = 0;
  while( (bosRead(bosFileHandle,bcs_.iw,"E")==0) && (iCount<nEventsToWrite)){

    iCount++;

    if(iCount%5000==0) printf("events processed %d\n",iCount);
    fWriter.ClearEvent();

    HEAD kfileHEADER(0);
    
    Fill_HEADER_Bank(&hHEADER);
    fWriter.SetHeader(&hHEADER);

    //--------------  Writing EVNT bank --------------------
    EVNT    kEVNT(0);
    if(kEVNT.get_nrows() > 0){
      for(int j = 0; j < kEVNT.get_nrows(); j++){
    	Fill_EVNT_Bank(&hEVNT,&kEVNT,j);
	//	printf("adding bank %d\n",j);
    	fWriter.AddBank("EVNT",(TObject *) &hEVNT);
      }
    }
    //--------------  Writing ECPB bank --------------------
    ECPB    kECPB(0);
    if(kECPB.get_nrows() > 0){
      for(int j = 0; j < kECPB.get_nrows(); j++){
	Fill_ECPB_Bank(&hECPB,&kECPB,j);
	fWriter.AddBank("ECPB",(TObject *) &hECPB);
      }
    }
    //--------------  Writing DCPB bank --------------------
    DCPB    kDCPB(0);
    if(kDCPB.get_nrows() > 0){
      for(int j = 0; j < kDCPB.get_nrows(); j++){
	Fill_DCPB_Bank(&hDCPB,&kDCPB,j);
	fWriter.AddBank("DCPB",(TObject *) &hDCPB);
      }
    }
    //--------------  Writing SCPB bank --------------------
    SCPB    kSCPB(0);
    if(kSCPB.get_nrows() > 0){
      for(int j = 0; j < kSCPB.get_nrows(); j++){
	Fill_SCPB_Bank(&hSCPB,&kSCPB,j);
	fWriter.AddBank("SCPB",(TObject *) &hSCPB);
      }
    }
    //--------------  Writing CCPB bank --------------------
    CCPB    kCCPB(0);
    if(kCCPB.get_nrows() > 0){
      for(int j = 0; j < kCCPB.get_nrows(); j++){
	Fill_CCPB_Bank(&hCCPB,&kCCPB,j);
	fWriter.AddBank("CCPB",(TObject *) &hCCPB);
      }
    }
    //--------------  Writing ICPB bank --------------------
    ICPB    kICPB(0);
    if(kICPB.get_nrows() > 0){
      for(int j = 0; j < kICPB.get_nrows(); j++){
	Fill_ICPB_Bank(&hICPB,&kICPB,j);
	fWriter.AddBank("ICPB",(TObject *) &hICPB);
      }
    }

    //--------------  Writing ICPB bank --------------------                                             
    ICHB    kICHB(0);
    if(kICHB.get_nrows() > 0){
      for(int j = 0; j < kICHB.get_nrows(); j++){
        Fill_ICHB_Bank(&hICHB,&kICHB,j);
	fWriter.AddBank("ICHB",(TObject *) &hICHB);
      }
    }
    //--------------  Writing ICPB bank --------------------     
    FBPM    kFBPM(0);
    if(kFBPM.get_nrows() > 0){
      for(int j = 0; j < kFBPM.get_nrows(); j++){
        Fill_FBPM_Bank(&hFBPM,&kFBPM,j);
        fWriter.AddBank("FBPM",(TObject *) &hFBPM);
      }
    }


    //--------------  Writing TGBI bank --------------------
    TGBI    kTGBI(0);
    if(kTGBI.get_nrows() > 0){
      for(int j = 0; j < kTGBI.get_nrows(); j++){
        Fill_TGBI_Bank(&hTGBI,&kTGBI,j);
        fWriter.AddBank("TGBI",(TObject *) &hTGBI);
      }
    }
    //--------------  Writing TGPB bank --------------------
    TGPB    kTGPB(0);
    if(kTGPB.get_nrows() > 0){
      for(int j = 0; j < kTGPB.get_nrows(); j++){
        Fill_TGPB_Bank(&hTGPB,&kTGPB,j);
        fWriter.AddBank("TGPB",(TObject *) &hTGPB);
      }
    }
    //--------------  Writing TAGR bank --------------------
    TAGR    kTAGR(0);
    if(kTAGR.get_nrows() > 0){
      for(int j = 0; j < kTAGR.get_nrows(); j++){
        Fill_TAGR_Bank(&hTAGR,&kTAGR,j);
        fWriter.AddBank("TAGR",(TObject *) &hTAGR);
      }
    }



    fWriter.WriteEvent();
    bosLdrop(bcs_.iw,"E");
    bosNgarbage(bcs_.iw);
 
  }
  
  bosClose(bosFileHandle);
  fWriter.CloseFile();
  
  return 1;
}

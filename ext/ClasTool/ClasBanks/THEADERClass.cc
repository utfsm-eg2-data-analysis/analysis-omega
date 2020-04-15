// @(#)ClasTool/ClasBanks:$Name:  $:$Id: THEADERClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>THEADERClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
           Maurik (7/21/00) Updated to add words.
</pre>
This class is used to access the header information bank data written into 
the ROOT DST for data from the CLAS at Jefferson Lab.
Contends is taken from several banks (indicated in brackets) as descibed in 
packages/bankdefs. <p>
The details on how exactly each variable is defined have to be extraced
from the RECSIS code. <p>
This class now has a custom streamer to accomodate a modification where
the RF2 and Level 2 and 3 trigger information were added. This should 
still work transparently with data that was writter with an older version
of WriteRootDST, except that the entries for those variables will be
set to zero.
<pre> 
<!-- */ 
// --> End_Html   
//--------------------------------------------------------------------------

#include "THEADERClass.h"
//
//

ClassImp(THEADERClass)

THEADERClass::THEADERClass()
{

}

THEADERClass::THEADERClass(THEADERClass *TmpHEADER){
  NRun  = TmpHEADER->NRun;     /* From HEAD bank */
  NEvent  = TmpHEADER->NEvent;   /* From HEAD bank */
  Time  = TmpHEADER->Time;     /* From HEAD bank */
  Type  = TmpHEADER->Type;     /* From HEAD bank */
  ROC   = TmpHEADER->ROC;      /* From HEAD bank */
  EvtClas  = TmpHEADER->EvtClas;  /* From HEAD bank */
  TrigBits  = TmpHEADER->TrigBits; /* From HEAD bank */
  EStatus  = TmpHEADER->EStatus;  /* From HEVT Bank */
  TrgPrs  = TmpHEADER->TrgPrs;   /* From HEVT Bank */
  NPGP  = TmpHEADER->NPGP;     /* From HEVT Bank */
  FC   = TmpHEADER->FC;       /* From HEVT Bank */
  FCG  = TmpHEADER->FCG;	   /* From HEVT Bank */
  TG  = TmpHEADER->TG;       /* From HEVT Bank */
  STT  = TmpHEADER->STT;      /* From HEVT Bank */
  RF1  = TmpHEADER->RF1;      /* From HEVT Bank */
  RF2  = TmpHEADER->RF2;      /* From HEVT Bank */
  Latch1  = TmpHEADER->Latch1;   /* From TGBI Bank (helicity)*/
  Helicity_Scaler  = TmpHEADER->Helicity_Scaler; /* From TGBI Bank (helicity)*/
  Interrupt_Time  = TmpHEADER->Interrupt_Time;  /* From TGBI Bank (helicity)*/
  Level2 = TmpHEADER->Level2;
  Level3 = TmpHEADER->Level3;
}

void THEADERClass::Print(){
  cout << "NRun     	   " << NRun <<endl;
  cout << "NEvent   	   " << NEvent  << endl;
  cout << "Time     	   " << Time  << endl;
  cout << "Type     	   " << Type  << endl;
  cout << "ROC      	   " << ROC   << endl;
  cout << "EvtClas  	   " << EvtClas  << endl;
  cout << "TrigBits 	   " << TrigBits  << endl;
  cout << "EStatus  	   " << EStatus  << endl;
  cout << "TrgPrs   	   " << TrgPrs  << endl;
  cout << "NPGP     	   " << NPGP  << endl;
  cout << "FC       	   " << FC   << endl;
  cout << "FCG      	   " << FCG  << endl;
  cout << "TG       	   " << TG  << endl;
  cout << "STT      	   " << STT  << endl;
  cout << "RF1             " << RF1  << endl;
  cout << "RF2             " << RF2  << endl;
  cout << "Latch1          " << Latch1  << endl;
  cout << "Helicity_Scaler " << Helicity_Scaler  << endl;
  cout << "Interrupt_Time  " << Interrupt_Time  << endl;
  cout << "Level2          " << Level2 << endl;
  cout << "Level3          " << Level3 << endl;    
}

//
//
// Being smart here with a custom streamer allows us to read
// root files that were written with an older version of this banks
// definition.
//

void THEADERClass::Streamer(TBuffer &R__b)
{
   // Stream an object of class THEADERClass.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); 
      TObject::Streamer(R__b);
      R__b >> NRun;
      R__b >> NEvent;
      R__b >> Time;
      R__b >> Type;
      R__b >> ROC;
      R__b >> EvtClas;
      R__b >> TrigBits;
      R__b >> EStatus;
      R__b >> TrgPrs;
      R__b >> NPGP;
      R__b >> FC;
      R__b >> FCG;
      R__b >> TG;
      R__b >> STT;
      R__b >> RF1;
      if (R__v>=2){
	R__b >> RF2;
      }else{
	RF2=0;
      }
      R__b >> Latch1;
      R__b >> Helicity_Scaler;
      R__b >> Interrupt_Time;
      if (R__v>=2){
	R__b >> Level2;
	R__b >> Level3;
      }else{
	Level2=0;
	Level3=0;
      }
      R__b.CheckByteCount(R__s, R__c, THEADERClass::IsA());
   } else {
      R__c = R__b.WriteVersion(THEADERClass::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << NRun;
      R__b << NEvent;
      R__b << Time;
      R__b << Type;
      R__b << ROC;
      R__b << EvtClas;
      R__b << TrigBits;
      R__b << EStatus;
      R__b << TrgPrs;
      R__b << NPGP;
      R__b << FC;
      R__b << FCG;
      R__b << TG;
      R__b << STT;
      R__b << RF1;
      R__b << RF2;
      R__b << Latch1;
      R__b << Helicity_Scaler;
      R__b << Interrupt_Time;
      R__b << Level2;
      R__b << Level3;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

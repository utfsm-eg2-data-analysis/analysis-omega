// @(#)ClasTool/ClasBanks:$Name:  $:$Id: THLSClass.cc,v 1.4 2007/03/01 22:26:59 holtrop Exp $
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<h1>THLSClass</h1>
<pre>
 Modified:
           Maurik (2/3/00) Comments.
</pre>
This class is used to access the 
HLS (scaler)
bank data written into the ROOT DST.
It was generated automatically from the ddl file in 
packages/bankdefs/hls.ddl
and later hand edited to provide comments and additional modifications.
The details on how exactly each variable is defined have to be extraced
from the RECSIS code.
<pre> 
<!-- */ 
// --> End_Html   
////////////////////////////////////////////////////////

#include "THLSClass.h"

ClassImp(THLSClass)

THLSClass::THLSClass(THLSClass *TmpHLS){
TenMhz = TmpHLS->TenMhz;  // 10 Mhz Clock.
OTR1 = TmpHLS->OTR1;  // 
OTR2 = TmpHLS->OTR2;  // 
SLM   = TmpHLS->SLM  ;  // 
LVL1R  = TmpHLS->LVL1R ; // Level 1 trigger rate
LRC = TmpHLS->LRC;    // Left Right Miller Coincidences
LRA = TmpHLS->LRA;    // Left Right Accidentals
Fci = TmpHLS->Fci;   // Faraday Cup Current Amplitude
Pmt1 = TmpHLS->Pmt1;  // Luminosity monitor on beam pipe 1
Pmt2 = TmpHLS->Pmt2;  // Luminosity monitor on beam pipe 2
Pmt3 = TmpHLS->Pmt3;  // Luminosity monitor on beam pipe 3
Pmt4 = TmpHLS->Pmt4;  // Luminosity monitor on beam pipe 4
Res1 = TmpHLS->Res1;  // Reserved 1
Res2 = TmpHLS->Res2;  // Reserved 2
HelAcc = TmpHLS->HelAcc; // Helicity states accumulating counter.
HLSAcc = TmpHLS->HLSAcc; // HLS Banks accumulatiing counter.
}

void   THLSClass::Print(){
  cout << "TenMhz =" << TenMhz << endl;  // 10 Mhz Clock.
  cout << "OTR1   =" << OTR1 << endl;  // 
  cout << "OTR2   =" << OTR2 << endl;  // 
  cout << "SLM    =" << SLM   << endl;  // 
  cout << "LVL1R  =" << LVL1R  << endl; // Level 1 trigger rate
  cout << "LRC    =" << LRC << endl;    // Left Right Miller Coincidences
  cout << "LRA    =" << LRA << endl;    // Left Right Accidentals
  cout << "Fci    =" << Fci << endl;   // Faraday Cup Current Amplitude
  cout << "Pmt1   =" << Pmt1 << endl;  // Luminosity monitor on beam pipe 1
  cout << "Pmt2   =" << Pmt2 << endl;  // Luminosity monitor on beam pipe 2
  cout << "Pmt3   =" << Pmt3 << endl;  // Luminosity monitor on beam pipe 3
  cout << "Pmt4   =" << Pmt4 << endl;  // Luminosity monitor on beam pipe 4
  cout << "Res1   =" << Res1 << endl;  // Reserved 1
  cout << "Res2   =" << Res2 << endl;  // Reserved 2
  cout << "HelAcc =" << HelAcc << endl; // Helicity states accumulating counter.
  cout << "HLSAcc =" << HLSAcc << endl; // HLS Banks accumulatiing counter.
}


////////////////////////////////////////////////////////////////
//
//  End of File  THLSClass.cc
////////////////////////////////////////////////////////////////

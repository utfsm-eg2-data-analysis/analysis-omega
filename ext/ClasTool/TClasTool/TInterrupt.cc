// @(#)ClasTool/TInterrupt:$Name:  $:$Id: TInterrupt.cc,v 1.2 2007/03/01 22:27:00 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all. *
 *                                                                          *
 * Documentation  : TInterrupt.html                                           *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  1999 (UNH)                                             *
 * Initial Authors:  Maurik Holtrop (UNH)                                   *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
</pre><H1> TInterrupt </H1>
<p>Created at UNH by <b><i><a href="http://www.physics.unh.edu/~maurik">Maurik Holtrop</a></b></i>.
<p>
This class facilitates you to have an interruptable analysis. </p>
<h2>Usage:</h2>
<pre>
// Set up the interrupt in the code initialization area.
TInterrupt *IntHandle=new TInterrupt();
gSystem->AddSignalHandler(IntHandle);
//
...
// 
// In the loop of the code:
//
if( IntHandlw->IsInterrupted() ){
  cerr << "TMaui::Run() Interrupted by CRTL-C \n";
  cerr << "Writing Histfile \n";
  WriteHistFile();
  CloseHistFile();
  cerr << "Exiting. \n\n";
  gSystem->Exit(0);         // We exit The code
  break;                    // Or we break out of the loop.
}

</pre>
<p>
Additional information about this package, including an overview, can be found at the
<a href="http://www.physics.unh.edu/~maurik/ClasTool">ClasTool Documentation</a> web pages.
</p>
<pre> 
<!-- */ 
// --> End_Html   
#include "TInterrupt.h"

ClassImp(TInterrupt)

Int_t TInterrupt::fgInterrupted=0;

Bool_t  TInterrupt::Notify(){
  cerr << "You pressed crtl-C for the " << ++NumSig << " time ! (exit on #5)\n";
  if(NumSig >= 5){
    gSystem->Exit(2);
  }

  fgInterrupted++;

  return(1);
}

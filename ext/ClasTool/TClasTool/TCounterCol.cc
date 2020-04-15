// @(#)ClasTool/TCounterCol:$Name:  $:$Id: TCounterCol.cc,v 1.2 2007/03/01 22:27:00 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all. *
 *                                                                          *
 * Documentation  : TCounterCol.html                                           *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  1999 (UNH)                                             *
 * Initial Authors:  Maurik Holtrop (UNH)                                   *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
</pre><H1> TCounterCol </H1>
<p>Created at UNH by <b><i><a href="http://www.physics.unh.edu/~maurik">Maurik Holtrop</a></b></i>.
<p>
This class is derived from TObjArray and extended to conveniently store a set of TCounter objects.
This makes it easier to keep track of how many times a particular cut passed or failed 
in your data analysis. Sure, there are other ways to count, but this class can simplify your 
code.</p>
The strength of using this class is that you can write out the results to a root file together with
your histograms, and thus keep track of your analysis better. The ease of storing the results in this
way is what makes this class worth using.</p>
<H2>How to use:</H2>
In your analysis routine, create a new TCounterCol, and setup the counters: <br>
<pre>
TCounterCol col;
cGoode=col.AddCounter("Good Electron");
cGoodp=col.AddCounter("Good Proton");
cGoodpi=col.AddCounter("Good Pion");
...
... // Start the event loop.
...
for(iEvent=0;iEvent&lt;AllEvents;iEvent++){  
   if(col.Test(MyGoodElectronTest(),cGoode)){
     ... Do what you wanted to do with a good electron.
   }

   if(MyGoodProtonTest()){
     col.True(cGoodp);
     // Do good proton stuff.
  }else{
     col.False(cGoodp);
     // Do bad proton stuff.
   }
...
...
}
...
col.Print(); // Print out the contents of counters.
col.Write(); // Write the counters to your open histogram file.
f.Close();   // Close the file.
<pre>
<p>
Additional information about this package, including an overview, can be found at the
<a href="http://www.physics.unh.edu/~maurik/ClasTool">ClasTool Documentation</a> web pages.
</p>
<pre> 
<!-- */ 
// --> End_Html   

#include "TCounterCol.h"

void TCounterCol::Reset(){
  // Reset all counters.
  TIter next(this);
  TCounter *cc;

  while( (cc=(TCounter *)next()) ){
    cc->Reset();
  }
}

void TCounterCol::SetCounterTitles(void){
    //
    // Set the Titles of each counter to reflect the
    // current count.
    // This is called before writing this object to file
    // so that an "ls" or "browse" on the object reflects
    // the correct numbers.
    //
    TIter next(this);
    TCounter *cc;
    while ((cc = (TCounter *) next())) {
        cc->SetTitle();
    }
}

void TCounterCol::Print(){
  // Print the conteds of each counter.
  TCounter *cc;

  for(Int_t i=0;i<=GetLast();i++){
    if( (cc=(TCounter *)At(i)) ){
      printf("(%03d) ",i);
      cc->Print();
    }else{
      printf("(%03d) Missing.",i);
    }    
  }
}

void TCounterCol::Browse(TBrowser *b){
  // Browse the tables
  TIter next(this);
  TCounter *cc;
  char tmpstr[40];

  for(Int_t i=0;i<GetEntries();i++){
    if( (cc=(TCounter *)At(i)) ){
      TString showthis;
      sprintf(tmpstr,"(%03d) ",i);
      showthis=tmpstr;
      showthis.Append(cc->GetTitle());
      b->Add((TObject *)cc,showthis);
    }
  }
}


ClassImp(TCounterCol)



// @(#)ClasTool/TFilter.cc:$Name:  $:$Id: TFilter.cc,v 1.3 2007/04/05 20:36:43 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all. *
 *                                                                          *
 * Documentation  : TFilter.html                                          *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  3/1/2007 (UNH)                                        *
 * Initial Authors:  Maurik Holtrop (UNH)                                   *
 ***************************************************************************/
// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

#include "TFilter.h"
//____________________ 
//BEGIN_HTML <!--
/* -->
</pre><H1> TFilter </H1>
<p>This Class is the base class for writing data filters. I highly recommend that you use it by 
<emph>deriving</emph> your own class from this one. All you then need to do is override the
default SelectEvent() fuction, which decides whether to keep the event or not. (The default
version keeps all events.) </p>
<p>Another good practice that I <b>strongly encourage</b> is that you keep a list of counters (TCounterCol) and 
a list of histograms that <b>show all your cuts and percentage passed</b> and stick these results
right in the output file. This can save you a headache later trying to figure out what was in the files.</p>
<p><b>Notice:</b> This class only works with data read by the TDSTReader (i.e. written by Write_Root_DST).</p>
<pre>
<!-- */
// --> End_Html
ClassImp(TFilter) // A class for creating data filters.
;  

TFilter::TFilter(){
  //
  // Initialize code.
  //

  // Add a signal handler so you can stop running with crtl-C

  cout << "TFilter initializer \n";

  Interrupt = new TInterrupt();
  gSystem->AddSignalHandler(Interrupt);  // Setup an intterupt handler.
  
  // Allow for timing the loop
  Time = new TStopwatch(); 
  // Setup histogramming array
  H= new TObjArray();
  SetFixEC();

  }

void TFilter::InitHistos(void){
  // This functions needs an override where you define your own histograms and counters.
  // You want to have the overridden InitHistos() routine called from the deriving class initializer.
  // NOTE: Your InitHistos method must at least define the C_Good_Event_Out counter.
  
  cout << "WARNING: TFilter::InitHistos() called, should be overridden.\n";


  // H->Add(H_PID = new TH1F("H_PID","Particle Types",40,0,39));

  C_Good_Event_Out    = Cuts.AddCounter("Good Event written out.");
}

Int_t TFilter::SelectEvent(){
  // This function must be overridden to provide your own cut.
  // This function returns 0 when you want to skip the event
  // and 1 when you want to keep it.
  return 1;
}

void TFilter::DeleteHistos(void){
  //
  // Delete all histograms by calling H->Delete()
  //
  H->Delete();
}

void TFilter::ClearHistos(void){
  //
  // Clear all histograms.
  //
  TIter next(H);
  TH1 *hist;
  
  while( (hist= (TH1 *)next()) ){
    hist->Reset();
  }
  
}

void TFilter::Write(void){
  //
  // Write all histograms in H and
  // all counters in Cuts to the currently
  // open file.
  //
  TIter next(H);
  TH1 *hist;

  Cuts.Write("Cuts",TObject::kSingleKey); // Write the cuts in a single key.

  TDirectory *dir=new TDirectory("Histograms","Filter Histograms");
  dir->cd();

  while( (hist= (TH1 *)next()) ){
    hist->Write();
  }

  dir->cd("..");
}

TTree *TFilter::Create_Out_Tree(TDSTReader *dstread){
  //
  // In a more simple world we would just be able to clone the input tree to the
  // output tree, using TTree *tree=chain->CloneTree().
  // This broke when there was a data change (from UChar_t to Char_t) in the 
  // TVirtualData class. 
  // Instead of cloning the input tree, we build a new tree, similar to the 
  // one in TDSTReader
  //
  tree=new TTree("CLASEVENT","CLAS Event Tree filtered");
  tree->SetAutoSave(1024*1024*1024);

  TTree *chain =dstread->GetTree();

#define __BUFSIZE__  16384
  int bufsize = __BUFSIZE__;
  int split   = 1;

#define AUTO_CONSTRUCT_TREE

#ifdef AUTO_CONSTRUCT_TREE
  //
  // This method is better, since it will adopt new banks in the data automatically,
  // the alternative, explicitly defining each branch, is kept for sake of pedagogy.
  //
  TObjArray *branches=chain->GetListOfBranches();
  TBranch *thisbranch;
  TIter nextbr(branches);
  while((thisbranch=(TBranch *)nextbr())){
    cout << "Adding " << thisbranch->GetName() << " of type " << thisbranch->GetClassName() <<endl;
    tree->Branch(thisbranch->GetName(),thisbranch->GetClassName(),(void **)thisbranch->GetAddress(),bufsize,split);
  }

#else

  tree->Branch("HEADER","THEADERClass",&dstread->fEvntHeader,bufsize,split);
  tree->Branch("EVNT",&dstread->fcaEVNTStore,bufsize,split);
  tree->Branch("ECPB",&dstread->fcaECPBStore,bufsize,split);
  tree->Branch("SCPB",&dstread->fcaSCPBStore,bufsize,split);
  tree->Branch("DCPB",&dstread->fcaDCPBStore,bufsize,split);
  tree->Branch("CCPB",&dstread->fcaCCPBStore,bufsize,split);
  tree->Branch("LCPB",&dstread->fcaLCPBStore,bufsize,split);
  
#ifdef WRITE_TGBI
  tree->Branch("TGBI",&dstread->fcaTGBIStore,bufsize,split);
#endif
  tree->Branch("MCHD",&dstread->fcaMCHDStore,bufsize,split);
#ifdef WRITE_PHOTON
  tree->Branch("STPB",&dstread->fcaSTPBStore,bufsize,split);
  tree->Branch("TGPB",&dstread->fcaTGPBStore,bufsize,split);
  tree->Branch("TAGR",&dstread->fcaTAGRStore,bufsize,split);
#endif

#ifdef WRITE_VERTEX
  tree->Branch("VERT",&dstread->fcaVERTStore,bufsize,split);
  tree->Branch("MVRT",&dstread->fcaMVRTStore,bufsize,split);
#endif

#ifdef WRITE_TBER
  tree->Branch("TBER",&dstread->fcaTBERStore,bufsize,split);
#endif

#ifdef WRITE_MCHD
  tree->Branch("MCHD",&dstread->fcaMCHDStore);
#endif

#ifdef WRITE_GSIM
  tree->Branch("GSIM",&dstread->fcaGSIMStore,bufsize,split);
#endif

#endif

  tree->SetBranchStatus("*",1);

  tree->SetMaxTreeSize(21474836480ULL); // Allow 20 Gbyte files.
  //  filevt->SetAutoSave(1024*1024*512);  // This is not needed but good idea
  return(tree);
}

Int_t TFilter::Run(Int_t Max_evt){

  Int_t ntree=-1;  // Force a load of the output tree on first event.

  chain=GetTree(); 
  TDSTReader *dstread = (TDSTReader *)GetReader();
  tree = Create_Out_Tree(dstread);  // Instead of cloning, we recreate the tree.
  // This avoids complaining when the tree being read has slightly different types than the
  // output tree.
  
  cout << "Running ...." << endl;

  Time->Start(kTRUE);

  for(iEvent=0;iEvent<Max_evt && Next()==0; iEvent++){

    if(iEvent % 100000 == 0 ){
      printf("Analyzed %09d events, now at %09d, written %09d events.\n",iEvent,GetHEADER()->GetNEvent(),((TCounter *)Cuts[C_Good_Event_Out])->GetTrues());
    }
    
    // Check if we are still on the same tree in the chain.
    // If we are onto the next tree, we need to reset the branches!!

    if(ntree != chain->GetTreeNumber()){
      ntree = chain->GetTreeNumber();               
      TIter next(chain->GetListOfBranches()); 
      TBranch *branch;
      while ((branch = (TBranch*)next())) {
	void *add = branch->GetAddress();
	if (add) tree->SetBranchAddress(branch->GetName(),add);
	else{
	  cerr<<"ERROR- Can not reset the branches of output tree !\n";
	  return(-1);
	}
      }
    } 

    // Here we call SelectEvent(), the user needs to supply this function.
    //
    // Inside this function you can also fill histograms, do various calculation
    // call other functions....

    if(Cuts.Test( SelectEvent() , C_Good_Event_Out)){
      tree->Fill();  // Fill the output tree.
    }
    
    if(Interrupt->IsInterrupted()){
      break;
    }
    
  } // END EVENT LOOP.

  Time->Stop();

  printf("Processed %d events in %6.2f sec, %6.2f CPU sec. \n",iEvent,Time->RealTime(),Time->CpuTime());
  printf("Rate is %7.1f events/sec, %7.1f events/CPUsec \n",iEvent/Time->RealTime(),iEvent/Time->CpuTime());
  
  return(iEvent);
}


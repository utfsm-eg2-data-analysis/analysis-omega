// @(#)PartSieve/TPartSieveHistograms:$Name:  $:$Id: TPartSieveHists.cc,v 1.3 2007/04/05 20:38:47 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all.            *
 *                                                                          *
 * Documentation  : TPartSieveHists.html                                *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  04/2/2002 (UNH)                                        *
 * Initial Authors:  Maurik Holtrop (UNH)                                   *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//Begin_Html <!--
/* -->
<H1>TPartSieveHists</H1>
<H2>Particle ID Histogramming service</H2>
<p>Created at UNH by <a href="http://www.physics.unh.edu/~maurik">Maurik Holtrop</a></b></i></p>
<p>TPartSieveHistograms supports the TPartSieve class by providing a number of
generally useful histograms that help determine the correct settings of the
particle cuts. It is thus rather linked to the TPartSieve class. Since opinions on
what cuts are best differ, and thus which histograms are useful differ, these classes will never
satisfy everyones tastes.
</p>
<p>
<H2>Use: </H2>
<p>See TPartSieve for use of that class.<p>
This class should be initialized in the initialization of your analysis code. It will create
a standard set of histograms in the directory "SieveHists". <br>
In your event loop you would want to call the Fill() method right after sieving the particles.<br>
After the loop is finished you can write the collection of histograms out to disk with the Write() method.</p>
<H3>Example Code:</H3>
<pre>
{
TClasTool *ct=new TClasTool();
ct->InitDSTReader();
ct->SetBeamEnergy(5.015); // in GeV 
ct->Add("mydata.root");   // WriteRootDST file with data.
TPartSieve *Sieve=new TPartSieve(ct,0x03); // 0x03 is the control flag.
TPartSieveHistograms *SHists=new TPartSieveHistograms(Sieve);
Sieve->SortOn();
Sieve->ConfidenceOn();
for(Int_t ievt=0;ct->Next();ievt++){
   Sieve->SieveEvent();
   SHists->Fill();
   //
   // Do analysis
}
TFile fs("SieveHists.root","CREATE");
SHists->Write();
fs.Close();
}
</pre>
</p>
<p>
Additional information about this package, including an overview, can be found at the
<a href="http://www.physics.unh.edu/~maurik/ClasTool">ClasTool Documentation</a> web pages.
<pre> 
<!-- */ 
// --> End_Html   
///////////////////////////////////////////////////////////////////////////////////


#include "TPartSieveHists.h"
;
ClassImp(TPartSieveHists) // Package to sort particles and fix PID.
;

TPartSieveHists::~TPartSieveHists()
{
    // Proper destructor: Clean up.
  DeleteHists(); // Note: this routine also deletes the TObjArray!
}

  
void TPartSieveHists::Initialize(){
  //
  // Run code initialization tasks.
  //
  if(fControl & kMain_Histos){
    fH = new TObjArray();
    ABetaPIdx.reserve(kNParticleTypes);
    ADeltatPIdx.reserve(kNParticleTypes);
    SBetaPIdx.reserve(kNParticleTypes);
    SDeltatPIdx.reserve(kNParticleTypes);    
  }else{
    fH=NULL;
  }
  if(fControl & kPaddle_Histos){
    fHP = new TObjArray();
    ASCBetaP.reserve(6);    // Six sectors.
    ASCDeltatP.reserve(6);    // Six sectors.
    for(Int_t i=0;i<6;i++){
      ASCBetaP[i].reserve(48); // 48 Paddles;
      ASCDeltatP[i].reserve(48); // 48 Paddles;

    }
  }else{
    fHP=NULL;
  }

  InitHists(); // Setup histograms.

}

void TPartSieveHists::InitHists(){
  //
  // Define the histograms.
  // 

  // Histograms on ALL particles (unsorted)
  //
  cout << "Init histograms:";

  if(fH){
    fH->Add(APartCount=new TH1F("APartCount","Input Particle Counts",kNParticleTypes,0,kNParticleTypes));
    fH->Add(AMassPos  =new TH1F("AMassPos",  "Calculated Mass of + particles",300,0.,3.0));
    fH->Add(AMassNeg  =new TH1F("AMassNeg",  "Calculated Mass of - particles",300,0.,3.0));
    
    fH->Add(AElec_mom     = new TH1F("AElec_mom","Electron momentum, electron",500,0.,5.));
    fH->Add(AElec_Q2W     = new TH2F("AElec_Q2W" ,"W vs Q2, electron",300,0.,5.,300,0.,4.));
    fH->Add(AElec_Q2Lc    = new TH2F("AElec_Q2Lc" ,"Lc vs Q2, electron",300,0.,5.,300,0.,4.));
    fH->Add(AElec_ec_u    = new TH1F("AElec_ec_u","EC u, electron",500,0,500));
    fH->Add(AElec_ec_v    = new TH1F("AElec_ec_v","EC v, electron",500,0,500));
    fH->Add(AElec_ec_w    = new TH1F("AElec_ec_w","EC w, electron",500,0,500));
    fH->Add(AElec_ec_xy   = new TH2F("AElec_ec_xy","EC xy, electron",420,-420,420,420,-420,420));
    fH->Add(AElec_ec_etot = new TH2F("AElec_ec_etot","EC Etot/p vs p,electron",300,0.,4.5,300,0.,.5));
    fH->Add(AElec_ec_eio  = new TH2F("AElec_ec_eio","EC Eout/p vs Ein/p, electron",300,0.,0.5,300,0.,0.5));
    fH->Add(AElec_cc      = new TH1F("AElec_cc","CC photo electrons, electron",300,0.,300.));
    
    fH->Add(ABetaPPos  = new TH2F("ABetaPPos","Beta versus Momentum, + particles",300,0,4.,300,0.1,1.1));
    fH->Add(ABetaPNeg  = new TH2F("ABetaPNeg","Beta versus Momentum, - particles",300,0,4.,300,0.1,1.1));
    
    
    // Histograms on Sorted particles.
    //
    fH->Add(SPartCount=new TH1F("SPartCount","Sorted Particle Counts",kNParticleTypes,0,kNParticleTypes));
    fH->Add(SMassPos  =new TH1F("SMassPos",  "Sorted Calculated Mass of + particles",300,0.,3.0));
    fH->Add(SMassNeg  =new TH1F("SMassNeg",  "Sorted Calculated Mass of - particles",300,0.,3.0));
    
    fH->Add(SElec_mom     = new TH1F("SElec_mom","S Electron momentum, electron",500,0.,5.));
    fH->Add(SElec_Q2W     = new TH2F("SElec_Q2W" ,"S W vs Q2, electron",300,0.,5.,300,0.,4.));
    fH->Add(SElec_Q2Lc    = new TH2F("SElec_Q2Lc" ,"S Lc vs Q2, electron",300,0.,5.,300,0.,4.));
    fH->Add(SElec_ec_u    = new TH1F("SElec_ec_u","S EC u, electron",500,0,500));
    fH->Add(SElec_ec_v    = new TH1F("SElec_ec_v","S EC v, electron",500,0,500));
    fH->Add(SElec_ec_w    = new TH1F("SElec_ec_w","S EC w, electron",500,0,500));
    fH->Add(SElec_ec_xy   = new TH2F("SElec_ec_xy","S EC xy, electron",420,-420,420,420,-420,420));
    fH->Add(SElec_ec_etot = new TH2F("SElec_ec_etot","S EC Etot/p vs p,electron",300,0.,4.5,300,0.,.5));
    fH->Add(SElec_ec_eio  = new TH2F("SElec_ec_eio","S EC Eout/p vs Ein/p, electron",300,0.,0.5,300,0.,0.5));
    fH->Add(SElec_cc      = new TH1F("SElec_cc","S CC photo electrons, electron",300,0.,300.));
    
    fH->Add(SBetaPPos  = new TH2F("SBetaPPos","S Beta versus Momentum, + particles",300,0,4.,300,0.1,1.1));
    fH->Add(SBetaPNeg  = new TH2F("SBetaPNeg","S Beta versus Momentum, - particles",300,0,4.,300,0.1,1.1));
    
    
    
    for(Int_t i=0;i<kNParticleTypes;i++){
      TString part_name=ClasTool::GetPartShortNameIdx(i);
      TString part_symb=ClasTool::GetPartSymbolIdx(i);
      Int_t part_charge=ClasTool::GetPartChargeIdx(i);
      
      TString hname;
      TString htitle;
      
      // Book All Beta versus momentum histograms
      htitle="Beta vs P,";
      htitle.Append(part_symb);
      hname="BetaP";    
      if(part_charge>0){
	hname.Append("Pos");
      }else if(part_charge<0){
	hname.Append("Neg");
      }else{
	hname.Append("Neut");
      }
      hname.Append(part_name);
      
      cout << "Book histo named: "<<hname <<" titled:" << htitle << endl;
      
      
      ABetaPIdx[i]=fH->GetEntries();    
      
      
      fH->Add(new TH2F("A"+hname,"A "+htitle,300,0,4.,300,0.1,1.1));
      
      SBetaPIdx[i]=fH->GetEntries();    
      fH->Add(new TH2F("S"+hname,"S "+htitle,300,0,4.,300,0.1,1.1));
      
      // Book All Deltat versus momentum histograms
      
      htitle="#Delta t versus Momentum,";
      htitle.Append(part_symb);
      hname="DeltatP";    
      if(part_charge>0){
	hname.Append("Pos");
      }else if(part_charge<0){
	hname.Append("Neg");
      }else{
	hname.Append("Neut");
      }
      hname.Append(part_name);
      
      cout << "Book histo named: "<<hname <<" titled:" << htitle << endl;
      
      ADeltatPIdx[i]=fH->GetEntries();    
      fH->Add(new TH2F("A"+hname,"A "+htitle,300,0,4.,300,-2.5,2.5));
      
      SDeltatPIdx[i]=fH->GetEntries();    
      fH->Add(new TH2F("S"+hname,"S "+htitle,300,0,4.,300,-2.5,2.5));
    }
  }

  if(fHP){
    for(Int_t isec=0;isec<6;isec++){
      for(Int_t ipad=0;ipad<48;ipad++){
	TString hname;
	TString htitle;
	char sec[3],pad[5];
	sprintf(sec,"%d",isec+1);
	sprintf(pad,"%02d",ipad+1);

	htitle="Beta vs P, Sector ";
	hname="SCBetaP";
	htitle.Append(sec);
	htitle.Append(" Paddle ");
	htitle.Append(pad);
	hname.Append(sec);
	hname.Append("P");
	hname.Append(pad);

	ASCBetaP[isec][ipad]=fHP->GetEntries();
	fHP->Add(new TH2F(hname,htitle,300,0.,4.,300,0.1,1.1));

	htitle="#Delta t vs P, Sector ";
	hname="SCDeltatP";
	htitle.Append(sec);
	htitle.Append(" Paddle ");
	htitle.Append(pad);
	hname.Append(sec);
	hname.Append("P");
	hname.Append(pad);

	ASCDeltatP[isec][ipad]=fHP->GetEntries();
	fHP->Add(new TH2F(hname,htitle,300,0.,4.,300,-5.,5.));

      }
    }
  }

} 

void TPartSieveHists::DeleteHists(){
  // Delete all histograms AND delete the TObjArray that contained them.
  if(fH){
    fH->Delete();
    delete fH;
  }
  if(fHP){
    fHP->Delete();
    delete fHP;
  }
}

void TPartSieveHists::ClearHists(){
  //
  // Clear all histograms.
  //

  if(fH){
    TIter next(fH);
    TH1 *hist;

    while( (hist= (TH1 *)next()) ){
      hist->Reset();
    }
  }

  if(fHP){
    TIter next(fHP);
    TH1 *hist;

    while( (hist= (TH1 *)next()) ){
      hist->Reset();
    }
  }
}


void TPartSieveHists::Write(void){
  //
  // Write all histograms in fH and
  // all counters in fCuts to the currently
  // open file.
  //

  fCuts.Write("Cuts",TObject::kSingleKey);

  if(fH){
    TIter next(fH);
    TH1 *hist;  
    TDirectory *dir=new TDirectory("Hists","Sieve Hists");
    dir->cd();

    while( (hist= (TH1 *)next()) ){
      hist->Write();
    }
  
    dir->cd("..");
  }

  if(fHP){
    TIter next(fHP);
    TH1 *hist;  
    TDirectory *dir=new TDirectory("Paddles","SC Paddle Hists");
    dir->cd();

    while( (hist= (TH1 *)next()) ){
      hist->Write();
    }
  
    dir->cd("..");
  }

}

Int_t TPartSieveHists::Fill(){
  //
  // Fill all the defined histograms.
  //

  Float_t EventStart=fCT->GetHEADER()->STT;

  if(fH){
    Float_t Q2,W;
    Float_t nu,Lc;



    // Fill the histograms relating to unsorted data.  
    for(Int_t ipart=0;ipart<fCT->GetNPart();ipart++){
      
      TEVNTClass *evnt=fCT->GetEVNT(ipart);
      Float_t mass = evnt->GetMass();
      Float_t p=evnt->GetMomentum();
      Float_t beta=evnt->GetBeta();
      
      if(ipart==0 && evnt->GetId()==11){ // Electron with ID=11.
      
	fCT->GetInvariants(&Q2,&W);
	if(W>0){
	  W=TMath::Sqrt(W);
	}else{
	  W=-1.;
	}
	nu=fCT->GetBeamEnergy()-p;

	Lc= (0.19732696 )*2*nu/((1.02)*(1.02) + Q2); // HBarc in Gev*fm = 0.197...

	AElec_mom->Fill(p);
	AElec_Q2W->Fill(Q2,W);
	AElec_Q2Lc->Fill(Q2,Lc);
      
	if(evnt->GetECidx()>=0){
	  Float_t u,v,w;
	  TECPBClass *ec=(TECPBClass *)fCT->GetBankRow("ECPB",evnt->GetECidx());
	  ec->GetUVW(&u,&v,&w);
	  AElec_ec_u->Fill(u);
	  AElec_ec_v->Fill(v);
	  AElec_ec_w->Fill(w);
	  AElec_ec_xy->Fill(ec->X,ec->Y);
	  AElec_ec_etot->Fill(p,ec->Etot/p);
	  AElec_ec_eio->Fill(ec->Ein/p,ec->Eout/p);
	}
	if(evnt->GetCCidx()>=0){
	  TCCPBClass *cc=(TCCPBClass *)fCT->GetBankRow("CCPB",evnt->GetCCidx());
	  AElec_cc->Fill(cc->Nphe);
	}


      }


      APartCount->Fill(ClasTool::GetTypeFromPid(evnt->GetId()));
      if(evnt->GetCharge()>0){
	// All positive particles.
	AMassPos->Fill(mass);      
	ABetaPPos->Fill(p,beta);
      }else if(evnt->GetCharge()<0){
	AMassNeg->Fill(mass);
	ABetaPNeg->Fill(p,beta);
      }
    
      if(evnt->GetSCidx()>=0){
	TSCPBClass *sc=(TSCPBClass *)fCT->GetBankRow("SCPB",evnt->GetSCidx());
      
	Int_t idx=ClasTool::GetTypeFromPid(evnt->GetId());      
	Float_t beta2=GetBetaP(p,idx);
	Float_t deltat = sc->Time - sc->Path/(29.9792*beta2) -EventStart ;

	TH2F *abetap=(TH2F *)fH->At( ABetaPIdx[idx]);
	abetap->Fill(p,beta);
      
	TH2F *adeltatp=(TH2F *)fH->At( ADeltatPIdx[idx]);
	adeltatp->Fill(p,deltat);

	
      
      }    
    }

    // Fill the histograms relating to sorted data.

    for(Int_t ipart=0;ipart<kNParticleTypes;ipart++){
      Int_t Npart= fS->GetNIdx(ipart);

      SPartCount->Fill(ipart,Npart);

      for(Int_t jp=0;jp<Npart;jp++){
	Int_t index = fS->GetIndexIdx(ipart,jp);

	TEVNTClass *evnt=fCT->GetEVNT(index);
	Float_t mass = evnt->GetMass();
	Float_t p=evnt->GetMomentum();
	Float_t beta=evnt->GetBeta();

	if(ipart==kElectron && jp==0 && evnt->GetId()==11){ // Electron with ID=11.
      
	  fCT->GetInvariants(&Q2,&W);
	  if(W>0){
	    W=TMath::Sqrt(W);
	  }else{
	    W=-1.;
	  }
	  nu=fCT->GetBeamEnergy()-p;
	
	  Lc= (0.19732696 )*2*nu/((1.02)*(1.02) + Q2); // HBarc in Gev*fm = 0.197...
	
	  SElec_mom->Fill(p);
	  SElec_Q2W->Fill(Q2,W);
	  SElec_Q2Lc->Fill(Q2,Lc);
	
	  if(evnt->GetECidx()>=0){
	    Float_t u,v,w;
	    TECPBClass *ec=(TECPBClass *)fCT->GetBankRow("ECPB",evnt->GetECidx());
	    ec->GetUVW(&u,&v,&w);
	    SElec_ec_u->Fill(u);
	    SElec_ec_v->Fill(v);
	    SElec_ec_w->Fill(w);
	    SElec_ec_xy->Fill(ec->X,ec->Y);
	    SElec_ec_etot->Fill(p,ec->Etot/p);
	    SElec_ec_eio->Fill(ec->Ein/p,ec->Eout/p);
	  }
	  if(evnt->GetCCidx()>=0){
	    TCCPBClass *cc=(TCCPBClass *)fCT->GetBankRow("CCPB",evnt->GetCCidx());
	    SElec_cc->Fill(cc->Nphe);
	  }
	
	}

	if(evnt->GetCharge()>0){
	  SMassPos->Fill(mass);
	  SBetaPPos->Fill(p,beta);
	}else if(evnt->GetCharge()<0){
	  SMassNeg->Fill(mass);
	  SBetaPNeg->Fill(p,beta);
	}

	if(evnt->GetSCidx()>=0){
	  TSCPBClass *sc=(TSCPBClass *)fCT->GetBankRow("SCPB",evnt->GetSCidx());

	
	  Int_t idx=ClasTool::GetTypeFromPid(evnt->GetId());
	
	  Float_t beta2=GetBetaP(p,idx);
	  Float_t deltat = sc->Time - sc->Path/(29.9792*beta2) -EventStart ;
	
	  TH2F *sbetap=(TH2F *)fH->At( SBetaPIdx[idx]);
	  sbetap->Fill(p,beta);
	
	  TH2F *sdeltatp=(TH2F *)fH->At( SDeltatPIdx[idx]);
	  sdeltatp->Fill(p,deltat);
	}    
      }      
    
    }
  }

  if(fHP){
    // Fill the histograms relating to unsorted data.  
    for(Int_t ipart=0;ipart<fCT->GetNPart();ipart++){
      
      TEVNTClass *evnt=fCT->GetEVNT(ipart);
      Float_t p=evnt->GetMomentum();
      Float_t beta=evnt->GetBeta();
      
      if(evnt->GetSCidx()>=0){
	TSCPBClass *sc=(TSCPBClass *)fCT->GetBankRow("SCPB",evnt->GetSCidx());
	
	Int_t idx=ClasTool::GetTypeFromPid(evnt->GetId());      
	Float_t beta2=GetBetaP(p,idx);
	Float_t deltat = sc->Time - sc->Path/(29.9792*beta2) -EventStart ;

	Int_t isec=sc->GetSector()-1;
	Int_t ipad=sc->GetPaddle()-1;

	TH2F *betap=(TH2F *)fHP->At( ASCBetaP[isec][ipad]);
	betap->Fill(p,beta);

	TH2F *deltatp=(TH2F *)fHP->At( ASCDeltatP[isec][ipad]);
	deltatp->Fill(p,deltat);

      }
    }
  }

  return(1);
}

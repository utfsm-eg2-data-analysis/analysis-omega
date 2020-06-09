/******************************************/
/* write_tree.cxx                         */
/*                                        */
/* Sebastián Morán                        */
/*                                        */
/******************************************/

#include "Riostream.h"
#include "TApplication.h"
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TClasTool.h"
#include "TIdentificator.h"
#include "TMath.h"

/*** Global variables ***/

const Float_t m2 = 0.139570*0.139570; 
const Double_t lines[14][2]={    {-0.70 , 0.70 },   {-0.70 , 0.65 },
                                 {-0.70 , 0.65 },   {-0.70 , 0.65 },
                                 {-0.55 , 0.55 },   {-0.50 , 0.55 },
                                 {-0.50 , 0.40 },   {-0.48 , 0.40 },
                                 {-0.50 , 0.40 },   {-0.50 , 0.40 },
                                 {-0.50 , 0.40 },   {-0.50 , 0.40 },
				 {-0.32 , 0.32 },   {-0.30 , 0.37 } };

/*** Declaration of functions ***/

TString  getPartId(Int_t k,TClasTool* input,TIdentificator* t,Int_t (*ptrToSampFrackC)(TIdentificator *t, Int_t j),Int_t (*ptrToSampFrackFe)(TIdentificator *t, Int_t j),Int_t (*ptrToSampFrackPb)(TIdentificator *t, Int_t j),  Int_t (*ptrToSampFrackD2)(TIdentificator *t, Int_t j), Int_t (*ptrToSampFrackC_sim)(TIdentificator *t, Int_t j),Int_t (*ptrToSampFrackFe_sim)(TIdentificator *t, Int_t j),Int_t (*ptrToSampFrackPb_sim)(TIdentificator *t, Int_t j),  Int_t (*ptrToSampFrackD2_sim)(TIdentificator *t, Int_t j), TVector3* (*ptrTouvwCoor)(TIdentificator *t),  TString Metal,TString dataSimOpt);

Int_t getVC_RD_Shift_C (TIdentificator* t);
Int_t getVC_RD_Shift_Fe(TIdentificator* t);
Int_t getVC_RD_Shift_Pb(TIdentificator* t);

TVector3* uvwCoor(TIdentificator* t);

Int_t SampFrackCheck_C (TIdentificator* t, Int_t j);
Int_t SampFrackCheck_Fe(TIdentificator* t, Int_t j);
Int_t SampFrackCheck_Pb(TIdentificator* t, Int_t j);
Int_t SampFrackCheck_D2(TIdentificator* t, Int_t j);

Int_t SampFrackCheck_C_sim (TIdentificator* t, Int_t j);
Int_t SampFrackCheck_Fe_sim(TIdentificator* t, Int_t j);
Int_t SampFrackCheck_Pb_sim(TIdentificator* t, Int_t j);
Int_t SampFrackCheck_D2_sim(TIdentificator* t, Int_t j);

TVector3 *GetCorrectedVert(TIdentificator* t); 

Int_t getVC_TM_C (Double_t ZC);
Int_t getVC_TM_Fe(Double_t ZC);
Int_t getVC_TM_Pb(Double_t ZC);

Int_t getVC_RD(Double_t Z); // for simulations only, no shift

Double_t getXf(Int_t k, TIdentificator* t, Bool_t kind);
Float_t  getPhiPQ(Int_t k,TIdentificator* t, Bool_t kind);

int main(int argc, char **argv) {
  
  TString Metal      = (TString)argv[1];
  TString dataSimOpt = "sim"; //(TString)argv[2]; 'data' or 'sim'

  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");
  char File[200];
  //system("ls -1 /data/jlab/mss/clas/eg2a/production/Pass2/Clas/clas_41146_00.pass2.root > dataFiles.txt");
  //system("ls -1 /eos/user/o/orsosa/HSim/Fe2/ROOT/simul_Fe*.root > dataFiles.txt");
  system("ls -1 in.root > dataFiles.txt");
  ifstream in("dataFiles.txt", ios::in);
  if (!in) {
    cerr << "File Not Opened!" << endl;
    exit(1);
  }
  while (in >> File) {
    input->Add(File);
  }
  in.close();
  system("rm dataFiles.txt");

  const char* NtupleName;
  const char* NtupleName_elec; 
  const char* NtupleNameFidCut;
  const char* VarList = "TargType:Q2:Nu:Sector:PhiPQ_RD:PhiPQ:Zh:Pt2:Xf:deltaZ:Xf_RD:Xb:VC_RD:YC:VC_TM:Nphe:P:Mass2:Sector_pi:betta";
  const char* VarList_elec = "Q2:Xb:Nu:TargType:VC_RD:VC_TM:YC:Sector:Nphe:P"; 

  Float_t *vars      = new Float_t[20];
  Float_t *elec_vars = new Float_t[10];  

  const char* VarListThr = "Q2:Nu:W:Sector:PhiPQ:Zh:Pt:Pt2:Xf:P:deltaZ:Xb:Xf_RD:PhiPQ_RD";
  const char* VarListThr_elec ="Q2:Xb:Nu:Sector"; 

  Float_t *varsThr      = new Float_t[14];
  Float_t *varsThr_elec = new Float_t[4];

  TIdentificator *t = new TIdentificator(input);

  Long_t nEntries = (Long_t) input->GetEntries();

  TFile *output;

  if (dataSimOpt=="data") {
    NtupleName = "ntuple_data";
    NtupleName_elec = "ntuple_data_electrons";
    output = new TFile("sm_el_sm_pi.root", "RECREATE", "Data of particles");       
  } else if (dataSimOpt=="sim") { 
    NtupleName = "ntuple_accept";
    NtupleName_elec = "ntuple_accept_electrons";
    output = new TFile("sm_el_sm_pi.root", "RECREATE", "Data of particles");       
  }

  TNtuple *ntuple = new TNtuple(NtupleName,"Pion pluses",VarList);
  TNtuple *ntuple_thrown      = 0;
  TNtuple *ntuple_thrown_elec = 0;
  TNtuple *elec_ntuple = new TNtuple(NtupleName_elec,"electrons",VarList_elec);
  
  if (dataSimOpt=="sim") {
    ntuple_thrown = new TNtuple("ntuple_thrown","pions",VarListThr);
    ntuple_thrown_elec = new TNtuple("ntuple_thrown_electrons","electrons",VarListThr_elec);
  }
  
  input->Next();
  
  for (Int_t k = 0; k < nEntries; k++) {

    input->Next();
    Int_t nRows =  input->GetNRows("EVNT");  

    if (nRows > 0 && 
	getPartId(0,input,t,SampFrackCheck_C,SampFrackCheck_Fe,SampFrackCheck_Pb, SampFrackCheck_D2,SampFrackCheck_C_sim,SampFrackCheck_Fe_sim,SampFrackCheck_Pb_sim, SampFrackCheck_D2_sim, uvwCoor,Metal,dataSimOpt) =="electron" &&
	t->Q2()>1. && t->W()>2. && t->Nu()/5.015 < 0.85) {
      
	elec_vars[0] = t->Q2();
	elec_vars[1] = t->Xb();
	elec_vars[2] = t->Nu();
	elec_vars[3] = t->ElecVertTarg();
	
	if (dataSimOpt=="data") {
	  if (Metal == "C")       elec_vars[4] = getVC_RD_Shift_C(t); 
	  else if (Metal == "Fe") elec_vars[4] = getVC_RD_Shift_Fe(t); 
	  else if (Metal == "Pb") elec_vars[4] = getVC_RD_Shift_Pb(t); 
	} else if (dataSimOpt == "sim") {
	  elec_vars[4] = getVC_RD(t->Z(0));
	}
	
	Float_t ZC = GetCorrectedVert(t)->Z();

	if (dataSimOpt=="data") {
	  if (Metal == "C")       elec_vars[5] = getVC_TM_C(ZC);
	  else if (Metal == "Fe") elec_vars[5] = getVC_TM_Fe(ZC);
	  else if (Metal == "Pb") elec_vars[5] = getVC_TM_Pb(ZC);
	} else if (dataSimOpt == "sim") {
	  if (Metal != "D2") elec_vars[5] = 2. ;
	  else if (Metal == "D2") elec_vars[5] = 1.;
	}
	elec_vars[6] = GetCorrectedVert(t)->Y();
	elec_vars[7] = t->Sector(0);
	elec_vars[8] = t->Nphe(0);
	elec_vars[9] = t->Momentum(0);

	elec_ntuple->Fill(elec_vars);
	
      for (Int_t i = 1; i < nRows; i++) {
       TString part;
part=getPartId(i,input,t,SampFrackCheck_C,SampFrackCheck_Fe,SampFrackCheck_Pb,SampFrackCheck_D2,SampFrackCheck_C_sim,SampFrackCheck_Fe_sim,SampFrackCheck_Pb_sim,SampFrackCheck_D2_sim, uvwCoor,Metal,dataSimOpt);
	if ((part=="pion +"|| part =="high energy pion +") && 
	      t->Pt2(i)<t->Momentum(i)*t->Momentum(i)&&t->Momentum(i) < 5.015) 
	  {
	  vars[0] = t -> ElecVertTarg();
	  vars[1] = t -> Q2();
	  vars[2] = t -> Nu();
	  vars[3] = t -> Sector(0);
	  vars[4] = getPhiPQ(i, t,0); 
	  vars[5] = t -> PhiPQ(i);
	  vars[6] = t -> Zh(i);
	  vars[7] = t -> Pt2(i);
	  vars[8] = t -> Xf(i);
	  vars[9] = (t -> Z(i)) - (t -> Z(0));  //pion-elec
	  vars[10] = getXf(i,t,0);
	  vars[11] = t -> Xb();
	  if (dataSimOpt=="data") {
	  if (Metal=="C")vars[12]       = getVC_RD_Shift_C(t);
	  else if (Metal=="Fe")vars[12] = getVC_RD_Shift_Fe(t);
          else if (Metal=="Pb")vars[12] = getVC_RD_Shift_Pb(t);
	  }else if (dataSimOpt=="sim") {
	  	  vars[12] = getVC_RD(t->Z(0));	  
	  }		  
          TVector3 RotatedVertPos(t->X(0,0), t->Y(0,0), t->Z(0,0));
          TVector3 RotatedVertDir(t->Px(0,0),t->Py(0,0),t->Pz(0,0)); 
          TVector3 TargetPos(0.043,-0.33,0);   TVector3 *V_corr = new TVector3();
          Float_t sect = t->Sector(0,0);  RotatedVertPos.RotateZ(-TMath::DegToRad()*60.*sect);
          RotatedVertDir.RotateZ(-TMath::DegToRad()*60.*sect);  TargetPos.RotateZ(-TMath::DegToRad()*60.*sect);
          Float_t ShiftLength = (TargetPos.X()-RotatedVertPos.X())/RotatedVertDir.X();
          RotatedVertDir = ShiftLength*RotatedVertDir;  RotatedVertPos = RotatedVertPos+RotatedVertDir;
          V_corr->SetX((RotatedVertPos-TargetPos).X()); V_corr->SetY((RotatedVertPos-TargetPos).Y());
          V_corr->SetZ(RotatedVertPos.Z());	

	  vars[13] =   V_corr->Y() ;
	  Float_t ZC = V_corr->Z();
	  
	  if (dataSimOpt=="data") {
	  if (Metal=="C")vars[14] = getVC_TM_C(ZC) ;
	  else if (Metal=="Fe")vars[14] = getVC_TM_Fe(ZC) ;	  
	  else if (Metal=="Pb")vars[14] = getVC_TM_Pb(ZC) ;
	  }else if (dataSimOpt=="sim"){
	  	if (Metal!="D2")      vars[14] = 2.;
		else if (Metal=="D2") vars[14] = 1.;
	  }
	  vars[15] =   t->Nphe(i) ;
	  vars[16] =   t->Momentum(i) ;
	  vars[17] =   t->Mass2(i); 
	  vars[18] =   t->Sector(i);	  
	  vars[19] =   t->Betta(i);	  
	  ntuple->Fill(vars);
	}
      }
    }
    
   if(dataSimOpt=="sim" && t -> Id(0,1)==3 && t->Q2(1)>1.&& t->W(1)>2.&& t->Nu(1)/5.015<0.85) {
                varsThr_elec[0] = t->Q2(1);
                varsThr_elec[1] = t->Xb(1);
		varsThr_elec[2] = t->Nu(1);
		varsThr_elec[3] = t->Sector(0,1);
       ntuple_thrown_elec->Fill(varsThr_elec);

      for(Int_t i=1; i < input->GetNRows("GSIM"); i++) {
      if(t -> Id(i,1)==8) {
		varsThr[0]  = t -> Q2(1);
                varsThr[1]  = t -> Nu(1);
                varsThr[2]  = t -> W(1);
                varsThr[3]  = t -> Sector(0,1);
                varsThr[4]  = t -> PhiPQ(i,1);
                varsThr[5]  = t -> Zh(i,1);
                varsThr[6]  = TMath::Sqrt(t -> Pt2(i,1));
                varsThr[7]  = t -> Pt2(i,1);
                varsThr[8] = t -> Xf(i,1);
                varsThr[9] = t -> Momentum(i,1);
                varsThr[10] = (t -> Z(i,1)) - (t -> Z(0,1));//deltaZ
                varsThr[11] = t -> Xb(1);
	        varsThr[12] = getXf(i,t,1);
                varsThr[13] = getPhiPQ(i,t,1);
		ntuple_thrown->Fill(varsThr);
   } //end id pions cicle
   } // end nrows cicle
   } // end electrons cicle GSIM
   // input->Next();
  }
  
  output->Write();
  output->Close();
  
  cout << "Done." << endl;
  
  return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TString getPartId(Int_t k, TClasTool* input, TIdentificator *t, Int_t (*ptrToSampFrackC)(TIdentificator *t, Int_t j), Int_t (*ptrToSampFrackFe)(TIdentificator *t, Int_t j), Int_t (*ptrToSampFrackPb)(TIdentificator *t, Int_t j),   Int_t (*ptrToSampFrackD2)(TIdentificator *t, Int_t j),  Int_t (*ptrToSampFrackC_sim)(TIdentificator *t, Int_t j), Int_t (*ptrToSampFrackFe_sim)(TIdentificator *t, Int_t j), Int_t (*ptrToSampFrackPb_sim)(TIdentificator *t, Int_t j),   Int_t (*ptrToSampFrackD2_sim)(TIdentificator *t, Int_t j),  TVector3* (*ptrTouvwCoor)(TIdentificator *t),TString Metal,TString dataSimOpt) {
  
    Int_t number_dc =  input->GetNRows("DCPB");
    Int_t number_cc =  input->GetNRows("CCPB"); 
    Int_t number_sc =  input->GetNRows("SCPB");
    Int_t number_ec =  input->GetNRows("ECPB"); 

    TString partId="not recognized";

    if (number_dc != 0) {
      if (k==0 && 
	  t->Status(0)>0 && t->Status(0)<100 && t->Charge(0) == -1 &&  number_cc != 0 && 
	  number_ec != 0 && number_sc != 0 && t->StatCC(0) > 0 && t->StatSC(0) > 0 && 
	  t->StatDC(0) > 0 && t->StatEC(0) > 0 && t->DCStatus(0) > 0 && t->SCStatus(0) == 33 &&
	  t->Nphe(0) > (t->Sector(0)==0||t->Sector(0)==1)*25+(t->Sector(0)==2)*26+(t->Sector(0)==3)*21+(t->Sector(0)==4||t->Sector(0)==5)*28 &&
	  (t->TimeEC(0) - t->TimeSC(0) - (t->PathEC(0)-t->PathSC(0))/30) < 5*0.35 &&
	  (t->TimeEC(0) - t->TimeSC(0) - (t->PathEC(0)-t->PathSC(0))/30) > -5*0.35 &&
	  t->Eout(0) != 0 && t->Ein(0) > 0.06 && t->FidCheckCut() == 1) {
	  
	  //U,V,W coordinates
	  Float_t ex=0., wy=0., zd=0., yu=0., ve=0., wu=0., xi=0., yi=0., zi=0., ec_phy=0., phy=0.;
	  Float_t rot[3][3];
	  Float_t ec_the=0.4363323, ylow = -182.974, yhi = 189.956, tgrho = 1.95325, sinrho = 0.8901256, cosrho = 0.455715;
	  ex = t->XEC(0);
	  wy = t->YEC(0);
	  zd = t->ZEC(0);
	  phy = TMath::ATan2(wy,ex)*57.29578;  
	  if (phy < 0.) {
	    phy = phy + 360;
	  }
	  phy = phy+30.;
	  if (phy > 360.){
	    phy = phy - 360.;
	  }
	  ec_phy = ((Int_t) (phy/60.))*1.0471975;  
	  rot[0][0] = TMath::Cos(ec_the)*TMath::Cos(ec_phy);rot[0][1] = -TMath::Sin(ec_phy); 
	  rot[0][2] = TMath::Sin(ec_the)*TMath::Cos(ec_phy);rot[1][0] = TMath::Cos(ec_the)*TMath::Sin(ec_phy);	  
	  rot[1][1] = TMath::Cos(ec_phy); rot[1][2] = TMath::Sin(ec_the)*TMath::Sin(ec_phy); 	  
	  rot[2][0] = -TMath::Sin(ec_the); rot[2][1] = 0.;rot[2][2] = TMath::Cos(ec_the);    
	  yi = ex*rot[0][0]+wy*rot[1][0]+zd*rot[2][0];xi = ex*rot[0][1]+wy*rot[1][1]+zd*rot[2][1];     
	  zi = ex*rot[0][2]+wy*rot[1][2]+zd*rot[2][2];zi = zi-510.32 ; yu = (yi-ylow)/sinrho; 
	  ve = (yhi-ylow)/tgrho - xi + (yhi-yi)/tgrho;wu = ((yhi-ylow)/tgrho + xi + (yhi-yi)/tgrho)/2./cosrho;
	  
	  if (yu > 40 && yu < 410 && ve < 370 && wu < 405) {
	      if (dataSimOpt == "data") {
		if (t->Etot(0)/0.27 > (t->Sector(0)==0||t->Sector(0)==1)*(1.05*t->Momentum(0) - 0.46) + 
		    (t->Sector(0)==2||t->Sector(0)==4||t->Sector(0)==5)*(1.1*t->Momentum(0) - 0.43) + 
		    (t->Sector(0)==3)*(1.07*t->Momentum(0) -0.43) &&
		    t->Etot(0)/0.27 < (t->Sector(0)==0||t->Sector(0)==1)*(1.05*t->Momentum(0) + 0.18) + 
		    (t->Sector(0)==2||t->Sector(0)==4||t->Sector(0)==5)*(1.1*t->Momentum(0) + 0.18) + 
		    (t->Sector(0)==3)*(1.07*t->Momentum(0) + 0.18) &&
		    (t->Ein(0)/0.27 + t->Eout(0)/0.27)< (t->Sector(0)==0||t->Sector(0)==1)*(1.11 * t->Momentum(0)) +  
		    (t->Sector(0)==2||t->Sector(0)==5)*(1.19 * t->Momentum(0)) +
		    (t->Sector(0)==3)*(1.15 * t->Momentum(0)) +
		    (t->Sector(0)==4)*(1.22 * t->Momentum(0)) &&
		    (t->Ein(0)/0.27 + t->Eout(0)/0.27) >(t->Sector(0)==0||t->Sector(0)==1)*(0.75 * t->Momentum(0)) +  
		    (t->Sector(0)==2||t->Sector(0)==5)*(0.84 * t->Momentum(0)) +
		    (t->Sector(0)==3)*(0.83 * t->Momentum(0)) +
		    (t->Sector(0)==4)*(0.85 * t->Momentum(0))) {
		  
		  if      (Metal=="C"  && ptrToSampFrackC(t,0) ==1) {partId="electron";}
		  else if (Metal=="Fe" && ptrToSampFrackFe(t,0)==1) {partId="electron";}
		  else if (Metal=="Pb" && ptrToSampFrackPb(t,0)==1) {partId="electron";}
		}
	      } else if (dataSimOpt == "sim") {
		if (t->Etot(0)/0.27 > (t->Sector(0)==0||t->Sector(0)==1)*(1.03*t->Momentum(0) -0.42) + 
		    (t->Sector(0)==2)*(1.05*t->Momentum(0) -0.46) + 
		    (t->Sector(0)==3)*(1.03*t->Momentum(0) -0.44) + 
		    (t->Sector(0)==4)*(1.06*t->Momentum(0) -0.46) +
		    (t->Sector(0)==5)*(1.04*t->Momentum(0) -0.47) &&
		    t->Etot(0)/0.27 < (t->Sector(0)==0||t->Sector(0)==1||t->Sector(0)==2)*(1.05*t->Momentum(0) + 0.21) + 
		    (t->Sector(0)==3)*(1.03*t->Momentum(0) + 0.23) + 
		    (t->Sector(0)==4)*(1.06*t->Momentum(0) + 0.20) +
		    (t->Sector(0)==5)*(1.04*t->Momentum(0) + 0.22) &&
		    (t->Ein(0)/0.27 + t->Eout(0)/0.27)< (t->Sector(0)==0||t->Sector(0)==1)*(1.13 * t->Momentum(0)) +  
		    (t->Sector(0)==2||t->Sector(0)==3||t->Sector(0)==5)*(1.14*t->Momentum(0)) +
		    (t->Sector(0)==4)*(1.15*t->Momentum(0)) &&
		    (t->Ein(0)/0.27 + t->Eout(0)/0.27) >(t->Sector(0)==0||t->Sector(0)==1)*(0.79 * t->Momentum(0)) +  
		    (t->Sector(0)==2||t->Sector(0)==5)*(0.79 * t->Momentum(0)) +
		    (t->Sector(0)==3)*(0.79 * t->Momentum(0)) +
		    (t->Sector(0)==4)*(0.79 * t->Momentum(0))) {

		  if (Metal == "C" && ptrToSampFrackC_sim(t,0) == 1) {
		    partId = "electron";
		  } else if (Metal == "Fe" && ptrToSampFrackFe_sim(t,0) == 1) {
		    partId = "electron";
		  } else if (Metal == "Pb" && ptrToSampFrackPb_sim(t,0) == 1) {
		    partId = "electron";
		  } else if (Metal == "D2" && ptrToSampFrackD2_sim(t,0) == 1) {
		    partId = "electron";
		  }
		}
	      }
	  }
	}
      
      if (k > 0) {
	if (t->Status(k)>0 &&  t->Status(k)<100 && t->Charge(k)==1 &&  number_cc != 0 && 
	    number_ec != 0 &&  number_sc != 0 &&  t->StatCC(k)>0 && t->StatSC(k)>0 && 
	    t->StatDC(k)>0 && t->StatEC(k)>0 && t->DCStatus(k)>0 && t->SCStatus(k) == 33 &&   
	    t->Nphe(k)>(t->Sector(k)==0||t->Sector(k)==1)*25+(t->Sector(k)==2)*26+
	    (t->Sector(k)==3)*21+(t->Sector(k)==4||t->Sector(k)==5)*28 &&
	    (t->TimeEC(k)-t->TimeSC(k)-(t->PathEC(k)-t->PathSC(k))/30) < 5*0.35  &&
	    (t->TimeEC(k)-t->TimeSC(k)-(t->PathEC(k)-t->PathSC(k))/30) > -5*0.35 &&
	    t->Eout(k) != 0 &&  t->Ein(k)>0.06  &&  t->FidCheckCut() == 1)
	  { 
	    //U,V,W coordinates
	    Float_t ex=0., wy=0., zd=0., yu=0., ve=0., wu=0., xi=0., yi=0., zi=0., ec_phy=0., phy=0.; Float_t rot[3][3];
	    Float_t ec_the=0.4363323, ylow   = -182.974, yhi = 189.956, tgrho= 1.95325, sinrho = 0.8901256, cosrho = 0.455715;
	    ex = t->XEC(k); wy = t->YEC(k);zd = t->ZEC(k);
	    phy = TMath::ATan2(wy,ex)*57.29578;  
	    if(phy<0.){phy = phy + 360;}phy = phy+30.;if(phy>360.){phy = phy-360.;}ec_phy = ((Int_t) (phy/60.))*1.0471975;  
	    rot[0][0] = TMath::Cos(ec_the)*TMath::Cos(ec_phy);rot[0][1] = -TMath::Sin(ec_phy); 
	    rot[0][2] = TMath::Sin(ec_the)*TMath::Cos(ec_phy);rot[1][0] = TMath::Cos(ec_the)*TMath::Sin(ec_phy);	  
	    rot[1][1] = TMath::Cos(ec_phy); rot[1][2] = TMath::Sin(ec_the)*TMath::Sin(ec_phy); 	  
	    rot[2][0] = -TMath::Sin(ec_the); rot[2][1] = 0.;rot[2][2] = TMath::Cos(ec_the);    
	    yi = ex*rot[0][0]+wy*rot[1][0]+zd*rot[2][0];xi = ex*rot[0][1]+wy*rot[1][1]+zd*rot[2][1];     
	    zi = ex*rot[0][2]+wy*rot[1][2]+zd*rot[2][2];zi = zi-510.32 ; yu = (yi-ylow)/sinrho; 
	    ve = (yhi-ylow)/tgrho - xi + (yhi-yi)/tgrho;wu = ((yhi-ylow)/tgrho + xi + (yhi-yi)/tgrho)/2./cosrho;
	    
	    if (yu>40 && yu<410 && ve < 370 && wu < 405){
	      
	      if (dataSimOpt=="data"){
		if (t->Etot(k)/0.27 > (t->Sector(k)==0||t->Sector(k)==1)*(1.05*t->Momentum(k) -0.46) + 
		    (t->Sector(k)==2||t->Sector(k)==4||t->Sector(k)==5)*(1.1*t->Momentum(k) -0.43) + 
		    (t->Sector(k)==3)*(1.07*t->Momentum(k) -0.43) &&
		    t->Etot(k)/0.27 < (t->Sector(k)==0||t->Sector(k)==1)*(1.05*t->Momentum(k) + 0.18) + 
		    (t->Sector(k)==2||t->Sector(k)==4||t->Sector(k)==5)*(1.1*t->Momentum(k) + 0.18) + 
		    (t->Sector(k)==3)*(1.07*t->Momentum(k) + 0.18) &&
		    (t->Ein(k)/0.27 + t->Eout(k)/0.27)< (t->Sector(k)==0||t->Sector(k)==1)*(1.11 * t->Momentum(k)) +  
		    (t->Sector(k)==2||t->Sector(k)==5)*(1.19 * t->Momentum(k)) +
		    (t->Sector(k)==3)*(1.15 * t->Momentum(k)) +
		    (t->Sector(k)==4)*(1.22 * t->Momentum(k)) &&
		    (t->Ein(k)/0.27 + t->Eout(k)/0.27) >(t->Sector(k)==0||t->Sector(k)==1)*(0.75 * t->Momentum(k)) +  
		    (t->Sector(k)==2||t->Sector(k)==5)*(0.84 * t->Momentum(k)) +
		    (t->Sector(k)==3)*(0.83 * t->Momentum(k)) +
		    (t->Sector(k)==4)*(0.85 * t->Momentum(k))) {
		  if      (Metal=="C"  && ptrToSampFrackC(t,k) ==1) {partId="positron";}
		  else if (Metal=="Fe" && ptrToSampFrackFe(t,k)==1) {partId="positron";}
		  else if (Metal=="Pb" && ptrToSampFrackPb(t,k)==1) {partId="positron";}
		  else if (Metal=="D2" && ptrToSampFrackD2(t,k)==1) {partId="positron";}
		}	
	      }	else if (dataSimOpt=="sim") {
		if (t->Etot(k)/0.27 > (t->Sector(k)==0||t->Sector(k)==1)*(1.03*t->Momentum(k) -0.42) + 
		    (t->Sector(k)==2)*(1.05*t->Momentum(k) -0.46) + 
		    (t->Sector(k)==3)*(1.03*t->Momentum(k) -0.44) + 
		    (t->Sector(k)==4)*(1.06*t->Momentum(k) -0.46) +
		    (t->Sector(k)==5)*(1.04*t->Momentum(k) -0.47) &&
		    t->Etot(k)/0.27 < (t->Sector(k)==0||t->Sector(k)==1||t->Sector(k)==2)*(1.05*t->Momentum(k) + 0.21) + 
		    (t->Sector(k)==3)*(1.03*t->Momentum(k) + 0.23) + 
		    (t->Sector(k)==4)*(1.06*t->Momentum(k) + 0.20) +
		    (t->Sector(k)==5)*(1.04*t->Momentum(k) + 0.22) &&
		    (t->Ein(k)/0.27 + t->Eout(k)/0.27)< (t->Sector(k)==0||t->Sector(k)==1)*(1.13 * t->Momentum(k)) +  
		    (t->Sector(k)==2||t->Sector(k)==3||t->Sector(k)==5)*(1.14*t->Momentum(k)) +
		    (t->Sector(k)==4)*(1.15*t->Momentum(k)) &&
		    (t->Ein(k)/0.27 + t->Eout(k)/0.27) >(t->Sector(k)==0||t->Sector(k)==1)*(0.79 * t->Momentum(k)) +  
		    (t->Sector(k)==2||t->Sector(k)==5)*(0.79 * t->Momentum(k)) +
		    (t->Sector(k)==3)*(0.79 * t->Momentum(k)) +
		    (t->Sector(k)==4)*(0.79 * t->Momentum(k))) {  
		  if      (Metal=="C"  && ptrToSampFrackC_sim(t,k) ==1) {partId="positron";}
		  else if (Metal=="Fe" && ptrToSampFrackFe_sim(t,k)==1) {partId="positron";}
		  else if (Metal=="Pb" && ptrToSampFrackPb_sim(t,k)==1) {partId="positron";}
		  else if (Metal=="D2" && ptrToSampFrackD2_sim(t,k)==1) {partId="positron";}
		}
	      }
	      
	    }
	  }
	
	if(partId != "positron")
	  {
	    if (t->Charge(k) == 1 && t->Status(k) > 0 && t->Status(k) < 100 &&  t->StatDC(k) > 0 && t->DCStatus(k) > 0)
	      {
		if (t->Momentum(k)>=2.7)
		  {
		    if (number_cc != 0 && t->StatCC(k) > 0 && t->Nphe(k) > 25 && t->Chi2CC(k) < 5 / 57.3  && 
			t->TimeCorr4(0.139,k)+0.08 < 0.35 && t->TimeCorr4(0.139,k)+0.08 > -0.35    )
		      {  partId = "high energy pion +";  }
		  }
		else if (t->Momentum(k) < 2.7)
		  {
		    if (number_sc != 0 && t->StatSC(k) > 0 &&
			((t->Momentum(k)>0.00 && t->Momentum(k)<=0.25 &&  
			  t->TimeCorr4(0.139,k)+0.08>=lines[0][0] && t->TimeCorr4(0.139,k)+0.08<=lines[0][1]) ||
			 (t->Momentum(k)>0.25 && t->Momentum(k)<=0.50 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[1][0] && t->TimeCorr4(0.139,k)+0.08<=lines[1][1]) ||
			 (t->Momentum(k)>0.50 && t->Momentum(k)<=0.75 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[2][0] && t->TimeCorr4(0.139,k)+0.08<=lines[2][1]) ||
			 (t->Momentum(k)>0.75 && t->Momentum(k)<=1.00 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[3][0] && t->TimeCorr4(0.139,k)+0.08<=lines[3][1]) ||
			 (t->Momentum(k)>1.00 && t->Momentum(k)<=1.25 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[4][0] && t->TimeCorr4(0.139,k)+0.08<=lines[4][1]) ||  
			 (t->Momentum(k)>1.25 && t->Momentum(k)<=1.50 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[5][0] && t->TimeCorr4(0.139,k)+0.08<=lines[5][1]) ||
			 (t->Momentum(k)>1.50 && t->Momentum(k)<=1.75 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[6][0] && t->TimeCorr4(0.139,k)+0.08<=lines[6][1]) ||
			 (t->Momentum(k)>1.75 && t->Momentum(k)<=2.00 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[7][0] && t->TimeCorr4(0.139,k)+0.08<=lines[7][1]) ||
			 (t->Momentum(k)>2.00 && t->Momentum(k)<=2.25 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[8][0] && t->TimeCorr4(0.139,k)+0.08<=lines[8][1]) ||
			 (t->Momentum(k)>2.25 && t->Momentum(k)<=2.50 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[9][0] && t->TimeCorr4(0.139,k)+0.08<=lines[9][1] && t->Mass2(k) < 0.5) ||  
			 (t->Momentum(k)>2.50 && t->Momentum(k)<2.70 && 
			  t->TimeCorr4(0.139,k)+0.08>=lines[10][0] && t->TimeCorr4(0.139,k)+0.08<=lines[10][1] && t->Mass2(k) < 0.4) || 
			 (t->Momentum(k) > 2.7 &&  t->Momentum(k) <= 3.3 &&
			  t->TimeCorr4(0.139,k)+0.08 >= -0.5 && t->TimeCorr4(0.139,k)+0.08 <= 0.4 && t->Mass2(k) < 0.4)  || 
			 (t->Momentum(k) > 3.3 && t->Momentum(k) <= 3.7 &&
			  t->TimeCorr4(0.139,k)+0.08 >= -0.32 && t->TimeCorr4(0.139,k)+0.08 <= 0.32 && t->Mass2(k) < 0.37) || 
			 (t->Momentum(k) > 3.7  &&
			  t->TimeCorr4(0.139,k)+0.08 >= -0.3 && t->TimeCorr4(0.139,k)+0.08 <= 0.3 && t->Mass2(k) < 0.37)))
		      {
			partId = "pion +";
		      }	
		  } //end cicle for momentum < 2.7
	      } //end of if (partId != "positron")
	  } //end cicle for positive particles  
      } //end cicle for k>0  
    } //end cicle for number_dc != 0
    return partId;
}

TVector3 *uvwCoor(TIdentificator* t){
  Float_t ex=0.;Float_t wy=0.;Float_t zd=0.;Float_t yu=0.;Float_t ve=0.;Float_t wu=0.;Float_t xi=0.;  
  Float_t yi=0.;Float_t zi=0.;Float_t ec_phy = 0.;Float_t phy = 0.;Float_t rot[3][3];Float_t ec_the = 0.4363323; 
  Float_t ylow   = -182.974;Float_t yhi    = 189.956;Float_t tgrho  = 1.95325;Float_t sinrho = 0.8901256; 
  Float_t cosrho = 0.455715;ex = t->XEC(0);wy = t->YEC(0);zd = t->ZEC(0);phy = TMath::ATan2(wy,ex)*57.29578;  
  if(phy<0.){phy = phy + 360;}phy = phy+30.;if(phy>360.){phy = phy-360.;}ec_phy = ((Int_t) (phy/60.))*1.0471975;  
  rot[0][0] = TMath::Cos(ec_the)*TMath::Cos(ec_phy);rot[0][1] = -TMath::Sin(ec_phy); 
  rot[0][2] = TMath::Sin(ec_the)*TMath::Cos(ec_phy);rot[1][0] = TMath::Cos(ec_the)*TMath::Sin(ec_phy);	  
  rot[1][1] = TMath::Cos(ec_phy);rot[1][2] = TMath::Sin(ec_the)*TMath::Sin(ec_phy); 	  
  rot[2][0] = -TMath::Sin(ec_the);rot[2][1] = 0.;rot[2][2] = TMath::Cos(ec_the);    
  yi = ex*rot[0][0]+wy*rot[1][0]+zd*rot[2][0];xi = ex*rot[0][1]+wy*rot[1][1]+zd*rot[2][1];     
  zi = ex*rot[0][2]+wy*rot[1][2]+zd*rot[2][2];zi = zi-510.32 ;yu = (yi-ylow)/sinrho; 
  ve = (yhi-ylow)/tgrho - xi + (yhi-yi)/tgrho;wu = ((yhi-ylow)/tgrho + xi + (yhi-yi)/tgrho)/2./cosrho;
  TVector3 *uvwCoordinates = new TVector3(yu,ve,wu);
  return uvwCoordinates;
}

Int_t SampFrackCheck_C(TIdentificator* t, Int_t j){
  // values obtained from analyzer, original ones
  const Double_t kMeanCPara[6][3]={{0.252164,0.0122263,-0.000793937},
				   {0.278574,0.0187482,-0.00238217},
				   {0.262079,0.0230685,-0.00354741},
				   {0.251108,0.0201568,-0.00332367},
				   {0.263396,0.00955238,-0.00102038},
				   {0.255245,0.0232659,-0.00304798}};
  
  const Double_t kSigmaCPara[6][2]={{9.55113e-03,3.40672e-02},
				    {1.39889e-02,3.74682e-02},
				    {9.32762e-03,2.90046e-02},
				    {8.21055e-03,2.98893e-02},
				    {2.25684e-02,3.06508e-02},
                       {1.17254e-02,3.64221e-02}};
  Int_t ret=0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s    = t->Sector(j);
  Double_t MeanE  = kMeanCPara[s][0] + kMeanCPara[s][1]*p + kMeanCPara[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaCPara[s][0]*kSigmaCPara[s][0] + kSigmaCPara[s][1]*kSigmaCPara[s][1]/p);
  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE)
    {ret=1;}
  return ret;
}

Int_t SampFrackCheck_C_sim(TIdentificator* t, Int_t j){
  // values obtained for SM electrons and SM simulations (No EC cuts involved)
  const Double_t kMeanCPara[6][3]={
				   {0.250469, 0.015964, -0.00389408 }, 
				   {0.251445, 0.0159875, -0.00375825},
				   {0.250031, 0.0178331, -0.00422464},
				   {0.25105, 0.0152426, -0.00390999},
				   {0.25027, 0.01694, -0.00381344},
				   {0.249087, 0.0150609, -0.0034316}};
  const Double_t kSigmaCPara[6][2]={
				    {0.00510237, 0.0248174 }, 
				    {0.00431604, 0.0244632},
				    {8.4798e-08, 0.024983},
				    {0.00255027, 0.0254091},
				    {0.00399372, 0.0249107},
				    {0.00552327, 0.0246847}};
  Int_t ret=0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s    = t->Sector(j);
  Double_t MeanE  = kMeanCPara[s][0] + kMeanCPara[s][1]*p + kMeanCPara[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaCPara[s][0]*kSigmaCPara[s][0] + kSigmaCPara[s][1]*kSigmaCPara[s][1]/p);
  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE)
    {ret=1;}
  return ret;
}

Int_t SampFrackCheck_D2(TIdentificator* t, Int_t j){
  // values obtained for SM electrons and SM simulations (No EC cuts involved)
  const Double_t kMeanD2Para[6][3]={{0.24876 , 0.0179894, -0.00442957 }, 
				    {0.248957, 0.0181533, -0.00416637},
				    {0.248164, 0.0188304, -0.00427462},
				    {0.250525, 0.0161461, -0.0041662},
				    {0.248031, 0.0196832, -0.00456827},
				    {0.249069, 0.015629 , -0.00363472}};

  const Double_t kSigmaD2Para[6][2]={{0.00399225, 0.0249298 }, 
				     {0.00538627, 0.0242045},
				     {0.00335732, 0.0247301},
				     {0.00346977, 0.0251755},
				     {0.00354094, 0.0252441},
				     {0.00274538, 0.0254185}};

  Int_t ret = 0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s = t->Sector(j);
  Double_t MeanE  = kMeanD2Para[s][0] + kMeanD2Para[s][1]*p + kMeanD2Para[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaD2Para[s][0]*kSigmaD2Para[s][0] + kSigmaD2Para[s][1]*kSigmaD2Para[s][1]/p);

  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE) ret=1;
  
  return ret;
}

Int_t SampFrackCheck_D2_sim(TIdentificator* t, Int_t j){
  // values obtained for SM electrons and SM simulations (No EC cuts involved)
  const Double_t kMeanD2Para[6][3]={
				    {0.24876 , 0.0179894, -0.00442957 }, 
				    {0.248957, 0.0181533, -0.00416637},
				    {0.248164, 0.0188304, -0.00427462},
				    {0.250525, 0.0161461, -0.0041662},
				    {0.248031, 0.0196832, -0.00456827},
				    {0.249069, 0.015629 , -0.00363472}};

  const Double_t kSigmaD2Para[6][2]={
				     {0.00399225, 0.0249298 }, 
				     {0.00538627, 0.0242045},
				     {0.00335732, 0.0247301},
				     {0.00346977, 0.0251755},
				     {0.00354094, 0.0252441},
				     {0.00274538, 0.0254185}};

  Int_t ret=0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s    = t->Sector(j);
  Double_t MeanE  = kMeanD2Para[s][0] + kMeanD2Para[s][1]*p + kMeanD2Para[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaD2Para[s][0]*kSigmaD2Para[s][0] + kSigmaD2Para[s][1]*kSigmaD2Para[s][1]/p);
  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE)
    {ret=1;}
  return ret;
}

Int_t SampFrackCheck_Fe(TIdentificator* t, Int_t j){
//original, from Analizer
const Double_t kMeanFePara[6][3]={{0.222404,0.0222688,-0.0024153},
                       		{0.234623,0.0194985,-0.00208357},
                      		{0.252287,0.024248,-0.00338846},
                       		{0.250946,0.0208409,-0.00326824},
                       		{0.271956,0.0118487,-0.00187084},
                       		{0.252613,0.022819,-0.00311242}};

const Double_t kSigmaFePara[6][2]={{9.23027e-03,2.98343e-02},
                       		 {8.66367e-03,3.08858e-02},
                       		 {1.07826e-02,2.63854e-02},
                       		 {7.22581e-03,2.98809e-02},
                       		 {1.84073e-02,3.48029e-02},
                       		 {4.11461e-03,3.55081e-02}};

  Int_t ret=0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s = t->Sector(j);
  Double_t MeanE  = kMeanFePara[s][0] + kMeanFePara[s][1]*p + kMeanFePara[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaFePara[s][0]*kSigmaFePara[s][0] + kSigmaFePara[s][1]*kSigmaFePara[s][1]/p);
  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE)
  {ret=1;}
  return ret;
}

Int_t SampFrackCheck_Fe_sim(TIdentificator* t, Int_t j){
//values obtained for SM electrons and SM simulations (No EC cuts involved)
const Double_t kMeanFePara[6][3]={
{0.249113, 0.0172746, -0.00420656 }, 
{0.248658, 0.0185365, -0.00428943},
{0.249016, 0.0185937, -0.00438778},
{0.247588, 0.0196735, -0.00515405},
{0.247964, 0.0196745, -0.00455197},
{0.246463, 0.0184054, -0.00431434}};

const Double_t kSigmaFePara[6][2]={
{0.00431529, 0.0251379 }, 
{0.00540396, 0.0241749},
{0.00417432, 0.0249617},
{0.00431868, 0.0250086},
{0.0038769, 0.0251642},
{0.00444093, 0.025143}};

  Int_t ret=0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s = t->Sector(j);
  Double_t MeanE  = kMeanFePara[s][0] + kMeanFePara[s][1]*p + kMeanFePara[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaFePara[s][0]*kSigmaFePara[s][0] + kSigmaFePara[s][1]*kSigmaFePara[s][1]/p);
  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE)
  {ret=1;}
  return ret;
}

Int_t SampFrackCheck_Pb(TIdentificator* t, Int_t j){
//original, from Analyzer
const Double_t kMeanPbPara[6][3]={{0.253431,0.0138251,-0.0014016},
                       		{0.249059,0.0147784,-0.00148693},
                       		{0.254573,0.022589,-0.00305686},
		       		{0.255589,0.0190419,-0.00305263},
		       		{0.276739,0.0111585,-0.00175784},
		       		{0.262587,0.0191659,-0.0026264}};

const Double_t kSigmaPbPara[6][2]={{7.67408e-03,3.54391e-02},
                       		 {7.52798e-03,3.38371e-02},
                       		 {8.13241e-03,2.77300e-02},
                       		 {7.20303e-03,3.03627e-02},
                       		 {1.80841e-02,3.53020e-02},
		       		 {1.99220e-03,3.76172e-02}};

  Int_t ret=0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s    = t->Sector(j);
  Double_t MeanE  = kMeanPbPara[s][0] + kMeanPbPara[s][1]*p + kMeanPbPara[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaPbPara[s][0]*kSigmaPbPara[s][0] + kSigmaPbPara[s][1]*kSigmaPbPara[s][1]/p);
  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE)
  {ret=1;}
  return ret;
}

Int_t SampFrackCheck_Pb_sim(TIdentificator* t, Int_t j) {
  // values obtained for SM electrons and SM simulations (No EC cuts involved)
  const Double_t kMeanPbPara[6][3]={
				    {0.247887, 0.0188033, -0.00463279 }, 
				    {0.247159, 0.0206521, -0.00493913},
				    {0.247663, 0.0197017, -0.00459223},
				    {0.249099, 0.0173088, -0.00436998},
				    {0.249669, 0.0175364, -0.00392209},
				    {0.247958, 0.0165727, -0.00381158}};
  
  const Double_t kSigmaPbPara[6][2]={
				     {0.00358101, 0.0253111 }, 
				     {0.00417953, 0.0245174},
				     {1.8082e-07, 0.0253269},
				     {0.00339505, 0.0254005},
				     {0.00482576, 0.0250319},
				     {0.00332387, 0.0253196}};
  
  Int_t ret=0;
  Double_t E = TMath::Max(t->Etot(j),t->Ein(j)+t->Eout(j));
  Double_t p = t->Momentum(j);
  Int_t s    = t->Sector(j);
  Double_t MeanE  = kMeanPbPara[s][0] + kMeanPbPara[s][1]*p + kMeanPbPara[s][2]*p*p;
  Double_t SigmaE = TMath::Sqrt(kSigmaPbPara[s][0]*kSigmaPbPara[s][0] + kSigmaPbPara[s][1]*kSigmaPbPara[s][1]/p);
  if (TMath::Abs(E/p - MeanE)< 2.5*SigmaE)
    {ret=1;}
  return ret;
}

Int_t getVC_RD_Shift_C(TIdentificator* t ){
  
  Float_t ele_liq_lim_RD[6][2];   Float_t ele_sol_lim_RD[6][2];
  
  ele_liq_lim_RD[0][0] = -32.;     ele_liq_lim_RD[0][1] = -28.;     ele_liq_lim_RD[5][0] = -32.5;
  ele_liq_lim_RD[5][1] = -28.5;    ele_liq_lim_RD[4][0] = -32.7;    ele_liq_lim_RD[4][1] = -28.7;
  ele_liq_lim_RD[3][0] = -32.2;    ele_liq_lim_RD[3][1] = -28.2;    ele_liq_lim_RD[2][0] = -31.7;
  ele_liq_lim_RD[2][1] = -27.7;    ele_liq_lim_RD[1][0] = -31.5;    ele_liq_lim_RD[1][1] = -27.5;

  ele_sol_lim_RD[0][0] = -26.1;    ele_sol_lim_RD[0][1] = -23.1;    ele_sol_lim_RD[5][0] = -26.6;  
  ele_sol_lim_RD[5][1] = -23.6;    ele_sol_lim_RD[4][0] = -26.8;    ele_sol_lim_RD[4][1] = -23.8; 
  ele_sol_lim_RD[3][0] = -26.3;    ele_sol_lim_RD[3][1] = -23.3;    ele_sol_lim_RD[2][0] = -25.8; 
  ele_sol_lim_RD[2][1] = -22.8;    ele_sol_lim_RD[1][0] = -25.6;    ele_sol_lim_RD[1][1] = -22.6;    
  
  Int_t p_vertex_cut_elec_RD = 0;
  Int_t n_sector_RD = t->Sector(0,0);
  
  if (t->Z(0,0) >= ele_liq_lim_RD[n_sector_RD][0] &&
      t->Z(0,0) <= ele_liq_lim_RD[n_sector_RD][1])
    {
                p_vertex_cut_elec_RD = 1;
    }
  if (t->Z(0,0) >= ele_sol_lim_RD[n_sector_RD][0] &&
      t->Z(0,0) <= ele_sol_lim_RD[n_sector_RD][1])
    {
      p_vertex_cut_elec_RD = 2;
    }
  
  return p_vertex_cut_elec_RD; 
}

Int_t getVC_RD_Shift_Fe(TIdentificator* t ){

    Float_t ele_liq_lim_RD[6][2];    Float_t ele_sol_lim_RD[6][2];

    ele_liq_lim_RD[0][0] = -32.1;    ele_liq_lim_RD[0][1] = -28.1;    ele_liq_lim_RD[5][0] = -32.6;
    ele_liq_lim_RD[5][1] = -28.6;    ele_liq_lim_RD[4][0] = -32.8;    ele_liq_lim_RD[4][1] = -28.8;
    ele_liq_lim_RD[3][0] = -32.3;    ele_liq_lim_RD[3][1] = -28.3;    ele_liq_lim_RD[2][0] = -31.8;
    ele_liq_lim_RD[2][1] = -27.8;    ele_liq_lim_RD[1][0] = -31.6;    ele_liq_lim_RD[1][1] = -27.6;

    ele_sol_lim_RD[0][0] = -26.3;    ele_sol_lim_RD[0][1] = -23.3;    ele_sol_lim_RD[5][0] = -26.8;
    ele_sol_lim_RD[5][1] = -23.8;    ele_sol_lim_RD[4][0] = -27.;     ele_sol_lim_RD[4][1] = -24.;
    ele_sol_lim_RD[3][0] = -26.5;    ele_sol_lim_RD[3][1] = -23.5;    ele_sol_lim_RD[2][0] = -26.;
    ele_sol_lim_RD[2][1] = -23.;     ele_sol_lim_RD[1][0] = -25.8;    ele_sol_lim_RD[1][1] = -22.8;
 
    Int_t p_vertex_cut_elec_RD = 0;
    Int_t n_sector_RD = t->Sector(0,0);

    if (t->Z(0,0) >= ele_liq_lim_RD[n_sector_RD][0] &&
        t->Z(0,0) <= ele_liq_lim_RD[n_sector_RD][1])
        {
                p_vertex_cut_elec_RD = 1;
        }
    if (t->Z(0,0) >= ele_sol_lim_RD[n_sector_RD][0] &&
	t->Z(0,0) <= ele_sol_lim_RD[n_sector_RD][1])
        {
         	p_vertex_cut_elec_RD = 2;
	}

return p_vertex_cut_elec_RD;

}

Int_t getVC_RD_Shift_Pb(TIdentificator* t ){

    Float_t ele_liq_lim_RD[6][2];    Float_t ele_sol_lim_RD[6][2];

    ele_liq_lim_RD[0][0] = -32.;     ele_liq_lim_RD[0][1] = -28.;     ele_liq_lim_RD[5][0] = -32.5;
    ele_liq_lim_RD[5][1] = -28.5;    ele_liq_lim_RD[4][0] = -32.7;    ele_liq_lim_RD[4][1] = -28.7;
    ele_liq_lim_RD[3][0] = -32.2;    ele_liq_lim_RD[3][1] = -28.2;    ele_liq_lim_RD[2][0] = -31.7;
    ele_liq_lim_RD[2][1] = -27.7;    ele_liq_lim_RD[1][0] = -31.5;    ele_liq_lim_RD[1][1] = -27.5;

    ele_sol_lim_RD[0][0] = -26.3;    ele_sol_lim_RD[0][1] = -23.3;    ele_sol_lim_RD[5][0] = -26.8;
    ele_sol_lim_RD[5][1] = -23.8;    ele_sol_lim_RD[4][0] = -27.;     ele_sol_lim_RD[4][1] = -24.;
    ele_sol_lim_RD[3][0] = -26.5;    ele_sol_lim_RD[3][1] = -23.5;    ele_sol_lim_RD[2][0] = -26.;
    ele_sol_lim_RD[2][1] = -23.;     ele_sol_lim_RD[1][0] = -25.8;    ele_sol_lim_RD[1][1] = -22.8;

    Int_t p_vertex_cut_elec_RD = 0;
    Int_t n_sector_RD = t->Sector(0,0);

    if (t->Z(0,0) >= ele_liq_lim_RD[n_sector_RD][0] &&
        t->Z(0,0) <= ele_liq_lim_RD[n_sector_RD][1])
        {
                p_vertex_cut_elec_RD = 1;
        }
    if (t->Z(0,0) >= ele_sol_lim_RD[n_sector_RD][0] &&
	t->Z(0,0) <= ele_sol_lim_RD[n_sector_RD][1])
        {
         	p_vertex_cut_elec_RD = 2;
	}

return p_vertex_cut_elec_RD;
}


TVector3 *GetCorrectedVert(TIdentificator* t) {
  TVector3 *V_corr = new TVector3(); TVector3 RotatedVertPos(t->X(0),t->Y(0),t->Z(0));    
  TVector3 RotatedVertDir(t->Px(0),t->Py(0),t->Pz(0)); TVector3 TargetPos(0.043,-0.33,0);
  Float_t sect = t->Sector(0);
  RotatedVertPos.RotateZ(-TMath::DegToRad()*60.*sect); RotatedVertDir.RotateZ(-TMath::DegToRad()*60.*sect);
  TargetPos.RotateZ(-TMath::DegToRad()*60.*sect);
  Float_t ShiftLength = (TargetPos.X()-RotatedVertPos.X())/RotatedVertDir.X();
  RotatedVertDir = ShiftLength*RotatedVertDir; RotatedVertPos = RotatedVertPos+RotatedVertDir;
  V_corr->SetX((RotatedVertPos-TargetPos).X());V_corr->SetY((RotatedVertPos-TargetPos).Y());
  V_corr->SetZ(RotatedVertPos.Z());
  return V_corr;
}

Int_t getVC_TM_C (Double_t ZC) {
  Int_t p_vertex_cut_elec_TM = 0;
  if (ZC >= -31.8  && ZC <= -28.4)   { p_vertex_cut_elec_TM = 1; } //LT          
  if (ZC >= -25.33 && ZC <= -24.10)  { p_vertex_cut_elec_TM = 2; } //ST              
  return p_vertex_cut_elec_TM;
}

Int_t getVC_TM_Fe(Double_t ZC) {
  Int_t p_vertex_cut_elec_TM = 0;
  if (ZC >= -31.8  && ZC <= -28.4)   { p_vertex_cut_elec_TM = 1; } //LT   
  if (ZC >= -25.65 && ZC <= -24.26)  { p_vertex_cut_elec_TM = 2; } //ST   
  return p_vertex_cut_elec_TM;
}

Int_t getVC_TM_Pb(Double_t ZC) {
  Int_t p_vertex_cut_elec_TM = 0;
  if (ZC >= -31.8  && ZC <= -28.4)    { p_vertex_cut_elec_TM = 1; } //LT  
  if (ZC >= -25.54 && ZC <= -24.36)  { p_vertex_cut_elec_TM = 2; }  //ST     
  return p_vertex_cut_elec_TM;
}

Int_t getVC_RD(Double_t Z) {
  // for simulations is just the center -25 (ST) and -30 (LT) plus and minus 1.5 cm
  Int_t p_vertex_cut_elec_RD = 0;
  if (Z >= -31.5 && Z <= -28.5) {
    p_vertex_cut_elec_RD = 1;
  }
  
  if (Z >= -26.5 && Z <= -23.5) {
    p_vertex_cut_elec_RD = 2;
  }
  return p_vertex_cut_elec_RD;
}

Float_t getPhiPQ(Int_t k, TIdentificator* t, Bool_t kind) {
  //PhiPQ variable as RD defined it 
  Float_t qx, qy, qz, hx, hy, hz;
  Float_t A1, A2,A3, B1,B2,B3;
  Float_t AA, BB, AB;
  Float_t angle;
  if (kind == 0) {
    qx = -t->Px(0,0);
    qy = -t->Py(0,0);
    qz = 5.014 - t->Pz(0,0);
    hx = t->Px(k,0);
    hy = t->Py(k,0);
    hz = t->Pz(k,0);
  } else if (kind==1){
    qx = -t->Px(0,1);
    qy = -t->Py(0,1);
    qz = 5.014 - t->Pz(0,1);
    hx = t->Px(k,1);
    hy = t->Py(k,1);
    hz = t->Pz(k,1);
  }
  
  A1= -qy;
  A2=  qx;
  A3=  0.;
  
  B1 = qy*hz - qz*hy;
  B2 = qz*hx - qx*hz;
  B3 = qx*hy - qy*hx;
  
  AA = A1*A1 + A2*A2 + A3*A3 ;
  BB = B1*B1 + B2*B2 + B3*B3 ;
  AB = A1*B1 + A2*B2 + A3*B3 ;
  
  if (TMath::Abs(AB/TMath::Sqrt(AA*BB)) >= 1.) angle = 0.;
  else angle = TMath::ACos(AB/TMath::Sqrt(AA*BB))*57.2957795;
  
  return angle;
}

Double_t getXf(Int_t k, TIdentificator* t , Bool_t kind) {
  Double_t xf;
  Double_t term1, term2, term3;
  Double_t Mass_pion   = 0.139570 ;
  Double_t NeutronMass = 0.939565;
  
  Double_t  Zh, Q2, W2, Nu, p_pion;
  TVector3 v3p_hadron, v3p_elec_incident, v3p_elec_scat, v3VirtPhoton;
  v3p_elec_incident.SetXYZ(0, 0, 5.014);
  
  if (kind==0) {
    Zh = t->Zh(k);
    Q2 = t->Q2();
    W2 = t->W() * t->W();
    Nu = t->Nu();
    p_pion = t->Momentum(k);
    v3p_hadron.SetXYZ(t->Px(k,0), t->Py(k,0),t->Pz(k,0));
    v3p_elec_scat.SetXYZ(t->Px(0,0), t->Py(0,0),t->Pz(0,0));
    v3VirtPhoton.SetXYZ(-t->Px(0,0), -t->Py(0,0), 5.014-t->Pz(0,0)); // p-p'=q 
  } else if (kind==1){
    Zh = t->Zh(k,1);
    Q2 = t->Q2(1);
    W2 = t->W(1)*t->W(1);
    Nu = t->Nu(1);
    p_pion = t->Momentum(k,1);
    v3p_hadron.SetXYZ(t->Px(k,1), t->Py(k,1),t->Pz(k,1));
    v3p_elec_scat.SetXYZ(t->Px(0,1), t->Py(0,1),t->Pz(0,1));
    v3VirtPhoton.SetXYZ(-t->Px(0,1), -t->Py(0,1), 5.014-t->Pz(0,1)); // p-p'=q 
  }
  Double_t angle;
  angle = v3p_hadron.Angle(v3VirtPhoton);  
  //this angle is in radians 
  
  term1 = Nu*Nu*Zh - TMath::Sqrt(Nu*Nu + Q2)*p_pion*cos(angle);
  term2 = Zh*NeutronMass*Nu*Nu - Zh*Q2*Nu - (NeutronMass + Nu) * term1;
  term3 = (W2 - Mass_pion*Mass_pion) * TMath::Sqrt(Nu*Nu + Q2);
  
  xf = 2*(term2/term3);
  return xf;
}



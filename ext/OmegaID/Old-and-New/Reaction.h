/*************************************************/
/*  Reaction.h                                   */
/*                                               */
/*  Created by Orlando Soto, CCTVAL              */
/*  Modified for omega by Andrés Bórquez, CCTVAL */
/*                                               */
/*************************************************/

#include <vector>
#include <sys/stat.h>
#include <cstdarg>
#include <algorithm>
#include <map>
#include <string>

#include "TSpectrum.h"
#include "Riostream.h"
#include "TApplication.h"
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TClasTool.h"
#include "TIdentificator.h"
#include "TMath.h"
#include "TBenchmark.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TMatrixD.h"
#include "TClonesArray.h"

#include "do_pid.h"
#include "Particle.h"
#include "Combo.h"

class Reaction {
public:
  char name[50];
  char filename[50];
  
  Combo *kPrimary; //primary                                                                                                                           TParticlePDG *kPdgInfo;
  
  std::vector<Particle*> *kSecondary; //all secondary
  std::vector <Combo *> *kCombo; //partial combinations
  std::vector <Combo *> kBkgnd; //background combinations

  static const Int_t kBUFFLIMIT = 100;
  std::vector<TH1F*> hSPid;
  TFile *kOutFile;
  Float_t *kData;
  Float_t *keData;
  TNtuple  *kElecData;
  TTree *kOutData, *kOutBkgnd;
  
  //  TTree *kP4Tree;                                                                                                                                 
  bool fEMatch;
  
  int kPPid;
  int kNSecondary;
  
  std::vector<int>::iterator kSIt;
  std::vector<int> kSPid; //Amount of secondary particles for a given pid.                                                                            
  std::map<int,int> kNSPid; //Amount of secondary pid particles required.                                                                             
  Reaction(){
    strcpy(name, "omega -> pi+ pi- a a"), strcpy(filename, "test_omega_pippimpi0.root");
    init();
  }
  
  Reaction(const char *n,const char *fn,bool fEMatch=false): fEMatch(fEMatch) {
    strcpy(name,n);
    strcpy(filename,fn);
    init();
  }
  
  int store() {
    for (int k = 0; k < kSPid.size(); k++) {
      hSPid[k]->Write("", TObject::kOverwrite);
    }
    kOutBkgnd->Write("", TObject::kOverwrite);
    kElecData->Write("", TObject::kOverwrite);
    return kOutData->Write("",TObject::kOverwrite);
  }
  
  ~Reaction() {
    clear();
    delete[] kSecondary;
    delete[] kCombo;
    delete kOutData;
    delete kOutBkgnd;
    delete[] kData;
    delete[] keData;
    delete P4Arr;
    kOutFile->Close();
    delete kOutFile;
    delete kPdgInfo;
    hSPid.clear();
  }
  
  void clear() {
    for (int k = 0; k < kSPid.size(); k++) {
      kSecondary[k].clear();
      kCombo[k].clear();
    }
  }

  // To store different information modify init() and fill()
  int init() {
    kNSecondary=0;
    kOutFile = new TFile(filename, "recreate");    
    TString varlist = "M:Phx:Phy:Phz:Nu:Q2:Z:Cospq:Pt2:Event:M2_01:M2_02:vzec:z1:z2:z3:W:vxec:vyec:qx1:qy1:qz1:qx2:qy2:qz2:E1:E2:E1c:E2c:x1:y1:x2:y2:TargType:TargTypeO:PhiPQ";

    kElecData = new TNtuple("ElecData", Form("%s", name),"Nu:Q2:Event:vzec:Ee:Pex:Pey:Pez:W");

    kData = new Float_t[varlist.CountChar(':') + 1];
    keData = new Float_t[kElecData->GetNvar()];
    P4Arr = new TClonesArray("TLorentzVector");
    kOutData = new TTree("outdata", Form("%s", name));
    kOutData->Branch("P4", &P4Arr, 6);
    kOutData->Branch("primary", kData, varlist);
    
    kOutBkgnd = kOutData->CloneTree(0);
    kOutBkgnd->SetName("outbkgnd");
    
    return 0;
  }
  
  int fill() {
    fill(kPrimary,kOutData);
  }

  int fill_elec() {
    keData[0] = Nu_prev;
    keData[1] = Q2_prev;
    keData[2] = evnt_prev;
    keData[3] = Zec_prev;
    keData[4] = Ee_prev;
    keData[5] = Pex_prev;
    keData[6] = Pey_prev;
    keData[7] = Pez_prev;
    keData[8] = W_prev;
    kElecData->Fill(keData);
  }

  int fill(Combo *comb,TTree *ttree) {
    Double_t Px = comb->Px();
    Double_t Py = comb->Py();
    Double_t Pz = comb->Pz();
    Double_t E = comb->E();
    Double_t P2 = comb->P2();
    Double_t M2 = comb->M2();
    Double_t M = (M2>=0)?TMath::Sqrt(M2):-1.0;
    Float_t cospq = ((kEbeam-Pez_prev)*Pz - Pex_prev*Px - Pey_prev*Py)/( sqrt((Q2_prev + Nu_prev*Nu_prev)*P2) );
    Float_t Pt2 = P2*(1-cospq*cospq);

    Double_t phi_pq;
    TVector3 Vhad(Px,Py,Pz);
    TVector3 Vvirt(-Pex_prev,-Pey_prev,kEbeam-Pez_prev);
    Double_t phi_z = TMath::Pi()-Vvirt.Phi();
    Vvirt.RotateZ(phi_z);
    Vhad.RotateZ(phi_z);
    TVector3 Vhelp(0.,0.,1.);
    Double_t phi_y = Vvirt.Angle(Vhelp);
    Vvirt.RotateY(phi_y);
    Vhad.RotateY(phi_y);
    phi_pq = Vhad.Phi() * 180./(TMath::Pi());

    kData[0] = M;
    kData[1] = Px;
    kData[2] = Py;
    kData[3] = Pz;
    kData[4] = Nu_prev;
    kData[5] = Q2_prev;
    kData[6] = (Float_t)E/Nu_prev;
    kData[7] = cospq;
    kData[8] = Pt2;
    kData[9] = evnt_prev;

    kData[10]=((comb->Npart==3)? ( *(*comb)[0] + *(*comb)[1]).M2() : 0);
    kData[11]=((comb->Npart==3)? ( *(*comb)[0] + *(*comb)[2]).M2() : 0);
    kData[12] = Zec_prev; // z electron corrected.                                                                                                    

    kData[13] = (*comb)[0]->vz;
    kData[14] = ((comb->Npart>1)?(*comb)[1]->vz:0);
    kData[15] = ((comb->Npart>2)?(*comb)[2]->vz:0);
    kData[16] = W_prev;
    kData[17] = Xec_prev;
    kData[18] = Yec_prev;

    Double_t qx1,qy1,qz1,qx2,qy2,qz2;
    qx1 = (*comb)[0]->Px();
    qy1 = (*comb)[0]->Py();
    qz1 = (*comb)[0]->Pz();
    qx2 = ((comb->Npart>1)?(*comb)[1]->Px():0);
    qy2 = ((comb->Npart>1)?(*comb)[1]->Py():0);
    qz2 = ((comb->Npart>1)?(*comb)[1]->Pz():0);
    Float_t E1 = (*comb)[0]->E();
    Float_t E2 = ((comb->Npart>1)?(*comb)[1]->E():0);
    kData[19] = qx1;
    kData[20] = qy1;
    kData[21] = qz1;
    kData[22] = qx2;
    kData[23] = qy2;
    kData[24] = qz2;
    kData[25] = E1;
    kData[26] = E2;
    kData[27] = E1;
    kData[28] = E2;

    if (0.35 < E1 && E1 < 1.2) kData[27] /= hcfm->GetBinContent(hcfm->FindBin(E1));
    if (0.35 < E2 && E2 < 1.2) kData[28] /= hcfm->GetBinContent(hcfm->FindBin(E2));
    kData[29] = (*comb)[0]->vx;
    kData[30] = (*comb)[0]->vy;
    kData[31] = ((comb->Npart>1)?(*comb)[1]->vx:0);
    kData[32] = ((comb->Npart>1)?(*comb)[1]->vy:0);
    kData[33] = TargType_prev;
    kData[34] = TargTypeO_prev;
    kData[35] = phi_pq;

    for (int k = 0; k < kNSecondary; k++) {

      Double_t px= (*comb)[k]->Px();
      Double_t py= (*comb)[k]->Py();
      Double_t pz= (*comb)[k]->Pz();
      Double_t e= (*comb)[k]->E();

      new ((*P4Arr)[k]) TLorentzVector(px,py,pz,e);
    }
    return ttree->Fill();
  }

  inline Double_t kinFit(Double_t *W, Double_t *Wa, TMatrixD &V) {
    bool db = false;
    if (db) std::cout<<"V Matrix on  "<<__LINE__<<std::endl;
    if (db) V.Print();

    //    TMatrixD V(4,4) = *Vm;//covariance matrix                                                                                                   
    TMatrixD V_new(4,4);//covariance matrix updated                                                                                                   
    TMatrixD VD(1,1);//auxiliary matrix                                                                                                               
    TMatrixD D(1,4);//derivatives of restriction on xa                                                                                                
    TMatrixD d(1,1);//restriction on xa                                                                                                               
    TMatrixD x(4,1);//corrected point                                                                                                                 
    TMatrixD xa(4,1);//linearization point                                                                                                            
    TMatrixD x0(4,1);// initial point                                                                                                                 
    TMatrixD lam(1,1);//constrain multiplier                                                                                                          
    Double_t Chi2 =0;//chi2 value                       

    D(0,0) = -2*Wa[0]; D(0,1) = -2*Wa[1]; D(0,2) = -2*Wa[2]; D(0,3) = 2*Wa[3];
    if (db) std::cout<<"D Matrix on  "<<__LINE__<<std::endl;
    if (db) D.Print();
    //x(0,0) = W[0]; x(1,0) = W[1]; x(2,0) = W[2]; x(3,0) = W[3];                                                                                     
    xa(0,0) = Wa[0]; xa(1,0) = Wa[1]; xa(2,0) = Wa[2]; xa(3,0) = Wa[3];
    x0(0,0) = W[0]; x0(1,0) = W[1]; x0(2,0) = W[2]; x0(3,0) = W[3];

    //lam(0,0) = 0;                                                                                                                                   
    d(0,0)=Wa[3]*Wa[3] - Wa[0]*Wa[0] - Wa[1]*Wa[1] - Wa[2]*Wa[2] - kPdgInfo->Mass()*kPdgInfo->Mass();

    TMatrixD DT =(D).Transpose(D);
    if (db) std::cout <<"DT Matrix on  " << __LINE__ << std::endl;
    if (db) DT.Print();
    D.Transpose(D);

    TMatrixD VDL = (D*V);
    if (db)std::cout<<"VDL Matrix on  "<<__LINE__<<std::endl;
    if (db)VDL.Print();
    VD=VDL*DT;
    if (db)std::cout<<"VD Matrix on  "<<__LINE__<<std::endl;
    if (db)VD.Print();
    VD.Invert();
    if (db)std::cout<<"VD Matrix on  "<<__LINE__<<std::endl;
    if (db)VD.Print();
    lam = VD*(D*(x0-xa) + d);

    TMatrixD lamT = lam.Transpose(lam);
    lam.Transpose(lam);

    x = x0 + (V*DT)*lam;
    W[0]=x(0,0);W[1]=x(1,0);W[2]=x(2,0);W[3]=x(3,0);
    V_new = V - (V*DT)*VD*(D*V);
    V=V_new;
    TMatrixD aux=(lamT*(D*(x0 - xa) + d));
    //aux.Print();                                                                                                                                    
    Chi2=aux(0,0);

    return Chi2;
  }

  int pushSecondary(int pid)
  {
    kNSecondary++;
    if (!isPid(pid))
      {
	kSPid.push_back(pid);
	kNSPid[pid]=1;
	int k = kSPid.size();
	hSPid.push_back(new TH1F(Form("hNPart%d",k), TDatabasePDG::Instance()->GetParticle(pid)->GetName(),20,0,20) );
      }
    else
      kNSPid[pid]++;


    return pid;
  }

  int addSecondary(int pid)
  {
    pid = TDatabasePDG::Instance()->GetParticle(pid)->PdgCode();
    pushSecondary(pid);
    return pid;
  }

  int addSecondary(const char *name) {
    int pid  = TDatabasePDG::Instance()->GetParticle(name)->PdgCode();
    pushSecondary(pid);
    return pid;
  }

  int addPrimary(int pid){
    kPdgInfo = TDatabasePDG::Instance()->GetParticle(pid);
    kPPid=kPdgInfo->PdgCode();
    return kPPid;
  }
  int addPrimary(const char *name){
    kPdgInfo = TDatabasePDG::Instance()->GetParticle(name);
    kPPid=kPdgInfo->PdgCode();
    return kPPid;
  }

  bool isPid(int pid) {
    kSIt = std::find (kSPid.begin(), kSPid.end(), pid);
    if (kSIt != kSPid.end())
      return true;
    else
      return false;
  }
  bool checkMinPart() {
    bool minPart=true;
    for (int k=0;k<kSPid.size();k++) {
      if (fEMatch)
        minPart=minPart && (kSecondary[k].size() == kNSPid[kSPid[k]]);
      else
        minPart=minPart && (kSecondary[k].size() >= kNSPid[kSPid[k]]);
      hSPid[k]->Fill(kSecondary[k].size());
    }
    return minPart;
  }
  bool checkMinPart(Combo *c) {
    bool minPart=true;
    for (int k=0;k<kSPid.size();k++) {
      minPart=minPart && (c->findPid(kSPid[k]) == kNSPid[kSPid[k]]);
    }
    return minPart;
  }

  void setElectVar() {
    Nu_prev = Nu;
    Q2_prev = Q2;
    Zec_prev = Zec;
    Xec_prev = Xec;
    Yec_prev = Yec;
    W_prev = W;
    Pex_prev = Pex;
    Pey_prev = Pey;
    Pez_prev = Pez;
    Ee_prev = Ee;
    TargType_prev = TargType;
    TargTypeO_prev = TargTypeO;
  }

  int takeN(int N, int kspid, int pos = 0, Combo *c = 0,int count = 0) {
    Combo *c_new;
    if (DEBUG) std::cout << "### take N:  " << N << "##############" << std::endl;
    if (N<1) return -1;
    if (N!=1) {
      for (int k =pos;k<kSecondary[kspid].size()-N+1;k++) {
        if (c==0) c_new = new Combo();
        else c_new = new Combo(*c);
        c_new->addParticle(kSecondary[kspid][pos]);
        count = takeN(N-1,kspid,k+1,c_new,count);
      }
    } else {
      for (int k = pos; k < kSecondary[kspid].size(); k++) {
        if (c==0) c_new = new Combo();
        else c_new = new Combo(*c);
        c_new->addParticle(kSecondary[kspid][k]);
        if (DEBUG) std::cout << "############ Npart from takeN: " << c_new->Npart << "#### pid: " << kSPid[kspid] << "#############" << std::endl;
        //kCombo[kspid].push_back(new Combo(*c));                                                                                                     
        kCombo[kspid].push_back(c_new);
	//kParticles.push_back(new Particle(*kSecondary[kspid][k]));                                                                                  
        //std::cout<<__LINE__<<" "<< kCombo[kspid].back()->M()<<std::endl;                                                                            
        count++;
      }
    }
    return count;
  }

  int findSecondary() {
    int count=0;
    for (int k = 0; k < kSPid.size(); k++) {
      if (pid == kSPid[k]) {
        kSecondary[k].push_back(new Particle(Px,Py,Pz,Ep,vx,vy,vz,pid));
        count++;
      }
    }
    return count;
  }

  int correct_momentum() {
    Float_t Rt = TMath::Sqrt( ECX*ECX + ECY*ECY );
    Float_t R = TMath::Sqrt( ECX*ECX + ECY*ECY + (ECZ-Zec)*(ECZ -Zec) );
    Float_t theta_gam = TMath::ASin(Rt/R);
    Float_t phi_gam = TMath::ATan2(ECY,ECX);
    Px = Ep*TMath::Sin(theta_gam)*TMath::Cos(phi_gam);
    Py = Ep*TMath::Sin(theta_gam)*TMath::Sin(phi_gam);
    Pz = Ep*TMath::Cos(theta_gam);
    return 0;
  }

  int getCombinations(TChain *t) {

    kSecondary = new std::vector<Particle*> [kSPid.size()];
    kCombo = new std::vector<Combo*> [kSPid.size()];

    t->GetEntry(0);
    setElectVar();
    evnt_prev = evnt;
    std::cout << "Processing..." << std::endl;
    std::cout.fill('.');

    for (int i = 0; i < Ne; i++) {
      t->GetEntry(i);
      Ep = E;
      if (data_type<2)// not gsim                                                                                                                     
	{
	  Ep = (pid==22)? (E/0.272):( (pid==211 || pid==-211)?(sqrt(P*P+ TMath::Power(TDatabasePDG::Instance()->GetParticle("pi-")->Mass(),2)) ):E);

	  if (pid==22)
	    correct_momentum();

	}
      if (evnt==evnt_prev)
	{
	  //std::cout<<__LINE__<<" "<<findSecondary()<<std::endl;                                                                                       
	  Particle *p = new Particle(Px,Py,Pz,Ep,vx,vy,vz,pid);

	  push_bkgnd(p);

	  findSecondary();
	}
      else
	{
	  //      fill_elec();                                                                                                                          
	  pop_bkgnd();
	  if (checkMinPart())
	    {
	      int Npart = 1;

	      for (int k =0;k<kSPid.size();k++)
		{
		  if (DEBUG) std::cout<<"############ Nsecondary of pid: "<<kSPid[k]<<" ::: "<<kSecondary[k].size()<<"###########"<<std::endl;
		  takeN(kNSPid[kSPid[k]] ,k);

		  Npart*=kCombo[k].size();
		}
	      if (DEBUG) std::cout<<"############ N candidates for primary: "<<Npart<<"####################\n##########################"<<std::endl;
	      for(int k=0;k<Npart;k++)
		{
		  kPrimary = new Combo();
		  int div=1;
		  for (int l =0;l<kSPid.size();l++)
		    {
		      int size = kCombo[l].size();
		      //std::cout<<__LINE__<<": \n";                                                                                                          
		      *kPrimary+=*kCombo[l][ (k/div)%size ];
		      //std::cout<<__LINE__<<": \n";                   
		      div*=size;
		    }
		  //  if (DEBUG) std::cout<<"############ Npart from primary: "<<kPrimary->Npart<<"####################"<<std::endl;                        
		  fill();
		  delete kPrimary;
		}
	    }
	  clear();
	  setElectVar();
	  evnt_prev=evnt;
	  Particle *p =new Particle(Px,Py,Pz,Ep,vx,vy,vz,pid);
	  push_bkgnd(p);
	  findSecondary();
	}
      std::cout<<setw(15)<<float(i+1)/Ne*100<<" %"<<"\r";
      std::cout.flush();
    }
    return 0;
  }

  int push_bkgnd(Particle *p)
  {
    if (isPid(p->pid) &&  kBkgnd.size() < kBUFFLIMIT)
      {
	if (!kBkgnd.empty())
	  {
	    int i;
	    for (i =0;i<kBkgnd.size();i++)
	      {
		if ( (kBkgnd[i]->findPid(p->pid)<kNSPid[p->pid] ) && (kBkgnd[i]->lastEvent!=evnt) && (kBkgnd[i]->isCompatible()) )
		  {
		    kBkgnd[i]->addParticle(p,evnt,kTRUE);
		    break;
		  }

	      }
	    if (i==kBkgnd.size())
	      {
		Combo *c = new Combo();
		c->addParticle(p,evnt);

		kBkgnd.push_back(c);
	      }
	  }
	else
	  {
	    Combo *c = new Combo();
	    c->addParticle(p,evnt);
	    kBkgnd.push_back(c);
	  }
      }
    return 0;
  }

  bool pop_bkgnd()
  {
    bool ret = false;
    if (!kBkgnd.empty())
      {
	for (int i =0;i<kBkgnd.size();i++)
	  {
	    if (checkMinPart(kBkgnd[i]))
	      {
		//      std::cout<<__FILE__<<"::"<<__LINE__<<std::endl;                                                                                     
		fill(kBkgnd[i],kOutBkgnd);
		delete kBkgnd[i];
		kBkgnd.erase(kBkgnd.begin()+i);
		ret = true;
	      }
	  }
      }
    return ret;
  }

  int getBkgnd(TChain *t) {
    t->GetEntry(0);
    setElectVar();
    evnt_prev = evnt;
    std::cout << "Processing..." << std::endl;
    std::cout.fill('.');
    for ( int i = 0; i < Ne; i++)
      {
	t->GetEntry(i);
	Ep = (pid==22)? (E/0.272):sqrt(P*P+ TMath::Power(TDatabasePDG::Instance()->GetParticle("pi-")->Mass(),2));

	if (pid==22)
	  correct_momentum();

	if (evnt==evnt_prev)
	  {
	    //std::cout<<__LINE__<<" "<<findSecondary()<<std::endl;                                                                                       
	    Particle *p = new Particle(Px,Py,Pz,Ep,vx,vy,vz,pid);
	    push_bkgnd(p);
	  }
	else
	  {
	    pop_bkgnd();
	    setElectVar();
	    evnt_prev=evnt;
	    Particle *p = new Particle(Px,Py,Pz,Ep,vx,vy,vz,pid);
	    push_bkgnd(p);
	  }
	std::cout<<setw(15)<<float(i+1)/Ne*100<<" %"<<"\r";
	std::cout.flush();
      }
    return 0;
  }
};

void check_dir(const char *outdir)
{
  struct stat sb;
  if (stat(outdir, &sb) != 0) {
    system(Form("mkdir %s",outdir));
  }

}

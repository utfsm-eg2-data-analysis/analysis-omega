/*************************************************/
/*  eta_id.cxx                                   */
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
#include <string.h>

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
#include "Reaction.h"

// Global Variables
bool DEBUG = false;

TH1F *hW;
TH1F *hW2;
TH1F *hWmb;
TH1F *hW2mb;
TH1F *hT;
TH1F *hcfm;
TH2F *hEpi0_th;

Float_t kMPi0 = 1.33196e-1;// Got from sim
Float_t kSPi0 = 1.94034e-2;// Got from sim
//Float_t kMPi0=5.39609e-01;
//Float_t kSPi0=5.98542e-02;

bool GSIM = false;
int data_type = 0;
Float_t kPt2, kEvent; 

TNtuple *tuple;
//TNtuple *tuple_sim;
TNtuple *tuplemb;
TNtuple *tuplePi0_gamma, *tupleGamma;

Float_t kEbeam = 5.014;
Float_t E, Ee, Ee_prev, Ep, P, Px, Py, Pz, evnt, evnt_prev, Zec, Zec_prev, Yec, Yec_prev, Xec, Xec_prev, TEc;
Float_t Q2, Q2_prev, W, W_prev, Nu, Nu_prev, Pex, Pex_prev, Pey, Pey_prev, Pez, Pez_prev, TargType, TargType_prev;
Float_t TargTypeO = 0, TargTypeO_prev = 0;
Float_t pid, vx, vy, vz, ECX, ECY, ECZ;

long Ne = -1;

char st[3]= "Fe"; // solid target: C | Fe | Pb // important line 1
char tt[3] = "Fe"; // cut on solid target or Deuterium : (st) or D. // important line 2

Float_t kMprt = 0.938272;
Float_t kMntr = 0.939565;

TClonesArray *P4Arr;

int main(int argc, char *argv[]) {

  TBenchmark *bm = new TBenchmark();
  bm->Start("get_omega");
  
  parseopt(argc, argv);

  TFile *corrfile = new TFile("gammECorr.root", "read");
  hcfm = (TH1F*) corrfile->Get("hcfm");

  TChain *t = new TChain();
  if (data_type == 1) t->Add("/data/tsunami/user/b/borquez/EG2Pruned/prune_simulFe_Fe.root/ntuple_accept"); // important line 3
  else if (data_type == 2) t->Add("/data/tsunami/user/b/borquez/EG2Pruned/prune_simulFe_Fe.root/ntuple_thrown"); // important line 4
  else t->Add("/data/tsunami/user/b/borquez/EG2Pruned/prune_dataFe-thickD2.root/ntuple_data"); // important line 5
  
  t->SetBranchStatus("*", 0);
  t->SetBranchStatus("E", 1);
  t->SetBranchStatus("Ee", 1);
  t->SetBranchStatus("P", 1);
  t->SetBranchStatus("Px", 1);
  t->SetBranchStatus("Py", 1);
  t->SetBranchStatus("Pz", 1);
  t->SetBranchStatus("evnt", 1);
  t->SetBranchStatus("Zec", 1);
  t->SetBranchStatus("Yec", 1);
  t->SetBranchStatus("Xec", 1);
  t->SetBranchStatus("TEc", 1);
  t->SetBranchStatus("Q2", 1);
  t->SetBranchStatus("Nu", 1);
  t->SetBranchStatus("W", 1);
  t->SetBranchStatus("Pex", 1);
  t->SetBranchStatus("Pey", 1);
  t->SetBranchStatus("Pez", 1);
  t->SetBranchStatus("pid", 1);
  t->SetBranchStatus("vxh", 1);
  t->SetBranchStatus("vyh", 1);
  t->SetBranchStatus("vzh", 1);
  t->SetBranchStatus("TargType", 1);
  t->SetBranchStatus("ECX", 1);
  t->SetBranchStatus("ECY", 1);
  t->SetBranchStatus("ECZ", 1);
  t->SetBranchAddress("E", &E);
  t->SetBranchAddress("Ee", &Ee);
  t->SetBranchAddress("P", &P);
  t->SetBranchAddress("Px", &Px);
  t->SetBranchAddress("Py", &Py);
  t->SetBranchAddress("Pz", &Pz);
  t->SetBranchAddress("Zec", &Zec);
  t->SetBranchAddress("Yec", &Yec);
  t->SetBranchAddress("Xec", &Xec);
  t->SetBranchAddress("evnt", &evnt);
  t->SetBranchAddress("TEc", &TEc);
  t->SetBranchAddress("Q2", &Q2);
  t->SetBranchAddress("Nu", &Nu);
  t->SetBranchAddress("W", &W);
  t->SetBranchAddress("Pex", &Pex);
  t->SetBranchAddress("Pey", &Pey);
  t->SetBranchAddress("Pez", &Pez);
  t->SetBranchAddress("pid", &pid);
  t->SetBranchAddress("vxh", &vx);
  t->SetBranchAddress("vyh", &vy);
  t->SetBranchAddress("vzh", &vz);
  t->SetBranchAddress("TargType", &TargType);
  t->SetBranchAddress("ECX", &ECX);
  t->SetBranchAddress("ECY", &ECY);
  t->SetBranchAddress("ECZ", &ECZ);

  if (Ne == -1) Ne = t->GetEntries();

  std::cout << "Number of entries to be processed: " << Ne << std::endl;

  // w -> pi+ pi- a a
  Reaction r("w -> pi+ pi- a a","/data/tsunami/user/b/borquez/EG2Pruned/woutFe-thickD2.root"); // important line 6
  r.addPrimary("omega");
  r.addSecondary("gamma");
  r.addSecondary("gamma");
  r.addSecondary("pi+");
  r.addSecondary("pi-");

  r.getCombinations(t);
  r.store();
  
  std::cout << std::endl;

  r.kOutData->Print();
  r.kOutBkgnd->Print();

  corrfile->Close();
  bm->Show("get_omega");

  return 0;
}

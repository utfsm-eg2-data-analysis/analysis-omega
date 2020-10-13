/**************************************/
/* analysisConfig.h                   */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <chrono>

#include "TROOT.h"
#include "TString.h"
#include "TCut.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TTree.h"
#include "TEntryList.h"
#include "TLeaf.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGaxis.h"
#include "TAxis.h"
#include "TMath.h"
#include "TPad.h"
#include "TObjArray.h"
#include "TVector3.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TNtuple.h"
#include "TLorentzVector.h"
#include "TPaveStats.h"

using Clock=std::chrono::high_resolution_clock;

/*** DIRECTORIES ***/

TString hostName = getenv("HOSTNAME");
TString proDir   = getenv("PRODIR");
TString workDir  = getenv("WORKDIR");
TString tmpDir   = workDir + "/tmp";

/*** DATA CUTS ***/

// DIS
TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";

// reconstructions
TCut cutPi0    = "0.059 < pi0M_corr && pi0M_corr < 0.203"; // mean=0.131 & sigma=0.024
TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";

// latest Status cuts
TCut statusCuts_electrons = "StatusEl > 0 && DCStatusEl > 0 && SCStatusEl == 33";
TCut statusCuts_pip       = "Status[2] > 0 && StatDC[2] > 0 && DCStatus[2] > 0"; // MUST UPDATE
TCut statusCuts_pim       = "Status[3] > 0 && StatDC[3] > 0 && DCStatus[3] > 0"; // MUST UPDATE
TCut cutStatus            = statusCuts_electrons && statusCuts_pip && statusCuts_pim;
// TCut statusCuts_pip_le    = "P_corr[2] < 2.7 && StatSC[2] > 0";
// TCut statusCuts_pip_he    = "P_corr[2] >= 2.7 && Nphe[2] > 25 && StatCC[2] > 0 && Chi2CC[2] < 5./57.3";
// TCut statusCuts_pim_le    = "P_corr[3] <= 2.5 && !(StatCC[3] > 0 && Nphe[3] > 25)";
// TCut statusCuts_pim_he    = "P_corr[3] > 2.5";
// TCut cutStatus            = statusCuts_electrons && statusCuts_pip && (statusCuts_pip_le || statusCuts_pip_he) && statusCuts_pim && (statusCuts_pim_le || statusCuts_pim_he);

// TM vertex cuts
TCut cutTargType_D  = "-31.8 < Zec && Zec < -28.4";
TCut cutTargType_C  = "-25.33 < Zec && Zec < -24.10";
TCut cutTargType_Fe = "-25.65 < Zec && Zec < -24.26";
TCut cutTargType_Pb = "-25.54 < Zec && Zec < -24.36";

// enhance results
TCut cutBinLimits = "Q2 > 1 && Q2 < 4 && Nu > 2.2 && Nu < 4.2 && wZ_corr > 0.5 && wZ_corr < 1.0 && wPt2_corr > 0. && wPt2_corr < 1.5";

/*** SIMREC/ACCEPTED CUTS ***/

// DIS
TCut cutDIS_simrec = cutDIS; // same as data

// reconstructions
TCut cutPi0_simrec    = "0.084 < pi0M_corr && pi0M_corr < 0.186"; // mean=0.135 & sigma=0.017
TCut cutPipPim_simrec = cutPipPim; // same as data

// latest Status cuts
TCut statusCuts_electrons_simrec = "StatusEl > 0 && DCStatusEl > 0 && SCStatusEl == 33"; // same as data
TCut statusCuts_pip_simrec       = "Status[0] > 0 && StatDC[0] > 0 && DCStatus[0] > 0"; // same as data
TCut statusCuts_pim_simrec       = "Status[1] > 0 && StatDC[1] > 0 && DCStatus[1] > 0"; // same as data
TCut cutStatus_simrec            = statusCuts_electrons_simrec && statusCuts_pip_simrec && statusCuts_pim_simrec;

/*** GSIM/THROWN CUTS ***/

// DIS
TCut cutDIS_gsim = "mc_Q2 > 1 && mc_W > 2 && mc_Yb < 0.85";

// reconstructions
TCut cutPi0_gsim    = "0.1333 < mc_pi0M && mc_pi0M < 0.1367"; // mean=0.135 & sigma=5.7e-4
TCut cutPipPim_gsim = "0.48 > mc_pippimM || 0.51 < mc_pippimM";

/*** OTHER CUTS ***/

// exclusive for ntuple_e
TCut cutStatus_ntuple_e = "Status > 0 && DCStatus > 0 && SCStatus == 33";
TCut cutVertex_Y = "Yec > -1.4 && Yec < 1.4"; // lose ~1m candidates

/*** BINNING ***/

// 5 bins for each kinematic variable, obtained with GetQuantiles.cxx
const Double_t edgesQ2[6]  = {1.0, 1.187, 1.376, 1.616, 2.008, 4.0};
const Double_t edgesNu[6]  = {2.2, 3.233, 3.550, 3.786, 3.994, 4.2};
const Double_t edgesZ[6]   = {0.5, 0.548, 0.601, 0.665, 0.761, 1.0};
const Double_t edgesPt2[6] = {0.0, 0.049, 0.113, 0.204, 0.361, 1.5};

/*** ELECTRON NUMBERS ***/

// [D,C,Fe,Pb][bin], obtained from GetElectronNumber.cxx
const Double_t electronNumber[4] = {69544805., 15054966., 29018550., 11256909.};
const Double_t electronNumberQ2[4][5] = {{12842908., 13596600., 13772639., 14536805., 14795432.},
					 {2815127., 2969424., 2983337., 3136969., 3149865.},
					 {5472138., 5782588., 5778550., 6038794., 5946114.},
					 {2189122., 2292324., 2263405., 2312089., 2199791.}};
const Double_t electronNumberNu[4][5] = {{24118754., 13777701., 11012654., 9580918., 8663965.},
					 {5115492., 2932212., 2366977., 2110598., 1972135.},
					 {9572387., 5684183., 4664129., 4149167., 3856291.},
					 {3793213., 2175171., 1761324., 1584883., 1584883.}};

/*** CONSTANTS ***/

// run numbers
Int_t runNumbersC  = 118; // from 119; because I removed 42040
Int_t runNumbersFe = 263; // from 265; because I removed 41315 and 41394
Int_t runNumbersPb = 169; // from 171; because I removed 41834 and 41979
Int_t runNumbersTotal = runNumbersC + runNumbersFe + runNumbersPb;

TDatabasePDG pdg;
const Float_t kMproton = pdg.GetParticle(2212)->Mass();
const Float_t kMpi = pdg.GetParticle(211)->Mass();
const Float_t kMpi0 = pdg.GetParticle(111)->Mass();
const Float_t kMe = pdg.GetParticle(11)->Mass();
const Float_t kMomega = pdg.GetParticle(223)->Mass();
const Float_t kMeta = pdg.GetParticle(221)->Mass();
const Float_t kMf1 = pdg.GetParticle(20223)->Mass();
const Float_t kMK0 = pdg.GetParticle(311)->Mass();
const Float_t kMrho = pdg.GetParticle(113)->Mass();

const Float_t kEbeam = 5.014;

/*** FUNCTIONS ***/

Float_t particleMass(Float_t fPid) {
  if (fPid == -9999) return -9999; // closure
  return pdg.GetParticle((Int_t) fPid)->Mass();
}

// good color options: kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
void drawHorizontalLine(Double_t y, Color_t cc = kBlack, TString style = "dash") {
  // define style
  Int_t ss;
  if (style == "dash") ss = 2;
  else if (style == "cont") ss = 1;

  // draw line!
  Double_t u;
  gPad->Update(); // necessary
  u = (y - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.1, u, 0.9, u);
  liney->SetLineWidth(3);
  liney->SetLineColor(cc);
  liney->SetLineStyle(ss);
  liney->SetNDC(kTRUE);
  liney->Draw();
}

// good color options: kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
void drawVerticalLine(Double_t x, Color_t cc = kBlack, TString style = "dash") {
  // define style
  Int_t ss;
  if (style == "dash") ss = 2;
  else if (style == "cont") ss = 1;

  // draw line!
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineWidth(3);
  linex->SetLineColor(cc);
  linex->SetLineStyle(ss);
  linex->SetNDC(kTRUE);
  linex->Draw();
}

TString particleName(Int_t particleID) {
  if (particleID == 223) return "omega";
  else if (particleID == 111) return "pi0";
  else if (particleID == 211) return "pi+";
  else if (particleID == -211) return "pi-";
  else if (particleID == 22) return "gamma";
  else if (particleID == 11) return "electron";
  else return "";
}

Int_t particleID(TString particleName) {
  if (particleName == "omega") return 223;
  else if (particleName == "pi0") return 111;
  else if (particleName == "pi+") return 211;
  else if (particleName == "pi-") return -211;
  else if (particleName == "gamma") return 22;
  else if (particleName == "electron") return 11;
  else return 0;
}

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

/*** Global variables ***/

TString proDir = getenv("PRODIR");
TString tmpDir = proDir + "/tmp";

TString dataDir = proDir + "/out/filterData";
TString simDir  = proDir + "/out/filterSim";

TString rawSimDir_jlab = "/home/borquez/volatile/omegaSim"; // + /output/<target>/<ndir>/recsis<target>_{00..99}.root
TString rawSimDir_utfsm = "/eos/user/b/borquez/omegaSim"; // + /<set>/<target>/recsis<target>_{0000..0099}.root
TString rawDataDir_utfsm = "/data/jlab/mss/clas/eg2a/production/Pass2/Clas"; // + /clas_<rn>_<nfile>.pass2.root

TCut cutDIS = "Q2 > 1 && W > 2 && Yb < 0.85";
TCut cutPi0 = "0.059 < pi0M && pi0M < 0.203"; // mean=0.131 & sigma=0.024
TCut cutPipPim = "0.48 > pippimM || 0.51 < pippimM";

// cut for pi0 from MW
TCut cutPi0_MW = "0.059 < pi0M && pi0M < 0.209"; // mean=0.134 & sigma=0.025

// cut for pi0 from GSIM files
TCut cutPi0_gsim = "0.132 < mpi0 && mpi0 < 0.138";

// these cuts are for the files filtered with old OS programs
TCut cutDIS_old = "Q2 > 1 && W > 2";
TCut cutPi0_old = "0.059 < mpi0 && mpi0 < 0.209"; // mikewood cut
TCut cutPipPim_old = "0.48 > mpippim || 0.51 < mpippim"; // mikewood cut

// edges obtained with GetQuantiles.cxx
const Double_t edgesQ2[6] = {1, 1.187, 1.376, 1.616, 2.008, 4};
const Double_t edgesNu[6] = {2.2, 3.233, 3.550, 3.786, 3.994, 4.2};
const Double_t edgesZ[6] = {0.5, 0.548, 0.601, 0.665, 0.761, 1.}; // q5
// const Double_t edgesZ[6] = {0.5, 0.560, 0.631, 0.732, 1.}; // q4
// const Double_t edgesZ[6] = {0.5, 0.583, 0.693, 1.}; // q3
const Double_t edgesPt2[6] = {0, 0.049, 0.113, 0.204, 0.361, 1.5};

// run numbers
Int_t runNumbersC = 118; // from 119; because I removed 42040
Int_t runNumbersFe = 263; // from 265; because I removed 41315 and 41394 (why the last one?)
Int_t runNumbersPb = 169; // from 171; because I removed 41834 and 41979
Int_t runNumbersTotal = runNumbersC + runNumbersFe + runNumbersPb;

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

// constants
TDatabasePDG pdg;
const Float_t kMproton = pdg.GetParticle(2212)->Mass();
const Float_t kMpi = pdg.GetParticle(211)->Mass();
const Float_t kMpi0 = pdg.GetParticle(111)->Mass();
const Float_t kMe = pdg.GetParticle(11)->Mass();
const Float_t kMomega = pdg.GetParticle(223)->Mass();

void setAlias_old(TTree *treeExtracted) {
  // pip
  treeExtracted->SetAlias("p2pip", "fX[2]*fX[2] + fY[2]*fY[2] + fZ[2]*fZ[2]");
  treeExtracted->SetAlias("E2pip", "p2pip + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pip", "E2pip - p2pip");
  treeExtracted->SetAlias("mpip", "TMath::Sqrt(m2pip)");
  treeExtracted->SetAlias("Epip", "TMath::Sqrt(E2pip)");
  treeExtracted->SetAlias("Ppip", "TMath::Sqrt(p2pip)");
  
  // pim
  treeExtracted->SetAlias("p2pim", "fX[3]*fX[3] + fY[3]*fY[3] + fZ[3]*fZ[3]");
  treeExtracted->SetAlias("E2pim", "p2pim + 0.13957*0.13957");
  treeExtracted->SetAlias("m2pim", "E2pim - p2pim");
  treeExtracted->SetAlias("mpim", "TMath::Sqrt(m2pim)");
  treeExtracted->SetAlias("Epim", "TMath::Sqrt(E2pim)");
  treeExtracted->SetAlias("Ppim", "TMath::Sqrt(p2pim)");
  
  // pi0
  treeExtracted->SetAlias("Pxpi0", "fX[0] + fX[1]");
  treeExtracted->SetAlias("Pypi0", "fY[0] + fY[1]");
  treeExtracted->SetAlias("Pzpi0", "fZ[0] + fZ[1]");
  treeExtracted->SetAlias("p2pi0", "Pxpi0*Pxpi0 + Pypi0*Pypi0 + Pzpi0*Pzpi0");
  treeExtracted->SetAlias("cos_theta", "(fX[0]*fX[1] + fY[0]*fY[1] + fZ[0]*fZ[1])/(fE[0]*fE[1])"); // original
  treeExtracted->SetAlias("m2pi0", "2*fE[0]*fE[1]*(1 - cos_theta)"); // original
  treeExtracted->SetAlias("mpi0", "TMath::Sqrt(m2pi0)");
  treeExtracted->SetAlias("E2pi0", "m2pi0 + p2pi0");
  treeExtracted->SetAlias("Epi0", "TMath::Sqrt(E2pi0)");
  treeExtracted->SetAlias("Ppi0", "TMath::Sqrt(p2pi0)");
  
  // crossed terms
  treeExtracted->SetAlias("p1p2", "fX[2]*fX[3] + fY[2]*fY[3] + fZ[2]*fZ[3]");
  treeExtracted->SetAlias("E1E2", "TMath::Sqrt(E2pip*E2pim)");
  treeExtracted->SetAlias("p2p3", "fX[3]*Pxpi0 + fY[3]*Pypi0 + fZ[3]*Pzpi0");
  treeExtracted->SetAlias("E2E3", "TMath::Sqrt(E2pim*E2pi0)");
  treeExtracted->SetAlias("p1p3", "fX[2]*Pxpi0 + fY[2]*Pypi0 + fZ[2]*Pzpi0");
  treeExtracted->SetAlias("E1E3", "TMath::Sqrt(E2pip*E2pi0)");

  // dalitz plots!
  treeExtracted->SetAlias("m2pippim", "m2pip + m2pim + 2*(E1E2 - p1p2)");
  treeExtracted->SetAlias("m2pimpi0", "m2pim + m2pi0 + 2*(E2E3 - p2p3)");
  treeExtracted->SetAlias("m2pippi0", "m2pip + m2pi0 + 2*(E1E3 - p1p3)");

  // for the cuts
  treeExtracted->SetAlias("mpippim", "TMath::Sqrt(m2pippim)");
  treeExtracted->SetAlias("mpimpi0", "TMath::Sqrt(m2pimpi0)");
  treeExtracted->SetAlias("mpippi0", "TMath::Sqrt(m2pippi0)");

  // omega
  treeExtracted->SetAlias("Eomega", "Epip + Epim + fE[0] + fE[1]");
  treeExtracted->SetAlias("Pxomega", "fX[0] + fX[1] + fX[2] + fX[3]");
  treeExtracted->SetAlias("Pyomega", "fY[0] + fY[1] + fY[2] + fY[3]");
  treeExtracted->SetAlias("Pzomega", "fZ[0] + fZ[1] + fZ[2] + fZ[3]");
  treeExtracted->SetAlias("p2omega", "Pxomega*Pxomega + Pyomega*Pyomega + Pzomega*Pzomega");
  treeExtracted->SetAlias("momega", "TMath::Sqrt(Eomega*Eomega - Pxomega*Pxomega - Pyomega*Pyomega - Pzomega*Pzomega)");
  treeExtracted->SetAlias("deltam", "momega - mpi0 - mpip - mpim");
  treeExtracted->SetAlias("Pomega", "TMath::Sqrt(p2omega)");
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

void setAlias(TTree *treeExtracted) {
  treeExtracted->SetAlias("Pl2", "wP2*CosThetaPQ*CosThetaPQ");
  treeExtracted->SetAlias("absQ", "TMath::Sqrt(Nu*Nu + Q2)");
  treeExtracted->SetAlias("Mx2", "W*W + wM*wM - 2*Z*Nu*Nu + 2*TMath::Sqrt(Pl2)*absQ - 2*Z*Nu*0.938272");
  treeExtracted->SetAlias("Mx", "TMath::Sqrt(Mx2)");

  treeExtracted->SetAlias("swD", Form("wD + 2*%f + %f", kMpi, kMpi0));
}

/*
    // my own normalization
    simrecHistA->Draw("HIST");
    c->Update();
    //scale hint1 to the pad coordinates
    Float_t rightmax2 = 1.1*simrecHistC->GetMaximum();
    Float_t scale2 = gPad->GetUymax()/rightmax2;
    simrecHistC->Scale(scale2);
    simrecHistC->Draw("SAME HIST");
    //draw an axis on the right side
    TGaxis *axis2 = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(),
			       gPad->GetUxmax(), gPad->GetUymax(),
			       0, rightmax2, 510, "+L");
    axis2->SetLineColor(kRed);
    axis2->SetLabelColor(kRed);
    axis2->Draw();
*/

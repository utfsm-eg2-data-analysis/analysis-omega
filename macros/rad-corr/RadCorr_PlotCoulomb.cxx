#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void RadCorr_PlotCoulomb() {
  // Radiative corrections: plot coulomb correction factors for electrons obtained from EXTERNALS

  // Custom binning, based on gExternalsDir + "/Utilities/include/Binning.hxx"
  Double_t kEdgesNu_extern[7] = {2.2, 2.58, 2.96, 3.35, 3.68, 3.94, 4.2};
  Double_t kEdgesQ2_extern[6] = {1, 1.25, 1.51, 1.92, 2.96, 4.0};

  const Int_t NbinsNu = (Int_t)(sizeof(kEdgesNu_extern) / sizeof(kEdgesNu_extern[0])) - 1;
  const Int_t NbinsQ2 = (Int_t)(sizeof(kEdgesQ2_extern) / sizeof(kEdgesQ2_extern[0])) - 1;
  const Int_t Ntargets = 4;

  TString targetSufix[Ntargets] = {"d2", "C12", "Fe56", "Pb208"};
  Color_t targetColor[Ntargets] = {kGreen, kRed, kBlue, kBlack};

  /*** INPUT ***/

  std::ifstream ExternalsFiles[Ntargets];
  Double_t RadCorrFactor[Ntargets][NbinsQ2][NbinsNu];

  for (Int_t tt = 0; tt < Ntargets; tt++) {

    ExternalsFiles[tt].open(gExternalsDir + "/OUT/clas" + targetSufix[tt] + ".out", std::ios::in);

    std::string auxLine;
    TString auxString[13];  // 13 = number of columns in the .out files
    Int_t countLine = 0;
    Int_t binInNu;
    Int_t binInQ2;
    while (getline(ExternalsFiles[tt], auxLine)) {
      // std::cout << auxLine << std::endl;
      // given the first line represents the name of the columns
      if (countLine > 0) {
        for (Int_t i = 0; i < 13; i++) {
          auxString[i] = ((TObjString *)(((TString)auxLine).Tokenize("   ")->At(i)))->String();
          // std::cout << auxString[i] << std::endl;
        }
        binInNu = (countLine - 1) / NbinsQ2;
        binInQ2 = (countLine - 1) - NbinsQ2 * binInNu;
        // Column 5: Sig_Born
        // Column 12: C_cor
        RadCorrFactor[tt][binInQ2][binInNu] = auxString[12].Atof();
      }
      countLine++;
    }
  }

  // DEBUG

  /*
    for (Int_t tt = 0; tt < Ntargets; tt++) {
      for (Int_t n = 0; n < NbinsNu; n++) {
        for (Int_t q = 0; q < NbinsQ2; q++) {
          std::cout << targetSufix[tt] << "_" << n << "_" << q << ": " << RadCorrFactor[tt][q][n] << std::endl;
        }
      }
    }
  */

  /*** GRAPHS ***/

  // fill arrays
  Double_t Empty[NbinsNu];
  Double_t BinGeoCenter[NbinsNu];  // geometrical center
  for (Int_t n = 0; n < NbinsNu; n++) {
    Empty[n] = 0;
    BinGeoCenter[n] = (kEdgesNu_extern[n] + kEdgesNu_extern[n + 1]) / 2.;
  }

  // define graphs
  TGraphErrors *RCgraph[Ntargets][NbinsQ2];
  for (Int_t tt = 0; tt < Ntargets; tt++) {
    for (Int_t q = 0; q < NbinsQ2; q++) {
      RCgraph[tt][q] = new TGraphErrors(NbinsNu, BinGeoCenter, RadCorrFactor[tt][q], Empty, Empty);
      // set graphs' titles and axis
      if (tt == 0) {
        RCgraph[tt][q]->SetTitle(Form("%.2f < Q^{2} < %.2f", kEdgesQ2_extern[q], kEdgesQ2_extern[q + 1]));
        RCgraph[tt][q]->GetXaxis()->SetTitle("#nu (GeV)");
        // RCgraph[tt][q]->GetXaxis()->SetNdivisions(500 + Nbins, kFALSE);
        // RCgraph[tt][q]->GetXaxis()->SetLimits(EdgesKinvar[0], EdgesKinvar[Nbins]);
        RCgraph[tt][q]->GetYaxis()->SetTitle("#delta_{CC}");
        RCgraph[tt][q]->GetYaxis()->SetRangeUser(1., 1.075);
      }
      // set graphs' style
      RCgraph[tt][q]->SetMarkerStyle(20);
      RCgraph[tt][q]->SetMarkerSize(1);
      RCgraph[tt][q]->SetMarkerColor(targetColor[tt]);
    }
  }

  /*** CANVAS ***/

  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLineWidth(2);

  // set margin sizes
  // gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  // gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);

  gStyle->SetOptStat(0);

  TCanvas *can1 = new TCanvas("rc-factors_coulomb", "rc-factors_coulomb", 1800, 1200);
  can1->Divide(3, 2, 0.01, 0.01);

  for (Int_t q = 0; q < NbinsQ2; q++) {
    can1->cd(q + 1);
    gPad->SetGridy(1);

    RCgraph[0][q]->Draw("AP");
    RCgraph[1][q]->Draw("P");
    RCgraph[2][q]->Draw("P");
    RCgraph[3][q]->Draw("P");

    // legend
    TLegend *legend = new TLegend(0.2, 0.65, 0.3, 0.85);  // x1,y1,x2,y2
    legend->AddEntry(RCgraph[0][q], "D", "p");
    legend->AddEntry(RCgraph[1][q], "C", "p");
    legend->AddEntry(RCgraph[2][q], "Fe", "p");
    legend->AddEntry(RCgraph[3][q], "Pb", "p");
    legend->SetFillStyle(1001);
    legend->SetFillColor(kWhite);
    legend->SetTextFont(62);
    legend->SetTextSize(0.04);
    legend->SetBorderSize(1);
    legend->Draw();
  }
}
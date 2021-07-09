#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef SETALIASES_CXX
#include "SetAliases.cxx"
#endif

void RadCorr_PlotHapradRatios() {
  // Radiative corrections: plot radiative correction factors for hadrons obtained from HAPRAD_CPP

  const Int_t Nbins = 36;

  const Int_t Ntargets = 4;
  TString targetSufix[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {kGreen, kRed, kBlue, kBlack};

  /*** INPUT ***/

  std::ifstream HapradFiles[Ntargets];
  Double_t RadCorrFactor[Ntargets][Nbins];

  for (Int_t tt = 0; tt < Ntargets; tt++) {

    HapradFiles[tt].open(gHapradDir + "/Utilities/bin/RCFactor_" + targetSufix[tt] + ".txt", std::ios::in);

    std::string auxLine;
    TString auxString[7];  // number of columns in the .txt file
    Int_t countLine = 0;
    Int_t binInPhiPQ;
    TObjString *auxObjString;
    while (getline(HapradFiles[tt], auxLine)) {
      //std::cout << countLine << ": " << auxLine << std::endl;
      // ignore the first line that represents the name of the columns
      if (countLine > 0) {
        // retrieve each column
        for (Int_t i = 0; i < 7; i++) {
          auxObjString = (TObjString *)(((TString)auxLine).Tokenize("\t")->At(i));
          auxString[i] = auxObjString->String();
          //std::cout << auxString[i] << std::endl;
        }
        // store variables of interest
        // Column 0: BinInPhiPQ
        binInPhiPQ = auxString[0].Atoi();
        // Column 6 or 7: Rad Corr Factor
        RadCorrFactor[tt][binInPhiPQ] = auxString[6].Atof();
      }
      countLine++;
    }
  }

  // DEBUG
  /*
    for (Int_t tt = 0; tt < Ntargets; tt++) {
      for (Int_t p = 0; p < Nbins; p++) {
        std::cout << targetSufix[tt] << "_" << p << ": " << RadCorrFactor[tt][p] << std::endl;
      }
      std::cout << std::endl;
    }
  */

  /*** HISTS ***/

  TH1D *hist[Ntargets];
  TH1D *ratio[Ntargets];
  for (Int_t tt = 0; tt < Ntargets; tt++) {
    hist[tt] = new TH1D(Form("hist_%d", tt), "", Nbins, -180, 180);
    ratio[tt] = new TH1D(Form("ratio_%d", tt), "", Nbins, -180, 180);
    for (Int_t p = 0; p < Nbins; p++) {
      hist[tt]->SetBinContent(p + 1, RadCorrFactor[tt][p]);
    }
    // calculate ratio
    ratio[tt]->Divide(hist[tt], hist[0]);
    // style
    // hist[tt]->SetTitle(Form("%.2f < Q^{2} < %.2f", kEdgesQ2_extern[q], kEdgesQ2_extern[q + 1]));
    ratio[tt]->GetXaxis()->SetTitle("#phi_{PQ} (deg)");
    ratio[tt]->GetYaxis()->SetTitle("RC Factor(A) / RC Factor(D)");
    ratio[tt]->GetYaxis()->SetRangeUser(0.98, 1.01);
    ratio[tt]->SetMarkerStyle(20);
    ratio[tt]->SetMarkerSize(1);
    ratio[tt]->SetMarkerColor(targetColor[tt]);
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

  TCanvas *can1 = new TCanvas("rc-ratios_haprad", "rc-ratios_haprad", 960, 960);

  gPad->SetGridy(1);

  ratio[1]->Draw("P HIST");
  ratio[2]->Draw("P HIST SAME");
  ratio[3]->Draw("P HIST SAME");

  // legend
  TLegend *legend = new TLegend(0.2, 0.65, 0.3, 0.85);  // x1,y1,x2,y2
  legend->AddEntry(ratio[1], "C", "p");
  legend->AddEntry(ratio[2], "Fe", "p");
  legend->AddEntry(ratio[3], "Pb", "p");
  legend->SetFillStyle(1001);
  legend->SetFillColor(kWhite);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(1);
  legend->Draw();
}
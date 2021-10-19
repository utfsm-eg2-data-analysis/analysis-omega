#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Ntargets = 2;
const Int_t NbinsPhiPQ = 4;

void Draw_RadCorrRatios(TString StoreOption = "") {
  // Draw ratio of Radiative Correction Factors obtained for "D" and "A", in PhiPQ binning

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  /*** MAIN ***/

  Double_t RadCorrFactor[Ntargets][NbinsPhiPQ];
  Double_t RadCorrRatio[NbinsPhiPQ];

  TString titleAxis = "#phi_{PQ} [deg]";
  Double_t EdgesPhiPQ[NbinsPhiPQ + 1] = {-180., -90., 0., 90., 180.};
  TString histProperties = Form("(%i, %.2f, %.2f)", NbinsPhiPQ, EdgesPhiPQ[0], EdgesPhiPQ[NbinsPhiPQ]);

  TString targetString[Ntargets] = {"D", "A"};

  std::ifstream InputFile[Ntargets];

  // loop over targets
  for (Int_t t = 0; t < Ntargets; t++) {

    InputFile[t].open(gProDir + "/gfx/rad-corr_omega/RCFactor_omega_" + targetString[t] + ".txt", std::ios::in);

    std::string auxLine;
    TString auxString[7];  // number of columns in the .txt file
    Int_t countLine = 0;
    Int_t binInPhiPQ;
    TObjString *auxObjString;

    while (getline(InputFile[t], auxLine)) {
      // ignore the first line that represents the name of the columns
      if (countLine > 0) {
        // retrieve each column
        for (Int_t i = 0; i < 7; i++) {
          auxObjString = (TObjString *)(((TString)auxLine).Tokenize("\t")->At(i));
          auxString[i] = auxObjString->String();
        }
        // store variables of interest
        // Column 0: BinInPhiPQ
        binInPhiPQ = auxString[0].Atoi();
        // Column 6 or 7: Rad Corr Factor
        RadCorrFactor[t][binInPhiPQ] = auxString[6].Atof();
      }
      countLine++;
    }
  }

  /*** GRAPHS ***/

  // define arrays
  Double_t binCenter[NbinsPhiPQ];
  Double_t binError[NbinsPhiPQ];
  Double_t empty[NbinsPhiPQ];

  // fill arrays
  for (Int_t i = 0; i < NbinsPhiPQ; i++) {
    empty[i] = 0;
    binCenter[i] = (EdgesPhiPQ[i] + EdgesPhiPQ[i + 1]) / 2.;
    binError[i] = (EdgesPhiPQ[i + 1] - EdgesPhiPQ[i]) / TMath::Sqrt(12);
    // do the division!
    RadCorrRatio[i] = RadCorrFactor[1][i] / RadCorrFactor[0][i];
  }

  // set graphs
  TGraphErrors *RadCorrGraph;

  RadCorrGraph = new TGraphErrors(NbinsPhiPQ, binCenter, RadCorrRatio, binError, empty);

  // style
  RadCorrGraph->SetTitle("");
  RadCorrGraph->SetMarkerColor(myBlack);
  RadCorrGraph->SetLineColor(myBlack);
  RadCorrGraph->SetLineWidth(3);
  RadCorrGraph->SetMarkerStyle(20);
  RadCorrGraph->SetMarkerSize(1.5);

  // set axis
  RadCorrGraph->GetYaxis()->SetRangeUser(0.95, 1.0);

  RadCorrGraph->GetYaxis()->SetTitle("#delta^{RC}_{A} / #delta^{RC}_{D}");
  RadCorrGraph->GetYaxis()->SetTitleSize(0.05);
  RadCorrGraph->GetYaxis()->SetTitleOffset(1.4);
  RadCorrGraph->GetYaxis()->SetMaxDigits(3);

  RadCorrGraph->GetXaxis()->SetTitle(titleAxis);
  RadCorrGraph->GetXaxis()->SetTitleSize(0.05);

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "rad-corr-ratios";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 1080, 1080);

  RadCorrGraph->Draw("AP");

  // legend
  TLegend *legend = new TLegend(0.2, 0.75, 0.5, 0.9);  // x1,y1,x2,y2
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  // legend->SetHeader("Ratio between Solid and Liquid Radiative Correction Factors");
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->Draw();

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/rad-corr_omega";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}

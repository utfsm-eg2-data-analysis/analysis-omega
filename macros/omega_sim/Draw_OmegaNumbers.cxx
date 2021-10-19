#ifndef GLOBAL_H
#include "Global.h"
#endif

#ifndef DRAWFUNCTIONS_CXX
#include "DrawFunctions.cxx"
#endif

const Int_t Nkinvars = 4;
const Int_t Ntargets = 4;
const Int_t Nbins = 4;

void Draw_OmegaNumbers(TString StoreOption = "") {
  // draw the obtained number of omegas after background subtraction via event-mixing (sim)

  // prevent output printing
  if (StoreOption != "") {
    gROOT->SetBatch(kTRUE);
  }

  Double_t intOmega[Nkinvars][Ntargets][Nbins];
  Double_t intOmegaError[Nkinvars][Ntargets][Nbins];

  /*** MAIN ***/

  TString kinvarOption[4] = {"Q2", "Nu", "wZ", "wPt2"};
  TString titleAxis[4];
  TString histProperties[4];
  titleAxis[0] = "Q^{2} [GeV^{2}]";
  histProperties[0] = "(100, 1., 4.)";
  titleAxis[1] = "#nu [GeV]";
  histProperties[1] = "(100, 2.2, 4.2)";
  titleAxis[2] = "z_{h}";
  histProperties[2] = "(100, 0.5, 0.9)";
  titleAxis[3] = "p_{T}^{2} [GeV^{2}]";
  histProperties[3] = "(100, 0., 1.5)";

  Double_t EdgesKinvar[Nkinvars][Nbins + 1];
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[0][i] = kEdgesQ2[i];
  }
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[1][i] = kEdgesNu[i];
  }
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[2][i] = kEdgesZ[i];
  }
  for (Int_t i = 0; i < Nbins + 1; i++) {
    EdgesKinvar[3][i] = kEdgesPt2[i];
  }

  TString targetString[Ntargets] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[Ntargets] = {myGreen, myRed, myBlue, myBlack};

  TFile *rootInputFile[Nkinvars][Ntargets];

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      rootInputFile[k][t] = new TFile(gProDir + "/gfx/omega_sim/evnt-mixing_" + targetString[t] + "_" + kinvarOption[k] + ".root");
      // loop over bins
      for (Int_t i = 0; i < Nbins; i++) {

        TF1 *Fit = (TF1 *)rootInputFile[k][t]->Get(Form("model_%i", i));
        TH1D *Hist = (TH1D *)rootInputFile[k][t]->Get(Form("sub_%i", i));

        Double_t fitMean = Fit->GetParameter(1);
        Double_t fitSigma = Fit->GetParameter(2);

        // remove negative entries
        intOmega[k][t][i] = 0;
        intOmegaError[k][t][i] = 0;
        for (Int_t s = TMath::Floor((fitMean - 3 * fitSigma - 0.66) / 0.01); s <= TMath::Ceil((fitMean + 3 * fitSigma - 0.66) / 0.01);
             s++) {
          if (Hist->GetBinContent(s) > 0) intOmega[k][t][i] += Hist->GetBinContent(s);
          if (Hist->GetBinContent(s) > 0) intOmegaError[k][t][i] += Hist->GetBinError(s) * Hist->GetBinError(s);
        }
        intOmegaError[k][t][i] = TMath::Sqrt(intOmegaError[k][t][i]);
      }
    }
  }

  /*** GRAPHS ***/

  // creating and filling histograms
  TGraphErrors *omegaGraph[Nkinvars][Ntargets];

  // define arrays
  Double_t binCenter[Nkinvars][Nbins];
  Double_t binError[Nkinvars][Nbins];

  // fill arrays

  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t i = 0; i < Nbins; i++) {
      binCenter[k][i] = (EdgesKinvar[k][i] + EdgesKinvar[k][i + 1]) / 2.;
      binError[k][i] = (EdgesKinvar[k][i + 1] - EdgesKinvar[k][i]) / TMath::Sqrt(12);
    }
  }

  // set graphs
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      omegaGraph[k][t] = new TGraphErrors(Nbins, binCenter[k], intOmega[k][t], binError[k], intOmegaError[k][t]);

      // style
      omegaGraph[k][t]->SetTitle("");
      omegaGraph[k][t]->SetMarkerColor(targetColor[t]);
      omegaGraph[k][t]->SetLineColor(targetColor[t]);
      omegaGraph[k][t]->SetLineWidth(3);
      omegaGraph[k][t]->SetMarkerStyle(20);
      omegaGraph[k][t]->SetMarkerSize(1.5);
    }
  }

  /*** SET Y AXIS ***/

  for (Int_t k = 0; k < Nkinvars; k++) {
    omegaGraph[k][0]->GetYaxis()->SetRangeUser(0., 1.2 * TMath::MaxElement(Nbins, omegaGraph[k][0]->GetY()));

    omegaGraph[k][0]->GetYaxis()->SetTitle("N_{#omega}^{rec}");
    omegaGraph[k][0]->GetYaxis()->SetTitleSize(0.06);
    omegaGraph[k][0]->GetYaxis()->SetTitleOffset(1.2);
    omegaGraph[k][0]->GetYaxis()->SetMaxDigits(3);

    omegaGraph[k][0]->GetXaxis()->SetTitle(titleAxis[k]);
    omegaGraph[k][0]->GetXaxis()->SetTitleSize(0.06);
  }

  /*** FIX Y-AXIS ***/

  Double_t MaxRangeSim[Nkinvars] = {0, 0, 0, 0};
  for (Int_t k = 0; k < Nkinvars; k++) {
    for (Int_t t = 0; t < Ntargets; t++) {
      // get the maximum of an array of length Nbins, and compare it with MaxRangeSim
      if (TMath::MaxElement(Nbins, omegaGraph[k][t]->GetY()) > MaxRangeSim[k]) {
        MaxRangeSim[k] = TMath::MaxElement(Nbins, omegaGraph[k][t]->GetY());
      }
    }
  }

  /*** DRAW ***/

  SetMyStyle();

  TString CanvasName = "omega-numbers_sim";
  TCanvas *c = new TCanvas(CanvasName, CanvasName, 2160, 2160);
  c->Divide(2, 2, 0.001, 0.001);  // nx, ny, margins

  // set y-axis for all plots
  omegaGraph[0][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeSim[0]);
  omegaGraph[1][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeSim[1]);
  omegaGraph[2][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeSim[2]);
  omegaGraph[3][0]->GetYaxis()->SetRangeUser(0., 1.2 * MaxRangeSim[3]);

  c->cd(1);
  omegaGraph[0][0]->Draw("AP");
  omegaGraph[0][1]->Draw("P");
  omegaGraph[0][2]->Draw("P");
  omegaGraph[0][3]->Draw("P");

  c->cd(2);
  omegaGraph[1][0]->Draw("AP");
  omegaGraph[1][1]->Draw("P");
  omegaGraph[1][2]->Draw("P");
  omegaGraph[1][3]->Draw("P");

  // legend
  TLegend *legend = new TLegend(0.6, 0.65, 0.85, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(omegaGraph[0][0], "D (Sim. Rec.)", "pl");
  legend->AddEntry(omegaGraph[0][1], "C (Sim. Rec.)", "pl");
  legend->AddEntry(omegaGraph[0][2], "Fe (Sim. Rec.)", "pl");
  legend->AddEntry(omegaGraph[0][3], "Pb (Sim. Rec.)", "pl");
  legend->SetFillStyle(0);
  legend->SetTextFont(62);
  legend->SetTextSize(0.04);
  legend->SetBorderSize(0);
  legend->Draw();

  c->cd(3);
  omegaGraph[2][0]->Draw("AP");
  omegaGraph[2][1]->Draw("P");
  omegaGraph[2][2]->Draw("P");
  omegaGraph[2][3]->Draw("P");

  c->cd(4);
  omegaGraph[3][0]->Draw("AP");
  omegaGraph[3][1]->Draw("P");
  omegaGraph[3][2]->Draw("P");
  omegaGraph[3][3]->Draw("P");

  /*** OUTPUT ***/

  if (StoreOption != "") {
    TString OutputDir = gProDir + "/gfx/omega_sim";
    system("mkdir -p " + OutputDir);
    c->Print(OutputDir + "/" + CanvasName + "." + StoreOption);
  }
}

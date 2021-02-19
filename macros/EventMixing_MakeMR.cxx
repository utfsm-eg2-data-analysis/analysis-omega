#include "Global.h"

// from FitSub.cxx results

void EventMixing_MakeMR(TString kinvarOption) {
  
  const Int_t Nbins = 4;
  const Int_t Ntargets = 4;
  
  Double_t fitOmega[Ntargets][Nbins];
  Double_t fitOmegaError[Ntargets][Nbins]; 

  /*** INPUT ***/

  Int_t kinvarIndex;
  Double_t EdgesKinvar[Nbins + 1];
  if (kinvarOption == "Q2") {
    kinvarIndex = 0;
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarIndex = 1;
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesNu[i];
  } else if (kinvarOption == "wZ") {
    kinvarIndex = 2;
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesZ[i];
  } else if (kinvarOption == "wPt2") {
    kinvarIndex = 3;
    for (Int_t i = 0; i < Nbins + 1; i++) EdgesKinvar[i] = kEdgesPt2[i];
  }

  TString targetString[4] = {"D", "C", "Fe", "Pb"};
  Color_t targetColor[4] = {kGreen+3, kRed, kBlue, kBlack};

  /*** MAIN ***/
  
  TFile *rootInputFile[Ntargets];
  TH1F *omegaHist[Ntargets];
  TH1F *omegaMR[Ntargets];
  
  for (Int_t t = 0; t < Ntargets; t++) {
    rootInputFile[t] = new TFile(gProDir + "/macros/out/evnt-mixing_fit-sub_" + targetString[t] + ".root");
    omegaHist[t] = new TH1F("omegaNumber_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    omegaMR[t] = new TH1F("omegaMR_" + targetString[t], "", Nbins, EdgesKinvar[0], EdgesKinvar[Nbins]);
    for (Int_t i = 0; i < Nbins; i++) {  // i for bins
      TF1 *Fit = (TF1 *)rootInputFile[t]->Get(Form("fit_%d_%d", i, kinvarIndex));
      TFitResultPtr FitResult = (TFitResult *)rootInputFile[t]->Get(Form("TFitResult-sub_%d_%d-fit_%d_%d", i, kinvarIndex, i, kinvarIndex));
      std::vector<Double_t> Parameters = FitResult->Parameters();
      std::vector<Double_t> Errors = FitResult->Errors();
      fitOmega[t][i] = Fit->Integral(0.65, 0.90)/0.01;
      fitOmegaError[t][i] = Fit->IntegralError(0.65, 0.90, FitResult->GetParams(), FitResult->GetCovarianceMatrix().GetMatrixArray(), 1e-1)/0.01;
      // fill hist
      omegaHist[t]->SetBinContent(i + 1, fitOmega[t][i]);
      omegaHist[t]->SetBinError(i + 1, fitOmegaError[t][i]);
      // divide solid targets with liquid target
      if (t > 0) omegaMR[t]->Divide(omegaHist[t], omegaHist[0]);
    }
  }

  /*** DEFINE TGRAPHERRORS ***/
  
  // define arrays
  Double_t empty[Nbins];
  Double_t MR_x[Nbins];
  Double_t MR_xerr[Nbins];
  Double_t MR_y[Ntargets][Nbins];
  Double_t MR_yerr[Ntargets][Nbins];

  // fill arrays
  for (Int_t i = 0; i < Nbins; i++) {
    empty[i] = 0.;
    MR_x[i] = (EdgesKinvar[i] + EdgesKinvar[i + 1]) / 2.;
    MR_xerr[i] = (EdgesKinvar[i + 1] - EdgesKinvar[i]) / TMath::Sqrt(12);
    for (Int_t tt = 1; tt < Ntargets; tt++) {  // solid targets only
      MR_y[tt][i] = omegaMR[tt]->GetBinContent(i + 1);
      MR_yerr[tt][i] = omegaMR[tt]->GetBinError(i + 1);      
    }
  }

  std::cout << "N OMEGA DEUT = ";
  for (Int_t i = 0; i < Nbins; i++) std::cout << fitOmega[0][i] << "\t";
  std::cout << std::endl;
  std::cout << "N OMEGA CARB = ";
  for (Int_t i = 0; i < Nbins; i++) std::cout << fitOmega[1][i] << "\t";
  std::cout << std::endl;
  std::cout << "RATIO CARB/DEUT = ";
  for (Int_t i = 0; i < Nbins; i++) std::cout << MR_y[1][i] << "\t";
  std::cout << std::endl;

  // define graphs
  TGraphErrors *MRgraph[Ntargets];
  for (Int_t tt = 1; tt < Ntargets; tt++) { // solid targets only  
    MRgraph[tt] = new TGraphErrors(Nbins, MR_x, MR_y[tt], MR_xerr, MR_yerr[tt]);
  }

  // set style
  MRgraph[1]->SetTitle("Multiplicity Ratio: #omega");
  // MRgraph[1]->GetXaxis()->SetTitle(kinvarTitle);
  MRgraph[1]->GetXaxis()->CenterTitle();
  MRgraph[1]->GetXaxis()->SetNdivisions(400 + Nbins, kFALSE);
  MRgraph[1]->GetXaxis()->SetLimits(EdgesKinvar[0], EdgesKinvar[Nbins]);
  MRgraph[1]->GetYaxis()->SetTitle("R_{#omega}");
  MRgraph[1]->GetYaxis()->CenterTitle();
  MRgraph[1]->GetYaxis()->SetRangeUser(0., 2.0);

  for (Int_t tt = 1; tt < Ntargets; tt++) { // solid targets only 
    MRgraph[tt]->SetMarkerStyle(21);
    MRgraph[tt]->SetMarkerSize(1.5);
    MRgraph[tt]->SetMarkerColor(targetColor[tt]);
    MRgraph[tt]->SetLineColor(targetColor[tt]);
    MRgraph[tt]->SetLineWidth(3);
    
  }  
  
  /*** DRAW ***/
  
  // define canvas
  TCanvas *c = new TCanvas("evnt-mixing_MR_" + kinvarOption, "", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  MRgraph[1]->Draw("AP");  // Carbon
  MRgraph[2]->Draw("P");   // Iron
  MRgraph[3]->Draw("P");   // Lead

    // legend position
  /*
  Double_t legendX = 0.8;
  if (kinvarOption == "Nu") legendX = 0.1;

  // legend
  TLegend *legend = new TLegend(legendX, 0.75, legendX + 0.1, 0.9);  // x1,y1,x2,y2
  legend->AddEntry(CarbonMR_gr, "Carbon", "p");
  legend->AddEntry(IronMR_gr, "Iron", "p");
  legend->AddEntry(LeadMR_gr, "Lead", "p");
  legend->Draw();

  c->Print(plotFile);  // output file
  */
}

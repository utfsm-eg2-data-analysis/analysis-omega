/**************************************/
/* SampFrac_points.cxx                */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// final stage: plot points for mean & (mean +- 2.5sigma) depending on momentum bin

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/SampFrac";

// options
TString setOption;
TString targetOption;
TString tayaOption;

Double_t mean[50], mean_error[50];
Double_t sigma[50], sigma_error[50];
Int_t Nbins, minBin, maxBin;

// input tree
TString treeFile;

// input parameters from fits
TString fitDir;
TString textFile;

// output
TString plotFile;
TString plotFile_mean;
TString plotFile_sigma;
TString plotFile_afterfit;

/*** Mathematical Functions ***/

Double_t secondPol(Double_t *x, Double_t *par) {
  return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}

// Sqrt of the Inverse = SI
Double_t siFunction(Double_t *x, Double_t *par) {
  return TMath::Sqrt(par[0]*par[0] + par[1]*par[1]/x[0]);
}

Double_t topFunction(Double_t *x, Double_t *par) {
  return secondPol(x, par) + 2.5*siFunction(x, &par[3]);
}

Double_t botFunction(Double_t *x, Double_t *par) {
  return secondPol(x, par) - 2.5*siFunction(x, &par[3]);
}

int main(int argc, char **argv) {

  /*** Parse Command Line ***/
  
  if (argc < 3) {
    std::cout << "Two arguments <set> <option> are required." << std::endl;
    exit(0);
  } else {
    setOption    = argv[1];
    targetOption = argv[2];
    // tree
    treeFile = outDir + "/samp-frac_" + setOption + "-" + targetOption + ".root";
    // fits
    fitDir = outDir + "/" + setOption + "-" + targetOption;
    // outputs
    textFile = fitDir + "/samp-frac-points_" + setOption + "-" + targetOption + ".dat";
    plotFile = fitDir + "/samp-frac-points_" + setOption + "-" + targetOption + ".png";
    plotFile_mean  = fitDir + "/samp-frac-mean_" + setOption + "-" + targetOption + ".png";
    plotFile_sigma = fitDir + "/samp-frac-sigma_" + setOption + "-" + targetOption + ".png";
    plotFile_afterfit = fitDir + "/samp-frac-afterfit_" + setOption + "-" + targetOption + ".png";
    // to compare
    tayaOption = argv[3];
    if (tayaOption != "") plotFile_afterfit = fitDir + "/samp-frac-afterfit_" + setOption + "-" + targetOption + "_taya.png";
  }

  /*** Options ***/
  
  if (setOption == "old" && targetOption == "C") {
    minBin = 7;
    maxBin = 30;
  } else if (setOption == "old" && targetOption == "Fe") {
    minBin = 8;
    maxBin = 28;
  } else if (setOption == "usm") {
    minBin = 7;
    maxBin = 30;
  } else if (setOption == "jlab" && targetOption == "D") {
    minBin = 7;
    maxBin = 27;
  } else if (setOption == "jlab" && targetOption != "D") {
    minBin = 7;
    maxBin = 28;
  } else if (setOption == "all") {
    minBin = 7;
    maxBin = 30;
  }
  Nbins = maxBin - minBin;
  
  /*** Read data ***/

  TString fitFile;
  
  for (Int_t i = minBin; i <= maxBin; i++) {    
    fitFile = fitDir + "/samp-frac-fit_" + setOption + "-" + targetOption + "_" + Form("%d", i) + ".dat";
    std::cout << "Reading " << fitFile << " ..." << std::endl;
    std::ifstream inFile(fitFile);

    TString auxString1, auxString2;
    Int_t l = 0; // line counter
    while (inFile >> auxString1 >> auxString2) {
      l++;
      if (l == 1) { // first line
        mean[i]       = auxString1.Atof();
        mean_error[i] = auxString2.Atof();
	std::cout << "  mean  = " << mean[i] << " +- " << mean_error[i] << std::endl;
      } else if (l == 2) {
        sigma[i]       = auxString1.Atof();
	sigma_error[i] = auxString2.Atof();
	std::cout << "  sigma = " << sigma[i] << " +- " << sigma_error[i] << std::endl;
      }
    }
    inFile.close();
  }
  
  /*** Histograms ***/

  // set hists
  Double_t minRange = (minBin-1)*0.1;
  Double_t maxRange = maxBin*0.1;
  TH1F *meanHist = new TH1F("meanHist", "", Nbins, minRange, maxRange);
  TH1F *sigmaHist = new TH1F("sigmaHist", "", Nbins, minRange, maxRange);

  // fill hists
  for (Int_t cc = minBin; cc <= maxBin; cc++) {
    meanHist->SetBinContent(cc + 1 - minBin, mean[cc]);
    meanHist->SetBinError(cc + 1 - minBin, mean_error[cc]);
    
    sigmaHist->SetBinContent(cc + 1 - minBin, sigma[cc]);
    sigmaHist->SetBinError(cc + 1 - minBin, sigma_error[cc]);
  }

  TH1F *topHist = new TH1F("topHist", "", Nbins, minRange, maxRange);
  topHist->Add(meanHist, sigmaHist, 1, 2.5);
  
  TH1F *botHist = new TH1F("botHist", "", Nbins, minRange, maxRange);
  botHist->Add(meanHist, sigmaHist, 1, -2.5);

  // styles
  topHist->SetFillStyle(0);
  topHist->SetLineColor(kBlack);
  topHist->SetLineWidth(3);
  topHist->GetYaxis()->SetRangeUser(0.1, 0.4);

  meanHist->SetFillStyle(0);
  meanHist->SetLineColor(kBlack);
  meanHist->SetLineWidth(3);

  botHist->SetFillStyle(0);
  botHist->SetLineColor(kBlack);
  botHist->SetLineWidth(3);

  /*** First fit: mean ***/

  // define function
  TF1 *meanFcn = new TF1("meanFcn", secondPol, minRange, maxRange, 3);

  // setting initial guess values
  meanFcn->SetParameter(0, 2.6e-1);
  meanFcn->SetParameter(1, 8.9e-3);
  meanFcn->SetParameter(2, -1.9e-3);

  meanHist->Fit("meanFcn", "F", "goff"); // REN0

  Double_t meanFcn_params[3];
  meanFcn->GetParameters(meanFcn_params);

  // draw
  TCanvas *c0 = new TCanvas("c0", "c0", 1000, 1000);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(111);
    
  meanHist->Draw("E");

  gPad->Update();
  TPaveStats *paramsBox = (TPaveStats*) meanHist->FindObject("stats");
  paramsBox->SetX1NDC(0.6);
  paramsBox->SetX2NDC(0.9);
  paramsBox->SetY1NDC(0.1);
  paramsBox->SetY2NDC(0.25);
  
  meanFcn->SetLineWidth(3);
  meanFcn->SetLineColor(kRed);
  meanFcn->Draw("SAME");
  
  c0->Print(plotFile_mean); // output file

  /*** Second fit: sigma ***/

  // define function
  TF1 *sigmaFcn = new TF1("sigmaFcn", siFunction, minRange, maxRange, 2);

  // setting initial guess values
  sigmaFcn->SetParameter(0, 5.7e-3);
  sigmaFcn->SetParameter(1, 3.05e-2);

  sigmaHist->Fit("sigmaFcn", "F", "goff"); // REN0

  Double_t sigmaFcn_params[2];
  sigmaFcn->GetParameters(sigmaFcn_params);

  // draw
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(111);
    
  sigmaHist->Draw("E");

  gPad->Update();
  TPaveStats *paramsBox2 = (TPaveStats*) sigmaHist->FindObject("stats");
  paramsBox2->SetX1NDC(0.6);
  paramsBox2->SetX2NDC(0.9);
  paramsBox2->SetY1NDC(0.75);
  paramsBox2->SetY2NDC(0.9);
  
  sigmaFcn->SetLineWidth(3);
  sigmaFcn->SetLineColor(kBlue);
  sigmaFcn->Draw("SAME");
  
  c1->Print(plotFile_sigma); // output file
  
  /*** 2D Hist ***/

  // color stuff, smoran
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

  // input tree
  TChain *tElectrons = new TChain();
  tElectrons->Add(treeFile + "/ntuple_e");

  TH2F *theHist;
  tElectrons->Draw("Etot/P:P>>hist(100, 0., 5, 100, 0.1, 0.4)", "", "goff");
  theHist = (TH2F *)gROOT->FindObject("hist");
  
  theHist->SetContour(99);
  
  /*** Drawing ***/
  
  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetNumberContours(NCont); // colors, smoran

  theHist->Draw("COLZ");
  topHist->Draw("SAME");
  botHist->Draw("SAME");

  // fit again to prevent function and params box apparition
  meanHist->SetStats(0);
  meanHist->Fit("meanFcn", "F0", "goff"); // REN0
  meanHist->Draw("SAME");
  
  c2->Print(plotFile); // output file
  
  /*** Drawing - After fit ***/
  
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetNumberContours(NCont); // colors, smoran

  theHist->Draw("COLZ");
  topHist->Draw("SAME");
  botHist->Draw("SAME");

  // define functions beforehand
  TF1 *topFcn = new TF1("topFcn", topFunction, minRange, maxRange, 5);
  TF1 *botFcn = new TF1("botFcn", botFunction, minRange, maxRange, 5);
  TF1 *meanFcn_v1 = new TF1("meanFcn_v1", secondPol, minRange, maxRange, 3);

  if (tayaOption == "") {
    // fit again to prevent function and params box apparition
    meanHist->SetStats(0);
    meanHist->Fit("meanFcn", "F0", "goff"); // REN0
    meanHist->Draw("SAME");

    topFcn->SetParameter(0, meanFcn_params[0]);
    topFcn->SetParameter(1, meanFcn_params[1]);
    topFcn->SetParameter(2, meanFcn_params[2]);
    topFcn->SetParameter(3, sigmaFcn_params[0]);
    topFcn->SetParameter(4, sigmaFcn_params[1]);
    topFcn->SetLineColor(kWhite);
    topFcn->SetLineWidth(3);
    topFcn->Draw("SAME");

    botFcn->SetParameter(0, meanFcn_params[0]);
    botFcn->SetParameter(1, meanFcn_params[1]);
    botFcn->SetParameter(2, meanFcn_params[2]);
    botFcn->SetParameter(3, sigmaFcn_params[0]);
    botFcn->SetParameter(4, sigmaFcn_params[1]);
    botFcn->SetLineColor(kWhite);
    botFcn->SetLineWidth(3);
    botFcn->Draw("SAME");
  
    meanFcn->SetLineColor(kWhite);
    meanFcn->SetLineWidth(3);
    meanFcn->Draw("SAME");
  } else if (tayaOption == "taya") {
    // to compare, set taya parameters
    topFcn->SetParameter(0, 2.6e-1);
    topFcn->SetParameter(1, 8.9e-3);
    topFcn->SetParameter(2, -1.9e-3);
    topFcn->SetParameter(3, 5.7e-3);
    topFcn->SetParameter(4, 3.05e-2);
    topFcn->SetLineColor(kWhite);
    topFcn->SetLineWidth(3);
    topFcn->Draw("SAME");

    botFcn->SetParameter(0, 2.6e-1);
    botFcn->SetParameter(1, 8.9e-3);
    botFcn->SetParameter(2, -1.9e-3);
    botFcn->SetParameter(3, 5.7e-3);
    botFcn->SetParameter(4, 3.05e-2);
    botFcn->SetLineColor(kWhite);
    botFcn->SetLineWidth(3);
    botFcn->Draw("SAME");

    meanFcn_v1->SetParameter(0, 2.6e-1);
    meanFcn_v1->SetParameter(1, 8.9e-3);
    meanFcn_v1->SetParameter(2, -1.9e-3);
  
    meanFcn_v1->SetLineColor(kWhite);
    meanFcn_v1->SetLineWidth(3);
    meanFcn_v1->Draw("SAME");
  }
  
  c3->Print(plotFile_afterfit); // output file  
    
  return 0;
}

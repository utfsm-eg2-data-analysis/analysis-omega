/**************************************/
/* BinMigration_map.cxx               */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include "analysisConfig.h"

TString inputDir    = workDir + "/Acceptance/merged/old";
TString outputDir   = workDir + "/BinMigration";

int main() {

  // just in case
  system("mkdir -p " + outputDir);
  
  TString tarArray[4] = {"D", "C", "Fe", "Pb"};
  TString kinName[4] = {"Q2", "Nu", "Z", "Pt2"};
  TString kinVar[4] = {"Q", "N", "Z", "P"};
  
  TString targetOption;
  TString inputFile;
  TString currentHistName;
  
  Double_t gsimN[4][4][5];
  Double_t simrecN[4][4][5][5];
  
  for (Int_t t = 0; t < 4; t++) { // target loop
    targetOption = tarArray[t];
    for (Int_t k = 0; k < 4; k++) { // kinvar loop
      inputFile = inputDir + "/acceptance_" + targetOption + ".root";
      TFile *rootInputFile = new TFile(inputFile);
      for (Int_t i = 0; i < 5; i++) {
	currentHistName = "GSIM_" + targetOption + "_" + kinVar[k] + Form("%d", i);
	TH1F *gsimHist = (TH1F *)rootInputFile->Get(currentHistName);
	std::cout << currentHistName << " = " << gsimHist->GetEntries() << std::endl;
        gsimN[t][k][i] = gsimHist->GetEntries();
	for (Int_t j = 0; j < 5; j++) {
	  currentHistName = "SIMREC_" + targetOption + "_" + kinVar[k] + Form("%d", i) + kinVar[k] + Form("%d", j);
	  TH1F *simrecHist = (TH1F *)rootInputFile->Get(currentHistName);
	  std::cout << currentHistName << " = " << simrecHist->GetEntries() << std::endl;
	  simrecN[t][k][i][j] = simrecHist->GetEntries();
	}
      } // end of bins loop
    } // end of kinvar loop
  } //end of target loop

  TString plotFile;
  TString plotFile1;
  TString plotFile2;  
  for (Int_t t = 0; t < 4; t++) { // target loop
    targetOption = tarArray[t];
    for (Int_t k = 0; k < 4; k++) { // kinvar loop
      plotFile = outputDir + "/matrix_" + targetOption + "-" + kinName[k] + ".png";
      plotFile1 = outputDir + "/gsim_" + targetOption + "-" + kinName[k] + ".png";
      plotFile1 = outputDir + "/norm-matrix_" + targetOption + "-" + kinName[k] + ".png";
      TH2F *gsimMap    = new TH2F("gsimMap", "", 5, 0.5, 1., 5, 0.5, 1.);
      TH2F *theMap     = new TH2F("theMap", "", 5, 0.5, 1., 5, 0.5, 1.);
      TH2F *theMapNorm = new TH2F("theMapNorm", "", 5, 0.5, 1., 5, 0.5, 1.);
      Double_t normFactor[5] = {0, 0, 0, 0, 0};
      for (Int_t i = 0; i < 5; i++) {
	for (Int_t j = 0; j < 5; j++) {
	  // normal simrec map
	  theMap->SetBinContent(i+1, j+1, simrecN[t][k][i][j]);
	  theMap->GetXaxis()->SetBinLabel(i+1, "mc_" + kinVar[k] + Form("%d", i));
	  theMap->GetYaxis()->SetBinLabel(j+1, kinVar[k] + Form("%d", j));
	  // gsim map
	  gsimMap->SetBinContent(i+1, j+1, gsimN[t][k][i]);
	  // the map norm
	  normFactor[j] += simrecN[t][k][i][j];
	  theMapNorm->GetXaxis()->SetBinLabel(i+1, "mc_" + kinVar[k] + Form("%d", i));
	  theMapNorm->GetYaxis()->SetBinLabel(j+1, kinVar[k] + Form("%d", j));
	}
      }
      // normal map
      /*
      TCanvas *c = new TCanvas("c", "c", 1000, 1000);
      gStyle->SetOptStat(0);
      theMap->SetTitle("Bin Migration Map for " + targetOption + " Simulations");
      theMap->Draw("COLZ TEXT");
      c->Print(plotFile);
      */
      // gsim map
      /*
      TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
      gStyle->SetOptStat(0);
      gsimMap->Draw("TEXT");
      c1->Print(plotFile1);
      */
      // theMapNorm->Divide(theMap, gsimMap);
      for (Int_t i = 0; i < 5; i++) {      
	for (Int_t j = 0; j < 5; j++) {
	  theMapNorm->SetBinContent(i+1, j+1, simrecN[t][k][i][j]/normFactor[j]);
	}
      }
      TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
      gStyle->SetOptStat(0);
      gStyle->SetPaintTextFormat(".2g");
      theMapNorm->SetTitle("Bin Migration Map for " + targetOption + " Simulations");
      theMapNorm->Draw("COLZ TEXT");
      c2->Print(plotFile1);
    }
  }
  
  /*
  TH1F *DeutOmegaN_GSIM   = new TH1F("DeutOmegaN_GSIM", "", 5, 0.5, 1.);
  TH1F *CarbOmegaN_GSIM   = new TH1F("CarbOmegaN_GSIM", "", 5, 0.5, 1.);
  TH1F *IronOmegaN_GSIM   = new TH1F("IronOmegaN_GSIM", "", 5, 0.5, 1.);
  TH1F *LeadOmegaN_GSIM   = new TH1F("LeadOmegaN_GSIM", "", 5, 0.5, 1.);
  */
  
  return 0;
}

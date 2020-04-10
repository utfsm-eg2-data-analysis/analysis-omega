/**************************************/
/* MakeMR-sn.cxx                      */
/*                                    */
/* Created by Andrés Bórquez, CCTVAL  */
/*                                    */
/**************************************/

// From the MakeRooFits results, we obtain mean, sigma, omega number and bkg number
// -- with the mean and sigma, we obtain a 5sigma NBS MR
// -- with the omega number and bkg number, we obtain the SN for each target

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/MakeMR/sn";
TString fitDir = proDir + "/out/MakeRooFits";

// parameters
Int_t flagZ = 0;
Int_t flagQ2 = 0;
Int_t flagNu = 0;
Int_t flagPt2 = 0;

// for kinvar
TString  kinvarName;
Int_t    kinvarConstant = 1; // default for (Q2, Nu, Pt2)
Int_t    kinvarNbins = 5;    // default for all
TString  kinvarSufix;
Double_t kinvarEdges[6];

TString textFile1;
TString textFile2;

TString plotFile1;
TString plotFile2;
TString plotFile3;
TString plotFile4;

TString targetName[4] = {"D", "C", "Fe", "Pb"};

// [D, C, Fe, Pb][kinvar]
Double_t omegaMean[4][5];
Double_t omegaSigma[4][5];

Double_t omegaNumber_fit[4][5];
Double_t omegaError_fit[4][5];

Double_t omegaNumber_int[4][5];
Double_t omegaError_int[4][5];

Double_t bkgNumber[4][5];
Double_t bkgError[4][5];

Double_t massEdges[4][5][2];

/*** Declaration of functions ***/

inline void parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

void integrateData(TString targetOption);

void testErrorProp1(TH1F *SNX, TH1F *deltaX);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  
  /*** Read fit results ***/

  for (Int_t targIndex = 0; targIndex < 4; targIndex++) {
    for (Int_t index = 0; index < kinvarNbins; index++) {
      
      TString kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
      
      TString fitFile = fitDir + "/roofit-" + targetName[targIndex] + kinvarAuxSufix + ".dat";
      
      std::cout << "Reading " << fitFile << " ..." << std::endl;
      std::ifstream inFile(fitFile);
      
      TString auxString1, auxString2;
      Int_t l = 0; // line counter
      while (inFile >> auxString1 >> auxString2) {
	l++;
	if (l == 1) { // third line
	  omegaMean[targIndex][index] = auxString1.Atof();
	  std::cout << "  Omega Mean for " << targetName[targIndex] << kinvarAuxSufix << ": " << omegaMean[targIndex][index] << std::endl;
	} else if (l == 2) {
	  omegaSigma[targIndex][index] = auxString1.Atof();
	std::cout << "  Omega Sigma for " << targetName[targIndex] << kinvarAuxSufix << ": " << omegaSigma[targIndex][index] << std::endl;
	} else if (l == 3) {
	  omegaNumber_fit[targIndex][index] = auxString1.Atof();
	  omegaError_fit[targIndex][index] = auxString2.Atof();
	  std::cout << "  Omega Number for " << targetName[targIndex] << kinvarAuxSufix << ": " << omegaNumber_fit[targIndex][index] << " +/- " << omegaError_fit[targIndex][index] << std::endl;
	} else if (l == 5) {
	  bkgNumber[targIndex][index] = auxString1.Atof();
	  bkgError[targIndex][index] = auxString2.Atof();
	  std::cout << "  Bkg Number for " << targetName[targIndex] << kinvarAuxSufix << ": " << bkgNumber[targIndex][index] << " +/- " << bkgError[targIndex][index] << std::endl;
	}
      }
      inFile.close();

      // assign mass edges!
      massEdges[targIndex][index][0] = omegaMean[targIndex][index] - 5*omegaSigma[targIndex][index];
      massEdges[targIndex][index][1] = omegaMean[targIndex][index] + 5*omegaSigma[targIndex][index];
      std::cout << "  Mass range for " << targetName[targIndex] << kinvarAuxSufix << ": [" << massEdges[targIndex][index][0] << ", " << massEdges[targIndex][index][1] << "]" << std::endl;
      std::cout << std::endl;
    }
  }
  
  /*** Integrate data ***/
  
  integrateData("D");
  integrateData("C");
  integrateData("Fe");
  integrateData("Pb");

  /*** Manage histograms ***/
  
  // creating and filling histograms
  TH1F *DeutOmegaN_int = new TH1F("DeutOmegaN_int", "", kinvarNbins, 0.5, 1.);
  TH1F *CarbonOmegaN_int = new TH1F("CarbonOmegaN_int", "", kinvarNbins, 0.5, 1.);
  TH1F *IronOmegaN_int = new TH1F("IronOmegaN_int", "", kinvarNbins, 0.5, 1.);
  TH1F *LeadOmegaN_int = new TH1F("LeadOmegaN_int", "", kinvarNbins, 0.5, 1.);
    
  // for each bin in kinvar
  for (Int_t cc = 0; cc < kinvarNbins; cc++) {
    DeutOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[0][cc]);
    DeutOmegaN_int->SetBinError(cc + 1, omegaError_int[0][cc]);
    
    CarbonOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[1][cc]);
    CarbonOmegaN_int->SetBinError(cc + 1, omegaError_int[1][cc]);
    
    IronOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[2][cc]);
    IronOmegaN_int->SetBinError(cc + 1, omegaError_int[2][cc]);
        
    LeadOmegaN_int->SetBinContent(cc + 1, omegaNumber_int[3][cc]);
    LeadOmegaN_int->SetBinError(cc + 1, omegaError_int[3][cc]);
  }
  
  /*** Drawing ***/

  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetGridx(1);
  c->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  TH1F *CarbonMR = new TH1F("CarbonMR", "", kinvarNbins, 0.5, 1.);
  CarbonMR->SetTitle("#omega MR(" + kinvarName + ") - NBS #omega(5#sigma)");
  CarbonMR->GetXaxis()->SetTitle(kinvarName);
  CarbonMR->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
  CarbonMR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[0]));
  CarbonMR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[1]));
  CarbonMR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[2]));
  CarbonMR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[3]));
  CarbonMR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[4]));
  CarbonMR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[5]));
  CarbonMR->GetYaxis()->SetTitle("MR");

  CarbonMR->SetMarkerColor(kRed);
  CarbonMR->SetLineColor(kRed);
  CarbonMR->SetLineWidth(3);
  CarbonMR->SetMarkerStyle(21);
  CarbonMR->Divide(CarbonOmegaN_int, DeutOmegaN_int);
  CarbonMR->Scale(4.6194); // electron normalization
  
  CarbonMR->SetAxisRange(0., 1.2, "Y"); // range
  CarbonMR->Draw("E");  
  
  TH1F *IronMR = new TH1F("IronMR", "", kinvarNbins, 0.5, 1.);
  IronMR->SetMarkerColor(kBlue);
  IronMR->SetLineColor(kBlue);
  IronMR->SetLineWidth(3);
  IronMR->SetMarkerStyle(21);
  IronMR->Divide(IronOmegaN_int, DeutOmegaN_int);
  IronMR->Scale(2.3966); // electron normalization
  
  IronMR->Draw("E SAME");

  TH1F *LeadMR = new TH1F("LeadMR", "", kinvarNbins, 0.5, 1.);
  LeadMR->SetMarkerColor(kBlack);
  LeadMR->SetLineColor(kBlack);
  LeadMR->SetLineWidth(3);
  LeadMR->SetMarkerStyle(21);
  LeadMR->Divide(LeadOmegaN_int, DeutOmegaN_int);
  LeadMR->Scale(6.1780); // electron normalization
  
  LeadMR->Draw("E SAME");
    
  // legend
  TLegend *legend = new TLegend(0.9, 0.75, 1., 0.9);
  legend->AddEntry(CarbonMR, "Carbon", "pl");
  legend->AddEntry(IronMR, "Iron", "pl");
  legend->AddEntry(LeadMR, "Lead", "pl");
  legend->Draw();

  c->Print(plotFile1); // output file

  /*** Save results ***/
  
  std::ofstream outFinalFile(textFile1, std::ios::out); // output file
  // first line
  outFinalFile << CarbonMR->GetBinContent(1) << "\t" << CarbonMR->GetBinError(1) << "\t"
	       << IronMR->GetBinContent(1) << "\t" << IronMR->GetBinError(1) << "\t"
	       << LeadMR->GetBinContent(1) << "\t" << LeadMR->GetBinError(1)  << std::endl;
  // second line
  outFinalFile << CarbonMR->GetBinContent(2) << "\t" << CarbonMR->GetBinError(2) << "\t"
	       << IronMR->GetBinContent(2) << "\t" << IronMR->GetBinError(2) << "\t"
	       << LeadMR->GetBinContent(2) << "\t" << LeadMR->GetBinError(2) << std::endl;
  // third line
  outFinalFile << CarbonMR->GetBinContent(3) << "\t" << CarbonMR->GetBinError(3) << "\t"
	       << IronMR->GetBinContent(3) << "\t" << IronMR->GetBinError(3) << "\t"
	       << LeadMR->GetBinContent(3) << "\t" << LeadMR->GetBinError(3) << std::endl;
  // fourth line
  outFinalFile << CarbonMR->GetBinContent(4) << "\t" << CarbonMR->GetBinError(4) << "\t"
	       << IronMR->GetBinContent(4) << "\t" << IronMR->GetBinError(4) << "\t"
	       << LeadMR->GetBinContent(4) << "\t" << LeadMR->GetBinError(4) << std::endl;
  // fifth line
  outFinalFile << CarbonMR->GetBinContent(5) << "\t" << CarbonMR->GetBinError(5) << "\t"
	       << IronMR->GetBinContent(5) << "\t" << IronMR->GetBinError(5) << "\t"
	       << LeadMR->GetBinContent(5) << "\t" << LeadMR->GetBinError(5) << std::endl;
  
  outFinalFile.close();
  std::cout << "File " << textFile1 << " has been created!" << std::endl;

  /*** SN plots ***/
  
  // creating and filling histograms
  TH1F *DeutOmegaN_fit = new TH1F("DeutOmegaN_fit", "", kinvarNbins, 0.5, 1.);
  TH1F *CarbonOmegaN_fit = new TH1F("CarbonOmegaN_fit", "", kinvarNbins, 0.5, 1.);
  TH1F *IronOmegaN_fit = new TH1F("IronOmegaN_fit", "", kinvarNbins, 0.5, 1.);
  TH1F *LeadOmegaN_fit = new TH1F("LeadOmegaN_fit", "", kinvarNbins, 0.5, 1.);

  TH1F *DeutBkgN = new TH1F("DeutBkgN", "", kinvarNbins, 0.5, 1.);
  TH1F *CarbonBkgN = new TH1F("CarbonBkgN", "", kinvarNbins, 0.5, 1.);
  TH1F *IronBkgN = new TH1F("IronBkgN", "", kinvarNbins, 0.5, 1.);
  TH1F *LeadBkgN = new TH1F("LeadBkgN", "", kinvarNbins, 0.5, 1.);
      
  for (Int_t k = 0; k < kinvarNbins; k++) {

    // omega number from fit
    DeutOmegaN_fit->SetBinContent(k + 1, omegaNumber_fit[0][k]);
    DeutOmegaN_fit->SetBinError(k + 1, omegaError_fit[0][k]);
    CarbonOmegaN_fit->SetBinContent(k + 1, omegaNumber_fit[1][k]);
    CarbonOmegaN_fit->SetBinError(k + 1, omegaError_fit[1][k]);
    IronOmegaN_fit->SetBinContent(k + 1, omegaNumber_fit[2][k]);
    IronOmegaN_fit->SetBinError(k + 1, omegaError_fit[2][k]);
    LeadOmegaN_fit->SetBinContent(k + 1, omegaNumber_fit[3][k]);
    LeadOmegaN_fit->SetBinError(k + 1, omegaError_fit[3][k]);

    // bkg number from fit
    DeutBkgN->SetBinContent(k + 1, bkgNumber[0][k]);
    DeutBkgN->SetBinError(k + 1, bkgError[0][k]);
    CarbonBkgN->SetBinContent(k + 1, bkgNumber[1][k]);
    CarbonBkgN->SetBinError(k + 1, bkgError[1][k]);
    IronBkgN->SetBinContent(k + 1, bkgNumber[2][k]);
    IronBkgN->SetBinError(k + 1, bkgError[2][k]);
    LeadBkgN->SetBinContent(k + 1, bkgNumber[3][k]);
    LeadBkgN->SetBinError(k + 1, bkgError[3][k]);
  }

  // drawing
  TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
  c2->Divide(2,2,0.01,0.01); // nx, ny, margins
  c2->SetGridx(1);
  c2->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  c2->cd(1);
  TH1F *SNDeutHist = new TH1F("SNDeutHist", "", kinvarNbins, 0.5, 1.);
  SNDeutHist->Divide(DeutOmegaN_fit, DeutBkgN);
  SNDeutHist->SetMarkerColor(kGreen+2);
  SNDeutHist->SetLineColor(kGreen+2);
  SNDeutHist->SetLineWidth(3);
  SNDeutHist->SetMarkerStyle(21);
  SNDeutHist->Draw("E");

  c2->cd(2);
  TH1F *SNCarbonHist = new TH1F("SNCarbonHist", "", kinvarNbins, 0.5, 1.);
  SNCarbonHist->Divide(CarbonOmegaN_fit, CarbonBkgN);
  SNCarbonHist->SetMarkerColor(kGreen+2);
  SNCarbonHist->SetLineColor(kGreen+2);
  SNCarbonHist->SetLineWidth(3);
  SNCarbonHist->SetMarkerStyle(21);
  SNCarbonHist->Draw("E");

  c2->cd(3);
  TH1F *SNIronHist = new TH1F("SNIronHist", "", kinvarNbins, 0.5, 1.);
  SNIronHist->Divide(IronOmegaN_fit, IronBkgN);
  SNIronHist->SetMarkerColor(kGreen+2);
  SNIronHist->SetLineColor(kGreen+2);
  SNIronHist->SetLineWidth(3);
  SNIronHist->SetMarkerStyle(21);
  SNIronHist->Draw("E");

  c2->cd(4);
  TH1F *SNLeadHist = new TH1F("SNLeadHist", "", kinvarNbins, 0.5, 1.);
  SNLeadHist->Divide(LeadOmegaN_fit, LeadBkgN);
  SNLeadHist->SetMarkerColor(kGreen+2);
  SNLeadHist->SetLineColor(kGreen+2);
  SNLeadHist->SetLineWidth(3);
  SNLeadHist->SetMarkerStyle(21);
  SNLeadHist->Draw("E");

  c2->Print(plotFile2);

  /*** Obtaining correction factors ***/
  
  TH1F *unitaryHist = new TH1F("unitaryHist", "", kinvarNbins, 0.5, 1.);
  for (Int_t u = 1; u <= kinvarNbins; u++) {
    unitaryHist->SetBinContent(u, 1.);
    unitaryHist->SetBinError(u, 0.);
  }

  TH1F *deltaDeut = new TH1F("deltaDeut", "", kinvarNbins, 0.5, 1.);
  deltaDeut->Add(SNDeutHist, unitaryHist);
  deltaDeut->Divide(SNDeutHist);

  TH1F *deltaCarbon = new TH1F("deltaCarbon", "", kinvarNbins, 0.5, 1.);
  deltaCarbon->Add(SNCarbonHist, unitaryHist);
  deltaCarbon->Divide(SNCarbonHist);
  
  TH1F *deltaIron = new TH1F("deltaIron", "", kinvarNbins, 0.5, 1.);
  deltaIron->Add(SNIronHist, unitaryHist);
  deltaIron->Divide(SNIronHist);
  
  TH1F *deltaLead = new TH1F("deltaLead", "", kinvarNbins, 0.5, 1.);
  deltaLead->Add(SNLeadHist, unitaryHist);
  deltaLead->Divide(SNLeadHist);

  // debug
  testErrorProp1(SNDeutHist, deltaDeut);
  std::cout << std::endl;
  
  // drawing
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
  c3->SetGridx(1);
  c3->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  // the DR: delta ratio
  TH1F *CarbonDR = new TH1F("CarbonDR", "", kinvarNbins, 0.5, 1.);
  CarbonDR->Divide(deltaDeut, deltaCarbon);

  CarbonDR->SetTitle("#omega DR(" + kinvarName + ")");
  CarbonDR->GetXaxis()->SetTitle(kinvarName);
  CarbonDR->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
  CarbonDR->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[0]));
  CarbonDR->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[1]));
  CarbonDR->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[2]));
  CarbonDR->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[3]));
  CarbonDR->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[4]));
  CarbonDR->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[5]));
  CarbonDR->GetYaxis()->SetTitle("DR");
  CarbonDR->SetAxisRange(0., 3., "Y"); // range

  CarbonDR->SetMarkerColor(kRed);
  CarbonDR->SetLineColor(kRed);
  CarbonDR->SetLineWidth(3);
  CarbonDR->SetMarkerStyle(21);
  
  CarbonDR->Draw("E");  
  
  TH1F *IronDR = new TH1F("IronDR", "", kinvarNbins, 0.5, 1.);
  IronDR->Divide(deltaDeut, deltaIron);

  IronDR->SetMarkerColor(kBlue);
  IronDR->SetLineColor(kBlue);
  IronDR->SetLineWidth(3);
  IronDR->SetMarkerStyle(21);
  
  IronDR->Draw("E SAME");

  TH1F *LeadDR = new TH1F("LeadDR", "", kinvarNbins, 0.5, 1.);
  LeadDR->Divide(deltaDeut, deltaLead);

  LeadDR->SetMarkerColor(kBlack);
  LeadDR->SetLineColor(kBlack);
  LeadDR->SetLineWidth(3);
  LeadDR->SetMarkerStyle(21);
  
  LeadDR->Draw("E SAME");
    
  // legend
  TLegend *legend3 = new TLegend(0.9, 0.75, 1., 0.9);
  legend3->AddEntry(CarbonDR, "Carbon", "pl");
  legend3->AddEntry(IronDR, "Iron", "pl");
  legend3->AddEntry(LeadDR, "Lead", "pl");
  legend3->Draw();

  c3->Print(plotFile3); // output file

  /*** Final stage ***/

  TCanvas *c4 = new TCanvas("c4", "c4", 1000, 1000);
  c4->SetGridx(1);
  c4->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  
  TH1F *CarbonMR_sn = new TH1F("CarbonMR_sn", "", kinvarNbins, 0.5, 1.);
  CarbonMR_sn->Multiply(CarbonMR, CarbonDR);

  CarbonMR_sn->SetTitle("#omega MR(" + kinvarName + ") using SN as Correction Factor");
  CarbonMR_sn->GetXaxis()->SetTitle(kinvarName);
  CarbonMR_sn->GetXaxis()->SetNdivisions(200 + kinvarNbins, kFALSE);
  CarbonMR_sn->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[0]));
  CarbonMR_sn->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[1]));
  CarbonMR_sn->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[2]));
  CarbonMR_sn->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[3]));
  CarbonMR_sn->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[4]));
  CarbonMR_sn->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1, Form("%.02f", kinvarEdges[5]));
  CarbonMR_sn->GetYaxis()->SetTitle("MR");
  CarbonMR_sn->SetAxisRange(0., 1.2, "Y"); // range

  CarbonMR_sn->SetMarkerColor(kRed);
  CarbonMR_sn->SetLineColor(kRed);
  CarbonMR_sn->SetLineWidth(3);
  CarbonMR_sn->SetMarkerStyle(21);
  
  CarbonMR_sn->Draw("E");  
  
  TH1F *IronMR_sn = new TH1F("IronMR_sn", "", kinvarNbins, 0.5, 1.);
  IronMR_sn->Multiply(IronMR, IronDR);

  IronMR_sn->SetMarkerColor(kBlue);
  IronMR_sn->SetLineColor(kBlue);
  IronMR_sn->SetLineWidth(3);
  IronMR_sn->SetMarkerStyle(21);
  
  IronMR_sn->Draw("E SAME");

  TH1F *LeadMR_sn = new TH1F("LeadMR_sn", "", kinvarNbins, 0.5, 1.);
  LeadMR_sn->Multiply(LeadMR, LeadDR);

  LeadMR_sn->SetMarkerColor(kBlack);
  LeadMR_sn->SetLineColor(kBlack);
  LeadMR_sn->SetLineWidth(3);
  LeadMR_sn->SetMarkerStyle(21);
  
  LeadMR_sn->Draw("E SAME");
    
  // legend
  TLegend *legend4 = new TLegend(0.9, 0.75, 1., 0.9);
  legend4->AddEntry(CarbonMR_sn, "Carbon", "pl");
  legend4->AddEntry(IronMR_sn, "Iron", "pl");
  legend4->AddEntry(LeadMR_sn, "Lead", "pl");
  legend4->Draw();

  c4->Print(plotFile4); // output file

  /*** Save results ***/
  
  std::ofstream outFile_SN(textFile2, std::ios::out); // output file
  // first line
  outFile_SN << CarbonMR_sn->GetBinContent(1) << "\t" << CarbonMR_sn->GetBinError(1) << "\t"
	     << IronMR_sn->GetBinContent(1) << "\t" << IronMR_sn->GetBinError(1) << "\t"
	     << LeadMR_sn->GetBinContent(1) << "\t" << LeadMR_sn->GetBinError(1)  << std::endl;
  // second line
  outFile_SN << CarbonMR_sn->GetBinContent(2) << "\t" << CarbonMR_sn->GetBinError(2) << "\t"
	     << IronMR_sn->GetBinContent(2) << "\t" << IronMR_sn->GetBinError(2) << "\t"
	     << LeadMR_sn->GetBinContent(2) << "\t" << LeadMR_sn->GetBinError(2) << std::endl;
  // third line
  outFile_SN << CarbonMR_sn->GetBinContent(3) << "\t" << CarbonMR_sn->GetBinError(3) << "\t"
	     << IronMR_sn->GetBinContent(3) << "\t" << IronMR_sn->GetBinError(3) << "\t"
	     << LeadMR_sn->GetBinContent(3) << "\t" << LeadMR_sn->GetBinError(3) << std::endl;
  // fourth line
  outFile_SN << CarbonMR_sn->GetBinContent(4) << "\t" << CarbonMR_sn->GetBinError(4) << "\t"
	     << IronMR_sn->GetBinContent(4) << "\t" << IronMR_sn->GetBinError(4) << "\t"
	     << LeadMR_sn->GetBinContent(4) << "\t" << LeadMR_sn->GetBinError(4) << std::endl;
  // fifth line
  outFile_SN << CarbonMR_sn->GetBinContent(5) << "\t" << CarbonMR_sn->GetBinError(5) << "\t"
	     << IronMR_sn->GetBinContent(5) << "\t" << IronMR_sn->GetBinError(5) << "\t"
	     << LeadMR_sn->GetBinContent(5) << "\t" << LeadMR_sn->GetBinError(5) << std::endl;
  
  outFile_SN.close();
  std::cout << "File " << textFile2 << " has been created!" << std::endl;

  return 0;
}

/*** Functions ***/

inline void parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR-sn -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hzqnp")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'z': flagZ = 1; break;
    case 'q': flagQ2 = 1; break;
    case 'n': flagNu = 1; break;
    case 'p': flagPt2 = 1; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR-sn -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR-sn program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-sn -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakeMR-sn -[kinvar]" << std::endl;
  std::cout << "    (exclusive and mandatory)" << std::endl;
  std::cout << "    z : Z" << std::endl;
  std::cout << "    q : Q2" << std::endl;
  std::cout << "    n : Nu" << std::endl;
  std::cout << "    p : Pt2" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kinvar
  if (flagZ) {
    kinvarName = "Z";
    kinvarConstant = 3;
    kinvarSufix = "-z";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesZ[i];
  } else if (flagQ2) {
    kinvarName = "Q2";
    kinvarSufix = "-q";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesQ2[i];
  } else if (flagNu) {
    kinvarName = "Nu";
    kinvarSufix = "-n";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesNu[i];
  } else if (flagPt2) {
    kinvarName = "Pt2";
    kinvarSufix = "-p";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesPt2[i];
  }
  // input files
  fitDir = fitDir + "/" + kinvarName;
  // for output files
  plotFile1 = outDir + "/nbs-MR-" + kinvarName + ".png";
  textFile1 = outDir + "/nbs-MR-" + kinvarName + ".dat";
  plotFile2 = outDir + "/sn-" + kinvarName + ".png";
  plotFile3 = outDir + "/DR-" + kinvarName + ".png";
  plotFile4 = outDir + "/sn-MR-" + kinvarName + ".png";
  textFile2 = outDir + "/sn-MR-" + kinvarName + ".dat";
}

void integrateData(TString targetOption) {

  TString inputFile1, inputFile2, inputFile3;
  Int_t   targIndex;
  
  TCut cutTargType;
  TCut cutAll = cutPi0 && cutDIS && cutPipPim;
  
  // for targets, unified D
  if (targetOption == "D") {
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
    cutTargType = "TargType == 1";
    targIndex = 0;
    std::cout << "Reading " << inputFile1 << std::endl;
    std::cout << "        " << inputFile2 << std::endl;
    std::cout << "        " << inputFile3 << " ..." << std::endl;
  } else if (targetOption == "C") {
    inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
    targIndex = 1;
    std::cout << "Reading " << inputFile1 << " ..." << std::endl;
  } else if (targetOption == "Fe") {
    inputFile1 = dataDir + "/Fe/comb_Fe-thickD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
    targIndex = 2;
    std::cout << "Reading " << inputFile1 << " ..." << std::endl;
  } else if (targetOption == "Pb") {
    inputFile1 = dataDir + "/Pb/comb_Pb-thinD2.root";
    inputFile2 = "";
    inputFile3 = "";
    cutTargType = "TargType == 2";
    targIndex = 3;
    std::cout << "Reading " << inputFile1 << " ..." << std::endl;
  }

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  for (Int_t index = 0; index < kinvarNbins; index++) {

    TString kinvarAuxSufix = kinvarSufix + Form("%d", index + kinvarConstant);
    
    TCut kinvarCut;
    kinvarCut = Form("%f < ", kinvarEdges[index]) + kinvarName + " && " + kinvarName + Form(" < %f", kinvarEdges[index+1]);
    TCut cutMass = Form("%f < wD && wD < %f", massEdges[targIndex][index][0], massEdges[targIndex][index][1]);
    
    TH1F *dataHist;
    treeExtracted->Draw("wD>>data(60, 0.2, 0.5)", cutAll && cutTargType && kinvarCut && cutMass, "goff");
    dataHist = (TH1F *)gROOT->FindObject("data");
    
    // save numbers!
    omegaNumber_int[targIndex][index] = dataHist->IntegralAndError(1, 60, omegaError_int[targIndex][index], "");
    std::cout << "  Omega Number for " << targetOption << kinvarAuxSufix << ": " << omegaNumber_int[targIndex][index] << " +/- " << omegaError_int[targIndex][index] << std::endl;
    
    delete dataHist;
  }
  std::cout << std::endl;
}

void testErrorProp1(TH1F *SNX, TH1F *deltaX) {
  Double_t sn_val, sn_err;
  Double_t del_val, del_err;
  Double_t cal_err;
  
  for (Int_t t = 1; t <= 5; t++) {
    
    sn_val=SNX->GetBinContent(t);
    sn_err=SNX->GetBinError(t);
    
    del_val=deltaX->GetBinContent(t);
    
    cal_err=del_val*TMath::Sqrt(TMath::Power((sn_err/(sn_val+1)), 2) + TMath::Power((sn_err/sn_val), 2));
    
    std::cout << "cal_err=" << cal_err << std::endl;
    
    del_err = deltaX->GetBinError(t);
    std::cout << "del_err=" << del_err<< std::endl;
    std::cout << "del_val=" << del_val<< std::endl;
    std::cout << std::endl;
  }
}

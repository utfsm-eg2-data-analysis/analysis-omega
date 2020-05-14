/**************************************/
/* SysPi0Compare.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

/*** TASK 4 for Analysis Note ***/

// This program corresponds to systematics studies on Pi0 mass
// stage 1: plots both MR_a(Z) and MR_b(Z) of preference
//          it can be any Nsigma combination around omega or pi0 peaks
// stage 2: plots mentioned MR difference in percentage

#include "analysisConfig.h"

/*** Global variables ***/

TString inputDir = proDir + "/out/SystPi0";
TString outDir = inputDir;

Double_t MR_a[3][5];
Double_t MR_aE[3][5];

Double_t MR_b[3][5];
Double_t MR_bE[3][5];

/*** Parameters ***/

TString MROption_a;
TString MROption_b;
TString inputFileName_a;
TString inputFileName_b;
TString outSufix;
TString histTitle_a;
TString histTitle_b;
TString histTitleFull;

Bool_t legendFlag = kFALSE; // default
TString legendName_a[3];
TString legendName_b[3];
TString legendSufix = "";

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printUsage();

void readTextFiles();
void printResults(TH1F *CarbonDiff2, TH1F *IronDiff2, TH1F *LeadDiff2);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  
  readTextFiles();

  /*** Creating and filling histograms ***/

  TH1F *CarbonMR_a = new TH1F("CarbonMR_a", "", 5, 0.5, 1.);
  TH1F *IronMR_a = new TH1F("IronMR_a", "", 5, 0.5, 1.);
  TH1F *LeadMR_a = new TH1F("LeadMR_a", "", 5, 0.5, 1.);
  
  TH1F *CarbonMR_b = new TH1F("CarbonMR_b", "", 5, 0.5, 1.);
  TH1F *IronMR_b = new TH1F("IronMR_b", "", 5, 0.5, 1.);
  TH1F *LeadMR_b = new TH1F("LeadMR_b", "", 5, 0.5, 1.);
  
  for (Int_t i = 0; i < 5; i++) {
    // a
    CarbonMR_a->SetBinContent(i+1, MR_a[0][i]);
    CarbonMR_a->SetBinError(i+1, MR_aE[0][i]);
    IronMR_a->SetBinContent(i+1, MR_a[1][i]);
    IronMR_a->SetBinError(i+1, MR_aE[1][i]);
    LeadMR_a->SetBinContent(i+1, MR_a[2][i]);
    LeadMR_a->SetBinError(i+1, MR_aE[2][i]);
    
    // b
    CarbonMR_b->SetBinContent(i+1, MR_b[0][i]);
    CarbonMR_b->SetBinError(i+1, MR_bE[0][i]);
    IronMR_b->SetBinContent(i+1, MR_b[1][i]);
    IronMR_b->SetBinError(i+1, MR_bE[1][i]);
    LeadMR_b->SetBinContent(i+1, MR_b[2][i]);
    LeadMR_b->SetBinError(i+1, MR_bE[2][i]);
  }
  
  /*** Drawing ***/
   
  std::cout << "Drawing..." << std::endl;
  TCanvas *ca = new TCanvas("ca", "ca", 1000, 1000);
  ca->SetGridx(0);
  ca->SetGridy(1);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0.5);

  CarbonMR_a->SetTitle("Comp. " + histTitleFull);
  CarbonMR_a->GetXaxis()->SetTitle("Z");
  CarbonMR_a->GetXaxis()->SetNdivisions(208, kTRUE);
  CarbonMR_a->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0.5");
  CarbonMR_a->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0.557");
  CarbonMR_a->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"0.617");
  CarbonMR_a->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"0.689");
  CarbonMR_a->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"0.784");
  CarbonMR_a->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1.0");
  CarbonMR_a->GetYaxis()->SetTitle("#omega MR(Z)");

  // "special" colors for a
  CarbonMR_a->SetMarkerColor(kOrange+10);
  CarbonMR_a->SetLineColor(kOrange+10);
  CarbonMR_a->SetLineWidth(3);
  CarbonMR_a->SetMarkerStyle(21);
  CarbonMR_a->SetMarkerSize(2);

  IronMR_a->SetMarkerColor(kCyan+1);
  IronMR_a->SetLineColor(kCyan+1);
  IronMR_a->SetLineWidth(3);
  IronMR_a->SetMarkerStyle(21);
  IronMR_a->SetMarkerSize(2);

  LeadMR_a->SetMarkerColor(kGreen+3);
  LeadMR_a->SetLineColor(kGreen+3);
  LeadMR_a->SetLineWidth(3);
  LeadMR_a->SetMarkerStyle(21);
  LeadMR_a->SetMarkerSize(2);
  
  // regular colors for b
  CarbonMR_b->SetMarkerColor(kRed);
  CarbonMR_b->SetLineColor(kRed);
  CarbonMR_b->SetLineWidth(3);
  CarbonMR_b->SetMarkerStyle(24);
  CarbonMR_b->SetMarkerSize(2);
  
  IronMR_b->SetMarkerColor(kBlue);
  IronMR_b->SetLineColor(kBlue);
  IronMR_b->SetLineWidth(3);
  IronMR_b->SetMarkerStyle(24);
  IronMR_b->SetMarkerSize(2);
  
  LeadMR_b->SetMarkerColor(kBlack);
  LeadMR_b->SetLineColor(kBlack);
  LeadMR_b->SetLineWidth(3);
  LeadMR_b->SetMarkerStyle(24);
  LeadMR_b->SetMarkerSize(2);
  
  // draw already!
  Double_t maxMR = 1.2;
  Double_t minMR = 0.0;
  CarbonMR_a->SetAxisRange(minMR, maxMR, "Y"); // range

  CarbonMR_a->Draw("E1");
  IronMR_a->Draw("E1 SAME");
  LeadMR_a->Draw("E1 SAME");
  
  CarbonMR_b->Draw("E1 SAME");
  IronMR_b->Draw("E1 SAME");
  LeadMR_b->Draw("E1 SAME");
    
  // legend

  if (legendFlag) {
    TLegend *legend = new TLegend(0.7, 0.4, 1., 0.9);
    legend->AddEntry(CarbonMR_a, legendName_a[0], "pl");
    legend->AddEntry(IronMR_a, legendName_a[1], "pl");
    legend->AddEntry(LeadMR_a, legendName_a[2], "pl");
    legend->AddEntry(CarbonMR_b, legendName_b[0], "pl");
    legend->AddEntry(IronMR_b, legendName_b[1], "pl");
    legend->AddEntry(LeadMR_b, legendName_b[2], "pl");
    legend->Draw();
  }
  
  ca->Print(outDir + "/comp-MR-" + outSufix + legendSufix + ".png"); // output file

  /*** STAGE 2: Plot difference ***/
  
  TH1F *CarbonMRdiff = new TH1F("CarbonMRdiff", "", 5, 0.5, 1.);

  CarbonMRdiff->SetTitle("Diff. " + histTitleFull + " in (%)");
  CarbonMRdiff->GetXaxis()->SetTitle("Z");
  CarbonMRdiff->GetXaxis()->SetNdivisions(208, kTRUE);
  CarbonMRdiff->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"0.5");
  CarbonMRdiff->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"0.557");
  CarbonMRdiff->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"0.617");
  CarbonMRdiff->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"0.689");
  CarbonMRdiff->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"0.784");
  CarbonMRdiff->GetXaxis()->ChangeLabel(-1,-1,-1,-1,-1,-1,"1.0");
  CarbonMRdiff->GetYaxis()->SetTitle("Difference (%)");
  
  CarbonMRdiff->Add(CarbonMR_a, CarbonMR_b, 1, -1);
  CarbonMRdiff->Divide(CarbonMR_a);
  CarbonMRdiff->Scale(100);
  
  CarbonMRdiff->SetMarkerColor(kRed);
  CarbonMRdiff->SetMarkerStyle(22);
  CarbonMRdiff->SetMarkerSize(3);

  TH1F *IronMRdiff = new TH1F("IronMRdiff", "", 5, 0.5, 1.);
  IronMRdiff->Add(IronMR_a, IronMR_b, 1, -1);
  IronMRdiff->Divide(IronMR_a);
  IronMRdiff->Scale(100);
  
  IronMRdiff->SetMarkerColor(kBlue);
  IronMRdiff->SetMarkerStyle(22);
  IronMRdiff->SetMarkerSize(3);
  
  TH1F *LeadMRdiff = new TH1F("LeadMRdiff", "", 5, 0.5, 1.);
  LeadMRdiff->Add(LeadMR_a, LeadMR_b, 1, -1);
  LeadMRdiff->Divide(LeadMR_a);
  LeadMRdiff->Scale(100);
  
  LeadMRdiff->SetMarkerColor(kBlack);
  LeadMRdiff->SetMarkerStyle(22);
  LeadMRdiff->SetMarkerSize(3);
  
  TCanvas *cb = new TCanvas("cb", "cb", 1366, 1000);
  cb->SetGridx(1);
  cb->SetGridy(1);
  gStyle->SetOptStat(0);

  CarbonMRdiff->SetAxisRange(-5, 5, "Y"); // range
  CarbonMRdiff->Draw("HIST P");
  IronMRdiff->Draw("HIST P SAME");
  LeadMRdiff->Draw("HIST P SAME");

  drawHorizontalLine(0);

  TLegend *l2 = new TLegend(0.15, 0.15, 0.3, 0.3);
  l2->AddEntry(CarbonMRdiff, "Carbon", "p");
  l2->AddEntry(IronMRdiff, "Iron", "p");
  l2->AddEntry(LeadMRdiff, "Lead", "p");
  l2->Draw();
  
  cb->Print(outDir + "/diff-MR-" + outSufix + ".png"); // output file

  printResults(CarbonMRdiff, IronMRdiff, LeadMRdiff);
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SystPi0Compare -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hA:B:l")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'A': MROption_a = optarg; break;
    case 'B': MROption_b = optarg; break;
    case 'l': legendFlag = kTRUE; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./SystPi0Compare -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "SystPi0Compare program. Usage is:" << std::endl;
  std::cout << "./SystPi0Compare -[options] -[more options]" << std::endl;
  std::cout << "  h         : prints help and exit program" << std::endl;
  std::cout << "  A[NwMi]   : selects MR" << std::endl;
  std::cout << "  B[NwMi]   : selects MR" << std::endl;
  std::cout << "  where N stands for the number of sigma around omega peak" << std::endl;
  std::cout << "  where M stands for the number of sigma around pi0 peak" << std::endl;
  std::cout << "  l         : prints legend" << std::endl;
}

void assignOptions() {
  // for a
  if (MROption_a == "3w3i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-3w-3pi0.dat";
    histTitle_a = "{#omega (3#sigma) & #pi^{0} (3#sigma)}";
  } else if (MROption_a == "3w4i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-3w-4pi0.dat";
    histTitle_a = "{#omega (3#sigma) & #pi^{0} (4#sigma)}";
  } else if (MROption_a == "3w5i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-3w-5pi0.dat";
    histTitle_a = "{#omega (3#sigma) & #pi^{0} (5#sigma)}";
  } else if (MROption_a == "4w3i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-4w-3pi0.dat";
    histTitle_a = "{#omega (4#sigma) & #pi^{0} (3#sigma)}";
  } else if (MROption_a == "4w4i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-4w-4pi0.dat";
    histTitle_a = "{#omega (4#sigma) & #pi^{0} (4#sigma)}";
  } else if (MROption_a == "4w5i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-4w-5pi0.dat";
    histTitle_a = "{#omega (4#sigma) & #pi^{0} (5#sigma)}";
  } else if (MROption_a == "5w3i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-5w-3pi0.dat";
    histTitle_a = "{#omega (5#sigma) & #pi^{0} (3#sigma)}";
  } else if (MROption_a == "5w4i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-5w-4pi0.dat";
    histTitle_a = "{#omega (5#sigma) & #pi^{0} (4#sigma)}";
  } else if (MROption_a == "5w5i") {
    inputFileName_a = inputDir + "/nbs-MR-Z-5w-5pi0.dat";
    histTitle_a = "{#omega (5#sigma) & #pi^{0} (5#sigma)}";
  }
  // for b
  if (MROption_b == "3w3i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-3w-3pi0.dat";
    histTitle_b = "{#omega (3#sigma) & #pi^{0} (3#sigma)}";
  } else if (MROption_b == "3w4i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-3w-4pi0.dat";
    histTitle_b = "{#omega (3#sigma) & #pi^{0} (4#sigma)}";
  } else if (MROption_b == "3w5i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-3w-5pi0.dat";
    histTitle_b = "{#omega (3#sigma) & #pi^{0} (5#sigma)}";
  } else if (MROption_b == "4w3i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-4w-3pi0.dat";
    histTitle_b = "{#omega (4#sigma) & #pi^{0} (3#sigma)}";
  } else if (MROption_b == "4w4i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-4w-4pi0.dat";
    histTitle_b = "{#omega (4#sigma) & #pi^{0} (4#sigma)}";
  } else if (MROption_b == "4w5i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-4w-5pi0.dat";
    histTitle_b = "{#omega (4#sigma) & #pi^{0} (5#sigma)}";
  } else if (MROption_b == "5w3i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-5w-3pi0.dat";
    histTitle_b = "{#omega (5#sigma) & #pi^{0} (3#sigma)}";
  } else if (MROption_b == "5w4i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-5w-4pi0.dat";
    histTitle_b = "{#omega (5#sigma) & #pi^{0} (4#sigma)}";
  } else if (MROption_b == "5w5i") {
    inputFileName_b = inputDir + "/nbs-MR-Z-5w-5pi0.dat";
    histTitle_b = "{#omega (5#sigma) & #pi^{0} (5#sigma)}";
  }
  // file sufix
  outSufix = MROption_a + "_vs_" + MROption_b;
  histTitleFull = histTitle_a + " vs " + histTitle_b;
  // legends
  legendName_a[0] = "C - " + histTitle_a;
  legendName_a[1] = "Fe - " + histTitle_a;
  legendName_a[2] = "Pb - " + histTitle_a;
  legendName_b[0] = "C - " + histTitle_b;
  legendName_b[1] = "Fe - " + histTitle_b;
  legendName_b[2] = "Pb - " + histTitle_b;
  if (legendFlag) legendSufix = ".legend";
}

void readTextFiles() {

  // fill MR_a
  std::cout << "Reading " << inputFileName_a << "..." << std::endl;
  std::ifstream inFile_a(inputFileName_a);

  TString auxString1, auxString2, auxString3, auxString4, auxString5, auxString6;
  Int_t l = 0; // line counter
  while (inFile_a >> auxString1 >> auxString2 >> auxString3 >> auxString4 >> auxString5 >> auxString6) {
    MR_a[0][l] = auxString1.Atof();
    MR_aE[0][l] = auxString2.Atof();
    MR_a[1][l] = auxString3.Atof();
    MR_aE[1][l] = auxString4.Atof();
    MR_a[2][l] = auxString5.Atof();
    MR_aE[2][l] = auxString6.Atof();
    std::cout << auxString1 << " " << auxString2 << " " << auxString3 << " " << auxString4 << " " << auxString5 << " " << auxString6 << std::endl;
    l++;
  }
  inFile_a.close();

  // fill MR_b
  std::cout << "Reading " << inputFileName_b << "..." << std::endl;  
  std::ifstream inFile_b(inputFileName_b);
  
  l = 0; // reset line counter
  while (inFile_b >> auxString1 >> auxString2 >> auxString3 >> auxString4 >> auxString5 >> auxString6) {
    MR_b[0][l] = auxString1.Atof();
    MR_bE[0][l] = auxString2.Atof();
    MR_b[1][l] = auxString3.Atof();
    MR_bE[1][l] = auxString4.Atof();
    MR_b[2][l] = auxString5.Atof();
    MR_bE[2][l] = auxString6.Atof();
    std::cout << auxString1 << " " << auxString2 << " " << auxString3 << " " << auxString4 << " " << auxString5 << " " << auxString6 << std::endl;
    l++;
  }
  inFile_b.close();
  
}

void printResults(TH1F *CarbonDiff2, TH1F *IronDiff2, TH1F *LeadDiff2) {
  // Carbon
  Double_t sum_C = 0;
  Double_t avg_C;
  for (Int_t zp = 0; zp < 5; zp++) {
    std::cout << "Diff obtained for C in bin z" << (zp+3) << ": "  << CarbonDiff2->GetBinContent(zp + 1) << std::endl;
    sum_C += TMath::Abs(CarbonDiff2->GetBinContent(zp + 1));
  }
  avg_C = sum_C/5.;
  std::cout << "Mean difference for C: "  << avg_C << std::endl;

  // Iron
  Double_t sum_Fe = 0;
  Double_t avg_Fe;
  for (Int_t zpp = 0; zpp < 5; zpp++) {
    std::cout << "Diff obtained for Fe in bin z" << (zpp+3) << ": "  << IronDiff2->GetBinContent(zpp + 1) << std::endl;
    sum_Fe += TMath::Abs(IronDiff2->GetBinContent(zpp + 1));
  }
  avg_Fe = sum_Fe/5.;
  std::cout << "Mean difference for Fe: "  << avg_Fe << std::endl;

  // Lead
  Double_t sum_Pb = 0;
  Double_t avg_Pb;
  for (Int_t zppp = 0; zppp < 5; zppp++) {
    std::cout << "Diff obtained for Pb in bin z" << (zppp+3) << ": "  << LeadDiff2->GetBinContent(zppp + 1) << std::endl;
    sum_Pb += TMath::Abs(LeadDiff2->GetBinContent(zppp + 1));
  }
  avg_Pb = sum_Pb/5.;
  std::cout << "Mean difference for Pb: "  << avg_Pb << std::endl;
}

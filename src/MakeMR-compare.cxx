/**************************************/
/* MakeMR-compare.cxx                 */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// stage 1: plots both MR_a(Z) and MR_b(Z) of preference
// stage 2: plots mentioned MR difference in percentage
// UPDATE:
// added kinvar option
// updated style

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/MakeMR";
TString plotFile1;
TString plotFile2;

Double_t MR_a[3][5];
Double_t MR_aE[3][5];

Double_t MR_b[3][5];
Double_t MR_bE[3][5];

/*** Parameters ***/

TString kinvarOption;
Int_t kinvarNbins = 5;
TString kinvarTitle;
Double_t kinvarEdges[6];

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

  // define arrays
  Double_t MR_x[kinvarNbins];
  Double_t MR_xerr[kinvarNbins]; // new!
  
  // define arrays for A
  Double_t CarbonMR_a_y[kinvarNbins];
  Double_t CarbonMR_a_err[kinvarNbins];
  Double_t IronMR_a_y[kinvarNbins];
  Double_t IronMR_a_err[kinvarNbins];
  Double_t LeadMR_a_y[kinvarNbins];
  Double_t LeadMR_a_err[kinvarNbins];
  
  // fill arrays
  for (Int_t v = 0; v < kinvarNbins; v++) {
    MR_x[v] = (kinvarEdges[v] + kinvarEdges[v+1])/2.;
    MR_xerr[v] = (kinvarEdges[v+1] - kinvarEdges[v])/TMath::Sqrt(12); // new
    CarbonMR_a_y[v] = CarbonMR_a->GetBinContent(v+1);
    CarbonMR_a_err[v] = CarbonMR_a->GetBinError(v+1);
    IronMR_a_y[v] = IronMR_a->GetBinContent(v+1);
    IronMR_a_err[v] = IronMR_a->GetBinError(v+1);
    LeadMR_a_y[v] = LeadMR_a->GetBinContent(v+1);
    LeadMR_a_err[v] = LeadMR_a->GetBinError(v+1);
  }

  // define arrays for B
  Double_t CarbonMR_b_y[kinvarNbins];
  Double_t CarbonMR_b_err[kinvarNbins];
  Double_t IronMR_b_y[kinvarNbins];
  Double_t IronMR_b_err[kinvarNbins];
  Double_t LeadMR_b_y[kinvarNbins];
  Double_t LeadMR_b_err[kinvarNbins];
  
  // fill arrays
  for (Int_t v = 0; v < kinvarNbins; v++) {
    CarbonMR_b_y[v] = CarbonMR_b->GetBinContent(v+1);
    CarbonMR_b_err[v] = CarbonMR_b->GetBinError(v+1);
    IronMR_b_y[v] = IronMR_b->GetBinContent(v+1);
    IronMR_b_err[v] = IronMR_b->GetBinError(v+1);
    LeadMR_b_y[v] = LeadMR_b->GetBinContent(v+1);
    LeadMR_b_err[v] = LeadMR_b->GetBinError(v+1);
  }
   
  std::cout << "Drawing..." << std::endl;

  // define canvas
  TCanvas *ca = new TCanvas("ca", "ca", 1000, 1000);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);

  // define graphs for a
  TGraphErrors *CarbonMR_a_gr = new TGraphErrors(kinvarNbins, MR_x, CarbonMR_a_y, MR_xerr, CarbonMR_a_err);
  TGraphErrors *IronMR_a_gr = new TGraphErrors(kinvarNbins, MR_x, IronMR_a_y, MR_xerr, IronMR_a_err);
  TGraphErrors *LeadMR_a_gr = new TGraphErrors(kinvarNbins, MR_x, LeadMR_a_y, MR_xerr, LeadMR_a_err);
  // define graphs for b  
  TGraphErrors *CarbonMR_b_gr = new TGraphErrors(kinvarNbins, MR_x, CarbonMR_b_y, MR_xerr, CarbonMR_b_err);
  TGraphErrors *IronMR_b_gr = new TGraphErrors(kinvarNbins, MR_x, IronMR_b_y, MR_xerr, IronMR_b_err);
  TGraphErrors *LeadMR_b_gr = new TGraphErrors(kinvarNbins, MR_x, LeadMR_b_y, MR_xerr, LeadMR_b_err);
  
  // let's draw a!
  CarbonMR_a_gr->SetTitle("Multiplicity Ratio: #omega");
  CarbonMR_a_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbonMR_a_gr->GetXaxis()->CenterTitle();
  CarbonMR_a_gr->GetXaxis()->SetNdivisions(400 + kinvarNbins, kFALSE);
  CarbonMR_a_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[kinvarNbins]);
  CarbonMR_a_gr->GetYaxis()->SetTitle("R_{#omega}");
  CarbonMR_a_gr->GetYaxis()->CenterTitle();
  CarbonMR_a_gr->GetYaxis()->SetRangeUser(0., 1.4); // updated

  CarbonMR_a_gr->SetMarkerStyle(21);
  CarbonMR_a_gr->SetMarkerSize(1.5);
  CarbonMR_a_gr->SetMarkerColor(kRed);
  CarbonMR_a_gr->SetLineColor(kRed);
  CarbonMR_a_gr->SetLineWidth(3);
  
  CarbonMR_a_gr->Draw("AP");
  
  IronMR_a_gr->SetMarkerStyle(21);
  IronMR_a_gr->SetMarkerSize(1.5);
  IronMR_a_gr->SetMarkerColor(kBlue);
  IronMR_a_gr->SetLineColor(kBlue);
  IronMR_a_gr->SetLineWidth(3);
  
  IronMR_a_gr->Draw("P");

  LeadMR_a_gr->SetMarkerStyle(21);
  LeadMR_a_gr->SetMarkerSize(1.5);
  LeadMR_a_gr->SetMarkerColor(kBlack);
  LeadMR_a_gr->SetLineColor(kBlack);
  LeadMR_a_gr->SetLineWidth(3);
  
  LeadMR_a_gr->Draw("P");
  
  // let's draw b!
  CarbonMR_b_gr->SetMarkerStyle(24);
  CarbonMR_b_gr->SetMarkerSize(1.5);
  CarbonMR_b_gr->SetMarkerColor(kRed);
  CarbonMR_b_gr->SetLineColor(kRed);
  CarbonMR_b_gr->SetLineWidth(3);
  
  CarbonMR_b_gr->Draw("P");
  
  IronMR_b_gr->SetMarkerStyle(24);
  IronMR_b_gr->SetMarkerSize(1.5);
  IronMR_b_gr->SetMarkerColor(kBlue);
  IronMR_b_gr->SetLineColor(kBlue);
  IronMR_b_gr->SetLineWidth(3);
  
  IronMR_b_gr->Draw("P");

  LeadMR_b_gr->SetMarkerStyle(24);
  LeadMR_b_gr->SetMarkerSize(1.5);
  LeadMR_b_gr->SetMarkerColor(kBlack);
  LeadMR_b_gr->SetLineColor(kBlack);
  LeadMR_b_gr->SetLineWidth(3);
  
  LeadMR_b_gr->Draw("P");
    
  // legend
  if (legendFlag) {
    TLegend *legend = new TLegend(0.7, 0.4, 1., 0.9);
    legend->AddEntry(CarbonMR_a_gr, legendName_a[0], "pl");
    legend->AddEntry(IronMR_a_gr, legendName_a[1], "pl");
    legend->AddEntry(LeadMR_a_gr, legendName_a[2], "pl");
    legend->AddEntry(CarbonMR_b_gr, legendName_b[0], "pl");
    legend->AddEntry(IronMR_b_gr, legendName_b[1], "pl");
    legend->AddEntry(LeadMR_b_gr, legendName_b[2], "pl");
    legend->Draw();
  }
  
  ca->Print(plotFile1); // output file

  /*** STAGE 2: Plot difference ***/
  
  TH1F *CarbonMRdiff = new TH1F("CarbonMRdiff", "", 5, 0.5, 1.);
  CarbonMRdiff->Add(CarbonMR_a, CarbonMR_b, 1, -1);
  CarbonMRdiff->Divide(CarbonMR_a);
  CarbonMRdiff->Scale(100);

  TH1F *IronMRdiff = new TH1F("IronMRdiff", "", 5, 0.5, 1.);
  IronMRdiff->Add(IronMR_a, IronMR_b, 1, -1);
  IronMRdiff->Divide(IronMR_a);
  IronMRdiff->Scale(100);

  TH1F *LeadMRdiff = new TH1F("LeadMRdiff", "", 5, 0.5, 1.);
  LeadMRdiff->Add(LeadMR_a, LeadMR_b, 1, -1);
  LeadMRdiff->Divide(LeadMR_a);
  LeadMRdiff->Scale(100);

  // define arrays for diff
  Double_t empty[kinvarNbins];
  Double_t CarbonMRdiff_y[kinvarNbins];
  Double_t CarbonMRdiff_err[kinvarNbins];
  Double_t IronMRdiff_y[kinvarNbins];
  Double_t IronMRdiff_err[kinvarNbins];
  Double_t LeadMRdiff_y[kinvarNbins];
  Double_t LeadMRdiff_err[kinvarNbins];
  
  // fill arrays
  for (Int_t v = 0; v < kinvarNbins; v++) {
    empty[v] = 0;
    CarbonMRdiff_y[v] = CarbonMRdiff->GetBinContent(v+1);
    CarbonMRdiff_err[v] = CarbonMRdiff->GetBinError(v+1);
    IronMRdiff_y[v] = IronMRdiff->GetBinContent(v+1);
    IronMRdiff_err[v] = IronMRdiff->GetBinError(v+1);
    LeadMRdiff_y[v] = LeadMRdiff->GetBinContent(v+1);
    LeadMRdiff_err[v] = LeadMRdiff->GetBinError(v+1);
  }

  TCanvas *cb = new TCanvas("cb", "cb", 1000, 1000);
  cb->SetGridx(1);
  cb->SetGridy(1);
  gStyle->SetOptStat(0);
  
  // define graphs for diff
  TGraphErrors *CarbonMRdiff_gr = new TGraphErrors(kinvarNbins, MR_x, CarbonMRdiff_y, empty, CarbonMRdiff_err);
  TGraphErrors *IronMRdiff_gr = new TGraphErrors(kinvarNbins, MR_x, IronMRdiff_y, empty, IronMRdiff_err);
  TGraphErrors *LeadMRdiff_gr = new TGraphErrors(kinvarNbins, MR_x, LeadMRdiff_y, empty, LeadMRdiff_err);
    
  // let's draw diff!
  CarbonMRdiff_gr->SetTitle("Difference (%) between Multiplicity Ratios: #omega");
  CarbonMRdiff_gr->GetXaxis()->SetTitle(kinvarTitle);
  CarbonMRdiff_gr->GetXaxis()->CenterTitle();
  CarbonMRdiff_gr->GetXaxis()->SetNdivisions(400 + kinvarNbins, kFALSE);
  CarbonMRdiff_gr->GetXaxis()->SetLimits(kinvarEdges[0], kinvarEdges[kinvarNbins]);
  CarbonMRdiff_gr->GetYaxis()->SetTitle("Difference (%)");
  CarbonMRdiff_gr->GetYaxis()->CenterTitle();
  CarbonMRdiff_gr->GetYaxis()->SetRangeUser(-100, 100); // updated

  CarbonMRdiff_gr->SetMarkerColor(kRed);
  CarbonMRdiff_gr->SetMarkerStyle(22);
  CarbonMRdiff_gr->SetMarkerSize(3);
  CarbonMRdiff_gr->SetLineColor(kRed);
  CarbonMRdiff_gr->SetLineWidth(3);
  
  CarbonMRdiff_gr->Draw("AP");
  
  IronMRdiff_gr->SetMarkerColor(kBlue);
  IronMRdiff_gr->SetMarkerStyle(22);
  IronMRdiff_gr->SetMarkerSize(3);
  IronMRdiff_gr->SetLineColor(kBlue);
  IronMRdiff_gr->SetLineWidth(3);
  
  IronMRdiff_gr->Draw("P");
  
  LeadMRdiff_gr->SetMarkerColor(kBlack);
  LeadMRdiff_gr->SetMarkerStyle(22);
  LeadMRdiff_gr->SetMarkerSize(3);
  LeadMRdiff_gr->SetLineColor(kBlack);
  LeadMRdiff_gr->SetLineWidth(3);
  
  LeadMRdiff_gr->Draw("P");
  
  drawHorizontalLine(0, kBlack, "cont");

  TLegend *l2 = new TLegend(0.15, 0.15, 0.3, 0.3);
  l2->AddEntry(CarbonMRdiff_gr, "Carbon", "p");
  l2->AddEntry(IronMRdiff_gr, "Iron", "p");
  l2->AddEntry(LeadMRdiff_gr, "Lead", "p");
  l2->Draw();
  
  cb->Print(plotFile2); // output file

  printResults(CarbonMRdiff, IronMRdiff, LeadMRdiff);
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakeMR-compare -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hk:A:B:l")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'k': kinvarOption = optarg; break;      
    case 'A': MROption_a = optarg; break;
    case 'B': MROption_b = optarg; break;
    case 'l': legendFlag = kTRUE; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakeMR-compare -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MakeMR-compare program. Usage is:" << std::endl;
  std::cout << "./MakeMR-compare -[options] -[more options]" << std::endl;
  std::cout << "  h     : prints help and exit program" << std::endl;
  std::cout << "  k     : selects kinvar" << std::endl;
  std::cout << "  A[MR] : selects MR" << std::endl;
  std::cout << "  B[MR] : selects MR" << std::endl;
  std::cout << "  where MR could be: {nbs, g, g-b2, bw}" << std::endl;
  std::cout << "  l     : prints legend" << std::endl;
}

void assignOptions() {
  // for kinvar option
  if (kinvarOption == "Z") {
    kinvarTitle = "Z";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesZ[i];
  } else if (kinvarOption == "Q2") {
    kinvarTitle = "Q^{2} (GeV^{2})";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesQ2[i];
  } else if (kinvarOption == "Nu") {
    kinvarTitle = "#nu (GeV)";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesNu[i];
  } else if (kinvarOption == "Pt2") {
    kinvarTitle = "p_{T}^{2} (GeV^{2})";
    for (Int_t i = 0; i < (kinvarNbins+1); i++) kinvarEdges[i] = edgesPt2[i];
  }
  // for a
  if (MROption_a == "g") {
    inputFileName_a = proDir + "/out/MakeMR/bs/bs-MR-" + kinvarOption + "-g-b1.dat";
    histTitle_a = "(MR G+pol1)";
  } else if (MROption_a == "g-b2") {
    inputFileName_a = proDir + "/out/MakeMR/bs/bs-MR-" + kinvarOption + "-g-b2.dat";
    histTitle_a = "(MR G+pol2)";
  } else if (MROption_a == "bw") {
    inputFileName_a = proDir + "/out/MakeMR/bs/bs-MR-" + kinvarOption + "-bw-b1.dat";
    histTitle_a = "(MR BW+pol1)";
  } else if (MROption_a == "nbs") {
    inputFileName_a = proDir + "/out/MakeMR/nbs/nbs-MR-" + kinvarOption + "-5sigma.dat";
    histTitle_a = "(MR non-BS (-5#sigma,5#sigma))";
  }
  // for b
  if (MROption_b == "g") {
    inputFileName_b = proDir + "/out/MakeMR/bs/bs-MR-" + kinvarOption + "-g-b1.dat";
    histTitle_b = "(MR G+pol1)";
  } else if (MROption_b == "g-b2") {
    inputFileName_b = proDir + "/out/MakeMR/bs/bs-MR-" + kinvarOption + "-g-b2.dat";
    histTitle_b = "(MR G+pol2)";
  } else if (MROption_b == "bw") {
    inputFileName_b = proDir + "/out/MakeMR/bs/bs-MR-" + kinvarOption + "-bw-b1.dat";
    histTitle_b = "(MR BW+pol1)";
  } else if (MROption_b == "nbs") {
    inputFileName_b = proDir + "/out/MakeMR/nbs/nbs-MR-" + kinvarOption + "-5sigma.dat";
    histTitle_b = "(MR non-BS (-5#sigma,5#sigma))";
  }
  // file sufix
  plotFile1 = outDir + "/comp-MR-" + kinvarOption + "-" + MROption_a + "_vs_" + MROption_b + ".png";
  plotFile2 = outDir + "/diff-MR-" + kinvarOption + "-" + MROption_a + "_vs_" + MROption_b + ".png";
  histTitleFull = histTitle_a + " - " + histTitle_b;
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
    std::cout << auxString1 << auxString2 << auxString3 << auxString4 << auxString5 << auxString6 << std::endl;
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
    std::cout << auxString1 << auxString2 << auxString3 << auxString4 << auxString5 << auxString6 << std::endl;
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

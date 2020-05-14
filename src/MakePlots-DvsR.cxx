/**************************************/
/* MakePlots-DvsR.cxx                 */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// offers a comparison between data and simrec
// works with old format!!
// pending:
// - add cut around omega mass
// - add gsim (should develop a RvsG...)

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/MakePlots";

TString inputDataFile1 = "";
TString inputDataFile2 = "";
TString inputDataFile3 = "";
TString inputSimrecFile;

// main options
TString targetOption;
TString kinvarOption;
Int_t binNumberZ = 0; // [3-7]: binning on

// cuts
TCut cutAll = cutPi0_old && cutDIS_old && cutPipPim_old;
TCut cutTargType;
TCut cutZ;

// names stuff (to be assigned by the options)
TString titleZ = "";
TString titleKinvar;
TString titleXAxis;
TString titleYAxis = "Normalized Counts = Entries^{-1}"; // default
TString outPrefix;
TString toPlotKinvar;
TString sufixZBin = "";
TString histProperties;

Double_t normSimrec = 1;
Double_t normData = 1;

TString plotFile;

// default values for legend position
Double_t legendY1 = 0.8;
Double_t legendY2 = 0.9;
Double_t legendX1 = 0.65;
Double_t legendX2 = 0.85;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();
void assignOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);
  
  /*** Data ***/
  
  TChain *tData = new TChain();
  tData->Add(inputDataFile1 + "/outdata");
  tData->Add(inputDataFile2 + "/outdata");
  tData->Add(inputDataFile3 + "/outdata");

  setAlias_old(tData);
  
  TH1F *dataHist;
  tData->Draw(toPlotKinvar + ">>data" + histProperties, cutAll && cutTargType && cutZ, "goff");
  dataHist = (TH1F *)gROOT->FindObject("data");
  
  dataHist->SetTitleFont(22);
  dataHist->SetTitle(titleKinvar + targetOption + titleZ);
  dataHist->SetLineColor(kBlack);
  dataHist->SetLineWidth(3);
  dataHist->GetXaxis()->SetTitle(titleXAxis);
  dataHist->GetYaxis()->SetTitle(titleYAxis);
  dataHist->GetXaxis()->CenterTitle();
  dataHist->GetYaxis()->CenterTitle();
  
  /*** Reconstructed ***/
  
  TChain *tSimrec = new TChain();
  tSimrec->Add(inputSimrecFile + "/outdata");

  setAlias_old(tSimrec);
  
  TH1F *simrecHist;
  tSimrec->Draw(toPlotKinvar + ">>simrec" + histProperties, cutAll && cutTargType && cutZ, "goff");
  simrecHist = (TH1F *)gROOT->FindObject("simrec");

  simrecHist->SetTitleFont(22);
  simrecHist->SetLineColor(kBlue);
  simrecHist->SetLineWidth(3);
    
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  gStyle->SetOptStat(0);
  c->SetGrid();

  // normalization
  if (kinvarOption == "IMD") {
    normData = (Double_t) dataHist->GetBinContent(dataHist->GetMaximumBin());
    normSimrec = (Double_t) simrecHist->GetBinContent(simrecHist->GetMaximumBin());
  } else {
    normData = (Double_t) dataHist->GetEntries();
    normSimrec = (Double_t) simrecHist->GetEntries();
  }
  
  dataHist->Scale(1/normData);
  simrecHist->Scale(1/normSimrec);
  
  dataHist->Draw();
  simrecHist->Draw("SAME");

  TLegend *l = new TLegend(legendX1, legendY1, legendX2, legendY2);
  l->AddEntry(dataHist, "data", "l");
  l->AddEntry(simrecHist, "reconstructed", "l");
  l->Draw();
  
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakePlots-DvsR -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:k:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots-DvsR -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakePlots-DvsR program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  toPlotKinvar = " << toPlotKinvar << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakePlots-DvsR program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots-DvsR -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;  
  std::cout << "./MakePlots -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -k[kinvar]" << std::endl;
  std::cout << "    sets kinvar to draw, which can be: " << std::endl;
  std::cout << "    Q2" << std::endl;
  std::cout << "    Nu" << std::endl;
  std::cout << "    W" << std::endl;
  std::cout << "    P(pi+pi-pi0)" << std::endl;
  std::cout << "    wD(pi+pi-pi0)" << std::endl;
  std::cout << "    Z" << std::endl;
  std::cout << "    Pt2" << std::endl;
  std::cout << "    PhiPQ" << std::endl;
  std::cout << "    P0(pi0)" << std::endl;
  std::cout << "    P+(pi+)" << std::endl;
  std::cout << "    P-(pi-)" << std::endl;
  std::cout << "    M0(pi0)" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -z[3-7]" << std::endl;
  std::cout << "    turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for targets
  if (targetOption == "D") {
    inputDataFile1 = dataDir + "/C/wout_C-thickD2.root";
    inputDataFile2 = dataDir + "/Fe/wout_Fe-thickD2.root";
    inputDataFile3 = dataDir + "/Pb/wout_Pb-thinD2.root";
    inputSimrecFile = simDir + "/jlab/D/wout_simrecD.root";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    inputDataFile1 = dataDir + "/C/wout_C-thickD2.root";
    inputSimrecFile = simDir + "/jlab/C/wout_simrecC.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    inputDataFile1 = dataDir + "/Fe/wout_Fe-thickD2.root";
    inputSimrecFile = simDir + "/jlab/Fe/wout_simrecFe.root";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    inputDataFile1 = dataDir + "/Pb/wout_Pb-thinD2.root";
    inputSimrecFile = simDir + "/usm/Pb/wout_simrecPb.root";
    cutTargType = "TargType == 2";
  }
  // for Z binning
  if (binNumberZ) {
    cutZ = Form("%f < Z && Z < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    titleZ = Form(" in (%.02f < Z < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // for kinvar
  if (kinvarOption == "Q2") {
    toPlotKinvar = "Q2";
    titleKinvar = "Q^{2} for ";
    titleXAxis = "Q^{2} (GeV^{2})";
    histProperties = "(200, 1., 4.)";
  } else if (kinvarOption == "Nu") {
    toPlotKinvar = "Nu";
    titleKinvar = "#nu for ";
    titleXAxis = "#nu (GeV)";
    histProperties = "(200, 2.2, 4.2)";
    legendX1 = 0.15;
    legendX2 = 0.35;
  } else if (kinvarOption == "W") {
    toPlotKinvar = "W";
    titleKinvar = "W(#omega) for ";
    titleXAxis = "W";
    histProperties = "(200, 2., 3.)";
  } else if (kinvarOption == "P") {
    toPlotKinvar = "Pomega";
    titleKinvar = "P(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleXAxis = "P (GeV)";
    histProperties = ""; 
  } else if (kinvarOption == "IMD") {
    toPlotKinvar = "deltam";
    titleKinvar = "IMD(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleXAxis = "IMD (GeV)";
    titleYAxis = "Normalized Counts = Max Height^{-1}";
    histProperties = "(200, 0., 1.6)";
  } else if (kinvarOption == "Z") {
    toPlotKinvar = "Z";
    titleKinvar = "Z(#omega) for ";
    titleXAxis = "Z";
    histProperties = "(300, 0., 1.5)";
  } else if (kinvarOption == "Pt2") {
    toPlotKinvar = "Pt2";
    titleKinvar = "p_{T}^{2}(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleXAxis = "p_{T}^{2} (GeV^{2})";
    histProperties = "(150, 0., 1.5)";
  } else if (kinvarOption == "PhiPQ") {
    toPlotKinvar = "PhiPQ";
    titleKinvar = "#phi_{PQ}(#omega) for ";
    titleXAxis = "#phi_{PQ}";
    histProperties = "";
    legendY1 = 0.3;
    legendY2 = 0.4;
  } else if (kinvarOption == "P0") {
    toPlotKinvar = "Ppi0";
    titleKinvar = "P(#pi^{0}) for ";
    titleXAxis = "P (GeV)";
    histProperties = "";
  } else if (kinvarOption == "P+") {
    toPlotKinvar = "Ppip";
    titleKinvar = "P(#pi^{+}) for ";
    titleXAxis = "P (GeV)";
    histProperties = "";
  } else if (kinvarOption == "P-") {
    toPlotKinvar = "Ppim";
    titleKinvar = "P(#pi^{-}) for ";
    titleXAxis = "P (GeV)";
    histProperties = "";
  } else if (kinvarOption == "M0") {
    toPlotKinvar = "mpi0";
    titleKinvar = "IM(#gamma #gamma) for ";
    titleXAxis = "IM (GeV)";
    histProperties = "(200, 0., 1.6)";
  }
  // names
  plotFile = outDir + "/data_vs_simrec-" + targetOption + sufixZBin + "-" + toPlotKinvar + ".png";
}

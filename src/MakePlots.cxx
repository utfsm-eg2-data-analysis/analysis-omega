/**************************************/
/* MakePlots.cxx                      */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// Plots different kinvar spectrums, such as:
//   {IM(omega), IMD(omega),
//    Q2, Z, Nu, Pt2, PhiPQ, pi0M}
// For different sets of targets: D, C, Fe, Pb
// For data only (for now)
// UPDATE:
// - added OS quality cuts
// - added WB quality cuts
// PENDING: add dependence on the other variables

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir      = proDir + "/out/MakePlots";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// main options
Int_t   dataFlag   = 0;
Int_t   simrecFlag = 0;
Int_t   gsimFlag   = 0;
TString targetOption;
TString kinvarOption = "wM_corr";
Int_t   binNumberZ = 0; // 0: off | [3-7]: on

TCut cutTargType;

TCut cutZ = "";
TString titleZ = "";
TString sufixZBin = "";

TString titleDraw;

TString titleKinvar;
TString titleAxis;
TString histProperties;

TString outPrefix;
TString plotFile;

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
  
  TCut cutAll = cutDIS && cutPipPim && cutPi0;

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  TH1F *theHist;
  treeExtracted->Draw(kinvarOption + ">>" + outPrefix + histProperties, cutAll && cutTargType && cutZ, "goff");
  theHist = (TH1F *)gROOT->FindObject(outPrefix);
  
  theHist->SetTitleFont(22);
  theHist->SetTitle(titleKinvar + targetOption + titleDraw + titleZ);
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);
  theHist->GetXaxis()->SetTitle(titleAxis);
  theHist->GetYaxis()->SetTitle("Counts");
  theHist->GetYaxis()->SetMaxDigits(3);
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 768); 
  c->SetGrid();
  
  theHist->Draw("HIST"); // comment if allstat

  /*** Beginning of status parenthesis ***/

  TCut statusCuts_electrons = "StatusEl > 0 && StatusEl < 100 && StatCCEl > 0 && StatSCEl > 0 && StatDCEl > 0 && StatECEl > 0 && DCStatusEl > 0 && SCStatusEl == 33";

  TCut statusCuts_pip = "Status[2] > 0 && Status[2] < 100 && StatDC[2] > 0 && DCStatus[2] > 0";
  TCut statusCuts_pip_le = "P_corr[2] < 2.7 && StatSC[2] > 0";
  TCut statusCuts_pip_he = "P_corr[2] >= 2.7 && Nphe[2] > 25 && StatCC[2] > 0 && Chi2CC[2] < 5./57.3";

  TCut statusCuts_pim = "Status[3] > 0 && Status[3] < 100 && StatDC[3] > 0 && DCStatus[3] > 0";
  TCut statusCuts_pim_le = "P_corr[3] <= 2.5 && !(StatCC[3] > 0 && Nphe[3] > 25)";
  TCut statusCuts_pim_he = "P_corr[3] > 2.5";

  TH1F *testHist;
  // treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutAll && cutTargType && cutZ && statusCuts_electrons, "goff"); // elstat
  // treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutAll && cutTargType && cutZ && statusCuts_pip && (statusCuts_pip_le || statusCuts_pip_he), "goff"); // ppstat
  // treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutAll && cutTargType && cutZ && statusCuts_pim && (statusCuts_pim_le || statusCuts_pim_he), "goff"); // pmstat
  treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutAll && cutTargType && cutZ &&
   		                                                 statusCuts_pim && (statusCuts_pim_le || statusCuts_pim_he) &&
   		                                                 statusCuts_pip && (statusCuts_pip_le || statusCuts_pip_he) &&
  		                                                 statusCuts_electrons, "goff"); // allstat
  testHist = (TH1F *)gROOT->FindObject("test");

  // testHist->SetLineColor(kOrange+7); // elstat
  // testHist->SetLineColor(kBlue); // ppstat
  // testHist->SetLineColor(kRed); // pmstat
  testHist->SetLineColor(kGreen+3); // allstat
  testHist->SetLineWidth(3);

  testHist->Draw("HIST SAME");
  // testHist->Draw("HIST"); // allstat
  
  /*** End of status parenthesis ***/

  drawVerticalLine(0.782, kRed);
  
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakePlots -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hdsgt:k:z:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': dataFlag = 1; break;
    case 's': simrecFlag = 1; break;
    case 'g': gsimFlag = 1; break;
    case 't': targetOption = optarg; break;
    case 'k': kinvarOption = optarg; break;
    case 'z': binNumberZ = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakePlots program. The chosen parameters are:" << std::endl;
  std::cout << "  dataFlag     = " << dataFlag << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  kinvarOption = " << kinvarOption << std::endl;
  std::cout << "  binNumberZ   = " << binNumberZ << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakePlots program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -d" << std::endl;
  std::cout << "    draws data" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -s" << std::endl;
  std::cout << "    draws simrec" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -g" << std::endl;
  std::cout << "    draws gsim" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -k[kinvar]" << std::endl;
  std::cout << "    sets kinvar to draw, it can be: " << std::endl;
  std::cout << "    wM_corr (omega invariant mass)" << std::endl;
  std::cout << "    wD_corr (omega invariant mass difference)" << std::endl;
  std::cout << "    Q2" << std::endl;
  std::cout << "    Nu" << std::endl;
  std::cout << "    Z" << std::endl;
  std::cout << "    Pt2" << std::endl;
  std::cout << "    PhiPQ" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots -z[3-7]" << std::endl;
  std::cout << "    turns on binning in Z (off by default) and analyzes that specific bin" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  if (dataFlag) {
    outPrefix = "data";
    titleDraw = " Data ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = dataDir + "/C/comb_dataC.root";
      inputFile2 = dataDir + "/Fe/comb_dataFe.root";
      inputFile3 = dataDir + "/Pb/comb_dataPb.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/C/comb_dataC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Fe/comb_dataFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Pb/comb_dataPb.root";
    }
  }
  /* else if (simrecFlag) {
    outPrefix = "simrec";
    titleDraw = " Reconstructed ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = simDir + "/jlab/D/comb_simrecD.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/C/comb_simrecC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/Fe/comb_simrecFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/usm/Pb/comb_simrecPb.root";
    }
  } else if (gsimFlag) {
    outPrefix = "gsim";
    titleDraw = " Generated ";
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = simDir + "/jlab/D/comb_gsimD.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/C/comb_gsimC.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/jlab/Fe/comb_gsimFe.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = simDir + "/usm/Pb/comb_gsimPb.root";
    }
 
  }
  */
  // for Z binning
  if (binNumberZ) {
    cutZ = Form("%f < wZ_corr && wZ_corr < %f", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    // OS quality cuts
    /*
    cutZ = Form("%f < Z && Z < %f && %f < Pt2 && Pt2 < %f && %f < Q2 && Q2 < %f && %f < Nu && Nu < %f",
		edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3],
		edgesPt2[0], edgesPt2[5],
		edgesQ2[0], edgesQ2[5],
		edgesNu[0], edgesNu[5]);
    */
    titleZ = Form("in (%.02f < wZ_corr < %.02f)", edgesZ[binNumberZ-3], edgesZ[binNumberZ+1-3]);
    sufixZBin = Form("-z%d", binNumberZ);
  }
  // for kinvar
  if (kinvarOption == "wM_corr") {
    titleKinvar = "IM(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(250, 0., 2.5.)";
  } else if (kinvarOption == "wM_true") {
    titleKinvar = "IM(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(250, 0., 2.5.)";
  } else if (kinvarOption == "wD_corr") {
    titleKinvar = "IMD(#pi^{+} #pi^{-} #pi^{0}) for ";
    titleAxis = "IMD (GeV)";
    histProperties = "(200, 0., 1.6)";
  } else if (kinvarOption == "Q2") {
    titleKinvar = "Q^{2} for ";
    titleAxis = "Q^{2} (GeV^{2})";
    histProperties = "(100, 1., 4.)";  
  } else if (kinvarOption == "Nu") {
    titleKinvar = "#nu for ";
    titleAxis = "#nu (GeV)";
    histProperties = "(200, 2.2, 4.2)";
  } else if (kinvarOption == "Z") {
    titleKinvar = "Z for ";
    titleAxis = "Z";
    histProperties = "(100, 0., 1.2)";
  } else if (kinvarOption == "Pt2") {
    titleKinvar = "p_{T}^{2} for ";
    titleAxis = "p_{T}^{2} (GeV^{2})";
    histProperties = "(100, 0., 1.5)";
  } else if (kinvarOption == "PhiPQ") {
    titleKinvar = "#phi_{PQ} for ";
    titleAxis = "#phi_{PQ} (degrees)";
    histProperties = "(100, -180, 180.)";
  } else if (kinvarOption == "pi0M") {
    titleKinvar = "IM(#gamma #gamma) for ";
    titleAxis = "IM (GeV)";
    histProperties = "(100, 0, 1.6)";
  } 
  // output name
  plotFile = outDir + "/" + outPrefix + "-" + targetOption + "-" + kinvarOption + sufixZBin + ".png";
}

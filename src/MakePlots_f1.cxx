/**************************************/
/* MakePlots_f1.cxx                   */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir      = proDir + "/out/FilterNCombine/f1";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

// main options
TString targetOption;
TString kinvarOption = "wM_corr";

TCut cutTargType;

TString titleDraw;

TString titleKinvar;
TString titleAxis;
TString histProperties;

TString plotFile;
Color_t targetColor;

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
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");

  TCut cutPi0A = "0.059 < pi0A_M_corr && pi0A_M_corr < 0.203";
  TCut cutPi0B = "0.059 < pi0B_M_corr && pi0B_M_corr < 0.203";

  TCut statusCuts_pip_f1 = "Status[4] > 0 && StatDC[4] > 0 && DCStatus[4] > 0";
  TCut statusCuts_pim_f1 = "Status[5] > 0 && StatDC[5] > 0 && DCStatus[5] > 0";
  TCut cutStatus_f1      = statusCuts_electrons && statusCuts_pip_f1 && statusCuts_pim_f1;
  
  TH1F *theHist;
  treeExtracted->Draw(kinvarOption + ">>data" + histProperties, cutDIS && cutTargType && cutStatus_f1 && cutPi0A && cutPi0B, "goff"); //  && cutPi0A && cutPi0B && cutStatus_f1
  theHist = (TH1F *)gROOT->FindObject("data");
  
  theHist->SetTitle(titleKinvar + targetOption + titleDraw);
  theHist->SetLineColor(targetColor);
  theHist->SetLineWidth(3);
  theHist->GetXaxis()->SetTitle(titleAxis);
  theHist->GetXaxis()->CenterTitle();
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
  /*
  TH1F *testHist;
  // treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutAll && cutTargType && cutZ && statusCuts_electrons, "goff"); // elstat
  // treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutAll && cutTargType && cutZ && statusCuts_pip && (statusCuts_pip_le || statusCuts_pip_he), "goff"); // ppstat
  // treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutAll && cutTargType && cutZ && statusCuts_pim && (statusCuts_pim_le || statusCuts_pim_he), "goff"); // pmstat
  treeExtracted->Draw(kinvarOption + ">>test" +  histProperties, cutDIS && cutTargType &&
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
  */
  /*** End of status parenthesis ***/

  drawVerticalLine(kMf1, kRed);
  
  c->Print(plotFile); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MakePlots_f1 -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MakePlots_f1 -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing MakePlots_f1 program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "MakePlots_f1 program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots_f1 -h" << std::endl;
  std::cout << "    prints help and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MakePlots_f1 -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for kind of data
  titleDraw = " Data ";
  // for targets
  if (targetOption == "D") {
    cutTargType = "TargType == 1";
    inputFile1 = proDir + "/out/FilterNCombine/f1/combC_data.root";
    inputFile2 = proDir + "/out/FilterNCombine/f1/combFe_data.root";
    inputFile3 = proDir + "/out/FilterNCombine/f1/combPb_data.root";
    targetColor = kGreen+3;
  } else if (targetOption == "C") {
    cutTargType = "TargType == 2";
    inputFile1 = proDir + "/out/FilterNCombine/f1/combC_data.root";
    targetColor = kRed;
  } else if (targetOption == "Fe") {
    cutTargType = "TargType == 2";
    inputFile1 = proDir + "/out/FilterNCombine/f1/combFe_data.root";
    targetColor = kBlue;
  } else if (targetOption == "Pb") {
    cutTargType = "TargType == 2";
    inputFile1 = proDir + "/out/FilterNCombine/f1/combPb_data.root";
    targetColor = kBlack;
  } else if (targetOption == "All") {
    cutTargType = "TargType == 1 || TargType == 2";
    inputFile1 = proDir + "/out/FilterNCombine/f1/combC_data.root";
    inputFile2 = proDir + "/out/FilterNCombine/f1/combFe_data.root";
    inputFile3 = proDir + "/out/FilterNCombine/f1/combPb_data.root";
    targetColor = kOrange+3;
  }
  titleKinvar = "m(4 #gamma #pi^{+} #pi^{-}) for ";
  titleAxis = "Reconstructed Mass (GeV)";
  histProperties = "(250, 0., 2.5.)";
  // output name
  plotFile = outDir + "/f1-" + targetOption + ".png";
}

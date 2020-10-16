/**************************************/
/* Acceptance_EN.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// get electron numbers from simulation files

#include "analysisConfig.h"

// the only option
TString targetOption;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  printOptions();

  // set options
  TString outputFile = "electron-numbers" + targetOption + ".root";

  // extract histograms
  TChain *treeExtracted = new TChain();
  treeExtracted->Add("pruned" + targetOption + "_*.root/ntuple_e"); // all files in current dir

  // create and open output file
  TFile *outputRootFile = new TFile(outputFile, "RECREATE");      

  /*** BIG PICTURE - GSIM ***/
  
  // set GSIM cuts
  TCut cutGSIM = cutDIS_gsim;

  // create histogram
  TH1F *bigHist_GSIM;
  treeExtracted->Draw("mc_Q2>>GSIM_" + targetOption + "(900, 1., 4.)", cutGSIM, "goff");
  bigHist_GSIM = (TH1F *)gROOT->FindObject("GSIM_" + targetOption);
  bigHist_GSIM->SetTitle("GSIM Q2 for " + targetOption);

  // save hist
  bigHist_GSIM->Write();
  
  /*** BINNING - GSIM ***/
  
  TH1F   *binHist;
  TString binHistName;
  TCut binCutGSIM;
  
  // Q2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "GSIM_" + targetOption + Form("_Q%d", i);
    binCutGSIM  = Form("mc_Q2 > %.3f && mc_Q2 < %.3f" , edgesQ2[i], edgesQ2[i+1]);
    // extract
    treeExtracted->Draw("mc_Q2>>" + binHistName + Form("(150, %.2f, %.2f)", edgesQ2[i], edgesQ2[i+1]), cutGSIM && binCutGSIM, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("GSIM Q2 for " + targetOption + " in " + Form("(%.2f < mc_Q2 < %.2f)" , edgesQ2[i], edgesQ2[i+1]));
    // save
    binHist->Write();      
  }

  // Nu
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "GSIM_" + targetOption + Form("_N%d", i);
    binCutGSIM  = Form("mc_Nu > %.3f && mc_Nu < %.3f" , edgesNu[i], edgesNu[i+1]);
    // extract
    treeExtracted->Draw("mc_Nu>>" + binHistName + Form("(150, %.2f, %.2f)" , edgesNu[i], edgesNu[i+1]), cutGSIM && binCutGSIM, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("GSIM Nu for " + targetOption + " in " + Form("(%.2f < mc_Nu < %.2f)" , edgesNu[i], edgesNu[i+1]));
    // save
    binHist->Write();      
  }

  /*** BIG PICTURE - SIMREC ***/
  
  // set SIMREC cuts
  TCut cutSIMREC = cutDIS_simrec && cutStatus_ntuple_e;
  
  // create histogram
  TH1F *bigHist_SIMREC;
  treeExtracted->Draw("Q2>>SIMREC_" + targetOption + "(600, 1., 4.)", cutSIMREC, "goff");
  bigHist_SIMREC = (TH1F *)gROOT->FindObject("SIMREC_" + targetOption);
  bigHist_SIMREC->SetTitle("SIMREC Q2 for " + targetOption);

  // save hist
  bigHist_SIMREC->Write();

  /*** BINNING - SIMREC ***/
  
  TCut binCutSIMREC;
  
  // Q2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "SIMREC_" + targetOption + Form("_Q%d", i);
    binCutSIMREC = Form("Q2 > %.3f && Q2 < %.3f" , edgesQ2[i], edgesQ2[i+1]);
    // extract
    treeExtracted->Draw("Q2>>" + binHistName + Form("(75, %.2f, %.2f)" , edgesQ2[i], edgesQ2[i+1]), cutSIMREC && binCutSIMREC, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("SIMREC Q2 for " + targetOption + " in " + Form("(%.2f < Q2 < %.2f)", edgesQ2[i], edgesQ2[i+1]));
    // save
    binHist->Write();
  }

  // Nu
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "SIMREC_" + targetOption + Form("_N%d", i);
    binCutSIMREC = Form("Nu > %.3f && Nu < %.3f" , edgesNu[i], edgesNu[i+1]);
    // extract
    treeExtracted->Draw("Nu>>" + binHistName + Form("(75, %.2f, %.2f)" , edgesNu[i], edgesNu[i+1]), cutSIMREC && binCutSIMREC, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("SIMREC Nu for " + targetOption + " in " + Form("(%.2f < Nu < %.2f)", edgesNu[i], edgesNu[i+1]));
    // save
    binHist->Write();
  }

  // close file
  outputRootFile->Close();
  
  std::cout << std::endl;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./Acceptance_EN -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./Acceptance_EN -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing Acceptance_EN program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void printUsage() {
  std::cout << "Acceptance_EN program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_EN -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_EN -t[target]" << std::endl;
  std::cout << "    selects target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
}

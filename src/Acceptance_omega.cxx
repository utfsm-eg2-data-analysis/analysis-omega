/**************************************/
/* Acceptance_omega.cxx               */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plot omega invariant mass difference of sim/reconstructed or sim/generated
// histograms are written in an output root file

#include "analysisConfig.h"

/*** Global variables ***/

// options
Int_t simrecFlag = 0;
Int_t gsimFlag   = 0;
TString targetOption;
TString setOption;
TString nDir;

// filenames
TString inputDir;
TString outputDir;
TString outputFile;
TString nDirSufix = ""; // default

// cuts
TCut cutSIMREC;
TCut cutGSIM;

// hist properties
TString varName;
TString histName;
TString histProperties;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // set cuts
  cutGSIM   = cutDIS_gsim && cutPi0_gsim && cutPipPim_gsim;
  cutSIMREC = cutDIS_simrec && cutPi0_simrec && cutPipPim_simrec && cutStatus_simrec;
  if (gsimFlag) cutSIMREC = "";

  // extract histograms
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputDir + "/comb" + targetOption + "_*.root/mix");

  // create histogram
  TH1F *theHist;
  treeExtracted->Draw(varName + ">>" + histName + histProperties, cutSIMREC && cutGSIM, "goff");
  theHist = (TH1F *)gROOT->FindObject(histName);

  // create file, write hist
  TFile *theFile = new TFile(outputFile, "RECREATE");
  theHist->Write();

  /*** BINNING ***/
  
  TH1F   *binHist;
  TString binHistName;
  TCut binCutSIMREC;
  TCut binCutGSIM;
  
  // Q2
  for (Int_t i = 0; i < 5; i++) {
    if (gsimFlag) {
      // update
      binHistName = histName + Form("_Q%d", i);
      binCutGSIM   = Form("mc_Q2 > %f && mc_Q2 < %f" , edgesQ2[i], edgesQ2[i+1]);
      // extract
      treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutGSIM, "goff");
      binHist = (TH1F *)gROOT->FindObject(binHistName);
      // save
      binHist->Write();      
    } else if (simrecFlag) {
      for (Int_t j = 0; j < 5; j++) {
	// update
	binHistName = histName + Form("_Q%dQ%d", i, j);
	binCutGSIM   = Form("mc_Q2 > %f && mc_Q2 < %f" , edgesQ2[i], edgesQ2[i+1]);
	binCutSIMREC = Form("Q2 > %f && Q2 < %f" , edgesQ2[j], edgesQ2[j+1]);
	// extract
	treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutSIMREC && binCutGSIM, "goff");
	binHist = (TH1F *)gROOT->FindObject(binHistName);
	// save
	binHist->Write();
      }
    }
  }

  // Nu
  for (Int_t i = 0; i < 5; i++) {
    if (gsimFlag) {
      // update
      binHistName = histName + Form("_N%d", i);
      binCutGSIM   = Form("mc_Nu > %f && mc_Nu < %f" , edgesNu[i], edgesNu[i+1]);
      // extract
      treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutGSIM, "goff");
      binHist = (TH1F *)gROOT->FindObject(binHistName);
      // save
      binHist->Write();      
    } else if (simrecFlag) {
      for (Int_t j = 0; j < 5; j++) {
	// update
	binHistName = histName + Form("_N%dN%d", i, j);
	binCutGSIM   = Form("mc_Nu > %f && mc_Nu < %f" , edgesNu[i], edgesNu[i+1]);
	binCutSIMREC = Form("Nu > %f && Nu < %f" , edgesNu[j], edgesNu[j+1]);
	// extract
	treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutSIMREC && binCutGSIM, "goff");
	binHist = (TH1F *)gROOT->FindObject(binHistName);
	// save
	binHist->Write();
      }
    }
  }

  // Pt2
  for (Int_t i = 0; i < 5; i++) {
    if (gsimFlag) {
      // update
      binHistName = histName + Form("_P%d", i);
      binCutGSIM   = Form("mc_wPt2 > %f && mc_wPt2 < %f" , edgesPt2[i], edgesPt2[i+1]);
      // extract
      treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutGSIM, "goff");
      binHist = (TH1F *)gROOT->FindObject(binHistName);
      // save
      binHist->Write();      
    } else if (simrecFlag) {
      for (Int_t j = 0; j < 5; j++) {
	// update
	binHistName = histName + Form("_P%dP%d", i, j);
	binCutGSIM   = Form("mc_wPt2 > %f && mc_wPt2 < %f" , edgesPt2[i], edgesPt2[i+1]);
	binCutSIMREC = Form("wPt2_corr > %f && wPt2_corr < %f" , edgesPt2[j], edgesPt2[j+1]);
	// extract
	treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutSIMREC && binCutGSIM, "goff");
	binHist = (TH1F *)gROOT->FindObject(binHistName);
	// save
	binHist->Write();
      }
    }
  }

  // Z
  for (Int_t i = 0; i < 5; i++) {
    if (gsimFlag) {
      // update
      binHistName = histName + Form("_Z%d", i);
      binCutGSIM   = Form("mc_wZ > %f && mc_wZ < %f" , edgesZ[i], edgesZ[i+1]);
      // extract
      treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutGSIM, "goff");
      binHist = (TH1F *)gROOT->FindObject(binHistName);
      // save
      binHist->Write();      
    } else if (simrecFlag) {
      for (Int_t j = 0; j < 5; j++) {
	// update
	binHistName = histName + Form("_Z%dZ%d", i, j);
	binCutGSIM   = Form("mc_wZ > %f && mc_wZ < %f" , edgesZ[i], edgesZ[i+1]);
	binCutSIMREC = Form("wZ_corr > %f && wZ_corr < %f" , edgesZ[j], edgesZ[j+1]);
	// extract
	treeExtracted->Draw(varName + ">>" + binHistName + histProperties, cutSIMREC && cutGSIM && binCutSIMREC && binCutGSIM, "goff");
	binHist = (TH1F *)gROOT->FindObject(binHistName);
	// save
	binHist->Write();
      }
    }
  }
  
  // close file
  theFile->Close();
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./Acceptance_omega -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "hs:g:r:n:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'r': simrecFlag = 1; gsimFlag = 0; targetOption = optarg; break;
    case 'g': simrecFlag = 0; gsimFlag = 1; targetOption = optarg; break;
    case 's': setOption = optarg; break;
    case 'n': nDir      = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./Acceptance_omega -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "Acceptance_omega program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_omega -h" << std::endl;
  std::cout << "  print usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_omega -[r,g][target]" << std::endl;
  std::cout << "  select simulation: r (simrec) or g (generated)" << std::endl;
  std::cout << "  select target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;  
  std::cout << "./Acceptance_omega -s[set]" << std::endl;
  std::cout << "  choose set: old, usm, jlab - all" << std::endl;
  std::cout << std::endl;
  std::cout << "./Acceptance_omega -n[ndir]" << std::endl;
  std::cout << "  if jlab, choose directory number" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing Acceptance_omega program. The chosen parameters are:" << std::endl;
  std::cout << "  simrecFlag   = " << simrecFlag << std::endl;
  std::cout << "  gsimFlag     = " << gsimFlag << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  setOption    = " << setOption << std::endl;
  std::cout << "  nDir         = " << nDir << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for set
  if (setOption == "jlab") {
    nDirSufix = "-" + nDir;
    inputDir = workDir + "/FilterNCombine/" + setOption + "/" + targetOption + "/" + nDir;
  } else {
    inputDir = workDir + "/FilterNCombine/" + setOption + "/" + targetOption;
  }
  outputDir = workDir + "/Acceptance/omega";
  system("mkdir -p " + outputDir);
  // for type of sim
  if (simrecFlag) {
    varName = "wD_corr";
    histProperties = "(400, 0., 1.6)";
    histName = "omega-" + targetOption + "_SIMREC";
    outputFile  = outputDir + "/mass-omega_" + setOption + "-" + targetOption + nDirSufix + "_SIMREC.root";
   } else if (gsimFlag) {
    varName = "mc_wD";
    histProperties = "(800, 0., 1.6)";
    histName = "omega-" + targetOption + "_GSIM";
    outputFile  = outputDir + "/mass-omega_" + setOption + "-" + targetOption + nDirSufix + "_GSIM.root";
  }
}

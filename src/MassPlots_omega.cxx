/**************************************/
/* MassPlots.cxx                      */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plot omega invariant mass difference of data
// histograms are written in an output root file
// (exclusive for PC)

#include "analysisConfig.h"

// the only option
TString targetOption;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);  
  printOptions();

  // set options
  TString outputFile = "omega-data-" + targetOption + ".root";

  // set dirs
  TString dataDir = workDir + "/FilterNCombine/data";
  TString outDir  = workDir + "/Acceptance/data";
  system("mkdir -p " + outDir); // just in case
  
  // extract histograms
  TChain *treeExtracted = new TChain();
  if (targetOption == "D") {
    treeExtracted->Add(dataDir + "/C/comb_dataC.root/mix");
    treeExtracted->Add(dataDir + "/Fe/comb_dataFe.root/mix");
    treeExtracted->Add(dataDir + "/Pb/comb_dataPb.root/mix");
  } else {
    treeExtracted->Add(dataDir + "/" + targetOption + "/comb_data" + targetOption + ".root/mix");
  }
  
  // create and open output file
  TFile *theFile = new TFile(outputFile, "RECREATE");
  
  /*** BIG PICTURE - DATA ***/
  
  // set DATA cuts
  TCut cutTargType;
  if (targetOption == "D") {
    cutTargType = cutTargType_D;
  } else if (targetOption == "C") {
    cutTargType = cutTargType_C;    
  } else if (targetOption == "Fe") {
    cutTargType = cutTargType_Fe;
  } else if (targetOption == "Pb") {
    cutTargType = cutTargType_Pb;
  }
  TCut cutDATA = cutDIS && cutPi0 && cutPipPim && cutStatus && cutTargType;

  // create histogram
  TH1F *bigHist_DATA;
  treeExtracted->Draw("wSD_corr>>DATA_" + targetOption + "(400, 0., 1.6)", cutDATA, "goff");
  bigHist_DATA = (TH1F *)gROOT->FindObject("DATA_" + targetOption);
  bigHist_DATA->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption);

  // save hist
  bigHist_DATA->Write();
  
  /*** BINNING - DATA ***/
  
  TH1F   *binHist;
  TString binHistName;
  TCut    binCutDATA;
  
  // Q2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_Q%d", i);
    binCutDATA  = Form("Q2 > %.3f && Q2 < %.3f" , edgesQ2[i], edgesQ2[i+1]);
    // extract
    treeExtracted->Draw("wSD_corr>>" + binHistName + "(120, 0.60, 0.96)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Q2 < %.2f)" , edgesQ2[i], edgesQ2[i+1]));
    // save
    binHist->Write();      
  }

  // Nu
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_N%d", i);
    binCutDATA  = Form("Nu > %.3f && Nu < %.3f" , edgesNu[i], edgesNu[i+1]);
    // extract
    treeExtracted->Draw("wSD_corr>>" + binHistName + "(120, 0.60, 0.96)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Nu < %.2f)" , edgesNu[i], edgesNu[i+1]));
    // save
    binHist->Write();      
  }

  // Pt2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_P%d", i);
    binCutDATA  = Form("wPt2_corr > %.3f && wPt2_corr < %.3f" , edgesPt2[i], edgesPt2[i+1]);
    // extract
    treeExtracted->Draw("wSD_corr>>" + binHistName + "(120, 0.60, 0.96)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Pt2 < %.2f)" , edgesPt2[i], edgesPt2[i+1]));
    // save
    binHist->Write();      
  }

  // Z
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "DATA_" + targetOption + Form("_Z%d", i);
    binCutDATA  = Form("wZ_corr > %.3f && wZ_corr < %.3f" , edgesZ[i], edgesZ[i+1]);
    // extract
    treeExtracted->Draw("wSD_corr>>" + binHistName + "(120, 0.60, 0.96)", cutDATA && binCutDATA, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("DATA #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Z < %.2f)" , edgesZ[i], edgesZ[i+1]));
    // save
    binHist->Write();
  }
    
  // close file
  theFile->Close();
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MassPlots_omega -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./MassPlots_omega -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "MassPlots_omega program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MassPlots_omega -h" << std::endl;
  std::cout << "  print usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MassPlots_omega -t[target]" << std::endl;
  std::cout << "  select target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing MassPlots_omega program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

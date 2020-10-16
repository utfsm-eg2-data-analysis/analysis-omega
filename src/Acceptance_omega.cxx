/**************************************/
/* Acceptance_omega.cxx               */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// plot omega invariant mass difference of sim/reconstructed or sim/generated
// histograms are written in an output root file

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
  TString outputFile = "acceptance" + targetOption + ".root";
  
  // extract histograms
  TChain *treeExtracted = new TChain();
  treeExtracted->Add("comb" + targetOption + "_*.root/mix"); // all files in current dir

  // create and open output file
  TFile *theFile = new TFile(outputFile, "RECREATE");
  
  /*** BIG PICTURE - GSIM ***/
  
  // set GSIM cuts
  TCut cutGSIM = cutDIS_gsim && cutPi0_gsim && cutPipPim_gsim;

  // create histogram
  TH1F *bigHist_GSIM;
  treeExtracted->Draw("mc_wD>>GSIM_" + targetOption + "(1600, 0., 1.6)", cutGSIM, "goff");
  bigHist_GSIM = (TH1F *)gROOT->FindObject("GSIM_" + targetOption);
  bigHist_GSIM->SetTitle("GSIM #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption);

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
    treeExtracted->Draw("mc_wD>>" + binHistName + "(1600, 0., 1.6)", cutGSIM && binCutGSIM, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("GSIM #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < mc_Q2 < %.2f)" , edgesQ2[i], edgesQ2[i+1]));
    // save
    binHist->Write();      
  }

  // Nu
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "GSIM_" + targetOption + Form("_N%d", i);
    binCutGSIM  = Form("mc_Nu > %.3f && mc_Nu < %.3f" , edgesNu[i], edgesNu[i+1]);
    // extract
    treeExtracted->Draw("mc_wD>>" + binHistName + "(1600, 0., 1.6)", cutGSIM && binCutGSIM, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("GSIM #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < mc_Nu < %.2f)" , edgesNu[i], edgesNu[i+1]));
    // save
    binHist->Write();      
  }

  // Pt2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "GSIM_" + targetOption + Form("_P%d", i);
    binCutGSIM  = Form("mc_wPt2 > %.3f && mc_wPt2 < %.3f" , edgesPt2[i], edgesPt2[i+1]);
    // extract
    treeExtracted->Draw("mc_wD>>" + binHistName + "(1600, 0., 1.6)", cutGSIM && binCutGSIM, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("GSIM #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < mc_Pt2 < %.2f)" , edgesPt2[i], edgesPt2[i+1]));
    // save
    binHist->Write();      
  }

  // Z
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "GSIM_" + targetOption + Form("_Z%d", i);
    binCutGSIM  = Form("mc_wZ > %.3f && mc_wZ < %.3f" , edgesZ[i], edgesZ[i+1]);
    // extract
    treeExtracted->Draw("mc_wD>>" + binHistName + "(1600, 0., 1.6)", cutGSIM && binCutGSIM, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("GSIM #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < mc_Z < %.2f)" , edgesZ[i], edgesZ[i+1]));
    // save
    binHist->Write();
  }
  
  /*** BIG PICTURE - SIMREC ***/
  
  // set SIMREC cuts
  TCut cutSIMREC = cutDIS_simrec && cutPi0_simrec && cutPipPim_simrec && cutStatus_simrec;
  
  // create histogram
  TH1F *bigHist_SIMREC;
  treeExtracted->Draw("wD_corr>>SIMREC_" + targetOption + "(800, 0., 1.6)", cutSIMREC, "goff");
  bigHist_SIMREC = (TH1F *)gROOT->FindObject("SIMREC_" + targetOption);
  bigHist_SIMREC->SetTitle("SIMREC #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption);

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
    treeExtracted->Draw("wD_corr>>" + binHistName + "(800, 0., 1.6)", cutSIMREC && binCutSIMREC, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("SIMREC #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Q2 < %.2f)" , edgesQ2[i], edgesQ2[i+1]));
    // save
    binHist->Write();
  }

  // Nu
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "SIMREC_" + targetOption + Form("_N%d", i);
    binCutSIMREC = Form("Nu > %.3f && Nu < %.3f" , edgesNu[i], edgesNu[i+1]);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(800, 0., 1.6)", cutSIMREC && binCutSIMREC, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("SIMREC #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Nu < %.2f)" , edgesNu[i], edgesNu[i+1]));
    // save
    binHist->Write();
  }

  // Pt2
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "SIMREC_" + targetOption + Form("_P%d", i);
    binCutSIMREC = Form("wPt2_corr > %.3f && wPt2_corr < %.3f" , edgesPt2[i], edgesPt2[i+1]);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(800, 0., 1.6)", cutSIMREC && binCutSIMREC, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("SIMREC #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Pt2 < %.2f)", edgesPt2[i], edgesPt2[i+1]));
    // save
    binHist->Write();
  }

  // Z
  for (Int_t i = 0; i < 5; i++) {
    // update
    binHistName = "SIMREC_" + targetOption + Form("_Z%d", i);
    binCutSIMREC = Form("wZ_corr > %.3f && wZ_corr < %.3f" , edgesZ[i], edgesZ[i+1]);
    // extract
    treeExtracted->Draw("wD_corr>>" + binHistName + "(800, 0., 1.6)", cutSIMREC && binCutSIMREC, "goff");
    binHist = (TH1F *)gROOT->FindObject(binHistName);
    binHist->SetTitle("SIMREC #Deltam(#gamma #gamma #pi^{+} #pi^{-}) for " + targetOption + " in " + Form("(%.2f < Z < %.2f)", edgesZ[i], edgesZ[i+1]));
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
    std::cerr << "Empty command line. Execute ./Acceptance_omega -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
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
  std::cout << "./Acceptance_omega -t[target]" << std::endl;
  std::cout << "  select target: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing Acceptance_omega program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

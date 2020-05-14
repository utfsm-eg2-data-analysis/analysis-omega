/**************************************/
/* DalitzPlots.cxx                    */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// UPDATE:
// adapted to new config file and new FNC format

#include "analysisConfig.h"

/*** Global variables ***/

// options
TString targetOption;

// dir
TString outDir = proDir + "/out/DalitzPlots";
TString inputFile1  = "";
TString inputFile2  = "";
TString inputFile3  = "";

TString outFile1;
TString outFile2;
TString outFile3;

// cuts
TCut cutTargType;
TCut cutAll;

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // make dir, just in case
  system("mkdir -p " + outDir);
  
  TCut cutAll = cutDIS; // no cut on pippim nor pi0! we want to see it!

  // define histograms
  TH2F *dataHist;
  TH2F *dataHist2;
  TH2F *dataHist3;  

  // extracting tree
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  /*** Setting alias - 0 ***/
  
  // (1) -> pip, (2) -> pim, (3) -> pi0

  // energy squared
  treeExtracted->SetAlias("pipE2", "pipP2 + pipM*pipM");
  treeExtracted->SetAlias("pipE", "TMath::Sqrt(pipE2)");
  treeExtracted->SetAlias("pimE2", "pimP2 + pimM*pimM");
  treeExtracted->SetAlias("pimE", "TMath::Sqrt(pimE2)");
  // crossed terms
  treeExtracted->SetAlias("pimpi0P", "Px[3]*pi0Px + Py[3]*pi0Py + Pz[3]*pi0Pz");
  treeExtracted->SetAlias("pimpi0E", "pimE*pi0E");
  treeExtracted->SetAlias("pippi0P", "Px[2]*pi0Px + Py[2]*pi0Py + Pz[2]*pi0Pz");
  treeExtracted->SetAlias("pippi0E", "pipE*pi0E");
  // dalitz plots!
  treeExtracted->SetAlias("pippimM2", "pippimM*pippimM"); // better prevent
  treeExtracted->SetAlias("pimpi0M2", "pimM*pimM + pi0M*pi0M + 2*(pimpi0E - pimpi0P)");
  treeExtracted->SetAlias("pippi0M2", "pipM*pipM + pi0M*pi0M + 2*(pippi0E - pippi0P)");
  // for the cuts
  treeExtracted->SetAlias("pimpi0M", "TMath::Sqrt(pimpi0M2)");
  treeExtracted->SetAlias("pippi0M", "TMath::Sqrt(pippi0M2)");
  
  /*** The cuts: pip pim vs pim pi0 ***/
  
  // box
  Double_t sum23 = kMpi + kMpi0;
  Double_t sum12 = 2*kMpi;
  Double_t difP1 = kMomega - kMpi;
  Double_t difP3 = kMomega - kMpi0;
  
  TCut cutLeft1   = Form("pimpi0M > %f", sum23); // (mpim + mpi0)
  TCut cutRight1  = Form("pimpi0M < %f", difP1); // (momega - mpip)
  TCut cutBottom1 = Form("pippimM > %f", sum12); // (mpip + mpim)
  TCut cutTop1    = Form("pippimM < %f", difP3); // (momega - mpi0)

  TCut cutBox1 = cutLeft1 && cutRight1 && cutBottom1 && cutTop1;
  
  // dalitz
  treeExtracted->SetAlias("Estar2", Form("(pippimM2 - %f + %f)/2/pippimM", kMpi*kMpi, kMpi*kMpi));
  treeExtracted->SetAlias("Estar3", Form("(%f - pippimM2 - %f)/2/pippimM", kMomega*kMomega, kMpi0*kMpi0));
  treeExtracted->SetAlias("Estar23", "Estar2 + Estar3");
  treeExtracted->SetAlias("Estar23Sq", "Estar23*Estar23");
  
  treeExtracted->SetAlias("Eroot2", Form("TMath::Sqrt(Estar2*Estar2 - %f)", kMpi*kMpi));
  treeExtracted->SetAlias("Eroot3", Form("TMath::Sqrt(Estar3*Estar3 - %f)", kMpi0*kMpi0));
  treeExtracted->SetAlias("Edif23", "Eroot2 - Eroot3");
  treeExtracted->SetAlias("Esum23", "Eroot2 + Eroot3");
  treeExtracted->SetAlias("Edif23Sq", "Edif23*Edif23");
  treeExtracted->SetAlias("Esum23Sq", "Esum23*Esum23");

  treeExtracted->SetAlias("Max23", "Estar23Sq - Edif23Sq");
  treeExtracted->SetAlias("Min23", "Estar23Sq - Esum23Sq");
  
  TCut cutDalitz23Up = "pimpi0M2 < Max23";
  TCut cutDalitz23Down = "pimpi0M2 > Min23";
  
  /*** Drawing: pip pim vs pim pi0 ***/
  
  // data->Draw("m2pippim:m2pimpi0>>data(100, 0., 1., 100, 0., 1.)", cutAll && cutTargType && cutBox1 && cutDalitz23Up && cutDalitz23Down, "goff");
  treeExtracted->Draw("pippimM2:pimpi0M2>>data(100, 0., 1., 100, 0., 1.)", cutAll && cutTargType, "goff");
  dataHist = (TH2F *)gROOT->FindObject("data");
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1, 0);

  dataHist->SetTitle("#omega Dalitz plot for " + targetOption);
  dataHist->GetYaxis()->SetTitle("M^{2} (#pi^{+} #pi^{-}) GeV^{2}");
  dataHist->GetXaxis()->SetTitle("M^{2} (#pi^{-} #pi^{0}) GeV^{2}");
  dataHist->SetContour(99);
  dataHist->Draw("COLZ");

  // normalization
  //dataHist->Scale(1/dataHist->GetEntries());
  //gPad->SetLogz(); // new!

  c->Print(outFile1);
  
  /*** The cuts: pip pim vs pip pi0 ***/

  // box
  Double_t sum13 = kMpi + kMpi0;
  Double_t difP2 = kMomega - kMpi;
  
  TCut cutLeft2   = Form("pippi0M > %f", sum13); // (mpip + mpi0)
  TCut cutRight2  = Form("pippi0M < %f", difP2); // (momega - mpim)
  TCut cutBottom2 = Form("pippimM > %f", sum12); // (mpip + mpim)
  TCut cutTop2    = Form("pippimM < %f", difP3); // (momega - mpi0)

  TCut cutBox2 = cutLeft2 && cutRight2 && cutBottom2 && cutTop2;

  // dalitz : (6) -> 12-2-1, (7) -> 12-3
  treeExtracted->SetAlias("Estar6", Form("(pippimM2 - %f + %f)/2/pippimM", kMpi*kMpi, kMpi*kMpi));
  treeExtracted->SetAlias("Estar7", Form("(%f - pippimM2 - %f)/2/pippimM", kMomega*kMomega, kMpi0*kMpi0));
  treeExtracted->SetAlias("Estar67", "Estar6 + Estar7");
  treeExtracted->SetAlias("Estar67Sq", "Estar67*Estar67");

  treeExtracted->SetAlias("Eroot6", Form("TMath::Sqrt(Estar6*Estar6 - %f)", kMpi*kMpi));
  treeExtracted->SetAlias("Eroot7", Form("TMath::Sqrt(Estar7*Estar7 - %f)", kMpi0*kMpi0));
  treeExtracted->SetAlias("Edif67", "Eroot6 - Eroot7");
  treeExtracted->SetAlias("Esum67", "Eroot6 + Eroot7");
  treeExtracted->SetAlias("Edif67Sq", "Edif67*Edif67");
  treeExtracted->SetAlias("Esum67Sq", "Esum67*Esum67");

  treeExtracted->SetAlias("Max67", "Estar67Sq - Edif67Sq");
  treeExtracted->SetAlias("Min67", "Estar67Sq - Esum67Sq");
  
  TCut cutDalitz67Up = "pippi0M2 < Max67";
  TCut cutDalitz67Down = "pippi0M2 > Min67";
  
  /*** Drawing: pip pim vs pip pi0 ***/
  
  // treeExtracted->Draw("m2pippim:m2pippi0>>data2(100, 0., 1., 100, 0., 1.)", cutAll && cutTargType && cutBox2 && cutDalitz67Up && cutDalitz67Down, "goff");
  treeExtracted->Draw("pippimM2:pippi0M2>>data2(100, 0., 1., 100, 0., 1.)", cutAll && cutTargType, "goff");
  dataHist2 = (TH2F *)gROOT->FindObject("data2");
  
  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
  c2->SetTickx(1);
  c2->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1, 0);

  dataHist2->SetTitle("#omega Dalitz plot for " + targetOption);
  dataHist2->GetYaxis()->SetTitle("M^{2} (#pi^{+} #pi^{-}) GeV^{2}");
  dataHist2->GetXaxis()->SetTitle("M^{2} (#pi^{+} #pi^{0}) GeV^{2}");
  dataHist2->SetContour(99);
  dataHist2->Draw("COLZ");

  // testing the cut
  drawBlackDashedHorizontalLine(0.48*0.48);
  drawBlackDashedHorizontalLine(0.51*0.51);
  
  // normalization
  //dataHist2->Scale(1/dataHist2->GetEntries());
  //gPad->SetLogz();

  c2->Print(outFile2); // output file
  
  /*** The cuts: pip pi0 vs pim pi0 ***/
  
  // box
  TCut cutLeft3   = Form("pimpi0M > %f", sum23); // (mpim + mpi0)
  TCut cutRight3  = Form("pimpi0M < %f", difP1); // (momega - mpip)
  TCut cutBottom3 = Form("pippi0M > %f", sum13); // (mpip + mpi0)
  TCut cutTop3    = Form("pippi0M < %f", difP2); // (momega - mpim)

  TCut cutBox3 = cutLeft3 && cutRight3 && cutBottom3 && cutTop3;

  // dalitz : (4) -> 13-1-3, (5) -> 13-2
  treeExtracted->SetAlias("Estar4", Form("(pippi0M2 - %f + %f)/2/pippi0M", kMpi*kMpi, kMpi0*kMpi0));
  treeExtracted->SetAlias("Estar5", Form("(%f - pippi0M2 - %f)/2/pippi0M", kMomega*kMomega, kMpi*kMpi));
  treeExtracted->SetAlias("Estar45", "Estar4 + Estar5");
  treeExtracted->SetAlias("Estar45Sq", "Estar45*Estar45");

  treeExtracted->SetAlias("Eroot4", Form("TMath::Sqrt(Estar4*Estar4 - %f)", kMpi0*kMpi0));
  treeExtracted->SetAlias("Eroot5", Form("TMath::Sqrt(Estar5*Estar5 - %f)", kMpi*kMpi));
  treeExtracted->SetAlias("Edif45", "Eroot4 - Eroot5");
  treeExtracted->SetAlias("Esum45", "Eroot4 + Eroot5");
  treeExtracted->SetAlias("Edif45Sq", "Edif45*Edif45");
  treeExtracted->SetAlias("Esum45Sq", "Esum45*Esum45");

  treeExtracted->SetAlias("Max45", "Estar45Sq - Edif45Sq");
  treeExtracted->SetAlias("Min45", "Estar45Sq - Esum45Sq");
  
  TCut cutDalitz45Up = "pimpi0M2 < Max45";
  TCut cutDalitz45Down = "pimpi0M2 > Min45";
  
  /*** Drawing: pip pi0 vs pim pi0 ***/
  
  // treeExtracted->Draw("m2pippi0:m2pimpi0>>data3(100, 0., 1., 100, 0., 1.)", cutAll && cutTargType && cutBox3 && cutDalitz45Up && cutDalitz45Down, "goff");
  treeExtracted->Draw("pippi0M2:pimpi0M2>>data3(100, 0., 1., 100, 0., 1.)", cutAll && cutTargType, "goff");
  dataHist3 = (TH2F *)gROOT->FindObject("data3");
  
  TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
  c3->SetTickx(1);
  c3->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1, 0);

  dataHist3->SetTitle("#omega Dalitz plot for " + targetOption);
  dataHist3->GetYaxis()->SetTitle("M^{2} (#pi^{+} #pi^{0}) GeV^{2}");
  dataHist3->GetXaxis()->SetTitle("M^{2} (#pi^{-} #pi^{0}) GeV^{2}");
  dataHist3->SetContour(99);
  dataHist3->Draw("COLZ");

  // normalization
  //dataHist3->Scale(1/dataHist3->GetEntries());
  //gPad->SetLogz();

  c3->Print(outFile3); // output file
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./DalitzPlots -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./DalitzPlots -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "DalitzPlots program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./DalitzPlots -[options] -[more options]" << std::endl;
  std::cout << "  h           : prints help and exit program" << std::endl;
  std::cout << "  t[target]   : select target: D | C | Fe | Pb" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
    // for targets
    if (targetOption == "D") {
      cutTargType = "TargType == 1";
      inputFile1 = dataDir + "/C/comb_C-thickD2.root";
      inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
      inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";
    } else if (targetOption == "C") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/C/comb_C-thickD2.root";
    } else if (targetOption == "Fe") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Fe/comb_Fe-thickD2.root";
    } else if (targetOption == "Pb") {
      cutTargType = "TargType == 2";
      inputFile1 = dataDir + "/Pb/comb_Pb-thinD2.root";
    }
    // out
    outFile1 = outDir + "/dalitz1-" + targetOption + ".png";
    outFile2 = outDir + "/dalitz2-" + targetOption + ".png";
    outFile3 = outDir + "/dalitz3-" + targetOption + ".png";
}

void printOptions() {
  std::cout << "Executing DalitzPlots program. The chosen options are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

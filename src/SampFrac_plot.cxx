/**************************************/
/* SampFrac_plot.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// stage 2: plot 2D spectrum without any sampling fraction cut

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/SampFrac";

// options
TString setOption;
TString targetOption;

TString treeFile;
TString plotFile;

int main(int argc, char **argv) {

  /*** Parse Command Line ***/
  
  if (argc != 3) {
    std::cout << "Two arguments <set> <option> are required." << std::endl;
    exit(0);
  } else {
    setOption    = argv[1];
    targetOption = argv[2];
    // filenames
    treeFile = outDir + "/samp-frac_" + setOption + "-" + targetOption + ".root";
    plotFile = outDir + "/samp-frac-plot_" + setOption + "-" + targetOption + ".png";
  }
  
  // just in case
  system("mkdir -p " + outDir);
    
  /*** Histograms ***/
  
  // color stuff, smoran
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

  // input tree
  TChain *tElectrons = new TChain();
  tElectrons->Add(treeFile + "/ntuple_e");

  TH2F *theHist;
  tElectrons->Draw("Etot/P:P>>hist(100, 0., 5, 100, 0.1, 0.4)", "", "goff");
  theHist = (TH2F *)gROOT->FindObject("hist");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->SetTickx(1);
  c->SetTicky(1);
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(NCont); // colors, smoran
  
  theHist->SetTitle("Sampling Fraction");
  theHist->GetYaxis()->SetTitle("Etot/P");
  theHist->GetXaxis()->SetTitle("P");
  theHist->GetYaxis()->CenterTitle();
  theHist->GetXaxis()->CenterTitle();
  theHist->SetContour(99);
  theHist->Draw("COLZ");
  
  c->Print(plotFile); // output file
  
  return 0;
}

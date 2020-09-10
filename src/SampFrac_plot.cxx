/**************************************/
/* SampFrac_plot.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

#include "TClasTool.h"
#include "TIdentificator.h"

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/SampFrac";
TString inputFile;

inline int parseCommandLine(int argc, char* argv[]);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  
  // just in case
  system("mkdir -p " + outDir);

  TString plotFile = outDir + "/hola.png";
  
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");  
  input->Add(inputFile);

  TString varListElectrons = "P:Etot:Ein:Eout";
  Float_t varElectrons[4];
  
  TNtuple *tElectrons = new TNtuple("ntuple_e", "All electrons", varListElectrons);
  
  TIdentificator *t = new TIdentificator(input);

  Int_t nEvents = (Int_t) input->GetEntries();

  // jumps to first readable event, mandatory!
  input->Next();
  
  // loop around events
  for (Int_t k = 0; k < nEvents; k++) {

    // update electrons' UVW vector
    TVector3 *ECxyz_e = new TVector3(t->XEC(0), t->YEC(0), t->ZEC(0));
    TVector3 *ECuvw_e = t->XYZToUVW(ECxyz_e);
    
    // electron condition without any sampling fraction cut, assuming electron is in row 0  
    if (t->Status(0) > 0 &&
	t->DCStatus(0) > 0 &&
	t->SCStatus(0) == 33 &&
	t->Charge(0) == -1 &&
	t->Nphe(0) > (t->Sector(0)==0 || t->Sector(0)==1)*25 + (t->Sector(0)==2)*26 + (t->Sector(0)==3)*21 + (t->Sector(0)==4 || t->Sector(0)==5)*28 &&
	t->Momentum(0) > 0.64 &&
	t->Ein(0) > 0.06 &&
	t->Eout(0) > 0 &&
	(t->TimeEC(0) - t->TimeSC(0) - 0.7) > -5*0.35 &&
	(t->TimeEC(0) - t->TimeSC(0) - 0.7) < 5*0.35 &&
	ECuvw_e->X() > 40 &&
	ECuvw_e->X() < 400 &&
	ECuvw_e->Y() >= 0 &&
	ECuvw_e->Y() < 360 &&
	ECuvw_e->Z() >= 0 &&
	ECuvw_e->Z() < 390 &&
	t->FidCheckCut(0)) {

      varElectrons[0] = t->Momentum(0,0);
      varElectrons[1] = t->Etot(0);
      varElectrons[2] = t->Ein(0);
      varElectrons[3] = t->Eout(0);
      
      tElectrons->Fill(varElectrons);
    }

    // next event!!
    input->Next();
  }
  
  std::cout << "Job finished!" << std::endl;

  /*** Histograms ***/
  
  // color stuff, smoran
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  
  TH2F *theHist;
  tElectrons->Draw("Etot/P:P>>hist(100, 0., 5, 100, 0.1, 0.4)", "", "goff");
  theHist = (TH2F *)gROOT->FindObject("hist");
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1366, 769);
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

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./SampFrac_plot -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "I:")) != -1)
    switch (c) {
    case 'I': inputFile = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./SampFrac_plot -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

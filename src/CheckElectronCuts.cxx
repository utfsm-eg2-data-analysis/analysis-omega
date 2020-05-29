/***************************************/
/*  CheckElectronCuts.cxx              */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// Checking the electrons' EC-SC coincidence time cut on data
// UPDATE:
// - added input/output options
// - added all other cuts
// PENDING:
// - add target option

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckElectronCut";
TString outFile;

TString inputFile;
// TString inputFile = rawDataDir_utfsm + "/clas_42011_00.pass2.root"; // _*.pass2.root
TString textFile;

TString targetOption;
TString cutOption;

TString outTitle = "Electrons EC SC coincidence time cut";

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();
  
  // dir structure, just in case
  system("mkdir -p " + outDir);

  // define output file
  TFile *rootFile = new TFile(outFile, "RECREATE", outTitle); // output file
  
  /*** Reading file ***/
  
  std::cout << "Reading " << textFile << " ..." << std::endl;
  std::ifstream inFile(textFile);
  
  TString rn;
  while (inFile >> rn) {
    
    std::cout << "rn = " << rn << std::endl;
    // inputFile = "/home/borquez/Downloads/clas_" + rn + "_*.pass2.root"; // _*.pass2.root (HP)
    inputFile = rawDataDir_utfsm + "/clas_" + rn + "_*.pass2.root"; // (utfsm cluster)
        
    // define histogram and value
    TH1F *theHist_final = new TH1F("tECtSC_" + rn, "Electrons (t_{EC} - t_{SC}) distribution", 250, -5., 5.);
  
    // init ClasTool
    TClasTool *input = new TClasTool();
    input->InitDSTReader("ROOTDSTR");
    input->Add(inputFile);
    
    // define TIdentificator
    TIdentificator *t = new TIdentificator(input);
    Long_t nEntries = (Long_t) input->GetEntries();
    
    // jump to first event!
    input->Next();
    
    // define number of rows
    Int_t number_dc = input->GetNRows("DCPB");
    Int_t number_cc = input->GetNRows("CCPB");
    Int_t number_sc = input->GetNRows("SCPB");
    Int_t number_ec = input->GetNRows("ECPB");
    Int_t number_ev = input->GetNRows("EVNT");
    
    // loop around events
    for (Int_t n = 0; n < nEntries; n++) {
      
      // update number of rows
      number_dc = input->GetNRows("DCPB");
      number_cc = input->GetNRows("CCPB");
      number_sc = input->GetNRows("SCPB");
      number_ec = input->GetNRows("ECPB");
      number_ev = input->GetNRows("EVNT");
      
      // loop around rows
      for (Int_t k = 0; k < number_ev; k++) {
	
	// update electrons' UVW vector
	TVector3 *ECxyz = new TVector3(t->XEC(k), t->YEC(k), t->ZEC(k));
	TVector3 *ECuvw = t->XYZToUVW(ECxyz);
	
	Bool_t statusCuts = t->Status(k) > 0 && t->Status(k) < 100 && t->StatCC(k) > 0 && t->StatSC(k) > 0 && t->StatDC(k) > 0 && t->StatEC(k) > 0 && t->DCStatus(k) > 0 && t->SCStatus(k) == 33;
	Bool_t numberCuts = number_cc != 0 && number_ec != 0 && number_sc != 0;
	Bool_t condition = t->Charge(k) == -1 &&
	  (t->Nphe(k) > (t->Sector(k)==0 || t->Sector(k)==1)*25 + (t->Sector(k)==2)*26 + (t->Sector(k)==3)*21 + (t->Sector(k)==4 || t->Sector(k)==5)*28) &&
	  t->Momentum(k) > 0.64 &&
	  t->Ein(k) > 0.06 &&
	  t->SampFracCheck(targetOption) &&
	  (t->Etot(k) / 0.27 / 1.15 + 0.4 > t->Momentum(k)) &&
	  (t->Etot(k) / 0.27 / 1.15 - 0.2 < t->Momentum(k)) &&
	  (t->Ein(k) + t->Eout(k) > 0.8 * 0.27 * t->Momentum(k)) &&
	  (t->Ein(k) + t->Eout(k) < 1.2 * 0.27 * t->Momentum(k)) &&
	  t->Eout(k) > 0 &&
	  ECuvw->X() > 40 && ECuvw->X() < 400 && ECuvw->Y() >= 0 && ECuvw->Y() < 360 && ECuvw->Z() >= 0 && ECuvw->Z() < 390;
	
	// fill histograms
	if (condition) theHist_final->Fill(t->TimeEC(k) - t->TimeSC(k)); // mike
      } // end of loop in rows
      
      // jump to next event
      input->Next();
    } // end of loop in events
    
    theHist_final->GetXaxis()->SetTitle("(ns)");
    theHist_final->SetLineColor(kGreen+2);
    theHist_final->SetLineWidth(3);
    
    /*** Drawing ***/
    
    // TCanvas *c = new TCanvas("c", "c", 1000, 1000);
    gStyle->SetOptStat("emr");
    
    // draw hist
    theHist_final->Draw("HIST"); // mike's suggestion
    // drawVerticalLine(theHist_final->GetMean(), kGreen+2, "dash");
    
    // save plot? nah
    // c->Write();
    
    // write all present objects into root file
    rootFile->Write();
  } // end of reading text file

  // stop reading text file and close root file
  inFile.close();
  rootFile->Close();
  
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckElectronCuts -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckElectronCuts -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "CheckElectronCuts program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckElectronCuts -h" << std::endl;
  std::cout << "  prints help and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CutFlow -t[target]" << std::endl;
  std::cout << "  selects target: C, Fe, Pb" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing CheckElectronCuts program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // targets
  if (targetOption == "C") {
    textFile = proDir + "/include/C-thickD2rn.txt";
  } else if (targetOption == "Fe") {
    textFile = proDir + "/include/Fe-thickD2rn.txt";    
  } else if (targetOption == "Pb") {
    textFile = proDir + "/include/Pb-thinD2rn.txt";
  }
  // regardless of the cut option
  outFile = outDir + "/cec-" + targetOption + ".root";  
}


/*** Previous time ***/

/*
  TH1F *theHist = new TH1F("analyser", "Electrons' EC SC coincidence time cut - Analyser", 150, -3, 3);
  TH1F *theHist_b = new TH1F("taya", "Electrons' EC SC coincidence time cut - Taya's approx.", 150, -3, 3);
  TH1F *theHist_b2 = new TH1F("taya2", "Electrons' EC SC coincidence time cut - Taya's Analysis Note", 150, -3, 3);
  TH1F *theHist_c = new TH1F("mike", "Electrons' EC SC coincidence time cut - Mike's suggestion", 150, -3, 3);

  TH1F *theHist_d = new TH1F("centering-factor", "title", 150, 0., 1.);
*/
/*
  std::cout << "./CheckElectronCuts -C[cut]" << std::endl;
  std::cout << "  selects target: mike, taya, taya2, hayk" << std::endl;
  std::cout << std::endl;

  if (cutOption == "hayk") {
    theHist->Draw("HIST"); // analyser
    drawVerticalLine(5*0.35, kBlack, "dash");
    drawVerticalLine(theHist->GetMean(), kBlack, "cont");
  } else if (cutOption == "taya") {
    theHist_b->Draw("HIST"); // taya's approx.
    drawVerticalLine(5*0.35, kBlue, "dash");
    drawVerticalLine(-5*0.35, kBlue, "dash");
    drawVerticalLine(theHist_b->GetMean(), kBlue, "cont");
  } else if (cutOption == "taya2") {
    theHist_b2->Draw("HIST"); // taya's literal
    drawVerticalLine(5*0.35, kRed);
    drawVerticalLine(-5*0.35, kRed);
    drawVerticalLine(theHist_b2->GetMean(), kRed, "cont");
  } else if (cutOption == "mike") {
  }


  theHist->GetXaxis()->SetTitle("(ns)");
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);

  theHist_b->GetXaxis()->SetTitle("(ns)");
  theHist_b->SetLineColor(kBlue);
  theHist_b->SetLineWidth(3);

  theHist_b2->GetXaxis()->SetTitle("(ns)");
  theHist_b2->SetLineColor(kRed);
  theHist_b2->SetLineWidth(3);
*/
/*
theHist->Fill(t->TimeEC(k) - t->TimeSC(k) - (t->PathEC(k) - t->PathSC(k))/30.);      // analyser
	theHist_b->Fill(t->TimeEC(k) - t->TimeSC(k) - 0.7);                                  // taya's approx.
	theHist_b2->Fill(t->TimeEC(k) - (t->TimeSC(k) - (t->PathEC(k) - t->PathSC(k))/30.)); // taya's literal

	theHist_d->Fill((t->PathEC(k) - t->PathSC(k))/30.);                                  // centering-factor
*/

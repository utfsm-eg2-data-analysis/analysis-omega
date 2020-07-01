/***************************************/
/*  CSC_flow.cxx                       */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// Program that plots the effect of different status cuts, for different particles.
// UPDATE:
// - now it supports particle options: electrons and photon
// PENDING:
// - add pip and pim
// - properly add target option!
// - add the rn list in the analysisConfig.h file
// FUTURE:
// - see effect on simulations

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

TString outDir = proDir + "/out/CheckStatusCut";
TString plotFile;

Int_t partOption;
TString targetOption;

TString partName;
TString partTitle;
Int_t nCuts;

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

  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");

  input->Add("/home/borquez/Downloads/clas_42011_00.pass2.root"); // _*.pass2
  
  // define TIdentificator
  TIdentificator *t = new TIdentificator(input);
  Int_t nEvents = (Int_t) input->GetEntries(); // get total number of events

  TCut statusCuts_electrons = "StatusEl > 0 && StatusEl < 100 && StatCCEl > 0 && StatSCEl > 0 && StatDCEl > 0 && StatECEl > 0 && DCStatusEl > 0 && SCStatusEl == 33";

  TCut statusCuts_pip = "Status[2] > 0 && Status[2] < 100 && StatDC[2] > 0 && DCStatus[2] > 0";
  TCut statusCuts_pip_le = "P_corr[2] < 2.7 && StatSC[2] > 0";
  TCut statusCuts_pip_he = "P_corr[2] >= 2.7 && Nphe[2] > 25 && StatCC[2] > 0 && Chi2CC[2] < 5./57.3";

  TCut statusCuts_pim = "Status[3] > 0 && Status[3] < 100 && StatDC[3] > 0 && DCStatus[3] > 0";
  TCut statusCuts_pim_le = "P_corr[3] <= 2.5 && !(StatCC[3] > 0 && Nphe[3] > 25)";
  TCut statusCuts_pim_he = "P_corr[3] > 2.5";
  
  // define electron counters
  Int_t c00 = 0; // no cut
  Int_t c01 = 0; // status > 0
  Int_t c02 = 0; // status < 100
  Int_t c03 = 0; // statcc > 0
  Int_t c04 = 0; // statsc > 0
  Int_t c05 = 0; // statdc >0
  Int_t c06 = 0; // statec > 0
  Int_t c07 = 0; // dcstatus > 0
  Int_t c08 = 0; // scstatus = 33

  // define pi+ counters
  Int_t p00 = 0; // no cut
  Int_t p01 = 0; // status > 0
  Int_t p02 = 0; // status < 100
  Int_t p03 = 0; // statdc > 0
  Int_t p04 = 0; // dcstatus > 0
  Int_t p05 = 0; // he pi+: statsc > 0
  Int_t p06 = 0; // le pi+: nphe > 25
  Int_t p07 = 0; // le pi+: statcc > 25
  Int_t p08 = 0; // le pi+: chi2cc < 5./57.3
    
  // define pi- counters
  Int_t m00 = 0; // no cut
  Int_t m01 = 0; // status > 0
  Int_t m02 = 0; // status < 100
  Int_t m03 = 0; // statdc > 0
  Int_t m04 = 0; // dcstatus > 0
  Int_t m05 = 0; // le pi-: !(statcc > 0 && nphe > 25)
  Int_t m06 = 0; // he pi-
  
  // jump to first event, mandatory!
  input->Next();

  // define number of rows
  Int_t number_dc = input->GetNRows("DCPB");
  Int_t number_cc = input->GetNRows("CCPB");
  Int_t number_sc = input->GetNRows("SCPB");
  Int_t number_ec = input->GetNRows("ECPB");
  Int_t number_ev = input->GetNRows("EVNT");
  
  // loop around events
  for (Int_t n = 0; n < nEvents; n++) { // nEvents // 500

    // update number of rows
    number_dc = input->GetNRows("DCPB");
    number_cc = input->GetNRows("CCPB");
    number_sc = input->GetNRows("SCPB");
    number_ec = input->GetNRows("ECPB");
    number_ev = input->GetNRows("EVNT");
    
    if (partName == "electron") {
      if (number_ev > 0) {
	c00++;
	if (t->Status(0) > 0) {
	  c01++;
	  if (t->Status(0) < 100) {
	    c02++;
	    if (t->StatCC(0) > 0) {
	      c03++;
	      if (t->StatSC(0) > 0) {
		c04++;
		if (t->StatDC(0) > 0) {
		  c05++;
		  if (t->StatEC(0) > 0) {
		    c06++;
		    if (t->DCStatus(0) > 0) {
		      c07++;
		      if (t->SCStatus(0) == 33) {
			c08++;
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
      
    }

    input->Next();
  }
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  // define histogram and value
  TH1F *theHist = new TH1F("cutflow-" + partName, "Status Cuts Chart - " + partTitle + " id", nCuts, 0, nCuts);
  
  // fill histograms
  if (partName == "electron") {
    theHist->SetBinContent(1, c00);
    theHist->SetBinContent(2, c01);
    theHist->SetBinContent(3, c02);
    theHist->SetBinContent(4, c03);
    theHist->SetBinContent(5, c04);
    theHist->SetBinContent(6, c05);
    theHist->SetBinContent(7, c06);
    theHist->SetBinContent(8, c07);
    theHist->SetBinContent(9, c08); // nCuts = 9
  } else if (partName == "pi+") {
    theHist->SetBinContent(1, p00);
    theHist->SetBinContent(2, p01);
    theHist->SetBinContent(3, p02);
    theHist->SetBinContent(4, p03);
    theHist->SetBinContent(5, p04);
    theHist->SetBinContent(6, p05);
    theHist->SetBinContent(7, p06);
    theHist->SetBinContent(8, p07);
    theHist->SetBinContent(9, p08); // nCuts = 9
  } else if (partName == "pi-") {
    theHist->SetBinContent(1, m00);
    theHist->SetBinContent(2, m01);
    theHist->SetBinContent(3, m02);
    theHist->SetBinContent(4, m03);
    theHist->SetBinContent(5, m04);
    theHist->SetBinContent(6, m05);
    theHist->SetBinContent(7, m06); // nCuts = 7
  }

  theHist->GetXaxis()->CenterLabels();
  theHist->GetXaxis()->SetNdivisions(200 + nCuts, kFALSE);

  gPad->SetGridx(1);
  
  theHist->GetXaxis()->SetTitle("Cut id");
  theHist->SetLineColor(kBlack);
  theHist->SetLineWidth(3);
    
  theHist->Draw("HIST");
  
  c->Print(plotFile); // output file
    
  return 0;
}

/*** Functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./CheckStatusCuts_flow -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:p:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'p': partOption = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CheckStatusCuts_flow -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "CheckStatusCuts_flow program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_flow -h" << std::endl;
  std::cout << "  prints help and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_flow -t[target]" << std::endl;
  std::cout << "  selects target: C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./CheckStatusCuts_flow -p[pid]" << std::endl;
  std::cout << "  selects particle by its pid number" << std::endl;
  std::cout << "    electron =   11" << std::endl;
  std::cout << "    pi+      =  211" << std::endl;
  std::cout << "    pi-      = -211" << std::endl;
  std::cout << std::endl;  
}

void printOptions() {
  std::cout << "Executing CheckStatusCuts_flow program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  partOption   = " << partOption << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for particle option
  if (partOption == 11) {
    nCuts = 9;
    partTitle = "Electrons'";
  } else if (partOption == 211) {
    nCuts = 9;
    partTitle = "#pi^{+}";
  } else if (partOption == -211) {
    nCuts = 7;
    partTitle = "#pi^{-}";
  }
  partName = particleName(partOption); // defined in analysisConfig.h
  // for target option
  
  // names
  plotFile = outDir + "/csc-flow-" + targetOption + "-" + partName + ".png";
}

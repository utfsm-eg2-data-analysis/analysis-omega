/***************************************/
/*  CutFlow.cxx                        */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// Program that plots the effect of different Analyser cuts, for different particles.
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

TString outDir = proDir + "/out/CutFlow";
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
  Long_t nEntries = (Long_t) input->GetEntries(); // get total number of events
      
  // define electron counters
  Int_t c00 = 0; // no cut
  Int_t c01 = 0; // number_xx cut
  Int_t c02 = 0; // all status
  Int_t c03 = 0; // charge
  Int_t c04 = 0; // CC Nphe
  Int_t c05 = 0; // P > 0.64
  Int_t c06 = 0; // Eout > 0 and Ein > 0.06
  Int_t c07 = 0; // SC EC time
  Int_t c08 = 0; // sampling fraction cut
  Int_t c09 = 0; // EC fid cuts
  Int_t c10 = 0; // DC fid cuts
  Int_t c11 = 0; // sampling fraction "band"

  // define photon counters
  Int_t g00 = 0; // no cut, number_ev > 1
  Int_t g01 = 0; // charge
  Int_t g02 = 0; // speed of light
  Int_t g03 = 0; // min energy
  Int_t g04 = 0; // EC fid cuts
  
  // start TIdentificator
  input->Next();

  // define number of rows
  Int_t number_dc = input->GetNRows("DCPB");
  Int_t number_cc = input->GetNRows("CCPB");
  Int_t number_sc = input->GetNRows("SCPB");
  Int_t number_ec = input->GetNRows("ECPB");
  Int_t number_ev = input->GetNRows("EVNT");
  
  // loop around events
  for (Int_t n = 0; n < 100; n++) { // nEntries

    // update number of rows
    number_dc = input->GetNRows("DCPB");
    number_cc = input->GetNRows("CCPB");
    number_sc = input->GetNRows("SCPB");
    number_ec = input->GetNRows("ECPB");
    number_ev = input->GetNRows("EVNT");
    
    if (partName == "electron") {
      if (number_ev > 0) {
	c00++;
	
	// update electrons' UVW vector
	TVector3 *ECxyz_e = new TVector3(t->XEC(0), t->YEC(0), t->ZEC(0));
	TVector3 *ECuvw_e = t->XYZToUVW(ECxyz_e);
	
	if (number_dc != 0 && number_cc != 0 &&
	    number_ec != 0 && number_sc != 0) {
	  c01++;
	  if (t->StatCC(0) > 0 && t->StatSC(0) > 0 && t->StatDC(0) > 0 && t->StatEC(0) > 0 &&
	      t->DCStatus(0) > 0 && t->SCStatus(0) == 33) {
	    c02++;
	    if (t->Charge(0) == -1) {
	      c03++;
	      if (t->Nphe(0) > (t->Sector(0)==0 || t->Sector(0)==1)*25 + (t->Sector(0)==2)*26 + (t->Sector(0)==3)*21 + (t->Sector(0)==4 || t->Sector(0)==5)*28) {
		c04++;
		if (t->Momentum(0) > 0.64) {
		  c05++;
		  if (t->Ein(0) > 0.06 && t->Eout(0) > 0) {
		    c06++;
		    if (t->TimeEC(0) - t->TimeSC(0) - 0.7 > -5*0.35 &&
			t->TimeEC(0) - t->TimeSC(0) - 0.7 < 5*0.35) {
		      c07++;
		      if (t->SampFracCheck(targetOption)) {
			c08++;
			if (ECuvw_e->X() > 40 && ECuvw_e->X() < 400 &&
			    ECuvw_e->Y() >= 0 && ECuvw_e->Y() < 360 &&
			    ECuvw_e->Z() >= 0 && ECuvw_e->Z() < 390) {
			  c09++;
			  if (t->FidCheckCut()) {
			    c10++;
			    if (t->Etot(0) / 0.27 / 1.15 + 0.4 > t->Momentum(0) &&
				t->Etot(0) / 0.27 / 1.15 - 0.2 < t->Momentum(0) &&
				t->Ein(0) + t->Eout(0) > 0.8 * 0.27 * t->Momentum(0) &&
				t->Ein(0) + t->Eout(0) < 1.2 * 0.27 * t->Momentum(0)) {
			      c11++;
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
	}	
      }
      
    } else if (partName == "gamma") { // end of partname condition

      // k > 0, don't forget that!
      for (Int_t k = 1; k < number_ev; k++) { // IMPORTANT: this condition is equivalent to the number_dc != 0 cut!
	g00++;
	
	// photons
	TVector3 *ECxyz = new TVector3(t->XEC(k), t->YEC(k), t->ZEC(k));
	TVector3 *ECuvw = t->XYZToUVW(ECxyz);
	
	if (t->Charge(k) == 0) {
	  g01++;
	  if (t->PathEC(k)/(t->Betta(k)*30) - t->PathEC(k)/30 > -2.2 &&
	      t->PathEC(k)/(t->Betta(k)*30) - t->PathEC(k)/30 < 1.3) {
	    g02++;
	    if (TMath::Max(t->Etot(k), t->Ein(k)+t->Eout(k))/0.272 > 0.1) {
	      g03++;      
	      if (ECuvw->X() > 40 && ECuvw->X() < 410 &&
		  ECuvw->Y() >= 0 && ECuvw->Y() < 370 &&
		  ECuvw->Z() >= 0 && ECuvw->Z() < 410) {
		g04++;
	      }
	    }
	  }
	}
      }
      
    } else if (partName == "pip") { // end of partname condition



    } else if (partName == "pim") { // end of partname condition


      
    } // end of partname condition

    input->Next();
  }
  
  /*** Drawing ***/
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  // define histogram and value
  TH1F *theHist = new TH1F("cutflow-" + partName, "Analyser Cuts Flow - " + partTitle + " id", nCuts, 0, nCuts);
  
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
    theHist->SetBinContent(9, c08);
    theHist->SetBinContent(10, c09);
    theHist->SetBinContent(11, c10);
    theHist->SetBinContent(12, c11); // nCuts = 12
  } else if (partName == "gamma") {
    theHist->SetBinContent(1, g00);
    theHist->SetBinContent(2, g01);
    theHist->SetBinContent(3, g02);
    theHist->SetBinContent(4, g03);
    theHist->SetBinContent(5, g04); // nCuts = 5
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
    std::cerr << "Empty command line. Execute ./CutFlow -h to print usage." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:p:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'p': partOption = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./CutFlow -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "CutFlow program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./CutFlow -h" << std::endl;
  std::cout << "  prints help and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./CutFlow -t[target]" << std::endl;
  std::cout << "  selects target: C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./CutFlow -p[pid]" << std::endl;
  std::cout << "  selects particle by its pid number" << std::endl;
  std::cout << "  electron =   11" << std::endl;
  std::cout << "  gamma    =   22" << std::endl;
  std::cout << "  pi+      =  211" << std::endl;
  std::cout << "  pi-      = -211" << std::endl;
  std::cout << std::endl;  
}

void printOptions() {
  std::cout << "Executing CutFlow program. The chosen parameters are:" << std::endl;
  std::cout << "  targetOption = " << targetOption << std::endl;
  std::cout << "  partOption   = " << partOption << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // for particle option
  if (partOption == 11) {
    nCuts = 12;
    partTitle = "Electrons'";
  } else if (partOption == 22) {
    nCuts = 5;
    partTitle = "Photons'";
  } else if (partOption == 211) {
    nCuts = 0;
    partTitle = "#pi^{+}";
  } else if (partOption == -211) {
    nCuts = 0;
    partTitle = "#pi^{-}";
  }
  partName = particleName(partOption); // defined in analysisConfig.h
  // for targets, nothig yet
  // names
  plotFile = outDir + "/cutflow-" + targetOption + "-" + partName + ".png";
}

/***************************************/
/*  GetSimpleTuple.cxx                 */
/*                                     */
/*  Original by Orlando Soto           */
/*  Modified by Andrés Bórquez         */
/*                                     */
/***************************************/

// UPDATE:
// - removed the infamous "mflag" from GetCategorization
// PENDING:
// - add all files of a data run number
// - add scale factor for the fcup values
// - do the momentum/angular matching for simulations

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

// options
Int_t   simFlag = 0;
TString targetOption;
TString setOption;
TString NjlabDir;
TString rnOption; // new!
TString nFile; // for raw data, don't know how to add it yet

TString outDir;
TString inputFile;

TString outFile;
TString NtupleName;
TString outTitle;

TString analyserOption;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printOptions();
void printUsage();

int main(int argc, char **argv) {
  
  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  system("mkdir -p " + outDir);

  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");
  input->Add(inputFile);
    
  /*** Beginning Faraday Cup studies ***/

  TChain *c = new TChain(); // fcup
  Double_t fcup = 0; // search for maximum in the run files
    
  // only for data
  if (!simFlag) {
    // add scaler branch
    c->Add(inputFile + "/SCALER");

    Int_t Ne = c->GetEntries();
    Double_t currentFC;
    
    // looping around tree entries
    for (Int_t i = 0; i < Ne; i++) {
      c->GetEntry(i);
      currentFC = c->GetLeaf("SC_TRGS.Fcup_g2")->GetValue();
      if (currentFC > fcup) fcup = currentFC;
    }
    printf("  fcup = %.0f", fcup);
    std::cout << std::endl;
  }

  delete c;
  
  /*** Pruning RAW data ***/

  // hadron variables
  TString varListHadrons = "TargType:Q2:Nu:Xb:W:SectorEl:ThetaPQ:PhiPQ:Zh:Pt:W2p:Xf:T:P:T4:deltaZ:E:Ee:Pe:Ect:Sct:Ecr:Scr:evnt:Px:Py:Pz:Xe:Ye:Ze:Xec:Yec:Zec:TEc:ECX:ECY:ECZ:Pex:Pey:Pez:Ein:Eout:Eine:Eoute:pid:Betta:vxh:vyh:vzh:fcup";
  if (simFlag) {
    varListHadrons += ":mc_TargType:mc_Q2:mc_Nu:mc_Xb:mc_W:mc_SectorEl:mc_ThetaPQ:mc_PhiPQ:mc_Zh:mc_Pt:mc_W2p:mc_Xf:mc_T:mc_P:mc_T4:mc_deltaZ:mc_E:mc_Ee:mc_Pe:mc_Ect:mc_Sct:mc_Ecr:mc_Scr:mc_evnt:mc_Px:mc_Py:mc_Pz:mc_Xe:mc_Ye:mc_Ze:mc_Xec:mc_Yec:mc_Zec:mc_TEc:mc_ECX:mc_ECY:mc_ECZ:mc_Pex:mc_Pey:mc_Pez:mc_Ein:mc_Eout:mc_Eine:mc_Eoute:mc_pid:mc_Betta:mc_vxh:mc_vyh:mc_vzh";
  }
  Int_t   NvarHadrons = varListHadrons.CountChar(':') + 1; // 50 for data; 99 for sim
  Float_t varHadrons[NvarHadrons];
  
  // electron variables
  TString varListElectrons = "Q2:W:Nu:vxec:vyec:vzec:vxe:vye:vze:Pex:Pey:Pez:event:TargType:sector:Xb:ECX:ECY:ECZ";
  if (simFlag) {
    varListElectrons += ":mc_Q2:mc_W:mc_Nu:mc_vxec:mc_vyec:mc_vzec:mc_vxe:mc_vye:mc_vze:mc_Pex:mc_Pey:mc_Pez:mc_event:mc_TargType:mc_sector:mc_Xb"; // no ECX, ECY, ECZ
  }
  Int_t   NvarElectrons = varListElectrons.CountChar(':') + 1; // 19 for data, 35 for sim
  Float_t varElectrons[NvarElectrons];

  // define TIdentificator
  TIdentificator *t = new TIdentificator(input);
  Long_t nEntries = (Long_t) input->GetEntries();
  
  // define file
  TFile *rootFile = new TFile(outFile, "RECREATE", outTitle); // output file
  
  // define tuples
  TNtuple *tHadrons   = new TNtuple(NtupleName, "Stable particles", varListHadrons);
  TNtuple *tElectrons = new TNtuple("ntuple_e", "All Electrons", varListElectrons);

  // define this vector
  TVector3 *vert;
  
  // start TIdentificator
  input->Next();

  // loop around events
  for (Int_t k = 0; k < nEntries; k++) {
    
    // reset electron values
    for (Int_t r = 0; r < NvarElectrons; r++) varElectrons[r] = -9999.;
    Int_t eflag = 0; // reconstructed has electron

    /*** FOR SIMULATIONS ***/
    
    // found electron in gsim!
    if (simFlag && t->Id(0,1) == 11) {

      varElectrons[19] = t->Q2(1);
      varElectrons[20] = t->W(1);
      varElectrons[21] = t->Nu(1);
      varElectrons[22] = 0; // vxec
      varElectrons[23] = 0; // vyec
      varElectrons[24] = 0; // vzec
      varElectrons[25] = t->X(0,1);
      varElectrons[26] = t->Y(0,1);
      varElectrons[27] = t->Z(0,1);
      varElectrons[28] = t->Px(0,1);
      varElectrons[29] = t->Py(0,1);
      varElectrons[30] = t->Pz(0,1);
      varElectrons[31] = k;
      varElectrons[32] = t->ElecVertTarg(1);
      varElectrons[33] = t->Sector(0,1);
      varElectrons[34] = t->Xb(1);

      // found electron in simrec!
      if (input->GetNRows("EVNT") > 0 && (t->GetCategorization(0, analyserOption.Data())) == "electron") {
	varElectrons[0] = t->Q2();
	varElectrons[1] = t->W();
	varElectrons[2] = t->Nu();
	vert = t->GetCorrectedVert();
	Float_t vxec = vert->X(); 
	Float_t vyec = vert->Y();
	Float_t vzec = vert->Z(); 
	varElectrons[3] = vxec; 
	varElectrons[4] = vyec; 
	varElectrons[5] = vzec;
	varElectrons[6] = t->X(0);
	varElectrons[7] = t->Y(0);
	varElectrons[8] = t->Z(0);
	varElectrons[9] = t->Px(0);
	varElectrons[10] = t->Py(0);
	varElectrons[11] = t->Pz(0);
	varElectrons[12] = k;
	varElectrons[13] = t->ElecVertTarg();
	varElectrons[14] = t->Sector(0);
	varElectrons[15] = t->Xb();
	varElectrons[16] = t->XEC(0);
	varElectrons[17] = t->YEC(0);
	varElectrons[18] = t->ZEC(0);	
	eflag = 1;
      }

      // fill!
      tElectrons->Fill(varElectrons);

      // loop in generated particles
      for (Int_t i = 1; i < input->GetNRows("GSIM"); i++) {

	// reset values
	for (Int_t r = 0; r < NvarHadrons; r++) varHadrons[r] = -9999.;
	Int_t gflag = 0; // generated row has hadron
	Int_t rflag = 0; // reconstructed row has hadron

	// hadron found in gsim!
      	if (t->Id(i,1) == 22 || t->Id(i,1) == -211 || t->Id(i,1) == 211) {
	  varHadrons[50] = t->ElecVertTarg(1); // mc_TargType
	  varHadrons[51] = t->Q2(1); // mc_Q2
	  varHadrons[52] = t->Nu(1); // mc_Nu
	  varHadrons[53] = t->Xb(1); // mc_Xb
	  varHadrons[54] = t->W(1); // mc_W
	  varHadrons[55] = t->Sector(0,1); // mc_Sector
	  varHadrons[56] = t->ThetaPQ(i,1);
	  varHadrons[57] = t->PhiPQ(i,1);
	  varHadrons[58] = t->Zh(i,1);
	  varHadrons[59] = TMath::Sqrt(t->Pt2(i,1));
	  varHadrons[60] = t->Mx2(i,1);
	  varHadrons[61] = t->Xf(i,1);
	  varHadrons[62] = t->T(i,1);
	  varHadrons[63] = t->Momentum(i,1);
	  varHadrons[64] = 0; //t -> TimeCorr4(0.139570,i);
	  varHadrons[65] = (t->Z(i,1)) - (t->Z(0,1));
	  varHadrons[66] = t->Momentum(i,1); //TMath::Max(t->Etot(i),t->Ein(i)+t->Eout(i));;
	  varHadrons[67] = TMath::Sqrt(t->Momentum(0,1)*t->Momentum(0,1) + kMe*kMe); //TMath::Max(t->Etot(0),t->Ein(0)+t->Eout(0));
	  varHadrons[68] = t->Momentum(0,1);
          varHadrons[69] = 0; //t->TimeEC(0);
          varHadrons[70] = 0; //t->TimeSC(0);
          varHadrons[71] = 0; //t->PathEC(0);
          varHadrons[72] = 0; //t->PathSC(0);
          varHadrons[73] = k;
          varHadrons[74] = t->Px(i,1);
          varHadrons[75] = t->Py(i,1);
          varHadrons[76] = t->Pz(i,1);
          varHadrons[77] = t->X(0,1);
          varHadrons[78] = t->Y(0,1);
          varHadrons[79] = t->Z(0,1);
          //vert = t->GetCorrectedVert();
          varHadrons[80] = t->X(0,1); //vert->X(); 
          varHadrons[81] = t->Y(0,1); //vert->Y(); 
          varHadrons[82] = t->Z(0,1); //vert->Z(); 
          varHadrons[83] = 0; //t->TimeEC(i);
          varHadrons[84] = 0; //t->XEC(i);
          varHadrons[85] = 0; //t->YEC(i);
          varHadrons[86] = 0; //t->ZEC(i);
          varHadrons[87] = t->Px(0,1);
          varHadrons[88] = t->Py(0,1);
          varHadrons[89] = t->Pz(0,1);
	  varHadrons[90] = 0;
	  varHadrons[91] = 0;
	  varHadrons[92] = 0;
	  varHadrons[93] = 0;
	  varHadrons[94] = t->Id(i,1);
	  varHadrons[95] = t->Betta(i,1);
          varHadrons[96] = t->X(i,1);
          varHadrons[97] = t->Y(i,1);
          varHadrons[98] = t->Z(i,1);
	  gflag = 1;
	}
    
	// there are reconstructed particles!
	if (eflag && i < input->GetNRows("EVNT")) {
	  TString category = t->GetCategorization(i, analyserOption.Data());
	  
	  // hadron in simrec found!
	  if (category == "gamma" || category == "pi-" || category == "high energy pion +" || category == "low energy pion +" || category == "s_electron") {
	    varHadrons[0] = t->ElecVertTarg(); // TargType
	    varHadrons[1] = t->Q2();           // Q2
	    varHadrons[2] = t->Nu();           // Nu
	    varHadrons[3] = t->Xb();           // Xb
	    varHadrons[4] = t->W();            // W
	    varHadrons[5] = t->Sector(0);      // SectorEl
	    varHadrons[6] = t->ThetaPQ(i);     // ThetaPQ
	    varHadrons[7] = t->PhiPQ(i);       // PhiPQ
	    varHadrons[8] = t->Zh(i);          // Zh
	    varHadrons[9] = TMath::Sqrt(t->Pt2(i)); // Pt
	    varHadrons[10] = t->Mx2(i);        // W2p
	    varHadrons[11] = t->Xf(i);         // Xf
	    varHadrons[12] = t->T(i);          // T
	    varHadrons[13] = t->Momentum(i);   // P
	    varHadrons[14] = t->TimeCorr4(0.139570,i); // T4, should be only for pions, not for gammas!
	    varHadrons[15] = (t->Z(i)) - (t->Z(0)); // deltaZ
	    varHadrons[16] = TMath::Max(t->Etot(i), t->Ein(i) + t->Eout(i)); // E
	    varHadrons[17] = TMath::Max(t->Etot(0), t->Ein(0) + t->Eout(0)); // Ee
	    varHadrons[18] = t->Momentum(0); // Pe
	    varHadrons[19] = t->TimeEC(0); // Ect (electron!)
	    varHadrons[20] = t->TimeSC(0); // Sct
	    varHadrons[21] = t->PathEC(0); // Ecr
	    varHadrons[22] = t->PathSC(0); // Scr
	    varHadrons[23] = k; // evnt
	    varHadrons[24] = t->Px(i); // Px
	    varHadrons[25] = t->Py(i); // Py
	    varHadrons[26] = t->Pz(i); // Pz
	    varHadrons[27] = t->X(0); // Xe
	    varHadrons[28] = t->Y(0); // Ye
	    varHadrons[29] = t->Z(0); // Ze
	    vert = t->GetCorrectedVert();
	    varHadrons[30] = vert->X(); // Xec
	    varHadrons[31] = vert->Y(); // Yec
	    varHadrons[32] = vert->Z(); // Zec
	    varHadrons[33] = t->TimeEC(i); // TEc (hadron!)
	    varHadrons[34] = t->XEC(i); // ECX
	    varHadrons[35] = t->YEC(i); // ECY
	    varHadrons[36] = t->ZEC(i); // ECZ
	    varHadrons[37] = t->Px(0); // Pex
	    varHadrons[38] = t->Py(0); // Pey
	    varHadrons[39] = t->Pz(0); // Pez
	    varHadrons[40] = t->Ein(i); // Ein
	    varHadrons[41] = t->Eout(i); // Eout
	    varHadrons[42] = t->Ein(0); // Eine
	    varHadrons[43] = t->Eout(0); // Eoute
	    varHadrons[44] = ((category == "gamma")?22:
			      ((category == "pi-")?-211:
			       (( category == "high energy pion +" || category == "low energy pion +")?211:
				((category == "s_electron")?11:-11)))); // pid
	    varHadrons[45] = t->Betta(i); // Betta
	    varHadrons[46] = t->X(i); // vxh
	    varHadrons[47] = t->Y(i); // vyh
	    varHadrons[48] = t->Z(i); // vzh
	    varHadrons[49] = fcup; // fcup
	    rflag = 1;
	  }
	} // end of gsim hadron
	
	// fill
	if (gflag || rflag) tHadrons->Fill(varHadrons);
	
      } // end of loop in gsim particles
      
    } // end of "electron found in gsim" condition
    
    /*** FOR DATA ***/
    
    // found electron
    if (!simFlag && input->GetNRows("EVNT") > 0 && t->GetCategorization(0, analyserOption.Data()) == "electron") {	
      varElectrons[0] = t->Q2();
      varElectrons[1] = t->W();
      varElectrons[2] = t->Nu();
      vert = t->GetCorrectedVert();
      Float_t vxec = vert->X(); 
      Float_t vyec = vert->Y();
      Float_t vzec = vert->Z(); 
      varElectrons[3] = vxec; 
      varElectrons[4] = vyec; 
      varElectrons[5] = vzec;
      varElectrons[6] = t->X(0);
      varElectrons[7] = t->Y(0);
      varElectrons[8] = t->Z(0);
      varElectrons[9] = t->Px(0);
      varElectrons[10] = t->Py(0);
      varElectrons[11] = t->Pz(0);
      varElectrons[12] = k;
      varElectrons[13] = t->ElecVertTarg();
      varElectrons[14] = t->Sector(0);
      varElectrons[15] = t->Xb();
      varElectrons[16] = t->XEC(0);
      varElectrons[17] = t->YEC(0);
      varElectrons[18] = t->ZEC(0);
      
      // fill
      tElectrons->Fill(varElectrons);      
      
      // loop in hadrons
      for (Int_t i = 1; i < input->GetNRows("EVNT"); i++) {
	TString category = t->GetCategorization(i, analyserOption.Data());

	// hadron found!
	if (category == "gamma" || category == "pi-" || category == "high energy pion +" || category == "low energy pion +" || category == "s_electron") {
	  varHadrons[0] = t->ElecVertTarg();
	  varHadrons[1] = t->Q2();
	  varHadrons[2] = t->Nu();
	  varHadrons[3] = t->Xb();
	  varHadrons[4] = t->W();
	  varHadrons[5] = t->Sector(0);
	  varHadrons[6] = t->ThetaPQ(i);
	  varHadrons[7] = t->PhiPQ(i);
	  varHadrons[8] = t->Zh(i);
	  varHadrons[9] = TMath::Sqrt(t->Pt2(i));
	  varHadrons[10] = t->Mx2(i);
	  varHadrons[11] = t->Xf(i);
	  varHadrons[12] = t->T(i);
	  varHadrons[13] = t->Momentum(i);
	  varHadrons[14] = t->TimeCorr4(0.139570,i);
	  varHadrons[15] = (t->Z(i)) - (t->Z(0));
	  varHadrons[16] = TMath::Max(t->Etot(i), t->Ein(i) + t->Eout(i));
	  varHadrons[17] = TMath::Max(t->Etot(0), t->Ein(0) + t->Eout(0));
	  varHadrons[18] = t->Momentum(0);
	  varHadrons[19] = t->TimeEC(0);
	  varHadrons[20] = t->TimeSC(0);
	  varHadrons[21] = t->PathEC(0);
	  varHadrons[22] = t->PathSC(0);
	  varHadrons[23] = k;
	  varHadrons[24] = t->Px(i);
	  varHadrons[25] = t->Py(i);
	  varHadrons[26] = t->Pz(i);
	  varHadrons[27] = t->X(0);
	  varHadrons[28] = t->Y(0);
	  varHadrons[29] = t->Z(0);
	  vert = t->GetCorrectedVert();
	  varHadrons[30] = vert->X(); 
	  varHadrons[31] = vert->Y(); 
	  varHadrons[32] = vert->Z(); 
	  varHadrons[33] = t->TimeEC(i);
	  varHadrons[34] = t->XEC(i);
	  varHadrons[35] = t->YEC(i);
	  varHadrons[36] = t->ZEC(i);
	  varHadrons[37] = t->Px(0);
	  varHadrons[38] = t->Py(0);
	  varHadrons[39] = t->Pz(0);
	  varHadrons[40] = t->Ein(i);
	  varHadrons[41] = t->Eout(i);
	  varHadrons[42] = t->Ein(0);
	  varHadrons[43] = t->Eout(0);
	  varHadrons[44] = ((category == "gamma")?22:
			    ((category == "pi-")?-211:
			     (( category == "high energy pion +" || category == "low energy pion +")?211:
			      ((category == "s_electron")?11:-11))));
	  varHadrons[45] = t->Betta(i);
	  varHadrons[46] = t->X(i);
	  varHadrons[47] = t->Y(i);
	  varHadrons[48] = t->Z(i);
	  varHadrons[49] = fcup; // fcup information, finally
	  
	  // fill
	  tHadrons->Fill(varHadrons);
	} // end of hadron found condition
	
      } // end of loop in hadrons
      
    } // end of "electron found in data" condition

    /*** NEXT EVENT! ***/
    
    input->Next();
  } // end of loop in events
  
  rootFile->Write();
  rootFile->Close();
  
  return 0;
}

inline int parseCommandLine(int argc, char* argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./bin/GetSimpleTuple -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ht:dS:n:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'S': simFlag = 1; setOption = optarg; break;
    case 'd': simFlag = 0; break;
    case 'n': NjlabDir = optarg; break;
    case 'r': rnOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./bin/GetSimpleTuple -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "GetSimpleTuple program." << std::endl;
  std::cout << "Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple -t[target]" << std::endl;
  std::cout << "    selects target: D, C, Fe, Pb" << std::endl;
  std::cout << "    IMPORTANT: D option is only for simulations" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple -d" << std::endl;
  std::cout << "    gets tuples from data" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple -S[old,usm,jlab]" << std::endl;
  std::cout << "    gets tuples from set of simulations" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple -n[00,01,02,...]" << std::endl;
  std::cout << "    selects N dir (exclusive and mandatory for -Sjlab option)" << std::endl;
  std::cout << "    (please, maintain numbering scheme!)" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple -r[0001,...,9999]" << std::endl;
  std::cout << "    selects run number (mandatory for all!)" << std::endl;
  std::cout << "    numbering scheme: 00,...,99     for jlab" << std::endl;
  std::cout << "                      0000,...,1XXX for old/usm" << std::endl;
  std::cout << "                      XXXXX         for data" << std::endl;
  std::cout << std::endl;
}

void assignOptions() {
  // data type
  if (!simFlag) {
    NtupleName = "ntuple_data";
    inputFile = rawDataDir_utfsm + "/clas_" + rnOption + "_" + nFile + " .pass2.root"; // how to add this???
    analyserOption = targetOption;
    outDir = proDir + "/out/prunedData/" + targetOption;
    outTitle = "Data of particles";
  } else if (simFlag) {
    NtupleName = "ntuple_sim";
    analyserOption = "Sim";
    outTitle = "Simulation of particles";
    outDir = proDir + "/out/prunedSim/" + setOption + "/" + targetOption;
    if (setOption == "jlab") {
      inputFile = rawSimDir_jlab + "/output/" + targetOption + "/" + NjlabDir + "/recsis" + targetOption + "_" + rnOption + ".root";
      outDir += "/" + NjlabDir;
    } else if (setOption == "old" || setOption == "usm") {
      inputFile = rawSimDir_utfsm + "/" + setOption + "/" + targetOption + "/recsis" + targetOption + "_" + rnOption + ".root";
    }
  }
  // regardless of the data type
  outFile = outDir + "/pruned" + targetOption + "_" + rnOption + ".root";
}

void printOptions() {
  std::cout << "Executing GetSimpleTuple program. The chosen parameters are: " << std::endl;
  std::cout << "  targetOption   = " << targetOption << std::endl;
  std::cout << "  simFlag        = " << simFlag << std::endl;
  std::cout << "  setOption      = " << setOption << std::endl;
  std::cout << "  NjlabDir       = " << NjlabDir << std::endl;
  std::cout << "  rnOption       = " << rnOption << std::endl;
  std::cout << "  inputFile      = " << inputFile << std::endl;
  std::cout << "  analyserOption = " << analyserOption << std::endl;
  std::cout << std::endl;
}

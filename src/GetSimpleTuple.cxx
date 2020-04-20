/***************************************/
/*  GetSimpleTuple.cxx                 */
/*                                     */
/*  Created by Orlando Soto            */
/*  Modified by Andrés Bórquez         */
/*                                     */
/***************************************/

// UPDATE:
// There are no longer separate trees for simrec and gsim

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

/*** Global variables ***/

// options
Int_t   simFlag = 0;
TString targetOption;
TString setOption;

TString outDir;
TString textFile;

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

  TString auxLine;
  
  /*** Reading text file to gather root file ***/
  
  ifstream in(textFile, ios::in);

  if (!in) {
    std::cerr << "Couldn't open file. Terminating..." << std::endl;
    exit(1);
  }

  std::cout << "Reading file " << textFile << " ..." << std::endl;
  while (in >> auxLine) {
    std::cout << "  auxLine = " << auxLine << std::endl;
    std::cout << std::endl;
    input->Add(auxLine);
  }
  in.close();
  
  // obtain electron mass
  TDatabasePDG pdg;
  Double_t kMe = pdg.GetParticle(11)->Mass();

  // hadron variables
  TString varListHadrons = "TargType:Q2:Nu:Xb:W:SectorEl:ThetaPQ:PhiPQ:Zh:Pt:W2p:Xf:T:P:T4:deltaZ:E:Ee:Pe:Ect:Sct:Ecr:Scr:evnt:Px:Py:Pz:Xe:Ye:Ze:Xec:Yec:Zec:TEc:ECX:ECY:ECZ:Pex:Pey:Pez:Ein:Eout:Eine:Eoute:pid:Betta:vxh:vyh:vzh";
  if (simFlag) {
    varListHadrons += ":mc_TargType:mc_Q2:mc_Nu:mc_Xb:mc_W:mc_SectorEl:mc_ThetaPQ:mc_PhiPQ:mc_Zh:mc_Pt:mc_W2p:mc_Xf:mc_T:mc_P:mc_T4:mc_deltaZ:mc_E:mc_Ee:mc_Pe:mc_Ect:mc_Sct:mc_Ecr:mc_Scr:mc_evnt:mc_Px:mc_Py:mc_Pz:mc_Xe:mc_Ye:mc_Ze:mc_Xec:mc_Yec:mc_Zec:mc_TEc:mc_ECX:mc_ECY:mc_ECZ:mc_Pex:mc_Pey:mc_Pez:mc_Ein:mc_Eout:mc_Eine:mc_Eoute:mc_pid:mc_Betta:mc_vxh:mc_vyh:mc_vzh";
  }
  Int_t   NvarHadrons = varListHadrons.CountChar(':') + 1; // 49 for data; 98 for sim
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
  
  for (Int_t k = 0; k < nEntries; k++) {
    Int_t nRows = input->GetNRows("EVNT");
    if (nRows < 1) {
      input->Next();
      continue;
    }

    if ((t->GetCategorization(0, analyserOption.Data(), true)) == "electron") { // here it goes!
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

      for (Int_t i = 1; i < nRows; i++) {
      	TString category = t->GetCategorization(i, analyserOption.Data()); // here it goes again
      	if (category == "gamma" || 
	    category == "pi-" || 
	    category == "high energy pion +" || 
	    category == "low energy pion +" || 
	    category == "s_electron" || 
	    category == "positron") {
	  varHadrons[0] = t->ElecVertTarg();
	  varHadrons[1] = t->Q2();
	  varHadrons[2] = t->Nu();
	  varHadrons[3] = t->Xb();
	  varHadrons[4] = t->W();
	  varHadrons[5] = t->Sector(0);
	  varHadrons[6] = t->ThetaPQ(i);
	  varHadrons[7] = t->PhiPQ(i);
	  varHadrons[8] = t->Zh(i);
	  varHadrons[9] = TMath::Sqrt(t -> Pt2(i));
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

	  // fill
	  tHadrons->Fill(varHadrons);
	}
      }
    }

    if (simFlag && t->Id(0, 1) == 11) {
      varElectrons[19] = t->Q2(1);
      varElectrons[20] = t->W(1);
      varElectrons[21] = t->Nu(1);
      varElectrons[22] = 0; // vxec:vyec:vzec
      varElectrons[23] = 0;
      varElectrons[24] = 0;
      varElectrons[25] = t->X(0,1);
      varElectrons[26] = t->Y(0,1);
      varElectrons[27] = t->Z(0,1);
      varElectrons[28] = t->Px(0,1);
      varElectrons[29] = t->Py(0,1);
      varElectrons[30] = t->Pz(0,1);
      varElectrons[31] = k;
      varElectrons[32] = t->ElecVertTarg();
      varElectrons[33] = t->Sector(0,1);
      varElectrons[34] = t->Xb(1);

      // fill
      tElectrons->Fill(varElectrons);

      for (Int_t i = 1; i < input->GetNRows("GSIM"); i++) {
      	if (t->Id(i,1) == 22 || t->Id(i,1) == -211 || t->Id(i,1) == 211) {
	  varHadrons[49] = t->ElecVertTarg(1);
	  varHadrons[50] = t->Q2(1);
	  varHadrons[51] = t->Nu(1);
	  varHadrons[52] = t->Xb(1);
	  varHadrons[53] = t->W(1);
	  varHadrons[54] = t->Sector(0,1);
	  varHadrons[55] = t->ThetaPQ(i,1);
	  varHadrons[56] = t->PhiPQ(i,1);
	  varHadrons[57] = t->Zh(i,1);
	  varHadrons[58] = TMath::Sqrt(t->Pt2(i,1));
	  varHadrons[59] = t->Mx2(i,1);
	  varHadrons[60] = t->Xf(i,1);
	  varHadrons[61] = t->T(i,1);
	  varHadrons[62] = t->Momentum(i,1);
	  varHadrons[63] = 0; //t -> TimeCorr4(0.139570,i);
	  varHadrons[64] = (t->Z(i,1)) - (t->Z(0,1));
	  varHadrons[65] = t->Momentum(i,1);//TMath::Max(t->Etot(i),t->Ein(i)+t->Eout(i));;
	  varHadrons[66] = TMath::Sqrt(t->Momentum(0,1)*t->Momentum(0,1)+kMe*kMe); //TMath::Max(t->Etot(0),t->Ein(0)+t->Eout(0));
	  varHadrons[67] = t->Momentum(0,1);
          varHadrons[68] = 0; //t->TimeEC(0);
          varHadrons[69] = 0; //t->TimeSC(0);
          varHadrons[70] = 0; //t->PathEC(0);
          varHadrons[71] = 0; //t->PathSC(0);
          varHadrons[72] = k;
          varHadrons[73] = t->Px(i,1);
          varHadrons[74] = t->Py(i,1);
          varHadrons[75] = t->Pz(i,1);
          varHadrons[76] = t->X(0,1);
          varHadrons[77] = t->Y(0,1);
          varHadrons[78] = t->Z(0,1);
          //vert = t->GetCorrectedVert();
          varHadrons[79] = t->X(0,1); //vert->X(); 
          varHadrons[80] = t->Y(0,1); //vert->Y(); 
          varHadrons[81] = t->Z(0,1); //vert->Z(); 
          varHadrons[82] = 0; //t->TimeEC(i);
          varHadrons[83] = 0; //t->XEC(i);
          varHadrons[84] = 0; //t->YEC(i);
          varHadrons[85] = 0; //t->ZEC(i);
          varHadrons[86] = t->Px(0,1);
          varHadrons[87] = t->Py(0,1);
          varHadrons[88] = t->Pz(0,1);
	  varHadrons[89] = 0;
	  varHadrons[90] = 0;
	  varHadrons[91] = 0;
	  varHadrons[92] = 0;
	  varHadrons[93] = t->Id(i,1);
	  varHadrons[94] = t->Betta(i,1);
          varHadrons[95] = t->X(i,1);
          varHadrons[96] = t->Y(i,1);
          varHadrons[97] = t->Z(i,1);
	  
	  // fill
	  tHadrons->Fill(varHadrons);
	}
      }
    }
    input->Next();
  }
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
  while ((c = getopt(argc, argv, "ht:dS:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'S': simFlag = 1; setOption = optarg; break;
    case 'd': simFlag = 0; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./bin/GetSimpleTuple -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "GetSimpleTuple program." << std::endl;
  std::cout << "It must exist a file /tmp/RAW-[set]-[target].tmp with the location of the input root file to prune." << std::endl;
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
}

void assignOptions() {
  // data type
  if (!simFlag) {
    // tuple
    NtupleName = "ntuple_data";
    // input
    textFile = tmpDir + "/RAW-data-" + targetOption + ".tmp";
    // analyser
    analyserOption = targetOption;
    // out
    outDir = proDir + "/out/prunedData/" + targetOption;
    outTitle = "Data of particles";
  } else if (simFlag) {
    // tuple
    NtupleName = "ntuple_sim";
    // input
    textFile = tmpDir + "/RAW-" + setOption + "-" + targetOption + ".tmp";
    // analyser
    analyserOption = "Sim";
    // out
    outDir = proDir + "/out/prunedSim/" + setOption + "/" + targetOption;
    outTitle = "Simulation of particles";
  }
  // regardless of the data type
  outFile = outDir + "/pruned_out.root";
}

void printOptions() {
  std::cout << "Executing GetSimpleTuple program. The chosen parameters are: " << simFlag << std::endl;
  std::cout << "  targetOption   = " << targetOption << std::endl;
  std::cout << "  simFlag        = " << simFlag << std::endl;
  std::cout << "  setOption      = " << setOption << std::endl;
  std::cout << "  analyserOption = " << analyserOption << std::endl;
  std::cout << std::endl;
}

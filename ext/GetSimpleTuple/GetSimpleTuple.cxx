/***************************************/
/*  GetSimpleTuple.cxx                 */
/*                                     */
/*  Created by Orlando Soto            */
/*  Modified by Andrés Bórquez         */
/*                                     */
/***************************************/

#include "Riostream.h"
#include "TApplication.h"
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TString.h"
#include "TMath.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"

#include "TClasTool.h"
#include "TIdentificator.h"

// Global variables
TString titleTarget;
TString targetOption;
TString analyserOption;
TString topFolder;
TString outFolder;
Bool_t simFlag = kFALSE;
TString categoryOption;

// Declaration of functions, parse ~ analysis
inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printOptions();
void printUsage();

int main(int argc, char **argv) {
  
  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // init ClasTool (?)
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");

  char File[200];
  
  if (!simFlag) {
    ifstream in("dataFiles" + titleTarget + ".txt", ios::in);
    if (!in) {
      std::cerr << "File Not Opened!" << std::endl;
      exit(1);
    }
    while (in >> File) {
      input->Add(File);
    }
    in.close();
  } else if (simFlag) {
    ifstream in("simulFiles-" + categoryOption + "-" + targetOption + ".tmp", ios::in);
    if (!in) {
      std::cerr << "File Not Opened!" << std::endl;
      exit(1);
    }
    while (in >> File) {
      input->Add(File);
    }
    in.close();
  }

  // obtain electron mass
  TDatabasePDG pdg;
  Double_t kMe = pdg.GetParticle(11)->Mass();

  // hadron variables
  TString VarList = "TargType:Q2:Nu:Xb:W:SectorEl:ThetaPQ:PhiPQ:Zh:Pt:W2p:Xf:T:P:T4:deltaZ:E:Ee:Pe:Ect:Sct:Ecr:Scr:evnt:Px:Py:Pz:Xe:Ye:Ze:Xec:Yec:Zec:TEc:ECX:ECY:ECZ:Pex:Pey:Pez:Ein:Eout:Eine:Eoute:pid:Betta:vxh:vyh:vzh";
  Int_t Nvar = VarList.CountChar(':') + 1;
  Float_t *vars = new Float_t[Nvar];
  
  // electron variables
  TString VarListElec = "Q2:W:Nu:vxec:vyec:vzec:vxe:vye:vze:Pex:Pey:Pez:event:TargType:sector:Xb:ECX:ECY:ECZ";
  Int_t NvarElec = VarListElec.CountChar(':') + 1; // 19 
  Float_t DataElec[NvarElec];

  TNtuple *ntuple_thrown = 0;
  TNtuple *e_thrown = 0;

  TVector3 *vert;

  TIdentificator *t = new TIdentificator(input);
  Long_t nEntries = (Long_t) input->GetEntries();

  TFile *output;

  // creates 2 ntuples for data & 4 ntuples for sim
  TString NtupleName;
  if (!simFlag) {
    NtupleName = "ntuple_data";
    output = new TFile(outFolder + "/prune_data" + titleTarget + ".root", "RECREATE", "Data of particles"); // output file
  } else if (simFlag) {
    NtupleName = "ntuple_accept";
    output = new TFile(outFolder + "/pruned" + targetOption + ".root", "RECREATE", "Simulation of particles"); // output file
    ntuple_thrown = new TNtuple("ntuple_thrown", "particles pluses", VarList);
    e_thrown = new TNtuple("e_thrown", "All Electrons", VarListElec);
  }
  
  TNtuple *ntuple = new TNtuple(NtupleName, "Stable particles", VarList);
  TNtuple *tElec = new TNtuple("e_rec", "All Electrons", VarListElec);  

  cout.width(4);
  input->Next();
  
  for (Int_t k = 0; k < nEntries; k++) {
    Int_t nRows = input->GetNRows("EVNT");
    // std::cout << "nrows:\t" << nRows << std::endl;
    if (nRows < 1) {
      input->Next();
      continue;
    }

    if ((t->GetCategorization(0, analyserOption.Data(), true)) == "electron") { // here it goes!
      DataElec[0] = t->Q2();
      DataElec[1] = t->W();
      DataElec[2] = t->Nu();
      vert = t->GetCorrectedVert();
      Float_t vxec = vert->X(); 
      Float_t vyec = vert->Y(); 
      Float_t vzec = vert->Z(); 
      DataElec[3] = vxec; 
      DataElec[4] = vyec; 
      DataElec[5] = vzec;
      DataElec[6] = t->X(0);
      DataElec[7] = t->Y(0);
      DataElec[8] = t->Z(0);
      DataElec[9] = t->Px(0);
      DataElec[10] = t->Py(0);
      DataElec[11] = t->Pz(0);
      DataElec[12] = k;
      DataElec[13] = t->ElecVertTarg();
      DataElec[14] = t->Sector(0);
      DataElec[15] = t->Xb();
      DataElec[16] = t->XEC(0);
      DataElec[17] = t->YEC(0);
      DataElec[18] = t->ZEC(0);

      tElec->Fill(DataElec);

      // std::cout << "Event: " << input->GetCurrentEvent() << std::endl;
      // std::cout << "Got electron data" << std::endl;

      Int_t NmbPion = 0;

      for (Int_t i = 1; i < nRows; i++) {
	// std::cout << "nr:\t" << i << std::endl; 
      	TString category = t->GetCategorization(i, analyserOption.Data()); // here it goes again
      	if (category == "gamma" || 
	    category == "pi-" || 
	    category == "high energy pion +" || 
	    category == "low energy pion +" || 
	    category == "s_electron" || 
	    category == "positron") {
	  vars[0] = t->ElecVertTarg();
	  vars[1] = t->Q2();
	  vars[2] = t->Nu();
	  vars[3] = t->Xb();
	  vars[4] = t->W();
	  vars[5] = t->Sector(0);
	  vars[6] = t->ThetaPQ(i);
	  vars[7] = t->PhiPQ(i);
	  vars[8] = t->Zh(i);
	  vars[9] = TMath::Sqrt(t -> Pt2(i));
	  vars[10] = t->Mx2(i);
	  vars[11] = t->Xf(i);
	  vars[12] = t->T(i);
	  vars[13] = t->Momentum(i);
	  vars[14] = t->TimeCorr4(0.139570,i);
	  vars[15] = (t->Z(i)) - (t->Z(0));
	  vars[16] = TMath::Max(t->Etot(i), t->Ein(i) + t->Eout(i));
          vars[17] = TMath::Max(t->Etot(0), t->Ein(0) + t->Eout(0));
          vars[18] = t->Momentum(0);
          vars[19] = t->TimeEC(0);
          vars[20] = t->TimeSC(0);
          vars[21] = t->PathEC(0);
          vars[22] = t->PathSC(0);
          vars[23] = k;
          vars[24] = t->Px(i);
          vars[25] = t->Py(i);
          vars[26] = t->Pz(i);
          vars[27] = t->X(0);
          vars[28] = t->Y(0);
          vars[29] = t->Z(0);
          vert = t->GetCorrectedVert();
          vars[30] = vert->X(); 
          vars[31] = vert->Y(); 
          vars[32] = vert->Z(); 
          vars[33] = t->TimeEC(i);
          vars[34] = t->XEC(i);
          vars[35] = t->YEC(i);
          vars[36] = t->ZEC(i);
          vars[37] = t->Px(0);
          vars[38] = t->Py(0);
          vars[39] = t->Pz(0);
          vars[40] = t->Ein(i);
          vars[41] = t->Eout(i);
          vars[42] = t->Ein(0);
          vars[43] = t->Eout(0);
	  vars[44] = ((category == "gamma")?22:
		     ((category == "pi-")?-211:
		     (( category == "high energy pion +" || category == "low energy pion +")?211:
		     ((category == "s_electron")?11:-11))));
	  vars[45] = t->Betta(i);
          vars[46] = t->X(i);
          vars[47] = t->Y(i);
          vars[48] = t->Z(i);
	  // Fill
	  ntuple->Fill(vars);
	}
      }
    }

    /*&& t -> Q2(1) > 1. && t -> W(1) > 2. && t -> Nu(1) / 5.015 < 0.85*/
    if (simFlag && t->Id(0, 1) == 11) {
      DataElec[0] = t->Q2(1);
      DataElec[1] = t->W(1);
      DataElec[2] = t->Nu(1);
      DataElec[3] = 0; // vxec:vyec:vzec
      DataElec[4] = 0;
      DataElec[5] = 0;
      DataElec[6] = t->X(0,1);
      DataElec[7] = t->Y(0,1);
      DataElec[8] = t->Z(0,1);
      DataElec[9] = t->Px(0,1);
      DataElec[10] = t->Py(0,1);
      DataElec[11] = t->Pz(0,1);
      DataElec[12] = k;
      DataElec[13] = t->ElecVertTarg();
      DataElec[14] = t->Sector(0,1);
      DataElec[15] = t->Xb(1);
      // Fill
      e_thrown->Fill(DataElec);

      // std::cout << "got electron gsim" << std::endl;

      Int_t NmbPion = 0;
      for (Int_t i = 1; i < input->GetNRows("GSIM"); i++) {
      	if (t->Id(i,1) == 22 || t->Id(i,1) == -211 || t->Id(i,1) == 211) {
	  vars[0] = t->ElecVertTarg(1);
	  vars[1] = t->Q2(1);
	  vars[2] = t->Nu(1);
	  vars[3] = t->Xb(1);
	  vars[4] = t->W(1);
	  vars[5] = t->Sector(0,1);
	  vars[6] = t->ThetaPQ(i,1);
	  vars[7] = t->PhiPQ(i,1);
	  vars[8] = t->Zh(i,1);
	  vars[9] = TMath::Sqrt(t->Pt2(i,1));
	  vars[10] = t->Mx2(i,1);
	  vars[11] = t->Xf(i,1);
	  vars[12] = t->T(i,1);
	  vars[13] = t->Momentum(i,1);
	  vars[14] = 0; //t -> TimeCorr4(0.139570,i);
	  vars[15] = (t->Z(i,1)) - (t->Z(0,1));
	  vars[16] = t->Momentum(i,1);//TMath::Max(t->Etot(i),t->Ein(i)+t->Eout(i));;
	  vars[17] = TMath::Sqrt(t->Momentum(0,1)*t->Momentum(0,1)+kMe*kMe); //TMath::Max(t->Etot(0),t->Ein(0)+t->Eout(0));
	  vars[18] = t->Momentum(0,1);
          vars[19] = 0; //t->TimeEC(0);
          vars[20] = 0; //t->TimeSC(0);
          vars[21] = 0; //t->PathEC(0);
          vars[22] = 0; //t->PathSC(0);
          vars[23] = k;
          vars[24] = t->Px(i,1);
          vars[25] = t->Py(i,1);
          vars[26] = t->Pz(i,1);
          vars[27] = t->X(0,1);
          vars[28] = t->Y(0,1);
          vars[29] = t->Z(0,1);
          //vert = t->GetCorrectedVert();
          vars[30] = t->X(0,1); //vert->X(); 
          vars[31] = t->Y(0,1); //vert->Y(); 
          vars[32] = t->Z(0,1); //vert->Z(); 
          vars[33] = 0; //t->TimeEC(i);
          vars[34] = 0; //t->XEC(i);
          vars[35] = 0; //t->YEC(i);
          vars[36] = 0; //t->ZEC(i);
          vars[37] = t->Px(0,1);
          vars[38] = t->Py(0,1);
          vars[39] = t->Pz(0,1);
	  vars[40] = 0;
	  vars[41] = 0;
	  vars[42] = 0;
	  vars[43] = 0;
	  vars[44] = t->Id(i,1);
	  vars[45] = t->Betta(i,1);
          vars[46] = t->X(i,1);
          vars[47] = t->Y(i,1);
          vars[48] = t->Z(i,1);
	  // Fill
	  ntuple_thrown->Fill(vars);
	}
      }
    }
    // std::cout << std::right << float(k+1)/nEntries*100 << "%\r";
    // cout.flush();
    // std::cout << std::right << float(k+1)/nEntries*100 << "%\n";
    input->Next();
  }
  output->Write();
  output->Close();
  // std::cout << "Done." << std::endl;
  return 0;
}

inline int parseCommandLine(int argc, char* argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./GetSimpleTuple -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "hd:s:f:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 'd': targetOption = optarg; analyserOption = targetOption; break;
    case 'f': categoryOption = optarg; break;
    case 's': simFlag = kTRUE; targetOption = optarg; analyserOption = "Sim"; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./GetSimpleTuple -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printUsage() {
  std::cout << "GetSimpleTuple program. It must exist a `dataFiles[target].txt` or a `simulFiles[target-short].txt` in the same folder. Usage is:" << std::endl;
  std::cout << "./GetSimpleTuple -[options] -[more options]" << std::endl;
  std::cout << "  h           : prints help and exit program" << std::endl;
  std::cout << "  d[target]   : gets tuples from data: C | Fe | Pb" << std::endl;
  std::cout << "  s[target]   : gets tuples from simulations: D | C | Fe | Pb" << std::endl;
  std::cout << "  f[category] : selects simulations from: old, bad, usm, jlab" << std::endl;
}

void assignOptions() {
  // target
  if (targetOption == "C") titleTarget = "C-thickD2";
  else if (targetOption == "Fe") titleTarget = "Fe-thickD2";
  else if (targetOption == "Pb") titleTarget = "Pb-thinD2";
  else titleTarget = targetOption;
  // kind of data
  if (!simFlag) {
    topFolder = "/eos/user/b/borquez/prunedData";
    outFolder = topFolder + "/" + titleTarget;
  } else if (simFlag) {
    topFolder = "/eos/user/b/borquez/prunedSim";
    outFolder = topFolder + "/" + categoryOption + "/" + targetOption;
  }
}

void printOptions() {
  std::cout << "simFlag=" << simFlag << std::endl;
  std::cout << "targetOption=" << targetOption << std::endl;
  std::cout << "categoryOption=" << categoryOption << std::endl;
  std::cout << "analyserOption=" << analyserOption << std::endl;
  std::cout << "outFolder=" << outFolder << std::endl;
}

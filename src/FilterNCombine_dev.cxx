/*****************************************/
/*  FilterNCombine.cxx                   */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// IN DEVELOPMENT
// - takes care on the jlab/nn dir
// - want to join gsim and simrec... 

#include "analysisConfig.h"

/*** Constants ***/

Float_t kEbeam = 5.014;

/*** Global variables ***/

// options
TString targetOption;
Int_t   simFlag = 0;
TString setOption;
TString NjlabDir;

TString treeName;

TString outDir; // depends on data type
TString outFile;

// input
TString textFile;
TString inputFile;

// There are 23 in total
Float_t tTargType;
Float_t tQ2, tNu, tXb, tW;
Float_t tSector;
Float_t tPhiPQ, tThetaPQ;
Float_t tE;
Float_t tEvent;
Float_t tPx, tPy, tPz;
Float_t tXec, tYec, tZec;
Float_t tECX, tECY, tECZ;
Float_t tPex, tPey, tPez;
Float_t tPid;

// added 23 more!
Float_t tmc_TargType;
Float_t tmc_Q2, tmc_Nu, tmc_Xb, tmc_W;
Float_t tmc_Sector;
Float_t tmc_PhiPQ, tmc_ThetaPQ;
Float_t tmc_E;
Float_t tmc_Event;
Float_t tmc_Px, tmc_Py, tmc_Pz;
Float_t tmc_Xec, tmc_Yec, tmc_Zec;
Float_t tmc_ECX, tmc_ECY, tmc_ECZ;
Float_t tmc_Pex, tmc_Pey, tmc_Pez;
Float_t tmc_Pid;

Int_t Ne;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void printUsage();
void assignOptions();
void printOptions();

Float_t CorrectGammaMomentum(Int_t i); // i stands for component
Float_t PhiPQ(Float_t fPx, Float_t fPy, Float_t fPz);
Float_t ThetaPQ(Float_t fPx, Float_t fPy, Float_t fPz);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();
  
  // dir structure, just in case
  system("mkdir -p " + outDir);

  /*** Read text file to gather input root file ***/

  std::ifstream inFile(textFile);
  std::cout << "Reading " << textFile << " ..." << std::endl;
  TString auxLine;
  while (inFile >> auxLine) {
    inputFile = auxLine;
    std::cout << "  inputFile = " << inputFile << std::endl;
  }
  inFile.close();
  std::cout << std::endl;
  
  /*** Init tree ***/
  
  // hadrons (t - tree)
  TChain *t = new TChain();
  t->Add(inputFile + "/" + treeName); // input

  t->SetBranchStatus("*", 0);
  
  t->SetBranchStatus("TargType", 1);
  t->SetBranchStatus("Q2", 1);
  t->SetBranchStatus("Nu", 1);
  t->SetBranchStatus("Xb", 1);
  t->SetBranchStatus("W", 1);
  t->SetBranchStatus("SectorEl", 1);  
  t->SetBranchStatus("PhiPQ", 1);
  t->SetBranchStatus("ThetaPQ", 1);  
  t->SetBranchStatus("E", 1);
  t->SetBranchStatus("evnt", 1);
  t->SetBranchStatus("Px", 1);
  t->SetBranchStatus("Py", 1);
  t->SetBranchStatus("Pz", 1);
  t->SetBranchStatus("Xec", 1);
  t->SetBranchStatus("Yec", 1);
  t->SetBranchStatus("Zec", 1);
  t->SetBranchStatus("ECX", 1);
  t->SetBranchStatus("ECY", 1);
  t->SetBranchStatus("ECZ", 1);
  t->SetBranchStatus("Pex", 1);
  t->SetBranchStatus("Pey", 1);
  t->SetBranchStatus("Pez", 1);
  t->SetBranchStatus("pid", 1);

  t->SetBranchAddress("TargType", &tTargType);
  t->SetBranchAddress("Q2", &tQ2);
  t->SetBranchAddress("Nu", &tNu);
  t->SetBranchAddress("Xb", &tXb);
  t->SetBranchAddress("W", &tW);
  t->SetBranchAddress("SectorEl", &tSector);  
  t->SetBranchAddress("PhiPQ", &tPhiPQ);
  t->SetBranchAddress("ThetaPQ", &tThetaPQ);
  t->SetBranchAddress("E", &tE);
  t->SetBranchAddress("evnt", &tEvent);
  t->SetBranchAddress("Px", &tPx);
  t->SetBranchAddress("Py", &tPy);
  t->SetBranchAddress("Pz", &tPz);
  t->SetBranchAddress("Xec", &tZec);
  t->SetBranchAddress("Yec", &tZec);
  t->SetBranchAddress("Zec", &tZec);
  t->SetBranchAddress("ECX", &tECX);
  t->SetBranchAddress("ECY", &tECY);
  t->SetBranchAddress("ECZ", &tECZ);
  t->SetBranchAddress("Pex", &tPex);
  t->SetBranchAddress("Pey", &tPey);
  t->SetBranchAddress("Pez", &tPez);
  t->SetBranchAddress("pid", &tPid);

  if (simFlag) {
    t->SetBranchStatus("mc_TargType", 1);
    t->SetBranchStatus("mc_Q2", 1);
    t->SetBranchStatus("mc_Nu", 1);
    t->SetBranchStatus("mc_Xb", 1);
    t->SetBranchStatus("mc_W", 1);
    t->SetBranchStatus("mc_SectorEl", 1);  
    t->SetBranchStatus("mc_PhiPQ", 1);
    t->SetBranchStatus("mc_ThetaPQ", 1);  
    t->SetBranchStatus("mc_E", 1);
    t->SetBranchStatus("mc_evnt", 1);
    t->SetBranchStatus("mc_Px", 1);
    t->SetBranchStatus("mc_Py", 1);
    t->SetBranchStatus("mc_Pz", 1);
    t->SetBranchStatus("mc_Xec", 1);
    t->SetBranchStatus("mc_Yec", 1);
    t->SetBranchStatus("mc_Zec", 1);
    t->SetBranchStatus("mc_ECX", 1);
    t->SetBranchStatus("mc_ECY", 1);
    t->SetBranchStatus("mc_ECZ", 1);
    t->SetBranchStatus("mc_Pex", 1);
    t->SetBranchStatus("mc_Pey", 1);
    t->SetBranchStatus("mc_Pez", 1);
    t->SetBranchStatus("mc_pid", 1);

    t->SetBranchAddress("mc_TargType", &tmc_TargType);
    t->SetBranchAddress("mc_Q2",       &tmc_Q2);
    t->SetBranchAddress("mc_Nu",       &tmc_Nu);
    t->SetBranchAddress("mc_Xb",       &tmc_Xb);
    t->SetBranchAddress("mc_W",        &tmc_W);
    t->SetBranchAddress("mc_SectorEl", &tmc_Sector);  
    t->SetBranchAddress("mc_PhiPQ",    &tmc_PhiPQ);
    t->SetBranchAddress("mc_ThetaPQ",  &tmc_ThetaPQ);
    t->SetBranchAddress("mc_E",        &tmc_E);
    t->SetBranchAddress("mc_evnt",     &tmc_Event);
    t->SetBranchAddress("mc_Px",  &tmc_Px);
    t->SetBranchAddress("mc_Py",  &tmc_Py);
    t->SetBranchAddress("mc_Pz",  &tmc_Pz);
    t->SetBranchAddress("mc_Xec", &tmc_Zec);
    t->SetBranchAddress("mc_Yec", &tmc_Zec);
    t->SetBranchAddress("mc_Zec", &tmc_Zec);
    t->SetBranchAddress("mc_ECX", &tmc_ECX);
    t->SetBranchAddress("mc_ECY", &tmc_ECY);
    t->SetBranchAddress("mc_ECZ", &tmc_ECZ);
    t->SetBranchAddress("mc_Pex", &tmc_Pex);
    t->SetBranchAddress("mc_Pey", &tmc_Pey);
    t->SetBranchAddress("mc_Pez", &tmc_Pez);
    t->SetBranchAddress("mc_pid", &tmc_Pid);
  }
  
  Ne = t->GetEntries();  
  // std::cout << "Number of entries to be processed: " << Ne << std::endl;
  // std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
  
  /*** Output settings ***/
  
  TFile *rootFile = new TFile(outFile, "RECREATE", "Omega Meson Filtered Combinations"); // output

  // 29 variables for each original detected particle
  Int_t   oTargType;
  Float_t oQ2, oNu, oXb, oYb, oW; // +1
  Float_t oZ, oPt2; // +2, recalculated
  Int_t   oSector;
  Float_t oPhiPQ, oThetaPQ, oCosThetaPQ; // +1
  Float_t oE;
  Int_t   oEvent;
  Float_t oPx, oPy, oPz;
  Float_t oP2; // +1
  Int_t   oPid;
  Float_t oXec, oYec, oZec;
  Float_t oECX, oECY, oECZ;
  Float_t oPex, oPey, oPez;
  Int_t   oEntry; // +1

  // 29 more variables for original generated particles
  Int_t   omc_TargType;
  Float_t omc_Q2, omc_Nu, omc_Xb, omc_Yb, omc_W; // +1
  Float_t omc_Z, omc_Pt2; // +2, recalculated
  Int_t   omc_Sector;
  Float_t omc_PhiPQ, omc_ThetaPQ, omc_CosThetaPQ; // +1
  Float_t omc_E;
  Int_t   omc_Event;
  Float_t omc_Px, omc_Py, omc_Pz;
  Float_t omc_P2; // +1
  Int_t   omc_Pid;
  Float_t omc_Xec, omc_Yec, omc_Zec;
  Float_t omc_ECX, omc_ECY, omc_ECZ;
  Float_t omc_Pex, omc_Pey, omc_Pez;
  Int_t   omc_Entry; // +1
  
  TTree *tOriginal = new TTree("original", "Original particles");
  tOriginal->Branch("TargType", &oTargType);
  tOriginal->Branch("Q2", &oQ2);
  tOriginal->Branch("Nu", &oNu);
  tOriginal->Branch("Xb", &oXb);
  tOriginal->Branch("Yb", &oYb);
  tOriginal->Branch("W", &oW);
  tOriginal->Branch("Z", &oZ);
  tOriginal->Branch("Pt2", &oPt2);
  tOriginal->Branch("Sector", &oSector);
  tOriginal->Branch("PhiPQ", &oPhiPQ);
  tOriginal->Branch("ThetaPQ", &oThetaPQ);
  tOriginal->Branch("CosThetaPQ", &oCosThetaPQ);
  tOriginal->Branch("E", &oE);
  tOriginal->Branch("Event", &oEvent);
  tOriginal->Branch("Px", &oPx);
  tOriginal->Branch("Py", &oPy);
  tOriginal->Branch("Pz", &oPz);
  tOriginal->Branch("pid", &oPid);
  tOriginal->Branch("Xec", &oXec);
  tOriginal->Branch("Yec", &oYec);
  tOriginal->Branch("Zec", &oZec);
  tOriginal->Branch("ECX", &oECX);
  tOriginal->Branch("ECY", &oECY);
  tOriginal->Branch("ECZ", &oECZ);
  tOriginal->Branch("Pex", &oPex);
  tOriginal->Branch("Pey", &oPey);
  tOriginal->Branch("Pez", &oPez);
  tOriginal->Branch("P2", &oP2);
  tOriginal->Branch("entry", &oEntry);

  if (simFlag) {
    tOriginal->Branch("mc_TargType", &omc_TargType);
    tOriginal->Branch("mc_Q2",  &omc_Q2);
    tOriginal->Branch("mc_Nu",  &omc_Nu);
    tOriginal->Branch("mc_Xb",  &omc_Xb);
    tOriginal->Branch("mc_Yb",  &omc_Yb);
    tOriginal->Branch("mc_W",   &omc_W);
    tOriginal->Branch("mc_Z",   &omc_Z);
    tOriginal->Branch("mc_Pt2", &omc_Pt2);
    tOriginal->Branch("mc_Sector",     &omc_Sector);
    tOriginal->Branch("mc_PhiPQ",      &omc_PhiPQ);
    tOriginal->Branch("mc_ThetaPQ",    &omc_ThetaPQ);
    tOriginal->Branch("mc_CosThetaPQ", &omc_CosThetaPQ);
    tOriginal->Branch("mc_E",     &omc_E);
    tOriginal->Branch("mc_Event", &omc_Event);
    tOriginal->Branch("mc_Px",    &omc_Px);
    tOriginal->Branch("mc_Py",    &omc_Py);
    tOriginal->Branch("mc_Pz",    &omc_Pz);
    tOriginal->Branch("mc_pid", &omc_Pid);
    tOriginal->Branch("mc_Xec", &omc_Xec);
    tOriginal->Branch("mc_Yec", &omc_Yec);
    tOriginal->Branch("mc_Zec", &omc_Zec);
    tOriginal->Branch("mc_ECX", &omc_ECX);
    tOriginal->Branch("mc_ECY", &omc_ECY);
    tOriginal->Branch("mc_ECZ", &omc_ECZ);
    tOriginal->Branch("mc_Pex", &omc_Pex);
    tOriginal->Branch("mc_Pey", &omc_Pey);
    tOriginal->Branch("mc_Pez", &omc_Pez);
    tOriginal->Branch("mc_P2", &omc_P2);
    tOriginal->Branch("mc_entry", &omc_Entry);
  }
  
  // 34 variables for mix of particles (6 are vectors)
  Int_t mTargType;
  Float_t mQ2, mNu, mXb, mYb, mW; // +1
  Float_t mZ, mPt2; // +2, recalculated
  Int_t mSector;
  Float_t mPhiPQ, mThetaPQ, mCosThetaPQ; // +1
  Float_t mE[4], mPx[4], mPy[4], mPz[4];
  Int_t mEvent, nPip, nPim, nGamma; // +3
  Int_t mPid[4];
  Float_t mXec, mYec, mZec;
  Float_t mPex, mPey, mPez;
  Int_t mEntry[4]; // +1

  Float_t pipP2, pipM;
  Float_t pimP2, pimM;
  Float_t pippimP, pippimE, pippimM;
  Float_t pi0Px, pi0Py, pi0Pz;
  Float_t pi0P2, pi0CosTheta, pi0E, pi0M;
  
  Float_t wE, wP2;
  Float_t wPx, wPy, wPz;
  Float_t wM, wD;

  // 34 more variables for mix of generated particles (6 are vectors)
  Int_t   mmc_TargType;
  Float_t mmc_Q2, mmc_Nu, mmc_Xb, mmc_Yb, mmc_W; // +1
  Float_t mmc_Z, mmc_Pt2; // +2, recalculated
  Int_t   mmc_Sector;
  Float_t mmc_PhiPQ, mmc_ThetaPQ, mmc_CosThetaPQ; // +1
  Float_t mmc_E[4], mmc_Px[4], mmc_Py[4], mmc_Pz[4];
  Int_t   mmc_Event, mc_nPip, mc_nPim, mc_nGamma; // +3
  Int_t   mmc_Pid[4];
  Float_t mmc_Xec, mmc_Yec, mmc_Zec;
  Float_t mmc_Pex, mmc_Pey, mmc_Pez;
  Int_t   mmc_Entry[4]; // +1

  Float_t mc_pipP2, mc_pipM;
  Float_t mc_pimP2, mc_pimM;
  Float_t mc_pippimP, mc_pippimE, mc_pippimM;
  Float_t mc_pi0Px, mc_pi0Py, mc_pi0Pz;
  Float_t mc_pi0P2, mc_pi0CosTheta, mc_pi0E, mc_pi0M;
  
  Float_t mc_wE, mc_wP2;
  Float_t mc_wPx, mc_wPy, mc_wPz;
  Float_t mc_wM, mc_wD;
  
  TTree *tMix = new TTree("mix", "Combination of particles");
  tMix->Branch("TargType", &mTargType);
  tMix->Branch("Q2", &mQ2);
  tMix->Branch("Nu", &mNu);
  tMix->Branch("Xb", &mXb);
  tMix->Branch("Yb", &mYb);
  tMix->Branch("W",  &mW);
  tMix->Branch("Z",  &mZ);
  tMix->Branch("Pt2", &mPt2);
  tMix->Branch("Sector", &mSector);
  tMix->Branch("PhiPQ",      &mPhiPQ);
  tMix->Branch("ThetaPQ",    &mThetaPQ);
  tMix->Branch("CosThetaPQ", &mCosThetaPQ);
  tMix->Branch("E", &mE, "E[4]/F");
  tMix->Branch("Event", &mEvent);
  tMix->Branch("nPip",   &nPip);
  tMix->Branch("nPim",   &nPim);
  tMix->Branch("nGamma", &nGamma);
  tMix->Branch("Px", &mPx, "Px[4]/F");
  tMix->Branch("Py", &mPy, "Py[4]/F");
  tMix->Branch("Pz", &mPz, "Pz[4]/F");
  tMix->Branch("pid", &mPid, "pid[4]/I");
  tMix->Branch("Xec", &mXec);
  tMix->Branch("Yec", &mYec);
  tMix->Branch("Zec", &mZec);
  tMix->Branch("Pex", &mPex);
  tMix->Branch("Pey", &mPey);
  tMix->Branch("Pez", &mPez);
  tMix->Branch("entry", &mEntry, "entry[4]/I");

  // pions variables (4 + 7 + 3)
  tMix->Branch("pipP2", &pipP2);
  tMix->Branch("pipM",  &pipM);
  tMix->Branch("pimP2", &pimP2);
  tMix->Branch("pimM",  &pimM);
  tMix->Branch("pi0Px", &pi0Px);
  tMix->Branch("pi0Py", &pi0Py);
  tMix->Branch("pi0Pz", &pi0Pz);  
  tMix->Branch("pi0P2", &pi0P2);
  tMix->Branch("pi0CosTheta", &pi0CosTheta);  
  tMix->Branch("pi0M", &pi0M);
  tMix->Branch("pi0E", &pi0E);
  tMix->Branch("pippimE", &pippimE);  
  tMix->Branch("pippimP", &pippimP);
  tMix->Branch("pippimM", &pippimM);
  
  // omega variables (7)
  tMix->Branch("wE",  &wE);
  tMix->Branch("wPx", &wPx);
  tMix->Branch("wPy", &wPy);
  tMix->Branch("wPz", &wPz);
  tMix->Branch("wP2", &wP2);
  tMix->Branch("wM",  &wM);
  tMix->Branch("wD",  &wD);

  if (simFlag) {
    tMix->Branch("mc_TargType", &mmc_TargType);
    tMix->Branch("mc_Q2", &mmc_Q2);
    tMix->Branch("mc_Nu", &mmc_Nu);
    tMix->Branch("mc_Xb", &mmc_Xb);
    tMix->Branch("mc_Yb", &mmc_Yb);
    tMix->Branch("mc_W",  &mmc_W);
    tMix->Branch("mc_Z",  &mmc_Z);
    tMix->Branch("mc_Pt2", &mmc_Pt2);
    tMix->Branch("mc_Sector", &mmc_Sector);
    tMix->Branch("mc_PhiPQ",      &mmc_PhiPQ);
    tMix->Branch("mc_ThetaPQ",    &mmc_ThetaPQ);
    tMix->Branch("mc_CosThetaPQ", &mmc_CosThetaPQ);
    tMix->Branch("mc_E", &mmc_E, "E[4]/F");
    tMix->Branch("mc_Event", &mmc_Event);
    tMix->Branch("mc_nPip",   &mc_nPip);
    tMix->Branch("mc_nPim",   &mc_nPim);
    tMix->Branch("mc_nGamma", &mc_nGamma);
    tMix->Branch("mc_Px", &mmc_Px, "Px[4]/F");
    tMix->Branch("mc_Py", &mmc_Py, "Py[4]/F");
    tMix->Branch("mc_Pz", &mmc_Pz, "Pz[4]/F");
    tMix->Branch("mc_pid", &mmc_Pid, "pid[4]/I");
    tMix->Branch("mc_Xec", &mmc_Xec);
    tMix->Branch("mc_Yec", &mmc_Yec);
    tMix->Branch("mc_Zec", &mmc_Zec);
    tMix->Branch("mc_Pex", &mmc_Pex);
    tMix->Branch("mc_Pey", &mmc_Pey);
    tMix->Branch("mc_Pez", &mmc_Pez);
    tMix->Branch("mc_entry", &mmc_Entry, "entry[4]/I");
    
    // pions variables (4 + 7 + 3)
    tMix->Branch("mc_pipP2", &mc_pipP2);
    tMix->Branch("mc_pipM",  &mc_pipM);
    tMix->Branch("mc_pimP2", &mc_pimP2);
    tMix->Branch("mc_pimM",  &mc_pimM);
    tMix->Branch("mc_pi0Px", &mc_pi0Px);
    tMix->Branch("mc_pi0Py", &mc_pi0Py);
    tMix->Branch("mc_pi0Pz", &mc_pi0Pz);  
    tMix->Branch("mc_pi0P2", &mc_pi0P2);
    tMix->Branch("mc_pi0CosTheta", &mc_pi0CosTheta);  
    tMix->Branch("mc_pi0M", &mc_pi0M);
    tMix->Branch("mc_pi0E", &mc_pi0E);
    tMix->Branch("mc_pippimE", &mc_pippimE);  
    tMix->Branch("mc_pippimP", &mc_pippimP);
    tMix->Branch("mc_pippimM", &mc_pippimM);
    
    // omega variables (7)
    tMix->Branch("mc_wE",  &mc_wE);
    tMix->Branch("mc_wPx", &mc_wPx);
    tMix->Branch("mc_wPy", &mc_wPy);
    tMix->Branch("mc_wPz", &mc_wPz);
    tMix->Branch("mc_wP2", &mc_wP2);
    tMix->Branch("mc_wM",  &mc_wM);
    tMix->Branch("mc_wD",  &mc_wD);
  }

  /*** START FILTERING ***/
  
  // counting variables
  Int_t currentEvent;
  Int_t previousEvent;
  
  Int_t nPipThisEvent = 0;
  Int_t nPimThisEvent = 0;
  Int_t nGammaThisEvent = 0;
  
  Int_t nParticles = 0;
  Int_t nCombThisEvent = 0;
  
  Int_t nOmega = 0;
  Int_t nAtLeastOmega = 0;

  Int_t nEvents = 0;

  /*** FOR DATA ***/

  if (!simFlag) {
  
    // searchs for different event numbers, iterates in all entries
    for (Int_t i = 0; i < Ne; i++) {
      t->GetEntry(i);
      currentEvent = (Int_t) tEvent;
      
      // prevents repetition until new event, very important
      if (i > 0) {
	t->GetEntry(i-1);
	previousEvent = (Int_t) tEvent;
	if (previousEvent == currentEvent) continue;
      }
      
      // std::cout << "Current event number: " << currentEvent << std::endl;
      // std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
      
      // looks at the entries (particles) of the current event
      for (Int_t j = i; j < Ne; j++) {
	t->GetEntry(j);
	if (tEvent == (Float_t) currentEvent) {
	  // std::cout << "  Entry number: " << j << std::endl;
	  // std::cout << "  Event number: " << (Int_t) tEvent << std::endl;
	  // std::cout << "  pid:          " << tPid << std::endl;
	  // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
	  // let's count the particles
	  if (tPid == (Float_t) 211) nPipThisEvent++;
	  if (tPid == (Float_t) -211) nPimThisEvent++;
	  if (tPid == (Float_t) 22) nGammaThisEvent++;
	} else {
	  j = Ne; // break this loop, optimize
	}
      }
      
      // show counts
      // std::cout << "  nPip   = " << nPipThisEvent << std::endl;
      // std::cout << "  nPim   = " << nPimThisEvent << std::endl;
      // std::cout << "  nGamma = " << nGammaThisEvent << std::endl;
      // std::cout << "  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
      
      /*** Candidate appeared! ***/
      
      if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
	
	nAtLeastOmega++;
	nParticles = nPipThisEvent + nPimThisEvent + nGammaThisEvent; // nParticlesThisEvent
	nCombThisEvent = TMath::Binomial(nPipThisEvent, 1)*TMath::Binomial(nPimThisEvent, 1)*TMath::Binomial(nGammaThisEvent, 2);
	nOmega += nCombThisEvent;
	
	// std::cout << "  AT LEAST ONE OMEGA HAS BEEN FOUND!" << std::endl;
	
	/*** The original ***/
	
	// saves all information from the original particles in the current event, with no mixing
	// warning: all the hadronic variables correspond to the respective hadron, nothing more
	for (Int_t j = i; j < Ne; j++) {
	  t->GetEntry(j);
	  if (tEvent == (Float_t) currentEvent) {
	    // assigning energy
	    // for gammas is corrected from a primitive sampling fraction, hence the factor 0.272
	    // for pions is assigned from the measured momentum and a constant invariant mass (pdg)
	    if (tPid == 22) {
	      oE = tE/0.272;
	    } else if (tPid == 211 || tPid == -211) {
	      oE = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz + kMpi*kMpi);
	    }
	    // assigning momentum
	    // for gammas is corrected with primitive sampling fraction and ECPB treatment
	    if (tPid == 22) {
	      oPx = CorrectGammaMomentum(0);
	      oPy = CorrectGammaMomentum(1);
	      oPz = CorrectGammaMomentum(2);
	    } else if (tPid == 211 || tPid == -211) {
	      oPx = tPx; oPy = tPy; oPz = tPz;
	    }
	    oTargType = (Int_t) tTargType;
	    oQ2 = tQ2;
	    oNu = tNu;
	    oXb = tXb;
	    oYb = oNu/kEbeam;                   // added
	    oW = tW;
	    oSector = (Int_t) tSector;
	    oZ = oE/oNu;                        // recalculated
	    oPhiPQ = PhiPQ(oPx, oPy, oPz);      // updated!
	    oThetaPQ = ThetaPQ(oPx, oPy, oPz);  // updated!
	    oXec = tXec;
	    oYec = tYec;
	    oZec = tZec;
	    oECX = tECX;
	    oECY = tECY;
	    oECZ = tECZ;
	    oPex = tPex;
	    oPey = tPey;
	    oPez = tPez;
	    oP2 = oPx*oPx + oPy*oPy + oPz*oPz;  // new!
	    oCosThetaPQ = ((kEbeam - oPez)*oPz - oPex*oPx - oPey*oPy)/(TMath::Sqrt(oP2*(oQ2 + oNu*oNu))); // new!
	    oPt2 = oP2*(1 - oCosThetaPQ*oCosThetaPQ); // recalculated
	    oPid = (Int_t) tPid;
	    oEntry = j;
	    oEvent = (Int_t) tEvent;
	    tOriginal->Fill();
	  } else {
	    j = Ne; // break this loop, optimize
	  }
	}
	
	/*** The mixing ***/
	
	// tag
	Int_t jPip = 0;
	Int_t jPim = 0;
	Int_t jGamma1 = 0;
	Int_t jGamma2 = 0;
	
	Int_t partialComb = 0;
	Int_t partialLim = nGammaThisEvent - 1;
	Int_t partialFlag = 1;

	for (Int_t iPip = 0; iPip < TMath::Binomial(nPipThisEvent, 1); iPip++) {
	  
	  // find and tag pip (loop in particles)
	  for (Int_t j = i; j < (i + nParticles); j++) {
	    t->GetEntry(j);
	    if (tPid == (Float_t) 211 && j > jPip) {
	      jPip = j; // tag pip
	      j = i + nParticles; // break search
	    }
	  }
	  
	  // force a new beginning for the other particles
	  jPim = 0;
	  jGamma1 = 0;
	  jGamma2 = 0;
	  
	  for (Int_t iPim = 0; iPim < TMath::Binomial(nPimThisEvent, 1); iPim++) {
	    
	    // find and tag pim
	    for (Int_t j = i; j < (i + nParticles); j++) {
	      t->GetEntry(j);
	      if (tPid == (Float_t) -211 && j > jPim) {
		jPim = j; // tag pim
		j = i + nParticles; // break search
	      }
	    }
	    
	    // force a new beginning for the other particles
	    jGamma1 = 0;
	    jGamma2 = 0;	  
	    
	    for (Int_t iGamma = 0; iGamma < TMath::Binomial(nGammaThisEvent, 2); iGamma++) { 
	      
	      // Let's say we have nCombThisEvent=nGammaThisEvent=3
	      // That is: we have 3 gammas in this event, and those are the only cause for the possible combinations
	      
	      // In the first iteration (iGamma == 0), we tag the first gamma in the list as gamma1 (call it 'a')
	      // Then, looking for gamma2, we start from the particle next to the previously tagged gamma1, so we tag the next gamma in the list as gamma2 (call it 'b')
	      // There we made our first combination (partialComb = 0 -> partialComb = 1)
	      
	      // In the second iteration (iGamma == 1), we tag the first gamma in the list as gamma1, which happens to be 'a', the same than before
	      // Then, looking for gamma2, the condition requires to be a different gamma2 (k > jGamma2) to the one selected in the first iteration
	      // That's how we choose another gamma2, in this case it would be 'c'
	      // There we made our second combiation (partialComb = 2)
	      
	      // Now, we have used this gamma 'a' twice (partialComb = 2 = partialLim, that's what it means)
	      // So partialFlag activates, partialComb resets and partialLim becomes 1 less
	      // Because the next combination would be 'bc'
	      
	      // In the third iteration, partialFlag is already activated, so we exclude previous gamma1 ('a') from the selection
	      // The next gamma in the list would be 'b', so it gets tagged as gamma1
	      // Then, looking for gamma2, we start looking for particles next to 'b', that would tag 'c' as gamma2
	      // There should be no problem, because at this point jGamma1=jGamma2='b'
	      // it happens that (partialComb = 0 -> partialComb = 1 = partialLim)
	      // so, partialFlag keeps activated (this forces the change of gamma1)
	      // but as partialLim = 1 is the last value possible, the loop is already ending
	      
	      // For nGammaThisEvent=3
	      // There are 3 possible combinations
	      // initial variables : gamma1=0, gamma2=0, partialcomb=0, partialflag=1, partiallim=2
	      // iGamma=0          : gamma2=0, partialflag=0, gamma1=a, gamma2=b, partialcomb=1
	      // iGamma=1          :                          gamma1=a, gamma2=c, partialcomb=2, partialcomb=0, partialflag=1, partiallim=1
	      // iGamma=2          : gamma2=0, partialflag=0, gamma1=b, gamma2=c, partialcomb=1
	      
	      // For nGammaThisEvent=4
	      // There are 6 possible combinations
	      // initial variables : gamma1=0, gamma2=0, partialcomb=0, partialflag=1, partiallim=3
	      // iGamma=0          : gamma2=0, partialflag=0, gamma1=a, gamma2=b, partialcomb=1
	      // iGamma=1          :                          gamma1=a, gamma2=c, partialcomb=2,
	      // iGamma=2          :                          gamma1=a, gamma2=d, partialcomb=3, partialcomb=0, partialflag=1, partiallim=2
	      // iGamma=3          : gamma1=b, gamma2=0, partialflag=0, gamma2=c, partialcomb=1
	      // iGamma=4          :                          gamma1=b, gamma2=d, partialcomb=2, partialcomb=0, partialflag=1, partiallim=1
	      // iGamma=5          : gamma1=c, gamma2=0, partialflag=0, gamma2=d, partialcomb=1
	      
	      // debug
	      if (iGamma == 0) {
		partialComb = 0;
		partialLim = nGammaThisEvent - 1;
		partialFlag = 1;
	      }
	      
	      // the big condition
	      if (partialFlag) {
		// find and tag gamma1
		for (Int_t j = i; j < (i + nParticles); j++) {
		  t->GetEntry(j);
		  if (tPid == (Float_t) 22 && j > jGamma1) { // excludes previous gamma1
		    jGamma1 = j; // tag gamma1
		    j = i + nParticles; // break search for j
		  }
		}
		jGamma2 = 0; // resets gamma2
		partialFlag = 0;
	      }
	      
	      // find and tag gamma2
	      for (Int_t k = (jGamma1 + 1); k < (i + nParticles); k++) { // excludes gamma1
		t->GetEntry(k);
		if (tPid == (Float_t) 22 && k > jGamma2) { // excludes previous gamma2
		  jGamma2 = k; // tag gamma2
		  k = i + nParticles; // break search for k
		}
	      }
	      
	      // fix partial comb
	      partialComb++;
	      if (partialComb == partialLim && partialLim > 1) {
		partialComb = 0;
		partialLim--;
		partialFlag = 1;
	      }
	    
	      // std::cout << "jGamma1=" << jGamma1 << std::endl;
	      // std::cout << "jGamma2=" << jGamma2 << std::endl;
	      // std::cout << "jPip=" << jPip << std::endl;
	      // std::cout << "jPim=" << jPim << std::endl;
	      
	      // now extract!
	      for (Int_t j = i; j < (i + nParticles); j++) {
		t->GetEntry(j);
		if (j == jGamma1) {
		  mE[0] = tE/0.272;                 // primitive sampling fraction
		  mPx[0] = CorrectGammaMomentum(0); // correction
		  mPy[0] = CorrectGammaMomentum(1); // correction
		  mPz[0] = CorrectGammaMomentum(2); // correction
		  mPid[0] = (Int_t) tPid;
		  mEntry[0] = jGamma1;
		} else if (j == jGamma2) {
		  mE[1] = tE/0.272;                 // primitive sampling fraction
		  mPx[1] = CorrectGammaMomentum(0); // correction
		  mPy[1] = CorrectGammaMomentum(1); // correction
		  mPz[1] = CorrectGammaMomentum(2); // correction
		  mPid[1] = (Int_t) tPid;
		  mEntry[1] = jGamma2;
		} else if (j == jPip) {
		  mE[2] = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz + kMpi*kMpi); // assigned invariant mass
		  mPx[2] = tPx; mPy[2] = tPy; mPz[2] = tPz;
		  mPid[2] = (Int_t) tPid;
		  mEntry[2] = jPip;
		} else if (j == jPim) {
		  mE[3] = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz + kMpi*kMpi); // assigned invariant mass		  
		  mPx[3] = tPx; mPy[3] = tPy; mPz[3] = tPz;
		  mPid[3] = (Int_t) tPid;
		  mEntry[3] = jPim;
		}
		mTargType = (Int_t) tTargType;
		mQ2 = tQ2;
		mNu = tNu;
		mXb = tXb;
		mYb = mNu/kEbeam;
		mW = tW;
		mSector = (Int_t) tSector;
		mXec = tXec;
		mYec = tYec;
		mZec = tZec;
		mPex = tPex;
		mPey = tPey;
		mPez = tPez;
		// define pions variables
		pipP2 = mPx[2]*mPx[2] + mPy[2]*mPy[2] + mPz[2]*mPz[2];
		pipM = TMath::Sqrt(mE[2]*mE[2] - pipP2); // = kMpi
		pimP2 = mPx[3]*mPx[3] + mPy[3]*mPy[3] + mPz[3]*mPz[3];
		pimM = TMath::Sqrt(mE[3]*mE[3] - pimP2); // = kMpi
		pi0Px = mPx[0] + mPx[1];
		pi0Py = mPy[0] + mPy[1];
		pi0Pz = mPz[0] + mPz[1];
		pi0P2 = pi0Px*pi0Px + pi0Py*pi0Py + pi0Pz*pi0Pz;
		pi0CosTheta = (mPx[0]*mPx[1] + mPy[0]*mPy[1] + mPz[0]*mPz[1])/(mE[0]*mE[1]);
		pi0M = TMath::Sqrt(2*mE[0]*mE[1]*(1 - pi0CosTheta));
		pi0E = TMath::Sqrt(pi0M*pi0M + pi0P2);
		// crossed terms
		pippimP = mPx[2]*mPx[3] + mPy[2]*mPy[3] + mPz[2]*mPz[3];
		pippimE = mE[2]*mE[3];
		pippimM = TMath::Sqrt(pipM*pipM + pimM*pimM + 2*(pippimE - pippimP));
		// define omega energy and Z
		wE = mE[0] + mE[1] + mE[2] + mE[3];
		mZ = wE/mNu;
		// define omega momentum and Pt2
		wPx = mPx[0] + mPx[1] + mPx[2] + mPx[3];
		wPy = mPy[0] + mPy[1] + mPy[2] + mPy[3];
		wPz = mPz[0] + mPz[1] + mPz[2] + mPz[3];
		wP2 = wPx*wPx + wPy*wPy + wPz*wPz;
		// define omega PhiPQ
		mPhiPQ = PhiPQ(wPx, wPy, wPz);
		mThetaPQ = ThetaPQ(wPx, wPy, wPz);
		mCosThetaPQ = ((kEbeam - mPez)*wPz - mPex*wPx - mPey*wPy)/(TMath::Sqrt(wP2*(mQ2 + mNu*mNu)));
		// define omega Pt2
		mPt2 = wP2*(1 - mCosThetaPQ*mCosThetaPQ);
		// define omega mass
		wM = TMath::Sqrt(wE*wE - wP2);
		wD = wM - pipM - pimM - pi0M;
		mEvent = (Int_t) tEvent;
		nPip = nPipThisEvent;
		nPim = nPimThisEvent;
		nGamma = nGammaThisEvent;
	      }
	      // and fill
	      tMix->Fill();
	    }
	  }
	}
	// end of condition of candidate
      }
      
      // reset count variables
      nPipThisEvent = 0;
      nPimThisEvent = 0;
      nGammaThisEvent = 0;
      // sum events
      nEvents++;

      
    } // end of loop in events
    
  } // end of "data" condition
  
  /*** FOR SIMULATIONS ***/
  
  if (simFlag) {

    // more counting variables!
    Int_t nMCPipThisEvent = 0;
    Int_t nMCPimThisEvent = 0;
    Int_t nMCGammaThisEvent = 0;
    
    Int_t nMCParticles = 0;
    Int_t nMCCombThisEvent = 0;
    
    Int_t nMCOmega = 0;
    Int_t nAtLeastMCOmega = 0;
        
    /*** DETECT OMEGA IN GSIM ***/

    // loop in events
    for (Int_t i = 0; i < Ne; i++) {
      t->GetEntry(i);
      currentEvent = (Int_t) tmc_Event;
      
      // prevents repetition until new event, very important
      if (i > 0) {
	t->GetEntry(i-1);
	previousEvent = (Int_t) tmc_Event;
	if (previousEvent == currentEvent || currentEvent == -9999) continue;
	if (previousEvent == -9999) {
	  t->GetEntry(i-2);
	  previousEvent = (Int_t) tmc_Event;
	  if (previousEvent == currentEvent || currentEvent == -9999) continue;
	}
      }
      
      // looks at the entries (particles) of the current event
      for (Int_t j = i; j < Ne; j++) {
	t->GetEntry(j);
	if (tmc_Event == (Float_t) currentEvent || tEvent == (Float_t) currentEvent) {
	  // let's count the particles
	  // gsim
	  if (tmc_Pid == (Float_t) 211) nMCPipThisEvent++;
	  if (tmc_Pid == (Float_t) -211) nMCPimThisEvent++;
	  if (tmc_Pid == (Float_t) 22) nMCGammaThisEvent++;
	  // reconstructed
	  if (tPid == (Float_t) 211) nPipThisEvent++;
	  if (tPid == (Float_t) -211) nPimThisEvent++;
	  if (tPid == (Float_t) 22) nGammaThisEvent++;
	} else {
	  j = Ne; // break this loop, optimize
	}
      }

      /*** Candidate appeared in gsim! ***/

      if (nMCPipThisEvent >= 1 && nMCPimThisEvent >= 1 && nMCGammaThisEvent >= 2) {
	
	// update counters
	nAtLeastMCOmega++;
	nMCParticles = nMCPipThisEvent + nMCPimThisEvent + nMCGammaThisEvent; // number of mc particles in this event
	nMCCombThisEvent = TMath::Binomial(nMCPipThisEvent, 1)*TMath::Binomial(nMCPimThisEvent, 1)*TMath::Binomial(nMCGammaThisEvent, 2);
	nMCOmega += nMCCombThisEvent;
		
	/*** The original ***/
	
	for (Int_t j = i; j < Ne; j++) {
	  t->GetEntry(j);	
	  
	  // omega in simrec from this gsim
	  if (nPipThisEvent >= 1 && nPimThisEvent >= 1 && nGammaThisEvent >= 2) {
	    if (tPid == 22) {
	      oE = tE/0.272;
	    } else if (tPid == 211 || tPid == -211) {
	      oE = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz + kMpi*kMpi);
	    }
	    if (tPid == 22) {
	      oPx = CorrectGammaMomentum(0);
	      oPy = CorrectGammaMomentum(1);
	      oPz = CorrectGammaMomentum(2);
	    } else if (tPid == 211 || tPid == -211) {
	      oPx = tPx; oPy = tPy; oPz = tPz;
	    }
	    oTargType = (Int_t) tTargType;
	    oQ2 = tQ2;
	    oNu = tNu;
	    oXb = tXb;
	    oYb = oNu/kEbeam;                   // added
	    oW = tW;
	    oSector = (Int_t) tSector;
	    oZ = oE/oNu;                        // recalculated
	    oPhiPQ = PhiPQ(oPx, oPy, oPz);      // updated!
	    oThetaPQ = ThetaPQ(oPx, oPy, oPz);  // updated!
	    oXec = tXec;
	    oYec = tYec;
	    oZec = tZec;
	    oECX = tECX;
	    oECY = tECY;
	    oECZ = tECZ;
	    oPex = tPex;
	    oPey = tPey;
	    oPez = tPez;
	    oP2 = oPx*oPx + oPy*oPy + oPz*oPz;
	    oCosThetaPQ = ((kEbeam - oPez)*oPz - oPex*oPx - oPey*oPy)/(TMath::Sqrt(oP2*(oQ2 + oNu*oNu)));
	    oPt2 = oP2*(1 - oCosThetaPQ*oCosThetaPQ); // recalculated
	    oPid = (Int_t) tPid;
	    oEntry = j;
	    oEvent = (Int_t) tEvent;
	  } // end of omega in simrec condition
	  
	  // gsim
	  if ((Int_t) tmc_Event != -9999) {
	    omc_E = tmc_E;                                     // gsim, no correction
	    omc_Px = tmc_Px; omc_Py = tmc_Py; omc_Pz = tmc_Pz; // gsim, no correction
	    omc_TargType = (Int_t) tmc_TargType;
	    omc_Q2 = tmc_Q2;
	    omc_Nu = tmc_Nu;
	    omc_Xb = tmc_Xb;
	    omc_Yb = omc_Nu/kEbeam;                   // added
	    omc_W = tmc_W;
	    omc_Sector = (Int_t) tmc_Sector;
	    omc_Z = omc_E/omc_Nu;                        // recalculated
	    omc_PhiPQ = PhiPQ(omc_Px, omc_Py, omc_Pz);      // updated!
	    omc_ThetaPQ = ThetaPQ(omc_Px, omc_Py, omc_Pz);  // updated!
	    omc_Xec = tmc_Xec;
	    omc_Yec = tmc_Yec;
	    omc_Zec = tmc_Zec;
	    omc_ECX = tmc_ECX;
	    omc_ECY = tmc_ECY;
	    omc_ECZ = tmc_ECZ;
	    omc_Pex = tmc_Pex;
	    omc_Pey = tmc_Pey;
	    omc_Pez = tmc_Pez;
	    omc_P2 = omc_Px*omc_Px + omc_Py*omc_Py + omc_Pz*omc_Pz;
	    omc_CosThetaPQ = ((kEbeam - omc_Pez)*omc_Pz - omc_Pex*omc_Px - omc_Pey*omc_Py)/(TMath::Sqrt(omc_P2*(omc_Q2 + omc_Nu*omc_Nu)));
	    omc_Pt2 = omc_P2*(1 - omc_CosThetaPQ*omc_CosThetaPQ); // recalculated
	    omc_Pid = (Int_t) tmc_Pid;
	    omc_Entry = j;
	    omc_Event = (Int_t) tmc_Event;
	  }
	  // fill
	  tOriginal->Fill();
	} else if () {
	  j = Ne; // break this loop, optimize
	}
	
      } // end of loop in particles
    } // end of "candidate in gsim" condition
    
	/*** The mixing ***/
    /*	
	// tag
	Int_t jPip = 0;
	Int_t jPim = 0;
	Int_t jGamma1 = 0;
	Int_t jGamma2 = 0;
	
	Int_t partialComb = 0;
	Int_t partialLim = nGammaThisEvent - 1;
	Int_t partialFlag = 1;

	for (Int_t iPip = 0; iPip < TMath::Binomial(nPipThisEvent, 1); iPip++) {
	  
	  // find and tag pip (loop in particles)
	  for (Int_t j = i; j < (i + nParticles); j++) {
	    t->GetEntry(j);
	    if (tPid == (Float_t) 211 && j > jPip) {
	      jPip = j; // tag pip
	      j = i + nParticles; // break search
	    }
	  }
	  
	  // force a new beginning for the other particles
	  jPim = 0;
	  jGamma1 = 0;
	  jGamma2 = 0;
	  
	  for (Int_t iPim = 0; iPim < TMath::Binomial(nPimThisEvent, 1); iPim++) {
	    
	    // find and tag pim
	    for (Int_t j = i; j < (i + nParticles); j++) {
	      t->GetEntry(j);
	      if (tPid == (Float_t) -211 && j > jPim) {
		jPim = j; // tag pim
		j = i + nParticles; // break search
	      }
	    }
	    
	    // force a new beginning for the other particles
	    jGamma1 = 0;
	    jGamma2 = 0;	  
	    
	    for (Int_t iGamma = 0; iGamma < TMath::Binomial(nGammaThisEvent, 2); iGamma++) { 
	      	      
	      // debug
	      if (iGamma == 0) {
		partialComb = 0;
		partialLim = nGammaThisEvent - 1;
		partialFlag = 1;
	      }
	      
	      // the big condition
	      if (partialFlag) {
		// find and tag gamma1
		for (Int_t j = i; j < (i + nParticles); j++) {
		  t->GetEntry(j);
		  if (tPid == (Float_t) 22 && j > jGamma1) { // excludes previous gamma1
		    jGamma1 = j; // tag gamma1
		    j = i + nParticles; // break search for j
		  }
		}
		jGamma2 = 0; // resets gamma2
		partialFlag = 0;
	      }
	      
	      // find and tag gamma2
	      for (Int_t k = (jGamma1 + 1); k < (i + nParticles); k++) { // excludes gamma1
		t->GetEntry(k);
		if (tPid == (Float_t) 22 && k > jGamma2) { // excludes previous gamma2
		  jGamma2 = k; // tag gamma2
		  k = i + nParticles; // break search for k
		}
	      }
	      
	      // fix partial comb
	      partialComb++;
	      if (partialComb == partialLim && partialLim > 1) {
		partialComb = 0;
		partialLim--;
		partialFlag = 1;
	      }
	    	      
	      // now extract!
	      for (Int_t j = i; j < (i + nParticles); j++) {
		t->GetEntry(j);
		if (j == jGamma1) {
		  if (!gsimFlag) {
		    mE[0] = tE/0.272;                 // primitive sampling fraction
		    mPx[0] = CorrectGammaMomentum(0); // correction
		    mPy[0] = CorrectGammaMomentum(1); // correction
		    mPz[0] = CorrectGammaMomentum(2); // correction
		  } else if (gsimFlag) {
		    mE[0] = tE;
		    mPx[0] = tPx;	mPy[0] = tPy; mPz[0] = tPz;
		  }		
		  mPid[0] = (Int_t) tPid;
		  mEntry[0] = jGamma1;
		} else if (j == jGamma2) {
		  if (!gsimFlag) {
		    mE[1] = tE/0.272;                 // primitive sampling fraction
		    mPx[1] = CorrectGammaMomentum(0); // correction
		    mPy[1] = CorrectGammaMomentum(1); // correction
		    mPz[1] = CorrectGammaMomentum(2); // correction
		  } else if (gsimFlag) {
		    mE[1] = tE;
		    mPx[1] = tPx;	mPy[1] = tPy; mPz[1] = tPz;
		  }
		  mPid[1] = (Int_t) tPid;
		  mEntry[1] = jGamma2;
		} else if (j == jPip) {
		  if (!gsimFlag) {
		    mE[2] = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz + kMpi*kMpi); // assigned invariant mass
		  } else if (gsimFlag) {
		    mE[2] = tE;
		  }
		  mPx[2] = tPx; mPy[2] = tPy; mPz[2] = tPz;
		  mPid[2] = (Int_t) tPid;
		  mEntry[2] = jPip;
		} else if (j == jPim) {
		  if (!gsimFlag) {
		    mE[3] = TMath::Sqrt(tPx*tPx + tPy*tPy + tPz*tPz + kMpi*kMpi); // assigned invariant mass
		  } else if (gsimFlag) {
		    mE[3] = tE;
		  }		  
		  mPx[3] = tPx; mPy[3] = tPy; mPz[3] = tPz;
		  mPid[3] = (Int_t) tPid;
		  mEntry[3] = jPim;
		}
		mTargType = (Int_t) tTargType;
		mQ2 = tQ2;
		mNu = tNu;
		mXb = tXb;
		mYb = mNu/kEbeam;
		mW = tW;
		mSector = (Int_t) tSector;
		mXec = tXec;
		mYec = tYec;
		mZec = tZec;
		mPex = tPex;
		mPey = tPey;
		mPez = tPez;
		// define pions variables
		pipP2 = mPx[2]*mPx[2] + mPy[2]*mPy[2] + mPz[2]*mPz[2];
		pipM = TMath::Sqrt(mE[2]*mE[2] - pipP2); // = kMpi
		pimP2 = mPx[3]*mPx[3] + mPy[3]*mPy[3] + mPz[3]*mPz[3];
		pimM = TMath::Sqrt(mE[3]*mE[3] - pimP2); // = kMpi
		pi0Px = mPx[0] + mPx[1];
		pi0Py = mPy[0] + mPy[1];
		pi0Pz = mPz[0] + mPz[1];
		pi0P2 = pi0Px*pi0Px + pi0Py*pi0Py + pi0Pz*pi0Pz;
		pi0CosTheta = (mPx[0]*mPx[1] + mPy[0]*mPy[1] + mPz[0]*mPz[1])/(mE[0]*mE[1]);
		pi0M = TMath::Sqrt(2*mE[0]*mE[1]*(1 - pi0CosTheta));
		pi0E = TMath::Sqrt(pi0M*pi0M + pi0P2);
		// crossed terms
		pippimP = mPx[2]*mPx[3] + mPy[2]*mPy[3] + mPz[2]*mPz[3];
		pippimE = mE[2]*mE[3];
		pippimM = TMath::Sqrt(pipM*pipM + pimM*pimM + 2*(pippimE - pippimP));
		// define omega energy and Z
		wE = mE[0] + mE[1] + mE[2] + mE[3];
		mZ = wE/mNu;
		// define omega momentum and Pt2
		wPx = mPx[0] + mPx[1] + mPx[2] + mPx[3];
		wPy = mPy[0] + mPy[1] + mPy[2] + mPy[3];
		wPz = mPz[0] + mPz[1] + mPz[2] + mPz[3];
		wP2 = wPx*wPx + wPy*wPy + wPz*wPz;
		// define omega PhiPQ
		mPhiPQ = PhiPQ(wPx, wPy, wPz);
		mThetaPQ = ThetaPQ(wPx, wPy, wPz);
		mCosThetaPQ = ((kEbeam - mPez)*wPz - mPex*wPx - mPey*wPy)/(TMath::Sqrt(wP2*(mQ2 + mNu*mNu)));
		// define omega Pt2
		mPt2 = wP2*(1 - mCosThetaPQ*mCosThetaPQ);
		// define omega mass
		wM = TMath::Sqrt(wE*wE - wP2);
		wD = wM - pipM - pimM - pi0M;
		mEvent = (Int_t) tEvent;
		nPip = nPipThisEvent;
		nPim = nPimThisEvent;
		nGamma = nGammaThisEvent;
	      }
	      // and fill
	      tMix->Fill();
	    }
	  }
	}
    */
	// end of condition of candidate
      
      // reset count variables
      nPipThisEvent = 0;
      nPimThisEvent = 0;
      nGammaThisEvent = 0;

      nMCPipThisEvent = 0;
      nMCPimThisEvent = 0;
      nMCGammaThisEvent = 0;

      // sum events
      if ((Int_t) tmc_Event != -9999) nEvents++;
      
     } // end of loop in events

    std::cout << "From a total of " << nEvents << " generated events..." << std::endl;
    std::cout << std::endl;
    std::cout << "  There are at least " << nAtLeastMCOmega << " generated events that have at least one omega particle," << std::endl;
    std::cout << "  we have found the following quantity of generated omegas: " << nMCOmega << "."  << std::endl;
    std::cout << std::endl;
    std::cout << "  And there are at least " << nAtLeastOmega << " reconstructed events that have at least one omega particle," << std::endl;
    std::cout << "  we have found the following quantity of reconstructed omegas: " << nOmega << "."  << std::endl;
    std::cout << std::endl;

  } // end of sim condition
  
  /*
	} // end of loop in events
	
	}
      */
  
  if (!simFlag){
    std::cout << "From a total of " << nEvents << " events." << std::endl;
    std::cout << "There are at least " << nAtLeastOmega << " events that have at least one omega particle," << std::endl;
    std::cout << "we have found the following quantity of omega candidates: " << nOmega << "."  << std::endl;
    std::cout << std::endl;
  }

  /*** Writing tree ***/

  rootFile->Write();
  rootFile->Close();

  std::cout << "File " << outFile << " has been created!" << std::endl;
  
  return 0;
}

/*** Input-related functions ***/

inline int parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./FilterNCombine -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:dS:n:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'd': simFlag = 0; break;
    case 'S': simFlag = 1; setOption = optarg; break;
    case 'n': NjlabDir = optarg; break;	    
    default:
      std::cerr << "Unrecognized argument. Execute ./FilterNCombine -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  // for data type
  if (!simFlag) {
    // ntuple name
    treeName = "ntuple_data";
    // input
    textFile = tmpDir + "/PRU-data-" + targetOption + ".tmp";
    // out
    outDir = dataDir + "/" + targetOption;
  } else if (simFlag) {
    // ntuple name
    treeName = "ntuple_sim";
    // input
    textFile = tmpDir + "/PRU-" + setOption + "-" + targetOption + ".tmp";
    if (setOption == "jlab") textFile = tmpDir + "/PRU-" + setOption + "-" + targetOption + "-" + NjlabDir + ".tmp";
    // out
    outDir = simDir + "/" + setOption + "/" + targetOption;
    if (setOption == "jlab") outDir += "/" + NjlabDir;
  }
  // regardless of the data type
  outFile = outDir + "/comb_out.root";
}

void printUsage() {
  std::cout << "FilterNCombine program." << std::endl;
  std::cout << "It must exist a file /tmp/PRU-[set]-[target].tmp with the location of the input root file to filter." << std::endl;
  std::cout << "Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -t[D, C, Fe, Pb]" << std::endl;
  std::cout << "    filters the respective target" << std::endl;
  std::cout << "    IMPORTANT: D option is only for simulations" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -d" << std::endl;
  std::cout << "    filters data" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine -S[old, usm, jlab]" << std::endl;
  std::cout << "    filters sim for chosen set" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple -n[00,01,02,...]" << std::endl;
  std::cout << "    selects N dir (exclusive and mandatory for -Sjlab option)" << std::endl;
  std::cout << "    (please, maintain numbering scheme!)" << std::endl;
  std::cout << std::endl;
}

void printOptions() {
  std::cout << "Executing FilterNCombine program. The chosen parameters are: " << std::endl;
  std::cout << "  targetOption   = " << targetOption << std::endl;
  std::cout << "  simFlag        = " << simFlag << std::endl;
  std::cout << "  setOption      = " << setOption << std::endl;
  std::cout << "  NjlabDir       = " << NjlabDir << std::endl;
  std::cout << std::endl;
}

/*** Mathematical functions ***/

Float_t CorrectGammaMomentum(Int_t i) {
  // returns the respective corrected momentum component
  // extracted from eta_id.cxx (Orlando Soto)

  Float_t fP[3];
  Float_t fE = tE/0.272; // primitive sampling fraction
  
  Float_t Rt = TMath::Sqrt(tECX*tECX + tECY*tECY);
  Float_t R = TMath::Sqrt(tECX*tECX + tECY*tECY + (tECZ - tZec)*(tECZ - tZec));
  Float_t theta_gam = TMath::ASin(Rt/R);
  Float_t phi_gam = TMath::ATan2(tECY, tECX);

  fP[0] = fE*TMath::Sin(theta_gam)*TMath::Cos(phi_gam);
  fP[1] = fE*TMath::Sin(theta_gam)*TMath::Sin(phi_gam);
  fP[2] = fE*TMath::Cos(theta_gam);

  // (0 -> x, 1 -> y, 2 -> z)
  return fP[i];
}

Float_t PhiPQ(Float_t fPx, Float_t fPy, Float_t fPz) {
  Float_t fPhiPQ;

  // two 3-momentum vectors are defined
  // one for the hadron
  // one for the virtual photon
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-tPex, -tPey, kEbeam - tPez);
  
  // the function Phi() and Theta() converts the vector into spherical coordinates
  // and the function RotateZ(amount) rotates the vector around z-axis a certain amount
  // now, this paragraph turns y-component of the virtual photon vector into 0 and rotates the hadron vector the same amount
  // to have the hadron vector in function of the virtual photon direction
  // if its not clear, try to draw these two vectors in the xy plane
  Float_t Phi_z = TMath::Pi() - virt.Phi();
  virt.RotateZ(Phi_z);
  hadr.RotateZ(Phi_z);

  // the function Angle() returns the angle between two vectors
  // now, take into account that the virtual photon vector is in the y=0 plane
  // again, this paragraph turns the x-component of the virtual photon vector into 0 and rotates the hadron vector the same amount
  // to have the hadron vector in function of the virtual photon direction
  // if its not clear, try to draw these two vectors in the xz plane
  TVector3 unit(0., 0., 1.);
  Float_t Phi_y = virt.Angle(unit);
  virt.RotateY(Phi_y);
  hadr.RotateY(Phi_y);
  
  // finally, it obtains the phi component (in spherical coordinates) of the hadron vector (now in the virtual photon frame of reference)
  // and converts it from radians to degrees
  fPhiPQ = hadr.Phi() * 180./(TMath::Pi());
  
  return fPhiPQ;
}

Float_t ThetaPQ(Float_t fPx, Float_t fPy, Float_t fPz) {
  Float_t fThetaPQ;
  
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-tPex, -tPey, kEbeam - tPez);

  // apparently, the angle between these two vectors is the theta angle
  // and this makes perfect sense if one draws it
  fThetaPQ = virt.Angle(hadr) * 180./(TMath::Pi());

  return fThetaPQ;
}

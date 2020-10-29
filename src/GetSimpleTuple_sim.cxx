/***************************************/
/*  GetSimpleTuple_sim.cxx             */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// developed on October 2020, independent of Analyser

#include "GetSimpleTuple_sim.h"

/*** Options ***/

TString targetOption;
TString rnOption;

/*** Declaration of functions ***/

int parseCommandLine(int argc, char* argv[]);
void printOptions();
void printUsage();

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  printOptions();
  
  // assign options
  TString inputFiles = "recsis" + targetOption + "_" + rnOption + ".root"; // node dir
  TString outputFile = "pruned" + targetOption + "_" + rnOption + ".root"; // node dir
  TString outTitle   = "Simulation of particles";

  /*** DATA STRUCTURES ***/
  
  // output
  sim_e se;
  sim_p sp;

  /*** INPUT ***/
  
  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");

  input->Add(inputFiles);

  // define TIdentificatorV2
  TIdentificatorV2 *t = new TIdentificatorV2(input);
  Int_t nEvents = (Int_t) input->GetEntries();

  /*** OUTPUT ***/

  // define output file
  TFile *rootFile = new TFile(outputFile, "RECREATE", outTitle);

  // define output ntuples
  TTree *tElectrons = new TTree("ntuple_e", "All electrons");
  SetElectronBranches_Sim(tElectrons, se);

  TTree *tParticles = new TTree("ntuple_sim", "Stable particles");  
  SetParticleBranches_Sim(tParticles, sp);

  /*** VECTORS ***/

  // define sorting vectors for gsim
  RVec<Int_t> gsimGamma_row;
  RVec<Int_t> gsimPip_row;
  RVec<Int_t> gsimPim_row;
  
  // define sorting vectors for simrec
  RVec<Int_t> simrecGamma_row;
  RVec<Int_t> simrecPip_row;  
  RVec<Int_t> simrecPim_row;

  /*** START ***/

  // jumps to first readable event (mandatory)
  input->Next();

  // loop around events
  for (Int_t i = 0; i < nEvents; i++) { // nEvents
    
    /*** STEP 1: FIND PARTICLES ***/
    
    if (t->Id(0, 1) == 11) {
      for (Int_t q = 1; q < input->GetNRows("GSIM"); q++) {
        if (t->Id(q, 1) == 211) gsimPip_row.push_back(q);
	else if (t->Id(q, 1) == -211) gsimPim_row.push_back(q);
	else if (t->Id(q, 1) == 22) gsimGamma_row.push_back(q);
      } // end of loop in gsim-particles

      if (input->GetNRows("EVNT") > 0) {
	if (t->GetCategorization(0, "Sim") == "electron") {
	  for (Int_t p = 1; p < input->GetNRows("EVNT"); p++) {
	  if (t->GetCategorization(p, "Sim") == "pi+") simrecPip_row.push_back(p);
	  else if (t->GetCategorization(p, "Sim") == "pi-") simrecPim_row.push_back(p);
	  else if (t->GetCategorization(p, "Sim") == "gamma") simrecGamma_row.push_back(p);
	  } // end of loop in simrec-particles
	} // end of electron-in-simrec condition
      } // end of something-in-EVNT-bank
      
    } // end of electron-in-gsim condition
    
    /*** STEP 2: SORT BY MOMENTUM ***/
    
    gsimPip_row   = SortByMomentum(t, gsimPip_row, 1);
    gsimPim_row   = SortByMomentum(t, gsimPim_row, 1);
    gsimGamma_row = SortByMomentum(t, gsimGamma_row, 1);
    
    simrecPip_row   = SortByMomentum(t, simrecPip_row, 0);
    simrecPim_row   = SortByMomentum(t, simrecPim_row, 0);
    simrecGamma_row = SortByMomentum(t, simrecGamma_row, 0);

    /*** STEP 3: ANGULAR MATCHING ***/

    simrecPip_row   = AngularMatching(t, simrecPip_row, gsimPip_row);
    simrecPim_row   = AngularMatching(t, simrecPim_row, gsimPim_row);
    simrecGamma_row = AngularMatching(t, simrecGamma_row, gsimGamma_row);
    
    /*** STEP 4: FILL ***/

    // electron
    if (t->Id(0, 1) == 11) {
      AssignElectronVar_GSIM(t, se, i, "Sim"); // (TIdentificatorV2, sim_e, evnt, targetOption)
      if (input->GetNRows("EVNT") > 0) {
	if (t->GetCategorization(0, "Sim") != "electron") NullElectronVar_SIMREC(se);
	else AssignElectronVar_SIMREC(t, se, i, "Sim");
      }
      tElectrons->Fill();
    }
    
    // pip
    for (Int_t pip = 0; pip < (Int_t) simrecPip_row.size(); pip++) {
      AssignParticleVar_GSIM(t, sp, gsimPip_row[pip], i, "Sim"); // (TIdentificatorV2, sim_p, row, evnt, targetOption)
      if (simrecPip_row[pip] == -1) NullParticleVar_SIMREC(sp);
      else AssignParticleVar_SIMREC(t, sp, simrecPip_row[pip], i, "Sim");
      tParticles->Fill();
    }
    
    // pim
    for (Int_t pim = 0; pim < (Int_t) simrecPim_row.size(); pim++) {
      AssignParticleVar_GSIM(t, sp, gsimPim_row[pim], i, "Sim"); // (TIdentificatorV2, sim_p, row, evnt, targetOption)
      if (simrecPim_row[pim] == -1) NullParticleVar_SIMREC(sp);
      else AssignParticleVar_SIMREC(t, sp, simrecPim_row[pim], i, "Sim");
      tParticles->Fill();
    }

    // gamma
    for (Int_t gamma = 0; gamma < (Int_t) simrecGamma_row.size(); gamma++) {
      AssignParticleVar_GSIM(t, sp, gsimGamma_row[gamma], i, "Sim"); // (TIdentificatorV2, sim_p, row, evnt, targetOption)
      if (simrecGamma_row[gamma] == -1) NullParticleVar_SIMREC(sp);
      else AssignParticleVar_SIMREC(t, sp, simrecGamma_row[gamma], i, "Sim");
      tParticles->Fill();
    }

    // reset memory
    gsimPip_row.clear();
    gsimPim_row.clear();
    gsimGamma_row.clear();
    
    simrecPip_row.clear();
    simrecPim_row.clear();
    simrecGamma_row.clear();
    
    // next event
    input->Next();
  } // end of loop in events
  
  // write and close output file
  rootFile->Write();
  rootFile->Close();

  std::cout << "File " << outputFile << " has been created!" << std::endl;
  
  return 0;
}

/*** Input/output functions ***/

void printUsage() {
  std::cout << "GetSimpleTuple_sim program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple_sim -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple_sim -t[target]" << std::endl;
  std::cout << "    selects target, which can be: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./GetSimpleTuple_sim -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for sim files = recsis<target>_<run number>.root" << std::endl;
  std::cout << std::endl;
}

int parseCommandLine(int argc, char* argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./bin/GetSimpleTuple_sim -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ht:r:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'r': rnOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./bin/GetSimpleTuple_sim -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void printOptions() {
  std::cout << "Executing GetSimpleTuple_sim program. The chosen parameters are: " << std::endl;
  std::cout << "  targetOption   = " << targetOption << std::endl;
  std::cout << "  rnOption       = " << rnOption << std::endl;
  std::cout << std::endl;
}

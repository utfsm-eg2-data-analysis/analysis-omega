/***************************************/
/*  ToyGST.cxx                         */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

#include "ROOT/RVec.hxx"

using namespace ROOT::VecOps;

/*** Global variables ***/

// options
TString testOption;
TString targetOption;
TString setOption;
TString rnOption;

// to be assigned
Int_t simFlag;
TString inputFile;
TString outDir;
TString outFile;
TString outTitle;
TString analyserOption;

// electron variables for sim
TString varListElectrons_sim = "Q2:W:Nu:Xb:Yb:vxe:vye:vze:Sector:TargType:Px:Py:Pz:P:Betta:Etot:Ein:Eout:vxec:vyec:vzec:XEC:YEC:ZEC:StatDC:DCStatus:StatEC:ECStatus:TimeEC:PathEC:Chi2EC:StatSC:SCStatus:TimeSC:PathSC:StatCC:CCStatus:Chi2CC:Status:evnt:mc_Q2:mc_W:mc_Nu:mc_Xb:mc_Yb:mc_vxe:mc_vye:mc_vze:mc_Sector:mc_TargType:mc_Px:mc_Py:mc_Pz:mc_P:mc_Betta"; // ready!
Float_t varElectrons_sim[55];

// particle variables for sim
TString varListParticles_sim = "Q2:W:Nu:Xb:Yb:vxe:vye:vze:SectorEl:TargType:Pex:Pey:Pez:Pe:BettaEl:Etote:Eine:Eoute:vxec:vyec:vzec:XECe:YECe:ZECe:StatDCEl:DCStatusEl:StatECEl:ECStatusEl:TimeECEl:PathECEl:Chi2ECEl:StatSCEl:SCStatusEl:TimeSCEl:PathSCEl:StatCCEl:CCStatusEl:Chi2CCEl:StatusEl:Zh:ThetaPQ:Pt2:Pl2:PhiPQ:Mx2:T:vxh:vyh:vzh:Sector:Px:Py:Pz:P:Betta:Mass2:Etot:Ein:Eout:XEC:YEC:ZEC:pid:T4:deltaZ:StatDC:DCStatus:StatEC:ECStatus:TimeEC:PathEC:Chi2EC:StatSC:SCStatus:TimeSC:PathSC:StatCC:CCStatus:Chi2CC:Status:evnt:mc_Q2:mc_W:mc_Nu:mc_Xb:mc_Yb:mc_vxe:mc_vye:mc_vze:mc_SectorEl:mc_TargType:mc_Pex:mc_Pey:mc_Pez:mc_Pe:mc_BettaEl:mc_Zh:mc_ThetaPQ:mc_Pt2:mc_Pl2:mc_PhiPQ:mc_Mx2:mc_T:mc_vxh:mc_vyh:mc_vzh:mc_Sector:mc_Px:mc_Py:mc_Pz:mc_P:mc_Betta:mc_Mass2:mc_pid:mc_deltaZ";
Float_t varParticles_sim[115];

// electron variables for data
TString varListElectrons_data = "Q2:W:Nu:Xb:Yb:vxe:vye:vze:Sector:TargType:Px:Py:Pz:P:Betta:Etot:Ein:Eout:vxec:vyec:vzec:XEC:YEC:ZEC:StatDC:DCStatus:StatEC:ECStatus:TimeEC:PathEC:Chi2EC:StatSC:SCStatus:TimeSC:PathSC:StatCC:CCStatus:Chi2CC:Status:evnt";
Float_t varElectrons_data[40];

// particle variables for data
TString varListParticles_data = "Q2:W:Nu:Xb:Yb:vxe:vye:vze:SectorEl:TargType:Pex:Pey:Pez:Pe:BettaEl:Etote:Eine:Eoute:vxec:vyec:vzec:XECe:YECe:ZECe:StatDCEl:DCStatusEl:StatECEl:ECStatusEl:TimeECEl:PathECEl:Chi2ECEl:StatSCEl:SCStatusEl:TimeSCEl:PathSCEl:StatCCEl:CCStatusEl:Chi2CCEl:StatusEl:Zh:ThetaPQ:Pt2:Pl2:PhiPQ:Mx2:T:vxh:vyh:vzh:Sector:Px:Py:Pz:P:Betta:Mass2:Etot:Ein:Eout:XEC:YEC:ZEC:pid:T4:deltaZ:StatDC:DCStatus:StatEC:ECStatus:TimeEC:PathEC:Chi2EC:StatSC:SCStatus:TimeSC:PathSC:StatCC:CCStatus:Chi2CC:Status:evnt";
Float_t varParticles_data[81];

// define ntuples as global
TNtuple *tElectrons;
TNtuple *tParticles;

// define TIdentificator object as global
TIdentificator *t;

/*** Declaration of functions ***/

int parseCommandLine(int argc, char* argv[]);
void assignOptions();
void printOptions();
void printUsage();

Int_t ChooseElectron(RVec<Int_t> Electron_row, Int_t kind);
RVec<Int_t> SortByMomentum(RVec<Int_t> row, Int_t kind);
Bool_t AngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row, Int_t n, Int_t m, Float_t angle);
RVec<Int_t> NewAngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row);

void PrintAll(Int_t ge, RVec<Int_t> gsimGamma_row, RVec<Int_t> gsimPip_row, RVec<Int_t> gsimPim_row,
	      Int_t ke, RVec<Int_t> simrecGamma_row, RVec<Int_t> simrecPip_row, RVec<Int_t> simrecPim_row);
void PrintAll_Data(Int_t ke, RVec<Int_t> dataGamma_row, RVec<Int_t> dataPip_row, RVec<Int_t> dataPim_row);

void FillElectron_Sim(Int_t evnt, Int_t ge, Int_t ke); // , TNtuple* tElectrons
void FillParticles_Sim(Int_t evnt, Int_t ge, RVec<Int_t> gsim_row, Int_t ke, RVec<Int_t> simrec_row); // , TNtuple* tParticles

void FillElectron_Data(Int_t evnt, Int_t ke); // , TNtuple* tElectrons
void FillParticles_Data(Int_t evnt, Int_t ke, RVec<Int_t> data_row); // , TNtuple* tParticles

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  printOptions();

  // dir structure, just in case
  if (setOption != "jlab") system("mkdir -p " + outDir);
  
  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");

  input->Add(inputFile);

  // define TIdentificator
  t = new TIdentificator(input);
  Int_t nEvents = (Int_t) input->GetEntries();

  /*** SETUP OUTPUT ***/

  // define output file
  TFile *rootFile = new TFile(outFile, "RECREATE", outTitle);

  // setup ntuples
  if (simFlag) {
    tElectrons = new TNtuple("ntuple_e", "All electrons", varListElectrons_sim);
    tParticles = new TNtuple("ntuple_sim", "Stable particles", varListParticles_sim);
  } else if (!simFlag) {
    tElectrons = new TNtuple("ntuple_e", "All electrons", varListElectrons_data);
    tParticles = new TNtuple("ntuple_data", "Stable particles", varListParticles_data);
  }
  
  // define sorting vectors for gsim
  RVec<Int_t> gsimElectron_row;
  RVec<Int_t> gsimGamma_row;
  RVec<Int_t> gsimPip_row;
  RVec<Int_t> gsimPim_row;
  
  // define sorting vectors for simrec
  RVec<Int_t> simrecElectron_row;  
  RVec<Int_t> simrecGamma_row;
  RVec<Int_t> simrecPip_row;  
  RVec<Int_t> simrecPim_row;

  // define sorting vectors for data
  RVec<Int_t> dataElectron_row;
  RVec<Int_t> dataGamma_row;
  RVec<Int_t> dataPip_row;
  RVec<Int_t> dataPim_row;

  // define DIS-electron row
  Int_t ge = -1; // for gsim
  Int_t ke = -1; // for data and simrec

  // jumps to first readable event, mandatory!
  input->Next();

  // loop around events
  for (Int_t k = 0; k < nEvents; k++) { // nEvents
    
    // simulation condition
    if (simFlag) {

      // loop 1 in generated and reconstructed particles to search for all reconstructed electrons
      for (Int_t p = 0; p < input->GetNRows("GSIM"); p++) {

	/*** GENERATED ELECTRONS ***/

	if (t->Id(p,1) == 11) gsimElectron_row.push_back(p);
	
	/*** RECONSTRUCTED ELECTRONS ***/

	if (p < input->GetNRows("EVNT")) { // important condition, prev seg fault
	  if (t->GetCategorization(p, 0, analyserOption) == "electron") simrecElectron_row.push_back(p);
	}
	
      } // end of loop 1

      /*** DIS ELECTRON FOR GENERATED ***/

      // if there is more than one electron in generated!
      if ((Int_t) gsimElectron_row.size() > 1) {
        ge = ChooseElectron(gsimElectron_row, 1);
      } else if ((Int_t) gsimElectron_row.size() == 1) {
	ge = gsimElectron_row[0];
      } else {
	ge = -1; // prevent seg fault
      }
      
      /*** DIS ELECTRON FOR RECONSTRUCTED ***/
	    
      // if there is more than one electron in reconstructed!
      if ((Int_t) simrecElectron_row.size() > 1) {
        ke = ChooseElectron(simrecElectron_row, 0);
      } else if ((Int_t) simrecElectron_row.size() == 1) {
	ke = simrecElectron_row[0];
      } else {
	ke = -1; // prevent seg fault
      }

      // loop 2 only if a generated electron was found!
      if (ge >= 0) {
	for (Int_t q = 0; q < input->GetNRows("GSIM"); q++) {

	  /*** GENERATED PARTICLES ***/
	  
	  if (q != ge) { // important condition
	    if (t->Id(q,1) == 22) gsimGamma_row.push_back(q);
	    else if (t->Id(q,1) == 211) gsimPip_row.push_back(q);
	    else if (q != ge && t->Id(q,1) == -211) gsimPim_row.push_back(q);
	  }

	  /*** RECONSTRUCTED PARTICLES ***/

	  if (ke >= 0 && q != ke && q < input->GetNRows("EVNT")) { // important conditions, prev seg fault	  
	    if (t->GetCategorization(q, ke, analyserOption) == "gamma") simrecGamma_row.push_back(q);
	    else if (t->GetCategorization(q, ke, analyserOption) == "pi+") simrecPip_row.push_back(q);
	    else if (t->GetCategorization(q, ke, analyserOption) == "pi-") simrecPim_row.push_back(q);
	  }
	  
	} // end of loop 2
      } // end of important condition-gsim
            
      /*** SORTING BY PARTICLE AND MOMENTUM ***/

      // gsim
      gsimGamma_row = SortByMomentum(gsimGamma_row, 1);
      gsimPip_row   = SortByMomentum(gsimPip_row, 1);
      gsimPim_row   = SortByMomentum(gsimPim_row, 1);

      // simrec
      simrecGamma_row = SortByMomentum(simrecGamma_row, 0);
      simrecPip_row   = SortByMomentum(simrecPip_row, 0);
      simrecPim_row   = SortByMomentum(simrecPim_row, 0);
            
      /*** ANGULAR MATCHING ***/

      simrecGamma_row = NewAngularMatching(simrecGamma_row, gsimGamma_row);
      simrecPip_row   = NewAngularMatching(simrecPip_row, gsimPip_row);
      simrecPim_row   = NewAngularMatching(simrecPim_row, gsimPim_row);

      /*** FILLING ***/
      
      FillElectron_Sim(k, ge, ke);
      FillParticles_Sim(k, ge, gsimGamma_row, ke, simrecGamma_row);
      FillParticles_Sim(k, ge, gsimPip_row, ke, simrecPip_row);
      FillParticles_Sim(k, ge, gsimPim_row, ke, simrecPim_row);
      
      // reset memory
      gsimElectron_row.clear();
      gsimGamma_row.clear();
      gsimPip_row.clear();
      gsimPim_row.clear();
      ge = -1;
      
      simrecElectron_row.clear();
      simrecGamma_row.clear();
      simrecPip_row.clear();
      simrecPim_row.clear();
      ke = -1;
      
    } else if (!simFlag) { // end of simulation condition & beginning of data condition

      /*** DATA ***/
      
      // loop 1 in detected particles
      for (Int_t p = 0; p < input->GetNRows("EVNT"); p++) {

	/*** DATA ELECTRONS ***/
	
	if (t->GetCategorization(p, 0, analyserOption) == "electron") {
	  dataElectron_row.push_back(p);
	}
      } // end of loop 1
      
      // just in case that there is more than one electron in data!
      if ((Int_t) dataElectron_row.size() > 1) {
        ke = ChooseElectron(dataElectron_row, 0);
      } else if ((Int_t) dataElectron_row.size() == 1) {
	ke = dataElectron_row[0];
      } else { // seg fault when no electron was found
	ke = -1;
      }

      // loop 2 in detected particles only when an electron was detected!
      if (ke >= 0) {
	for (Int_t q = 0; q < input->GetNRows("EVNT"); q++) {
	  
	  /*** DATA PARTICLES ***/
	  
	  if (q != ke) { // important condition
	    if (t->GetCategorization(q, ke, analyserOption) == "gamma") dataGamma_row.push_back(q);
	    else if (t->GetCategorization(q, ke, analyserOption) == "pi+") dataPip_row.push_back(q);
	    else if (t->GetCategorization(q, ke, analyserOption) == "pi-") dataPim_row.push_back(q);
	  }
	
	} // end of loop 2 in detected particles
      }

      /*** FILLING ***/
      
      FillElectron_Data(k, ke);
      FillParticles_Data(k, ke, dataGamma_row);
      FillParticles_Data(k, ke, dataPip_row);
      FillParticles_Data(k, ke, dataPim_row);
            
      // reset memory
      dataElectron_row.clear();
      dataGamma_row.clear();      
      dataPip_row.clear();
      dataPim_row.clear();
      ke = -1;
      
    } // end of data condition
    
    /*** NEXT EVENT! ***/

    input->Next();
    
  } // end of loop in events

  // write and close output file
  rootFile->Write();
  rootFile->Close();
  
  return 0;
}

/*** Input/output functions ***/

void printUsage() {
  std::cout << "ToyGST program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./ToyGST -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./ToyGST -t[target]" << std::endl;
  std::cout << "    selects target: D, C, Fe, Pb" << std::endl;
  std::cout << "    IMPORTANT: D option is only for simulations" << std::endl;
  std::cout << std::endl;
  std::cout << "./ToyGST -d" << std::endl;
  std::cout << "    gets tuples from data" << std::endl;
  std::cout << std::endl;
  std::cout << "./ToyGST -S[old,usm,jlab]" << std::endl;
  std::cout << "    gets tuples from set of simulations" << std::endl;
  std::cout << std::endl;
  std::cout << "./ToyGST -n[00,01,02,...]" << std::endl;
  std::cout << "    selects N dir (exclusive and mandatory for -Sjlab option)" << std::endl;
  std::cout << "    (please, maintain numbering scheme!)" << std::endl;
  std::cout << std::endl;
  std::cout << "./ToyGST -r[0001,...,9999]" << std::endl;
  std::cout << "    selects run number (mandatory for all!)" << std::endl;
  std::cout << "    numbering scheme: 00,...,99     for jlab" << std::endl;
  std::cout << "                      0000,...,1XXX for old/usm" << std::endl;
  std::cout << "                      XXXXX         for data" << std::endl;
  std::cout << std::endl;
}

int parseCommandLine(int argc, char* argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./bin/ToyGST -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ht:dS:r:T:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': targetOption = optarg; break;
    case 'S': simFlag = 1; setOption = optarg; break;
    case 'd': simFlag = 0; break;
    case 'r': rnOption = optarg; break;
    case 'T': testOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./bin/ToyGST -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  // first, check for testOption... to run at HP VM
  if (testOption == "Sim") {
    simFlag = 1;
    inputFile = "/home/borquez/Downloads/recsisC_0028.root";
    outDir = proDir + "/out/ToyGST";
    outFile = outDir + "/test_sim.root";
    outTitle = "Simulation of particles";
    analyserOption = testOption;
  } else if (testOption == "C") {
    simFlag = 0;
    inputFile = "/home/borquez/Downloads/clas_42011_00.pass2.root";
    outDir = proDir + "/out/ToyGST";
    outFile = outDir + "/test_data.root";
    outTitle = "Data of particles";
    analyserOption = testOption;
  } else {
    // data type
    if (!simFlag) {
      inputFile = rawDataDir_utfsm + "/clas_" + rnOption + "_*.pass2.root"; // *: all files of the rn
      analyserOption = targetOption;
      outDir = proDir + "/out/ToyGST/data/" + targetOption;
      outTitle = "Data of particles";
    } else if (simFlag) {
      analyserOption = "Sim";
      outTitle = "Simulation of particles";
      outDir = proDir + "/out/ToyGST/" + setOption + "/" + targetOption;
      if (setOption == "jlab") {
	inputFile = "recsis" + targetOption + "_" + rnOption + ".root"; // from node dir
	outDir = ""; // just in case
      } else if (setOption == "old" || setOption == "usm") {
	inputFile = rawSimDir_utfsm + "/" + setOption + "/" + targetOption + "/recsis" + targetOption + "_" + rnOption + "*.root"; // *: convenient amount of files
      }
    }
    // no longer independent of the data type
    if (setOption == "jlab") {
      outFile = "pruned" + targetOption + "_" + rnOption + ".root"; // into node dir
    } else {
      outFile = outDir + "/pruned" + targetOption + "_" + rnOption + ".root";
    }
  } // end of no-test condition
}

void printOptions() {
  std::cout << "Executing ToyGST program. The chosen parameters are: " << std::endl;
  std::cout << "  testOption     = " << testOption << std::endl;
  std::cout << "  targetOption   = " << targetOption << std::endl;
  std::cout << "  simFlag        = " << simFlag << std::endl;
  std::cout << "  setOption      = " << setOption << std::endl;
  std::cout << "  rnOption       = " << rnOption << std::endl;
  std::cout << "  inputFile      = " << inputFile << std::endl;
  std::cout << "  analyserOption = " << analyserOption << std::endl;
  std::cout << std::endl;
}

/*** Vector functions ***/

RVec<Int_t> SortByMomentum(RVec<Int_t> row, Int_t kind) {

  // returns a new "row2" where row values are sorted by their respective momentum
  // from lower to higher momentum

  // Argsort() creates an indices-vector with the indices sorted by the input-vector values
  // Take(input-vector, indices-vector) creates a sorted-vector by moving all input-vector indices to match the order assigned by the indices-vector

  // but first, fill the momentum vector
  RVec<Float_t> momentum;
  for (Int_t m = 0; m < (Int_t) row.size(); m++) {
    momentum.push_back(t->Momentum(row[m],kind));
  }
  
  RVec<Int_t> indices = Argsort(momentum);
  RVec<Int_t> row2 = Take(row, indices);

  return row2;
}

void PrintAll(Int_t ge, RVec<Int_t> gsimGamma_row, RVec<Int_t> gsimPip_row, RVec<Int_t> gsimPim_row,
	      Int_t ke, RVec<Int_t> simrecGamma_row, RVec<Int_t> simrecPip_row, RVec<Int_t> simrecPim_row) {

  // debug function
  // existencial question: what happens if there are more simrec gammas than gsim gammas?
  
  if (ge >= 0) {
    std::cout << std::left
	      << std::setw(14) << "gsim_row"
	      << std::setw(14) << "gsim_categ"
	      << std::setw(14) << "gsim_P"
	      << std::setw(4)  << "||"
	      << std::setw(14) << "simrec_row"
	      << std::setw(14) << "simrec_categ"
	      << std::setw(14) << "simrec_P" << std::endl;

    // the electron
    std::cout << std::left
	      << std::setw(14) << ge
	      << std::setw(14) << particleName(t->Id(ge, 1))
	      << std::setw(14) << t->Momentum(ge, 1)
	      << std::setw(4)  << "||";
    if (ke >= 0) {
      std::cout << std::setw(14) << ke
		<< std::setw(14) << t->GetCategorization(ke, 0, analyserOption)
		<< std::setw(14) << t->Momentum(ke, 0) << std::endl;
    } else {
      std::cout << std::setw(14) << "-9999"
		<< std::setw(14) << "-9999"
		<< std::setw(14) << "-9999" << std::endl;
    }

    // gammas
    for (Int_t j = 0; j < (Int_t) gsimGamma_row.size(); j++) {
      std::cout << std::left
		<< std::setw(14) << gsimGamma_row[j]
		<< std::setw(14) << particleName(t->Id(gsimGamma_row[j], 1))
		<< std::setw(14) << t->Momentum(gsimGamma_row[j], 1)
		<< std::setw(4) << "||";
      if (j < (Int_t) simrecGamma_row.size() && simrecGamma_row[j] != -1) {
	std::cout << std::setw(14) << simrecGamma_row[j]
		  << std::setw(14) << t->GetCategorization(simrecGamma_row[j], ke, analyserOption)
		  << std::setw(14) << t->Momentum(simrecGamma_row[j], 0) << std::endl;
      } else {
	std::cout << std::setw(14) << "-9999"
		  << std::setw(14) << "-9999"
		  << std::setw(14) << "-9999" << std::endl;
      }
    }

    // pip
    for (Int_t j = 0; j < (Int_t) gsimPip_row.size(); j++) {
      std::cout << std::left
		<< std::setw(14) << gsimPip_row[j]
		<< std::setw(14) << particleName(t->Id(gsimPip_row[j], 1))
		<< std::setw(14) << t->Momentum(gsimPip_row[j], 1)
		<< std::setw(4)  << "||";
      if (j < (Int_t) simrecPip_row.size() && simrecPip_row[j] != -1) {
	std::cout << std::setw(14) << simrecPip_row[j]
		  << std::setw(14) << t->GetCategorization(simrecPip_row[j], ke, analyserOption)
		  << std::setw(14) << t->Momentum(simrecPip_row[j], 0) << std::endl;
      } else {
	std::cout << std::setw(14) << "-9999"
		  << std::setw(14) << "-9999"
		  << std::setw(14) << "-9999" << std::endl;
      }
    }

    // pim
    for (Int_t j = 0; j < (Int_t) gsimPim_row.size(); j++) {
      std::cout << std::left
		<< std::setw(14) << gsimPim_row[j]
		<< std::setw(14) << particleName(t->Id(gsimPim_row[j], 1))
		<< std::setw(14) << t->Momentum(gsimPim_row[j], 1)
		<< std::setw(4)  << "||";
      if (j < (Int_t) simrecPim_row.size() && simrecPim_row[j] != -1) {
	std::cout << std::setw(14) << simrecPim_row[j]
		  << std::setw(14) << t->GetCategorization(simrecPim_row[j], ke, analyserOption)
		  << std::setw(14) << t->Momentum(simrecPim_row[j], 0) << std::endl;
      } else {
	std::cout << std::setw(14) << "-9999"
		  << std::setw(14) << "-9999"
		  << std::setw(14) << "-9999" << std::endl;
      }
    }
  }
  std::cout << std::endl;
}

void PrintAll_Data(Int_t ke, RVec<Int_t> dataGamma_row, RVec<Int_t> dataPip_row, RVec<Int_t> dataPim_row) {
  
  // debug function

  // first line
  std::cout << std::left
	    << std::setw(14) << "data_row"
	    << std::setw(14) << "data_categ"
	    << std::setw(14) << "data_P" << std::endl;

  
  // the electron
  if (ke >= 0) {
    std::cout << std::left
	      << std::setw(14) << ke
	      << std::setw(14) << t->GetCategorization(ke,0,analyserOption)
	      << std::setw(14) << t->Momentum(ke, 0) << std::endl;
  
    // gammas
    for (Int_t j = 0; j < (Int_t) dataGamma_row.size(); j++) {
      std::cout << std::left
		<< std::setw(14) << dataGamma_row[j]
		<< std::setw(14) << t->GetCategorization(dataGamma_row[j],ke,analyserOption)
		<< std::setw(14) << t->Momentum(dataGamma_row[j], 0) << std::endl;
    }
    
    // pip
    for (Int_t j = 0; j < (Int_t) dataPip_row.size(); j++) {
      std::cout << std::left
		<< std::setw(14) << dataPip_row[j]
		<< std::setw(14) << t->GetCategorization(dataPip_row[j],ke,analyserOption)
		<< std::setw(14) << t->Momentum(dataPip_row[j], 0) << std::endl;
    }
    
    // pim
    for (Int_t j = 0; j < (Int_t) dataPim_row.size(); j++) {
      std::cout << std::left
		<< std::setw(14) << dataPim_row[j]
		<< std::setw(14) << t->GetCategorization(dataPim_row[j],ke,analyserOption)
		<< std::setw(14) << t->Momentum(dataPim_row[j], 0) << std::endl;
    }
  }
 
  std::cout << std::endl;
}
  
Bool_t AngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row, Int_t n, Int_t m, Float_t angle) {

  // returns true if the respective n-row for simrec and m-row for gsim meet the angular matching condition

  // define two TVector3
  TVector3 simrec_Pvec(t->Px(simrec_row[n],0), t->Py(simrec_row[n],0), t->Pz(simrec_row[n],0));
  TVector3 gsim_Pvec(t->Px(gsim_row[m],1), t->Py(gsim_row[m],1), t->Pz(gsim_row[m],1));
  
  return (360*simrec_Pvec.Angle(gsim_Pvec)/(2*TMath::Pi()) < angle);
}

RVec<Int_t> NewAngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row) {

  // OBJECTIVE: match the simrec rows with the gsim rows, under angular matching
  // returns a new "simrec_row2" that has these features:
  // - the same size of the "gsim_row" vector
  // - simrec rows in the same position than the matched gsim vector
  // - empty rows are filled with "-1"

  // define vector sizes - loop length
  Int_t N = (Int_t) simrec_row.size();
  Int_t M = (Int_t) gsim_row.size();
  
  // define output vector
  RVec<Int_t> simrec_row2;
  simrec_row2.resize(M, -1); // M ints with value -1
  
  RVec<Int_t> simrec_notused;
  RVec<Int_t> gsim_used;

  Bool_t wasUsed;
  
  // n, m are vectors' positions
  for (Int_t n = 0; n < N; n++) {
    for (Int_t m = 0; m < M; m++) {

      // std::find function returns an iterator to the first element in the range ["first","last"[ that compares equal to "value"
      // if no such element is found, the function returns "last"
      wasUsed = (std::find(gsim_used.begin(), gsim_used.end(), gsim_row[m]) != gsim_used.end());
      
      if (AngularMatching(simrec_row, gsim_row, n, m, 10) && !wasUsed) {
	simrec_row2[m] = simrec_row[n];   // assign to output vector
	gsim_used.push_back(gsim_row[m]); // add gsim_row to gsim_used
	m = M;                            // jump to next iteration in n
      } else if (m == M-1) { // last m for a certain n, and haven't found pair yet
	simrec_notused.push_back(simrec_row[n]);
      }
      
    } // end of gsim loop
  } // end of simrec loop

  // fill output vector with not-used simrec_row
  if ((Int_t) simrec_notused.size() != 0) {
    Int_t counter = 0;
    for (Int_t q = 0; q < M; q++) {
      if (simrec_row2[q] == -1 && counter < (Int_t) simrec_notused.size()) {
	simrec_row2[q] = simrec_notused[counter]; // assign first element found in not-used vector
	counter++;                                // jump to next element in not-used vector
      }
    }
  }
  
  return simrec_row2;
}

Int_t ChooseElectron(RVec<Int_t> Electron_row, Int_t kind) {

  // selects the first electron that meet DIS requirements: Q2 > 1 and W > 1

  Int_t DISrow = -1;
  
  for (Int_t i = 0; i < (Int_t) Electron_row.size(); i++) {
    if (DISrow < 0 && t->Q2(Electron_row[i], kind) > 1. && t->W(Electron_row[i], kind) > 2.) {
      DISrow = Electron_row[i];
    } 
  }

  // if none is found, then selects the one with bigger momentum
  
  if (DISrow < 0) {
    Double_t highestMomentum = 0.;
    for (Int_t i = 0; i < (Int_t) Electron_row.size(); i++) {
      if (t->Momentum(Electron_row[i], kind) > highestMomentum) {
	highestMomentum = t->Momentum(Electron_row[i], kind);
	DISrow = Electron_row[i];
      }
    }
  }
  
  return DISrow;
}

void FillElectron_Sim(Int_t evnt, Int_t ge, Int_t ke) {

  // 15 vars depend on kind: 5 electron vars, 3 position, 4 momentum, 1 sector, 1 targtype, 1 betta
  
  TVector3 *vert;

  if (ge >= 0) {

    // simrec
    if (ke >= 0) {
      varElectrons_sim[0] = t->Q2(ke,0);
      varElectrons_sim[1] = t->W(ke,0);
      varElectrons_sim[2] = t->Nu(ke,0);
      varElectrons_sim[3] = t->Xb(ke,0);
      varElectrons_sim[4] = t->Yb(ke,0);
      varElectrons_sim[5] = t->X(ke,0);
      varElectrons_sim[6] = t->Y(ke,0);
      varElectrons_sim[7] = t->Z(ke,0);
      varElectrons_sim[8] = t->Sector(ke,0);
      varElectrons_sim[9] = t->ElecVertTarg(ke,0);
      varElectrons_sim[10] = t->Px(ke,0);
      varElectrons_sim[11] = t->Py(ke,0);
      varElectrons_sim[12] = t->Pz(ke,0);
      varElectrons_sim[13] = t->Momentum(ke,0);
      varElectrons_sim[14] = t->Betta(ke,0);
      varElectrons_sim[15] = t->Etot(ke);
      varElectrons_sim[16] = t->Ein(ke);
      varElectrons_sim[17] = t->Eout(ke);
      vert = t->GetCorrectedVert(ke);
      Float_t vxec = vert->X();
      Float_t vyec = vert->Y();
      Float_t vzec = vert->Z();
      varElectrons_sim[18] = vxec;
      varElectrons_sim[19] = vyec;
      varElectrons_sim[20] = vzec;
      varElectrons_sim[21] = t->XEC(ke);
      varElectrons_sim[22] = t->YEC(ke);
      varElectrons_sim[23] = t->ZEC(ke);
      varElectrons_sim[24] = t->StatDC(ke); // DC
      varElectrons_sim[25] = t->DCStatus(ke);
      varElectrons_sim[26] = t->StatEC(ke); // EC
      varElectrons_sim[27] = t->ECStatus(ke);
      varElectrons_sim[28] = t->TimeEC(ke);
      varElectrons_sim[29] = t->PathEC(ke);
      varElectrons_sim[30] = t->Chi2EC(ke);
      varElectrons_sim[31] = t->StatSC(ke); // SC
      varElectrons_sim[32] = t->SCStatus(ke);
      varElectrons_sim[33] = t->TimeSC(ke);
      varElectrons_sim[34] = t->PathSC(ke);
      varElectrons_sim[35] = t->StatCC(ke); // CC
      varElectrons_sim[36] = t->CCStatus(ke);
      varElectrons_sim[37] = t->Chi2CC(ke);
      varElectrons_sim[38] = t->Status(ke); // Status
    } else {
      for (Int_t q = 0; q < 39; q++) varElectrons_sim[q] = -9999.;
    }
    
    // gsim
    varElectrons_sim[39] = evnt;
    varElectrons_sim[40] = t->Q2(ge,1);
    varElectrons_sim[41] = t->W(ge,1);
    varElectrons_sim[42] = t->Nu(ge,1);
    varElectrons_sim[43] = t->Xb(ge,1);
    varElectrons_sim[44] = t->Yb(ge,1);
    varElectrons_sim[45] = t->X(ge,1);
    varElectrons_sim[46] = t->Y(ge,1);
    varElectrons_sim[47] = t->Z(ge,1);
    varElectrons_sim[48] = t->Sector(ge,1);
    varElectrons_sim[49] = t->ElecVertTarg(ge,1);
    varElectrons_sim[50] = t->Px(ge,1);
    varElectrons_sim[51] = t->Py(ge,1);
    varElectrons_sim[52] = t->Pz(ge,1);
    varElectrons_sim[53] = t->Momentum(ge,1);
    varElectrons_sim[54] = t->Betta(ge,1);

    tElectrons->Fill(varElectrons_sim);
  }
    
  // clear array
  for (Int_t q = 0; q < 55; q++) varElectrons_sim[q] = -9999.;
}

void FillParticles_Sim(Int_t evnt, Int_t ge, RVec<Int_t> gsim_row, Int_t ke, RVec<Int_t> simrec_row) {

  TVector3 *vert;
  Float_t mass;
  Int_t g;
  Int_t k;
  
  // there must be an electron to define the event
  if (ge >= 0) {
    
    for (Int_t j = 0; j < (Int_t) gsim_row.size(); j++) {
      
      // simrec first
      if (ke >= 0 && simrec_row[j] != -1 && j < (Int_t) simrec_row.size()) {
	k = simrec_row[j]; // to improve readability
	// rec electron
	varParticles_sim[0] = t->Q2(ke,0); 
	varParticles_sim[1] = t->W(ke,0);
	varParticles_sim[2] = t->Nu(ke,0);
	varParticles_sim[3] = t->Xb(ke,0);
	varParticles_sim[4] = t->Yb(ke,0);
	varParticles_sim[5] = t->X(ke,0);
	varParticles_sim[6] = t->Y(ke,0);
	varParticles_sim[7] = t->Z(ke,0);
	varParticles_sim[8] = t->Sector(ke,0);
	varParticles_sim[9] = t->ElecVertTarg(ke,0);
	varParticles_sim[10] = t->Px(ke,0);
	varParticles_sim[11] = t->Py(ke,0);
	varParticles_sim[12] = t->Pz(ke,0);
	varParticles_sim[13] = t->Momentum(ke,0);
	varParticles_sim[14] = t->Betta(ke,0);
	varParticles_sim[15] = t->Etot(ke);
	varParticles_sim[16] = t->Ein(ke);
	varParticles_sim[17] = t->Eout(ke);
	vert = t->GetCorrectedVert(ke);
	Float_t vxec = vert->X();
	Float_t vyec = vert->Y();
	Float_t vzec = vert->Z();
	varParticles_sim[18] = vxec;
	varParticles_sim[19] = vyec;
	varParticles_sim[20] = vzec;
	varParticles_sim[21] = t->XEC(ke);
	varParticles_sim[22] = t->YEC(ke);
	varParticles_sim[23] = t->ZEC(ke);
	varParticles_sim[24] = t->StatDC(ke); // DC
	varParticles_sim[25] = t->DCStatus(ke);
	varParticles_sim[26] = t->StatEC(ke); // EC
	varParticles_sim[27] = t->ECStatus(ke);
	varParticles_sim[28] = t->TimeEC(ke);
	varParticles_sim[29] = t->PathEC(ke);
	varParticles_sim[30] = t->Chi2EC(ke);
	varParticles_sim[31] = t->StatSC(ke); // SC
	varParticles_sim[32] = t->SCStatus(ke);
	varParticles_sim[33] = t->TimeSC(ke);
	varParticles_sim[34] = t->PathSC(ke);
	varParticles_sim[35] = t->StatCC(ke); // CC
	varParticles_sim[36] = t->CCStatus(ke);
	varParticles_sim[37] = t->Chi2CC(ke);
	varParticles_sim[38] = t->Status(ke); // Status
	// rec particle
	if (t->GetCategorization(k,ke,analyserOption) == "pi+" || t->GetCategorization(k,ke,analyserOption) == "pi-") mass = 0.1396;
	else if (t->GetCategorization(k,ke,analyserOption) == "gamma") mass = 0.;
	varParticles_sim[39] = t->Zh(k,ke,0,mass);
	varParticles_sim[40] = t->ThetaPQ(k,ke,0);
	varParticles_sim[41] = t->Pt2(k,ke,0);
	varParticles_sim[42] = t->Pl2(k,ke,0);
	varParticles_sim[43] = t->PhiPQ(k,ke,0);
	varParticles_sim[44] = t->Mx2(k,ke,0,mass);
	varParticles_sim[45] = t->T(k,ke,0,mass);
	varParticles_sim[46] = t->X(k,0);
	varParticles_sim[47] = t->Y(k,0);
	varParticles_sim[48] = t->Z(k,0);
	varParticles_sim[49] = t->Sector(k,0);
	varParticles_sim[50] = t->Px(k,0);
	varParticles_sim[51] = t->Py(k,0);
	varParticles_sim[52] = t->Pz(k,0);
	varParticles_sim[53] = t->Momentum(k,0);
	varParticles_sim[54] = t->Betta(k,0);
	varParticles_sim[55] = t->Mass2(k,0);
	varParticles_sim[56] = t->Etot(k);
	varParticles_sim[57] = t->Ein(k);
	varParticles_sim[58] = t->Eout(k);
	varParticles_sim[59] = t->XEC(k);
	varParticles_sim[60] = t->YEC(k);
	varParticles_sim[61] = t->ZEC(k);
	varParticles_sim[62] = particleID(t->GetCategorization(k,ke,analyserOption));
	varParticles_sim[63] = t->TimeCorr4(k,ke,mass);
	varParticles_sim[64] = t->Z(k,0) - t->Z(ke,0);
	varParticles_sim[65] = t->StatDC(k); // DC
	varParticles_sim[66] = t->DCStatus(k);
	varParticles_sim[67] = t->StatEC(k); // EC
	varParticles_sim[68] = t->ECStatus(k);
	varParticles_sim[69] = t->TimeEC(k);
	varParticles_sim[70] = t->PathEC(k);
	varParticles_sim[71] = t->Chi2EC(k);
	varParticles_sim[72] = t->StatSC(k); // SC
	varParticles_sim[73] = t->SCStatus(k);
	varParticles_sim[74] = t->TimeSC(k);
	varParticles_sim[75] = t->PathSC(k);
	varParticles_sim[76] = t->StatCC(k); // CC
	varParticles_sim[77] = t->CCStatus(k);
	varParticles_sim[78] = t->Chi2CC(k);
	varParticles_sim[79] = t->Status(k); // Status
      } else { // fill with emptiness
	for (Int_t q = 0; q < 80; q++) varParticles_sim[q] = -9999.;
      } // end of simrec
      
      // then gsim
      g = gsim_row[j];
      varParticles_sim[80] = evnt;
      // gen electron
      varParticles_sim[81] = t->Q2(ge,1);
      varParticles_sim[82] = t->W(ge,1);
      varParticles_sim[83] = t->Nu(ge,1);
      varParticles_sim[84] = t->Xb(ge,1);
      varParticles_sim[85] = t->Yb(ge,1);
      varParticles_sim[86] = t->X(ge,1);
      varParticles_sim[87] = t->Y(ge,1);
      varParticles_sim[88] = t->Z(ge,1);
      varParticles_sim[89] = t->Sector(ge,1);
      varParticles_sim[90] = t->ElecVertTarg(ge,1);
      varParticles_sim[91] = t->Px(ge,1);
      varParticles_sim[92] = t->Py(ge,1);
      varParticles_sim[93] = t->Pz(ge,1);
      varParticles_sim[94] = t->Momentum(ge,1);
      varParticles_sim[95] = t->Betta(ge,1);
      // gen particle
      if (t->Id(g,1) == 211 || t->Id(g,1) == -211) mass = 0.1396;
      else if (t->Id(g,1) == 22) mass = 0.;
      varParticles_sim[96] = t->Zh(g,ge,1,mass);
      varParticles_sim[97] = t->ThetaPQ(g,ge,1);
      varParticles_sim[98] = t->Pt2(g,ge,1);
      varParticles_sim[99] = t->Pl2(g,ge,1);
      varParticles_sim[100] = t->PhiPQ(g,ge,1);
      varParticles_sim[101] = t->Mx2(g,ge,1,mass);
      varParticles_sim[102] = t->T(g,ge,1,mass);
      varParticles_sim[103] = t->X(g,1);
      varParticles_sim[104] = t->Y(g,1);
      varParticles_sim[105] = t->Z(g,1);
      varParticles_sim[106] = t->Sector(g,1);
      varParticles_sim[107] = t->Px(g,1);
      varParticles_sim[108] = t->Py(g,1);
      varParticles_sim[109] = t->Pz(g,1);
      varParticles_sim[110] = t->Momentum(g,1);
      varParticles_sim[111] = t->Betta(g,1);
      varParticles_sim[112] = t->Mass2(g,1);
      varParticles_sim[113] = t->Id(g,1);
      varParticles_sim[114] = t->Z(g,1) - t->Z(ge,1);
	
      tParticles->Fill(varParticles_sim);
      
      // clear array
      for (Int_t q = 0; q < 115; q++) varParticles_sim[q] = -9999.;
    } // end of loop in gsim particles
  } // end of important condition

  // just in case, clear array again
  for (Int_t q = 0; q < 115; q++) varParticles_sim[q] = -9999.;
}

void FillElectron_Data(Int_t evnt, Int_t ke) {

  // 15 vars depend on kind: 5 electron vars, 3 position, 4 momentum, 1 sector, 1 targtype, 1 betta
  
  TVector3 *vert;

  // data
  if (ke >= 0) {
    varElectrons_data[0] = t->Q2(ke,0);
    varElectrons_data[1] = t->W(ke,0);
    varElectrons_data[2] = t->Nu(ke,0);
    varElectrons_data[3] = t->Xb(ke,0);
    varElectrons_data[4] = t->Yb(ke,0);
    varElectrons_data[5] = t->X(ke,0);
    varElectrons_data[6] = t->Y(ke,0);
    varElectrons_data[7] = t->Z(ke,0);
    varElectrons_data[8] = t->Sector(ke,0);
    varElectrons_data[9] = t->ElecVertTarg(ke,0);
    varElectrons_data[10] = t->Px(ke,0);
    varElectrons_data[11] = t->Py(ke,0);
    varElectrons_data[12] = t->Pz(ke,0);
    varElectrons_data[13] = t->Momentum(ke,0);
    varElectrons_data[14] = t->Betta(ke,0);
    varElectrons_data[15] = t->Etot(ke);
    varElectrons_data[16] = t->Ein(ke);
    varElectrons_data[17] = t->Eout(ke);
    vert = t->GetCorrectedVert(ke);
    Float_t vxec = vert->X();
    Float_t vyec = vert->Y();
    Float_t vzec = vert->Z();
    varElectrons_data[18] = vxec;
    varElectrons_data[19] = vyec;
    varElectrons_data[20] = vzec;
    varElectrons_data[21] = t->XEC(ke);
    varElectrons_data[22] = t->YEC(ke);
    varElectrons_data[23] = t->ZEC(ke);
    varElectrons_data[24] = t->StatDC(ke); // DC
    varElectrons_data[25] = t->DCStatus(ke);
    varElectrons_data[26] = t->StatEC(ke); // EC
    varElectrons_data[27] = t->ECStatus(ke);
    varElectrons_data[28] = t->TimeEC(ke);
    varElectrons_data[29] = t->PathEC(ke);
    varElectrons_data[30] = t->Chi2EC(ke);
    varElectrons_data[31] = t->StatSC(ke); // SC
    varElectrons_data[32] = t->SCStatus(ke);
    varElectrons_data[33] = t->TimeSC(ke);
    varElectrons_data[34] = t->PathSC(ke);
    varElectrons_data[35] = t->StatCC(ke); // CC
    varElectrons_data[36] = t->CCStatus(ke);
    varElectrons_data[37] = t->Chi2CC(ke);
    varElectrons_data[38] = t->Status(ke); // Status
    varElectrons_data[39] = evnt;

    tElectrons->Fill(varElectrons_data);
  }
  
  // clear array, just in case
  for (Int_t q = 0; q < 40; q++) varElectrons_data[q] = -9999.;
}

void FillParticles_Data(Int_t evnt, Int_t ke, RVec<Int_t> data_row) {

  TVector3 *vert;
  Float_t mass;
  Int_t k;
  
  // there must be an electron to define the event
  if (ke >= 0) {
    
    for (Int_t j = 0; j < (Int_t) data_row.size(); j++) {
      k = data_row[j];      
      // electron
      varParticles_data[0] = t->Q2(ke,0); 
      varParticles_data[1] = t->W(ke,0);
      varParticles_data[2] = t->Nu(ke,0);
      varParticles_data[3] = t->Xb(ke,0);
      varParticles_data[4] = t->Yb(ke,0);
      varParticles_data[5] = t->X(ke,0);
      varParticles_data[6] = t->Y(ke,0);
      varParticles_data[7] = t->Z(ke,0);
      varParticles_data[8] = t->Sector(ke,0);
      varParticles_data[9] = t->ElecVertTarg(ke,0);
      varParticles_data[10] = t->Px(ke,0);
      varParticles_data[11] = t->Py(ke,0);
      varParticles_data[12] = t->Pz(ke,0);
      varParticles_data[13] = t->Momentum(ke,0);
      varParticles_data[14] = t->Betta(ke,0);
      varParticles_data[15] = t->Etot(ke);
      varParticles_data[16] = t->Ein(ke);
      varParticles_data[17] = t->Eout(ke);
      vert = t->GetCorrectedVert(ke);
      Float_t vxec = vert->X();
      Float_t vyec = vert->Y();
      Float_t vzec = vert->Z();
      varParticles_data[18] = vxec;
      varParticles_data[19] = vyec;
      varParticles_data[20] = vzec;
      varParticles_data[21] = t->XEC(ke);
      varParticles_data[22] = t->YEC(ke);
      varParticles_data[23] = t->ZEC(ke);
      varParticles_data[24] = t->StatDC(ke); // DC
      varParticles_data[25] = t->DCStatus(ke);
      varParticles_data[26] = t->StatEC(ke); // EC
      varParticles_data[27] = t->ECStatus(ke);
      varParticles_data[28] = t->TimeEC(ke);
      varParticles_data[29] = t->PathEC(ke);
      varParticles_data[30] = t->Chi2EC(ke);
      varParticles_data[31] = t->StatSC(ke); // SC
      varParticles_data[32] = t->SCStatus(ke);
      varParticles_data[33] = t->TimeSC(ke);
      varParticles_data[34] = t->PathSC(ke);
      varParticles_data[35] = t->StatCC(ke); // CC
      varParticles_data[36] = t->CCStatus(ke);
      varParticles_data[37] = t->Chi2CC(ke);
      varParticles_data[38] = t->Status(ke); // Status
      // particle
      if (t->GetCategorization(k,ke,analyserOption) == "pi+" || t->GetCategorization(k,ke,analyserOption) == "pi-") mass = 0.1396;
      else if (t->GetCategorization(k,ke,analyserOption) == "gamma") mass = 0.;
      varParticles_data[39] = t->Zh(k,ke,0,mass);
      varParticles_data[40] = t->ThetaPQ(k,ke,0);
      varParticles_data[41] = t->Pt2(k,ke,0);
      varParticles_data[42] = t->Pl2(k,ke,0);
      varParticles_data[43] = t->PhiPQ(k,ke,0);
      varParticles_data[44] = t->Mx2(k,ke,0,mass);
      varParticles_data[45] = t->T(k,ke,0,mass);
      varParticles_data[46] = t->X(k,0);
      varParticles_data[47] = t->Y(k,0);
      varParticles_data[48] = t->Z(k,0);
      varParticles_data[49] = t->Sector(k,0);
      varParticles_data[50] = t->Px(k,0);
      varParticles_data[51] = t->Py(k,0);
      varParticles_data[52] = t->Pz(k,0);
      varParticles_data[53] = t->Momentum(k,0);
      varParticles_data[54] = t->Betta(k,0);
      varParticles_data[55] = t->Mass2(k,0);
      varParticles_data[56] = t->Etot(k);
      varParticles_data[57] = t->Ein(k);
      varParticles_data[58] = t->Eout(k);
      varParticles_data[59] = t->XEC(k);
      varParticles_data[60] = t->YEC(k);
      varParticles_data[61] = t->ZEC(k);
      varParticles_data[62] = particleID(t->GetCategorization(k,ke,analyserOption));
      varParticles_data[63] = t->TimeCorr4(k,ke,mass);
      varParticles_data[64] = t->Z(k,0) - t->Z(ke,0);
      varParticles_data[65] = t->StatDC(k); // DC
      varParticles_data[66] = t->DCStatus(k);
      varParticles_data[67] = t->StatEC(k); // EC
      varParticles_data[68] = t->ECStatus(k);
      varParticles_data[69] = t->TimeEC(k);
      varParticles_data[70] = t->PathEC(k);
      varParticles_data[71] = t->Chi2EC(k);
      varParticles_data[72] = t->StatSC(k); // SC
      varParticles_data[73] = t->SCStatus(k);
      varParticles_data[74] = t->TimeSC(k);
      varParticles_data[75] = t->PathSC(k);
      varParticles_data[76] = t->StatCC(k); // CC
      varParticles_data[77] = t->CCStatus(k);
      varParticles_data[78] = t->Chi2CC(k);
      varParticles_data[79] = t->Status(k); // Status
      varParticles_data[80] = evnt;

      tParticles->Fill(varParticles_data);      
    } // end of loop
  }
  
  // clear array, just in case
  for (Int_t q = 0; q < 81; q++) varParticles_data[q] = -9999.;
}

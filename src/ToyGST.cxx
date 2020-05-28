/***************************************/
/*  ToyGST.cxx                         */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// TESTING

#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

#include "ROOT/RVec.hxx"

using namespace ROOT::VecOps;

/*** Global variables ***/

// options
TString outDir = proDir + "/out"; // for test only

TString outFile = outDir + "/pruned_test.root";
TString NtupleName = "ntuple_sim";
TString outTitle = "Simulation of particles";

TString analyserOption = "Sim";

// to be assigned
Int_t simFlag;
TString inputFile;

TIdentificator *t;

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();

RVec<Int_t> SortByMomentum(RVec<Int_t> row, RVec<Float_t> momentum);
Bool_t AngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row, Int_t n, Int_t m, Float_t angle);
RVec<Int_t> NewAngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row);

void PrintAll(RVec<Int_t> gsimElectron_row, RVec<Int_t> gsimGamma_row, RVec<Int_t> gsimPip_row, RVec<Int_t> gsimPim_row,
	      RVec<Int_t> simrecElectron_row, RVec<Int_t> simrecGamma_row, RVec<Int_t> simrecPip_row, RVec<Int_t> simrecPim_row);

int main(int argc, char **argv) {

  parseCommandLine(argc, argv);
  assignOptions();
  
  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");

  input->Add(inputFile);

  // define TIdentificator
  t = new TIdentificator(input);
  Int_t nEvents = (Int_t) input->GetEntries();
  
  // define sorting vectors for gsim
  RVec<Int_t> gsimElectron_row;
  RVec<Float_t> gsimElectron_P;

  RVec<Int_t> gsimGamma_row;
  RVec<Float_t> gsimGamma_P;

  RVec<Int_t> gsimPip_row;
  RVec<Float_t> gsimPip_P;  

  RVec<Int_t> gsimPim_row;
  RVec<Float_t> gsimPim_P;
  
  // define sorting vectors for simrec
  RVec<Int_t> simrecElectron_row;
  RVec<Float_t> simrecElectron_P;
  
  RVec<Int_t> simrecGamma_row;
  RVec<Float_t> simrecGamma_P;

  RVec<Int_t> simrecPip_row;
  RVec<Float_t> simrecPip_P;
  
  RVec<Int_t> simrecPim_row;
  RVec<Float_t> simrecPim_P;

  // jumps to first readable event, mandatory!
  input->Next();

  // loop around events
  for (Int_t k = 0; k < 25; k++) { // nEvents
    
    // simulation condition
    if (simFlag) {

      // loop in generated particles
      for (Int_t p = 0; p < input->GetNRows("GSIM"); p++) {

	/*** GENERATED ***/
	
	if (t->Id(p,1) == 11 || t->Id(p,1) == 211 || t->Id(p,1) == -211 || t->Id(p,1) == 22) {

	  std::cout << "GSIM = " << k << ", part = " << p << ", ID = " << t->Id(p,1) << ", P = " << t->Momentum(p,1) << std::endl;

	  if (t->Id(p,1) == 11) {
	    gsimElectron_row.push_back(p);
	    gsimElectron_P.push_back(t->Momentum(p,1));
	  }
	  
	  if (t->Id(p,1) == 22) {
	    gsimGamma_row.push_back(p);
	    gsimGamma_P.push_back(t->Momentum(p,1));
	  }

	  if (t->Id(p,1) == 211) {
	    gsimPip_row.push_back(p);
	    gsimPip_P.push_back(t->Momentum(p,1));
	  }

	  if (t->Id(p,1) == -211) {
	    gsimPim_row.push_back(p);
	    gsimPim_P.push_back(t->Momentum(p,1));
	  }
	}
	
	/*** RECONSTRUCTED ***/

	if (p < input->GetNRows("EVNT") && (t->GetCategorization(p, analyserOption) == "electron" ||
					    t->GetCategorization(p, analyserOption) == "gamma" ||
					    t->GetCategorization(p, analyserOption) == "pi+" ||
					    t->GetCategorization(p, analyserOption) == "pi-")) {

	  std::cout << "SIMREC = " << k << ", part = " << p << ", ID = " << t->Id(p,0) << ", categ = "
		    << t->GetCategorization(p, analyserOption) << ", P = " << t->Momentum(p,0) << std::endl;

	  if (t->GetCategorization(p, analyserOption) == "electron") {
	    simrecElectron_row.push_back(p);
	    simrecElectron_P.push_back(t->Momentum(p,0));
	  }

	  if (t->GetCategorization(p, analyserOption) == "gamma") {
	    simrecGamma_row.push_back(p);
	    simrecGamma_P.push_back(t->Momentum(p,0));
	  }

	  if (t->GetCategorization(p, analyserOption) == "pi+") {
	    simrecPip_row.push_back(p);
	    simrecPip_P.push_back(t->Momentum(p,0));
	  }

	  if (t->GetCategorization(p, analyserOption) == "pi-") {
	    simrecPim_row.push_back(p);
	    simrecPim_P.push_back(t->Momentum(p,0));
	  }
	}

      } // end of loop in particles

      std::cout << std::endl;
      
      /*** SORTING BY PARTICLE AND MOMENTUM ***/

      // gsim
      gsimElectron_row = SortByMomentum(gsimElectron_row, gsimElectron_P);
      gsimGamma_row = SortByMomentum(gsimGamma_row, gsimGamma_P);
      gsimPip_row = SortByMomentum(gsimPip_row, gsimPip_P);
      gsimPim_row = SortByMomentum(gsimPim_row, gsimPim_P);

      // simrec
      simrecElectron_row = SortByMomentum(simrecElectron_row, simrecElectron_P);      
      simrecGamma_row = SortByMomentum(simrecGamma_row, simrecGamma_P);
      simrecPip_row = SortByMomentum(simrecPip_row, simrecPip_P);
      simrecPim_row = SortByMomentum(simrecPim_row, simrecPim_P);
            
      /*** FILLING ***/

      PrintAll(gsimElectron_row, gsimGamma_row, gsimPip_row, gsimPim_row,
	       simrecElectron_row, simrecGamma_row, simrecPip_row, simrecPim_row);

      /*** ANGULAR MATCHING ***/

      std::cout << "...starting angular matching..." << std::endl;
      simrecElectron_row = NewAngularMatching(simrecElectron_row, gsimElectron_row);
      simrecGamma_row = NewAngularMatching(simrecGamma_row, gsimGamma_row);
      simrecPip_row = NewAngularMatching(simrecPip_row, gsimPip_row);
      simrecPim_row = NewAngularMatching(simrecPim_row, gsimPim_row);

      /*** FILLING V2 ***/

      PrintAll(gsimElectron_row, gsimGamma_row, gsimPip_row, gsimPim_row,
	       simrecElectron_row, simrecGamma_row, simrecPip_row, simrecPim_row);

      // reset memory
      
      gsimElectron_P.clear();
      gsimElectron_row.clear();
      gsimGamma_P.clear();
      gsimGamma_row.clear();
      
      gsimPip_P.clear();
      gsimPip_row.clear();
      gsimPim_P.clear();
      gsimPim_row.clear();

      simrecElectron_P.clear();
      simrecElectron_row.clear();
      simrecGamma_P.clear();
      simrecGamma_row.clear();
      
      simrecPip_P.clear();
      simrecPip_row.clear();
      simrecPim_P.clear();
      simrecPim_row.clear();
      
    } else if (!simFlag) { // end of simulation condition & beginning of data condition

      // loop in detected particles
      for (Int_t p = 0; p < input->GetNRows("EVNT"); p++) {

	/*** DATA ***/
	
	if (t->GetCategorization(p, analyserOption) == "electron" || t->GetCategorization(p, analyserOption) == "gamma" ||
	    t->GetCategorization(p, analyserOption) == "pi+" || t->GetCategorization(p, analyserOption) == "pi-") {
	  std::cout << "DATA = " << k << ", part = " << p << ", ID = " << t->Id(p,0) << ", categ = " << t->GetCategorization(p, analyserOption) << ", P = " << t->Momentum(p,0) << std::endl;
	}
	
      } // end of loop in particles      

    } // END OF DATA CONDITION
    
    /*** NEXT EVENT! ***/

    std::cout << std::endl;
    input->Next();
    
  } // end of loop in events
    
  return 0;
}

inline int parseCommandLine(int argc, char* argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./bin/ToyGST -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ha:")) != -1)
    switch (c) {
    case 'a': analyserOption = optarg; break;
    default:
      std::cerr << "Unrecognized argument. Execute ./bin/ToyGST -h to print usage." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  if (analyserOption == "Sim") {
    simFlag = 1;
    inputFile = "/home/borquez/Downloads/recsisC_0028.root";
  } else if (analyserOption == "C") {
    simFlag = 0;
    inputFile = "/home/borquez/Downloads/clas_42011_00.pass2.root";
  }
}

/*** Vector functions ***/

RVec<Int_t> SortByMomentum(RVec<Int_t> row, RVec<Float_t> momentum) {

  // returns a new "row2" where row values are sorted by their respective momentum
  // from lower to higher momentum

  // Argsort() creates an indices-vector with the indices sorted by the input-vector values
  // Take(input-vector, indices-vector) creates a sorted-vector by moving all input-vector indices to match the order assigned by the indices-vector
  
  RVec<Int_t> indices = Argsort(momentum);
  RVec<Int_t> row2 = Take(row, indices);

  return row2;
}

void PrintAll(RVec<Int_t> gsimElectron_row, RVec<Int_t> gsimGamma_row, RVec<Int_t> gsimPip_row, RVec<Int_t> gsimPim_row,
	      RVec<Int_t> simrecElectron_row, RVec<Int_t> simrecGamma_row, RVec<Int_t> simrecPip_row, RVec<Int_t> simrecPim_row) {

  std::cout << std::left
	    << std::setw(14) << "gsim_row"
	    << std::setw(14) << "gsim_categ"
	    << std::setw(14) << "gsim_P"
	    << std::setw(4)  << "||"
	    << std::setw(14) << "simrec_row"
	    << std::setw(14) << "simrec_categ"
	    << std::setw(14) << "simrec_P" << std::endl;

  // electrons
  for (Int_t j = 0; j < (Int_t) gsimElectron_row.size(); j++) {
    std::cout << std::left
	      << std::setw(14) << gsimElectron_row[j]
	      << std::setw(14) << particleName(t->Id(gsimElectron_row[j], 1))
	      << std::setw(14) << t->Momentum(gsimElectron_row[j], 1)
	      << std::setw(4)  << "||";
    if (j < (Int_t) simrecElectron_row.size() && simrecElectron_row[j] != -1) {
      std::cout << std::setw(14) << simrecElectron_row[j]
		<< std::setw(14) << t->GetCategorization(simrecElectron_row[j], analyserOption)
		<< std::setw(14) << t->Momentum(simrecElectron_row[j], 0) << std::endl;
    } else {
      std::cout << std::setw(14) << "-9999"
		<< std::setw(14) << "-9999"
		<< std::setw(14) << "-9999" << std::endl;
    }
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
		<< std::setw(14) << t->GetCategorization(simrecGamma_row[j], analyserOption)
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
		<< std::setw(14) << t->GetCategorization(simrecPip_row[j], analyserOption)
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
		<< std::setw(14) << t->GetCategorization(simrecPim_row[j], analyserOption)
		<< std::setw(14) << t->Momentum(simrecPim_row[j], 0) << std::endl;
    } else {
      std::cout << std::setw(14) << "-9999"
		<< std::setw(14) << "-9999"
		<< std::setw(14) << "-9999" << std::endl;
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

// ok, now i know how to match... just put a condition!!
// doesn't work... i'm showing just when momentum order also obeys the match...
// now, the questions are:
//   how do i prevent excluding those who doesn't match the condition ??? :c
//   how do i put

/***************************************/
/*  ToyGST.cxx                         */
/*                                     */
/*  Andrés Bórquez                     */
/*                                     */
/***************************************/

// UPDATE:
// - if nElectron > 1, select the one who obeys DIS

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

// define TIdentificator object as global
TIdentificator *t;

// define ntuple list of variables


TString varListParticles = "TargType:Q2:Nu:Xb:W:SectorEl:ThetaPQ:PhiPQ:Zh:Pt:W2p:Xf:T:P:T4:deltaZ:E:Ee:Pe:Ect:Sct:Ecr:Scr:evnt:Px:Py:Pz:Xe:Ye:Ze:Xec:Yec:Zec:TEc:ECX:ECY:ECZ:Pex:Pey:Pez:Ein:Eout:Eine:Eoute:pid:Betta:vxh:vyh:vzh";

//                         " 0:1: 2:   3:   4:   5:  6:  7:  8:  9: 10: 11:   12:      13:    14:15: 16: 17: 18"
TString varListElectrons = "Q2:W:Nu:vxec:vyec:vzec:vxe:vye:vze:Pex:Pey:Pez:event:TargType:sector:Xb:ECX:ECY:ECZ";

/*** Declaration of functions ***/

inline int parseCommandLine(int argc, char* argv[]);
void assignOptions();

RVec<Int_t> SortByMomentum(RVec<Int_t> row, RVec<Float_t> momentum);
Bool_t AngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row, Int_t n, Int_t m, Float_t angle);
RVec<Int_t> NewAngularMatching(RVec<Int_t> simrec_row, RVec<Int_t> gsim_row);

void PrintAll(RVec<Int_t> gsimElectron_row, RVec<Int_t> gsimGamma_row, RVec<Int_t> gsimPip_row, RVec<Int_t> gsimPim_row,
	      RVec<Int_t> simrecElectron_row, RVec<Int_t> simrecGamma_row, RVec<Int_t> simrecPip_row, RVec<Int_t> simrecPim_row);
void ResetVectors(RVec<Int_t> gsimElectron, RVec<Int_t> gsimGamma, RVec<Int_t> gsimPip, RVec<Int_t> gsimPim,
		  RVec<Int_t> simrecElectron, RVec<Int_t> simrecGamma, RVec<Int_t> simrecPip, RVec<Int_t> simrecPim);

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
      ResetVectors(gsimElectron_row, gsimGamma_row, gsimPip_row, gsimPim_row,
		   simrecElectron_row, simrecGamma_row, simrecPip_row, simrecPim_row);
      ResetVectors(gsimElectron_P, gsimGamma_P, gsimPip_P, gsimPim_P,
		   simrecElectron_P, simrecGamma_P, simrecPip_P, simrecPim_P);
      
    } else if (!simFlag) { // end of simulation condition & beginning of data condition

      // loop in detected particles
      for (Int_t p = 0; p < input->GetNRows("EVNT"); p++) {

	/*** DATA ***/
	
	if (t->GetCategorization(p, analyserOption) == "electron" || t->GetCategorization(p, analyserOption) == "gamma" ||
	    t->GetCategorization(p, analyserOption) == "pi+" || t->GetCategorization(p, analyserOption) == "pi-") {
	  std::cout << "DATA = " << k << ", part = " << p << ", ID = " << t->Id(p,0) << ", categ = " << t->GetCategorization(p, analyserOption) << ", P = " << t->Momentum(p,0) << std::endl;
	}
	
      } // end of loop in particles      

    } // end of data condition
    
    /*** NEXT EVENT! ***/

    std::cout << std::endl;
    input->Next();
    
  } // end of loop in events
    
  return 0;
}

/*** Input/output functions ***/

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

  // debug function
  
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

void ResetVectors(RVec<Int_t> gsimElectron, RVec<Int_t> gsimGamma, RVec<Int_t> gsimPip, RVec<Int_t> gsimPim,
		  RVec<Int_t> simrecElectron, RVec<Int_t> simrecGamma, RVec<Int_t> simrecPip, RVec<Int_t> simrecPim) {

  // cleans memory, clears all vectors
  // can be used for "_row" and "P" vectors
  
  gsimElectron.clear();
  gsimGamma.clear();      
  gsimPip.clear();
  gsimPim.clear();
  
  simrecElectron.clear();
  simrecGamma.clear();
  simrecPip.clear();
  simrecPim.clear();
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

  // selects first electron that meet DIS requirements: Q2 > 1 and W > 1

  // define winner
  Int_t winner;
  
  if ((Int_t) Electron_row.size() > 1) {
    
    for (Int_t i = 0; i < (Int_t) Electron_row.size(), i++) {
      if (t->Q2(Electron_row[0]) > 1. && t->W(Electron_row[0]) > 2.) winner = Electron_row[0];
    }
    
  } else {
    return Electron_row[0];
  }
  
  return winner;
}

/*** Filling tree functions ***/

void SetElectronVars(Float_t *e_vars, TIdentificator *t, Int_t k, bool sim) {

  TVector3 *vert;
  
  if (!simFlag) {
    // variables reminder
    //  0:1: 2:   3:   4:   5:  6:  7:  8:  9: 10: 11:   12
    // Q2:W:Nu:vxec:vyec:vzec:vxe:vye:vze:Pex:Pey:Pez:event
    e_vars[0] = t -> Q2();
    e_vars[1] = t -> W();
    e_vars[2] = t -> Nu();
    vert = t->GetCorrectedVert();
    Float_t vxec=vert->X(); 
    Float_t vyec=vert->Y(); 
    Float_t vzec=vert->Z(); 
    e_vars[3] = vxec; 
    e_vars[4] = vyec; 
    e_vars[5] = vzec;
    e_vars[6] = t->X(0);
    e_vars[7] = t->Y(0);
    e_vars[8] = t->Z(0);
    e_vars[9] = t -> Px(0);
    e_vars[10] = t -> Py(0);
    e_vars[11] = t -> Pz(0);
    e_vars[12] = k;
  } else if ( sim == 1 ) {
    e_vars[0] = t -> Q2(1);
    e_vars[1] = t -> W(1);
    e_vars[2] = t -> Nu(1);
    e_vars[3] = 0;
    e_vars[4] = 0;
    e_vars[5] = 0;
    e_vars[6] = t -> X(0,1);
    e_vars[7] = t -> Y(0,1);
    e_vars[8] = t -> Z(0,1);
    e_vars[9] = t -> Px(0,1);
    e_vars[10] = t -> Py(0,1);
    e_vars[11] = t -> Pz(0,1);
    e_vars[12] = k;
  }
}

void SetParticleVars(Float_t * particle_vars, TIdentificator * t, Int_t k, Int_t i, bool sim, TString category) {
  Int_t f = 0;
  if ( sim == 0 ) {
    particle_vars[f] = t -> ElecVertTarg(); f++;
    particle_vars[f] = t -> Q2(); f++;
    particle_vars[f] = t -> Nu(); f++;
    particle_vars[f] = t -> Xb(); f++;
    particle_vars[f] = t -> W(); f++;
    particle_vars[f] = t -> Sector(0); f++;
    particle_vars[f] = t -> ThetaPQ(i); f++;
    particle_vars[f] = t -> PhiPQ(i); f++;
    particle_vars[f] = t -> Zh(i); f++;
    particle_vars[f] = TMath::Sqrt(t -> Pt2(i)); f++;
    particle_vars[f] = t -> Mx2(i); f++;
    particle_vars[f] = t -> Xf(i); f++;
    particle_vars[f] = t -> T(i); f++;
    particle_vars[f] = t -> Momentum(i); f++;
    particle_vars[f] = t -> TimeCorr4(0.139570,i); f++;
    particle_vars[f] = (t -> Z(i)) - (t -> Z(0)); f++;
    particle_vars[f] = k; f++;	      
    particle_vars[f] = ((category == "gamma")?22:
			((category == "pi-")?-211:
			 (( category == "high energy pion +" || category == "low energy pion +")?211:
			  ((category == "s_electron")?11:-11)
			  )
			 )
			); f++;
    particle_vars[f] = t -> ThetaLab(i); f++;
    particle_vars[f] = t -> PhiLab(i); f++;
    particle_vars[f] = t -> Px(i); f++;
    particle_vars[f] = t -> Py(i); f++;
    particle_vars[f] = t -> Pz(i); f++;
  } else if ( sim == 1 ) {
    Int_t f = 0;
    particle_vars[f] = t -> ElecVertTarg(1); f++;
    particle_vars[f] = t -> Q2(1); f++;
    particle_vars[f] = t -> Nu(1); f++;
    particle_vars[f] = t -> Xb(1); f++;
    particle_vars[f] = t -> W(1); f++;
    particle_vars[f] = t -> Sector(0,1); f++;
    particle_vars[f] = t -> ThetaPQ(i,1); f++;
    particle_vars[f] = t -> PhiPQ(i,1); f++;
    particle_vars[f] = t -> Zh(i,1); f++;
    particle_vars[f] = TMath::Sqrt(t -> Pt2(i,1)); f++;
    particle_vars[f] = t -> Mx2(i,1); f++;
    particle_vars[f] = t -> Xf(i,1); f++;
    particle_vars[f] = t -> T(i,1); f++;
    particle_vars[f] = t -> Momentum(i,1); f++;
    particle_vars[f] = 0; f++;//t -> TimeCorr4(0.139570,i);
    particle_vars[f] = (t -> Z(i,1)) - (t -> Z(0,1)); f++;
    particle_vars[f] = k; f++;
    particle_vars[f] = t -> Id(i,1); f++;
    particle_vars[f] = t -> ThetaLab(i,1); f++;
    particle_vars[f] = t -> PhiLab(i,1); f++;
    particle_vars[f] = t -> Px(i,1); f++;
    particle_vars[f] = t -> Py(i,1); f++;
    particle_vars[f] = t -> Pz(i,1); f++;
  }
}

#ifndef UX_HXX
#define UX_HXX

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** Global variables ***/

TString gDataKind = "";

TString gTargetOption;
TString gRunNumber;

// event mixing, turned off by default
Int_t gMixData = 0;
Int_t gMixReconstructed = 0;
Int_t gParticleToSwap;

TString gInputFile;
TString gOutputFile;

/*** Input-related functions ***/

void printUsage() {
  std::cout << "ThreePionFinder_" << gDataKind << " program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./ThreePionFinder_" << gDataKind << " -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./ThreePionFinder_" << gDataKind << " -t[D, C, Fe, Pb]" << std::endl;
  std::cout << "    filters respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./ThreePionFinder_" << gDataKind << " -r[rn]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for input files = pruned<target>_<rn>.root" << std::endl;
  std::cout << std::endl;
  std::cout << "./ThreePionFinder_" << gDataKind << " -m[211, -211, 111, 999]" << std::endl;
  std::cout << "    (event mixing) swap a particular kind of particle for all the omega candidates:" << std::endl;
  std::cout << "    pi+ (211), pi- (-211), pi0 (111), all three pions (999)" << std::endl;
  std::cout << std::endl;
}

void parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./ThreePionFinder_" << gDataKind << " -h to print help." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ht:r:m:")) != -1) switch (c) {
      case 'h':
        printUsage();
        exit(0);
        break;
      case 't':
        gTargetOption = optarg;
        break;
      case 'r':
        gRunNumber = optarg;
        break;
      case 'm':
        gMixData = 1;
        gMixReconstructed = 1;
        gParticleToSwap = atoi(optarg);
        break;
      default:
        std::cerr << "Unrecognized argument. Execute ./ThreePionFinder_" << gDataKind << " -h to print help." << std::endl;
        exit(1);
        break;
    }
}

void assignOptions() {
  TString sufixParticleToSwap;
  if (gParticleToSwap == 211) {
    sufixParticleToSwap = "sPip";
  } else if (gParticleToSwap == -211) {
    sufixParticleToSwap = "sPim";
  } else if (gParticleToSwap == 111) {
    sufixParticleToSwap = "sPi0";
  } else if (gParticleToSwap == 999) {
    sufixParticleToSwap = "sAll";
  } else {
    sufixParticleToSwap = "";
  }
  // for everyone, at node dir
  if (gMixData || gMixReconstructed) {
    gInputFile = "redu" + gTargetOption + "_" + gRunNumber + ".root";
    gOutputFile = "bkgmix" + gTargetOption + "_" + gRunNumber + "_" + sufixParticleToSwap + ".root";
  } else {
    gInputFile = "pruned" + gTargetOption + "_" + gRunNumber + ".root";
    gOutputFile = "omega" + gTargetOption + "_" + gRunNumber + ".root";
  }
}

void printOptions() {
  std::cout << "Executing ThreePionFinder_" << gDataKind << " program. The chosen parameters are: " << std::endl;
  std::cout << "  gTargetOption   = " << gTargetOption << std::endl;
  std::cout << "  gRunNumber      = " << gRunNumber << std::endl;
  if (gMixData || gMixReconstructed) {
    std::cout << "  gParticleToSwap = " << gParticleToSwap << std::endl;
  }
  std::cout << std::endl;
}

#endif

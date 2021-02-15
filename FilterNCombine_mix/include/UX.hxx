#ifndef UX_HXX
#define UX_HXX

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** Global variables ***/

TString gTargetOption;
TString gRunNumber;

Int_t gParticleToSwap;

TString gInputFile;
TString gOutputFile;

/*** Input-related functions ***/

void printUsage() {
  std::cout << "FilterNCombine_mix program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_mix -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_mix -t[C, Fe, Pb]" << std::endl;
  std::cout << "    filters respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_mix -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for input files = pruned<target>_<run number>.root" << std::endl;
  std::cout << std::endl;
  std::cout << "./FilterNCombine_mix -p[211, -211, 111, 999]" << std::endl;
  std::cout << "    selects particles to swap:" << std::endl;
  std::cout << "    pi plus (211), pi minus (-211), pi0 (111), all three (999)" << std::endl;
  std::cout << std::endl;
}

inline void parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./FilterNCombine_mix -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:r:p:")) != -1)
    switch (c) {
    case 'h': printUsage(); exit(0); break;
    case 't': gTargetOption = optarg; break;
    case 'r': gRunNumber = optarg; break;
    case 'p': gParticleToSwap = atoi(optarg); break;
    default:
      std::cerr << "Unrecognized argument. Execute ./FilterNCombine_mix -h to print help." << std::endl;
      exit(0);
      break;
    }
}

void assignOptions() {
  TString sufixParticleToSwap;
  if (gParticleToSwap == 211) sufixParticleToSwap = "sPip";
  else if (gParticleToSwap == -211) sufixParticleToSwap = "sPim";
  else if (gParticleToSwap == 111) sufixParticleToSwap = "sPi0";
  else if (gParticleToSwap == 999) sufixParticleToSwap = "sAll";
  // for everyone, at node dir
  gInputFile  = "pruned" + gTargetOption + "_" + gRunNumber + ".root";
  gOutputFile = "bkgmix" + gTargetOption + "_" + gRunNumber + "_" + sufixParticleToSwap + ".root";
}

void printOptions() {
  std::cout << "Executing FilterNCombine_mix program. The chosen parameters are: " << std::endl;
  std::cout << "  gTargetOption   = " << gTargetOption << std::endl;
  std::cout << "  gRunNumber      = " << gRunNumber << std::endl;
  std::cout << "  gParticleToSwap = " << gParticleToSwap << std::endl;
  std::cout << std::endl;
}

#endif

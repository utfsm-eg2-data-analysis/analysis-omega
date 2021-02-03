#ifndef MIXINGBKG_UX_HXX
#define MIXINGBKG_UX_HXX

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** Global variables ***/

TString gDataKind = "";

TString gTargetOption;
TString gRunNumber;

TString gInputFile;
TString gOutputFile;

/*** Input-related functions ***/

void printUsage() {
  std::cout << "MixingBkg program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./MixingBkg -h" << std::endl;
  std::cout << "    prints this message and exits program" << std::endl;
  std::cout << std::endl;
  std::cout << "./MixingBkg -t[C, Fe, Pb]" << std::endl;
  std::cout << "    filters the respective target" << std::endl;
  std::cout << std::endl;
  std::cout << "./MixingBkg -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << "    numbering scheme for input files = pruned<target>_<run number>.root" << std::endl;
  std::cout << std::endl;
}

void parseCommandLine(int argc, char* argv[]) {
  Int_t c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./MixingBkg -h to print help." << std::endl;
    exit(0);
  }
  while ((c = getopt(argc, argv, "ht:r:")) != -1) {
    switch (c) {
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
      default:
        std::cerr << "Unrecognized argument. Execute ./MixingBkg -h to print help." << std::endl;
        exit(0);
        break;
    }
  }
}

void assignOptions() {
  // for everyone, at node dir
  gInputFile = "pruned" + gTargetOption + "_" + gRunNumber + ".root";
  gOutputFile = "bkgmix" + gTargetOption + "_" + gRunNumber + ".root";
}

void printOptions() {
  std::cout << "Executing MixingBkg program. The chosen parameters are: " << std::endl;
  std::cout << "  gTargetOption = " << gTargetOption << std::endl;
  std::cout << "  gRunNumber    = " << gRunNumber << std::endl;
  std::cout << std::endl;
}

#endif

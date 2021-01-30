#ifndef UX_HXX
#define UX_HXX

// User Experience

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** Options/global variables ***/

TString gTargetOption;
TString gRunNumber;

TString gInputFile;
TString gOutputFile;

/*** Input/output functions ***/

void printUsage() {
  std::cout << "Reductor program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Reductor -h" << std::endl;
  std::cout << "    prints usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Reductor -t[target]" << std::endl;
  std::cout << "    selects target, which can be: C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./Reductor -r[run number]" << std::endl;
  std::cout << "    selects run number" << std::endl;
  std::cout << std::endl;
}

void parseCommandLine(int argc, char *argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./bin/Reductor -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ht:r:")) != -1) switch (c) {
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
        std::cerr << "Unrecognized argument. Execute ./bin/Reductor -h to print usage." << std::endl;
        exit(0);
        break;
    }
}

void assignOptions() {
  gInputFile  = "pruned" + gTargetOption + "_" + gRunNumber + ".root";
  gOutputFile = "pruned" + gTargetOption + "_" + gRunNumber + "_red.root";
}

void printOptions() {
  std::cout << "Executing Reductor program. The chosen parameters are: " << std::endl;
  std::cout << "  gTargetOption   = " << gTargetOption << std::endl;
  std::cout << "  gRunNumber      = " << gRunNumber << std::endl;
  std::cout << std::endl;
}

#endif

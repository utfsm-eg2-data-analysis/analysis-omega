#ifndef UX_HXX
#define UX_HXX

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** Global variables ***/

TString gDataKind = "data"; // default
TString gTreeName;
TString gDataDescription;

TString gTargetOption;
TString gRunNumber;

TString gInputFile;
TString gOutputFile;

/*** Input/output functions ***/

void printUsage() {
  std::cout << "Reductor program. Usage is:" << std::endl;
  std::cout << std::endl;
  std::cout << "./Reductor -h" << std::endl;
  std::cout << "    print usage and exit program" << std::endl;
  std::cout << std::endl;
  std::cout << "./Reductor -t[target]" << std::endl;
  std::cout << "    select target, which can be: D, C, Fe, Pb" << std::endl;
  std::cout << std::endl;
  std::cout << "./Reductor -r[run number]" << std::endl;
  std::cout << "    select run number" << std::endl;
  std::cout << std::endl;
  std::cout << "./Reductor -s" << std::endl;
  std::cout << "    run on a simulation file" << std::endl;
  std::cout << std::endl;
}

void parseCommandLine(int argc, char *argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./Reductor -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ht:r:s")) != -1) switch (c) {
      case 'h':
        printUsage();
        exit(0);
        break;
      case 't':
        gTargetOption = optarg;
        break;
      case 's':
        gDataKind = "sim";
        break;
      case 'r':
        gRunNumber = optarg;
        break;
      default:
        std::cerr << "Unrecognized argument. Execute ./Reductor -h to print usage." << std::endl;
        exit(1);
        break;
    }
}

void assignOptions() {
  gTreeName = "ntuple_" + gDataKind;
  gInputFile = "pruned" + gTargetOption + "_" + gRunNumber + ".root";
  gOutputFile = "redu" + gTargetOption + "_" + gRunNumber + ".root";
  gDataDescription = "Data of particles";
  if (gDataKind == "sim") {
    gDataDescription = "Simulation of particles";
  }
}

void printOptions() {
  std::cout << "Executing Reductor program. The chosen parameters are: " << std::endl;
  std::cout << "  gDataKind       = " << gDataKind << std::endl;
  std::cout << "  gTargetOption   = " << gTargetOption << std::endl;
  std::cout << "  gRunNumber      = " << gRunNumber << std::endl;
  std::cout << std::endl;
}

#endif

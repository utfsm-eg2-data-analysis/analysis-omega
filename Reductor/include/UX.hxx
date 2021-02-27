#ifndef UX_HXX
#define UX_HXX

// User Experience

#ifndef HEADERS_HXX
#include "Headers.hxx"
#endif

/*** Options/global variables ***/

TString gDataKind = "data";  // default
TString gTreeName;

Int_t gReduceSimrec = 0;
Int_t gReduceMC = 0;

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
  std::cout << "./Reductor -s[int]" << std::endl;
  std::cout << "    reduce simulations instead of data" << std::endl;
  std::cout << "    0 to reduce MC, 1 to reduce simrec" << std::endl;
  std::cout << std::endl;
}

void parseCommandLine(int argc, char *argv[]) {
  int c;
  if (argc == 1) {
    std::cerr << "Empty command line. Execute ./bin/Reductor -h to print usage." << std::endl;
    exit(1);
  }
  while ((c = getopt(argc, argv, "ht:r:s:")) != -1) switch (c) {
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
      case 's':
        gDataKind = "sim";
	gReduceMC = 1*(atoi(optarg) == 0) + 0*(atoi(optarg) != 0);
	gReduceSimrec = 0*(atoi(optarg) == 0) + 1*(atoi(optarg) != 0);
        break;
      default:
        std::cerr << "Unrecognized argument. Execute ./bin/Reductor -h to print usage." << std::endl;
        exit(0);
        break;
    }
}

void assignOptions() {
  TString sufix = "";
  if (gReduceMC) sufix = "_MC";
  gTreeName = "ntuple_" + gDataKind;
  gInputFile = "pruned" + gTargetOption + "_" + gRunNumber + ".root";
  gOutputFile = "pruned" + gTargetOption + "_" + gRunNumber + "_red" + sufix + ".root";
}

void printOptions() {
  std::cout << "Executing Reductor program. The chosen parameters are: " << std::endl;
  std::cout << "  gTargetOption   = " << gTargetOption << std::endl;
  std::cout << "  gRunNumber      = " << gRunNumber << std::endl;
  std::cout << "  gDataKind       = " << gDataKind << std::endl;
  if (gDataKind == "sim") {
    std::cout << "  gReduceMC       = " << gReduceMC << std::endl;
    std::cout << "  gReduceSimrec   = " << gReduceSimrec << std::endl;
  }
  std::cout << std::endl;
}

#endif

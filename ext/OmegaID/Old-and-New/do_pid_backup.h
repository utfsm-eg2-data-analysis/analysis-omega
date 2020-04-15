#include <getopt.h>

extern bool GSIM;
extern int data_type;
extern long Ne;

inline void printhelp() {
  std::cout << "####### Help #########\n"
    "\t[-t | --data-type] <target_type> : data type [data | simrec | gsim ]. Default data\n"
    "\t[-n | --max-events] <N>              : max number of events to be considered. Default all\n"
    "\t-h              : Print help.\n"
    "#########################"	   << std::endl;
  exit(0);
}

inline int parseopt(int argc, char* argv[]) {
  int c;
  int option_index = 0;
  static struct option long_options[] =
    {
      {"max-events",     required_argument,       0, 'n'},
      {"help",     no_argument,       0, 'h'},
      {"data-type",  required_argument, 0, 't'},
      {0, 0, 0, 0}
    };

  if (argc == 1)
    printhelp();
  while ( (c = getopt_long(argc, argv, "ht:n:", long_options, &option_index)) != -1)
    switch (c) {
    case 'n':
      Ne = atoi(optarg);
      break;
    case 't':
	if(!strcmp(optarg,"data"))
	  data_type = 0;
	else if (!strcmp(optarg,"simrec")) 
	  data_type = 1;
	else if (!strcmp(optarg,"gsim"))
	  data_type = 2; 
	break;
    case 'h':
      printhelp();
      break;
    case '?':
      if (optopt == 't')
	fprintf(stderr, "Option -%c data type [data | simrec | gsim ]. Default data.\n", optopt);
      else if (isprint (optopt))
	fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
	fprintf(stderr,
		"Unknown option character `\\x%x'.\n",
		optopt);
      return 1;
    default:
      abort();
    }
}

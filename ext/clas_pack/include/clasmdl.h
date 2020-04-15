/* C representation of the clasmdl common block
   MUST BE KEPT IN SYNCH WITH clasmdl.inc */

#define NTRIG_MDL 21

typedef struct {
  int begjob, endrun, begrun, revent, endjob, othdat;
  int version, lccrun, nccrun, nevent, evtime, evtype;
  int rocstat, evtwght, evtclas;
  int phystyp[NTRIG_MDL];
  int itally[NTRIG_MDL];
  float cpusum[NTRIG_MDL+2];
  int itally_missed[NTRIG_MDL];
  int tevent;
  int trun, trec, ncrevt, tevent_skip, tevent_seen;
  int itally_skiped[NTRIG_MDL];
  int linter;
  int lscaler;
  int lepics;
  int prev_event;
} clasmdl_t;


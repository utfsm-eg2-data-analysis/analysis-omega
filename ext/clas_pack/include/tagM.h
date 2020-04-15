//$Id: tagM.h,v 1.6 2006/03/15 14:51:40 pasyuk Exp $

#ifndef TAGM_H
#define TAGM_H

#include <ntypes.h>
#include <bostypes.h>
#include <bosddl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Data structures to match format of bounds files */
typedef struct {
	int Echan;
	float kmin,kmax,kavg,ksdev;
}tagE_boundaries_t;

typedef struct {
	int Tctr;
	float kmin,kminfirst,kmax;
}tagT_boundaries_t;

/* E-T geometry correlation. Values are read from tagETcoinc_ALL.dat */
typedef struct {
	int Ectr,Tmin,Tmax,T1min,T1max,TCHANmin,TCHANmax;
}tagETgeom_t;

/* Holds info from tagger E or T counter hit */
typedef struct {
	int id;
	float t;	/* nanoseconds   */
	int   tdc;	/* TDC counts    */
	float E;	/* Energy in GeV */
	int status;
}TAG_HIT_t;

/* Holds info from ET coincidences found */
typedef struct{
	float energy; /* in GeV */
	float t, e_t; /* t = T-counter time (ns) e_t = E-counter time (ns) */
	int status;   /* for future use. always TAGM_ET for now */
	int tid,eid;
}TAG_ET_COINCIDENCE_t;


/* Global Variables */
extern float EID_TIME_OFFSETS[384];		/* align E-counters in ns						*/
extern float TID_TIME_OFFSETS[61];		/* align T-counters in ns (multi-hit)		*/
extern float E2T_TIME;						/* time difference between E and T cntrs	*/
extern float EID2NS,TID2NS;				/* Convert E-counter and T-counter TDC		*/
													/* counts to nanoseconds respectively		*/
extern float EE_TIME_WINDOW;				/* half of timing window size for adjacent E-cntrs in ns	*/
extern float TT_TIME_WINDOW;				/* half of timing window size for adjacent T-cntrs in ns	*/
extern float ET_TIME_WINDOW;				/* half of timing window size for E and T cntrs in ns		*/

/* Globals hold tables from bounds files for the energy closest to that
 * passed on the most recent call to tag_read_calib()
*/
extern tagE_boundaries_t	tagE_boundaries[767];
extern tagETgeom_t			tagETgeom[384];
extern tagT_boundaries_t	tagT_boundaries[61];
extern float TAGM_EBEAM_ENERGY; /* Electron beam energy (GeV) */


#define MAX_EHITS 750
#define MAX_THITS 1000
#define MAX_ETHITS 300

/* status flag definitions */
#define TAGM_NO_STATUS -1
#define TAGM_ET 0x00
#define TAGM_T_ONLY 0x02
#define TAGM_E_ONLY 0x04

/* subroutines */
float EfromEID(int id);
float EfromTID(int id);

int tagM_brun(int runnumber);
int tagM_init(void);
int tagM_evt(void);
int tagM_erun(void);
int tagM_GetECounterHits(TAG_HIT_t* e_hits);
int tagM_GetTCounterHits(TAG_HIT_t* t_hits);
int tagM_GetEChannelHits(int n_e_hits, TAG_HIT_t* e_hits, TAG_HIT_t* e_channel_hits);
int tagM_GetTChannelHits(int n_t_hits, TAG_HIT_t* t_hits, TAG_HIT_t* t_channel_hits);
int tagM_GetETCoincidences(int n_e_channel_hits,
									TAG_HIT_t* e_channel_hits,
									int n_t_channel_hits,
									TAG_HIT_t* t_channel_hits,
									TAG_ET_COINCIDENCE_t* et_coincidences,
									float time_offset);
int tagM_make_TAGM(int n_et_coincidences, TAG_ET_COINCIDENCE_t* et_coincidences, int group);


typedef int QSORT_PROC_t(const void *, const void *); /* type definition used to avoid compiler warnings */

#endif /* TAGM_H */




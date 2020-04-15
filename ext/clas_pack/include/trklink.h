/*
  This file contain some sobroutines to crate MTRK, CLST and SGMP BOS banks.
  
  Author         : G. Gavalian
  Creation Date  : 22 Feb 1998

 */

#define MAX_TRK 20
#define NSGCMX  20
#define NCLMX   10
#define MAX_TRK 20
#define MAX_SGM 60
#define SL_MAX  12
#define SECT_C  6
#define SLAY_C  6

#include "bosddl.h"


/*
  Function Prototypes
 */

int make_mtrk_bank_(int lnk_segm[MAX_TRK][6],int lnk_clust[MAX_TRK][6],int itr_sect[MAX_TRK],int ntr_link[1]);
int make_clst_bank_(int clust[6][6][10][20],int nsegmc[6][6][10],int nclust[6][6]);
int make_sgmp_bank_(int segm[6][6][MAX_SGM][12],int nsegm[6][6]);

int read_clst_bank_(int clust[6][6][10][20],int nsegmc[6][6][10],int nclust[6][6],int nread[1]);
int read_mtrk_bank_(int lnk_segm[MAX_TRK][6],int lnk_clust[MAX_TRK][6],int itr_sect[MAX_TRK],int ntr_link[1],int nread[1]);
int read_sgmp_bank_(int segm[6][6][60][12],int nsegm[6][6], int nread[1]);


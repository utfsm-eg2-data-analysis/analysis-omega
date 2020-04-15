#ifndef elossH_INCLUDED
#define elossH_INCLUDED
/* ----------- 
Function prototype for c wrapper for energy loss program 
see utilities/eloss
DJT -Jul 99
---------------- */

vector4_t c_momcor(vector4_t p_out, float pmass, vector3_t vertex, int iflag, int icell);

void InitEloss(int Run);

void initeloss_(int *Run);

typedef struct {
  float target_offset[3];
  float st_offset;
} eloss_geom_t;

extern eloss_geom_t eloss_geom_;
#endif

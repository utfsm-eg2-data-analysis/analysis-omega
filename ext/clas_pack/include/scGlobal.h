#ifndef scGlobalH_INCLUDED
#define scGlobalH_INCLUDED

#include <sc.h>

/* Global structures containing calibration constants */
int SC_NPADDLES = 342;
int SC_NPADDLES_SEC = 57;
int SC_VERSION_FLAG = 2;
sc_const_t sc_t0,sc_t0u;
sc_const_t sc_t1,sc_t1u;
sc_const_t sc_t2,sc_t2u;
sc_const_t sc_pedestals,sc_pedu;
sc_const_t sc_m0,sc_m0u;
sc_const_t sc_walk0,sc_walk0u;
sc_const_t sc_walk1,sc_walk1u;
sc_const_t sc_walk2,sc_walk2u;
sc_const_t sc_veff,sc_veffu;
sc_const_t sc_lambda,sc_lambdau;
sc_const_t sc_tsig0;
sc_const_t sc_tsig1;
sc_int_const_t sc_status,sc_swapindex;
float yoffset[SC_NPADDLES_TOTAL]; 
float paddle1[54];
float paddle2[54];
float adc_ref;
float pulse_norm;

#endif









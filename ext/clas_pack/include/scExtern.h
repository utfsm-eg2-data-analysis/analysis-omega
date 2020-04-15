#ifndef scExternH_INCLUDED
#define scExternH_INCLUDED

#include <sc.h>

/* External  structures containing calibration constants */
extern int SC_NPADDLES;
extern int SC_NPADDLES_SEC;
extern int SC_VERSION_FLAG;
extern sc_const_t sc_t0,sc_t0u;
extern sc_const_t sc_t1,sc_t1u;
extern sc_const_t sc_t2,sc_t2u;
extern sc_const_t sc_pedestals,sc_pedu;
extern sc_const_t sc_m0,sc_m0u;
extern sc_const_t sc_walk0,sc_walk0u;
extern sc_const_t sc_walk1,sc_walk1u;
extern sc_const_t sc_walk2,sc_walk2u;
extern sc_const_t sc_veff,sc_veffu;
extern sc_const_t sc_lambda,sc_lambdau;
extern sc_const_t sc_tsig0;
extern sc_const_t sc_tsig1;
extern sc_int_const_t sc_status,sc_swapindex;
extern float yoffset[SC_NPADDLES_TOTAL]; 
extern float paddle1[54];
extern float paddle2[54];
extern float adc_ref;
extern float pulse_norm;

#endif












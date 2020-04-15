#ifndef g1cPcor_H
#define g1cPcor_H

#include <kinematics.h>

extern "C" {

void InitPcor();

void initpcor_();

vector4_t g1cPcor(vector4_t p4, int sector, int q);

void g1cpcor_(float *p3, int *sector, int *q);

float g1cTAGRcor(float epho, float E0, int runID);

void g1ctagrcor_(float *epho, float *E0, int *runID);

vector4_t g1cDCeloss(vector4_t p4, int sector);

void g1cdceloss_(float *p4, int *sector);

vector4_t g1cMomCor(vector4_t p4,int sector, int q);

void g1cmomcor_(float *p4,int *sector,int *q);

}

#endif

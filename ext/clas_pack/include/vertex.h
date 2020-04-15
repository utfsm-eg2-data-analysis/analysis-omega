/* vertex.h
    define a set of structures used in finding detached vertices
*/

#ifndef vertexH_INCLUDED
#define vertexH_INCLUDED


#include <ntypes.h>

typedef struct {
  vector3_t point;
  vector3_t dir;
}  line_t;

void vertex_brun(int runno);
void vertex_brun_(int *runno); /*wrapper for fortran users*/
void make_vert();
void make_vert_(); /*wrapper for fortran users*/
void make_mvrt();
void make_mvrt_();

extern int mtv(int *tracks, int ntrk,vector3_t *vert,float Cmat[9],float *chi2,int *iter); 
extern int mtv_(int *tracks, int *ntrk,vector3_t *vert,float Cmat[9],float *chi2,int *iter);                      /*Fortran wrapper for C++ routine*/






#endif

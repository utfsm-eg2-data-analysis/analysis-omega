/*
 * trackswim.h
 *
*/

#ifndef TRACKMODELH_INCLUDED
#define TRACKMODELH_INCLUDED

/*
 * For full documentation, see:
 *
 * http://lemond.phy.bnl.gov/documentation/trackswim.html
*/



#include <ntypes.h>

/*
 * Flags used in the 'trk3_xxx()' calls:
*/

#define SWIM_DBG_TRACE    0x0001
#define SWIM_F_FORWARD    0x0002
#define SWIM_F_BACKWARD   0x0004

/*
 * Boundary subvolume
*/

typedef struct     /* imagine a plane perpendicular to the Z axis */
{
  double ux[3];        /* unit vector in the X direction */
  double xmin,xmax;    /* size of the plane in the X direction */

  double uy[3];        /* unit vector in the Y direction (UP) */
  double ymin,ymax;    /* size of the plane in the Y direction */

} trk_planeLimits_t;


int trackswim_init(void);

/*
 * Arguments to all routines:
 *
 * trk_xxx define the track as an array: (x,y,z,qp,dpx,dpy,dpz),
 *                     where x,y,z are the starting point,
 *                           qp is q/p - charge divided by momentum magnitude
 *                           dpx,dpy,dpz are the momentum unit vector
 *
 * trk3_xxx define the track as an array: v, p and charge,
 *                     where v is the starting point,
 *                           p is the momentum
 *                           charge is the charge (positive, negative or zero).
 *
 * trk3p_xxx define the track as an array: v, punit and qp,
 *                     where v is the starting point,
 *                           punit is the momentum magnitude
 *                           qp is q/p - charge divided by momentum.
 *
*/

/* Routines to swim a given distance along the track. Distance can be positive or negative */

int trk_swimAway(double trk[7],double dist);
int trk3_swimAway(vector3_t *v,vector3_t *p,int charge,float dist,int flags);
int trk3p_swimAway(vector3_t *v,vector3_t *punit,float qp,float dist,int flags);

/* Routines to swim to a plane.
 *
 * The plane is defined as 'dnorm' - normal vector and
 *                         'dpos'  - distance from point (0,0,0)
 *
 * 'box' defines the volume to swim in. If it is set to NULL, to swimming subvolume is unlimited.
*/

int trk_swimToPlane(double trk[7],const char dname[],
		    const double dnorm[3],double dpos,
		    const trk_planeLimits_t *box);

int trk3_swimToPlane(vector3_t *v,vector3_t *p,int charge,
		     const char *planeName,
		     const vector3_t *dnorm,float dpos,
		     const trk_planeLimits_t *box,
		     int flags);

int trk3p_swimToPlane(vector3_t *v,vector3_t *punit,float qp,
		      const char *planeName,
		      const vector3_t *dnorm,float dpos,
		      const trk_planeLimits_t *box,
		      int flags);

/* Routines to swim to a point in space */

int trk_swimToV(double trk[7],const double target[3]);

int trk3_swimToV(vector3_t *v,vector3_t *p,int charge,const vector3_t *target,int flags);
int trk3p_swimToV(vector3_t *v,vector3_t *punit,float qp,const vector3_t *target,int flags);

/* Routines to swim to a Cylinder
 *
 * The target cylinder is defined by it's 'center', 'axis' and 'radius'.
*/

int trk3_swimToCyl(vector3_t *v,vector3_t *p,int charge,
		   const vector3_t *center,const vector3_t *axis,float radius,float length,
		   int flags);

int trk3p_swimToCyl(vector3_t *v,vector3_t *punit,float qp,
		    const vector3_t *center,const vector3_t *axis,float radius,float length,
		    int flags);

#endif
/* end file */

// g11 monte carlo smearing header file -*- C++ -*-
#ifndef _smear_mc_H
#define _smear_mc_H

extern "C" { // 'dumb it down' for c and fortran
//_____________________________________________________________________________

  // Initialize the random number generator:
  /* C/C++ Function:
   * Parameter: seed   Seeding for random number generator
   */
  void InitSmearMC(int __seed);

  /* FORTRAN Subroutine:
   * Parameter: seed   Seeding for random number generator
   */
  void InitSmearMC_(int *__seed);
//_____________________________________________________________________________

  // Smear Momentum
  /* C/C++ Function:
   * Parameters: p3[3]          Input 3-momentum [x,y,z]
   *             mass           Particle's mass in GeV
   *             sig_p_track    Tracking error for p
   *             sig_lam_track  Tracking error for lambda 
   *             sig_phi_track  Tracking error for phi
   *             q              Charge(ex 1 for proton)
   *             p3smear[3]     Smeared 3-momentum
   */
  void SmearMomentum(const float __p3[3],float __mass,float __sig_p_track,
		     float __sig_lam_track,float __sig_phi_track,int __q,
		     float __p3smear[3]);

  /* FORTRAN Subroutine:
   * Parameters: p3[3]          Input 3-momentum [x,y,z]
   *             mass           Particle's mass in GeV
   *             sig_p_track    Tracking error for p
   *             sig_lam_track  Tracking error for lambda 
   *             sig_phi_track  Tracking error for phi
   *             q              Charge(ex 1 for proton)
   *             p3smear[3]     Smeared 3-momentum
   */
  void SmearMomentum_(float __p3[3],float *__mass,float *__sig_p_track,
		      float *__sig_lam_track,float *__sig_phi_track,int *__q,
		      float __p3smear[3]);

//_____________________________________________________________________________
}
#endif /* _smear_mc_H */

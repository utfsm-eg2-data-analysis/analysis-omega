/*************************************************/
/*  Particle.h                                   */
/*                                               */
/*  Created by Orlando Soto, CCTVAL              */
/*  Modified for omega by Andrés Bórquez, CCTVAL */
/*                                               */
/*************************************************/

#include <vector>
#include <sys/stat.h>
#include <cstdarg>
#include <algorithm>
#include <map>
#include <string>

#include "TSpectrum.h"
#include "Riostream.h"
#include "TROOT.h"
#include "TClasTool.h"
#include "TIdentificator.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TLatex.h"
#include "TDatabasePDG.h"
#include "TParticlePDG.h"
#include "TMatrixD.h"
#include "TClonesArray.h"

#include "do_pid.h"

class Particle: public TLorentzVector {
public:
  Float_t vx, vy, vz, pid, time;
  //TParticlePDG *info; 
  
  Particle() : TLorentzVector(), vx(0),vy(0),vz(0),pid(0),time(0) {}
  
  Particle(Float_t px,Float_t py, Float_t pz, Float_t e, Float_t x, Float_t y, Float_t z, Float_t pid=0, Float_t t=0): TLorentzVector(px,py,pz,e),vx(x),vy(y),vz(z),pid(pid),time(t){}
  
  Particle(TLorentzVector lv, Float_t x=0, Float_t y=0, Float_t z=0, Float_t pid=0, Float_t t=0): TLorentzVector(lv), vx(x),vy(y),vz(z),pid(pid),time(time){}
  
  Particle(Particle &p):vx(p.vx),vy(p.vy),vz(p.vz),pid(p.pid),time(p.time) {
    SetVect(p.Vect());
    SetT(p.T());
  }
  
  inline Double_t P2() const {
    return P()*P();
  }
  
  //const: the object that owns the method will not be modified by this method         
  inline Particle operator + (const Particle & q) const {
    Particle p;
    p.SetVect(Vect() + q.Vect());
    p.SetT(E() + q.T());
    return p;
  }
   
  // Converts x,y,z EC hit in CLAS coordinate system                                                                 
  // into u,v,w distances of the EC hit, and then test the fiducial cut. (Phonetic names)
  inline Bool_t checkFiducial() {
    
    Bool_t test = kFALSE;
    Float_t ex = 0., wy = 0., zd = 0., yu = 0., ve = 0., wu = 0., xi = 0., yi = 0., zi = 0., ec_phy = 0., phy = 0., ro	\
      t[3][3];

    // Parameters                                                                                                      
    Float_t ec_the = 0.4363323;
    Float_t ylow = -182.974;
    Float_t yhi = 189.956;
    Float_t tgrho = 1.95325;
    Float_t sinrho = 0.8901256;
    Float_t cosrho = 0.455715;

    // Variables
    ex = vx;
    wy = vy;
    zd = vz;

    phy = TMath::ATan2(wy,ex)*57.29578;
    
    if (phy < 0.) phy = phy + 360;
    phy = phy+30.;
    if (phy > 360.) phy = phy - 360.;

    ec_phy = ((Int_t) (phy/60.))*1.0471975;

    rot[0][0] = TMath::Cos(ec_the)*TMath::Cos(ec_phy);
    rot[0][1] = -TMath::Sin(ec_phy);
    rot[0][2] = TMath::Sin(ec_the)*TMath::Cos(ec_phy);
    rot[1][0] = TMath::Cos(ec_the)*TMath::Sin(ec_phy);
    rot[1][1] = TMath::Cos(ec_phy);
    rot[1][2] = TMath::Sin(ec_the)*TMath::Sin(ec_phy);
    rot[2][0] = -TMath::Sin(ec_the);
    rot[2][1] = 0.;
    rot[2][2] = TMath::Cos(ec_the);

    yi = ex*rot[0][0] + wy*rot[1][0] + zd*rot[2][0];
    xi = ex*rot[0][1] + wy*rot[1][1] + zd*rot[2][1];
    zi = ex*rot[0][2] + wy*rot[1][2] + zd*rot[2][2];
    zi = zi - 510.32 ;

    yu = (yi - ylow)/sinrho;
    ve = (yhi - ylow)/tgrho - xi + (yhi-yi)/tgrho;
    wu = ((yhi - ylow)/tgrho + xi + (yhi-yi)/tgrho)/2./cosrho;

    //U in ]40, 410[ , V in [0,370[ and W in [0,410[.)                                                                  
    if ((40<yu&&yu<410) && (ve<370)  && (wu<410))
      test=kTRUE;
    //    TVector3 * result3= new TVector3(yu,ve,wu);
    return test;
  }

  inline Particle operator += (const Particle & q) {
    SetVect(Vect() + q.Vect());
    SetT(E() + q.T());
    return *this;
  }
  
  const char *getName() {
    return ((TDatabasePDG::Instance())->GetParticle(pid))->GetName();
  }
};

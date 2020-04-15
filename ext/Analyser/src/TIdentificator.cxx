#include "TIdentificator.h"
#include "massConst.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

const Double_t kFidThetaMax = 54;

// For FidThetaMin calculation for electron
const Double_t kThetaPar0[6] = { 15        , 15        ,  15       , 15        ,  13       ,  13        };
const Double_t kThetaPar1[6] = { -0.425145 , -1.02217  , -0.7837   , -1.47798  ,   3.47361 ,   3.5714   };
const Double_t kThetaPar2[6] = { -0.666294 , -0.616567 , -0.673602 , -0.647113 ,  -0.34459 ,  -0.398458 };
const Double_t kThetaPar3[6] = {  5.73077  ,  5.51799  ,  8.05224  ,  7.74737  ,   8.45226 ,   9.54265  };
const Double_t kThetaPar4[6] = { 10.4976   , 14.0557   , 15.2178   , 16.7291   , -63.4556  , -22.649    };
const Double_t kThetaPar5[6] = { -1.13254  , -1.16189  , -2.08386  , -1.79939  ,  -3.3791  ,  -1.89746  };

// For parameter 0 of the FidPhiMin calculation for electron
const Double_t kFidPar0Low0[6] = {  25      ,  25        ,  25       ,  24.6345  ,  23.4731  ,  24.8599  };
const Double_t kFidPar0Low1[6] = { -12      , -12        , -12       , -12       , -12       , -12       };
const Double_t kFidPar0Low2[6] = {   0.5605 ,   0.714261 ,  0.616788 ,   0.62982 ,   1.84236 ,   1.00513 };
const Double_t kFidPar0Low3[6] = {  4.4     ,  4.4       ,  4.4      ,   4.4     ,   4.4     ,   4.4     };

// For parameter 1 of the FidPhiMin calculation for electron
const Double_t kFidPar1Low0[6] = {  2.1945   ,  4        ,  3.3352  ,  2.22769   ,  1.63143   ,  3.19807  };
const Double_t kFidPar1Low1[6] = {  1.51417  ,  1.56882  ,  2       ,  2         ,  1.90179   ,  0.173168 };
const Double_t kFidPar1Low2[6] = { -0.354081 , -2        , -2       , -0.760895  , -0.213751  , -0.1      };
const Double_t kFidPar1Low3[6] = {  0.5      ,  0.5      ,  1.01681 ,  1.31808   ,  0.786844  ,  1.6      };

// For parameter 0 of the FidPhiMax calculation for electron
const Double_t kFidPar0High0[6] = { 25       ,  25        ,  25        ,  25        ,  23.7067  ,  25       };
const Double_t kFidPar0High1[6] = { -8       , -10.3277   , -12        , -11.3361   , -12       , -11.4641  };
const Double_t kFidPar0High2[6] = {  0.479446 ,  0.380908 ,   0.675835 ,   0.636018 ,   2.92146 ,   0.55553 };
const Double_t kFidPar0High3[6] = {  4.8      ,  4.79964  ,   4.4      ,   4.4815   ,   4.4     ,   4.41327 };

// For parameter 1 of the FidPhiMax calculation for electron
const Double_t kFidPar1High0[6] = {  3.57349 ,  3.02279  ,  2.02102 ,  3.1948   ,  3.0934   ,  2.48828 };
const Double_t kFidPar1High1[6] = {  2       ,  0.966175 ,  2       ,  0.192701 ,  0.821726 ,  2       };
const Double_t kFidPar1High2[6] = { -2       , -2        , -1.70021 , -1.27578  , -0.233492 , -2       };
const Double_t kFidPar1High3[6] = {  0.5     ,  0.527823 ,  0.68655 ,  1.6      ,  1.6      ,  0.70261 };

// For FidThetaMinPiPlus calculation for pi+
const Double_t kThetaPar0PiPlus[6] = {  7.00823   ,  5.5        ,  7.06596   ,  6.32763   ,  5.5       ,  5.5      };
const Double_t kThetaPar1PiPlus[6] = {  0.207249  ,  0.1        ,  0.127764  ,  0.1       ,  0.211012  ,  0.281549 };
const Double_t kThetaPar2PiPlus[6] = {  0.169287  ,  0.506354   , -0.0663754 ,  0.221727  ,  0.640963  ,  0.358452 };
const Double_t kThetaPar3PiPlus[6] = {  0.1       ,  0.1        ,  0.100003  ,  0.1       ,  0.1       ,  0.1      };
const Double_t kThetaPar4PiPlus[6] = {  0.1       ,  3.30779    ,  4.499     ,  5.30981   ,  3.20347   ,  0.776161 };
const Double_t kThetaPar5PiPlus[6] = { -0.1       , -0.651811   , -3.1793    , -3.3461    , -1.10808   , -0.462045 };

// For parameter 0 of the FidPhiMinPiPlus calculation for pi+
const Double_t kFidPar0Low0PiPlus[6] = {  25.      ,  25.      ,  25.     ,  25.       ,  25.       ,  25.       };
const Double_t kFidPar0Low1PiPlus[6] = { -12.      , -12.      , -12.     , -12        , -12        , -12        };
const Double_t kFidPar0Low2PiPlus[6] = {   1.64476 ,   1.51915 ,   1.1095 ,   0.977829 ,   0.955366 ,   0.969146 };
const Double_t kFidPar0Low3PiPlus[6] = {   4.4     ,   4.4     ,   4.4    ,   4.4      ,   4.4      ,   4.4      };

// For parameter 1 of the FidPhiMinPiPlus calculation for pi+
const Double_t kFidPar1Low0PiPlus[6] = {  4.        ,  4.   ,  2.78427 ,  3.58539 ,  3.32277   ,  4.      };
const Double_t kFidPar1Low1PiPlus[6] = {  2.        ,  2.   ,  2.      ,  1.38233 ,  0.0410601 ,  2.      };
const Double_t kFidPar1Low2PiPlus[6] = { -0.978469  , -2.   , -1.73543 , -2.      , -0.953828  , -2.      };
const Double_t kFidPar1Low3PiPlus[6] = {  0.5       ,  0.5  ,  0.5     ,  0.5     ,  0.5       ,  1.08576 };

// For parameter 0 of the FidPhiMaxPiPlus calculation for pi+
const Double_t kFidPar0High0PiPlus[6] = {  25.      , 24.8096  , 24.8758  ,  25.       , 25.       , 25.      };
const Double_t kFidPar0High1PiPlus[6] = { -11.9735  , -8.      , -8.      , -12.       , -8.52574  , -8.      };
const Double_t kFidPar0High2PiPlus[6] = {  0.803484 ,  0.85143 ,  1.01249 ,   0.910994 ,  0.682825 ,  0.88846 };
const Double_t kFidPar0High3PiPlus[6] = {  4.40024  ,  4.8     ,  4.8     ,   4.4      ,  4.79866  ,  4.8     };

// For parameter 1 of the FidPhiMaxPiPlus calculation for pi+
const Double_t kFidPar1High0PiPlus[6] = {  2.53606  ,  2.65468  ,  3.17084 ,  2.47156 ,  2.42349  ,  2.64394 };
const Double_t kFidPar1High1PiPlus[6] = {  0.442034 ,  0.201149 ,  1.27519 ,  1.76076 ,  1.25399  ,  0.15892 };
const Double_t kFidPar1High2PiPlus[6] = { -2.       , -0.179631 , -2.      , -1.89436 , -2.       , -2.      };
const Double_t kFidPar1High3PiPlus[6] = {  1.02806  ,  1.6      ,  0.5     ,  1.03961 ,  0.815707 ,  1.31013 };

// sampling fraction correction, electrons.
const Double_t kMeanFePar[6][3]={{0.222404,0.0222688,-0.0024153},
                       {0.234623,0.0194985,-0.00208357},
                       {0.252287,0.024248,-0.00338846},
                       {0.250946,0.0208409,-0.00326824},
                       {0.271956,0.0118487,-0.00187084},
                       {0.252613,0.022819,-0.00311242}};

const Double_t kSigmaFePar[6][2]={{9.23027e-03,2.98343e-02},
                       {8.66367e-03,3.08858e-02},
                       {1.07826e-02,2.63854e-02},
                       {7.22581e-03,2.98809e-02},
                       {1.84073e-02,3.48029e-02},
                       {4.11461e-03,3.55081e-02}};


const Double_t kMeanCPar[6][3]={{0.252164,0.0122263,-0.000793937},
                          {0.278574,0.0187482,-0.00238217},
                          {0.262079,0.0230685,-0.00354741},
                          {0.251108,0.0201568,-0.00332367},
                          {0.263396,0.00955238,-0.00102038},
                          {0.255245,0.0232659,-0.00304798}};

const Double_t kSigmaCPar[6][2]={{9.55113e-03,3.40672e-02},
                       {1.39889e-02,3.74682e-02},
                       {9.32762e-03,2.90046e-02},
                       {8.21055e-03,2.98893e-02},
                       {2.25684e-02,3.06508e-02},
                       {1.17254e-02,3.64221e-02}};

const Double_t kMeanPbPar[6][3]={{0.253431,0.0138251,-0.0014016},
                       {0.249059,0.0147784,-0.00148693},
                       {0.254573,0.022589,-0.00305686},
                       {0.255589,0.0190419,-0.00305263},
                       {0.276739,0.0111585,-0.00175784},
                       {0.262587,0.0191659,-0.0026264}};

const Double_t kSigmaPbPar[6][2]={{7.67408e-03,3.54391e-02},
                       {7.52798e-03,3.38371e-02},
                       {8.13241e-03,2.77300e-02},
                       {7.20303e-03,3.03627e-02},
                       {1.80841e-02,3.53020e-02},
                       {1.99220e-03,3.76172e-02}};


ClassImp(TIdentificator);

TIdentificator::TIdentificator(TClasTool *CT)
  : kEbeam(5.014), kMpi(0.139570), kMprt(0.938272), kMntr(0.939565), kGOOD(-1000.)
{
    // Create a TIdentificator object, related to CT.
    this->fCT = CT;    
}



TIdentificator::~TIdentificator()
{
    // Default destructor for TIdentificator.
    fCT = 0;
}

Double_t TIdentificator::Momentum(Int_t k, Bool_t kind)
{
    // Return the full momentum for the particle in the row k of the EVNT
    // bank.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if (kind == 0) {
        return sqrt(Px(k) * Px(k) + Py(k) * Py(k) + Pz(k) * Pz(k));
    } else {                            // Fix this in case kind != 1
        return sqrt(Px(k,1) * Px(k,1) + Py(k,1) * Py(k,1) + Pz(k,1) * Pz(k,1));
    }
}



Double_t TIdentificator::Moment(Int_t k, Bool_t kind)
{
    // Deprecated. Use Momentum.

    if (kind == 0) {
        fEVNT = (TEVNTClass *) fCT->GetBankRow("EVNT", k);
        return sqrt(fEVNT->Px * fEVNT->Px + fEVNT->Py * fEVNT->Py +
                    fEVNT->Pz * fEVNT->Pz);
    } else {                            // Fix this in case kind != 1
        fGSIM = (TGSIMClass *) fCT->GetBankRow("GSIM", k);
        return sqrt(fGSIM->Px * fGSIM->Px + fGSIM->Py * fGSIM->Py +
                    fGSIM->Pz * fGSIM->Pz);
    }
}



Double_t TIdentificator::Mass2(Int_t k, Bool_t kind)
{
    // Return the mass squared for the particle in the row k of the EVNT bank.

    if (kind == 0) {
        return Momentum(k) * Momentum(k) * (pow(Betta(k), -2) - 1);
    } else {
        return Momentum(k,1) * Momentum(k,1) * (pow(Betta(k,1), -2) - 1);
    }
}



Double_t TIdentificator::ThetaLab(Int_t k, Bool_t kind)
{
    // Return the polar angle in Lab frame for the particle in the row k of
    // the EVNT bank.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    Double_t theta_val;

    if (kind == 0)
    {
        TVector3 v3p(Px(k), Py(k), Pz(k));
        theta_val = v3p.Theta() * 180. / TMath::Pi();
    } else {                            // Fix this in case k != 1
        TVector3 v3p(Px(k,1), Py(k,1), Pz(k,1));
        theta_val = v3p.Theta() * 180. / TMath::Pi();
    }

    return theta_val;
}



Double_t TIdentificator::PhiLab(Int_t k, Bool_t kind)
{
    // Return the azimuthal angle in Lab frame for the particle in the row k
    // of the EVNT bank.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    Double_t phi_val;

    if (kind == 0) {
        TVector3 v3p(Px(k), Py(k), Pz(k));
        phi_val = v3p.Phi() * 180. / TMath::Pi();
    } else {
        TVector3 v3p(Px(k,1), Py(k,1), Pz(k,1));
        phi_val = v3p.Phi() * 180. / TMath::Pi();
    }

    if (phi_val < -30.)
        phi_val += 360.;
    else if (phi_val > 330.)
        phi_val -= 360.;

    return phi_val;
}



Double_t TIdentificator::ThetaVirtLab(Bool_t kind) // Check if it is correct !!!
{
    // Return the polar angle of the virtual photon in Lab frame, for the
    // particle in the row k of the EVNT bank.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    Double_t theta_virt;

    if(kind==0) 
        theta_virt=acos((kEbeam-Momentum(0)*cos(ThetaLab(0)*TMath::Pi()/180.))/(sqrt(Q2()+Nu()*Nu())));
    else
        theta_virt=acos((kEbeam-Momentum(0,1)*cos(ThetaLab(0,1)*TMath::Pi()/180.))/(sqrt(Q2(1)+Nu(1)*Nu(1))));
    return theta_virt;
}



Double_t TIdentificator::PhiVirtLab(Bool_t kind) // Check if it is correct !!!
{
    // Return the azimuthal angle of the virtual photon in Lab frame, for the
    // particle in the row k of the EVNT bank.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.
    if(PhiLab(0,kind) > 0) 
        return (-180.+PhiLab(0,kind));
    else 
        return (180.+PhiLab(0,kind));
}


Double_t TIdentificator::ThetaPQ(Int_t k, Bool_t kind)
{
    // Return the polar angle of the born particle in respect to virtual
    // photon direction, for the particle in the row k of the EVNT bank. It
    // doesn't apply for electron.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    Double_t theta_pq;
    if(kind==0){
        TVector3 Vpi(Px(k),Py(k),Pz(k));
        TVector3 Vvirt(-Px(0),-Py(0),kEbeam-Pz(0));
        theta_pq=Vvirt.Angle(Vpi)*180./(TMath::Pi());
    }
    else {
        TVector3 Vpi(Px(k,1),Py(k,1),Pz(k,1));
        TVector3 Vvirt(-Px(0,1),-Py(0,1),kEbeam-Pz(0,1));
        theta_pq=Vvirt.Angle(Vpi)*180./(TMath::Pi());
    }
    return theta_pq;
}



Double_t TIdentificator::PhiPQ(Int_t k, Bool_t kind)
{
    // Return the azimuthal angle of the born particle in respect to virtual
    // photon direction, for the particle in the row k of the EVNT bank. It
    // doesn't apply for electron.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    Double_t phi_pq;
    if(kind==0){
        TVector3 Vpi(Px(k),Py(k),Pz(k));
        TVector3 Vvirt(-Px(0),-Py(0),kEbeam-Pz(0));
        Double_t phi_z = TMath::Pi()-Vvirt.Phi();
        Vvirt.RotateZ(phi_z);
        Vpi.RotateZ(phi_z);
        TVector3 Vhelp(0.,0.,1.);
        Double_t phi_y = Vvirt.Angle(Vhelp);
        Vvirt.RotateY(phi_y);
        Vpi.RotateY(phi_y);
        phi_pq=Vpi.Phi() * 180./(TMath::Pi());
    }
    else {
        TVector3 Vpi(Px(k,1),Py(k,1),Pz(k,1));
        TVector3 Vvirt(-Px(0,1),-Py(0,1),kEbeam-Pz(0,1));
        Double_t phi_z = TMath::Pi()-Vvirt.Phi();
        Vvirt.RotateZ(phi_z);
        Vpi.RotateZ(phi_z);
        TVector3 Vhelp(0.,0.,1.);
        Double_t phi_y=Vvirt.Angle(Vhelp);
        Vvirt.RotateY(phi_y);
        Vpi.RotateY(phi_y);
        phi_pq = Vpi.Phi() * 180./(TMath::Pi());
    }
    return phi_pq;
}



Double_t TIdentificator::CosThetaPQ(Int_t k, Bool_t kind)
{
    // Return the cosine of ThetaPQ, for the particle in the row k of the EVNT
    // bank. It doesn't apply for electron.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if (kind == 0)
        return (Pz(k) * (kEbeam - Pz(0)) - Px(k) * Px(0) - Py(k) * Py(0)) /
                            (sqrt(Nu() * Nu() + Q2()) * Momentum(k));
    else                                // Fix this in case kind != 1
        return (Pz(k,1) * (kEbeam - Pz(0,1)) - Px(k,1) * Px(0,1) -
                Py(k,1) * Py(0,1)) /
                            (sqrt(Nu(1) * Nu(1) + Q2(1)) * Momentum(k,1));
}

Double_t TIdentificator::Pt2(Int_t k, Bool_t kind)
{
    if (kind == 0)
        return Momentum(k) * Momentum(k) *
                            (1 - CosThetaPQ(k) * CosThetaPQ(k));
    else                                // Fix this in case k != 1
        return Momentum(k,1) * Momentum(k,1) *
                            (1 - CosThetaPQ(k,1) * CosThetaPQ(k,1));
}

Double_t TIdentificator::Pl2(Int_t k, Bool_t kind)
{
    if (kind == 0)
        return Momentum(k) * Momentum(k) * CosThetaPQ(k) * CosThetaPQ(k);
    else                                // Fix this in case k != 1
        return Momentum(k,1) * Momentum(k,1) * CosThetaPQ(k,1) * CosThetaPQ(k,1);
}

Double_t TIdentificator::PlCM(Int_t k, Bool_t kind)
{
    if (kind == 0)
      return (Nu() + kMprt) * (TMath::Sqrt(Pl2(k)) - TMath::Sqrt(Q2() + Nu() * Nu()) * Zh(k) * Nu() / (Nu() + kMprt)) / W();
    else                                // Fix this in case k != 1
      return (Nu(1) + kMprt) * (TMath::Sqrt(Pl2(k,1)) - TMath::Sqrt(Q2(1) + Nu(1) * Nu(1)) * Zh(k,1) * Nu(1) / (Nu(1) + kMprt)) / W(1);
}

Double_t TIdentificator::PmaxCM(Bool_t kind)
{
    if (kind == 0)
      return TMath::Sqrt(TMath::Power(W() * W() - kMntr * kMntr + kMpi * kMpi, 2) - 4. * kMpi * kMpi * W() * W()) / 2. / W();
    else                                // Fix this in case k != 1
      return TMath::Sqrt(TMath::Power(W(1) * W(1) - kMntr * kMntr + kMpi * kMpi, 2) - 4. * kMpi * kMpi * W(1) * W(1)) / 2. / W(1);
}


Double_t TIdentificator::PTrans2PQ(Int_t k, Bool_t kind)
{
    // Return the momentum transverse component squared of the born particle
    // in respect to virtual photon direction, for the particle in the row k
    // of the EVNT bank. It doesn't apply for electron.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if (kind == 0)
        return Momentum(k) * Momentum(k) *
                            (1 - CosThetaPQ(k) * CosThetaPQ(k));
    else                                // Fix this in case kind != 1
        return Momentum(k,1) * Momentum(k,1) *
                            (1 - CosThetaPQ(k,1) * CosThetaPQ(k,1));
}



Double_t TIdentificator::PLong2PQ(Int_t k, Bool_t kind)
{
    // Return the momentum longitudinal component squared of the born particle
    // in respect to virtual photon direction, for the particle in the row k
    // of the EVNT bank. It doesn't apply for electron.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if (kind == 0)
        return Momentum(k) * Momentum(k) * CosThetaPQ(k) * CosThetaPQ(k);
    else                                // Fix this in case kind != 1
        return Momentum(k,1) * Momentum(k,1) * CosThetaPQ(k,1) * CosThetaPQ(k,1);
}



Int_t TIdentificator::Sector(Int_t k, Bool_t kind) // Check if it is correct !!! Add k==1
{
    // Return the sector of the CLAS detector where the particle was detected,
    // for the particle in the row k of the EVNT bank.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if ( kind == 0) {
        if (PhiLab(k) != 330.)
            return int((PhiLab(k) + 90.) / 60.) - 1;
        else return 5;
    } else {
        if (PhiLab(k,1) != 330.)
            return int((PhiLab(k,1) + 90.) / 60.) - 1;
        else return 5;
    }
}



Double_t TIdentificator::Q2(Bool_t kind)
{
    // Return the four-momentum transfer of the electron-nucleon interaction.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.
    if (kind == 0) {
        return 4. * kEbeam * Momentum(0) *
	  sin(ThetaLab(0)*TMath::Pi()/180./2) * sin(ThetaLab(0)*TMath::Pi()/180./2);
    } else {                            // Fix this in case k != 1
        return 4. * kEbeam * Momentum(0,1) *
	  sin(ThetaLab(0,1)*TMath::Pi()/180./2) * sin(ThetaLab(0,1)*TMath::Pi()/180./2);
    }
}



Double_t TIdentificator::W(Bool_t kind)
{
    // Return the invariant mass of the electron-nucleon interaction.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if (kind == 0) {
         return TMath::Sqrt(kMprt * kMprt + 2. * kMprt * Nu() - Q2());
    } else {                            // Fix this in case k != 1
         return TMath::Sqrt(kMprt * kMprt + 2. * kMprt * Nu(1) - Q2(1));
    }
}



Double_t TIdentificator::Nu(Bool_t kind)
{
    // Return the energy transfer of the electron-nucleon interaction.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if (kind == 0) {
        return kEbeam - Momentum(0);
    } else {                            // Fix this in case k != 1
        return kEbeam - Momentum(0,1);
    }
}



Double_t TIdentificator::Xb(Bool_t kind)
{
    if (kind == 0) {
         return Q2() / 2. / Nu() / kMprt;
    } else {                            // Fix this in case k != 1
         return Q2(1) / 2. / Nu(1) / kMprt;
    }
}



Double_t TIdentificator::Yb(Bool_t kind) /**/
{
    /*if (kind == 0)
        return Nu(0) / kEbeam;
    else
        return Nu(1) / kEbeam;*/
    if (kind == 0) {
        return Nu() / kEbeam;
    } else {                            // Fix this in case k != 1
        return Nu() / kEbeam;
    }        
}

Double_t TIdentificator::Zh(Int_t k, Bool_t kind, Double_t Mass)
{
    if (kind == 0)
        return sqrt(Mass * Mass + Momentum(k) * Momentum(k)) / Nu();
    else                                // Fix this in case k != 1
        return sqrt(Mass * Mass + Momentum(k,1) * Momentum(k,1)) / Nu(1);
}

Double_t TIdentificator::Xf(Int_t k, Bool_t kind)
{
    if (kind == 0)
      return PlCM(k) / PmaxCM();
    else                                // Fix this in case k != 1
      return PlCM(k,1) / PmaxCM(1);
}

Double_t TIdentificator::Mx2(Int_t k, Bool_t kind)
{
    if (kind == 0)
      return W() * W() - 2. * Nu() * Zh(k) * (Nu() + kMprt) + kMpi * kMpi + 2. * TMath::Sqrt((Q2() + Nu() * Nu()) * Pl2(k));
    else                                // Fix this in case k != 1
      return W(1) * W(1) - 2. * Nu(1) * Zh(k,1) * (Nu(1) + kMprt) + kMpi * kMpi + 2. * TMath::Sqrt((Q2(1) + Nu(1) * Nu(1)) * Pl2(k,1));
}

Double_t TIdentificator::T(Int_t k, Bool_t kind)
{
    if (kind == 0)
      return 2. * TMath::Sqrt((Nu() * Nu() + Q2()) * Pl2(k)) + kMpi * kMpi - Q2() - 2. * Nu() * Nu() * Zh(k);
    else                                // Fix this in case k != 1
      return 2. * TMath::Sqrt((Nu(1) * Nu(1) + Q2(1)) * Pl2(k,1)) + kMpi * kMpi - Q2(1) - 2. * Nu(1) * Nu(1) * Zh(k,1);
}


Double_t TIdentificator::ZhPi(Int_t k, Double_t Mass, Bool_t kind) // name needs to be switched
{
    // Return the energy fraction of the born particle, for the particle in
    // the row k of the EVNT bank. It doesn't apply for electron.
    //
    // If kind is zero, the EVNT bank is used. If not, the GSIM bank is used
    // instead.

    if (kind == 0)
        return sqrt(Mass * Mass + Momentum(k) * Momentum(k)) / Nu(0);
    else                                // Fix this in case kind != 1
        return sqrt(Mass * Mass + Momentum(k,1) * Momentum(k,1)) / Nu(1);
}



Double_t TIdentificator::TimeCorr4(Double_t mass, Int_t k)
{
    return (PathSC(0)/30.) - TimeSC(0) + TimeSC(k) - 0.08 -
                (PathSC(k) / 30.) * sqrt(pow(mass/Momentum(k),2) + 1);
}

Double_t TIdentificator::FidTheta(Int_t k, Bool_t kind)
{
    Double_t fid_theta_val;

    if (kind == 0)
    {
        TVector3 v3p(Px(k), Py(k), Pz(k));
        fid_theta_val = v3p.Theta() * 180 / TMath::Pi();
    } else {
        TVector3 v3p(Px(k,1), Py(k,1), Pz(k,1));
        fid_theta_val = v3p.Theta() * 180 / TMath::Pi();
    }

    return fid_theta_val;
}



Double_t TIdentificator::FidThetaMin()
{
    Int_t sector = Sector(0);

    Double_t theta_min_val = kThetaPar0[sector] +
            kThetaPar1[sector] / pow(Momentum(0),2) +
            kThetaPar2[sector] * Momentum(0) +
            kThetaPar3[sector] / Momentum(0) +
            kThetaPar4[sector] *exp(kThetaPar5[sector] * Momentum(0));

    return theta_min_val;
}



Double_t TIdentificator::FidThetaMinPiPlus(Int_t k)
{
    Int_t sector = Sector(k);

    Double_t theta_min_val = kThetaPar0PiPlus[sector] +
            kThetaPar1PiPlus[sector] / pow(Momentum(k), 2) +
            kThetaPar2PiPlus[sector] * Momentum(k) +
            kThetaPar3PiPlus[sector] / Momentum(k) +
            kThetaPar4PiPlus[sector] * exp(kThetaPar5PiPlus[sector] * Momentum(k));

    return theta_min_val;
}



Double_t TIdentificator::FidFunc(Int_t side, Int_t param)
{
    Int_t sector = Sector(0);
    Double_t fid_func_val = 0.0; // dummy value to avoid that uninitialized warning

    if (side == 0 && param==0)
        fid_func_val = kFidPar0Low0[sector] +
                    kFidPar0Low1[sector] * exp(kFidPar0Low2[sector] *
                            (Momentum(0) - kFidPar0Low3[sector]));
    else if (side == 1 && param==0)
        fid_func_val = kFidPar0High0[sector] +
                    kFidPar0High1[sector] * exp(kFidPar0High2[sector] *
                            (Momentum(0) - kFidPar0High3[sector]));
    else if (side == 0 && param==1)
        fid_func_val=kFidPar1Low0[sector] +
                    kFidPar1Low1[sector] * Momentum(0) *
                    exp(kFidPar1Low2[sector] * pow((Momentum(0) -
                                kFidPar1Low3[sector]),2));
    else if (side == 1 && param==1)
        fid_func_val = kFidPar1High0[sector] +
                    kFidPar1High1[sector] * Momentum(0) *
                    exp(kFidPar1High2[sector] * pow((Momentum(0) -
                                kFidPar1High3[sector]),2));

    return fid_func_val;
}



Double_t TIdentificator::FidFuncPiPlus(Int_t side, Int_t param, Int_t k)
{
    Int_t sector = Sector(k);
    Double_t fid_func_val_pip = 0.0; // dummy value to avoid that uninitialized warning

    if (side == 0 && param == 0)
        fid_func_val_pip = kFidPar0Low0PiPlus[sector] +
                    kFidPar0Low1PiPlus[sector] * exp(kFidPar0Low2PiPlus[sector] *
                            (Momentum(k) - kFidPar0Low3PiPlus[sector]));
    else if (side == 1 && param == 0)
        fid_func_val_pip = kFidPar0High0PiPlus[sector] +
                    kFidPar0High1PiPlus[sector] * exp(kFidPar0High2PiPlus[sector] *
                            (Momentum(k) - kFidPar0High3PiPlus[sector]));
    else if (side == 0 && param == 1)
        fid_func_val_pip = kFidPar1Low0PiPlus[sector] +
                    kFidPar1Low1PiPlus[sector] * Momentum(k) *
                    exp(kFidPar1Low2PiPlus[sector] * pow((Momentum(k) -
                                kFidPar1Low3PiPlus[sector]), 2));
    else if (side == 1 && param == 1)
        fid_func_val_pip = kFidPar1High0PiPlus[sector] +
                    kFidPar1High1PiPlus[sector] * Momentum(k) *
                    exp(kFidPar1High2PiPlus[sector] * pow((Momentum(k) -
                                kFidPar1High3PiPlus[sector]), 2));

    return fid_func_val_pip;
}



Double_t TIdentificator::FidPhi(Int_t k, Bool_t kind)
{
    Double_t fid_phi_val;

    if (kind == 0) {
        TVector3 v3p(Px(k), Py(k), Pz(k));
        fid_phi_val = v3p.Phi() * 180 / TMath::Pi();
    } else {
        TVector3 v3p(Px(k,1), Py(k,1), Pz(k,1));
        fid_phi_val = v3p.Phi() * 180 / TMath::Pi();
    }

    if (fid_phi_val < -30)
        fid_phi_val += 360;
    else if (fid_phi_val > 330)
        fid_phi_val -= 360;

    return fid_phi_val;
}



Double_t TIdentificator::FidPhiMin()
{
    Int_t sector = Sector(0);
    Double_t fid_phi_min_val;

    if (FidTheta(0) <= FidThetaMin()) {
        fid_phi_min_val = 60. * sector;
        return fid_phi_min_val;
    } else {
        fid_phi_min_val = 60. * sector - FidFunc(0,0) *
                (1 - 1 / (1 + (FidTheta(0) - FidThetaMin()) / FidFunc(0,1)));
        return fid_phi_min_val;
    }
}



Double_t TIdentificator::FidPhiMax()
{
    Int_t sector = Sector(0);
    Double_t fid_phi_max_val;

    if (FidTheta(0) <= FidThetaMin()){
        fid_phi_max_val = 60. * sector;
        return fid_phi_max_val;
    } else {
        fid_phi_max_val = 60. * sector + FidFunc(1,0) *
                (1 - 1 / (1 + (FidTheta(0) - FidThetaMin()) / FidFunc(1,1)));
        return fid_phi_max_val;
    }
}



Double_t TIdentificator::FidPhiMinPiPlus(Int_t k)
{
    Int_t sector = Sector(k);

    Double_t fid_phi_min_val;

//    if (FidTheta(k) <= FidThetaMinPiPlus(k) || FidTheta(k) >= kFidThetaMax)
    if (FidTheta(k) <= FidThetaMinPiPlus(k)) {
        fid_phi_min_val = 60. * sector;
    } else {
        fid_phi_min_val = 60. * sector - FidFuncPiPlus(0,0,k) *
                (1 - 1 / (1 + (FidTheta(k) - FidThetaMinPiPlus(k)) / FidFuncPiPlus(0,1,k)));
    }

    return fid_phi_min_val;
}



Double_t TIdentificator::FidPhiMaxPiPlus(Int_t k)
{
    Int_t sector = Sector(k);
    Double_t fid_phi_max_val;

//    if (FidTheta(CT, k) <= FidThetaMinPiPlus(k) || FidTheta(k) >= kFidThetaMax)
    if (FidTheta(k) <= FidThetaMinPiPlus(k)) {
        fid_phi_max_val = 60. * sector;
    } else {
        fid_phi_max_val = 60. * sector + FidFuncPiPlus(1,0,k) *
                (1 - 1 / (1 + (FidTheta(k) - FidThetaMinPiPlus(k)) / FidFuncPiPlus(1,1,k)));
    }

    return fid_phi_max_val;
}



Bool_t TIdentificator::FidCheckCut()
{
    if (FidTheta(0) > FidThetaMin() &&
                FidPhi(0) > FidPhiMin() &&
                FidPhi(0) < FidPhiMax())
        return 1;                               // Fiducial Cut passed
    else
        return 0;                               // Fiducial Cut not passed
}



Bool_t TIdentificator::FidCheckCutPiPlus(Int_t k)
{
//    if (FidTheta(CT, k) > FidThetaMinPiPlus(CT, k) &&
//            FidTheta(k) < fid_theta_max &&
//            FidPhi(k) > FidPhiMinPiPlus(CT, k) &&
//            FidPhi(k) < FidPhiMaxPiPlus(CT, k))
//        return 1;

    if (FidTheta(k) > FidThetaMinPiPlus(k) &&
            FidPhi(k) > FidPhiMinPiPlus(k) &&
            FidPhi(k) < FidPhiMaxPiPlus(k))
        return 1;                               // Fiducial Cut passed
    else
        return 0;                               // Fiducial Cut not passed
}



Int_t TIdentificator::FidSector(Int_t k, Bool_t kind)
{
    Int_t sector;

    if (kind == 0) {
        if (FidPhi(k) != 330) {
            sector = int((FidPhi(k) + 90) / 60) - 1;
            return sector;
        } else {
            return 5;
        }
    }
    else {
        if (FidPhi(k,1) != 330) {
            sector = int((FidPhi(k,1) + 90) / 60) - 1;
            return sector;
        } else {
            return 5;
        }
    }
}



Int_t TIdentificator::ElecVertTarg()
{
    Int_t p_vertex_cut_elec = 0;
    Double_t ele_liq_lim[6][2];
    Double_t ele_sol_low[6];

    ele_liq_lim[0][0] = -32.5;
    ele_liq_lim[0][1] = -28;
    ele_liq_lim[1][0] = -32.5;
    ele_liq_lim[1][1] = -27.5;
    ele_liq_lim[2][0] = -32;
    ele_liq_lim[2][1] = -27.25;
    ele_liq_lim[3][0] = -32;
    ele_liq_lim[3][1] = -27.75;
    ele_liq_lim[4][0] = -32.5;
    ele_liq_lim[4][1] = -28.35;
    ele_liq_lim[5][0] = -33.5;
    ele_liq_lim[5][1] = -28.75;

    Double_t ele_sol_high = -20;

    ele_sol_low[0] = -26.5;
    ele_sol_low[1] = -26.;
    ele_sol_low[2] = -25.65;
    ele_sol_low[3] = -25.85;
    ele_sol_low[4] = -26.65;
    ele_sol_low[5] = -27.15;

    Int_t n_sector = Sector(0);

    if (Z(0) >= ele_liq_lim[n_sector][0] && Z(0) <= ele_liq_lim[n_sector][1])
        p_vertex_cut_elec = 1;
    if (Z(0) >= ele_sol_low[n_sector] && Z(0) <= ele_sol_high)
        p_vertex_cut_elec = 2;

    return p_vertex_cut_elec;
}

Int_t TIdentificator::ElecVertTarg(Bool_t kind) {
    Int_t vertex_cut_elec = 0;
    Double_t ele_liq_lim[6][2];
    Double_t ele_sol_low[6];
    ele_liq_lim[0][0] = -32.5;
    ele_liq_lim[0][1] = -28;
    ele_liq_lim[1][0] = -32.5;
    ele_liq_lim[1][1] = -27.5;
    ele_liq_lim[2][0] = -32;
    ele_liq_lim[2][1] = -27.25;
    ele_liq_lim[3][0] = -32;
    ele_liq_lim[3][1] = -27.75;
    ele_liq_lim[4][0] = -32.5;
    ele_liq_lim[4][1] = -28.35;
    ele_liq_lim[5][0] = -33.5;
    ele_liq_lim[5][1] = -28.75;
    
    Double_t ele_sol_high=-20;
    
    ele_sol_low[0] = -26.5;
    ele_sol_low[1] = -26.;
    ele_sol_low[2] = -25.65;
    ele_sol_low[3] = -25.85;
    ele_sol_low[4] = -26.65;
    ele_sol_low[5] = -27.15;

    if(kind == 0) {
        Int_t n_sector = Sector(0);
        if(Z(0)>=ele_liq_lim[n_sector][0] && Z(0)<=ele_liq_lim[n_sector][1]) 
            vertex_cut_elec=1;
        if(Z(0)>=ele_sol_low[n_sector] && Z(0)<=ele_sol_high) 
            vertex_cut_elec=2;
        return vertex_cut_elec;
    } else {
        Int_t n_sector = Sector(0,1);
        if(Z(0,1)>=ele_liq_lim[n_sector][0] && Z(0,1)<=ele_liq_lim[n_sector][1]) 
            vertex_cut_elec=1;
        if(Z(0,1)>=ele_sol_low[n_sector] && Z(0,1)<=ele_sol_high) 
            vertex_cut_elec=2;
        return vertex_cut_elec;
    }
}

Bool_t TIdentificator::PionVertTarg(Int_t k)
{
    Bool_t vertex_cut_pion = 0;
    Double_t pion_liq_low;
    Double_t pion_liq_high;
    Int_t n_ele_sector = Sector(0);
    Int_t n_pion_sector = Sector(k);

    if (n_pion_sector == 5 || (n_ele_sector == 3 && n_pion_sector == 4) ||
                (n_pion_sector == 0 && n_ele_sector != 1 && n_ele_sector != 4))
        pion_liq_low = -36.;
    else pion_liq_low = -35.;

    if (n_ele_sector == 3 && n_pion_sector == 2)
        pion_liq_high = -24.;
    else if ((n_ele_sector == 5 && n_pion_sector != 2 && n_pion_sector != 3) ||
                (n_pion_sector == 5 && n_ele_sector != 2) ||
                (n_ele_sector == 0 && n_pion_sector == 0) ||
                (n_ele_sector == 1 && n_pion_sector == 1) ||
                (n_pion_sector == 4 && (n_ele_sector == 3 || n_ele_sector == 4)))
        pion_liq_high = -26.;
    else
        pion_liq_high = -25.;

    if (ElecVertTarg() == 1 && Z(k) >= pion_liq_low && Z(k) <= pion_liq_high)
        vertex_cut_pion = 1;

    if (ElecVertTarg() == 2 && Z(k) >= -30 && Z(k) <= -18)
        vertex_cut_pion = 1;

    return vertex_cut_pion;
}

TVector3 *TIdentificator::GetCorrectedVert()
{
//Electrons.
      TVector3 RotatedVertPos(X(0),Y(0),Z(0)); //vx, xy, vz from EVNT
      TVector3 RotatedVertDir(Px(0),Py(0),Pz(0));//px, py, pz from EVNT
      TVector3 TargetPos(0.043,-0.33,0);
      TVector3 *V_corr = new TVector3();
      Float_t sect = Sector(0); 
      RotatedVertPos.RotateZ(-TMath::DegToRad()*60.*sect);
      RotatedVertDir.RotateZ(-TMath::DegToRad()*60.*sect);
      TargetPos.RotateZ(-TMath::DegToRad()*60.*sect);
      Float_t ShiftLength = (TargetPos.X()-RotatedVertPos.X())/RotatedVertDir.X();
      RotatedVertDir = ShiftLength*RotatedVertDir;
      RotatedVertPos = RotatedVertPos+RotatedVertDir;
      V_corr->SetX((RotatedVertPos-TargetPos).X());
      V_corr->SetY((RotatedVertPos-TargetPos).Y());
      V_corr->SetZ(RotatedVertPos.Z());
      return V_corr;
}

TVector3 *TIdentificator::XYZToUVW(TVector3 *xyz){
  // Converts x,y,z EC hit in CLAS coordinate system
  // into u,v,w distances of the EC hit.

  Float_t ex=0.;
  Float_t wy=0.;
  Float_t zd=0.;
  Float_t yu=0.;
  Float_t ve=0.;
  Float_t wu=0.;
  Float_t xi=0.; 
  Float_t yi=0.; 
  Float_t zi=0.;
  Float_t ec_phy = 0.;  
  Float_t phy = 0.;
  Float_t rot[3][3];

  // Parameters
  Float_t ec_the = 0.4363323;
  Float_t ylow = -182.974;
  Float_t yhi = 189.956;
  Float_t tgrho = 1.95325; 
  Float_t sinrho = 0.8901256; 
  Float_t cosrho = 0.455715;

  // Variables
  ex = xyz->X();
  wy = xyz->Y();
  zd = xyz->Z();
  
  phy = TMath::ATan2(wy,ex)*57.29578;
  if(phy<0.){phy = phy + 360;}
  phy = phy+30.;
  if(phy>360.){phy = phy-360.;}

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

  yi = ex*rot[0][0]+wy*rot[1][0]+zd*rot[2][0];
  xi = ex*rot[0][1]+wy*rot[1][1]+zd*rot[2][1];
  zi = ex*rot[0][2]+wy*rot[1][2]+zd*rot[2][2];
  zi = zi-510.32 ;

  yu = (yi-ylow)/sinrho;
  ve = (yhi-ylow)/tgrho - xi + (yhi-yi)/tgrho;
  wu = ((yhi-ylow)/tgrho + xi + (yhi-yi)/tgrho)/2./cosrho;

  TVector3 * result3= new TVector3(yu,ve,wu);

  return result3;
}



#include "Categorize.C"

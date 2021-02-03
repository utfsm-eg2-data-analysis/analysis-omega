#ifndef ROTATEDTREEOPS_HXX
#define ROTATEDTREEOPS_HXX

#include "Headers.hxx"
#include "Math.hxx"
#include "PDG.hxx"

#include "FNCtree.h"

#ifndef INVLD
#define INVLD -9999
#endif

void AssignRotatedMixVar_REC(rec_m& m, Int_t index, TVector3* eMomentum, std::vector<TVector3*> pMomentum) {
  // electron
  // necessary because we want to update the electron values from the last electron added
  m.Pex = eMomentum->X();
  m.Pey = eMomentum->Y();
  m.Pez = eMomentum->Z();
  m.PhiLabEl = PhiLab(m.Pex, m.Pey, m.Pez);
  m.ThetaLabEl = ThetaLab(m.Pex, m.Pey, m.Pez);
  m.Q2 = 4. * kEbeam * eMomentum->Mag() * TMath::Sin(m.ThetaLabEl * TMath::DegToRad() / 2) * TMath::Sin(m.ThetaLabEl * TMath::DegToRad() / 2);
  m.Nu = kEbeam - eMomentum->Mag();
  m.W = TMath::Sqrt(kMassProton * kMassProton + 2. * kMassProton * m.Nu - m.Q2);
  m.Xb = m.Q2 / 2. / m.Nu / kMassProton;
  m.Yb = m.Nu / kEbeam;
  // particles
  Double_t fM = GetParticleMass((Int_t)m.Pid[index]);
  TLorentzVector* fGamma = GetCorrPhotonEnergy_ForMixingBkg(pMomentum[index]);
  Double_t fP = (m.Pid[index] == 22) * fGamma->P() + (m.Pid[index] != 22) * pMomentum[index]->Mag();
  m.E[index] = (m.Pid[index] == 22) * fGamma->E() + (m.Pid[index] != 22) * TMath::Sqrt(fP * fP + fM * fM);
  m.Px[index] = (m.Pid[index] == 22) * fGamma->Px() + (m.Pid[index] != 22) * pMomentum[index]->X();
  m.Py[index] = (m.Pid[index] == 22) * fGamma->Py() + (m.Pid[index] != 22) * pMomentum[index]->Y();
  m.Pz[index] = (m.Pid[index] == 22) * fGamma->Pz() + (m.Pid[index] != 22) * pMomentum[index]->Z();
  Double_t fCosThetaPQ = ((kEbeam - m.Pez) * m.Pz[index] - m.Pex * m.Px[index] - m.Pey * m.Py[index]) / (TMath::Sqrt(fP * fP * (m.Q2 + m.Nu * m.Nu)));
  m.Mass2[index] = fP * fP * (TMath::Power(m.Betta[index], -2) - 1);
  m.PhiPQ[index] = PhiPQ(m.Pex, m.Pey, m.Pez, m.Px[index], m.Py[index], m.Pz[index]);
  m.ThetaPQ[index] = ThetaPQ(m.Pex, m.Pey, m.Pez, m.Px[index], m.Py[index], m.Pz[index]);
  m.PhiLab[index] = PhiLab(m.Px[index], m.Py[index], m.Pz[index]);
  m.ThetaLab[index] = ThetaLab(m.Px[index], m.Py[index], m.Pz[index]);
  m.Pt2[index] = fP * fP * (1 - fCosThetaPQ * fCosThetaPQ);
  m.Pl2[index] = fP * fP * fCosThetaPQ * fCosThetaPQ;
  m.deltaTheta[index] = DeltaTheta(m.Pex, m.Pey, m.Pez, m.Px[index], m.Py[index], m.Pz[index]);
  m.Mx2[index] = m.W * m.W + fM * fM - 2 * m.Z[index] * m.Nu * m.Nu + 2 * TMath::Sqrt(m.Pl2[index] * (m.Nu * m.Nu + m.Q2)) - 2 * kMassProton * m.Z[index] * m.Nu;
}

#endif

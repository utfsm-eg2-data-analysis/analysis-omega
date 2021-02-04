#ifndef SETALIASES_CXX
#define SETALIASES_CXX

void SetAliases(TChain *treeExtracted) {
  treeExtracted->SetAlias("pippimM", "TMath::Sqrt(2*0.13957*0.13957 + 2*E[0]*E[1] - 2*(Px[0]*Px[1] + Py[0]*Py[1] + Pz[0]*Pz[1]))");
}

#endif

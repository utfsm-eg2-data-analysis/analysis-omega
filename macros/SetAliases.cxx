#ifndef SETALIASES_CXX
#define SETALIASES_CXX

void SetAliases(TChain *treeExtracted, Int_t SimulationsTree = 0) {
  treeExtracted->SetAlias("pippimM", "TMath::Sqrt(2*0.13957*0.13957 + 2*E[0]*E[1] - 2*(Px[0]*Px[1] + Py[0]*Py[1] + Pz[0]*Pz[1]))");
  if (SimulationsTree) {
    treeExtracted->SetAlias("mc_pippimM", "TMath::Sqrt(2*0.13957*0.13957 + 2*mc_E[0]*mc_E[1] - 2*(mc_Px[0]*mc_Px[1] + mc_Py[0]*mc_Py[1] + mc_Pz[0]*mc_Pz[1]))");
  }
}

#endif

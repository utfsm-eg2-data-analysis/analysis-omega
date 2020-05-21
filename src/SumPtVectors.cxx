/*****************************************/
/*  SumPtVectors.cxx                     */
/*                                       */
/*  Andrés Bórquez                       */
/*                                       */
/*****************************************/

// OBJECTIVE:
// - check if the vector sum of Pt of all omega constituents gives 0

#include "analysisConfig.h"

/*** Constants ***/

const Float_t kEbeam = 5.014;

/*** Global variables ***/

TString outDir = proDir + "/out/SumPtVectors";
TString plotFile = outDir + "/test.png";

// everything set for D data
TCut cutAll = cutDIS && cutPi0 && cutPipPim;
TString cutTargType = "TargType == 1";
TString inputFile1 = dataDir + "/C/comb_C-thickD2.root";
TString inputFile2 = dataDir + "/Fe/comb_Fe-thickD2.root";
TString inputFile3 = dataDir + "/Pb/comb_Pb-thinD2.root";

/*** Variables extracted from tree ***/

// constituents variables
Float_t tPx[4], tPy[4], tPz[4];

// electron (virtual photon) variables
Float_t tPex, tPey, tPez;

// omega variables
Float_t tPt2;
Float_t twPx, twPy, twPz;
Float_t twP2;

/*** Declaration of functions ***/

TVector3 PlVector(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fPex, Float_t fPey, Float_t fPez);
TVector3 PtVector(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fPex, Float_t fPey, Float_t fPez);

TVector3 PlVector_omega(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fwPx, Float_t fwPy, Float_t fwPz);
TVector3 PtVector_omega(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fwPx, Float_t fwPy, Float_t fwPz);

int main() {

  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  treeExtracted->SetBranchStatus("*", 1);

  // constituents
  treeExtracted->SetBranchAddress("Px", &tPx);
  treeExtracted->SetBranchAddress("Py", &tPy);
  treeExtracted->SetBranchAddress("Pz", &tPz);
  // omega
  treeExtracted->SetBranchAddress("wPx", &twPx);
  treeExtracted->SetBranchAddress("wPy", &twPy);
  treeExtracted->SetBranchAddress("wPz", &twPz);
  treeExtracted->SetBranchAddress("wP2", &twP2);
  treeExtracted->SetBranchAddress("Pt2", &tPt2);
  // electron
  treeExtracted->SetBranchAddress("Pex", &tPex);
  treeExtracted->SetBranchAddress("Pey", &tPey);
  treeExtracted->SetBranchAddress("Pez", &tPez);

  /*** First check ***/
  
  TVector3 vecPt;
  TVector3 vecPl;
  Float_t  calcPt2;
  Float_t  calcPl2;
  std::cout << "P2:calc(Pl2+Pt2):calc(Pl2):calc(Pt2):Pt2" << std::endl;
  for (Int_t i = 0; i < 25; i++) {
    treeExtracted->GetEntry(i);

    vecPt = PtVector(twPx, twPy, twPz, tPex, tPey, tPez); 
    calcPt2 = vecPt.Mag2();

    vecPl = PlVector(twPx, twPy, twPz, tPex, tPey, tPez); 
    calcPl2 = vecPl.Mag2();

    std::cout << twP2 << ":" << calcPl2 + calcPt2 << ":" << calcPl2 << ":" << calcPt2 << ":" << tPt2 << std::endl;
  }
  std::cout << std::endl;

  /*** Second check ***/
  
  TVector3 PtGamma1;
  TVector3 PtGamma2;
  TVector3 PtPip;
  TVector3 PtPim;

  Float_t  sumPt_x;
  Float_t  sumPt_y;
  Float_t  sumPt_z;

  // define histograms
  TH1F *theHist_x = new TH1F("sum pT_x", "sum p_{T} - x component", 400, -2, 2);
  TH1F *theHist_y = new TH1F("sum pT_y", "sum p_{T} - y component", 400, -2, 2);
  TH1F *theHist_z = new TH1F("sum pT_z", "sum p_{T} - z component", 400, -2, 2);

  // std::cout << "row:PtGamma1_x:PtGamma2_x:PtPip_x:PtPim_x:sumPt_x" << std::endl;
  for (Int_t i = 0; i < treeExtracted->GetEntries(); i++) { // treeExtracted->GetEntries()
    treeExtracted->GetEntry(i);

    PtGamma1 = PtVector(tPx[0], tPy[0], tPz[0], tPex, tPey, tPez);
    PtGamma2 = PtVector(tPx[1], tPy[1], tPz[1], tPex, tPey, tPez);
    PtPip    = PtVector(tPx[2], tPy[2], tPz[2], tPex, tPey, tPez);
    PtPim    = PtVector(tPx[3], tPy[3], tPz[3], tPex, tPey, tPez);

    sumPt_x = PtGamma1.Px() + PtGamma2.Px() + PtPip.Px() + PtPim.Px();
    sumPt_y = PtGamma1.Py() + PtGamma2.Py() + PtPip.Py() + PtPim.Py();
    sumPt_z = PtGamma1.Pz() + PtGamma2.Pz() + PtPip.Pz() + PtPim.Pz();
    
    // std::cout << i << ":" << PtGamma1.Px() << ":" << PtGamma2.Px() << ":" << PtPip.Px() << ":" << PtPim.Px() << ":" << sumPt_x << std::endl;

    // fill histograms
    theHist_x->Fill(sumPt_x);
    theHist_y->Fill(sumPt_y);
    theHist_z->Fill(sumPt_z);
  }
  std::cout << std::endl;

  theHist_x->GetXaxis()->SetTitle("#Sigma p_{T} - x component (GeV)");
  theHist_x->GetXaxis()->CenterTitle();

  theHist_y->GetXaxis()->SetTitle("#Sigma p_{T} - y component (GeV)");
  theHist_y->GetXaxis()->CenterTitle();

  theHist_z->GetXaxis()->SetTitle("#Sigma p_{T} - z component (GeV)");
  theHist_z->GetXaxis()->CenterTitle();
  
  /*** Drawing ***/
  
  TCanvas *c_x = new TCanvas("c_x", "c_x", 1000, 1000); 
  theHist_x->Draw("E");
  c_x->Print(outDir + "/sum-pT-wrt-virt_x.png"); // output file

  TCanvas *c_y = new TCanvas("c_y", "c_y", 1000, 1000); 
  theHist_y->Draw("E");
  c_y->Print(outDir + "/sum-pT-wrt-virt_y.png"); // output file

  TCanvas *c_z = new TCanvas("c_z", "c_z", 1000, 1000); 
  theHist_z->Draw("E");
  c_z->Print(outDir + "/sum-pT-wrt-virt_z.png"); // output file

  std::cout << std::endl;

  /*** Third check ***/
  // Is the sum of individual Pt = Pt of mother?
  
  TVector3 PtOmega;
  
  std::cout << "row:sumPt_x:PtOmega_x" << std::endl;
  for (Int_t i = 0; i < 25; i++) { // treeExtracted->GetEntries()
    treeExtracted->GetEntry(i);

    PtGamma1 = PtVector(tPx[0], tPy[0], tPz[0], tPex, tPey, tPez);
    PtGamma2 = PtVector(tPx[1], tPy[1], tPz[1], tPex, tPey, tPez);
    PtPip    = PtVector(tPx[2], tPy[2], tPz[2], tPex, tPey, tPez);
    PtPim    = PtVector(tPx[3], tPy[3], tPz[3], tPex, tPey, tPez);

    PtOmega = PtVector(twPx, twPy, twPz, tPex, tPey, tPez);
    
    sumPt_x = PtGamma1.Px() + PtGamma2.Px() + PtPip.Px() + PtPim.Px();
    
    std::cout << i << ":" << sumPt_x << ":" << PtOmega.Px() << std::endl;
  }
  std::cout << std::endl;

  // CONCLUSION:
  // - Orlando is right.
  // - Yes, sum of individual Pt = Pt of mother

  /*** Fourth check ***/
  // What happens if the obtain Pt w.r.t. mother, instead of virtual photon?

  // define histograms
  TH1F *sickHist_x = new TH1F("sum pT_x wrt #omega", "sum p_{T} w.r.t. #omega - x component", 100, -0.25, 0.25);
  TH1F *sickHist_y = new TH1F("sum pT_y wrt #omega", "sum p_{T} w.r.t. #omega - y component", 100, -0.25, 0.25);
  TH1F *sickHist_z = new TH1F("sum pT_z wrt #omega", "sum p_{T} w.r.t. #omega - z component", 200, -0.5, 0.5);
  
  // std::cout << "row:PtGamma1_x:PtGamma2_x:PtPip_x:PtPim_x:sumPt_x" << std::endl;
  for (Int_t i = 0; i < treeExtracted->GetEntries(); i++) { // treeExtracted->GetEntries()
    treeExtracted->GetEntry(i);

    PtGamma1 = PtVector_omega(tPx[0], tPy[0], tPz[0], twPx, twPy, twPz);
    PtGamma2 = PtVector_omega(tPx[1], tPy[1], tPz[1], twPx, twPy, twPz);
    PtPip    = PtVector_omega(tPx[2], tPy[2], tPz[2], twPx, twPy, twPz);
    PtPim    = PtVector_omega(tPx[3], tPy[3], tPz[3], twPx, twPy, twPz);

    sumPt_x = PtGamma1.Px() + PtGamma2.Px() + PtPip.Px() + PtPim.Px();
    sumPt_y = PtGamma1.Py() + PtGamma2.Py() + PtPip.Py() + PtPim.Py();
    sumPt_z = PtGamma1.Pz() + PtGamma2.Pz() + PtPip.Pz() + PtPim.Pz();
    
    // std::cout << i << ":" << PtGamma1.Px() << ":" << PtGamma2.Px() << ":" << PtPip.Px() << ":" << PtPim.Px() << ":" << sumPt_x << std::endl;
    
    // fill histograms!
    sickHist_x->Fill(sumPt_x);
    sickHist_y->Fill(sumPt_y);
    sickHist_z->Fill(sumPt_z);
  }
  std::cout << std::endl;

  sickHist_x->GetXaxis()->SetTitle("#Sigma p_{T} - x component (GeV)");
  sickHist_x->GetXaxis()->CenterTitle();

  sickHist_y->GetXaxis()->SetTitle("#Sigma p_{T} - y component (GeV)");
  sickHist_y->GetXaxis()->CenterTitle();

  sickHist_z->GetXaxis()->SetTitle("#Sigma p_{T} - z component (GeV)");
  sickHist_z->GetXaxis()->CenterTitle();
  
  /*** Drawing ***/
  
  TCanvas *c2_x = new TCanvas("c2_x", "c2_x", 1000, 1000); 
  c2_x->SetLogy();
  sickHist_x->Draw("E");
  c2_x->Print(outDir + "/sum-pT-wrt-omega_x.png"); // output file

  TCanvas *c2_y = new TCanvas("c2_y", "c2_y", 1000, 1000); 
  c2_y->SetLogy();
  sickHist_y->Draw("E");
  c2_y->Print(outDir + "/sum-pT-wrt-omega_y.png"); // output file

  TCanvas *c2_z = new TCanvas("c2_z", "c2_z", 1000, 1000); 
  c2_z->SetLogy();
  sickHist_z->Draw("E");
  c2_z->Print(outDir + "/sum-pT-wrt-omega_z.png"); // output file
  
  std::cout << std::endl;
  
  // CONCLUSION
  // - MW was right, too. Very weird result.
}

/*** Functions ***/

TVector3 PlVector(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fPex, Float_t fPey, Float_t fPez) {

  // define vectors: hadron momentum and virtual photon momentum
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 virt(-fPex, -fPey, kEbeam - fPez);

  // define longitudinal momentum
  // Pl = (hadr . virt)/abs(virt) in virt direction
  TVector3 fPl;
  fPl.SetMagThetaPhi(hadr.Dot(virt)/virt.Mag(), virt.Theta(), virt.Phi()); // (magnitude, theta, phi)

  return fPl;
}

TVector3 PtVector(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fPex, Float_t fPey, Float_t fPez) {

  // define vectors: hadron momentum and longitudinal momentum
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 fPl = PlVector(fPx, fPy, fPz, fPex, fPey, fPez);

  // define transversal momentum
  // vec{P} = vec{Pt} + vec{Pl}
  TVector3 fPt = hadr - fPl;
  
  return fPt;
}

TVector3 PlVector_omega(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fwPx, Float_t fwPy, Float_t fwPz) {

  // define vectors: hadron momentum and omega momentum
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 mother(fwPx, fwPy, fwPz);

  // define longitudinal momentum
  // Pl = (hadr . mother)/abs(mother) in mother direction
  TVector3 fPl;
  fPl.SetMagThetaPhi(hadr.Dot(mother)/mother.Mag(), mother.Theta(), mother.Phi()); // (magnitude, theta, phi)

  return fPl;
}

TVector3 PtVector_omega(Float_t fPx, Float_t fPy, Float_t fPz, Float_t fwPx, Float_t fwPy, Float_t fwPz) {

  // define vectors: hadron momentum and longitudinal momentum
  TVector3 hadr(fPx, fPy, fPz);
  TVector3 fPl = PlVector_omega(fPx, fPy, fPz, fwPx, fwPy, fwPz);

  // define transversal momentum
  // vec{P} = vec{Pt} + vec{Pl}
  TVector3 fPt = hadr - fPl;
  
  return fPt;
}

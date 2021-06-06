/*Double_t FeynmanX(Int_t k, Bool_t kind = 0) {
  // Returns the Feynman X scaling variable for the particle in the row k
  Double_t PlCM;     // PlCM: Longitudinal momentum of the hadron in the Center of Mass frame
  Double_t PlCMmax;  // Max PlCM's value expected (according to S.Moran thesis)
  PlCM = (Momentum(k, kind) - Zh(k, kind) * Nu(kind)(TMath::Sqrt(Q2(kind) + Nu(kind) * Nu(kind)) / (Nu(kind) + kMprt))) * (Nu(kind) + kMprt) /
         W(kind);  // Assuming Momentum is in the Lab frame and Zh is well defined
  PlCMmax = TMath::Sqrt(TMath::Power(W(kind), 4) + TMath::Power(kMpi * kMpi - kMntr * kMntr, 2) - 2 W(kind) * W(kind) * (kMpi * kMpi + kMntr * kMntr)) / (2 W(kind));
  return PlCM / PlCMmax;
}
*/
void GetXf() {

  // XF = 2*[    Zh*NeutronMass*Nu*Nu - Zh*Q2*Nu - (NeutronMass + Nu) * (Nu*Nu*Zh - TMath::Sqrt(Nu*Nu + Q2)*TMath::Sqrt(Pl2))   ]
  //     -------------------------------------------------------------------------------------------------------------------------
  //                                    (W2 - Mass_pion*Mass_pion) * TMath::Sqrt(Nu*Nu + Q2)
  /*
  TFile *archivo = new TFile("/home/borquez/analysis-omega/out/GetSimpleTuple/data/C/prunedC_42011.root", "READ");

  TTree *tree;
  tree = archivo->Get<TTree>("ntuple_data");
  */

  TChain *tree = new TChain();
  tree->Add("/home/borquez/analysis-omega/out/GetSimpleTuple/data/C/prunedC_*.root/ntuple_data");
  
  tree->SetAlias("term1", "Nu*Nu*Zh - TMath::Sqrt(Nu*Nu + Q2)*TMath::Sqrt(Pl2)");
  tree->SetAlias("term2", "Zh*0.939565*Nu*Nu - Zh*Q2*Nu - (0.939565 + Nu) * term1");
  tree->SetAlias("term3", "(W*W - 0.139570*0.139570) * TMath::Sqrt(Nu*Nu + Q2)");
  tree->SetAlias("Xf_version_code",    "2*term2/term3");

  tree->SetAlias("term4", "(TMath::Sqrt(Pl2) - Zh * Nu*TMath::Sqrt(Q2 + Nu * Nu) / (Nu + 0.939565)) * ((Nu + 0.939565) / W)");
  tree->SetAlias("term5", "TMath::Sqrt(TMath::Power(W, 4) + TMath::Power(0.139570 * 0.139570 - 0.939565 * 0.939565, 2) - 2 * W * W * (0.139570 * 0.139570 + 0.939565 * 0.939565)) / (2*W)");
  tree->SetAlias("Xf_version_thesis",    "term4/term5");

  // tree->Draw("Xf>>hist(200, -1, 1)", "pid == 211"); //  && Q2 > 1 && W > 2
  
  TH1D *hist1;
  //tree->Draw("PhiPQ>>hist1(180, -180, 180)", "pid == 211 && Xf > 0 && Nphe < 25", "goff"); //  && Q2 > 1 && W > 2
  tree->Draw("Xf_version_code>>hist1(200, -1.2, 1.2)", "pid == 211"); //  && Q2 > 1 && W > 2
  hist1 = (TH1D *)gROOT->FindObject("hist1");

  TH1D *hist2;
  //tree->Draw("PhiPQ>>hist2(180, -180, 180)", "pid == 211 && Xf < 0 && Nphe < 25", "goff"); //  && Q2 > 1 && W > 2
  tree->Draw("Xf_version_thesis>>hist2(200, -1.2, 1.2)", "pid == 211"); //  && Q2 > 1 && W > 2
  hist2 = (TH1D *)gROOT->FindObject("hist2");

  gStyle->SetOptStat(0);
  
  TCanvas *c = new TCanvas("c", "c", 800, 800);

  hist1->SetTitle("Positive Pions, C data"); //, N_{phe} < 25");
  hist1->GetYaxis()->SetMaxDigits(3);
  hist1->GetYaxis()->SetTitle("Counts");
  hist1->GetXaxis()->SetTitle("#phi_{PQ} [deg]");
  hist1->SetFillStyle(0);
  hist1->SetLineWidth(2);
  hist1->Draw("HIST");

  hist2->SetFillStyle(0);
  hist2->SetLineColor(kRed);
  hist2->SetLineWidth(2);
  hist2->Draw("HIST SAME");

  TLegend *l = new TLegend(0.45, 0.7, 0.65, 0.85); // x1,y1,x2,y2
  // l->AddEntry(hist1, "x_{F} > 0", "l");
  // l->AddEntry(hist2, "x_{F} < 0", "l");
  l->AddEntry(hist1, "Def. from code", "l");
  l->AddEntry(hist2, "Def. from thesis", "l");
  l->SetFillStyle(0);
  l->SetTextFont(42);
  l->SetTextSize(0.026);
  l->SetBorderSize(0);
  l->Draw();
  
  c->Draw();
}

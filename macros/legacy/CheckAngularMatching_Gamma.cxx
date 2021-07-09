void CheckAngularMatching_Gamma() {
  TChain *ntuple_sim = new TChain();
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v1.root/ntuple_sim");
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v2.root/ntuple_sim");
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v3.root/ntuple_sim");
 
  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>GammaFromAny(100, 0, 4.5)", electronCuts && "pid == 22", "goff");
  TH1F *GammaFromAny  = (TH1F *)gROOT->FindObject("GammaFromAny");
  GammaFromAny->SetLineColor(kBlack);
  GammaFromAny->SetLineWidth(2);
  GammaFromAny->SetFillStyle(0);

  GammaFromAny->SetTitle("Momentum distribution of simulation reconstructed #gamma");
  GammaFromAny->GetYaxis()->SetMaxDigits(3);
  GammaFromAny->GetYaxis()->SetTitle("Counts");
  GammaFromAny->GetXaxis()->SetTitle("P (GeV)");
    
  ntuple_sim->Draw("P>>GammaFromAny_AM(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid != -9999", "goff");
  TH1F *GammaFromAny_AM = (TH1F *)gROOT->FindObject("GammaFromAny_AM");
  GammaFromAny_AM->SetLineColor(kRed);
  GammaFromAny_AM->SetLineWidth(2);
  GammaFromAny_AM->SetFillStyle(0);

  ntuple_sim->Draw("P>>GammaFromAny_NAM(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == -9999", "goff");
  TH1F *GammaFromAny_NAM = (TH1F *)gROOT->FindObject("GammaFromAny_NAM");
  GammaFromAny_NAM->SetLineColor(kBlue);
  GammaFromAny_NAM->SetLineWidth(2);
  GammaFromAny_NAM->SetFillStyle(0);

  TCanvas *c = new TCanvas("gamma_AM", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  GammaFromAny->Draw("HIST");
  GammaFromAny_AM->Draw("HIST SAME");
  GammaFromAny_NAM->Draw("HIST SAME");
  
  TLegend *l = new TLegend(0.6, 0.6, 0.9, 0.9); // x1,y1,x2,y2
  l->AddEntry(GammaFromAny,     "X #rightarrow #gamma", "l");
  l->AddEntry(GammaFromAny_AM,  "X #rightarrow #gamma, Ang. Matching", "l");
  l->AddEntry(GammaFromAny_NAM, "X #rightarrow #gamma, No Ang. Matching", "l");
  l->Draw();
  
  c->Draw();

  /*** RATIO ***/

  TCanvas *c1 = new TCanvas("gamma_AM-ratio", "c1", 1000, 1000);
  gStyle->SetOptStat(0);

  TH1F *Ratio = new TH1F("Ratio", "Ratio", 100, 0, 4.5);
  Ratio->Divide(GammaFromAny_AM, GammaFromAny, 1, 1, "B");

  Ratio->SetTitle("N(X #rightarrow #gamma, Ang. Matching)/N(X #rightarrow #gamma)");
  Ratio->GetYaxis()->SetMaxDigits(3);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");

  Ratio->SetLineColor(kRed);
  Ratio->SetLineWidth(2);
  Ratio->SetFillStyle(0);
  
  Ratio->Draw("E");
    
  c1->Draw();  
}

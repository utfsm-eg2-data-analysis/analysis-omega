void CalcNeutronContamination() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_final.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";

  ntuple_sim->Draw("P>>GammaFromAny_AM(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid != -9999", "goff");
  TH1F *GammaFromAny_AM = (TH1F *)gROOT->FindObject("GammaFromAny_AM");

  ntuple_sim->Draw("P>>GammaFromNeut(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == 2112", "goff");
  TH1F *GammaFromNeut = (TH1F *)gROOT->FindObject("GammaFromNeut");

  TH1F *Ratio = new TH1F("Ratio", "Ratio", 100, 0, 4.5);
  Ratio->Divide(GammaFromNeut, GammaFromAny_AM, 1, 1, "B");
  
  Ratio->SetTitle("N(n #rightarrow #gamma)/N(X #rightarrow #gamma)");
  Ratio->GetYaxis()->SetMaxDigits(3);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");

  Ratio->SetLineColor(kOrange+3); // brown
  Ratio->SetLineWidth(2);
  Ratio->SetFillStyle(0);

  TCanvas *c = new TCanvas("neutron-contamination", "c", 1000, 1000);
  gStyle->SetOptStat(0);

  Ratio->Draw("E");
  
  c->Draw();
}

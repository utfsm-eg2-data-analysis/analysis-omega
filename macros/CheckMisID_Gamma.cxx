void CheckGammaMisID() {
  TChain *ntuple_sim = new TChain();
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_first.root/ntuple_sim");
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_second.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>GammaFromAny_AM(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid != -9999", "goff");
  TH1F *GammaFromAny_AM = (TH1F *)gROOT->FindObject("GammaFromAny_AM");
  GammaFromAny_AM->SetLineColor(kRed);
  GammaFromAny_AM->SetLineWidth(2);
  GammaFromAny_AM->SetFillStyle(0);

  GammaFromAny_AM->SetTitle("Momentum distribution of simulation reconstructed #gamma");
  GammaFromAny_AM->GetYaxis()->SetMaxDigits(3);
  GammaFromAny_AM->GetYaxis()->SetTitle("Counts");
  GammaFromAny_AM->GetXaxis()->SetTitle("P (GeV)");
  
  ntuple_sim->Draw("P>>GammaFromTrue(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == 22", "goff");
  TH1F *GammaFromTrue = (TH1F *)gROOT->FindObject("GammaFromTrue");
  GammaFromTrue->SetLineColor(kAzure+7);
  GammaFromTrue->SetLineWidth(2);
  GammaFromTrue->SetFillStyle(0);
  
  ntuple_sim->Draw("P>>GammaFromFake(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid != 22 && mc_pid != -9999", "goff");
  TH1F *GammaFromFake = (TH1F *)gROOT->FindObject("GammaFromFake");
  GammaFromFake->SetLineColor(kOrange+7);
  GammaFromFake->SetLineWidth(2);
  GammaFromFake->SetFillStyle(0);
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  GammaFromAny_AM->Draw("HIST");
  GammaFromTrue->Draw("HIST SAME");
  GammaFromFake->Draw("HIST SAME");

  TLegend *l = new TLegend(0.6, 0.6, 0.9, 0.9); // x1,y1,x2,y2
  l->AddEntry(GammaFromAny_AM, "X #rightarrow #gamma - Ang. Matching", "l");
  l->AddEntry(GammaFromTrue,   "#gamma #rightarrow #gamma - Ang. Matching", "l");
  l->AddEntry(GammaFromFake,   "(not #gamma) #rightarrow #gamma - Ang. Matching", "l");
  l->Draw();
  
  c->Draw();

  /*** Obtain ratio GammaFromFake/GammaFromAny_AM ***/
  
  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
  gStyle->SetOptStat(0);

  TH1F *Ratio = new TH1F("Ratio", "Ratio", 100, 0, 4.5);
  Ratio->Divide(GammaFromFake, GammaFromAny_AM, 1, 1, "B");

  Ratio->SetTitle("N((not #gamma) #rightarrow #gamma)/N(X #rightarrow #gamma)");
  Ratio->GetYaxis()->SetMaxDigits(3);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");  
  
  Ratio->SetLineColor(kOrange+7);
  Ratio->SetLineWidth(2);
  
  Ratio->Draw("E");
  
  c1->Draw();
}

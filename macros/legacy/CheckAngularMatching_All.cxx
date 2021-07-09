void CheckAngularMatching_All() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v1.root/ntuple_sim");
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v2.root/ntuple_sim");
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v3.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>AnyFromAny(100, 0, 5)", electronCuts && "pid != -9999", "goff");
  TH1F *AnyFromAny  = (TH1F *)gROOT->FindObject("AnyFromAny");
  AnyFromAny->SetLineColor(kBlack);
  AnyFromAny->SetLineWidth(2);
  AnyFromAny->SetFillStyle(0);

  AnyFromAny->SetTitle("Momentum distribution of simulation reconstructed particles");
  AnyFromAny->GetYaxis()->SetMaxDigits(3);
  AnyFromAny->GetYaxis()->SetTitle("Counts");
  AnyFromAny->GetXaxis()->SetTitle("P (GeV)");
    
  ntuple_sim->Draw("P>>AnyFromAny_AM(100, 0, 5", electronCuts && "pid != -9999 && mc_pid != -9999", "goff");
  TH1F *AnyFromAny_AM = (TH1F *)gROOT->FindObject("AnyFromAny_AM");
  AnyFromAny_AM->SetLineColor(kRed);
  AnyFromAny_AM->SetLineWidth(2);
  AnyFromAny_AM->SetFillStyle(0);

  ntuple_sim->Draw("P>>AnyFromAny_NAM(100, 0, 5)", electronCuts && "pid != -9999 && mc_pid == -9999", "goff");
  TH1F *AnyFromAny_NAM = (TH1F *)gROOT->FindObject("AnyFromAny_NAM");
  AnyFromAny_NAM->SetLineColor(kBlue);
  AnyFromAny_NAM->SetLineWidth(2);
  AnyFromAny_NAM->SetFillStyle(0);

  TCanvas *c = new TCanvas("all_AM", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  AnyFromAny->Draw("HIST");
  AnyFromAny_AM->Draw("HIST SAME");
  AnyFromAny_NAM->Draw("HIST SAME");
  
  TLegend *l = new TLegend(0.55, 0.55, 0.85, 0.85); // x1,y1,x2,y2
  l->AddEntry(PipFromAny,     "X #rightarrow X", "l");
  l->AddEntry(PipFromAny_AM,  "X #rightarrow X, Ang. Matching", "l");
  l->AddEntry(PipFromAny_NAM, "X #rightarrow X, No Ang. Matching", "l");
  l->SetLineWidth(0);
  l->Draw();
  
  c->Draw();

  /*** RATIO ***/
  // from all, how many did Angular Match?
  
  TCanvas *c1 = new TCanvas("all_AM-ratio", "c1", 1000, 1000);
  gStyle->SetOptStat(0);

  TH1F *Ratio = new TH1F("Ratio", "Ratio", 100, 0, 5);
  Ratio->Divide(AnyFromAny_AM, AnyFromAny, 1, 1, "B");

  Ratio->SetTitle("N(X #rightarrow X, Ang. Matching)/N(X #rightarrow X)");
  Ratio->GetYaxis()->SetMaxDigits(3);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");

  Ratio->SetLineColor(kRed);
  Ratio->SetLineWidth(2);
  Ratio->SetFillStyle(0);
  
  Ratio->Draw("E");
    
  c1->Draw();
}

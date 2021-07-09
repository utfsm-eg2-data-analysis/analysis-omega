void CheckAngularMatching_PiPlus() {
  TChain *ntuple_sim = new TChain();
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v1.root/ntuple_sim");
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v2.root/ntuple_sim");
  // ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v3.root/ntuple_sim");
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v4.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>PipFromAny(100, 0, 4)", electronCuts && "pid == 211", "goff");
  TH1F *PipFromAny  = (TH1F *)gROOT->FindObject("PipFromAny");
  PipFromAny->SetLineColor(kBlack);
  PipFromAny->SetLineWidth(2);
  PipFromAny->SetFillStyle(0);

  PipFromAny->SetTitle("Momentum distribution of simulation reconstructed #pi^{+}");
  PipFromAny->GetYaxis()->SetMaxDigits(3);
  PipFromAny->GetYaxis()->SetTitle("Counts");
  PipFromAny->GetXaxis()->SetTitle("P (GeV)");
    
  ntuple_sim->Draw("P>>PipFromAny_AM(100, 0, 4)", electronCuts && "pid == 211 && mc_pid != -9999", "goff");
  TH1F *PipFromAny_AM = (TH1F *)gROOT->FindObject("PipFromAny_AM");
  PipFromAny_AM->SetLineColor(kRed);
  PipFromAny_AM->SetLineWidth(2);
  PipFromAny_AM->SetFillStyle(0);

  ntuple_sim->Draw("P>>PipFromAny_NAM(100, 0, 4)", electronCuts && "pid == 211 && mc_pid == -9999", "goff");
  TH1F *PipFromAny_NAM = (TH1F *)gROOT->FindObject("PipFromAny_NAM");
  PipFromAny_NAM->SetLineColor(kBlue);
  PipFromAny_NAM->SetLineWidth(2);
  PipFromAny_NAM->SetFillStyle(0);

  TCanvas *c = new TCanvas("pip_AM", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  PipFromAny->Draw("HIST");
  PipFromAny_AM->Draw("HIST SAME");
  PipFromAny_NAM->Draw("HIST SAME");
  
  TLegend *l = new TLegend(0.6, 0.6, 0.9, 0.9); // x1,y1,x2,y2
  l->AddEntry(PipFromAny,     "X #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromAny_AM,  "X #rightarrow #pi^{+} - Ang. Matching", "l");
  l->AddEntry(PipFromAny_NAM, "X #rightarrow #pi^{+} - No Ang. Matching", "l");
  l->Draw();
  
  c->Draw();

  /*** RATIO ***/
  // from all, how many did Angular Match?
  
  TCanvas *c1 = new TCanvas("pip_AM-ratio", "c1", 1000, 1000);
  gStyle->SetOptStat(0);

  TH1F *Ratio = new TH1F("Ratio", "Ratio", 100, 0, 4);
  Ratio->Divide(PipFromAny_AM, PipFromAny, 1, 1, "B");

  Ratio->SetTitle("N(X #rightarrow #pi^{+}, Ang. Matching)/N(X #rightarrow #pi^{+})");
  Ratio->GetYaxis()->SetMaxDigits(3);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");

  Ratio->SetLineColor(kRed);
  Ratio->SetLineWidth(2);
  Ratio->SetFillStyle(0);
  
  Ratio->Draw("E");
    
  c1->Draw();
}

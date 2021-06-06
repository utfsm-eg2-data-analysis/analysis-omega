void CheckMisID_PiPlus() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v2.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>PipFromAny_AM(100, 0, 4)", electronCuts && "pid == 211 && mc_pid != -9999", "goff");
  TH1F *PipFromAny_AM = (TH1F *)gROOT->FindObject("PipFromAny_AM");
  PipFromAny_AM->SetLineColor(kRed);
  PipFromAny_AM->SetLineWidth(2);
  PipFromAny_AM->SetFillStyle(0);

  PipFromAny_AM->SetTitle("Momentum distribution of simulation reconstructed #pi^{+}");
  PipFromAny_AM->GetYaxis()->SetRangeUser(0, 2200);
  PipFromAny_AM->GetYaxis()->SetMaxDigits(3);
  PipFromAny_AM->GetYaxis()->SetTitle("Counts");
  PipFromAny_AM->GetXaxis()->SetTitle("P (GeV)");
  
  ntuple_sim->Draw("P>>PipFromTrue(100, 0, 4)", electronCuts && "pid == 211 && mc_pid == 211", "goff");
  TH1F *PipFromTrue = (TH1F *)gROOT->FindObject("PipFromTrue");
  PipFromTrue->SetLineColor(kAzure+7);
  PipFromTrue->SetLineWidth(2);
  PipFromTrue->SetFillStyle(0);
  
  ntuple_sim->Draw("P>>PipFromFake(100, 0, 4)", electronCuts && "pid == 211 && mc_pid != 211 && mc_pid != -9999", "goff");
  TH1F *PipFromFake = (TH1F *)gROOT->FindObject("PipFromFake");
  PipFromFake->SetLineColor(kOrange+7);
  PipFromFake->SetLineWidth(2);
  PipFromFake->SetFillStyle(0);
  
  TCanvas *c = new TCanvas("pip_MisID", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  PipFromAny_AM->Draw("HIST");
  PipFromTrue->Draw("HIST SAME");
  PipFromFake->Draw("HIST SAME");

  TLegend *l = new TLegend(0.55, 0.55, 0.85, 0.85); // x1,y1,x2,y2
  l->AddEntry(PipFromAny_AM, "X #rightarrow #pi^{+}, Ang. Matching", "l");
  l->AddEntry(PipFromTrue,   "#pi^{+} #rightarrow #pi^{+}, Ang. Matching", "l");
  l->AddEntry(PipFromFake,   "(not #pi^{+}) #rightarrow #pi^{+}, Ang. Matching", "l");
  l->SetLineWidth(0);
  l->Draw();
  
  c->Draw();

  /*** RATIO ***/
  // from all angular matched, how many are contaminated?
  
  TCanvas *c1 = new TCanvas("pip_MisID-ratio", "c1", 1000, 1000);
  gStyle->SetOptStat(0);

  TH1F *Ratio = new TH1F("Ratio", "Ratio", 100, 0, 4);
  Ratio->Divide(PipFromFake, PipFromAny_AM, 1, 1, "B");

  Ratio->SetTitle("N((not #pi^{+}) #rightarrow #pi^{+})/N(X #rightarrow #pi^{+})");
  Ratio->GetYaxis()->SetRangeUser(0, 0.1);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");

  Ratio->SetLineColor(kOrange+7);
  Ratio->SetLineWidth(2);
  Ratio->SetFillStyle(0);
  
  Ratio->Draw("E");
    
  c1->Draw();
}

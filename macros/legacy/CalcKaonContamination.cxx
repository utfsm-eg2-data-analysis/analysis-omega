void CalcKaonContamination() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_final.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";

  ntuple_sim->Draw("P>>PipFromAny_AM(100, 0, 4.5)", electronCuts && "pid == 211 && mc_pid != -9999", "goff");
  TH1F *PipFromAny_AM = (TH1F *)gROOT->FindObject("PipFromAny_AM");

  ntuple_sim->Draw("P>>PipFromKaon(100, 0, 4.5)", electronCuts && "pid == 211 && mc_pid == 321", "goff");
  TH1F *PipFromKaon = (TH1F *)gROOT->FindObject("PipFromKaon");

  TH1F *Ratio = new TH1F("Ratio", "Ratio", 100, 0, 4.5);
  Ratio->Divide(PipFromKaon, PipFromAny_AM, 1, 1, "B");
  
  Ratio->SetTitle("N(K^{+} #rightarrow #pi^{+})/N(X #rightarrow #pi^{+})");
  Ratio->GetYaxis()->SetMaxDigits(3);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");

  Ratio->SetLineColor(kRed);
  Ratio->SetLineWidth(2);
  Ratio->SetFillStyle(0);

  TCanvas *c = new TCanvas("kaonp-contamination", "c", 1000, 1000);
  gStyle->SetOptStat(0);

  Ratio->Draw("E");
  
  c->Draw();
}

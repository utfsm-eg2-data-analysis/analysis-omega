void RatioPionPlusMisID() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>PipFromAny(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211", "goff");
  TH1F *PipFromAny  = (TH1F *)gROOT->FindObject("PipFromAny");

  ntuple_sim->Draw("P>>PipFromTrue(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == 211", "goff");
  TH1F *PipFromTrue = (TH1F *)gROOT->FindObject("PipFromTrue");

  ntuple_sim->Draw("P>>PipFromKaon(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == 321", "goff");
  TH1F *PipFromKaon = (TH1F *)gROOT->FindObject("PipFromKaon");
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);

  TH1F *Ratio = new TH1F("ratio", "ratio", 100, 0, 4);
  // Ratio->Divide(PipFromTrue, PipFromAny, 1, 1, "B");
  Ratio->Divide(PipFromKaon, PipFromAny, 1, 1, "B");
  // Ratio->SetLineColor(kBlue);
  Ratio->SetLineColor(kRed);
  Ratio->SetLineWidth(2);

  // Ratio->SetTitle("N(#pi^{+} #rightarrow #pi^{+})/N(X #rightarrow #pi^{+})");
  Ratio->SetTitle("N(K^{+} #rightarrow #pi^{+})/N(X #rightarrow #pi^{+})");
  Ratio->GetYaxis()->SetMaxDigits(3);
  Ratio->GetYaxis()->SetTitle("Ratio");
  Ratio->GetXaxis()->SetTitle("P (GeV)");  

  Ratio->Draw("E");
  
  c->Print("piplus-misID_ratio.png");
}

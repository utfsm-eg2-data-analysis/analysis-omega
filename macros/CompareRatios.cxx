void CompareRatios() {
  TChain *ntuple_sim_v1 = new TChain();
  ntuple_sim_v1->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v1.root/ntuple_sim");

  TChain *ntuple_sim_v2 = new TChain();
  ntuple_sim_v2->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v2.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim_v1->Draw("P>>PipFromAny_v1(100, 0, 4)", electronCuts && "pid == 211", "goff");
  TH1F *PipFromAny_v1  = (TH1F *)gROOT->FindObject("PipFromAny_v1");
  ntuple_sim_v1->Draw("P>>PipFromAny_AM_v1(100, 0, 4)", electronCuts && "pid == 211 && mc_pid != -9999", "goff");
  TH1F *PipFromAny_AM_v1 = (TH1F *)gROOT->FindObject("PipFromAny_AM_v1");

  TH1F *Ratio_v1 = new TH1F("Ratio_v1", "Ratio_v1", 100, 0, 4);
  Ratio_v1->Divide(PipFromAny_AM_v1, PipFromAny_v1, 1, 1, "B");

  ntuple_sim_v2->Draw("P>>PipFromAny_v2(100, 0, 4)", electronCuts && "pid == 211", "goff");
  TH1F *PipFromAny_v2  = (TH1F *)gROOT->FindObject("PipFromAny_v2");
  ntuple_sim_v2->Draw("P>>PipFromAny_AM_v2(100, 0, 4)", electronCuts && "pid == 211 && mc_pid != -9999", "goff");
  TH1F *PipFromAny_AM_v2 = (TH1F *)gROOT->FindObject("PipFromAny_AM_v2");

  TH1F *Ratio_v2 = new TH1F("Ratio_v2", "Ratio_v2", 100, 0, 4);
  Ratio_v2->Divide(PipFromAny_AM_v2, PipFromAny_v2, 1, 1, "B");

  /*** RATIO ***/

  TCanvas *c = new TCanvas("compare-ratio", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  c->SetGrid();
  
  TH1F *CompareRatios = new TH1F("CompareRatios", "CompareRatios", 100, 0, 4);
  CompareRatios->Divide(Ratio_v2, Ratio_v1);

  CompareRatios->SetTitle("Ratio_v2/Ratio_v1");
  CompareRatios->GetYaxis()->SetMaxDigits(3);
  CompareRatios->GetYaxis()->SetTitle("Ratio");
  CompareRatios->GetXaxis()->SetTitle("P (GeV)");

  CompareRatios->SetLineColor(kRed);
  CompareRatios->SetLineWidth(2);
  CompareRatios->SetFillStyle(0);
  
  CompareRatios->Draw("E");
    
  c->Draw();
}

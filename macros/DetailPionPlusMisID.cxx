void DetailPionPlusMisID() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_final.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>PipFromFake(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid != 211 && mc_pid != -9999", "goff");
  TH1F *PipFromFake = (TH1F *)gROOT->FindObject("PipFromFake");
  PipFromFake->SetLineColor(kOrange+7);
  PipFromFake->SetLineWidth(2);
  PipFromFake->SetFillStyle(0);

  PipFromFake->SetTitle("Momentum distribution of simulation reconstructed #pi^{+}");
  PipFromFake->GetYaxis()->SetMaxDigits(3);
  PipFromFake->GetYaxis()->SetTitle("Counts");
  PipFromFake->GetXaxis()->SetTitle("P (GeV)");
  
  ntuple_sim->Draw("P>>PipFromProt(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == 2212", "goff");
  TH1F *PipFromProt = (TH1F *)gROOT->FindObject("PipFromProt");
  PipFromProt->SetLineColor(kGreen+3);
  PipFromProt->SetLineWidth(2);
  PipFromProt->SetFillStyle(0);

  ntuple_sim->Draw("P>>PipFromKaon(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == 321", "goff");
  TH1F *PipFromKaon = (TH1F *)gROOT->FindObject("PipFromKaon");
  PipFromKaon->SetLineColor(kRed);
  PipFromKaon->SetLineWidth(2);
  PipFromKaon->SetFillStyle(0);

  ntuple_sim->Draw("P>>PipFromPhot(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == 22", "goff");
  TH1F *PipFromPhot = (TH1F *)gROOT->FindObject("PipFromPhot");
  PipFromPhot->SetLineColor(kAzure+7);
  PipFromPhot->SetLineWidth(2);
  PipFromPhot->SetFillStyle(0);

  ntuple_sim->Draw("P>>PipFromNeut(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == 2112", "goff");
  TH1F *PipFromNeut = (TH1F *)gROOT->FindObject("PipFromNeut");
  PipFromNeut->SetLineColor(kOrange+3); // brown
  PipFromNeut->SetLineWidth(2);
  PipFromNeut->SetFillStyle(0);

  ntuple_sim->Draw("P>>PipFromPosi(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == -11", "goff");
  TH1F *PipFromPosi = (TH1F *)gROOT->FindObject("PipFromPosi");
  PipFromPosi->SetLineColor(kMagenta-4);
  PipFromPosi->SetLineWidth(2);
  PipFromPosi->SetFillStyle(0);

  ntuple_sim->Draw("P>>PipFromPim(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == -211", "goff");
  TH1F *PipFromPim = (TH1F *)gROOT->FindObject("PipFromPim");
  PipFromPim->SetLineColor(kBlue);
  PipFromPim->SetLineWidth(2);
  PipFromPim->SetFillStyle(0);

  ntuple_sim->Draw("P>>PipFromElec(100, 0, 4)", electronCuts && "pid != -9999 && pid == 211 && mc_pid == 11", "goff");
  TH1F *PipFromElec = (TH1F *)gROOT->FindObject("PipFromElec");
  PipFromElec->SetLineColor(kBlack);
  PipFromElec->SetLineWidth(2);
  PipFromElec->SetFillStyle(0);
  
  TCanvas *c = new TCanvas("pip_MisID-detail", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  PipFromFake->Draw("HIST");
  PipFromProt->Draw("HIST SAME");
  PipFromKaon->Draw("HIST SAME");
  PipFromPhot->Draw("HIST SAME");
  PipFromNeut->Draw("HIST SAME");
  PipFromPosi->Draw("HIST SAME");
  PipFromPim->Draw("HIST SAME");
  PipFromElec->Draw("HIST SAME");

  TLegend *l = new TLegend(0.55, 0.55, 0.85, 0.85); // x1,y1,x2,y2
  l->AddEntry(PipFromFake, "(not #pi^{+}) #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromProt, "p #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromKaon, "K^{+} #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromPhot, "#gamma #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromNeut, "n #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromPosi, "e^{+} #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromPim, "#pi^{-} #rightarrow #pi^{+}", "l");
  l->AddEntry(PipFromElec, "e^{-} #rightarrow #pi^{+}", "l");
  l->SetLineWidth(0);
  l->Draw();
  
  c->Print();
}

void DetailGammaMisID() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_final.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  
  ntuple_sim->Draw("P>>GammaFromFake(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid != 22 && mc_pid != -9999", "goff");
  TH1F *GammaFromFake = (TH1F *)gROOT->FindObject("GammaFromFake");
  GammaFromFake->SetLineColor(kOrange+7);
  GammaFromFake->SetLineWidth(2);
  GammaFromFake->SetFillStyle(0);

  GammaFromFake->SetTitle("Momentum distribution of simulation reconstructed #gamma");
  GammaFromFake->GetYaxis()->SetMaxDigits(3);
  GammaFromFake->GetYaxis()->SetTitle("Counts");
  GammaFromFake->GetXaxis()->SetTitle("P (GeV)");
  
  ntuple_sim->Draw("P>>GammaFromProt(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == 2212", "goff");
  TH1F *GammaFromProt = (TH1F *)gROOT->FindObject("GammaFromProt");
  GammaFromProt->SetLineColor(kGreen+3);
  GammaFromProt->SetLineWidth(2);
  GammaFromProt->SetFillStyle(0);

  ntuple_sim->Draw("P>>GammaFromKaon(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == 130", "goff");
  TH1F *GammaFromKaon = (TH1F *)gROOT->FindObject("GammaFromKaon");
  GammaFromKaon->SetLineColor(kRed);
  GammaFromKaon->SetLineWidth(2);
  GammaFromKaon->SetFillStyle(0);

  ntuple_sim->Draw("P>>GammaFromPip(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == 211", "goff");
  TH1F *GammaFromPip = (TH1F *)gROOT->FindObject("GammaFromPip");
  GammaFromPip->SetLineColor(kAzure+7);
  GammaFromPip->SetLineWidth(2);
  GammaFromPip->SetFillStyle(0);

  ntuple_sim->Draw("P>>GammaFromNeut(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == 2112", "goff");
  TH1F *GammaFromNeut = (TH1F *)gROOT->FindObject("GammaFromNeut");
  GammaFromNeut->SetLineColor(kOrange+3); // brown
  GammaFromNeut->SetLineWidth(2);
  GammaFromNeut->SetFillStyle(0);

  ntuple_sim->Draw("P>>GammaFromPosi(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == -11", "goff");
  TH1F *GammaFromPosi = (TH1F *)gROOT->FindObject("GammaFromPosi");
  GammaFromPosi->SetLineColor(kMagenta-4.5);
  GammaFromPosi->SetLineWidth(2);
  GammaFromPosi->SetFillStyle(0);

  ntuple_sim->Draw("P>>GammaFromPim(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == -211", "goff");
  TH1F *GammaFromPim = (TH1F *)gROOT->FindObject("GammaFromPim");
  GammaFromPim->SetLineColor(kBlue);
  GammaFromPim->SetLineWidth(2);
  GammaFromPim->SetFillStyle(0);

  ntuple_sim->Draw("P>>GammaFromElec(100, 0, 4.5)", electronCuts && "pid == 22 && mc_pid == 11", "goff");
  TH1F *GammaFromElec = (TH1F *)gROOT->FindObject("GammaFromElec");
  GammaFromElec->SetLineColor(kBlack);
  GammaFromElec->SetLineWidth(2);
  GammaFromElec->SetFillStyle(0);
  
  TCanvas *c = new TCanvas("gamma_MisID-detail", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  GammaFromFake->Draw("HIST");
  GammaFromProt->Draw("HIST SAME");
  GammaFromKaon->Draw("HIST SAME");
  GammaFromPip->Draw("HIST SAME");
  GammaFromNeut->Draw("HIST SAME");
  GammaFromPosi->Draw("HIST SAME");
  GammaFromPim->Draw("HIST SAME");
  GammaFromElec->Draw("HIST SAME");

  std::cout << "N(GammaFromFake) = " << GammaFromFake->GetEntries() << std::endl;
  std::cout << "N(GammaFromProt) = " << GammaFromProt->GetEntries() << std::endl;
  std::cout << "N(GammaFromKaon) = " << GammaFromKaon->GetEntries() << std::endl;
  std::cout << "N(GammaFromPip)  = " << GammaFromPip->GetEntries()  << std::endl;
  std::cout << "N(GammaFromNeut) = " << GammaFromNeut->GetEntries() << std::endl;
  std::cout << "N(GammaFromPosi) = " << GammaFromPosi->GetEntries() << std::endl;
  std::cout << "N(GammaFromPim)  = " << GammaFromPim->GetEntries()  << std::endl;
  std::cout << "N(GammaFromElec) = " << GammaFromElec->GetEntries() << std::endl;

  TLegend *l = new TLegend(0.55, 0.55, 0.85, 0.85); // x1,y1,x2,y2
  l->AddEntry(GammaFromFake, "(not #gamma) #rightarrow #gamma", "l");
  l->AddEntry(GammaFromProt, "p #rightarrow #gamma", "l");
  l->AddEntry(GammaFromKaon, "K^{0}_{L} #rightarrow #gamma", "l");
  l->AddEntry(GammaFromPip,  "#pi^{+} #rightarrow #gamma", "l");
  l->AddEntry(GammaFromNeut, "n #rightarrow #gamma", "l");
  l->AddEntry(GammaFromPosi, "e^{+} #rightarrow #gamma", "l");
  l->AddEntry(GammaFromPim,  "#pi^{-} #rightarrow #gamma", "l");
  l->AddEntry(GammaFromElec, "e^{-} #rightarrow #gamma", "l");
  l->SetLineWidth(0);
  l->Draw();
  
  c->Draw();
}

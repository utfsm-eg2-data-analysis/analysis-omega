void CalcElectronResolution() {
  TChain *ntuple_e = new TChain();
  ntuple_e->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC.root/ntuple_e");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  TCut angularMatching = "P != -9999 && mc_P != -9999";

  /*** PhiLab ***/
  
  ntuple_e->Draw("(PhiLab - mc_PhiLab)>>HistPhiLab(100, -2, 2)", electronCuts && angularMatching && "P > 0.75 && P < 0.85", "goff");
  TH1F *HistPhiLab = (TH1F *)gROOT->FindObject("HistPhiLab");
  HistPhiLab->SetLineColor(kRed);
  HistPhiLab->SetLineWidth(2);
  HistPhiLab->SetFillStyle(0);

  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(1);
  
  HistPhiLab->Draw("E");
    
  c->Draw();

  /*** ThetaLab ***/
  
  ntuple_e->Draw("(ThetaLab - mc_ThetaLab)>>HistThetaLab(100, -2, 2)", electronCuts && angularMatching && "P > 0.75 && P < 0.85", "goff");
  TH1F *HistThetaLab = (TH1F *)gROOT->FindObject("HistThetaLab");
  HistThetaLab->SetLineColor(kRed);
  HistThetaLab->SetLineWidth(2);
  HistThetaLab->SetFillStyle(0);

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
  gStyle->SetOptStat(1);
  
  HistThetaLab->Draw("E");
    
  c1->Draw();
}

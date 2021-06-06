void CalcResolution_PiPlus() {
  TChain *ntuple_sim = new TChain();
  ntuple_sim->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_HSim_v1.root/ntuple_sim");

  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(vyec) < 1.4";
  TCut angularMatching = "P != -9999 && mc_P != -9999";

  /*** PhiLab ***/
  
  ntuple_sim->Draw("(PhiLab - mc_PhiLab)>>HistPhiLab(100, -2, 2)", "mc_pid == 211" && electronCuts && angularMatching && "mc_P > 0.0 && mc_P < 0.35", "goff");
  TH1F *HistPhiLab = (TH1F *)gROOT->FindObject("HistPhiLab");
  HistPhiLab->SetLineColor(kBlack);
  HistPhiLab->SetLineWidth(2);
  HistPhiLab->SetFillStyle(0);

  TCanvas *c = new TCanvas("pip_res-phi", "c", 1000, 1000);
  gStyle->SetOptStat(1);
  
  HistPhiLab->Draw("E");
    
  c->Draw();

  /*** ThetaLab ***/
  
  ntuple_sim->Draw("(ThetaLab - mc_ThetaLab)>>HistThetaLab(100, -2, 2)", electronCuts && angularMatching && "mc_P > 0.0 && mc_P < 0.35", "goff");
  TH1F *HistThetaLab = (TH1F *)gROOT->FindObject("HistThetaLab");
  HistThetaLab->SetLineColor(kBlack);
  HistThetaLab->SetLineWidth(2);
  HistThetaLab->SetFillStyle(0);

  TCanvas *c1 = new TCanvas("pip_res-theta", "c1", 1000, 1000);
  gStyle->SetOptStat(1);
  
  HistThetaLab->Draw("E");
    
  c1->Draw();
}

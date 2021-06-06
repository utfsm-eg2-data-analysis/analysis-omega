void CompareElectronCuts() {
  TChain *ntuple_data_SM = new TChain();
  ntuple_data_SM->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_42011_dev.root/ntuple_data");

  TChain *ntuple_data_pre = new TChain();
  ntuple_data_pre->Add("/home/borquez/GetSimpleTuple_dev/bin/prunedC_42011_main.root/ntuple_data");

  ntuple_data_SM->Draw("Pe>>ElecSM(150, 0, 5)", "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 1 && TMath::Abs(vyec) < 1.4", "goff");
  TH1F *ElecSM  = (TH1F *)gROOT->FindObject("ElecSM");
  ElecSM->SetLineColor(kBlack);
  ElecSM->SetLineWidth(2);
  ElecSM->SetFillStyle(0);
  
  ntuple_data_pre->Draw("Pe>>ElecPrev(150, 0, 5)", "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 1 && TMath::Abs(vyec) < 1.4", "goff");
  TH1F *ElecPrev = (TH1F *)gROOT->FindObject("ElecPrev");
  ElecPrev->SetLineColor(kBlue);
  ElecPrev->SetLineWidth(2);
  ElecPrev->SetFillStyle(0);
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(1);
  /*
  ElecSM->Draw("HIST");
  ElecPrev->Draw("HIST SAME");
  */
  
  TH1F *Ratio = new TH1F("ratio", "ratio", 150, 0, 5);
  Ratio->Divide(ElecSM, ElecPrev);
  Ratio->SetLineColor(kBlack);
  Ratio->SetLineWidth(2);
  Ratio->Draw("E");

  std::cout << ElecSM->GetEntries() << "\t" << ElecPrev->GetEntries() << std::endl;
  
  c->Print("electron-compare.png");
}

void CheckCombBkgOnData() {
  // WORK IN PROGRES...
  
  TChain *mix = new TChain();
  mix->Add("/home/borquez/analysis-omega/out/FilterNCombine/basic/Fe/comb_basic-Fe.root/mix");

  // define cuts
  TCut cutPi0 = "0.059 < pi0M_corr && pi0M_corr < 0.203"; // mean=0.131 & sigma=0.024
  TCut cut02 = "TMath::Sqrt(2*M[0]*M[1] + 2*E_corr[0]*E_corr[1] - 2*(Px_corr[0]*Px_corr[1] + Py_corr[0]*Py_corr[1] + Pz_corr[0]*Pz_corr[1])) < 0.48 || TMath::Sqrt(2*M[0]*M[1] + 2*E_corr[0]*E_corr[1] - 2*(Px_corr[0]*Px_corr[1] + Py_corr[0]*Py_corr[1] + Pz_corr[0]*Pz_corr[1])) > 0.51"; // pippimM redefined... lalala
  TCut cut04 = "StatusEl > 0 && NRowsDCEl != 0 && DCStatusEl > 0 && StatDCEl > 0 && NRowsECEl != 0 && StatECEl > 0 && NRowsSCEl != 0 && SCStatusEl == 33";
  TCut cut05 = "Pe > 0.2 && ThetaLabEl < 120.";
  TCut cut06 = "P_corr[0] > 0.2 && ThetaLab[0] < 120.";
  // TCut cut07 = "Q2 > 1. && Q2 < 4. && Nu > 2.2 && Nu < 4.2 && wZ_corr > 0.5 && wZ_corr < 1.0 && wPt2_corr > 0. && wPt2_corr < 1.5";
  TCut cut08 = "P_corr[2] > 0.2 && P_corr[3] > 0.2";
  TCut cut09 = "P_corr[1] < 5.";
  // TCut cut10 = "deltaTheta[2] > 10. && deltaTheta[3] > 10.";
  TCut cut11 = "(BettaCalc[0] - Betta[0]) > -0.035 && (BettaCalc[0] - Betta[0]) < 0.025";
  TCut cut12 = "(BettaCalc[1] - Betta[1]) >= -0.03 && (BettaCalc[1] - Betta[1]) <= 0.03";
  TCut cut13 = "NpheEl > ((SectorEl==0||SectorEl==1)*25 + (SectorEl==2)*26 + (SectorEl==3)*21 + (SectorEl==4||SectorEl==5)*28)";
  TCut cut14 = "Status[0] > 0 && NRowsDC[0] != 0 && StatDC[0] > 0 && DCStatus[0] > 0";
  TCut cut15 = "Status[1] > 0 && NRowsDC[1] != 0 && StatDC[1] > 0 && DCStatus[1] > 0";
  //TCut cut16 = "deltaZ[0] > -2 && deltaZ[0] < 2";
  //TCut cut17 = "deltaZ[1] > -2 && deltaZ[1] < 2";
  // TCut cut18 = "wPhiPQ_corr < -80. || wPhiPQ_corr > 80";
  //TCut cut19 = "P2_corr[2]*(TMath::Power(Betta[2], -2) - 1) > -0.041537 && P2_corr[2]*(TMath::Power(Betta[2], -2) - 1) < 0.031435 && P2_corr[3]*(TMath::Power(Betta[3], -2) - 1) > -0.044665 && P2_corr[3]*(TMath::Power(Betta[3], -2) - 1) < 0.035156";
  //TCut cut20 = "Mass2[2] > -0.041537 && Mass2[2] < 0.031435 && Mass2[3] > -0.044665 && Mass2[3] < 0.035156";
  //TCut cut21 = "((Etote/0.27 > (SectorEl==0||SectorEl==1)*(1.05*Pe - 0.46) + (SectorEl==2||SectorEl==4||SectorEl==5)*(1.1*Pe - 0.43) + (SectorEl==3)*(1.07*Pe - 0.43)) && (Etote/0.27 < (SectorEl==0||SectorEl==1)*(1.05*Pe + 0.18) + (SectorEl==2||SectorEl==4||SectorEl==5)*(1.1*Pe + 0.18) + (SectorEl==3)*(1.07*Pe + 0.18)) &&  ((Eine/0.27 + Eoute/0.27) < (SectorEl==0||SectorEl==1)*(1.11*Pe) + (SectorEl==2||SectorEl==5)*(1.19*Pe) + (SectorEl==3)*(1.15*Pe) + (SectorEl==4)*(1.22*Pe)) && ((Eine/0.27 + Eoute/0.27) > (SectorEl==0||SectorEl==1)*(0.75*Pe) + (SectorEl==2||SectorEl==5)*(0.84*Pe) + (SectorEl==3)*(0.83*Pe) + (SectorEl==4)*(0.85*Pe)))";
  TCut cut22 = "(NRowsCC[0] != 0 && StatCC[0] > 0 && Nphe[0] > 25 && Chi2CC[0] < 5/57.3 && P_corr[0] >= 2.7 && T4[0] > -0.35 && T4[0] < 0.35) || (P_corr[0] < 2.7)";
  TCut cut23 = "(StatCC[1] > 0 && Nphe[1] > 25 && P_corr[1] > 2.5 && T4[1] > -1.50 && T4[1] < 1.50) || (P_corr[1] <= 2.5)";
  
  TCut electronCuts = "Q2 > 1 && W > 2 && Yb < 0.85 && TargType == 2 && TMath::Abs(Yec) < 1.4";
  TCut allCuts = cutPi0 && cut02 && cut04 && cut05 && cut06 && cut08 && cut09 && cut11 && cut12 && cut13 && cut14 && cut15 && cut22 && cut23;
  
  mix->Draw("wD_corr>>AllCombs(100, 0, 2.5)", allCuts && electronCuts, "goff");
  TH1F *AllCombs = (TH1F *)gROOT->FindObject("AllCombs");
  AllCombs->SetLineColor(kBlack);
  AllCombs->SetLineWidth(2);
  AllCombs->SetFillStyle(0);

  AllCombs->SetTitle("#Deltam(#gamma#gamma#pi^{+}#pi^{-}) on Fe data");
  AllCombs->GetYaxis()->SetMaxDigits(3);
  AllCombs->GetYaxis()->SetTitle("Counts");
  AllCombs->GetXaxis()->SetTitle("Reconstructed Mass (GeV)");
  
  mix->Draw("wD_corr>>FirstComb(100, 0, 2.5)", allCuts && electronCuts && "cIndex == 0", "goff");
  TH1F *FirstComb = (TH1F *)gROOT->FindObject("FirstComb");
  FirstComb->SetLineColor(kAzure+7);
  FirstComb->SetLineWidth(2);
  FirstComb->SetFillStyle(0);

  mix->Draw("wD_corr>>SecondComb(100, 0, 2.5)", allCuts && electronCuts && "cIndex == 1", "goff");
  TH1F *SecondComb = (TH1F *)gROOT->FindObject("SecondComb");
  SecondComb->SetLineColor(kRed);
  SecondComb->SetLineWidth(2);
  SecondComb->SetFillStyle(0);

  mix->Draw("wD_corr>>ThirdComb(100, 0, 2.5)", allCuts && electronCuts && "cIndex == 2", "goff");
  TH1F *ThirdComb = (TH1F *)gROOT->FindObject("ThirdComb");
  ThirdComb->SetLineColor(kOrange+7);
  ThirdComb->SetLineWidth(2);
  ThirdComb->SetFillStyle(0);
  
  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  gStyle->SetOptStat(0);
  
  AllCombs->Draw("HIST");
  FirstComb->Draw("HIST SAME");
  SecondComb->Draw("HIST SAME");
  ThirdComb->Draw("HIST SAME");
    
  TLegend *l = new TLegend(0.6, 0.6, 0.8, 0.8); // x1,y1,x2,y2
  l->AddEntry(AllCombs, "All combinations", "l");
  l->AddEntry(FirstComb, "Combination #1", "l");
  l->AddEntry(SecondComb, "Combination #2", "l");
  l->AddEntry(ThirdComb, "Combination #3", "l");
  l->Draw();
  
  c->Print("comb_bkg.png");  
}

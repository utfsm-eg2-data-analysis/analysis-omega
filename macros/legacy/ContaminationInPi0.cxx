void ContaminationInPi0() {
  // (work in progress...)
  
  /*** INPUT OPTIONS ***/

  TCut cutVertex = "Yec > -1.4 && Yec < 1.4";

  TString kinvarOption = "pi0M";
  TString titleAxis = "Reconstructed m(#gamma#gamma) [GeV]";
  TString histProperties = "(160, 0, 1.6)";
  TString mc_kinvarOption = "mc_" + kinvarOption;
  
  /*** MAIN ***/
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(gDataDir + "/comb_usm-D-*.root/mix");
  // treeExtracted->Add(gDataDir + "/comb_bkg-D-*.root/mix");

  TH1D *theHist_REC;
  treeExtracted->Draw(kinvarOption + ">>simrec" + histProperties, gCutDIS, "goff");
  theHist_REC = (TH1D *)gROOT->FindObject("simrec");  
  
  theHist_REC->SetFillStyle(0);
  theHist_REC->SetLineColor(kBlack);
  theHist_REC->SetLineWidth(2);

  theHist_REC->GetXaxis()->SetTitle(titleAxis);
  theHist_REC->GetXaxis()->CenterTitle();
  theHist_REC->GetYaxis()->SetTitle("Candidates");
  theHist_REC->GetYaxis()->SetMaxDigits(3);
  theHist_REC->GetYaxis()->CenterTitle();

  treeExtracted->SetAlias("Pgamma1", "TMath::Sqrt(Px[2]*Px[2] + Py[2]*Py[2] + Pz[2]*Pz[2])");
  treeExtracted->SetAlias("Pgamma2", "TMath::Sqrt(Px[3]*Px[3] + Py[3]*Py[3] + Pz[3]*Pz[3])");
  
  TH1D *neutronHist;
  treeExtracted->Draw(kinvarOption + ">>neutron" + histProperties, gCutDIS && "(TruePid[2] == 2112 || TruePid[3] == 2112)" && "(Pgamma1 > 3.5 && Pgamma2 > 3.5)", "goff");
  neutronHist = (TH1D *)gROOT->FindObject("neutron");
  
  neutronHist->SetFillStyle(0);
  neutronHist->SetLineColor(kGreen+3);
  neutronHist->SetLineWidth(2);

  TCanvas *c = new TCanvas("pi0-contamination", "c"); 
  c->SetGrid();
  gStyle->SetOptStat(0);
  
  theHist_REC->Draw("HIST");
  neutronHist->Draw("HIST SAME");

  TLegend *l = new TLegend(0.7, 0.7, 0.9, 0.9);
  l->AddEntry(theHist_REC, "X #rightarrow #gamma ", "l");
  l->AddEntry(neutronHist, "n #rightarrow #gamma", "l");
  l->Draw();
  
  c->Draw();
}

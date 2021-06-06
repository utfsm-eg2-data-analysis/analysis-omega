void MakePlots_Sim(TString targetOption, TString kinvarOption) {
  // (work in progress...)
  
  /*** INPUT OPTIONS ***/

  TCut cutVertex = "Yec > -1.4 && Yec < 1.4";

  TString titleAxis, histProperties;
  if (kinvarOption == "wM") {
    titleAxis = "Reconstructed M(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(150, 0., 2.5.)";
  } else if (kinvarOption == "wD") {
    titleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    histProperties = "(150, 0., 2.5)";
  } else if (kinvarOption == "Q2") {
    titleAxis = "Q^{2} [GeV^{2}]";
    histProperties = "(200, 1., 4.)";  
  } else if (kinvarOption == "Nu") {
    titleAxis = "#nu [GeV]";
    histProperties = "(200, 2.2, 4.2)";
  } else if (kinvarOption == "wZ") {
    titleAxis = "Z_{h}";
    histProperties = "(120, 0., 1.2)";
  } else if (kinvarOption == "wPt2") {
    titleAxis = "p_{T}^{2} [GeV^{2}]";
    histProperties = "(150, 0., 1.5)";
  } else if (kinvarOption == "wPhiPQ") {
    titleAxis = "#phi_{PQ} (degrees)";
    histProperties = "(120, -180, 180.)";
  } else if (kinvarOption == "pi0M") {
    titleAxis = "Reconstructed M(#gamma#gamma) [GeV]";
    histProperties = "(160, 0, 1.6)";
  }
  TString mc_kinvarOption = "mc_" + kinvarOption;
  
  /*** MAIN ***/
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(gDataDir + "/comb_usm-D-*.root/mix");
  
  TH1D *theHist_GEN;
  treeExtracted->Draw(mc_kinvarOption + ">>gsim" + histProperties, gCutGEN, "goff");
  theHist_GEN = (TH1D *)gROOT->FindObject("gsim");  

  // normalization
  // Double_t norm_GEN = theHist_GEN->Integral();
  Double_t norm_GEN = theHist_GEN->GetMaximum();
  theHist_GEN->Scale(1/norm_GEN);
  
  theHist_GEN->SetFillStyle(0);
  theHist_GEN->SetLineColor(kRed);
  theHist_GEN->SetLineWidth(2);
  
  theHist_GEN->GetXaxis()->SetTitle(titleAxis);
  theHist_GEN->GetXaxis()->CenterTitle();
  theHist_GEN->GetYaxis()->SetTitle("Candidates / Normalized");
  theHist_GEN->GetYaxis()->SetMaxDigits(3);
  theHist_GEN->GetYaxis()->CenterTitle();

  TH1D *theHist_REC;
  treeExtracted->Draw(kinvarOption + ">>simrec" + histProperties, gCutDATA, "goff");
  theHist_REC = (TH1D *)gROOT->FindObject("simrec");  

  // normalization
  // Double_t norm_REC = theHist_REC->Integral();
  Double_t norm_REC = theHist_REC->GetMaximum();
  theHist_REC->Scale(1/norm_REC);
  
  theHist_REC->SetFillStyle(0);
  theHist_REC->SetLineColor(kBlack);
  theHist_REC->SetLineWidth(2);
  
  TCanvas *c = new TCanvas("sim-" + targetOption + "_" + kinvarOption, "c"); 
  c->SetGrid();
  gStyle->SetOptStat(0);
  
  theHist_GEN->Draw("HIST");
  theHist_REC->Draw("HIST SAME");

  c->Draw();
}

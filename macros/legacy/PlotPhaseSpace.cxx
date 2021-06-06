void PlotPhaseSpace() {
  // WORK IN PROGRESS
  
  /*** INPUT OPTIONS ***/

  TCut cutVertex = "Yec > -1.4 && Yec < 1.4";
  TString inputFile1 = gDataDir + "/comb_data-C.root";
  TString inputFile2 = gDataDir + "/comb_data-Fe.root";
  TString inputFile3 = gDataDir + "/comb_data-Pb.root";

  TString yOption = "Q2";
  TString yTitleAxis = "Q^{2} [GeV^{2}]";
  TString yHistProperties = "120, 1., 4.";  
  TString xOption = "Xb";
  TString xTitleAxis = "X_{B}";
  TString xHistProperties = "140, 0., 0.7";  
  TString fHistProperties = "(" + xHistProperties + ", " + yHistProperties + ")";

  /*** MAIN ***/
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  TH2D *theHist;
  treeExtracted->Draw(yOption + ":" + xOption + ">>hist" + fHistProperties, gCutDATA && cutVertex, "goff");
  theHist = (TH2D *)gROOT->FindObject("hist");
  
  TCanvas *c = new TCanvas("data-phase-space", "c"); 
  gStyle->SetOptStat(0);

  theHist->GetXaxis()->SetTitle(xTitleAxis);
  theHist->GetXaxis()->CenterTitle();
  theHist->GetYaxis()->SetTitle(yTitleAxis);
  theHist->GetYaxis()->CenterTitle();
  
  theHist->Draw("COLZ");

  c->Draw();  
}

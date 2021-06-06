void MakePlots_2D(TString targetOption, TString yOption, TString xOption) {

  /*** SEBASTIAN STYLE ***/

  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  
  /*** INPUT OPTIONS ***/

  TCut cutVertex;
  TString inputFile1, inputFile2, inputFile3;
  if (targetOption == "D") {
    cutVertex = "TargType == 1 && Yec > -1.4 && Yec < 1.4";
    inputFile1 = gDataDir + "/comb_data-C.root";
    inputFile2 = gDataDir + "/comb_data-Fe.root";
    inputFile3 = gDataDir + "/comb_data-Pb.root";
  } else if (targetOption == "C" || targetOption == "Fe" || targetOption == "Pb") {
    cutVertex = "TargType == 2 && Yec > -1.4 && Yec < 1.4";
    inputFile1 = gDataDir + "/comb_data-" + targetOption +".root";
  }

  TString xTitleAxis, xHistProperties;
  if (xOption == "wM_corr") {
    xTitleAxis = "Reconstructed M(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    xHistProperties = "150, 0., 2.5.";
  } else if (xOption == "wD_corr") {
    xTitleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    xHistProperties = "150, 0., 2.5";
  } else if (xOption == "Q2") {
    xTitleAxis = "Q^{2} [GeV^{2}]";
    xHistProperties = "200, 1., 4.";  
  } else if (xOption == "Nu") {
    xTitleAxis = "#nu [GeV]";
    xHistProperties = "200, 2.2, 4.2";
  } else if (xOption == "wZ_corr") {
    xTitleAxis = "Z_{h}";
    xHistProperties = "120, 0., 1.2";
  } else if (xOption == "wPt2_corr") {
    xTitleAxis      = "p_{T}^{2} [GeV^{2}]";
    xHistProperties = "150, 0., 1.5";
  } else if (xOption == "wPhiPQ_corr") {
    xTitleAxis      = "#phi_{PQ} (deg)";
    xHistProperties = "120, -180, 180.";
  } else if (xOption == "pi0M_corr") {
    xTitleAxis      = "Reconstructed M(#gamma#gamma) [GeV]";
    xHistProperties = "160, 0, 1.6";
  }
  TString yTitleAxis, yHistProperties;
  if (yOption == "wM_corr") {
    yTitleAxis = "Reconstructed M(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    yHistProperties = "150, 0., 2.5";
  } else if (yOption == "wD_corr") {
    yTitleAxis = "Reconstructed #Deltam(#pi^{+}#pi^{-}#gamma#gamma) [GeV]";
    yHistProperties = "150, 0., 2.5";
  } else if (yOption == "Q2") {
    yTitleAxis = "Q^{2} [GeV^{2}]";
    yHistProperties = "200, 1., 4.";  
  } else if (yOption == "Nu") {
    yTitleAxis = "#nu [GeV]";
    yHistProperties = "200, 2.2, 4.2";
  } else if (yOption == "wZ_corr") {
    yTitleAxis = "Z_{h}";
    yHistProperties = "120, 0., 1.2";
  } else if (yOption == "wPt2_corr") {
    yTitleAxis      = "p_{T}^{2} [GeV^{2}]";
    yHistProperties = "150, 0., 1.5";
  } else if (yOption == "wPhiPQ_corr") {
    yTitleAxis      = "#phi_{PQ} (deg)";
    yHistProperties = "120, -180, 180.";
  } else if (yOption == "pi0M_corr") {
    yTitleAxis      = "Reconstructed M(#gamma#gamma) [GeV]";
    yHistProperties = "160, 0, 1.6";
  }
  TString fHistProperties = "(" + xHistProperties + ", " + yHistProperties + ")";

  /*** MAIN ***/
  
  TChain *treeExtracted = new TChain();
  treeExtracted->Add(inputFile1 + "/mix");
  treeExtracted->Add(inputFile2 + "/mix");
  treeExtracted->Add(inputFile3 + "/mix");
  
  TH2D *theHist;
  treeExtracted->Draw(yOption + ":" + xOption + ">>hist" + fHistProperties, gCutDATA && cutVertex, "goff");
  theHist = (TH2D *)gROOT->FindObject("hist");
  
  TCanvas *c = new TCanvas("data-" + targetOption + "_" + yOption + "_vs_" + xOption, "c"); 
  gStyle->SetOptStat(0);
  gStyle->SetNumberContours(NCont); // colors, smoran

  theHist->GetXaxis()->SetTitle(xTitleAxis);
  theHist->GetXaxis()->CenterTitle();
  theHist->GetYaxis()->SetTitle(yTitleAxis);
  theHist->GetYaxis()->CenterTitle();
  theHist->SetContour(99);
  
  theHist->Draw("COLZ");

  c->Draw();
}

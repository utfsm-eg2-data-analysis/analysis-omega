void DrawDiagonalLine(Double_t slope, Double_t constant, Double_t x1, Double_t x2, Color_t cc = kBlack, Style_t ss = kDashed, Int_t ww = 3, TString Name = "") {
  gPad->Update(); // necessary
  TF1 *function = new TF1(Name, Form("%f + %f*x", constant, slope), x1, x2);
  function->SetLineColor(cc); // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  function->SetLineStyle(ss); // kSolid, kDashed, kDotted
  function->SetLineWidth(ww);
  function->Draw("SAME");
}

void DrawVerticalLine(Double_t x, Color_t cc = kBlack, Style_t ss = kDashed) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.16, u, 0.95);
  linex->SetLineWidth(3);
  linex->SetLineColor(cc); // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  linex->SetLineStyle(ss); // kSolid, kDashed, kDotted
  linex->SetNDC(kTRUE);
  linex->Draw();
}

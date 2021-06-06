void DrawVerticalLine(Double_t x, Color_t cc = kBlack, Style_t ss = kDashed, Int_t ww = 3, Int_t OffsetOn = 0, Double_t OffsetY1 = -1, Double_t OffsetY2 = -1) {
  Double_t u;
  gPad->Update(); // necessary
  u = (x - gPad->GetX1())/(gPad->GetX2() - gPad->GetX1());
  // u = (x - x1)/(x2 - x1);
  TLine *linex = new TLine(u, 0.1, u, 0.9);
  linex->SetLineColor(cc); // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  linex->SetLineStyle(ss); // kSolid, kDashed, kDotted
  linex->SetLineWidth(ww);
  if (OffsetOn == 1) {
    linex->SetY1(0.15);
    linex->SetY2(0.95);
  } else if (OffsetOn == 2) {
    linex->SetY1(0.15);
    linex->SetY2(0.85);
  }
  if (OffsetY1 != -1 && OffsetY2 != -1) {
    linex->SetY1(OffsetY1);
    linex->SetY2(OffsetY2);
  }
  linex->SetNDC(kTRUE);
  linex->Draw();
}

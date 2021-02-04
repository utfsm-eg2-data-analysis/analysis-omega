void DrawHorizontalLine(Double_t y, Color_t cc = kBlack, Style_t ss = kDashed) {
  Double_t u;
  gPad->Update(); // necessary
  u = (y - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.16, u, 0.95, u);
  liney->SetLineWidth(3);
  liney->SetLineColor(cc); // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  liney->SetLineStyle(ss); // kSolid, kDashed, kDotted
  liney->SetNDC(kTRUE);
  liney->Draw();
}


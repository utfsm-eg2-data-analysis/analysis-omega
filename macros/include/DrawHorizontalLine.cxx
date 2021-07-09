void DrawHorizontalLine(Double_t y, Color_t cc = kBlack, Style_t ss = kDashed, Int_t ww = 3, Int_t OffsetOn = 0, Double_t OffsetX1 = -1, Double_t OffsetX2 = -1) {
  Double_t u;
  gPad->Update(); // necessary
  u = (y - gPad->GetY1())/(gPad->GetY2() - gPad->GetY1());
  // u = (y - y1)/(y2 - y1);
  TLine *liney = new TLine(0.1, u, 0.9, u);
  liney->SetLineColor(cc); // kBlack, kBlue, kRed, kGreen+2, kOrange+7, kGray+{1,2,3}
  liney->SetLineStyle(ss); // kSolid, kDashed, kDotted
  liney->SetLineWidth(ww);
  if (OffsetOn == 1) {
    liney->SetX1(0.15);
    liney->SetX2(0.95);    
  } else if (OffsetOn == 2) {
    liney->SetX1(0.15);
    liney->SetX2(0.85);    
  }
  if (OffsetX1 != -1 && OffsetX2 != -1) {
    liney->SetX1(OffsetX1);
    liney->SetX2(OffsetX2);
  }
  liney->SetNDC(kTRUE);
  liney->Draw();
}


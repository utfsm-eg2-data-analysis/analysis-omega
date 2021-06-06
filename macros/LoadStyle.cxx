#ifndef MCSTYLE_CXX
#define MCSTYLE_CXX

void LoadStyle() {
  // Manuel Calderon de la Barca {// Add my own options here:
  TStyle *mcStyle = new TStyle("mcStyle", "Manuel's Root Styles");
  mcStyle->SetCanvasDefW(800);
  mcStyle->SetCanvasDefH(600);
  
  // use plain black on white colors
  Int_t icol = 0; // WHITE
  mcStyle->SetFrameBorderMode(icol);
  mcStyle->SetFrameFillColor(icol);
  mcStyle->SetCanvasBorderMode(icol);
  mcStyle->SetCanvasColor(icol);
  mcStyle->SetPadBorderMode(icol);
  mcStyle->SetPadColor(icol);
  mcStyle->SetStatColor(icol);
  //mcStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  mcStyle->SetPaperSize(20, 26);

  // set margin sizes
  mcStyle->SetPadTopMargin(0.05);
  mcStyle->SetPadRightMargin(0.05);
  mcStyle->SetPadBottomMargin(0.15);
  mcStyle->SetPadLeftMargin(0.15);

  // set title offsets (for axis label)
  mcStyle->SetTitleXOffset(1.4);
  mcStyle->SetTitleYOffset(1.4);

  // use large fonts
  // Int_t font=72; // Helvetica italics
  //Int_t font=42; // Helvetica
  //Double_t tsize=0.05;
  Int_t    font = 43; // Helvetica
  Double_t tsize = 22;
  mcStyle->SetTextFont(font);
  mcStyle->SetTextSize(tsize);
  
  mcStyle->SetLabelFont(font, "x");
  mcStyle->SetTitleFont(font, "x");
  mcStyle->SetLabelFont(font, "y");
  mcStyle->SetTitleFont(font, "y");
  mcStyle->SetLabelFont(font, "z");
  mcStyle->SetTitleFont(font, "z");
  
  mcStyle->SetLabelSize(tsize, "x");
  mcStyle->SetTitleSize(tsize, "x");
  mcStyle->SetLabelSize(tsize, "y");
  mcStyle->SetTitleSize(tsize, "y");
  mcStyle->SetLabelSize(tsize, "z");
  mcStyle->SetTitleSize(tsize, "z");

  // use bold lines and markers
  mcStyle->SetMarkerStyle(20);
  mcStyle->SetMarkerSize(1.2);
  // mcStyle->SetHistLineWidth(2.);
  mcStyle->SetHistLineWidth(1.);
  mcStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //mcStyle->SetErrorX(0.001);
  // get rid of error bar caps
  mcStyle->SetEndErrorSize(0);

  // do not display any of the standard histogram decorations
  mcStyle->SetOptTitle(0);
  //mcStyle->SetOptStat(1111);
  mcStyle->SetOptStat(0);
  //mcStyle->SetOptFit(1111);
  mcStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  mcStyle->SetPadTickX(1);
  mcStyle->SetPadTickY(1);

  gROOT->SetStyle("mcStyle");
  gROOT->ForceStyle();
}

#endif

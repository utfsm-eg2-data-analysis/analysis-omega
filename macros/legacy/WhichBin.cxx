// WhichBin

void WhichBin(Double_t Value, TString Variable, Int_t NBins) {

  Double_t LowerLimit, UpperLimit;
  if (Variable == "Q2") {
    LowerLimit = 1.0;
    UpperLimit = 4.0;
  } else if (Variable == "Nu") {
    LowerLimit = 2.2;
    UpperLimit = 4.2;
  } else if (Variable == "Zh") {
    LowerLimit = 0.5;
    UpperLimit = 1.0;
  } else if (Variable == "Pt2") {
    LowerLimit = 0.0;
    UpperLimit = 1.5;    
  }
  
  Double_t BinWidth = (UpperLimit - LowerLimit)/(Double_t)NBins;
  
  Int_t Bin;  
  for (Int_t c = NBins; c >= 0; c--) {
    if (Value > LowerLimit + c*BinWidth) {
      Bin = c;
      break;
    }
  }
  std::cout << "Bin number is " << Bin << "!" << std::endl;
}

void CanvasMakeRooFits(TString targetOption) {

  /*** MAIN ***/

  TString inputDir  = gWorkDir + "/MakeRooFits";
  
  // set i/o and read
  TString inputFile     = inputDir + "/roofits_" + targetOption + "_test.root"; // TEMPORARY
  TFile  *rootInputFile = new TFile(inputFile);

  // define array
  TString kinVar[4] = {"Q", "N", "Z", "P"};

  TCanvas *c = new TCanvas("roofits-canvas", "c", 2000, 2000);
  c->Divide(5, 4, 0.01, 0.01); // ncolumns, nrows, margins

  TString currentPlotName;
  Int_t counter = 0;
  for (Int_t k = 0; k < 4; k++) { // nrows, on kinvars
    for (Int_t i = 0; i < 5; i++) { // ncolumns, on bins
      currentPlotName = "fit_" + targetOption + "_" + kinVar[k] + Form("%d", i);
      RooPlot *thePlot = (RooPlot *) rootInputFile->Get(currentPlotName);
      counter++;
      c->cd(counter);
      thePlot->Draw();
    }
  }

  c->Draw();
}

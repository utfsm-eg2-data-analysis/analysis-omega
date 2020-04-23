#include "analysisConfig.h"

#include "TClasTool.h"
#include "TIdentificator.h"

int main() {

  /*** 1 ***/
  
  std::cout << "PRODIR=" << proDir << std::endl;

  for (Int_t i = 0; i < 6; i++) {
    std::cout << "z" << i << " - " << edgesZ[i] << std::endl;
  }
  std::cout << std::endl;
  
  /*** 2 ***/

  // init ClasTool
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");

  TString currentFile = "/home/borquez/Downloads/recsisC_0028.root";
  input->Add(currentFile);

  Double_t nEntries = (Double_t) input->GetEntries();
  std::cout << "nEntries = " << nEntries << std::endl;

  /*** 3 ***/

  // define TIdentificator and start!
  TIdentificator *t = new TIdentificator(input);
  input->Next();
    
  // loop in evnt
  for (Int_t k = 0; k < nEntries; k++) { // should be nEntries

    Int_t nRows = input->GetNRows("EVNT");
    Int_t nRowsG = input->GetNRows("GSIM");
    std::cout << "(nRows, nRowsG) = (" << nRows << ", " << nRowsG << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "Event " << k << std::endl;

    // reset electron values
    Int_t    eflag = 0;
    
    Int_t    mc_eid = -9999;
    Double_t mc_epx = -9999.;
    Double_t mc_epy = -9999.;
    Double_t mc_epz = -9999.;
    
    TString  eid = "none";
    Double_t epx = -9999.;
    Double_t epy = -9999.;
    Double_t epz = -9999.;
    
    // found electron in gsim!
    if (t->Id(0, 1) == 11) {
      
      mc_eid = t->Id(0,1);
      mc_epx = t->Px(0,1);
      mc_epy = t->Py(0,1);
      mc_epz = t->Pz(0,1);

      // found electron in simrec!
      if ((t->GetCategorization(0, "Sim", true)) == "electron") {	
	eid = t->GetCategorization(0,"Sim", true);
	epx = t->Px(0);
	epy = t->Py(0);
	epz = t->Pz(0);
	eflag = 1;
      }

      // fill electron tree
      std::cout << "0 : (" << mc_eid << ", " << mc_epx << ", " << mc_epy << ", " << mc_epz << ", "
		<< eid << ", " << epx << ", " << epy << ", " << epz << ")" << std::endl;
      
      // loop in the rest of particles
      for (Int_t i = 1; i < input->GetNRows("GSIM"); i++) {

	// reset values
	Int_t    mc_id = -9999;
	Double_t mc_px = -9999.;
	Double_t mc_py = -9999.;
	Double_t mc_pz = -9999.;
	
	TString  id = "none";
	Double_t px = -9999.;
	Double_t py = -9999.;
	Double_t pz = -9999.;

	Int_t gflag = 0;
	Int_t rflag = 0;
	
      	if (t->Id(i,1) == 22 || t->Id(i,1) == -211 || t->Id(i,1) == 211) {
	  mc_id = t->Id(i,1);
	  mc_px = t->Px(i,1);
	  mc_py = t->Py(i,1);
	  mc_pz = t->Pz(i,1);
	  gflag = 1;
	}

	if (eflag && i < input->GetNRows("EVNT")) {
	  TString category = t->GetCategorization(i, "Sim");

	  std::cout << "yey " << k << " " << i << std::endl;
	  
	  if (category == "gamma" || category == "pi-" || category == "high energy pion +" || category == "low energy pion +" || category == "s_electron" || category == "positron") {
	    id = t->GetCategorization(i, "Sim");
	    px = t->Px(i);
	    py = t->Py(i);
	    pz = t->Pz(i);
	    rflag = 1;
	  }
	}
	
	// fill hadron tree
	if (gflag || rflag) {
	  std::cout << i << " : (" << mc_id << ", " << mc_px << ", " << mc_py << ", " << mc_pz << ", "
		    << id << ", " << px << ", " << py << ", " << pz << ")" << std::endl;
	}

      } // end of loop in the rest of particles
      
      std::cout << std::endl;
    } // end of electron at gsim condition
    
    input->Next();
  } // end of loop in event
  
}

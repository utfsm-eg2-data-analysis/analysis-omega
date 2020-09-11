/**************************************/
/* SampFrac_tree.cxx                  */
/*                                    */
/* Andrés Bórquez                     */
/*                                    */
/**************************************/

// stage 1: extract convenient tree from ClasTool-formatted data

#include "TClasTool.h"
#include "TIdentificator.h"

#include "analysisConfig.h"

/*** Global variables ***/

TString outDir = proDir + "/out/SampFrac";
TString inputFile = proDir + "/bin/clas_42011_*.pass2.root";

int main(int argc, char **argv) {

  // just in case
  system("mkdir -p " + outDir);

  TString treeFile = outDir + "/hola.root";
  
  TClasTool *input = new TClasTool();
  input->InitDSTReader("ROOTDSTR");  
  input->Add(inputFile);

  TString varListElectrons = "Sector:vzec:P:Etot:Ein:Eout";
  Float_t varElectrons[6];

  // setup output
  TFile *rootFile = new TFile(treeFile, "RECREATE", "Electrons");
  TNtuple *tElectrons = new TNtuple("ntuple_e", "All electrons", varListElectrons);
  
  TIdentificator *t = new TIdentificator(input);

  Int_t nEvents = (Int_t) input->GetEntries();

  // jumps to first readable event, mandatory!
  input->Next();
  
  // loop around events
  for (Int_t k = 0; k < nEvents; k++) {

    if (input->GetNRows("EVNT") > 0) {
    
      // update electrons' UVW vector
      TVector3 *ECxyz_e = new TVector3(t->XEC(0), t->YEC(0), t->ZEC(0));
      TVector3 *ECuvw_e = t->XYZToUVW(ECxyz_e);
      TVector3 *vert;
    
      // electron condition without any sampling fraction cut, assuming electron is in row 0  
      if (t->Status(0) > 0 &&
	  t->DCStatus(0) > 0 &&
	  t->SCStatus(0) == 33 &&
	  t->Charge(0) == -1 &&
	  t->Nphe(0) > (t->Sector(0)==0 || t->Sector(0)==1)*25 + (t->Sector(0)==2)*26 + (t->Sector(0)==3)*21 + (t->Sector(0)==4 || t->Sector(0)==5)*28 &&
	  t->Momentum(0) > 0.64 &&
	  t->Ein(0) > 0.06 &&
	  t->Eout(0) > 0 &&
	  (t->TimeEC(0) - t->TimeSC(0) - 0.7) > -5*0.35 &&
	  (t->TimeEC(0) - t->TimeSC(0) - 0.7) < 5*0.35 &&
	  ECuvw_e->X() > 40 &&
	  ECuvw_e->X() < 400 &&
	  ECuvw_e->Y() >= 0 &&
	  ECuvw_e->Y() < 360 &&
	  ECuvw_e->Z() >= 0 &&
	  ECuvw_e->Z() < 390 &&
	  t->FidCheckCut(0)) {
      
	varElectrons[0] = t->Sector(0,0);
	vert = t->GetCorrectedVert(0);
	varElectrons[1] = vert->Z();
	varElectrons[2] = t->Momentum(0,0);
	varElectrons[3] = t->Etot(0);
	varElectrons[4] = t->Ein(0);
	varElectrons[5] = t->Eout(0);
      
	tElectrons->Fill(varElectrons);
      }
    }

    // next event!!
    input->Next();
  }

  // write and close output file
  rootFile->Write();
  rootFile->Close();

  std::cout << "Created file: " << treeFile << std::endl;
    
  return 0;
}

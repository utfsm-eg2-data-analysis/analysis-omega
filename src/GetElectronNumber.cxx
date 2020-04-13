/**************************************/
/* GetElectronNumber.cxx              */
/*                                    */
/* Created by Andrés Bórquez          */
/*                                    */
/**************************************/

// Only works in UTFSM cluster, because there is the data

#include "analysisConfig.h"

/*** Global variables ***/

TCut cutTargType;

Int_t runNumbersC = 118; // from 119; because I removed 42040
Int_t runNumbersFe = 263; // from 265; because I removed 41315 and 41394
Int_t runNumbersPb = 169; // from 171; because I removed 41834 and 41979
Int_t runNumbersTotal = runNumbersC + runNumbersFe + runNumbersPb;

void readFiles(TString targetOption);

int main() {

  readFiles("D");
  readFiles("C");
  readFiles("Fe");
  readFiles("Pb");
}

void readFiles(TString targetOption) {

  TString textFile;
  TString rootFolder1 = proDir + "/out/prunedData/C";
  TString rootFolder2 = proDir + "/out/prunedData/Fe";
  TString rootFolder3 = proDir + "/out/prunedData/Pb";
  TString currentRootFolder;
  
  /*** Assigning options ***/
  
  if (targetOption == "D") {
    textFile = proDir + "/ext/RunNumbers/D-onlyD2rn.txt";
    cutTargType = "TargType == 1";
  } else if (targetOption == "C") {
    textFile = proDir + "/ext/RunNumbers/C-thickD2rn.txt";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Fe") {
    textFile = proDir + "/ext/RunNumbers/Fe-thickD2rn.txt";
    cutTargType = "TargType == 2";
  } else if (targetOption == "Pb") {
    textFile = proDir + "/ext/RunNumbers/Pb-thinD2rn.txt";
    cutTargType = "TargType == 2";
  }

  std::ifstream inFile(textFile);
  
  TString rootFile;
  TString auxLine;
  TString currentRN;
  
  Int_t eNumber = 0;
  Int_t i = 0; // counter
  
  while (inFile >> auxLine) {
    i++;
    currentRN = auxLine;

    /*** Reading root files ***/

    if (targetOption == "D") {
      if (i < (runNumbersC+1)) currentRootFolder = rootFolder1;
      else if (i > (runNumbersC) && i < (runNumbersC+runNumbersFe+1)) currentRootFolder = rootFolder2;
      else if (i > (runNumbersC+runNumbersFe)) currentRootFolder = rootFolder3;
    } else if (targetOption == "C") {
      currentRootFolder = rootFolder1;
    } else if (targetOption == "Fe") {
      currentRootFolder = rootFolder2;
    } else if (targetOption == "Pb") {
      currentRootFolder = rootFolder3;
    }
    
    std::cout << "currentRN=" << currentRN << " - " << "i=" << i << std::endl;
    
    /*** Summing Electron Numbers ***/
    
    rootFile = "prune_data_" + currentRN + ".root";    
    TFile *File = new TFile(currentRootFolder + rootFile);
    TTree *treeExtracted = (TTree *)File->Get("e_rec");
    eNumber += treeExtracted->Draw("Nu>>data(100, -10., 10.)", cutDIS && cutTargType, "goff"); // lazyness

    File->Close();
  }
  
  inFile.close();
  
  /*** Printing Final Result ***/

  std::cout << "eN (" << targetOption  << ") = " << eNumber << std::endl; 
}

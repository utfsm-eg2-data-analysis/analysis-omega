// @(#)PartSieve/TPartSieve:$Name:  $:$Id: TPartSieve.cc,v 1.8 2007/03/01 22:27:00 holtrop Exp $
// Author: Maurik Holtrop <http://www.physics.unh.edu/~maurik>

/****************************************************************************
 * Copyright (C) CopyLeft  This code is freely available to all.            *
 *                                                                          *
 * Documentation  : TPartSieve.html                                         *
 *                  (available also at:                                     *
 *                   http://www.physics.unh.edu/maurik/ClasTool)            *
 * Created on     :  04/2/2002 (UNH)                                        *
 * Initial Authors:  Maurik Holtrop (UNH)                                   *
 ***************************************************************************/

// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>, Will Morrison (UNH)

//____________________ 
//Begin_Html <!--
/* -->
</pre><H1> TPartSieve </H1>
<H2>Particle ID cleanup and improvement for ClasTool</H2>
<p>Created at UNH by Will Morrison and <b><i><a href="http://www.physics.unh.edu/~maurik">Maurik Holtrop</a></b></i></p>
<p>TPartSieve is part of the CLASTOOL analysis framework. 
It is designed to facilitate physics analysis by providing a structure
that can be customized to a specific analysis with custom cuts, etc., without changing the details of how the
functions are used in an analysis program. These customizations are easy to make, and TPartSieve is designed for
easy use and easy comprehension.</p>

<p>The Sieve can be run over an entire event in one of three modes, either Sort, Confidence or Refine.
Sort mode is useful for preliminary looks at data. It is also useful in code that already has Sieve mechanisms 
in place but no longer needs to use the Confidence or Refinement. This mode makes looking at specific particles 
very easy; one can for example loop through all pions in an event using only two lines of code.</p>

<p>Confidence mode assigns a confidence level to each particles ID, and throws away particles below an ajustable
confidence level. The confidence level is determined using a set of particle specific functions. See the 
function GetConfidence() for an explanation of the confidence level setting scheme.</p>

<p>Refine mode looks through particles and find ones with less than adequate confidence. It then 
determines what the id should be using a set of particle specific functions. These are NOT CURRENTLY
IMPLEMENTED.</p>

<H3>Benchmarking</H3>
<p>Running over one run and using this class's sort function and filling a histogram with the number of each 
particle took 34.5 seconds. A comparable program using only TClasTool took 31.6 seconds.
<p>
Additional information about this package, including an overview, can be found at the
<a href="http://www.physics.unh.edu/~maurik/ClasTool">ClasTool Documentation</a> web pages.
<pre> 
<!-- */ 
// --> End_Html   
///////////////////////////////////////////////////////////////////////////////////

#include "TClasTool.h"
#include "TClasTool_Const.h"
#include "TPartSieve.h"
#define MAXPARTS 10

ClassImp(TPartSieve) // Package to sort particles and fix PID.

//=======================================================================
TPartSieve::TPartSieve(){
  //
  // Class default constructor.
  //
  cout << "*** Warning *** TPartSieve instantiated but not initialized. ***\n";
}
//=======================================================================
TPartSieve::TPartSieve(TClasTool *clastool, Int_t runnum){
  //
  // Class Constructor, setting up PartSieve properly with a TClasTool
  //
  // The runnum argument may be used later when we couple to a database 
  // to get constants for cuts for a specific run. It is not used now.

  fCT = clastool;
  fDebug_Mode = 0;
  for(Int_t i=0;i<kNParticleTypes;i++)fNPart[i]=0;
  fSortFlag = 0;
  SortOn();
  SetConfidenceCut(.5);

  // Default values for tunable cuts.
  // These were used in EG2 analysis and probably need to be adjusted
  // for different analysis.
  
  fEC_U_Cut=40.;
  fEC_U_Cut_width=5.;
  fEC_V_Cut=360.;
  fEC_V_Cut_width=5.;
  fEC_W_Cut=390.;
  fEC_W_Cut_width=5.;

  fEC_Eio_slope=1.0;
  fEC_Eio_off=0.156;
  fEC_Ein_cut = 0.06;
  fEC_Eout_cut = 0.06;

  fCC_Phe_cut = 25.0;
  fCC_Phe_width= 3.;

  fConf_Pim_DT_min= -0.5;
  fConf_Pim_DT_max=  0.5;
  fConf_Pip_DT_min= -0.5;
  fConf_Pip_DT_max=  0.5;

  fConf_Km_DT_min= -0.25;
  fConf_Km_DT_max=  0.25;
  fConf_Kp_DT_min= -0.25;
  fConf_Kp_DT_max=  0.25;

  fConf_Prot_DT_min= -0.5;
  fConf_Prot_DT_max=  1.0;

  fConf_Deut_DT_min= -1.0;
  fConf_Deut_DT_max=  1.0;

  fConf_He3_DT_min= -1.5;
  fConf_He3_DT_max=  1.5;

  fConf_He4_DT_min= -1.5;
  fConf_He4_DT_max=  1.5;

  fConf_Neut_DT_min= -0.8;
  fConf_Neut_DT_max=  1.0;

  fConf_El_DC_chi2=4.;
  fConf_Prot_DC_chi2=5.;
  fConf_Pim_DC_chi2=5.;
  fConf_Pip_DC_chi2=5.;
  fConf_Km_DC_chi2=5.;
  fConf_Kp_DC_chi2=5.;

  fConf_Deut_DC_chi2=5.;
  fConf_He3_DC_chi2=5.;
  fConf_He4_DC_chi2=5.;

  fConf_El_DC_chi2_width=0.;
  fConf_Prot_DC_chi2_width=0.;
  fConf_Pim_DC_chi2_width=0.;
  fConf_Pip_DC_chi2_width=0.;
  fConf_Km_DC_chi2_width=0.;
  fConf_Kp_DC_chi2_width=0.;

  fConf_Deut_DC_chi2_width=0.;
  fConf_He3_DC_chi2_width=0.;
  fConf_He4_DC_chi2_width=0.;
}

//=======================================================================
TPartSieve::~TPartSieve()
{
  // Class default destructor.

}
//=======================================================================
void TPartSieve::SortOn()
{
  //Calling this function turns on a flag that causes SieveEvent() to
  //count and store the number of each particle and store each particle's
  //index into the EVNT bank.
  //
  //This is useful for getting how many of a certain particle are in 
  //an event. It is also useful because it is easy to tell it to get,
  //for example, the second kaon+, using GetEVNT. This should also be used 
  //in combination with the other two modes, in order for one to look at the
  //particles he has just analyzed.

  //fSortFlag is set using bitwise operations. The first bit corresponds
  //to sorting, the second to confidence, the third to id refinement.

  fSortFlag |= kSortFlag_SortOn;
}
//=======================================================================
void TPartSieve::ConfidenceOn()
{
  //Calling this function turns on a flag that causes SieveEvent() to
  //calculate and store a confidence level in each particle's id.
  //
  //Use this to measure the confidence level in each particle's RECSIS 
  //id. For example if a particle's RECSIS id is proton and this function
  //assigns a confidence of .65, there is a 65% chance that it is actually
  //a proton.

  fSortFlag |= kSortFlag_ConfidenceOn;
}
//=======================================================================
void TPartSieve::RefineIdOn()
{
  //Calling this function turns on a flag that causes SieveEvent() to
  //recalculate the id of each particle in the event.
  //
  //This mode will actually change the particle id's that were assigned 
  //in RECSIS. Make sure you understand what the refinements are actually
  //doing before you use this mode!

  fSortFlag |= kSortFlag_RefineIdOn;
}
//=======================================================================
void TPartSieve::SortOff()
{
  //Turns of particle sorting capability

 fSortFlag &= ~(kSortFlag_SortOn);
}
//=======================================================================
void TPartSieve::ConfidenceOff()
{
  //Turn off confidence setting capability

  fSortFlag &= ~(kSortFlag_ConfidenceOn);
}
//=======================================================================
void TPartSieve::RefineIdOff()
{
  //Turn off Id refining capability

  fSortFlag &= ~(kSortFlag_RefineIdOn);
}
//=======================================================================
void TPartSieve::SetDebugMode(Int_t Mode)
{
  //Set verbosity of code
  //Debug Mode = -1 : Absolutely no output
  //Debug Mode =  0 : Warning Messages only.
  //Debug Mode =  1 : Helpful non-warning messages and warning for too many particles in event.

  if(Mode > 1 || Mode < -1){
    cout << "Debug Mode = -1 : Absolutely no output." << endl;
    cout << "Debug Mode =  0 : Warning Messages only." << endl;
    cout << "Debug Mode =  1 : Helpful non-warning messages and warning";
    cout << "for to many particles in event." << endl;
    cout << endl << "Debug Mode set to zero." << endl << endl;
    Mode=0;
  }

  fDebug_Mode = Mode;
}
//=======================================================================
Int_t TPartSieve::SieveEvent() 
{
  // This function looks over each particle in the event. It can do the 
  // following in any combination:
  // 1. Count and save the number of each type of particle in the event,
  // as well as the EVNT index of each particle. These particles can then be
  // accessed by telling the Sieve to get the 0th, 1st, 2nd etc. of such 
  // and such a particle.
  // 2. Calculate the confidence that the RECSIS particle id is correct, 
  // however this is only useful if you then save this info using option 1.
  // 3. Recalculate the particle id and save this new id.



  for(Int_t i=0;i<kNParticleTypes;i++)fNPart[i]=0; //setting counters = 0

  for(Int_t j=0;j<fCT->GetNPart();j++){
    Float_t confidence=2.;//With confidence this high user cannot accidentally
    //eliminate particles with SetConfidenceCut(Float) when in SortMode
    
    //fSortFlag is a 3 bit number. See SortOn() for explanation.
    //Get confidence first in case the other two need it.
    if((fSortFlag&kSortFlag_ConfidenceOn)||(fSortFlag&kSortFlag_RefineIdOn)){ //confidence section
      confidence = GetPartConf(j);
    }
    //    if(fSortFlag&kSortFlag_RefineIdOn){ //Id refinement section
    // if(confidence<fRefConfidenceCut){
    // RefinePartId(j);
    //   }
    // }
    if(fSortFlag&kSortFlag_SortOn){ //count particles, store EVNT id's
      if(confidence>=fConfidenceCut && kSortFlag_ConfidenceOn){ //Store only particles passing confidence cut
	IndexPart(j,confidence);
      }
    }
  }
  return fCT->GetNPart();
}
//=======================================================================
void TPartSieve::IndexPart(Int_t Ind, Float_t confidence)
{
  //THIS FUNCTION HAS BEEN WRITTEN FOR INTERNAL USE ONLY AND IS NOT ACCESSIBLE TO THE USER.
  //
  //This will properly save a particle's index into the EVNT bank. It will
  //also incremement its counter. This routine saves the particle confidence 
  //if in the SetConfidence mode.



  fIndex[IDtoInd(fCT->GetPartID(Ind))][fNPart[IDtoInd(fCT->GetPartID(Ind))]]=Ind;

  if((fSortFlag/10)%2!=0){    
    fConfidence[IDtoInd(fCT->GetPartID(Ind))][fNPart[IDtoInd(fCT->GetPartID(Ind))]]=confidence;
  }

  //increment NPart counter after checking to prevent overflow
  if((fNPart[IDtoInd(fCT->GetPartID(Ind))]) < (MAXPARTS-1)){
    fNPart[IDtoInd(fCT->GetPartID(Ind))]++;
  }
  else if ((fNPart[IDtoInd(fCT->GetPartID(Ind))]) >= (MAXPARTS-1)){ //If overflow
    fNPart[IDtoInd(fCT->GetPartID(Ind))]=MAXPARTS-1;//decrease counter. Next part will
    if(fDebug_Mode>0){                             //overwrite this one.

      cout << "There are " << fNPart[IDtoInd(fCT->GetPartID(Ind))] << " particles with PID ";
      cout << fCT->GetPartID(Ind) << " in event number " << fCT->GetEventNumber()<< endl;
      cout << "There are " << fCT->GetNPart() << "parts in the event" <<endl <<endl;
      cout << "The maximum number of particles being stored is " << MAXPARTS << endl;
    }
  }
}

//========================================================================
Float_t TPartSieve::GetPartConf(Int_t Ind)
{
  // This function returns the confidence level that the particle with EVNT 
  // index Ind's RECSIS id is correct. For example if a particle's RECSIS id 
  // is proton and this function /returns a confidence of .65, there is a 65%
  // chance that it is actually a proton.
  //
  // The confidence level is set using a two-tiered system. The first tier consists
  // of the Conf### functions, where ### is the particle name.
  // In these functions the cuts that are to be used on the specific particle
  // are selected. These functions also may contain code for a cut that
  // is specific to a certain particle, however this should be very limited.
  //
  // The second tier of the system is the Cut functions themselves. The 
  // general idea for these functions is that there is an ideal value of
  // quantity that a particle may have. The experimental value will differ
  // from this ideal value. The user inputs the maximum difference between
  // ideal and experimental and the weight of this cut into the functions 
  // as arguements. These functions are meant to be general and may require
  // additional arguements such as the mass of the particle in question.

  // The Cut functions all return a Float_t value. The first tier Conf 
  // functions are meant to call the Cut functions in such a way that
  // each returned value is subtracted from a total confidence. The 
  // total confidence is then returned to this function.


  Float_t confidence=1.;;
     //
  switch (fCT->GetPartID(Ind)){
  case kUnknown_Id:
    //This is obviously different from the other cases because id 
    //is unknown. Since many of these are electrons test if it 
    //was the particle in slot 0, and see if this is an electron.
    if(Ind==0 && fSortFlag&kSortFlag_RefineIdOn){ 
      confidence=ConfEl(Ind);
      if(confidence>fRefConfidenceCut){
	TEVNTClass *evnt=fCT->GetEVNT(Ind);
	evnt->Id=kElectron_Id;           // Change the actual ID. Event will
      }                                  // sorted under new ID.
    }else{
      confidence = ConfUnknown(Ind);
    }
    break;
  case kPion_Plus_Id:
    confidence = ConfPip(Ind);
    break;
  case kProton_Id:
    confidence = ConfProt(Ind);
    break;
  case kElectron_Id:
    confidence = ConfEl(Ind);
    break;
  case kPhoton_Id:
    confidence = ConfPhot(Ind);
    break;
  case kPion_Minus_Id:
    confidence = ConfPim(Ind);
    break;
  case kNeutron_Id:
    confidence = ConfNeut(Ind);
    break;
  case kKaon_Plus_Id:
    confidence = ConfKp(Ind);
    break;
  case kDeuteron_Id:
    confidence = ConfDeut(Ind);
    break;
  case kKaon_Minus_Id:
    confidence = ConfKm(Ind);
    break;
  case kHe4_Id:
    confidence = ConfHe3(Ind);
    break;
  case kHe3_Id:
    confidence = ConfHe4(Ind);
    break;
  case kPositron_Id:
    confidence = ConfPos(Ind);
    break;
  default:
    if(fDebug_Mode>-1){
      cout << "INVALID PARTICE ID: " << fCT->GetPartID(Ind) << " IN TCLASTOOL." << endl;
    }
    confidence = 0;
    break;
  }
  return confidence;
}
//=======================================================================
void TPartSieve::RefinePartId(Int_t Ind)
{
  //
  // THIS IS CURRENTLY TOTALLY NON FUNCTIONAL. 
  // 
  // The thought behind it may even be flawed....



  
  //This is the most powerful tool in the Sieve. It takes an index into the 
  //EVNT Bank. It recalculates the ID of this particle using a function 
  //specific to the RECSIS id. This tool permanently changes the id so make
  //sure you know how it works.


  Int_t ID; // holds ID

  switch (fCT->GetPartID(Ind)){
  case kUnknown_Id:
    ID = RefineIdUnknown(Ind);
    ChangeID(Ind,ID);
    break;
  case kPion_Plus_Id:
    ID = RefineIdPip(Ind);
    ChangeID(Ind,ID);
    break;
  case kProton_Id:
    ID = RefineIdProt(Ind);
    ChangeID(Ind,ID);
    break;
  case kElectron_Id:
    ID = RefineIdEl(Ind);
    ChangeID(Ind,ID);
    break;
  case kPhoton_Id:
    ID = RefineIdPhot(Ind);
    ChangeID(Ind,ID);
    break;
  case kPion_Minus_Id:
    ID = RefineIdPim(Ind);
    ChangeID(Ind,ID);
    break;
  case kNeutron_Id:
    ID = RefineIdNeut(Ind);
    ChangeID(Ind,ID);
    break;
  case kKaon_Plus_Id:
    ID = RefineIdKp(Ind);
    ChangeID(Ind,ID);
    break;
  case kDeuteron_Id:
    ID = RefineIdDeut(Ind);
    ChangeID(Ind,ID);
    break;
  case kKaon_Minus_Id:
    ID = RefineIdKm(Ind);
    ChangeID(Ind,ID);
    break;
  case kHe4_Id:
    ID = RefineIdHe3(Ind);
    ChangeID(Ind,ID);
    break;
  case kHe3_Id:
    ID = RefineIdHe4(Ind);
    ChangeID(Ind,ID);
    break;
  case kPositron_Id:
    ID = RefineIdPos(Ind);
    ChangeID(Ind,ID);
    break;
  default:
    if(fDebug_Mode>-1){
      cout << "INVALID PARTICE ID: " << fCT->GetPartID(Ind) << endl;
    }
    break;
  }
}

//=================================================================================
Int_t TPartSieve::GetNPid(Int_t PartId)
{
  //Get the number of particles with PartId in last sorted event.
  //Returns negative on error.
  //
  //See GetNIdx(Int_t idx) (inlined function) for doing the same from an index.
  if(IDtoInd(PartId)>=0) return(fNPart[IDtoIndQuick()]);
  else{
    if(fDebug_Mode>-1){
      cout << PartId << " is not a valid Id number. Use pid from RECSIS." << endl;
    }
    return -1;
  }
}

//=================================================================================

Int_t TPartSieve::GetIndexPid(Int_t PartId, Int_t num)
{
  //Get the index into the EVNT bank for the numth PartId. Indexes start at 0.
  //Returns negative on error.

  if(num>=0){
    if(num<fNPart[IDtoInd(PartId)]){
      return fIndex[IDtoIndQuick()][num];
    } else{
      if(fDebug_Mode>-1){
	cout << "Index exceeds number of particles with pid number "<< PartId << endl;
      }
      return -2; 
    }
  }else{
    if(fDebug_Mode>-1){
      cout << "Index must be non-negative. Numbering starts at 0." << endl;
    }
    return -1;
  }
}

//=================================================================================

Int_t TPartSieve::GetIndexIdx(Int_t idx, Int_t num)
{
  //Get the index into the EVNT bank for the numth Idx. Indexes start at 0.
  //Returns negative on error.

  if(num>=0){
    if(num<fNPart[idx]){
      return fIndex[idx][num];
    } else{
      if(fDebug_Mode>-1){
	cout << "Index exceeds number of particles with index "<< idx << endl;
      }
      return -2; 
    }
  }else{
    if(fDebug_Mode>-1){
      cout << "Index must be non-negative. Numbering starts at 0." << endl;
    }
    return -1;
  }
}

//==================================================================================

TEVNTClass* TPartSieve::GetEVNTIdx(Int_t idx, Int_t num)
{
  //Returns a pointer to the TEVNTClass for the numth INDEX, starting at index 0.
  //Returns NULL on error.

  Int_t index = GetIndexIdx(idx,num);
  if(index>=0){
    return (TEVNTClass *)fCT->GetBankRow("EVNT",index);
  }else{
    return NULL;
  }

}

//=====================================================================================
TEVNTClass* TPartSieve::GetEVNTPid(Int_t PartId, Int_t num)
{
  //Returns a pointer to the TEVNTClass for the numth PartID, starting at index 0.
  //Returns NULL on error.

  Int_t index = GetIndexPid(PartId,num);
  if(index>=0){
    return (TEVNTClass *)fCT->GetBankRow("EVNT",index);
  }else{
    return NULL;
  }

}

//=====================================================================================
void TPartSieve::IndexConf(Float_t conf,Int_t PartId,Int_t num)
{
  //If you wish to save a particle confidence you have got independently of SieveEvent,
  //this will save it in the numth slot of PartId

  if(IDtoInd(PartId)>=0){
    if(num<MAXPARTS) fConfidence[IDtoInd(PartId)][num]=conf;
    else cout <<"Particle index " <<num<<" exceeds array dimensions" << endl;
  }
}

//=====================================================================================
void TPartSieve::Print()
{
  //Prints the number of each type of particle in the event and the SortFlag value.
  //You must call SieveEvent() first to see anything meaningful.
  cout << "N Electron:  " << fNPart[kElectron] << endl;
  cout << "N Positron:  " << fNPart[kPositron] << endl;
  cout << "N Photon:    " << fNPart[kPhoton] << endl;
  cout << "N Pion_Plus: " << fNPart[kPion_Plus] << endl;
  cout << "N Pion_Minus:" << fNPart[kPion_Minus] <<endl;
  cout << "N Kaon_Plus: " << fNPart[kKaon_Plus] << endl;
  cout << "N Kaon_Minus:" << fNPart[kKaon_Minus] << endl;
  cout << "N Proton:    " << fNPart[kProton] << endl;
  cout << "N Neutron:   " << fNPart[kNeutron] << endl;
  cout << "N Deuteron:  " << fNPart[kDeuteron] << endl;
  cout << "N He3:       " << fNPart[kHe3] << endl;
  cout << "N He4:       " << fNPart[kHe4] << endl;
  cout << "N Unknown:   " << fNPart[kUnknown] << endl;
  cout << "fSortFlag: " << fSortFlag << endl << endl;

}
//====================================================================================
Float_t TPartSieve::GetConfFast(Int_t PartId, Int_t num)
{
  //Returns the confidence from from the table. This table is constructed if the 
  //routine is run with ConfidenceOn(). Returns negative on error.

  if(num>=0){
    if(fSortFlag%10!=0){
      if(num<fNPart[IDtoInd(PartId)]){
	return fConfidence[IDtoIndQuick()][num];
      } else{
	if(fDebug_Mode>-1){
	  cout << "Index exceeds number of particles with pid number " << PartId << endl;
	}
	return -2; 
	
      }
    }else{
      if(fDebug_Mode>-1){
	cout << "Must call ConfidenceOn() to use GetConfFast()." << endl;
      }
      return -1;
    }
  } else{
    if(fDebug_Mode>-1){
      cout << "Index must be non-negative. Numbering starts at 0." << endl;
    }
    return -1;
  }
}

//==============================================================================
Int_t TPartSieve::IndtoID(Int_t Ind)
{ 
  //This transforms a particle index to the particle id#.
  //This is a passthrough call to TClasTool::GetPidFromType.
  //
  return(ClasTool::GetPidFromType(Ind));
}

  /*  switch(Ind) {
  case kElectron:
    return kElectron_Id;
  case kPion_Plus:
    return kPion_Plus_Id;
  case kPion_Minus:
    return kPion_Minus_Id;
  case kKaon_Plus:
    return kKaon_Plus_Id;
  case kKaon_Minus:
    return kKaon_Minus_Id;
  case kProton:
    return kProton_Id;
  case kPhoton:
    return kPhoton_Id;
  case kNeutron:
    return kNeutron_Id;
  case kDeuteron:
    return kDeuteron_Id;
  case kHe4:
    return kHe4_Id;
  case kHe3:
    return kHe3_Id;
  case kPositron:
    return kPositron_Id;
  default:
    if(fDebug_Mode>-1){
      cout << "INVALID Particle Index: " << Ind << endl << endl;
    }
    return -1;
    } 
*/

//}
//Could be made faster using an array in global space

//=========================================================================
//=========================================================================
Float_t TPartSieve::ConfUnknown(Int_t Ind)
{
  //The Conf functions select the cuts that are relevent to their particle.
  //There is a seperate function for each particle because it keeps the 
  //code easy to read and straightforward. It is also the job of these 
  //functions to select the weight of each cut and how much range the cut 
  //should have.
  //
  //Calculate the confidence that particle with EVNT index Ind is an electron.

  Float_t Confidence = 1; //            ConfEl(Ind);

  return Confidence;
}
//=========================================================================
Float_t TPartSieve::ConfPip(Int_t Ind)
{
  // Calculate the confidence that particle with EVNT index Ind is a Pi+.
  // Currently this is a hard cut on DeltaT, between 
  // fConf_Pim_DT_min and fConf_Pim_DT_max
  //
  Float_t dcqual=Get_DC_Qual(Ind,fConf_Pim_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_Pip_DT_min &&  deltat < fConf_Pip_DT_max){
    return dcqual;
  }else{
    return 0.;
  }
  
}

//=========================================================================
Float_t TPartSieve::ConfPim(Int_t Ind)
{
  // Calculate the confidence that particle with EVNT index Ind is a Pi-.
  // Currently this is a hard cut on DeltaT, between 
  // fConf_Pip_DT_min and fConf_Pip_DT_max
  //
  Float_t dcqual=Get_DC_Qual(Ind,fConf_Pim_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_Pim_DT_min &&  deltat < fConf_Pim_DT_max){
    return dcqual;
  }else{
    return 0.;
  }
}

//=========================================================================
Float_t TPartSieve::ConfProt(Int_t Ind)
{
  //Calculate the confidence that particle with EVNT index Ind is a proton.
  // Currently this is a hard cut on DeltaT, between 
  // fConf_Prot_DT_min and fConf_Prot_DT_max
  //
  Float_t dcqual=Get_DC_Qual(Ind,fConf_Prot_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_Prot_DT_min &&  deltat < fConf_Prot_DT_max){
    return dcqual;
  }else{
    return 0.;
  }
}
//=========================================================================
Float_t TPartSieve::ConfEl(Int_t Ind,Float_t WidthMultiply)
{
  //Calculate the confidence that particle with EVNT index Ind is an electron
  //

  Float_t Confidence=1.;

  TEVNTClass *evnt = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);

  Confidence *= Get_DC_Qual(Ind,fConf_El_DC_chi2);  

  Confidence *= ECUVWCut(evnt,WidthMultiply);
  Confidence *= EC_Eio_Cut(evnt,WidthMultiply);
  Confidence *= CC_Phe_Cut(evnt,WidthMultiply);

  return Confidence;
}

//=========================================================================
Float_t TPartSieve::ConfPos(Int_t Ind)
{
  //Calculate the confidence that particle with EVNT index Ind is a positron.
  //This calls the routine for the electron: ConfEl(Ind,0.)
  
  return ConfEl(Ind,0.);
}

//=========================================================================
Float_t TPartSieve::ConfPhot(Int_t Ind)
{
  //Calculate the confidence that particle with EVNT index Ind is a photon.

  Float_t Confidence = 1.;

  return Confidence;
}
//=========================================================================
Float_t TPartSieve::ConfNeut(Int_t Ind)
{
  //Calculate the confidence that particle with EVNT index Ind is a neutron.

  TEVNTClass *evnt = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  if(evnt->GetECidx()>=0 && evnt->GetDCStat()<=0 ){
    TECPBClass *ec=(TECPBClass *)fCT->GetBankRow("ECPB",evnt->GetECidx());
    Float_t p=evnt->GetMomentum();
    Int_t indx=IDtoInd(evnt->GetId());
    Float_t deltat=GetDeltaT_EC(ec,p,indx);
    
    if(  deltat > fConf_Neut_DT_min &&  deltat < fConf_Neut_DT_max){
      return 1.;
    }else{
      return 0.;
    }
  }else{
    return 0.;
  }
}
//=========================================================================
Float_t TPartSieve::ConfKp(Int_t Ind)
{
  // Calculate the confidence that particle with EVNT index Ind is a K+.
  // Currently this is a hard cut on DeltaT, between 
  // fConf_Pip_DT_min and fConf_Pip_DT_max
  //

  // Check to make sure the DC is adequate.
  Float_t dcqual=Get_DC_Qual(Ind,fConf_Kp_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_Kp_DT_min &&  deltat < fConf_Kp_DT_max){
    return dcqual;
  }else{
    return 0.;
  }
}
//=========================================================================
Float_t TPartSieve::ConfKm(Int_t Ind)
{
  // Calculate the confidence that particle with EVNT index Ind is a K-.
  // Currently this is a hard cut on DeltaT, between 
  // fConf_Pip_DT_min and fConf_Pip_DT_max
  //
  Float_t dcqual=Get_DC_Qual(Ind,fConf_Km_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_Km_DT_min &&  deltat < fConf_Km_DT_max){
    return dcqual;
  }else{
    return 0.;
  }
}
//=========================================================================
Float_t TPartSieve::ConfDeut(Int_t Ind)
{//not yet implemented
  //Calculate the confidence that particle with EVNT index Ind is a deuteron.

  Float_t dcqual=Get_DC_Qual(Ind,fConf_Deut_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_Deut_DT_min &&  deltat < fConf_Deut_DT_max){
    return dcqual;
  }else{
    return 0.;
  }
}
//=========================================================================
Float_t TPartSieve::ConfHe3(Int_t Ind)
{//not yet implemented
  //Calculate the confidence that particle with EVNT index Ind is a Helium 3.

  Float_t dcqual=Get_DC_Qual(Ind,fConf_He3_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_He3_DT_min &&  deltat < fConf_He3_DT_max){
    return dcqual;
  }else{
    return 0.;
  }

}
//=========================================================================
Float_t TPartSieve::ConfHe4(Int_t Ind)
{//not yet implemented
  //Calculate the confidence that particle with EVNT index Ind is a Helium 4.

  Float_t dcqual=Get_DC_Qual(Ind,fConf_He4_DC_chi2);

  Float_t deltat=GetDeltaT(Ind);
  if(  deltat > fConf_He4_DT_min &&  deltat < fConf_He4_DT_max){
    return dcqual;
  }else{
    return 0.;
  }

}

//=========================================================================
//=========================================================================
//=========================================================================
Int_t TPartSieve::RefineIdUnknown(Int_t Ind)
{  //Refine the Id of an unknown particle. We only test for electrons
  // right now.

  // Test i

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdPip(Int_t Ind)
{//not yet implemented
  //Refine the Id of a Pi+.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdProt(Int_t Ind)
{//not yet implemented
  //Refine the Id of a proton.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdEl(Int_t Ind)
{//not yet implemented
  //Refine the Id of an electron.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdPhot(Int_t Ind)
{//not yet implemented
  //Refine the Id of a photon.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdPim(Int_t Ind)
{//not yet implemented
  //Refine the Id of a Pi-.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdNeut(Int_t Ind)
{//not yet implemented
  //Refine the Id of a neutron.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdKp(Int_t Ind)
{//not yet implemented
  //Refine the Id of a kaon+.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdDeut(Int_t Ind)
{//not yet implemented
  //Refine the Id of a deuteron.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdKm(Int_t Ind)
{//not yet implemented
  //Refine the Id of a kaon-.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdHe3(Int_t Ind)
{//not yet implemented
  //Refine the Id of a helium 3.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdHe4(Int_t Ind)
{//not yet implemented
  //Refine the Id of a helium 4.

  return 0;
}
//=========================================================================
Int_t TPartSieve::RefineIdPos(Int_t Ind)
{//not yet implemented
  //Refine the Id of a positron.

  return 0;
}
//=========================================================================
//=========================================================================
void TPartSieve::ChangeID(Int_t Ind, Int_t ID)
{ // NOT YET IMPLEMENTED.
  //This function changes the id of the particle in the ClasTool bank with
  //index Ind to the ID in the arguement.

}
//=========================================================================
void TPartSieve::SetConfidenceCut(Float_t conf)
{
  //Set the minimum confidence a particle may have and be saved in the Sieve

  if(conf <=1.&&conf>=0) fConfidenceCut = conf;
  else {
    cout << "Confidence Cut should be >0 and <1." << endl;
    cout << "Confidence Cut Set to .5" << endl << endl;
    fConfidenceCut = .5;
  }
}
//==========================================================================
void TPartSieve::SetRefConfidenceCut(Float_t conf)
{
  //Set the minimum confidence a particle may have if it is not to be refined

  fRefConfidenceCut = conf;
}
//==========================================================================
Float_t TPartSieve::BetaBetaCut(Int_t Ind, Float_t mass, Float_t Weight,Float_t MaxDiff)
{
  // In these Cut functions the difference between an ideal value and the 
  // experimental value is calculated. The difference is scaled so that a
  // difference of MaxDiff is scaled to 1, values less are less than 1 and
  // values greater than MaxDiff are greater than 1. The scaled difference is
  // then multiplied by Weight and returned. The returned value is meant to 
  // be subtracted from the confidence.
  //
  // Compares the Beta from EVNT class with betta found using the formula
  // B= p/sqrt(p^2 + m^2).m is the input parameter mass. Use the accepted value.
  // Weight is a measure of how severe the cut is. Returns the 
  // reduction in confidence.

  if(MaxDiff<=0){//test for 0
    cout << "MaxDiff Must be > 0!!" << endl;
    return 0.;
  }

  TEVNTClass *fEVNT = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  Float_t P = fEVNT->GetMomentum();
  Float_t Betta = (P/sqrt(P*P + mass*mass));
  Float_t Diff = Betta - fEVNT->GetBeta();

  Float_t ScaledDiff = TMath::Abs(Diff/MaxDiff);

  return (Weight*ScaledDiff);
}
//================================================================================
Float_t TPartSieve::CutConfMax(Float_t x,Float_t cut,Float_t width){
  //
  // Helper function.
  // This function return 1 if x is below cut-width/2.
  // It will return       0 if x is above cut+width/2.
  // Between cut-width/2 and cut+width/2 it returns a value between 1 and 0
  // decreasing linearly.
  
  if(x < cut-width/2){return 1;}
  if(x > cut+width/2){return 0;}
  return( (cut-x)/width + 0.5);
}

Float_t TPartSieve::CutConfMin(Float_t x,Float_t cut,Float_t width){
  //
  // Helper function.
  // This function return 0 if x is below cut-width/2.
  // It will return       1 if x is above cut+width/2.
  // Between cut-width/2 and cut+width/2 it returns a value between 0 and 1
  // increasing linearly.
  
  if(x > cut+width/2){return 1;}
  if(x < cut-width/2){return 0;}
  return( (x-cut)/width + 0.5);
}

//================================================================================
Float_t TPartSieve::ECUVWCut(Int_t Ind, Float_t WidthMultiply){
  // See Float_t TPartSieve::ECUVWCut(TEVNTClass *evnt, Float_t WidthMultiply)
  TEVNTClass *evnt = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  return ECUVWCut(evnt, WidthMultiply);
}

Float_t TPartSieve::ECUVWCut(TEVNTClass *evnt, Float_t WidthMultiply)
{
  // This function cuts on the U,V and W coordinate on the EC plane. 
  // These cuts make sure we do not use the events that are too close to the edge
  // where some of the shower could have leaked out of the calorimeter.
  //
  // Instead of a hard cut, where the function would return 1 if you are inside
  // and 0 if you are outside, each cut specifies a "width". The function returns
  // a value of 0 or 1 outside this widht, and inside the width it returns a 
  // value bewteen 0 and 1. The "WidthMultiply" parameter allows you to stretch
  // or shrink these widths. So WidthMultiply=0 will give you the standard
  // 1 or 0 behavior.
  //
  // Cuts are specified by fEC_U_Cut, fEC_V_Cut and fEC_W_Cut, where the U cut
  // is a cut on minumum U, and the V and W cuts are maxima. The widths for
  // these cuts are set in fEC_?_Cut_width.
  //
  // Reasonable defaults are choosen for these cuts, but you probably want to 
  // fine tune them for your analysis.
  //
  //

  Float_t U,V,W;
  Float_t conf=1.;

  if(evnt->GetECidx()>=0){
    TECPBClass *ec=(TECPBClass *)fCT->GetBankRow("ECPB",evnt->GetECidx());
    ec->GetUVW(&U,&V,&W);
  //  printf("\nVals U: %5.2f  V: %5.2f  W:%5.2f \n",U,V,W);
  //  printf("Cuts U: %5.3f  ",CutConfMin(U,fEC_U_Cut,fEC_U_Cut_width*WidthMultiply));
  //  printf("V: %5.3f  ",CutConfMax(V,fEC_V_Cut,fEC_V_Cut_width*WidthMultiply));
  //  printf("W: %5.3f \n",CutConfMax(W,fEC_W_Cut,fEC_W_Cut_width*WidthMultiply));
    conf *= CutConfMin(U,fEC_U_Cut,fEC_U_Cut_width*WidthMultiply);
    conf *= CutConfMax(V,fEC_V_Cut,fEC_V_Cut_width*WidthMultiply);
    conf *= CutConfMax(W,fEC_W_Cut,fEC_W_Cut_width*WidthMultiply);
    //  printf("Conf: %6.3f \n\n",conf);
    return (conf);
  }else{
    return(0.);
  }
}

Float_t TPartSieve::EC_Eio_Cut(Int_t Ind,Float_t WidthMultiply){
  // See TPartSieve::EC_Eio_Cut((TEVNTClass *evnt,Float_t WidthMultiply)
  TEVNTClass *evnt = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  return EC_Eio_Cut(evnt, WidthMultiply);
}

Float_t TPartSieve::EC_Eio_Cut(TEVNTClass *evnt,Float_t WidthMultiply){
  //
  // This performs a cut on the EC Inner energy versus the EC Outer energy
  // to identify good electrons.
  // The cut is a line: Eout/p >= Off - Slope* Ein/p
  // Where Off=0.156 , Slope=1 is standard.
  //
  // Right now this is a hard cut, returning 0 or 1.

  Float_t p=evnt->GetMomentum();
  if(evnt->GetECidx()>=0){
    TECPBClass *ec=(TECPBClass *)fCT->GetBankRow("ECPB",evnt->GetECidx());

    Float_t Eip = ec->Ein /p;
    Float_t Eop = ec->Eout/p;
    
    if( (Eop >= fEC_Eio_off - fEC_Eio_slope*Eip) && (ec->Ein > fEC_Ein_cut ) && (ec->Eout >fEC_Eout_cut) ){
      return(1.);
    }else{
      return(0.);
    }
  }else{
    return(0.);
  }
}


//====================================================================================

Float_t TPartSieve::GetDeltaT(Int_t Ind){
  //
  // See TPartSieve::GetDeltaT(TSCPBClass *sc,Float_t p,Int_t ipart)
  //
  TEVNTClass *evnt = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  return GetDeltaT(evnt);
}

//====================================================================================
Float_t TPartSieve::GetDeltaT(TEVNTClass *evnt){
  //
  // Get the DeltaT (difference between flight time calculated from
  // sc hit and from momentum, see below) for event *evnt.
  //
  // First checks whether there was an SC hit, if not returns -1000.
  // Next, checks whether the SC paddle is on the bad paddle list,
  // if so, returns -999.
  // If neither of the above, it returns the DeltaT by calling the routine below.
  //
  if(evnt->GetSCidx()>=0){
    TSCPBClass *sc=(TSCPBClass *)fCT->GetBankRow("SCPB",evnt->GetSCidx());
    if(CheckSCPaddle(sc->Scpdht)){
      return -999.;
    }else{
      Float_t p=evnt->GetMomentum();
      Int_t indx=IDtoInd(evnt->GetId());       
      return GetDeltaT(sc,p,indx);
    }
  }else{
    return -1000.;
  }
}

//====================================================================================
Float_t TPartSieve::GetDeltaT(TSCPBClass *sc,Float_t p,Int_t ipart)
{
  //
  // Returns the difference between flight time calculated from
  // the scintellator hit time dt_sc=(sc->Time - head->STT) and the flight time
  // calculated from the momentum: dt_p=sc->Path/(29.9*betap), where 
  // betap = p/(p*p+m*m) , with m the guessed at particle mass.
  // This should thus be zero if the mass is guessed correctly and resolution
  // is perfect.
  //
  // No checking is done for the validity of the *sc pointer!
  // Returns the DeltaT.
  //
  Float_t EventStart = ((THEADERClass *)fCT->GetHEADER())->STT;
  Float_t beta = GetBetaP(p,ipart);
  return  sc->Time - sc->Path/(29.9792*beta) - EventStart ;
}

//====================================================================================
Float_t TPartSieve::GetDeltaT_EC(TECPBClass *ec,Float_t p,Int_t ipart)
{
  //
  // Same at GetDeltaT, but for the flight path to the EC.
  // Returns the difference between flight time calculated from
  // the EC hit time dt_ec=(ec->Time - head->STT) and the flight time
  // calculated from the momentum: dt_p=ec->Path/(29.9*betap), where 
  // betap = p/(p*p+m*m) , with m the guessed at particle mass.
  // This should thus be zero if the mass is guessed correctly and resolution
  // is perfect.
  //
  Float_t EventStart = ((THEADERClass *)fCT->GetHEADER())->STT;
  Float_t beta = GetBetaP(p,ipart);
  return  ec->Time - ec->Path/(29.9792*beta) - EventStart ;
}

//====================================================================================
Float_t TPartSieve::Get_DC_Qual(Int_t Ind,Float_t Chi2,Float_t Width){
  //
  // Check the quality of the track. 
  // If no DC at all or TEVNTClass::GetDCStat<=0 return 0.
  // Also return 0. if the TEVNTClass:GetStat()<=0;
  // This filters out the hit based only tracks.
  // Else, compare the Chi2 requested with the Chi2 of the track.
  // 
  TEVNTClass *evnt = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  
  if(evnt->GetDCidx()<0 || evnt->GetStat()<=0){
    return(0.);
  }else{
    TDCPBClass *dc = (TDCPBClass *)fCT->GetBankRow("DCPB",evnt->GetDCidx());
    return( CutConfMax( dc->GetChi2(),Chi2,Width ));
  }

  
}



//====================================================================================
Float_t TPartSieve::CC_Phe_Cut(Int_t Ind,Float_t WidthMultiply){
  //
  // Cut on the number of CC photons, given an index.
  //
  TEVNTClass *evnt = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  return CC_Phe_Cut(evnt, WidthMultiply);
}

//====================================================================================
Float_t TPartSieve::CC_Phe_Cut(TEVNTClass *evnt,Float_t WidthMultiply){
  //
  // Cut on the number of CC photons.
  //
  if(evnt->GetCCidx()>=0){
    TCCPBClass *cc=(TCCPBClass *)fCT->GetBankRow("CCPB",evnt->GetCCidx());
    return CutConfMin(cc->Nphe,fCC_Phe_cut,fCC_Phe_width*WidthMultiply);
  }else{
    return 0.;
  }

}


//==================================================================================
Float_t TPartSieve::NoCCCut(Int_t Ind, Float_t Weight)
{
  //Cut For particles missing a CC bank

  TEVNTClass *fEVNT = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  if(fEVNT->GetCCidx()>=0){
    return Weight;
  }else {
    return 0;
  }
}
//=================================================================================
Float_t TPartSieve::NoECCut(Int_t Ind, Float_t Weight)
{
  //Cut For particles missing an EC bank

  TEVNTClass *fEVNT = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  if(fEVNT->GetECidx()>=0){
    return Weight;
  }else {
    return 0;
  }
}
//=================================================================================
Float_t TPartSieve::NoDCCut(Int_t Ind,Float_t Weight)
{
  //Cut For particles missing a DC bank

  TEVNTClass *fEVNT = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  if(fEVNT->GetDCidx()>=0){
    return Weight;
  }else {
    return 0;
  }
}
//=================================================================================
Float_t TPartSieve::NoSCCut(Int_t Ind,Float_t Weight)
{
  //Cut For particles missing an SC bank

  TEVNTClass *fEVNT = (TEVNTClass *)fCT->GetBankRow("EVNT",Ind);
  if(fEVNT->GetSCidx()>=0){
    return Weight;
  }else {
    return 0;
  }
}
//=================================================================================

Bool_t TPartSieve::CheckSCPaddle(TSCPBClass *sc){
  // Check is sc is on the bad paddle list.
  return CheckSCPaddle(sc->Scpdht);
}

Bool_t TPartSieve::CheckSCPaddle(Int_t sccode){
  // Check is sccode is on the bad paddle list.
  if(sccode>9999){sccode=sccode/100;} // If "raw" code is used, renormalize it.
  //
  // Have STL check if it's there.
  // Uses a binary search, which requires the vector to be sorted.
  return binary_search(fvBadPaddles.begin(),fvBadPaddles.end(),sccode); 
}

Bool_t TPartSieve::CheckSCPaddle(Int_t sec,Int_t paddle){
  // Check if {sec,paddle} is on the bad baddle list.
  return CheckSCPaddle(sec*100+paddle);
}

Int_t TPartSieve::SetBadPaddle(Int_t sec,Int_t paddle){
  // Set a paddle as bad in bad paddle list.
  // Returns the new number of bad paddles;
  //
  if(sec<1 || sec>6){
    cout << "TPartSieve::SetBadPaddle invalid sector.\n";
  }else if(paddle<1 || paddle>48){
    cout << "TPartSieve::SetBadPaddle invalid paddle.\n";
  }else{
    fvBadPaddles.push_back(sec*100+paddle);
    sort(fvBadPaddles.begin(),fvBadPaddles.end());
  }
  return fvBadPaddles.size();
}

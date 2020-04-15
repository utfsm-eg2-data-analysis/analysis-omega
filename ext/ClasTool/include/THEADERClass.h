//////////////////////////////////////////////////////////////////////
//  TEVENTClass
//  Author:  G. Gavalian
//  Date  :  10/29/99
//
//  Modified:
//           Maurik (2/3/00) Comments
//           Maurik (7/21/03) Updated to include more info.
//===================================================

#ifndef __TEVENTCLASS__
#define __TEVENTCLASS__

#include <iostream>
using namespace std;
#include "TObject.h"
#include "TClonesArray.h"
#include "TString.h"

class THEADERClass : public TObject{

public:
  Int_t    NRun;     // Run number from HEAD bank.
  Int_t    NEvent;   // Event number from HEAD bank.
  Int_t    Time;     // Unix time from HEAD bank.
  Int_t    Type;     // Event type from HEAD bank.
  Int_t    ROC;      // ROC status from HEAD bank.
  Int_t    EvtClas;  // Event Type: 1-9 Physics event (2= sync, 4=level2 late fail) 10 Scaler event. < 0 Monte Carlo
  Int_t    TrigBits; // Level 1 Trigger Latch word.
  Int_t    EStatus;  // Event status after reconstruction (HEVT)
  Int_t    TrgPrs;   // Trigger type*10000 + Prescale factor for that trigger (Event Class) (HEVT)
  Int_t    NPGP;     // Number of final reconstructed particles*100 + Number of geometrically reconstructed particles (HEVT)
  Float_t  FC;       // Faraday Cup (K) (HEVT)
  Float_t  FCG;	     // Gated Faraday Cup (HEVT)
  Float_t  TG;       // Gated Clock (HEVT)
  Float_t  STT;      // Event start time (HEVT)
  Float_t  RF1;      // RF time (HEVT)
  Float_t  RF2;      // RF time (HEVT)
  Int_t    Latch1;   // Trigger Latch from TGBI Bank (helicity info)
  Int_t    Helicity_Scaler; // Helicity scaler from TGBI Bank.
  Int_t    Interrupt_Time;  // Microsecond Interupt time from TGBI Bank.
  Int_t    Level2;   // bits: 1-8:LVL2 sector bits,  9-12:Not Used, 13: LVL2 fail, 14: LVL2 pass, 15: LVL2 fail, 16: LVL2 pass
  Int_t    Level3;   // bits: 1-6:LVL3 sector bits,  7-24:Not Used, 25-32: Version number
//
public:
	THEADERClass();
	virtual ~THEADERClass(){};
	THEADERClass(THEADERClass *TmpHEADER);
	void Print();
	
	inline Int_t   GetRunNum()   const { return NRun;      }
	inline Int_t   GetNEvent()   const { return NEvent;    }
	inline Int_t   GetTime()     const { return Time;      } 
	inline Int_t   GetType()     const { return Type;      }
	inline Int_t   GetROC()      const { return ROC;       }
	inline Int_t   GetEvtClas()  const { return EvtClas;   }
	inline Int_t   GetTrigBits() const { return TrigBits;  }
	inline Int_t   GetEStatus()  const { return EStatus;   }
	inline Int_t   GetTrgPrs()   const { return TrgPrs;    }
	inline Int_t   GetNPGP()     const { return NPGP;      }
	inline Float_t GetFC()       const { return FC;        }
	inline Float_t GetFCG()      const { return FCG;       }
	inline Float_t GetTG()       const { return TG;        }
	inline Float_t GetSTT()      const { return STT;       }
	inline Float_t GetRF1()      const { return RF1;       }
	inline Float_t GetRF2()      const { return RF2;       }
	inline Int_t   GetLatch1()   const { return Latch1;    }
	inline Int_t   GetHS()       const { return Helicity_Scaler; }
	inline Int_t   GetIT()       const { return Interrupt_Time;  }
	inline Int_t   GetLevel2()   const { return Level2;    }
	inline Int_t   GetLevel3()   const { return Level3;    }
	
        ClassDef(THEADERClass,2) //Class containing all the header information for an event.
	  
};
#endif

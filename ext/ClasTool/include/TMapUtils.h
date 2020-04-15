/////////////////////////////////////////////////////////////////////
// 
//   File: TMapUtils.h   Header File for TMapUtils library
//   
//Begin_Html  
/*  TMapUtils library provides TOOLS to get information from

 Calibration Maps from mySQL database server. 
 This library is based on TMySQL library in ROOT
 
  Initial Author :  Gagik Gavalian (UNH)
  Creation Date  :  03/08/2000 

*/
//End_Html
/////////////////////////////////////////////////////////////////////

#ifndef __TMAPUTILS__
#define __TMAPUTILS__


#include <iostream>
using namespace std;
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>

// SQL Includes

#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
// ROOT includes

#include "TROOT.h"
#include "TObject.h"
#include "TString.h"
#include "TQuery.h"
#include "TDBItem.h"
#include "TRunIndex.h"
#include "TArray.h"
#include "TArrayI.h"
#include "TArrayF.h"


//#ifndef __MAKEDUMMLIB__
//#include "TMySQLServer.h"
//#endif

#define debugERRORS           0x10
#define debugQUERYPREVIEW     0x20
#define debugDEBUG            0x30
#define debugEXCEPTIONSPRINT  0x80

class TMapUtils : public TObject  {

 private:

  TString  fHOSTNAME;  // Database HOST name
  TString  fDATABASE;  // Database to use
  TString  fUSERNAME;  // Database User name 
  TString  fPASSWORD;  // Database User Password
  TString  fRun_INDEX_Table;
  Int_t    fDebugMode; // Debugmode controls printouts given from various methods
  TString  fItemValueVersion; // This contains Velue table version Development or Production
  
  //
  //
  //
 public:
  
  
  TMapUtils(); // Default Constructor
  TMapUtils(const char *dbHOSTNAME, const char *dbDATABASE,const char *dbUSERNAME); // Constructor with initializing Database Parameters
  virtual  ~TMapUtils(); // Default Destructor.
  
  
  void  SetDBParams(const char *dbHOSTNAME,const char *dbDATABASE, const char *dbUSERNAME){ // Set Database Parameters
    fHOSTNAME = dbHOSTNAME;
    fUSERNAME = dbUSERNAME;
    fDATABASE = dbDATABASE;}
  void  SetHost(const char *dbHOSTNAME){          // Set Database Server name
    fHOSTNAME = dbHOSTNAME;};
  void  SetDatabase(const char *dbDATABASE){      // Set Database name
    fDATABASE = dbDATABASE; };
  void  SetPassword(const char *dbPASSWORD){      // Set Database user Passowrd
    fPASSWORD = dbPASSWORD; };
  //
  //
  
  TString GetTableName(const char *dSystem,const char *dSubSystem, const char *dItem);
  void    ScanMaps();   // Prints out on Standart output  all Systems (Maps)
  void    ScanSystem(const char *tSystem);  // Prints on Standard output SusSystems  of System tSystem
  void    PrintItem(const char *tSystem, const char *tSubSystem,const char *tItem, Int_t tMinRun, Int_t tMaxRun);
  void    PrintItemTable(TSQLServer *fbConn,TDBItem tMapItem, Int_t fcRunNum);
  
  //
  
  Int_t   CreateSystem(const char *system);
  // Int_t   AddSubSystem(const char *system, const char *subsystem);
  // Int_t   AddItem(const char *system, const char *subsystem , const char *item, int length, const char *type, cons char *description = "UNDESCRIBED");
  // Int_t   RemoveSystem(const char *system);
  // Int_t   RemoveItem(const char *system, const char *subsystem, const char *item);
  // Int_t   RemoveSubSystem(const char *system, const char *subsystem);
  
  
  Int_t   TableExists(TSQLServer  *conn, const char *tblname); // Checks if given Table exists in database
  Int_t   TableExists_Ex(TSQLServer  *conn, const char *tblname); //  Checks if given Table exists in database with Exception
  
  TSQLServer *ConnectDB();
  
  //
  //
  
  Int_t   GetSystemIDEx(TSQLServer *conn, const char *system_name);
  Int_t   GetSystemID(TSQLServer *conn, const char *system_name,Int_t *pSystem_ID);
  Int_t   GetSubSystemIDEx(TSQLServer *conn, int system_id, const char *subsystem_name);
  Int_t   GetSubSystemID(TSQLServer *conn, int system_id, const char *subsystem_name, Int_t *pSubSystem_ID);
  void    GetItemEx(TSQLServer *conn, int subsystem_id, const char *item_name, TDBItem *fMapItem);
  Int_t   GetItem(TSQLServer *fbConn,const char *tSystem, const char *tSubSystem,const char *tItem,TDBItem *tMapItem);
  void    GetRunIndexEx(TSQLServer *fbConn, TDBItem tMapItem, Int_t fcRunNum, const char *fcAuthor, TRunIndex  *tRunIndex);
  Int_t   GetRunIndex(TSQLServer *fbConn, TDBItem tMapItem, Int_t fcRunNum, const char *fcAuthor, TRunIndex  *tRunIndex);
  
  //void    GetItemValueEx(TSQLServer *fbConn, TDBItem tMapItem, Int_t fcRunNum, const char *fcAuthor, TItemValue *tItemValue);
  
  //Int_t   GetItemValue(TSQLServer *fbConn, TItem tMapItem, Int_t fcRunNum, const char *fcAuthor, TItemValue *tItemValue);
  
  //
  //
  //
  
  TSQLResult & SelectValues(const char *fcSystem, const char *fcSubSystem, const char *fcItem, Int_t fcRun_no, const char *fcAuthor, const char *fcValueType);
  
  void   Get_Map_Int(const char *fcSystem, const char *fcSubSystem,const char *fcItem, Int_t fcRun_no,TArrayI *fIntArray, const char *fcAuthor = "*"); // 
  
  void   Get_Map_Float(const char *fcSystem, const char *fcSubSystem,const char *fcItem, Int_t fcRun_no,TArrayF *fFloatArray, const char *fcAuthor = "*");
  
  //
  
  //void    PrintArray(TArray tmpArray);
  void    PrintIntArray(TArrayI tmpIArray);
  void    PrintFloatArray(TArrayF tmpFArray);
  
  void    PrintInfo();
  void    SetDebugMode(Int_t DbgMode);
  void    SetDbVersion(const char *fVersion);
  void    SetIndexTable(const char *fRunIndexTableName);
  
  
  //
  //
  //
  
  ClassDef(TMapUtils,1) // Class of Tools for Calibration Constant Maps
    
};

#endif

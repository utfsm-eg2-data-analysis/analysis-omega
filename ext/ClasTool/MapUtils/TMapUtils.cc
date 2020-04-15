// Author:  Maurik Holtrop <http://www.physics.unh.edu/~maurik>

//____________________ 
//
//  File :  TMapUtils.cxx
//
//  TMapUtils is set of tools to get or put
//  data into CLAS Calibration Database (MySQL version)
//
//  THIS NEEDS MORE DOCUMENTATION.

#include "TMapUtils.h"

ClassImp(TMapUtils)


TMapUtils::TMapUtils(){

  // Default Destructor
  // 

  fPASSWORD = "";
  fRun_INDEX_Table = "RunIndex";
 // SetDbVersion("DEV");

}


TMapUtils::TMapUtils(const char *dbHOSTNAME, const char *dbDATABASE,const char *dbUSERNAME){
  // 
  // Constructor initializes Database host
  // Database and user name

  fHOSTNAME = dbHOSTNAME;
  fDATABASE = dbDATABASE;
  fUSERNAME = dbUSERNAME;
  fPASSWORD = "";
  
  //  SetDbVersion("DEV");
  fRun_INDEX_Table = "RunIndex";
  fDebugMode=debugERRORS+debugEXCEPTIONSPRINT;
}

TMapUtils::~TMapUtils(){
// Default destructor
//
//

  fDebugMode = 0;

}

Int_t   TMapUtils::CreateSystem(const char *system){

  TSQLServer *db = ConnectDB();
  Int_t  opResult = 0;
  try {
    TableExists_Ex(db,"System");
    Int_t sysId;
    if(GetSystemID(db,system,&sysId) == 0){
      if(fDebugMode&debugERRORS)cout << "==>> CreateSystem ::  System " << system << "  already exists..." << endl;
      opResult = -1;
    } else {
      TQuery create;
      create << "INSERT INTO System (systemName) VALUES(\"" << system << "\")";
      TSQLResult *create_res = db->Query(create.Data());
      if(create_res->GetRowCount() != 1) opResult = -1;
    }
    
  } catch (TQuery & fErrMsg){
    if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
    opResult = -1;
  }

  delete db;
  return opResult;
}


void TMapUtils::PrintInfo(){
// Prints information about Database settings
// HOSTNAME, DATABASE, USERNAME 
//
//
  cout << setiosflags(ios::left);
  cout << endl << " Class TMap Tools : Database Information " << endl;
  cout << "+-----------------+---------------------------------+"<<endl;
  cout << "| " << setw(16) << " Database  Host " << "| " << setw(32) << fHOSTNAME.Data() << "|" << endl;
  cout << "+-----------------+---------------------------------+"<<endl;
  cout << "| " << setw(16) << " DataBase " << "| " << setw(32) << fDATABASE.Data() << "|" << endl;
  cout << "+-----------------+---------------------------------+"<<endl;
  cout << "| " << setw(16) << " Database User " << "| " << setw(32) << fUSERNAME.Data() << "|" << endl;
  cout << "+-----------------+---------------------------------+"<<endl;
  cout << "| " << setw(16) << " Password " << "| " << setw(32) << fPASSWORD.Data() << "|" << endl;
  cout << "+-----------------+---------------------------------+"<<endl<<endl;

}

TSQLServer *TMapUtils::ConnectDB(){
  //
  //  Connecting to a Database on server specified in constructor
  //  and returning pointer to TSQLServer Structure...
  //

  TString serverHost;
  serverHost += "mysql://";
  serverHost += fHOSTNAME;  
  TSQLServer *db = TSQLServer::Connect(serverHost.Data(),fUSERNAME.Data(),fPASSWORD.Data());
  if(db->SelectDataBase(fDATABASE.Data())!= 0){
    if(fDebugMode&debugERRORS)cout << " ==>> ConnectDB:: Error selecting DataBase " << fDATABASE.Data() << endl;
  }

  return db;
}

void  TMapUtils::ScanMaps(){
//  Connectos to DATBASE on HOSTNAME and Prints out System Names from
//  table System. They correcspond to MAP names in old version of MapManager
//

  TString serverHost;
  serverHost += "mysql://";
  serverHost += fHOSTNAME;
  
  TSQLServer *db = TSQLServer::Connect(serverHost.Data(),fUSERNAME.Data(),fPASSWORD.Data());
  if(db->SelectDataBase(fDATABASE.Data()) != 0){
    if(fDebugMode&debugERRORS)cout << " ScanMaps: Error selecting DataBase " << fDATABASE.Data() << endl;
    return;
  }
  
  TSQLRow     *fRow;
  TSQLResult  *fResult;
  TQuery       fQuery;
  
  cout << setiosflags(ios::left);
  
  if(db->IsConnected()){
    
    
    fQuery << "select * from System";
    fResult = db->Query(fQuery.Data());
    
    cout << endl << endl << "+--------+-------------------------+" << endl;
    cout << "|  SysID |" << setw(25) << "  System Name  " << "|" << endl;
    cout << "+--------+-------------------------| " << endl;
    while((fRow=fResult->Next())){
      cout << "|  " << setw(4) << fRow->GetField(0) << "  " << setw(1) << "|" << "    " << setw(21) << fRow->GetField(1) << "|" << endl;
    }
    cout << "+--------+-------------------------+" << endl << endl;     
  }
  
  delete db;
}


void TMapUtils::ScanSystem(const char *tSystem){
//
// Prints out Subsystems and Items for Given System
//
//

  TString serverHost;
  serverHost += "mysql://";
  serverHost += fHOSTNAME;
  
  TSQLServer *db = TSQLServer::Connect(serverHost.Data(),fUSERNAME.Data(),fPASSWORD.Data());
  
  if(db->SelectDataBase(fDATABASE.Data()) != 0){
    if(fDebugMode&debugERRORS)cout << " ScanMaps: Error selecting DataBase " << fDATABASE.Data() << endl;
    return;
  }
  
  
  TSQLRow     *fRow;
  TSQLRow     *fItemRow; 
  TSQLResult  *fResult;
  TSQLResult  *fItemResult;     
  TQuery       fQuery;
  TQuery       fItemQuery;
  Int_t        tSysID;
  // TDBItemClass   tmpIndex;
  
  
  if(db->IsConnected()){
    
    
    GetSystemID(db,tSystem,&tSysID);
    
    cout << setiosflags(ios::left);
    
    fQuery << "select subsystemId,subsystemName,description from Subsystem where systemId=" << tSysID;
    fResult = db->Query(fQuery.Data());
    cout << endl << endl << "    ScanMap For System : " << tSystem << endl << endl;
    
    while((fRow=fResult->Next())){
      Int_t  tSubSysID = fQuery.IntOf(fRow->GetField(0));
      cout  << " SubSystem : " << fRow->GetField(1) 
            << " (ID=" << tSubSysID  << ")  Description : " << fRow->GetField(2)  << endl ; 
      
      fQuery.Reset();
      fQuery << "select * from Item where subsystemId=" << tSubSysID;
      
      if((fDebugMode&debugQUERYPREVIEW)>0) fQuery.Preview();
      
      fItemResult = db->Query(fQuery.Data());
      while((fItemRow=fItemResult->Next())){
        cout << setw(15) << "   " 
             << setw(12) << fItemRow->GetField(1) << " : " 
             << setw(7) << fItemRow->GetField(0) <<" : " 
             << setw(7) << fItemRow->GetField(3) << "  :  " 
             << setw(7) << fItemRow->GetField(4) << "  :  " 
             << setw(7) << fItemRow->GetField(5) << "  :  " 
             << endl;
      }
      cout << endl << endl;
    }
  }

  delete db;
}


void  TMapUtils::PrintItemTable(TSQLServer *fbConn,TDBItem tMapItem, Int_t fcRunNum){
  //
  //   
  //
  //
  //
  TSQLRow     *fRow;
  TSQLResult  *fResult;  
  TQuery       fQuery;
  
  cout << endl << "----------------------------------------------------------------------------------------" << endl;
  fQuery << "select * from " << fItemValueVersion.Data() << " where itemId=" << tMapItem.fItemId 
         << " AND " << fcRunNum << ">=minRun AND " <<  fcRunNum << "<=maxRun  ORDER BY time" ;
  fResult = fbConn->Query(fQuery.Data());
  for(int j = 0; j < fResult->GetRowCount(); j++){
    fRow = fResult->Next();
    for(int i = 0 ; i < fResult->GetFieldCount(); i++)
         cout << "  " << fRow->GetField(i);
    cout << endl;
  }
  cout << endl << "----------------------------------------------------------------------------------------" << endl;
}

void  TMapUtils::PrintItem(const char *tSystem, const char *tSubSystem,const char *tItem, Int_t tMinRun, Int_t tMaxRun){
  // 
  //  This function Prints content of ValueDescription table for Given Item
  // specified by (System,SubSystem,Item) in Run ranges tMinRun -> tMaxRun
  //
  // NOTE. This will print all entries independent of author entry in the database
  //
  
  TString serverHost;
  serverHost += "mysql://";
  serverHost += fHOSTNAME;
  
  TSQLRow     *fRow;
  TSQLResult  *fResult;
  TQuery       fQuery;
  TDBItem       flMapItem;
  
  TSQLServer *db = TSQLServer::Connect(serverHost.Data(),fUSERNAME.Data(),fPASSWORD.Data());
  

  if(db->SelectDataBase(fDATABASE.Data()) != 0){
    if(fDebugMode&debugERRORS)cout << " PrintTable: Error selecting DataBase " << fDATABASE.Data() << endl;
    return;
  }
  
  
  
  if(GetItem(db,tSystem,tSubSystem,tItem,&flMapItem)==0){
    
    cout << "--------------------- System found " << endl;
    fQuery << "select * from " << fItemValueVersion.Data() << " where itemId=" << flMapItem.fItemId 
           << " AND minRun>=" << tMinRun << " AND maxRun<=" << tMaxRun;
    if((fDebugMode&debugQUERYPREVIEW)>0) fQuery.Preview();
    fResult = db->Query(fQuery.Data());
    while((fRow=fResult->Next())){
      cout << setw(4) << "   "
           << setw(12) << fRow->GetField(0) << " : " 
           << setw(7) << fRow->GetField(2) <<" : " 
           << setw(7) << fRow->GetField(3) << "  :  " 
           << setw(7) << fRow->GetField(4) << "  :  " 
           << setw(7) << fRow->GetField(5) << "  :  " 
           << setw(7) << fRow->GetField(6) << "  :  " 
           << endl;                
    }
  }
  delete db;
}



TSQLResult & TMapUtils::SelectValues(const char *fcSystem, const char *fcSubSystem,const char *fcItem, Int_t fcRun_no, const char *fcAuthor, const char *fcValueType){
  //
  // Selects Values from Database for given Item , Run Number and author and returns 
  // TSQLResult to calling function. Also makes check on type of Item.
  //
  // NOTE. If calling this function one must call it from "try"-"catch" block.
  // If error accures function will trow an exception. 
  //
  
  TQuery  tmpQuery;
  TSQLResult *flResult;
  TDBItem flMapItem;
  TRunIndex flItemValue;
  
  TString serverHost;
  serverHost += "mysql://";
  serverHost += fHOSTNAME;
  
  TSQLServer *dbConn = TSQLServer::Connect(serverHost.Data(),fUSERNAME.Data(),fPASSWORD.Data());
  
  if( dbConn != 0 && dbConn->IsConnected() ) {
    
    if(dbConn->SelectDataBase(fDATABASE.Data()) != 0) {
      dbConn->Close();
      delete dbConn;
      dbConn = 0;
      TQuery localErrMsg;
      localErrMsg << " SelectValues: Error selecting DataBase " << fDATABASE.Data();
      throw localErrMsg;
    }
    
    if(GetItem(dbConn,fcSystem,fcSubSystem,fcItem,&flMapItem) != 0){
      dbConn->Close();
      delete dbConn;
      dbConn = 0;
      TQuery localErrMsg;
      localErrMsg << "SelectValues: Item Not Found ";
      throw localErrMsg;
    }
    
    if(fDebugMode&debugDEBUG)flMapItem.Print();
    
    if(GetRunIndex(dbConn,flMapItem,fcRun_no,fcAuthor,&flItemValue) != 0){
      dbConn->Close();
      delete dbConn;
      dbConn = 0;
      TQuery localErrMsg;
      localErrMsg << "SelectValues: Item Not Found ";
      throw localErrMsg;
    }
    
    
    if(flMapItem.fType != fcValueType){
      dbConn->Close();
      delete dbConn;
      dbConn = 0;
      TQuery localErrMsg;
      localErrMsg << "SelectValues: Type Is not what was expected.  " << fcValueType;
      throw localErrMsg;
    }
    
    
    tmpQuery.Reset(); 
    
    TQuery  flTblName;
    TQuery  fValues;
    
    fValues << "itemValueId,v_0001";
    char fieldname[32];
    for(int ival=2;ival<=flMapItem.fLength;ival++) {
      sprintf(fieldname,",v_%04d",ival);
      fValues << fieldname;
    }
    
    flTblName << fcSystem << "_" << fcSubSystem << "_" << fcItem ;//<< "_VALUE";
    
    tmpQuery << "select "<< fValues.Data() <<" from " <<  flTblName.Data() << " where itemValueId=" << flItemValue.fItemValueId;
    
    if((fDebugMode&debugQUERYPREVIEW)>0) tmpQuery.Preview();
    
    flResult = dbConn->Query(tmpQuery.Data());
    
    if(flResult->GetRowCount() != 1){
      dbConn->Close();
      delete dbConn;
      dbConn = 0;
      TQuery localErrMsg;
      localErrMsg << "SelectValues: Got unexpected count of Rows " << flResult->GetRowCount();
      throw localErrMsg;    
    }
    
    if(flResult->GetFieldCount() != flMapItem.fLength+1){
      dbConn->Close();
      delete dbConn;
      dbConn = 0;      
      TQuery localErrMsg;
      localErrMsg << "SelectValues: Wrong Item Length. expected : " << flMapItem.fLength 
                  << "  got : " << flResult->GetFieldCount()-1;
      throw localErrMsg;
    }           
    
  } else {
    
    TQuery localErrMsg;
    localErrMsg << "SelectValues: Database is not connected... "; 
    if( dbConn != 0 ) {
      delete dbConn;
      dbConn = 0;
    }
    throw localErrMsg; 
  }
  
  if( dbConn != 0 && dbConn->IsConnected() ) {
    dbConn->Close();
    delete dbConn;
    dbConn = 0;     
  } else if( dbConn != 0 ) {
    delete dbConn;
    dbConn = 0; 
  }
  return (*flResult);
}


void    TMapUtils::Get_Map_Int(const char *fcSystem, const char *fcSubSystem,const char *fcItem, Int_t fcRun_no,TArrayI *fIntArray, const char *fcAuthor){
  //
  //  This routine initializes Integer Buffer passed to it and fills it with  
  //  Values for given Item. There are several advantages using this method.
  //
  //  1) User does not have to warry about deleting array if it is defined
  //      as static. For example :
  //   {
  //       TIntBuffer  myDC_T0;
  //       GetMapIntBuff("DC_","t0","value",15678,&myDC_T0);
  //   }
  //   after this braket buffer will be delated automaticaly.
  //
  //   2) Class TIntBuffer has bound check (unlike array of int's).
  //      if one will ask for non existing element in array it will not 
  //      couse segmentation falt.
  //
  //  NOTE: It is recomended to use this function instead of 
  //  GetMapInt to avoid memory leaks. 
  // 
  // 
  
  TSQLRow  *sqlRow;
  TQuery    tmpQuery;
  
  try{
    
    TSQLResult & sqlResult = SelectValues(fcSystem,fcSubSystem,fcItem,fcRun_no,fcAuthor,"int");
    Int_t lBufferLength = sqlResult.GetFieldCount() - 1;
    
    fIntArray->Set(lBufferLength);
    fIntArray->Reset();
    
    //  flBuffer = new Int_t[lBufferLength];
    //  *fiBuffer_length = lBufferLength;
    
    sqlRow = sqlResult.Next();
    for(int j=0; j< lBufferLength ; j++) 
      fIntArray->AddAt(tmpQuery.IntOf(sqlRow->GetField(j+1)),j);
    
  } catch  (TQuery & fErrMsg) {
     if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
  }
  
}



void    TMapUtils::Get_Map_Float(const char *fcSystem, const char *fcSubSystem,const char *fcItem, Int_t fcRun_no,TArrayF *fFloatArray, const char *fcAuthor){
  //
  //  This routine initializes Float Buffer passed to it and fills it with  
  //  Values for given Item. There are several advantages using this method.
  //
  //  1) User does not have to warry about deleting array if it is defined
  //      as static. For example :
  //   {
  //       TFloatBuffer  myDC_T0;
  //       GetMapFloatBuff("DC_","t0","value",15678,&myDC_T0);
  //   }
  //   after this braket buffer will be delated automaticaly.
  //
  //   2) Class TFloatBuffer has bound check (unlike array of int's).
  //      if one will ask for non existing element in array it will not 
  //      couse segmentation falt.
  //
  //  NOTE: It is recomended to use this function instead of 
  //  GetMapFloat to avoid memory leaks. 
  // 
  // 
  
  
  
  TSQLRow  *sqlRow;
  TQuery    tmpQuery;
  
  try{
    
    TSQLResult & sqlResult = SelectValues(fcSystem,fcSubSystem,fcItem,fcRun_no,fcAuthor,"float");
    
    Int_t lBufferLength = sqlResult.GetFieldCount() - 1;
    if(fDebugMode&debugDEBUG)cout << "Get Map Float : Elements in array should be.... " << lBufferLength << endl;
    fFloatArray->Set(lBufferLength);
    fFloatArray->Reset();
    
    //  flBuffer = new Float_t[lBufferLength];
    //  *fiBuffer_length = lBufferLength;
    
    sqlRow = sqlResult.Next();
    
    for(int j=0; j< lBufferLength ; j++){
      if(fDebugMode&debugDEBUG)cout << "Adding element " << j << " to array " << endl;;
      fFloatArray->AddAt(tmpQuery.FloatOf(sqlRow->GetField(j+1)),j);
    }
    
  } catch  (TQuery & fErrMsg) {
    if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
  }
  
}


Int_t    TMapUtils::GetSystemID(TSQLServer *conn, const char *system_name, Int_t *pSystem_ID){
  //
  // This routine writes into pSystem_ID system ID for given System_name
  //
  // returns 0 if system was found. -1 otherwise
  //
  
  try{
    *pSystem_ID = GetSystemIDEx(conn,system_name);
  }catch  (TQuery & fErrMsg) {
     if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
    return -1;
  }
  return 0;
}

Int_t    TMapUtils::GetSystemIDEx(TSQLServer *conn, const char *system_name){
  Int_t System_id = -1;
  
  TSQLRow     *fRow;
  TSQLResult  *fResult;
  TQuery fQuery;
  
  fQuery << "select systemId from System where systemName=\"" << system_name << "\"";
  if((fDebugMode&debugQUERYPREVIEW)>0) fQuery.Preview();
  fResult = conn->Query(fQuery.Data());
  
  if(fResult->GetRowCount()==1){
    fRow = fResult->Next();
    sscanf(fRow->GetField(0),"%d",&System_id);
  } else {
    
    TQuery ErrMsg;
    ErrMsg << "==>> ERROR(TDBItemClass::GetSystemID): System " << system_name << " not Found ";
    throw ErrMsg;
  }
  
  return System_id;
}

Int_t   TMapUtils::TableExists(TSQLServer  *conn, const char *tblname){
  try{
    TableExists_Ex(conn,tblname);
  } catch (TQuery & fErrMsg){
    if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
    return -1;
  }
  return 0;
}

Int_t   TMapUtils::TableExists_Ex(TSQLServer  *conn, const char *tblname){
  //
  //  Checks if Tbale  tblname exists in database 
  //  returns 0 if table exists throws exception otherwise.
  //
  if(conn->IsConnected()){
    TSQLResult *tables = conn->GetTables(fDATABASE.Data(),tblname);
    if(tables->GetRowCount() != 1){
      TQuery ErrMsg;
      ErrMsg << "===>> TABLE EXISTS: (ERROR) Table  "<< tblname << "  is not found....";
      throw ErrMsg;   
    }
  } else {
    TQuery ErrMsg;
    ErrMsg << "===>> TABLE EXISTS: (ERROR)  Database is not connected....";
    throw ErrMsg;  
  }
  return 0;
}

Int_t    TMapUtils::GetSubSystemID(TSQLServer *conn, int system_id, const char *subsystem_name, Int_t *pSubSystem_ID){
  //
  //  SubSystem in pSubSystem_ID variable
  //
  //
  
  try{
    *pSubSystem_ID = GetSubSystemIDEx(conn,system_id,subsystem_name);
  }catch  (TQuery & fErrMsg) {
    if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
    return -1;
  }
  return 0;
}

Int_t    TMapUtils::GetSubSystemIDEx(TSQLServer *conn, int system_id, const char *subsystem_name){
  //
  // Returns SubSystem id from table SubSystem corresponding to given SystemID
  //
  //
  
  Int_t SubSystem_id = -1;
  
  TSQLRow     *fRow;
  TSQLResult  *fResult;
  TQuery fQuery;
  
  fQuery << "select subsystemId from Subsystem where systemId=" 
         << system_id << " AND subsystemName=\"" << subsystem_name <<"\"";
  
  if((fDebugMode&debugQUERYPREVIEW)>0) fQuery.Preview();
  
  fResult = conn->Query(fQuery.Data());
  
  if(fResult->GetRowCount()==1){
    fRow = fResult->Next();
    sscanf(fRow->GetField(0),"%d",&SubSystem_id);
    //     cout << " System ID = " << fRow->GetField(0) << endl;
  } else {
    TQuery ErrMsg;
    ErrMsg << "==>> ERROR(TDBItemClass::GetSubSystemID): SubSystem not found. System ID = " << system_id 
           << "  SubSystem Name : " << subsystem_name;
    throw ErrMsg;
  }
  
  return SubSystem_id;
}

void    TMapUtils::GetItemEx(TSQLServer *conn, int subsystem_id, const char *item_name, TDBItem *fMapItem){
  
  TSQLRow     *fRow;
  TSQLResult  *fResult;
  TQuery       fQuery;
  
  fQuery << "select * from Item where subsystemID=" 
         << subsystem_id << " AND itemName=\"" << item_name << "\"";
  if((fDebugMode&debugQUERYPREVIEW)>0) fQuery.Preview();
  
  fResult = conn->Query(fQuery.Data());
  
  if(fResult->GetRowCount()==1){
    fRow = fResult->Next();
    
    fMapItem->fItemId        = fQuery.IntOf(fRow->GetField(0));
    fMapItem->fItemName      = (char *) fRow->GetField(1);
    fMapItem->fSubsystemId   = fQuery.IntOf(fRow->GetField(2));
    fMapItem->fLength        = fQuery.IntOf(fRow->GetField(3));
    fMapItem->fType          = (char *) fRow->GetField(4);
    fMapItem->fDescription   = (char *) fRow->GetField(5);
    
  } else {
    TQuery ErrMsg;
    ErrMsg << "==>> ERROR(TDBItemClass::GetItemID): Item not found. SubSystem ID = " << subsystem_id 
           << "  Item Name : " << item_name;
    throw ErrMsg;
  }
}


Int_t  TMapUtils::GetItem(TSQLServer *fbConn, const char *fcSystem,const char *fcSubSystem,const char *fcItem, TDBItem *sfItem){
  
  try{
    
    Int_t  tmpSystemID    = GetSystemIDEx(fbConn,fcSystem);
    Int_t  tmpSubSystemID = GetSubSystemIDEx(fbConn,tmpSystemID,fcSubSystem);
    GetItemEx(fbConn,tmpSubSystemID,fcItem,sfItem);
    
  } catch (TQuery & fErrMsg) {
    if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
    return -1;
  } 
  
  return 0;
}


Int_t    TMapUtils::GetRunIndex(TSQLServer *fbConn, TDBItem tMapItem, Int_t fcRunNum, const char *fcAuthor, TRunIndex  *tRunIndex){
  //  
  // This routin finds latest ItemValueId from RunIndex table for given run number
  // and returns Record of Runindex entry in tRunIndex variable.
  // This is just wrapper for GetRunIndexEx routin which throws exception if 
  // ItemValueId is not found. returns 0 on success, -1 otherwise.
  //
  
  try{
    GetRunIndexEx(fbConn,tMapItem,fcRunNum,fcAuthor,tRunIndex);
  } catch (TQuery & fErrMsg) {
    if(fDebugMode&debugEXCEPTIONSPRINT)cout << endl << fErrMsg.Data() << endl << endl;
    return -1;
  }
  return 0;
}

void    TMapUtils::GetRunIndexEx(TSQLServer *fbConn, TDBItem tMapItem, Int_t fcRunNum, const char *fcAuthor, TRunIndex  *tRunIndex){
  //
  // This routin finds latest ItemValueId from RunIndex table for given run number
  // and returns Record of Runindex entry in tRunIndex variable.
  //
  
  TSQLRow     *fRow;
  TSQLResult  *fResult;
  TQuery       fQuery;
  TQuery       fValues;
  
  fQuery.Reset();
  fValues.Reset();
  
  if(tMapItem.fLength < 1){
    TQuery ErrMsg;
    ErrMsg << "==>> ERROR(TMapUtils::GetRININDEX): Item has wrong length " << tMapItem.fLength; 
    throw ErrMsg;      
  }
  //
  //fValues << "value_1";
  //for(int ival=2;ival<=tMapItem.fLength,ival++) fValues << ",value_" << ival;
  
  
  if(strstr(fcAuthor,"*") != NULL){
    
  }
  fQuery << "SELECT RunIndexId,minRun,maxRun,itemId,itemValueId,officer,time,comment FROM " 
         << fRun_INDEX_Table.Data() << " WHERE itemId=" << tMapItem.fItemId << " AND minRun<=" << fcRunNum 
         << " AND maxRun>=" << fcRunNum << " ORDER BY time DESC LIMIT 1";
  
  if((fDebugMode&debugQUERYPREVIEW)>0) fQuery.Preview();
  
  fResult = fbConn->Query(fQuery.Data());
  
  if(fResult->GetRowCount()<=0){
    TQuery ErrMsg;
    ErrMsg << "==>> ERROR(TMapUtils::GetRunIndexID): Item Value not found. Item ID = " << tMapItem.fItemId 
           << " Run : " << fcRunNum << "  Author : " << fcAuthor;
    throw ErrMsg;
  }
  
  fRow = fResult->Next();
  tRunIndex->fRunIndexId   = fQuery.IntOf(fRow->GetField(0));
  tRunIndex->fMinRun      = fQuery.IntOf(fRow->GetField(1));
  tRunIndex->fMaxRun      = fQuery.IntOf(fRow->GetField(2));
  tRunIndex->fItemId      = fQuery.IntOf(fRow->GetField(3));
  tRunIndex->fItemValueId = fQuery.IntOf(fRow->GetField(4));
  tRunIndex->fOfficer     = fRow->GetField(5);
  tRunIndex->fTime        = fRow->GetField(6);
  tRunIndex->fComment     = fRow->GetField(7);
  
}


TString TMapUtils::GetTableName(const char *dSystem,const char *dSubSystem, const char *dItem){
  
  TString  tblName;
  
  tblName = dSystem;
  tblName += "_" ;
  tblName = dSubSystem;
  tblName += "_" ;
  tblName = dItem;
  //  tblName += "_VALUE" ;
  
  return tblName;
}


void TMapUtils::SetDebugMode(Int_t DbgMode){
  fDebugMode = DbgMode;
}

void    TMapUtils::SetIndexTable(const char *fRunIndexTableName){
  fRun_INDEX_Table = fRunIndexTableName;
}

void    TMapUtils::SetDbVersion(const char *fVersion){
  //
  //
  //
  //
  if(strcmp(fVersion,"DEV") == 0){
    fItemValueVersion = "ItemValueDescription";
    if(fDebugMode&debugDEBUG)cout << "SetGbVersion: Set Database version to Development. Table \"" 
                                  << fItemValueVersion.Data() <<"\" will be used" << endl;
  }
  if(strcmp(fVersion,"PROD") == 0){
    fItemValueVersion = "ProductionItemValueDescription";
    if(fDebugMode&debugDEBUG)cout << "SetGbVersion: Set Database version to Production. Table \"" 
         << fItemValueVersion.Data() <<"\" will be used" << endl;
  }
}

//void    PrintArray(TArray tmpArray){
//Int_t cSize = tmpArray.GetSize();

//for(int jarray=0; jarray < cSize; jarray++) cout << "ARRAY[" << jarray << "] = " <<  tmpArray[jarray] << endl;

//}

void    TMapUtils::PrintIntArray(TArrayI tmpIArray){
  Int_t cSize = tmpIArray.GetSize();
  cout << endl << "Printing Array of Integers with " <<   cSize << " elements " << endl << endl;
  for(int jarray=0; jarray < cSize; jarray++) cout << "ARRAY[" << jarray << "] = " <<  tmpIArray[jarray] << endl;
  cout << endl;
}

void    TMapUtils::PrintFloatArray(TArrayF tmpFArray){
  
  Int_t cSize = tmpFArray.GetSize();
  cout << endl << "Printing Array of Floats with " <<   cSize << " elements " << endl << endl;
  for(int jarray=0; jarray < cSize; jarray++) cout << "ARRAY[" << jarray << "] = " <<  tmpFArray[jarray] << endl;
  cout << endl;
}

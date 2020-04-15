#ifndef TMapMan_
#define TMapMan_

#include <string.h>
#include <iostream.h>
extern "C" {
#include "map_manager.h"
	   }

#define _MAPINTS "INT"
#define _MAPFLOATS "FLOAT"
#define _MAPSTRINGS "STRING"
#define _MAPINTV 0
#define _MAPFLOATV 1
#define _MAPSTRINGV 2

class TMapMan {
 private:

char fMapFileName[99];
char fSubsystemName[99];
int fNItems;
char fItemName[99];
int fEntryTime;
int fLength;
int fType;
int fNArrays;

int fMapStatus;

 public:
 
 //---------------- constructor, destructors -----------
TMapMan();
TMapMan(const char* name1,const char* name2="",const char* name3="");
// give map fil name, set subsystem and item name 
~TMapMan();

 //  ----- simple getters:
  
 int GetNItems() {return fNItems;}
 int GetEntryTime() { return fEntryTime;}
 int GetLength() { return fLength;}
 int GetType() { return fType;}
 int GetNArrays() { return fNArrays;} 

//------------- class object seting & checking --------------------
//
// The principle of this class is that at any time you have a given setting,
// (the "current seting") given by three names:
//     a map file name, a subsystem name and an item name.
// If those three names are defined, your seting is complete.
// If some are missing, the seting is uncomplete, and some methods won't work.
// There are three ways of completing your seting:
//
//   1) Using the methods below (SetMapFile, SetMapSubsystem, SetMapItem, SetMap, SetMapsub)
//      - SetMapFile, SetMapSubsystem, SetMapItem explicitely sets the Mapfile name,
//      the subsystem name and the item name respectively.
//      - SetMap seek for the next undefined name, and sets it (for exemple, if the map file name
//         is already defined, but not the subsystem name, SetMap("sys") will set the name of the subsystem.
//         if SetMap has more arguments than undefined names, it will redefine some name, always starting
//         from the lowest level (item name).
//         for exemple: (in this order, this is essential!)
//              SetMap("XX_CALIB.map","tdc"); // will set your mapfile to XX_CALIB.map, and the subsystem to "tdc"
//                                            // item name is still undefined
//              SetMap("slope"); // will set your item name to "slope"
//              SetMap("zeros"); //will change your item name to "zeros"
//              SetMap("adc","ped"); //will change your seting to subssytem "adc", item "ped"
//              SetMap("YYY.map","tdc","offser";) // will change your seting to mapfile "YYY.map", 
//                                               // subsystem "tdc", item "offset"
//      - SetMapSub works on the same principle than SetMap, but it does not touch the item name,
//          that is to say, it only modifies the map file name and the subsystem name.
//          for exemple: (in this order)
//              SetMapSub("XXX.map"); // sets map file name
//              SetMapSub("subsys1"); // sets subsystem name
//              SetMapSub("subsys2"); // change subsystem name
//              SetMapSub("YYY.map","subsys") // change map file name and subsystem name
//
//   2) You can complete your seting as your are calling some methods, those methods will use
//      the SetMap and SetMapSub methods to complete your seting before they are executed
//      for exemple: (in this order;)
//             SetMap("XXX.map","subsys1"); // Sets the map file and subsystem names.
//             cout << GetItemLength("item1"); // uses SetMap("item1") to complete the setting (here set the item name)
//             cout << GetItemLength("item2"); // uses SetMap("item2") to modify the setting (change the item name)
//             cout << GetNItems("subsys2"); // uses SetMapSub("subsys2") to modify the seting (change the 
//                                           // subsystem name). Here SetMapSub is used instead of SetMap
//                                           // because the number of items is relative to a given subsystem.
//                                           // in other world GetNItems doesn't care of what is the current item name.
//             cout << GetItemType("XXX.map","subsys3","item3"); // is also possbile
//             cout << GetItemLength(); // is also possible, in that case it uses the current seting
//
//   3) Two methods will intrinsically modify your setings: NextItem() & NextSubsystem()
//      NextItem() changes your item name to the next item in the current subsystem
//      NextSubsystem changes your subsystem name to the next subsystem in the current map file
//      If you give arguments to NextItem, it will use SetMap to modify your current seting before it is executed
//      If you give arguments to NextSubsystem, it will use SetMapSub to modify your current seting before it
//                                               is executed.
//      If your item name is not defined when you call NextItem() it will find the first item of the subsystem.
//      If you suubsystem is not defined when you call NextSubsustem() it will find the first subsystem of your map.
//      To be abble to get the first item or subsystem, you might want to force your item or subsystem name
//       to be undefined, this is done through ClearItem() and ClearSubsystem() methods.
//      for exemple to get the first item in the X.map, subsystem subs, you can do, at any time:
//         ClearItem(); NextItem();

int IsDefined(const char* name) { return (strlen(name)!=0); } // check if the string is defined
int IsNotDefined(const char* name) { return (!IsDefined(name));}
int MapIsDefined(){ return (IsDefined(fMapFileName)); } // check if defined
int SubsystemIsDefined() { return (IsDefined(fSubsystemName));}
int ItemIsDefined(){ return (IsDefined(fItemName));}
char MapExists(const char* name="");
char ItemExists() { return (char)(Read_NArrays()!=-1);}
char SubsystemExists() { return (char)(Read_NItems()!=-1);}


void SetMapFileName(const char* name) { strcpy(fMapFileName,name);}
void PrintMapFileName(); // print Map file name
const char* GetMapFileName() { return fMapFileName ;}
const char* GetMapSubsystemName() { return fSubsystemName ;}
const char* GetMapItemName() { return fItemName ;}
void SetMapSubsystemName(const char* name) {  strcpy(fSubsystemName,name);} // sets Subsystem name
void PrintMapSubsystemName(); // Print subsystem name
void ClearSubsystemName() { SetMapSubsystemName("");} // this is for use in conjonction with NextSubsystem()
void SetMapItemName(const char* name) { strcpy(fItemName,name);} // sets item name
void PrintMapItemName(); 
void ClearItemName() {SetMapItemName("");} // this is for use in conjonction with NextItem()
void PrintMapNames() {PrintMapFileName(); cout << " / "; PrintMapSubsystemName();
 cout << " / ";PrintMapItemName(); cout << endl; }

int SetMapFile(int, const char*); // sets Map file name
int SetMapFile(const char* name) { return SetMapFile(1,name);} // verbose
int SetMapFileQ(const char* name) { return SetMapFile(0,name);} // quiet
int SetMapSubsystem(int,const char*); // sets Subsystem name & update fNItems
int SetMapSubsystem(const char* name) { return SetMapSubsystem(1,name); } // verbose
int SetMapSubsystemQ(const char* name) { return SetMapSubsystem(0,name); } // quiet
int SetMapItem(int,const char*); // sets item name & update fType, fLength, fNArrays
int SetMapItem(const char* name) { return SetMapItem(1,name);} // verbose
int SetMapItemQ(const char* name) { return SetMapItem(0,name);} // quiet
int ClearMap(); // clears Map, subsystem & item
int ClearSubsystem(); // clears subsystem and item
int ClearItem(); // clear item

// SetMap() updates the seting of (mapfile, subsystem, item)
// fill all undefined fields, if there are more parameters than undefined fields,
// overwrite the last ones. (overwrite item first, then subsystem, then map filename) 
// if the interger value is !=0 verbose mode (default for interactif)
int SetMap(int, const char*,const char*name2="",const char* name3="");
int SetMap(const char* name1,const char*name2="",const char* name3="")
{return SetMap(1,name1,name2,name3);} // verbose mode (default)
int SetMapQ(const char* name1,const char*name2="",const char* name3="")
{return SetMap(0,name1,name2,name3);} // quiet mode

// SetMapsub() updates the seting of (mapfile, subsystem), same rule as above.
int SetMapSub(int,const char*,const char* name2="");
int SetMapSub(const char* name1,const char* name2=""){ return SetMapSub(1,name1,name2);} // verbose
int SetMapSubQ(const char* name1,const char* name2=""){ return SetMapSub(0,name1,name2);} // quiet

//--------- Information getters -------------

int GetStatus(); // get status value of last action
void PrintStatus(); // print corresponding message of last action
void PrintMessStatus(int); // print message corresponding to  a given status value

// subsystem info
int Read_NItems(const char* name1="",const char* name2=""); // get Nitems of the current subsystem

protected:
// item info
int Read_ItemInfo(const char* name1="",const char* name2="",const char* name3="");
// Get item information - private - calls map_stat_item

public:
int Read_ItemLength(const char* name1="",const char* name2="",const char* name3=""); // Get item length
int Read_ItemType(const char* name1="",const char* name2="",const char* name3=""); // Get item type
int PrintItemType(const char* name1="",const char* name2="",const char* name3=""); // Print item type
int Read_NArrays(const char* name1="",const char* name2="",const char* name3="");
// Get number of entries for this item in the map
int Read_EntryTime(int time=0,const char* name1="",const char* name2="",const char* name3="");

int Print(int time =-1,const char* name1="",const char* name2="",const char* name3="");
// Prints information on currents seting, at given time, (time=-1 give general info)
int PrintSubsystem(int time =-1,const char* name1="",const char* name2="",const char* name3=""); 
// Prints informations on current subsystem, at given time, parameter is (time)
int PrintItem(int time=-1,const char* name1="",const char* name2="",const char* name3="");
// Prints informations on current item, at given time, parameter is (time)
protected:
int Read_DefItem(int,int*,float*,char*);

public:
char* PrintType(int); // Returns type name corresponding to type value (see #define at the
		      // beginning of this file

// ------------------ Map creation and modification --------------
int Create(const char* name=""); // create given map file

int AddItem(int,const char*,const char* name1="",const char* name2="",const char* name3="");
// add item, parameters are (length, type name) (see #define in this file), optionnaly sets (mapfile, sub, item before)
int AddItem(int,int,const char* name1="",const char* name2="",const char* name3="");
// add item, parameters are (length ,type value), optionnaly seting (mapfile, subsytem, item before)
int ArrayType(const char*); // converts a type name into type value (see #define beginning of this file)

int RemoveArray(int,const char* name1="",const char* name2="",const char* name3="");
// remove array at given time, parameter (time), optionnaly sets things before

int RemoveItem(const char* name1="",const char* name2="",const char* name3="");
// remove item, parameter (time), optionnaly sets things before

int RemoveSubsystem(const char*,const char*);
// remove subsystem, optionnaly sets (map filename, subsystem ) before

// ------------------ Arrays Getters -----------------

int GetCharArray(int,char*,int,const char* name1="",const char* name2="",const char* name3=""); 
// Get array of char, parameters are (length,chararray,time)

int GetFloatArray(int,float*,int,const char* name1="",const char* name2="",const char* name3="");
// Get array of float, parameters are (length,floatarray,time)

int GetIntArray(int,int*,int,const char* name1="",const char* name2="",const char* name3="");
// Get array of int, parameters are (length,intarray,time)

//char GetChar(int,int,const char* name1="",const char* name2="",const char* name3="");
// Get one char at given position, parameters are (position, time)
//float GetFloat(int,int,const char* name1="",const char* name2="",const char* name3="");
// Get one float at given position, parameters are (position,time)
//int GetInt(int,int,const char* name1="",const char* name2="",const char* name3="") ;
// Get one int at given position, parameterss are (position,time)


//  --------------------------  arrays setters ----------------------

int PutCharArray(int,const char*,int,const char* name1="",const char* name2="",const char* name3=""); 
// Put array of char, parameters are (length, chararray, time)
int PutFloatArray(int,const float*,int,const char* name1="",const char* name2="",const char* name3="");
 // Put array of float, parameters are (length, floatarray, time)
int PutIntArray(int,const int*,int,const char* name1="",const char* name2="",const char* name3="");
 // Put array of int, parameters are (length, intarray, time)

// ------------------------- Map browsing -----------------------------

// Find first occurence of matching int array, parameters are (length, intarray, beforetime)
int FindIntArray(int,int*,int,const char* name1="",const char* name2="",const char* name3=""); 
// optionally sets (mapfilename, subsystem, item) before

// Find first occurence of matching float array, parameters are (length, floatarray, beforetime)
int FindFloatArray(int,float*,int,const char* name1="",const char* name2="",const char* name3=""); 
// optionally sets (mapfilename, subsystem, item) before

//find next item
int NextItem(const char* name1="",const char* name2="",const char* name3="");
int NextSubsystem(const char* name1="",const char* name2="");

};

#endif





 

/*
 * itape.h
 *
*/

#ifndef itapeH_INCLUDED
#define itapeH_INCLUDED

#define TYPE_TAPEHEADER 0xffffff20
#define TYPE_ITAPE      0xffffff10  


#include <ntypes.h>


typedef struct
{
  uint32   length;       /* record length in bytes      */
  uint32   type;         /* should always be TYPE_ITAPE */
  uint32   transComputerCode;
  uint32   ngroups;
   int32   runNo;
  uint32   spillNo;
   int32   eventNo;      /* 0-BOS, (-1)-EOS, others- events number */
  uint16   eventType;    /* event type (decoded latch word)        */
   int16   trigger;      /* trigger: 0: BOS, 1-6: events, -1: EOS  */
   int32   time;         /* time as returned by time()             */
  uint32   latch;        /* virtual latch word                     */
} itape_header_t;

typedef struct
{
  uint32   length;
  uint32   type;
} group_header_t;



/* function prototypes */

int data_newItape(void* itape);
  /* void *data_addGroup(void *,int,int,int); */


int fillHeader(itape_header_t *buffer);
int addGroup(itape_header_t *buffer,int bufsize,char *bank);
int addGroups(itape_header_t *buffer,int bufsize,char *bank);
int GroupNum(char *name,int sec);
char *GroupName(int group,int *sec);
int GroupSize(int);
void cprint(char *c,char *b);
void GenBanks(itape_header_t *buffer,int bufsize,int *jw);
const itape_header_t *GetEvent1(void);
const itape_header_t *GetEvent(void);
void SendEndTape(void);
void SendBeginTape(int runNo);
char *getBuffer();
int isDispatcher(char *);





/* include the old disData.h */



/********************************************

An event will look like this:

---------------------------------------------
event      header              itape_header_t
           ----------------------------------
           group1              group_header_t
                               data
           ----------------------------------
           group2              group_header_t
                               data
           ----------------------------------
	   ...
           ----------------------------------
           groupN              group_header_t
                               data
---------------------------------------------

Assigned group numbers:

    RANGE           SUBSYSTEM                     OWNER

   0 -   99 - reserved for debugging purposes    C.Olchanski
 100 -  199 - TCYL data structures               C.Olchanski
 200 -  299 - LGD data structures                Rob
 300 -  399 - CSI data structures                ND?
 400 -  499 - MPS modules                        C.Olchanski
 500 -  599 - magnet DVMs                        C.Olchanski

**********************************************************************/

/*
 * Note: This file is used to automatically generate little <--> big
 *       endian data conversion routines. For each data group,
 *       it needs to know the data type and the include file
 *       where the data type is defined.
 *
 * Therefore each data group should be defined using the following
 *       format:
 *
 * #define GROUP_XXX        NUM  ** header.h:type_t - user comments **
 *
 *
 * There exist "special" predefined types and header files that can be used
 *       when there is no "real" data type or header file corresponding
 *       to the data group:
 *
 *   NOCONVERT_t --- a data type that does not need endian conversion,
 *                        for example an array of char.
 *   INTARRAY_t  --- a data type that should be converted as an array
 *                        of 32-bit integers, for example the raw data group.
 *
*/


#define GROUP_DELETED         0  /* groups deleted with data_removeGroup()    disData.h:NOCONVERT_t */


#ifdef mips
#define TRANSCOMPUTERCODE 1
#endif

#ifndef TRANSCOMPUTERCODE
#define TRANSCOMPUTERCODE 123
#endif


/*
 * 'data_newItape' will fill initialize an empty itape
*/

int data_newItape(void* itape);

/*
 * 'data_getGroup' returns the pointer to the group data or NULL
*/

void* data_getGroup(const void*buf,uint32 group);

unsigned long data_getGroupSize(const void*buf,uint32 group);

/*
 * 'data_getGroupHeader' returns thr pointer to the group header or NULL
*/

group_header_t* data_getGroupHeader(const void*buf,uint32 type);

void* data_addGroup(void* buffer,int bufsize,uint32 group,uint32 length);

group_header_t* data_addGroup_header(void* buffer,int bufsize,
				     uint32 group,uint32 length);

/*
 * 'data_renameGroup' will rename a given group. The return value is:
 * 0: success, non 0: error.
*/

int data_renameGroup(void* event,int oldName,int newName);

/*
 * 'data_removeGroup' returns 0 if group found and removed, 1 otherwise
 *    the space occupied by the removed group is not deallocated and is lost
 *    until 'data_clean' is called to compact the itape
*/

int data_removeGroup(void* buffer,uint32 groupName);


int data_removeAllgroups(void* buffer);  /* returns 1 */
int data_saveGroups(void* buffer,int nsave,int *isave);  /* returns 1 */

/*
 * returns the address of the end of used space inside the buffer
*/

void* data_getAdr(const void*buffer);

/*
 * 'data_clean' removes the unused parts of the itape created by the 'removeGroup' functions
 *
 *    NOTICE: this call moves data inside the itape and therefore all pointers
 *            into the itape (for example, pointers returned by 'getGroup')
 *            become invalid.
*/

int data_clean(void* buffer);

/*
 * Calculates a new CRC for the itape
*/

int data_addCRC(void*buffer);

/*
 * Check the CRC. If it is broken, return 1, otherwise, return 0
*/

int data_checkCRC(const void*buffer);
int data_checkCRC1(const void*buffer,int bufferLength);

/*
 * perform big <--> little endian conversion
*/

int endian_convertItape(void *itape,int itapeLength);

/* tmask() is used to check the trigger word in the itape against a trigger mask.
   The trigger word is an integer from -1 to 6 set by the DAQ code in the master SSP
   according to the trigger latch. It corresponds to the 8 possible triggers
   implemented in the E852 DAQ system.

   To find out which trigger latch values correspond to which trigger, see the DAQinit
   database (default.db, current.db, the currently selected db, etc...).

   Each bit in the trigger mask selects one of the triggers:

       bit 0 (0x01) - trigger -1 - EOS
       bit 1 (0x02) - trigger  0 - BOS
       bit 2 (0x04) - trigger 1
       bit 3 (0x08) - trigger 2
       bit 4 (0x10) - trigger 3
       bit 5 (0x20) - trigger 4
       bit 6 (0x40) - trigger 5
       bit 7 (0x80) - trigger 6
*/

int tmask(unsigned long mask,unsigned long trigger);

/*
 * To extract an event from a spill in shared memory
*/

void* data_getItape(const void*buffer,const void**nextItape);

/*
 * The 'data_listGroups' function will return-
 *    in 'ngroups' - number of groups in the event
 *    in 'groupsList' - a pointer to the array of groups
 *    in 'groupsSize' - a pointer to the array of their lengths
 *
 * All the three arguments can be NULL if the returned information is not needed
 * The arrays should be free'ed after use
*/

int data_listGroups(const void*event,int*ngroups,int **groupsList,int **groupsSize);



/* the old disIO.h */

#define DISIO_OK 0
#define DISIO_DATA 1
#define DISIO_EOF     100   /* socket connection was closed from the other side */
#define DISIO_NODATA  101   /* no data is available from the dispatcher yet */
#define DISIO_COMMAND 102   /* received a command */
#define DISIO_OVERRUN 103   /* supplied buffer too small for data (fatal error) */
#define DISIO_WRONGTYPE 104 /* the Dispatcher sent us data of an unexpected type */

#define DISIO_ERROR 1000

#define DISIO_Handle_E818 10099
#define DISIO_Handle_E852 10099
#define DISIO_Handle_E881 10002

extern int disIO_socket; /* the default Dispatcher connection socket */

/*
 * if 'server' is in the 'host:port' format, the 'port' argument is not used 
*/ 

int disIO_connect(const char*server,int port);
int disIO_disconnect(void);

/*
 * see the disIO manual for a list of commands
*/

int disIO_command(const char*str);

/*
 * Low level communication routines.
 * The 'socket' argument specifies the Dispatcher connection to use.
*/

unsigned long disIO_getaddress(const char*hostName); /* returns the IP address in host format or 0 if error */

int disIO_sendPacket(int Wsocket,int packetType,const void *ptr,int size);
int disIO_readPacket(int Rsocket,void**buffer,int*bufsize,int wait);
int disIO_cmd(int Wsocket, const char*CommandText);
int disIO_checkSocket(int Rsocket); /* check if data is available. Return value: 1 if yes, 0 if no and -1 if error */

const char* disIO_getHost(const char*server); /* get the 'host' part of the server name */
        int disIO_getPort(const char*server); /* get the 'port' part of the server name */
/*
 * High level routines
*/

int disIO_read_fd(void); /* get the Dispatcher connection socket */
int disIO_readRAW(void*buffer,int bufsize,int *nread,int wait);
int disIO_readCOOKED(void*buffer,int bufsize,int *nread,int wait);

int disIO_readRAW_alloc(void**buffer,int *bufsize,int wait);
int disIO_readCOOKED_alloc(void**buffer,int *bufsize,int wait);

int disIO_writeRAW(const void*buffer,int bufsize);
int disIO_writeCOOKED(const void*buffer,int bufsize);

/*
 * This implements a set of Map Manager 'write-only' requests.
 *
 * The 'systemName', 'subsystemName', 'itemName' and 'accessKey'
 * correspond to the 'file', 'subsystem', 'item' and 'firsttime'
 * arguments in the map_put_XXX(...) calls.
*/

#define MAP_REQUEST_PUT  102
#define MAP_REQUEST_ADD  103
#define MAP_REQUEST_ZERO 104

#define MAP_DATATYPE_INT    201
#define MAP_DATATYPE_FLOAT  202
#define MAP_DATATYPE_STRING 203

int disIO_mapRequest(int mapRequest,   /* from the MAP_REQUEST_XXX set */
		     const char *systemName,
		     const char *subsystemName,
		     const char *itemName,
		     int accessKey,
		     int dataType,     /* from the MAP_DATATYPE_XXX set */
		     int dataCount,
		     const void*dataPointer);


/* communications.h */
#define TransComputerCode 1 /* defines order of bytes for words--
	Silicon Graphics is defined to be 1, Vax is 0 */

#define DATA_RECORD 1
#define COMMAND     2
#define ITAPE       3
#define ITAPE_RECORD 4
#define TIMEOUT	    5

#define MAP_REQUEST 6

#define EIGHT_MM	9	

typedef struct {
    int transcomputer;
    int nbytes;
    int type;
} DatagramHeader_t;


typedef struct /* NOTE: all integers are 'network' endian (see 'man ntohl') */
{
  int requestCode; /* from the MAP_REQUEST_XXX set  */
  int dataType;    /* from the MAP_DATATYPE_XXX set */
  int dataCount;   /* number of 'dataType' items (array length) */

  int accessKey;   /* map manager access key */

  int    systemName_offset;
  int subsystemName_offset;
  int      itemName_offset;
  int          data_offset;
  
  char data[1];
} map_request_t;

/*
 * crc.h
 *
 *
 * CRC computation routines derived from Chuck Forsberg's Zmodem
 * implementation for UNIX. It is public domain, isn't it?
 *
 * -rev 04-16-87
 *  This file contains Unix specific code for setting terminal modes,
 *  very little is specific to ZMODEM or YMODEM per se (that code is in
 *  sz.c and rz.c).  The CRC-16 routines used by XMODEM, YMODEM, and ZMODEM
 *  are also in this file, a fast table driven macro version
 *
 */


#define CRC16INIT 0
#define CRC32INIT (0xFFFFFFFFL)

#define CRC16MAGIC (0xFFFF)
#define CRC32MAGIC (0xDEBB20E3L)

#include <itape.h>

uint32 data_crc(const void*data,int length);

/* End of crc.h */

/*
 * dataIO.h
 *
*/

#define DATAIO_EOF      0               /* file mark or end of tape              */
#define DATAIO_OK       1               /* no errors                             */
#define DATAIO_EOT      2               /* end of tape                           */
#define DATAIO_ERROR  (-1)              /* read/write error (message->stderr)    */
#define DATAIO_BADCRC (-2)              /* CRC mismatch error: data is damaged   */

int data_write(int fd,const void* event);         /* automatically regenerates the CRC word        */

int data_read(int fd,void* buffer,int bufsize);
int data_read_alloc(int fd,void **buffer);         /* memory pointed by *buffer should be free()ed  */

int data_flush(int fd);   /* Flush internal buffers: should always be called before a close()       */

int data_writeFM(int fd);                          /* Write a file mark on tape                     */

int data_findFM(int fd,int count); /* find a File Mark. count>0 seeks forward, count<0 seeks backwards */

/*
 * data_SeekTape: Position the data tape at the requested run number.
 *
 * Input arguments:     fd - file descriptor of the tape device (as returned by 'open' or 'fileno')
 *                   runNo - requested run number
 *
 * Return value:    0  if run was found.
 *                (-1) if run was not found
 *
 * Output arguments:  tapeNo - if a tape label is encountered while
 *                             seeking the requested run,
 *                             'tapeNo' will be set to the run number from it.
 *                             Otherwise the value is left unchanged.
*/

int data_SeekTape(int fd,int runNo,int *tapeNo);
/*
 * tapeIO.h
 *
*/


#define TAPEIO_OK       0
#define TAPEIO_ERROR  (-1)
#define TAPEIO_EOT    (-2)   /* end of data (End Of Tape) */

#define TAPEIO_STREAM   1    /* file descriptor is not a tape device      */
#define TAPEIO_FIXED    2    /* it's a tape device in fixed block mode    */
#define TAPEIO_VARIABLE 3    /* it's a tape device in variable block mode */
#define TAPEIO_PIPE     4    /* pipe or TCP socket */

int tape_devType(int fd); /* returns one of the TAPEIO_xxxx or (-1) if error */

int tape_write(int fd,const void*buffer,int len);
int tape_read(int fd,void*buffer,int len);
int tape_flush(int fd);
int tape_writeFM(int fd);

int tape_getBlockSize(int fd,unsigned long*minSize,unsigned long*maxSize,unsigned long*recSize);
int tape_getState(int fd);              /* returns bits defined in mtio.h: MT_BOT, etc... */
unsigned long tape_getPosition(int fd); /* returns current tape block number (does not work for jag tapes) */

int tape_setBlockSize(int fd,unsigned long newBlockSize);

int tape_rewind(int fd);
int tape_unload(int fd);
int tape_findFM(int fd,int count);  /* count > 0 seeks forward, count < 0 seeks backwards */

extern int tape_enablePipeIO;  /* enable the special handing of PIPEs */

#endif

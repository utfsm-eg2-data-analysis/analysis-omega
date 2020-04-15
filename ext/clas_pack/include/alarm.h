/* Include file for e852 error handler system*/

#define MCAST_PORT (6250)	/*multicast port to use*/
#define MCAST_GROUP ((225<<24) + (0<<16) + (0<<8) + 250) /*multicast address*/
#define MCAST_RELAY_PORT (6251) /*port for communications between relays*/

typedef struct {
  char magic[4];		/*"Magic" word - always should be "E852"*/
  int  code;			/*Type of message (see below)*/
  char name[32];		/*self-registered name of this process*/
  int  iname;			/*name, compressed to int (for quick compare)*/
  char subset[16];		/*subset of programs this process belongs to*/
  int  isubset;			/*subset, compressed to int*/
  int  pid;			/*pid of the process sending message*/
  int  computer;		/*sysid of the computer sending message*/
  int  n;			/*consequent message # from this process*/
  int  id;			/*Depending on the code, id is:
				  - unique message header, compressed to int,
				    followed by message itself, for 0-3;
				  - audio message # + minimum repeat time in 
				    seconds for 4;
				  - unique message header, compressed to int,
				    for 5-8;
				  - unused for 9-19;
				  - IP address of relay for 20-21; */
  int  relay_pid;		/*only zero-field(not yet relayed) messages 
				  will be relayed to other subnets*/
} MCAST_HEADER;

#define MCAST_BUFFER_SIZE (256)	/*maximum total size of message (bytes)*/

/*Types of multicast messages for MCAST_HEADER.code*/
#define MCAST_UNKNOWN  (0)   /*unknown severity -> analyze rate of this error*/
#define MCAST_WARNING  (1)   /*warning*/
#define MCAST_ERROR    (2)   /*error*/
#define MCAST_FATAL    (3)   /*fatal error*/
#define MCAST_AUDIO    (4)   /*Messages for e852 audio daemon*/
#define MCAST_RED      (5)   /*Set corresponding message to RED globally*/
#define MCAST_YELLOW   (6)   /*Set corresponding message to YELLOW globally*/
#define MCAST_GREEN    (7)   /*Set corresponding message to GREEN globally*/
#define MCAST_REMOVE   (8)   /*Remove corresponding message from system*/
#define MCAST_RED1     (9)   /*All YELLOW messages for this process -> RED*/
#define MCAST_YELLOW1 (10)   /*All RED messages for this process -> YELLOW*/
#define MCAST_GREEN1  (11)   /*All YELLOW messages for this process -> GREEN*/
#define MCAST_GR_YEL1 (12)   /*All GREEN messages for this process -> YELLOW*/
#define MCAST_REMOVE1 (13)   /*Remove all GREEN messages for this process*/
#define MCAST_RED2    (14)   /*All YELLOW messages -> RED*/
#define MCAST_YELLOW2 (15)   /*All RED messages -> YELLOW*/
#define MCAST_GREEN2  (16)   /*All YELLOW messages -> GREEN*/
#define MCAST_GR_YEL2 (17)   /*All GREEN messages -> YELLOW*/
#define MCAST_REMOVE2 (18)   /*Remove all GREEN messages*/
#define MCAST_QUERY   (19)   /*Is there a multicast relay to other subnets?*/
#define MCAST_RELAY   (20)   /*Responce from multicast relay*/
#define MCAST_RELAY_QUIT (21)   /*Relay is quitting...*/

/*Shortcuts for above*/
#define ALARM_UNKNOWN  MCAST_UNKNOWN
#define ALARM_WARNING  MCAST_WARNING
#define ALARM_ERROR    MCAST_ERROR
#define ALARM_FATAL    MCAST_FATAL

void eregister(const char *,const char *);
void eregister_get(void);
void esay(int,int);
void esend(int,const char *,const char *,...);
void esendp(int,const char *,const char *,...);
void esend_setmode(int);
void esend_color(int,const char *);
void esend_color_id(int,int);
void esend_color12(int);
void esend_query(void);
void esend_relay(int);
void esend_relay_quit(int);
int ereceive(void);
void eget_internals(int *,int *,MCAST_HEADER **,MCAST_HEADER **);

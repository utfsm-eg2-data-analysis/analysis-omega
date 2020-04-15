#include <rpc/rpc.h>

struct bdata {
	int type;
	union {
		struct {
			u_int iraw_len;
			int *iraw_val;
		} iraw;
		struct {
			u_int sraw_len;
			short *sraw_val;
		} sraw;
	} bdata_u;
};
typedef struct bdata bdata;
bool_t xdr_bdata();


struct aBank {
	char *name;
	char *format;
	int nr;
	int nrows;
	int ncols;
	int d_size;
	struct {
		u_int bd_len;
		bdata *bd_val;
	} bd;
};
typedef struct aBank aBank;
bool_t xdr_aBank();


typedef char *mstr;
bool_t xdr_mstr();


struct Event {
	int errcode;
	mstr s;
	struct {
		u_int b_len;
		aBank *b_val;
	} b;
};
typedef struct Event Event;
bool_t xdr_Event();


#define EVTSVC_INP ((u_long)0x20000033)
#define IVER ((u_long)33)
#define SVCNAME ((u_long)1)
extern mstr *svcname_1();
extern mstr *svcname_1_svc();
#define MsgNoReply ((u_long)2)
extern int *msgnoreply_1();
extern int *msgnoreply_1_svc();
#define MsgWReply ((u_long)3)
extern Event *msgwreply_1();
extern Event *msgwreply_1_svc();
#define BrowCreate ((u_long)4)
extern int *browcreate_1();
extern int *browcreate_1_svc();
#define BrowDestroy ((u_long)5)
extern int *browdestroy_1();
extern int *browdestroy_1_svc();
#define BrowFilter ((u_long)6)
extern Event *browfilter_1();
extern Event *browfilter_1_svc();


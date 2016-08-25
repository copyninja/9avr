/* copied from Inferno's include/styx.h file */
#define	VERSION9P	"9P2000"
#define	MAXWELEM	16

#define	BIT8SZ		1
#define	BIT16SZ		2
#define	BIT32SZ		4
#define	BIT64SZ		8
#define	QIDSZ	        (BIT8SZ+BIT32SZ+BIT64SZ)

#define	IOHDRSZ		24	/* ample room for Twrite/Rread header (iounit) */

enum
{
	Tversion =	100,
	Rversion,
	Tauth    =	102,
	Rauth,
	Tattach  =	104,
	Rattach,
	Terror   =	106,	/* illegal */
	Rerror,
	Tflush   =	108,
	Rflush,
	Twalk    =	110,
	Rwalk,
	Topen    =	112,
	Ropen,
	Tcreate  =	114,
	Rcreate,
	Tread    =	116,
	Rread,
	Twrite   =	118,
	Rwrite,
	Tclunk   =	120,
	Rclunk,
	Tremove  =	122,
	Rremove,
	Tstat    =	124,
	Rstat,
	Twstat   =	126,
	Rwstat,
	Tmax,
};

#ifndef __STYX_INCLUDE_H__

/* copied from Inferno's include/styx.h and include/fcall.h file */
#define	VERSION9P	"9P2000"
#define	MAXWELEM	16

#define GBIT8(p)        ((p)[0])
#define GBIT16(p)       ((p)[0]|((p)[1]<<8))
#define GBIT32(p)       ((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24))
#define GBIT64(p)       ((vlong)((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24)) |\
                                ((vlong)((p)[4]|((p)[5]<<8)|((p)[6]<<16)|((p)[7]<<24)) << 32))

#define PBIT8(p,v)      (p)[0]=(v)
#define PBIT16(p,v)     (p)[0]=(v);(p)[1]=(v)>>8
#define PBIT32(p,v)     (p)[0]=(v);(p)[1]=(v)>>8;(p)[2]=(v)>>16;(p)[3]=(v)>>24
#define PBIT64(p,v)     (p)[0]=(v);(p)[1]=(v)>>8;(p)[2]=(v)>>16;(p)[3]=(v)>>24;\
                        (p)[4]=(v)>>32;(p)[5]=(v)>>40;(p)[6]=(v)>>48;(p)[7]=(v)>>56

#define	BIT8SZ		1
#define	BIT16SZ		2
#define	BIT32SZ		4
#define	BIT64SZ		8
#define	QIDSZ	        (BIT8SZ+BIT32SZ+BIT64SZ)


#define	NOTAG		(ushort)~0U	/* Dummy tag */
#define	NOFID		(u32int)~0U	/* Dummy fid */
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

#endif // __STYX_INCLUDE_H__

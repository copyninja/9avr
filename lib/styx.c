#include "lib9.h"
#include "styx.h"

#include <assert.h>
#include <string.h>

#define QID_ROOT  0
#define QID_HELLO 1

short helloread(const struct DirectoryEntry *dp, ushort tag, ushort fid, ushort offset, ushort count) {
     return 0;
}

typedef struct DirectoryEntry {
     char *name;
     uchar qid;
     const struct DirectoryEntry *sub;
     short (*read)(const struct DirectoryEntry *dp, ushort tag, ushort fid, ushort offset, ushort count);
     short (*write)(const struct DirectoryEntry *dp, ushort offset, ushort count, uchar *buf);
} DirectoryEntry;

/* qid is 104 bits long */
const uchar qid_root[13] = {};

const DirectoryEntry dir_root[], dir_slash[];

const DirectoryEntry dir_root[] = {
     {"..", QID_ROOT, dir_slash },
     {"hello", QID_HELLO, 0, helloread, hellowrite },
     { 0 }
};

const DirectoryEntry dir_slash[] = {
     { "/", QID_ROOT, dir_root },
     { 0 }
};

const DirectoryEntry *qid_map[] = {
     /* QID_ROOT */  &dir_slash[0],
     /* QID_HELLO */ &dir_root[1],
};



uchar resp[16];

void process_styx_message(uchar *msg, short len)
{
     uchar type = msg[0];

     switch (type) {
     case Tversion:
          /*
            Tversion[1] tag[2] msize[4] version[s]
            Tversion NOTAG msize "9P2000"
          */

          uchar tag = GBIT16(&msg[1]);
          /* Client establishes with NOTAG  */
          assert(tag == NOTAG);

          /* msize is 4 bytes */
          u32int msize = GBIT32(&msg[3]);

          /* next 6 bytes is the string "9P2000" */
          char protover[7];
          strncpy(protover, (const char*)(msg+7), 6);
          protover[6] = '\0';


          if (strcmp(protover, VERSION9P) == 0) {
               /* send Rversion */
          }
          else {
               /* send Rerror */
          }

          break;
     default:
          break;
     }
}

/* All 9p messages start with these 7 bytes.
 * size[4] type[1] tag[2]
 * size - size is 32 bit little endian, indicating the message size
 *        (including 4 bytes of the size itself).
 * type - there are 28 message types in 9p2000 (see styx.h)
 */
void process_message(uchar *msg, short len)
{
     short msgsize;

     msgsize = GBIT32(&msg[0]);

     if (msgsize > 0) {
          process_styx_message(&msg[4], msgsize - 4);
     }
}


int msgloop(void)
{
     char buf[16];

     while (true) {
          int len = receive_message(buf, sizeof(buf));
          process_message(buf, len);
          send_response(resp);
     }

     return 0;
}

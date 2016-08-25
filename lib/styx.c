#include "lib9.h"

#define QID_ROOT  0
#define QID_HELLO 1

typedef struct DirectoryEntry {
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

void interpret(uchar *msg, short len)
{
    uchar type = msg[0];

    switch (type) {
    case Tversion:
        /* Tversion tag msize version == Tversion (-1) msize "9P2000" */
        uchar tag = GBIT16(&msg[1]);
        assert(tag == -1);

        /* msize is 4 bytes */
        u32int msize = GBIT32(&msg[3]);

        /* next 6 bytes is the string "9P2000" */
        char *protover
        asprintf(&protover, "%c%c%c%c%c%c", msg[7], msg[8], msg[9], msg[10], msg[11], msg[12]);

        if (strcmp(protover, "9P2000") == 0) {
            /* send Rversion */
        }
        else {
            /* send Rerror */
        }

        break;
    default:
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
        interpret(&msg[4], msgsize - 4);
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

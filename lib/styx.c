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

int msgloop(void)
{
    char buf[16];

    while (true) {
        int len = receive_message(buf, sizeof(buf));
        process_message(buf, len);
    }

    return 0;
}

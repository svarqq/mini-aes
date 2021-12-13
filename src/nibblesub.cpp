#include <unordered_map>
#include "aux.h"
#include "nibblesub.h"

unsigned short sub_blkenc(unsigned short blk) {
    unsigned short nibs[NUMNIBSINBLK];
    blktonibs(blk, nibs);
    for (int i=0; i<NUMNIBSINBLK; i++) { nibs[i] = ENCTABLE.at(nibs[i]); }
    return nibstoblk(nibs);
}

unsigned short sub_nibenc(unsigned short nibble) { return ENCTABLE.at(nibble); }

unsigned short sub_blkdec(unsigned short blk) {
    unsigned short nibs[NUMNIBSINBLK];
    blktonibs(blk, nibs);
    for (int i=0; i<NUMNIBSINBLK; i++) { nibs[i] = DECTABLE.at(nibs[i]); }
    return nibstoblk(nibs);
}

unsigned short sub_nibdec(unsigned short nibble) { return DECTABLE.at(nibble); }

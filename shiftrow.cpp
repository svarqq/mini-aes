#include "aux.h"

unsigned short shiftrow(unsigned short blk) {
    unsigned short nibs[NUMNIBSINBLK], tmp;
    blktonibs(blk, nibs);
    tmp = nibs[3];
    nibs[3] = nibs[1];
    nibs[1] = tmp;
    return nibstoblk(nibs);
}


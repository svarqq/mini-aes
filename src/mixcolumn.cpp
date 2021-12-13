#include "aux.h"
#include "mixcolumn.h"
#include <iostream>

const unsigned short MIXMAT[] = {3, 2, 2, 3};
const unsigned short DIVISOR = 19;       // 1 + x + x^4, 5 bits
unsigned short gf_mult(unsigned short, unsigned short);

unsigned short mixcolumn(unsigned short blk) {
    unsigned short nibs[NUMNIBSINBLK], mixnibs[NUMNIBSINBLK];
    blktonibs(blk, nibs);
    mixnibs[0] = gf_mult(nibs[0], MIXMAT[0]) ^ gf_mult(nibs[1], MIXMAT[2]);
    mixnibs[1] = gf_mult(nibs[0], MIXMAT[1]) ^ gf_mult(nibs[1], MIXMAT[3]);
    mixnibs[2] = gf_mult(nibs[2], MIXMAT[0]) ^ gf_mult(nibs[3], MIXMAT[2]);
    mixnibs[3] = gf_mult(nibs[2], MIXMAT[1]) ^ gf_mult(nibs[3], MIXMAT[3]);
    return nibstoblk(mixnibs);
}

unsigned short gf_mult(unsigned short nib1, unsigned short nib2) {
    // note function exploits that inputs are nibbles
    // perform polynomial multiplication
    unsigned short mult = 0;
    for (int i=0; i<NUMBITS_NIB; i++) {
        for (int j=0; j<NUMBITS_NIB; j++) {
            if ((nib1 >> i) & 1 && (nib2 >> j) & 1) {
                mult ^= (1 << (i+j));
            }
        }
    }

    // perform long division; right now mult could be 7 bits
    if ((mult >> 6) & 1) {
        mult ^= DIVISOR << 2;
    }
    if ((mult >> 5) & 1) {
        mult ^= DIVISOR << 1;
    }
    if ((mult >> 4) & 1) {
        mult ^= DIVISOR;
    }

    return mult;
}

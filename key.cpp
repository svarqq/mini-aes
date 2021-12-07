#include "aux.h"
#include "nibblesub.h"
#include "key.h"

const unsigned short RCON1 = 1;
const unsigned short RCON2 = 2;

unsigned short keyadd(unsigned short inblock, unsigned short key) {
    return inblock ^ key;
}

void genkeys(unsigned short secret_key, unsigned short outkeys[3]) {
    unsigned short key = secret_key;
    outkeys[0] = key;

    unsigned short keyarr[NUMNIBSINBLK] = {};
    blktonibs(key, keyarr);

    keyarr[0] ^= sub_nibenc(keyarr[3]) ^ RCON1;
    for (int i=1; i<NUMNIBSINBLK; i++) { keyarr[i] ^= keyarr[i-1]; }
    key = nibstoblk(keyarr);
    outkeys[1] = key;

    keyarr[0] ^= sub_nibenc(keyarr[3]) ^ RCON2;
    for (int i=1; i<NUMNIBSINBLK; i++) { keyarr[i] ^= keyarr[i-1]; }
    key = nibstoblk(keyarr);
    outkeys[2] = key;
}


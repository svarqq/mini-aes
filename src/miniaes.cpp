#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "aux.h"
#include "key.h"
#include "mixcolumn.h"
#include "nibblesub.h"
#include "shiftrow.h"

std::string encrypt(std::string plaintext, unsigned short secret_key, bool verbose) {
    const int num_blks = (int)round((float)plaintext.length()/2);
    unsigned short plaintext_blks[num_blks];
    unsigned short keys[NUMKEYS];

    text_to_blks(plaintext, plaintext_blks);
    genkeys(secret_key, keys);

    // Round 0
    for (int i=0; i<num_blks; i++) {
        plaintext_blks[i] = keyadd(plaintext_blks[i], keys[0]);
    }

    // Round 1
    for (int i=0; i<num_blks; i++) {
        plaintext_blks[i] = sub_blkenc(plaintext_blks[i]);
        plaintext_blks[i] = shiftrow(plaintext_blks[i]);
        plaintext_blks[i] = mixcolumn(plaintext_blks[i]);
        plaintext_blks[i] = keyadd(plaintext_blks[i], keys[1]);
    }

    // Round 2
    for (int i=0; i<num_blks; i++) {
        plaintext_blks[i] = sub_blkenc(plaintext_blks[i]);
        plaintext_blks[i] = shiftrow(plaintext_blks[i]);
        plaintext_blks[i] = keyadd(plaintext_blks[i], keys[2]);
    }

    return blks_to_text(plaintext_blks, num_blks);
}

std::string decrypt(std::string enctext, unsigned short secret_key, bool verbose) {
    const int num_blks = (int)round((float)enctext.length()/2);
    unsigned short enctext_blks[num_blks];
    unsigned short keys[NUMKEYS];

    text_to_blks(enctext, enctext_blks);
    genkeys(secret_key, keys);

    // Round 2 inverse
    for (int i=0; i<num_blks; i++) {
        enctext_blks[i] = keyadd(enctext_blks[i], keys[2]);
        enctext_blks[i] = shiftrow(enctext_blks[i]);
        enctext_blks[i] = sub_blkdec(enctext_blks[i]);
    }

    // Round 1 inverse
    for (int i=0; i<num_blks; i++) {
        enctext_blks[i] = keyadd(enctext_blks[i], keys[1]);
        enctext_blks[i] = mixcolumn(enctext_blks[i]);
        enctext_blks[i] = shiftrow(enctext_blks[i]);
        enctext_blks[i] = sub_blkdec(enctext_blks[i]);
    }

    // Round 0 inverse
    for (int i=0; i<num_blks; i++) {
        enctext_blks[i] = keyadd(enctext_blks[i], keys[0]);
    }

    return blks_to_text(enctext_blks, num_blks);
}




int main() {
    std::string plaintext = "Hello world!!";
    srand(time(NULL));
    unsigned short secret_key = rand() % (int)pow(2, NUMBITS_BLK);

    std::string tmp = encrypt(plaintext, secret_key, false);

    std::string tmp2 = decrypt(tmp, secret_key, false);
    

    return 0;
}

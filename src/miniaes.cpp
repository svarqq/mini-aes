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

void encrypt(unsigned short *in, unsigned short *out, bool verbose) {
    
}

void encrypt_base(unsigned short *in, unsigned short *out, bool verbose) {
    
}

int main() {
    std::string temp = "Hello world!!";
    unsigned short plaintext_blks[(int)round((float)temp.length()/2)];

    plaintext_to_blks(temp, plaintext_blks);
    

    return 0;
}

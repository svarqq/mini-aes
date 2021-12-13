#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstring>
#include <cstring>

#include "aux.h"
#include "key.h"
#include "mixcolumn.h"
#include "nibblesub.h"
#include "shiftrow.h"


unsigned short SECRET_KEY = 2666;

std::string encrypt(std::string plaintext, unsigned short secret_key) {
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

std::string decrypt(std::string enctext, unsigned short secret_key) {
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




int main(int argc, char **argv) {
    // check for legal arguments
    std::string aes_process;
    std::string aes_target;
    if (argc == 3) {
        if (strcmp(argv[1], "encrypt") == 0 || strcmp(argv[1], "decrypt") == 0) {
            aes_process = argv[1];
            aes_target = argv[2];
        } else {
            throw std::invalid_argument("First arguments must be either 'encrypt' or 'decrypt'\n"
                    "\t\tmini_aes [encrypt|decrypt] [text|filepath]");
        }
    } else {
        throw std::invalid_argument("Two arguments must be provided to mini_aes\n"
                "\t\tmini_aes [encrypt|decrypt] [text|filepath]");
    }

    // load text either as file input or argument input
    std::string intext;
    std::ifstream infile(aes_target);
    bool file_input = false;
    if (infile.is_open()) {
        file_input = true;
        intext = get_filetext(infile);
        infile.close();
    } else {
        intext = aes_target;
    }

    // encrypt or decrypt text depending on provided argument
    std::string outtext;
    if (aes_process.compare("encrypt") == 0) {
        outtext = encrypt(intext, SECRET_KEY);
    } else if (aes_process.compare("decrypt") == 0) {
        outtext = decrypt(intext, SECRET_KEY);
    }


    if (file_input) {
        std::string out_fname;
        int directory_idx = aes_target.rfind("/");
        int extension_idx = aes_target.rfind(".");
        std::cout << directory_idx << " | " << extension_idx << "\n";
        if (aes_process.compare("encrypt") == 0) {
            out_fname += "encrypted/";
            out_fname += aes_target.substr(directory_idx + 1, extension_idx-directory_idx-1);
            out_fname += ".enc";
        } else if (aes_process.compare("decrypt") == 0) {
            out_fname += "decrypted/";
            out_fname += aes_target.substr(directory_idx + 1, extension_idx-directory_idx-1);
            out_fname += ".dec";
        }
        write_file(out_fname, outtext);
        std::cout << aes_process << "ed text of '" << aes_target 
            << "' written to file '" << out_fname << "'.\n";
    } else {
        print_formatted_result(intext, outtext);
    }

    return 0;
}


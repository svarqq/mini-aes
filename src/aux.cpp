#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "aux.h"


const subtable ENCTABLE ({
    { 0, 14}, { 1,  4}, { 2, 13}, { 3,  1},
    { 4,  2}, { 5, 15}, { 6, 11}, { 7,  8},
    { 8,  3}, { 9, 10}, {10,  6}, {11, 12},
    {12,  5}, {13,  9}, {14,  0}, {15,  7}
});
const subtable DECTABLE ({
    { 0, 14}, { 1,  3}, { 2,  4}, { 3,  8},
    { 4,  1}, { 5, 12}, { 6, 10}, { 7, 15},
    { 8,  7}, { 9, 13}, {10,  9}, {11,  6},
    {12, 11}, {13,  2}, {14,  0}, {15,  5}
});
const int NUMBITS_NIB = 4;
const int NUMBITS_CHAR = 8;
const int NUMBITS_BLK = 16;
const int NUMNIBSINBLK = NUMBITS_BLK / NUMBITS_NIB;
const int NUMKEYS = 3;

void text_to_blks(std::string plaintext, unsigned short *blks) {
    for (int i=0; i<plaintext.length(); i+=2) {
        unsigned char byte1 = plaintext[i];
        if (i < plaintext.length() - 1) {
            unsigned char byte0 = plaintext[i+1];
            blks[i/2] = (unsigned short)(byte1 << NUMBITS_CHAR) + byte0;
        } else {
            blks[i/2] = (unsigned short)(byte1 << NUMBITS_CHAR);
        }
    }
}

std::string blks_to_text(unsigned short *blks, int num_blks) {
    std::string plaintext = "";
    for (int i=0; i<num_blks; i++) {
        unsigned char char1 = blks[i] >> NUMBITS_CHAR;
        unsigned char char2 = blks[i];   // retains first 8 of 16 bits
        plaintext.push_back(char1);
        if (i+1 != num_blks ||i+1 != num_blks ||  char2 != 0) {
            plaintext.push_back(char2);
        }
    }
    return plaintext;
}

void blktonibs(unsigned short blk, unsigned short outnibs[NUMNIBSINBLK]) {
    for (int i=0; i<NUMNIBSINBLK; i++) {
        outnibs[i] = (blk >> ((NUMBITS_NIB-1) - i)*NUMBITS_NIB) & (NUMBITS_BLK - 1);
    }
}

unsigned short nibstoblk(unsigned short nibs[NUMNIBSINBLK]) {
    unsigned short blk = 0;
    for (int i=0; i<NUMNIBSINBLK; i++) {
        blk ^= nibs[i] << ((NUMBITS_NIB-1) - i)*NUMBITS_NIB;
    }
    return blk;
}

std::string get_filetext(std::ifstream &file) {
    std::stringstream filebuf;
    filebuf << file.rdbuf();
    return filebuf.str();
}

void print_formatted_result(std::string intext, std::string outtext) {
    std::cout << "  ////////////////\n";
    std::cout << " // Input Text //\n";
    std::cout << "////////////////\n";
    std::cout << intext << "\n\n";
    std::cout << "  /////////////////\n";
    std::cout << " // Output Text //\n";
    std::cout << "/////////////////\n";
    std::cout << outtext << "\n";
}

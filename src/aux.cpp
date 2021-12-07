#include "aux.h"
#include <iostream>

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
const int NUMBITS_BLK = 16;
const int NUMNIBSINBLK = NUMBITS_BLK / NUMBITS_NIB;

void plaintext_to_blks(std::string plaintext, unsigned short *blks) {
    for (int i=0; i<plaintext.length(); i+=2) {
        if (i < plaintext.length() - 1) {
            blks[i/2] = (unsigned short)(plaintext[i] << NUMBITS_BLK/2) + plaintext[i+1];
        } else {
            blks[i/2] = (unsigned short)(plaintext[i] << NUMBITS_BLK/2);
        }
    }
}

std::string blks_to_plaintext(unsigned short *blks, int num_blks) {
    std::string plaintext = "";
    for (int i=0; i<num_blks; i++) {
        char char1 = (char) (blks[i] >> 8);
        char char2 = (char) (blks[i] & 255);
        plaintext.push_back(char1);
        plaintext.push_back(char2);
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


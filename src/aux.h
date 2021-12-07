#ifndef _AUX_H_
#define _AUX_H_

#include <string>
#include <unordered_map>

typedef std::unordered_map<unsigned short, unsigned short> subtable;
extern const subtable ENCTABLE;
extern const subtable DECTABLE;
extern const int NUMBITS_NIB;
extern const int NUMBITS_BLK;
extern const int NUMNIBSINBLK;

void plaintext_to_blks(std::string, unsigned short *);
void blktonibs(unsigned short, unsigned short *);
unsigned short nibstoblk(unsigned short *);

#endif


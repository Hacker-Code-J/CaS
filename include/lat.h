#include "config.h"

#ifndef _LAT_H
#define _LAT_H

static const u8 SBOX_4BIT[16] = {
    0xAU, 0x8U, 0xFU, 0x4U, 0x2U, 0x9U, 0xEU, 0xDU,
    0xCU, 0xBU, 0x6U, 0x0U, 0x5U, 0x1U, 0x3U, 0x7U
};

static const u8 INV_SBOX_4BIT[16] = {
	0xBU, 0xDU, 0x4U, 0xEU, 0x3U, 0xCU, 0xAU, 0xFU, 
	0x1U, 0x5U, 0x0U, 0x9U, 0x8U, 0x7U, 0x6U, 0x2U
};

static inline u8 dot(u8 u, u8 v) {
    u8 w = u & v;
    u8 dot = 0;

    while (w) {
        dot ^= 1;
        w &= w - 1;  // clear the least significant bit set
    }

    return dot;
}

i8 bias_integer(const u8* S, u8 alpha, u8 beta, u8 n);
i8** LAT(const u8* S, u8 n, u8 m);
void printLAT(const u8* S);

#endif /* _LAT_H */
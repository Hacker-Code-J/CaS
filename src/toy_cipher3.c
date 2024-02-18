#include "toy_cipher3.h"
#include "lat.h"

void TOY3(u8* dst, const u8* src, const u8* key) {
    u8 k1 = (*key >> 4) & 0xF;
    u8 k2 = (*key     ) & 0xF;
    u8 p1 = (*src >> 4) & 0xF;
    u8 p2 = (*src     ) & 0xF;
    u8 c1, c2, buffer1, buffer2;

    c1 = SBOX_4BIT[p1 ^ k1];
    c2 = SBOX_4BIT[p2 ^ k2];

    // printf("%X\n", (c1 << 4) | (c2 & 0xF));

    buffer1 = (((c1 >>  2) & 0b11) << 2) | ((c2 >> 2) & 0b11);
    buffer2 = (((c1      ) & 0b11) << 2) | ((c2     ) & 0b11);

    // printf("%X\n", (buffer1 << 4) | (buffer2 & 0xF));

    c1 = SBOX_4BIT[buffer1 ^ k2] ^ k1;
    c2 = SBOX_4BIT[buffer2 ^ k1] ^ k2;

    // printf("%X\n", (c1 << 4) | (c2 & 0xF));

    *dst = ((c1) << 4) | (c2 & 0xF);
}
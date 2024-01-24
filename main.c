#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "sbox_lat.h"
#include "toycipher.h"


int main() {

/*
 * CaS Study 2 (20240120)
*/

#if 1 /* Toy-cipher1 Analysis */
    u8 S_3bit[] = {0x7, 0x0, 0x6, 0x4,
		    0x5, 0x2, 0x1, 0x3};

    u8 S_4bit[] = {0xA, 0x8, 0xF, 0x4,
               0x2, 0x9, 0xE, 0xD,
               0xC, 0xB, 0x6, 0x0,
               0x5, 0x1, 0x3, 0x7};

    u8 pairs_3bit[2][2] = {
        {0x3, 0x4}, {0x5, 0x2}
    }; // {Plaintext, Ciphertext}
    size_t n_pairs_3bit = sizeof(pairs_3bit) / sizeof(pairs_3bit[0]);

    u8 pairs_4bit[2][2] = {
        {0xF, 0x3}, {0xA, 0x0}
    }; // {Plaintext, Ciphertext}
    size_t n_pairs_4bit = sizeof(pairs_4bit) / sizeof(pairs_4bit[0]);

    toy1_3bit_brute_force(S_3bit, pairs_3bit, n_pairs_3bit);
    puts("");
    toy1_4bit_brute_force(S_4bit, pairs_4bit, n_pairs_4bit);
    puts("");

    toy1_3bit_dictionary(S_3bit, pairs_3bit, n_pairs_3bit);
    puts("");
    toy1_4bit_dictionary(S_4bit, pairs_4bit, n_pairs_4bit);
    puts("");
#endif

#if 0 /* 4-bit Toy-cipher Analysis */

#endif

/*
 * CaS Study 1 (20240113)
*/

#if 0 /* 3-bit S-Box LAT */
    int S[] = {0x7, 0x0, 0x6, 0x4,
		   0x5, 0x2, 0x1, 0x3};  // Example S-box (replace with actual values)
    int n = 3;  // Example number of input bits
    int m = 3;  // Example number of output bits
#endif

#if 0 /* 4-bit S-Box LAT */
	u8 S[] = {0xA, 0x8, 0xF, 0x4,
               0x2, 0x9, 0xE, 0xD,
               0xC, 0xB, 0x6, 0x0,
               0x5, 0x1, 0x3, 0x7};  // Example S-box (replace with actual values)
    size_t n = 4;  // Example number of input bits
    size_t m = 4;  // Example number of output bits

    print_lat(S, n, m);
    // parsing_lat(S, n, m);
#endif

	return 0;
}
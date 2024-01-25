#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "sbox_lat.h"
#include "toycipher.h"

void printBinary(u8 n) {
    if (n > 1) {
        printBinary(n / 2);
    }
    printf("%d", n % 2);
}


int main() {

/*
 * CaS Study 2 (20240120)
*/
    u8 S_3bit[] = {
        0x7U, 0x0U, 0x6U, 0x4U,
		0x5U, 0x2U, 0x1U, 0x3U
    };

    u8 S_4bit[] = {
        0xAU, 0x8U, 0xFU, 0x4U,
        0x2U, 0x9U, 0xEU, 0xDU,
        0xCU, 0xBU, 0x6U, 0x0U,
        0x5U, 0x1U, 0x3U, 0x7U
    };

#if 0 /* Toy-cipher1 Analysis */
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

    // // Dynamically allocate memory for the dictionary
    // u8** dictionary_3bit = (u8**)malloc(8 * sizeof(u8*));
    // for (size_t i = 0; i < 8; i++) {
    //     dictionary_3bit[i] = (u8*)malloc(8 * sizeof(u8));
    // }

    // // Create the dictionary
    // create_dictionary(S_3bit, dictionary_3bit, 8);
    
    // // Search for the key
    // search_key(dictionary_3bit, pairs_3bit, n_pairs_3bit, 8);

    // // Free the dynamically allocated memory
    // for (size_t i = 0; i < 8; i++) {
    //     free(dictionary_3bit[i]);
    // }
    // free(dictionary_3bit);

#endif

#if 1 /* Toy-cipher2 Analysis */
    u8 pairs2_3bit[2][4] = {
        {(0x1F >> 3) & 0b111, (0x1F) & 0b111, (0x25 >> 3) & 0b111, (0x25) & 0b111},
        {(0x20 >> 3) & 0b111, (0x20) & 0b111, (0x05 >> 3) & 0b111, (0x05) & 0b111}
    }; // {Plaintext, Ciphertext}
    size_t n_pairs2_3bit = sizeof(pairs2_3bit) / sizeof(pairs2_3bit[0]);

    brute_force_toy2(S_3bit, pairs2_3bit, n_pairs2_3bit, 8);

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
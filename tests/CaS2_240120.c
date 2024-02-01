#define SHIFT_MASK(value, shift, mask) (((value) >> (shift)) & (mask))

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

#if 1 /* Toy-cipher1 Analysis */
    u8 pairs_3bit[2][2] = {
        {0x3, 0x4}, {0x5, 0x2}
    }; // {Plaintext, Ciphertext}
    size_t n_pairs_3bit = sizeof(pairs_3bit) / sizeof(pairs_3bit[0]);

    u8 pairs_4bit[2][2] = {
        {0xF, 0x3}, {0xA, 0x0}
    }; // {Plaintext, Ciphertext}
    size_t n_pairs_4bit = sizeof(pairs_4bit) / sizeof(pairs_4bit[0]);

    puts("Brute Force for 3-bit Toy-cipher1:");
    toy1_3bit_brute_force(S_3bit, pairs_3bit, n_pairs_3bit);
    puts("");

    // Dictionary generation (if applicable)
    puts("Dictionary for 3-bit Toy-cipher1:");
    u8 dictionary_3bit[8];
    toy1_3bit_dictionary(S_3bit, pairs_3bit, n_pairs_3bit, dictionary_3bit);
    puts("");

    puts("================================================================\n");

    puts("Brute Force for 4-bit Toy-cipher1:");
    toy1_4bit_brute_force(S_4bit, pairs_4bit, n_pairs_4bit);
    puts("");

    puts("Dictionary for 4-bit Toy-cipher1:");
    u8 dictionary_4bit[16];
    toy1_4bit_dictionary(S_4bit, pairs_4bit, n_pairs_4bit, dictionary_4bit);
    puts("");

    puts("================================================================\n");
#endif

#if 1 /* Toy-cipher2 Analysis */
    // u8 pairs2_3bit[2][4] = {
    //     {(0x1F >> 3) & 0b111, (0x1F) & 0b111, (0x25 >> 3) & 0b111, (0x25) & 0b111},
    //     {(0x20 >> 3) & 0b111, (0x20) & 0b111, (0x05 >> 3) & 0b111, (0x05) & 0b111}
    // }; // {Plaintext1, Plaintext2, Ciphertext1, Ciphertext2}
    u8 pairs2_3bit[2][4] = {
        {SHIFT_MASK(0x1F, 3, 0b111), SHIFT_MASK(0x1F, 0, 0b111), SHIFT_MASK(0x25, 3, 0b111), SHIFT_MASK(0x25, 0, 0b111)},
        {SHIFT_MASK(0x20, 3, 0b111), SHIFT_MASK(0x20, 0, 0b111), SHIFT_MASK(0x05, 3, 0b111), SHIFT_MASK(0x05, 0, 0b111)}
    };
    size_t n_pairs2_3bit = sizeof(pairs2_3bit) / sizeof(pairs2_3bit[0]);

    // u8 pairs2_4bit[2][4] = {
    //     {(0xDC >> 4) & 0b1111, (0xDC) & 0b1111, (0xF5 >> 4) & 0b1111, (0xF5) & 0b1111},
    //     {(0x9B >> 4) & 0b1111, (0x9B) & 0b1111, (0xE1 >> 4) & 0b1111, (0xE1) & 0b1111}
    // }; // {Plaintext1, Plaintext2, Ciphertext1, Ciphertext2}
    u8 pairs2_4bit[2][4] = {
        {SHIFT_MASK(0xDC, 4, 0b1111), SHIFT_MASK(0xDC, 0, 0b1111), SHIFT_MASK(0xF5, 4, 0b1111), SHIFT_MASK(0xF5, 0, 0b1111)},
        {SHIFT_MASK(0x9B, 4, 0b1111), SHIFT_MASK(0x9B, 0, 0b1111), SHIFT_MASK(0xE1, 4, 0b1111), SHIFT_MASK(0xE1, 0, 0b1111)}
    };
    size_t n_pairs2_4bit = sizeof(pairs2_4bit) / sizeof(pairs2_4bit[0]);

    u8 dictionary2_3bit[2 * 64]; // 2^2 + 2^4 = 20
    u8 dictionary2_4bit[2 * 256]; // 2^16 + 2^16 = 64

    puts("Brute Force for 3-bit Toy-cipher2:");
    toy2_3bit_brute_force(S_3bit, pairs2_3bit, n_pairs2_3bit);
    puts("");

    puts("Dictionary for 3-bit Toy-cipher2:");
    toy2_3bit_dictionary(S_3bit, pairs2_3bit, n_pairs2_3bit, dictionary2_3bit);
    puts("");

    puts("================================================================\n");

    puts("\nBrute Force for 4-bit Toy-cipher2:");
    toy2_4bit_brute_force(S_4bit, pairs2_4bit, n_pairs2_4bit);
    puts("");

    puts("Dictionary for 4-bit Toy-cipher2:");
    toy2_4bit_dictionary(S_4bit, pairs2_4bit, n_pairs2_4bit, dictionary2_4bit);
    puts("");

#endif
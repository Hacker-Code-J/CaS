#include "toycipher.h"
#include "utils.h"

// Brute Force Attack to find the key
void brute_force_toy1(u8* S, u8 pairs[][2], size_t n_pairs, size_t BIT) {
    u64 start, end;
    start = rdtsc();
    for (size_t key = 0; key < BIT; key++) {
        int match = 1;  // Flag to check if the key is correct for all pairs

        for (size_t i = 0; i < n_pairs; i++) {
            u8 P = pairs[i][0];
            u8 C = pairs[i][1];
            
            // Apply the relationship C = K xor SBOX(P xor K)
            if ((key ^ S[P ^ key]) != C) {
                match = 0;  // If any pair does not match, this key is not correct
                break;
            }
        }

        if (match) {
            end = rdtsc();
            // If the key is correct for all pairs, print the key
            printf("Key found: 0x%02lx\n", key);
            printf("Elapsed time: %llu cycles\n", (unsigned long long)(end - start));
            return;  // Exit the function as the key is found
        }
    }
    end = rdtsc();
    // If no key is found (which is unlikely in a properly set scenario), print a message
    printf("No key matches all the given input/output pairs.\n");
    printf("Elapsed time: %llu cycles\n", (unsigned long long)(end - start));
}

void toy1_3bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs) {
    brute_force_toy1(S, pairs, n_pairs, 8);
}

void toy1_4bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs) {
    brute_force_toy1(S, pairs, n_pairs, 16);
}

// // Function to create a dictionary mapping from input/output pairs to keys
// void createDictionary_3bit(u8 dictionary[8], u8 input[8], u8 output[8]) {
//     for (size_t key = 0; key < 8; key++) {
//         for (size_t i = 0; i < 8; i++) {
//             if (((key ^ input[i]) & 0x7) == output[i]) {
//                 dictionary[(input[i] << 3) | output[i]] = key;
//             }
//         }
//     }
// }

// // Dictionary-based search
// int dictionarySearch_3bit(u8 dictionary[8], u8 input, u8 output) {
//     return dictionary[(input << 3) | output];
// }
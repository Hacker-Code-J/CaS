#include "toycipher.h"
#include "utils.h"

// Brute Force Attack to find the key
void brute_force_toy1(u8* S, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE) {
    u64 start, end;
    start = rdtsc();
    for (size_t key = 0; key < SBOX_SIZE; key++) {
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

void toy1_3SBOX_SIZE_brute_force(u8* S, u8 pairs[][2], size_t n_pairs) {
    brute_force_toy1(S, pairs, n_pairs, 8);
}

void toy1_4SBOX_SIZE_brute_force(u8* S, u8 pairs[][2], size_t n_pairs) {
    brute_force_toy1(S, pairs, n_pairs, 16);
}

// Dictionary-based Implementation to find the key
void dictionary_toy1(u8* S, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE) {
    // Precompute the S-BOX output for each key and input
    u8 dictionary[SBOX_SIZE][SBOX_SIZE];
    for (int key = 0; key < SBOX_SIZE; key++) {
        for (int input = 0; input < SBOX_SIZE; input++) {
            dictionary[key][input] = key ^ S[input ^ key];
        }
    }

    u64 start, end;
    start = rdtsc();
    // Check for each input/output pair
    for (int key = 0; key < SBOX_SIZE; key++) {
        int match = 1;  // Flag to check if the key is correct for all pairs
        for (int i = 0; i < SBOX_SIZE; i++) {
            u8 P = pairs[i][0];
            u8 C = pairs[i][1];
            if (dictionary[key][P] != C) {
                match = 0;  // If any pair does not match, this key is not correct
                break;
            }
        }

        if (match) {
             end = rdtsc();
            // If the key is correct for all pairs, print the key
            printf("Key found: %d\n", key);
            printf("Elapsed time: %llu cycles\n", (unsigned long long)(end - start));
            return;  // Exit the function as the key is found
        }
    }
    end = rdtsc();
    // If no key is found (which is unlikely in a properly set scenario), print a message
    printf("No key matches all the given input/output pairs.\n");
    printf("Elapsed time: %llu cycles\n", (unsigned long long)(end - start));
}

void toy1_3SBOX_SIZE_dictionary(u8* S, u8 pairs[][2], size_t n_pairs) {
    dictionary_toy1(S, pairs, n_pairs, 8);
}

void toy1_4SBOX_SIZE_dictionary(u8* S, u8 pairs[][2], size_t n_pairs) {
    dictionary_toy1(S, pairs, n_pairs, 16);
}
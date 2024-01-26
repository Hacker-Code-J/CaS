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
            printf("%llu cycles\n", (unsigned long long)(end - start));
            return;  // Exit the function as the key is found
        }
    }
    end = rdtsc();
    // If no key is found (which is unlikely in a properly set scenario), print a message
    printf("No key matches all the given input/output pairs.\n");
    printf("%llu cycles\n", (unsigned long long)(end - start));
}

void toy1_3bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs) {
    brute_force_toy1(S, pairs, n_pairs, 8);
}

void toy1_4bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs) {
    brute_force_toy1(S, pairs, n_pairs, 16);
}

// Function to create the dictionary
void create_dictionary(u8* S, u8** dictionary, size_t SBOX_SIZE) {
    for (u8 key = 0; key < SBOX_SIZE; key++) {
        for (u8 p = 0; p < SBOX_SIZE; p++) {
            dictionary[key][p] = key ^ S[p ^ key];  // C = K xor SBOX(P xor K)
        }
    }

    for (size_t i = 0; i < SBOX_SIZE; i++) {
        for (size_t j = 0; j < SBOX_SIZE; j++)
            printf("0x%02x ", dictionary[i][j]);
        puts("");
    }
}

// Function to search for the key
void search_key(u8** dictionary, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE) {
    u64 start, end;
    start = rdtsc();
    
    for (u8 key = 0; key < SBOX_SIZE; key++) {
        int match = 1;  // Flag to check if the key is correct for all pairs

        for (size_t i = 0; i < n_pairs; i++) {
            u8 P = pairs[i][0];
            u8 C = pairs[i][1];

            if (dictionary[key][P ^ key] != C) {
                match = 0;  // If any pair does not match, this key is not correct
                break;
            }
        }

        if (match) {
            end = rdtsc();
            // If the key is correct for all pairs, print the key
            printf("Key found: 0x%02x\n", key);
            printf("%llu cycles\n", (unsigned long long)(end - start));
            return;  // Exit the function as the key is found
        }
    }
    end = rdtsc();
    
    // If no key is found (which is unlikely in a properly set scenario), print a message
    printf("No key matches all the given input/output pairs.\n");
    printf("%llu cycles\n", (unsigned long long)(end - start));
}

void toy1_3bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs) {
    // Dynamically allocate memory for the dictionary
    u8** dictionary = (u8**)malloc(8 * sizeof(u8*));
    for (size_t i = 0; i < 8; i++) {
        dictionary[i] = (u8*)malloc(8 * sizeof(u8));
    }

    // Create the dictionary
    create_dictionary(S, dictionary, 8);
    
    // Search for the key
    search_key(dictionary, pairs, n_pairs, 8);

    // Free the dynamically allocated memory
    for (size_t i = 0; i < 8; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
}
void toy1_4bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs) {
    // Dynamically allocate memory for the dictionary
    u8** dictionary = (u8**)malloc(16 * sizeof(u8*));
    for (size_t i = 0; i < 16; i++) {
        dictionary[i] = (u8*)malloc(16 * sizeof(u8));
    }

    // Create the dictionary
    create_dictionary(S, dictionary, 16);
    
    // Search for the key
    search_key(dictionary, pairs, n_pairs, 16);

    // Free the dynamically allocated memory
    for (size_t i = 0; i < 16; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
}

/*
 * C1 = SBOX(P1 xor K1) xor K2
 * C2 = SBOX(P2 xor K2) xor SBOX(P1 xor K1) xor K1
*/
void brute_force_toy2(u8* S, u8 pairs[][4], size_t n_pairs, size_t SBOX_SIZE) {
    u64 start, end;
    
    start = rdtsc();
    for (size_t k1 = 0; k1 < SBOX_SIZE; k1++) {
        for (size_t k2 = 0; k2 < SBOX_SIZE; k2++) {
            int match = 1;  // Flag to check if the keys are correct for all pairs

            for (size_t i = 0; i < n_pairs; i++) {
                u8 P1 = pairs[i][0];
                u8 P2 = pairs[i][1];
                u8 C1 = pairs[i][2];
                u8 C2 = pairs[i][3];
                
                // Apply the modified relationships for both pairs
                if ((S[P1 ^ k1] ^ k2) != C1 ||
                    (S[P2 ^ k2] ^ S[P1 ^ k1] ^ k1) != C2) {
                    match = 0;  // If any pair does not match, these keys are not correct
                    break;
                }
            }

            i8 shift = (SBOX_SIZE == 8) ? 3 : 4;
            if (match) {
                end = rdtsc();
                // If the keys are correct for all pairs, print the keys
                printf("Keys found: K1 = 0x%02lx, K2 = 0x%02lx and so K = 0x%02lx\n", k1, k2, (k1 << shift) | k2);
                printf("%llu cycles\n", (unsigned long long)(end - start));
                return;  // Exit the function as the keys are found
            }
        }
    }
    end = rdtsc();
    // If no keys are found (which is unlikely in a properly set scenario), print a message
    printf("No key pairs match all the given input/output pairs.\n");
    printf("%llu cycles\n", (unsigned long long)(end - start));
}

void toy2_3bit_brute_force(u8* S, u8 pairs[][4], size_t n_pairs) {
    brute_force_toy2(S, pairs, n_pairs, 8);
}
void toy2_4bit_brute_force(u8* S, u8 pairs[][4], size_t n_pairs) {
    brute_force_toy2(S, pairs, n_pairs, 16);
}
#include "toycipher.h"
#include "utils.h"

/*
 * C = K xor SBOX(P xor K)
*/
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

void generate_dictionary(u8* dictionary, size_t* dict_size, size_t SBOX_SIZE) {
    size_t index = 0;
    for (size_t key = 0; key < SBOX_SIZE; key++) {
        // Assume we have a function `is_valid_key` that checks if the key meets certain criteria
        // if (is_valid_key(key)) {
        //     dictionary[index++] = key;
        // }
        dictionary[index++] = key;
    }
    *dict_size = index;
}

void dictionary_attack_toy1(u8* S, u8 pairs[][2], size_t n_pairs, u8* dictionary, size_t dict_size) {
    generate_dictionary(dictionary, &dict_size, dict_size);
    
    u64 start, end;
    start = rdtsc();
    for (size_t index = 0; index < dict_size; index++) {
        u8 key = dictionary[index];
        int match = 1;

        for (size_t i = 0; i < n_pairs; i++) {
            u8 P = pairs[i][0];
            u8 C = pairs[i][1];
            
            // Assuming S is a precomputed SBOX
            u8 SBOX_result = S[P ^ key];

            // Apply the relationship C = K xor SBOX(P xor K)
            if ((key ^ SBOX_result) != C) {
                match = 0;
                break;
            }
        }

        if (match) {
            end = rdtsc();
            printf("Key found: 0x%02x\n", key);
            printf("%llu cycles\n", (unsigned long long)(end - start));
            return;
        }
    }

    end = rdtsc();   
    printf("No key matches all the given input/output pairs.\n");
    printf("%llu cycles\n", (unsigned long long)(end - start));
}

void toy1_3bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs, u8* dictionary) {
    dictionary_attack_toy1(S, pairs, n_pairs, dictionary, 8);
}

void toy1_4bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs, u8* dictionary) {
    dictionary_attack_toy1(S, pairs, n_pairs, dictionary, 16);
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

void generate_dictionary2(u8* dictionary, size_t* dict_size, size_t SBOX_SIZE) {
    size_t index = 0;
    size_t max_index = SBOX_SIZE * SBOX_SIZE;  // Maximum number of key pairs
    u8 shift = (SBOX_SIZE == 8) ? 3 : 4;
    for (size_t k1 = 0; k1 < ((SBOX_SIZE == 8) ? 4 : 32); k1++) {
        for (size_t k2 = 0; k2 < 16; k2++) {
            if (index >= max_index) {
                break;  // Prevent buffer overflow
            }

            // printf("k1: %2lx, k2: %2lx K: %2lx\n", k1, k2, (k1 << shift) | k2);
            // if (((k1 << shift) | k2) == 0xF0) {
            //     printf("0xF0 is included at index %zu\n", index);
            // }

            dictionary[index++] = (k1 << shift) | k2;
        }
    }
    *dict_size = index;
}

void dictionary_attack_toy2(u8* S, u8 pairs[][4], size_t n_pairs, u8* dictionary, size_t SBOX_SIZE) {
    size_t dict_size = SBOX_SIZE * SBOX_SIZE;
    i8 shift = (SBOX_SIZE == 8) ? 3 : 4;
    i8 mask = (SBOX_SIZE == 8) ? 0b111 : 0b1111;
    generate_dictionary2(dictionary, &dict_size, SBOX_SIZE);
    
    u64 start, end;
    start = rdtsc();
    
    for (size_t index = 0; index < dict_size; index++) {
        u8 k1 = (dictionary[index] >> shift) & mask;
        u8 k2 = dictionary[index] & mask;
        int match = 1;

        for (size_t i = 0; i < n_pairs; i++) {
            u8 P1 = pairs[i][0];
            u8 P2 = pairs[i][1];
            u8 C1 = pairs[i][2];
            u8 C2 = pairs[i][3];
            
            // Apply the modified relationships for both pairs
            if ((S[P1 ^ k1] ^ k2) != C1 ||
                (S[P2 ^ k2] ^ S[P1 ^ k1] ^ k1) != C2) {
                match = 0;
                break;
            }
        }

        if (match) {
            end = rdtsc();
            printf("Keys found: K1 = 0x%02x, K2 = 0x%02x and so K = 0x%02x\n", k1, k2, (k1 << shift) | k2);
            printf("%llu cycles\n", (unsigned long long)(end - start));
            return;
        }
    }
    end = rdtsc();   
    printf("No key pairs match all the given input/output pairs.\n");
    printf("%llu cycles\n", (unsigned long long)(end - start));
}

void toy2_3bit_dictionary(u8* S, u8 pairs[][4], size_t n_pairs, u8* dictionary) {
    dictionary_attack_toy2(S, pairs, n_pairs, dictionary, 8);
}
void toy2_4bit_dictionary(u8* S, u8 pairs[][4], size_t n_pairs, u8* dictionary) {
    dictionary_attack_toy2(S, pairs, n_pairs, dictionary, 16);
}
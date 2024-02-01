#include "config.h"

/* ToyCipher1 - Brute Force */
void brute_force_toy1(u8* S, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE);

void toy1_3bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs);
void toy1_4bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs);

/* ToyCipher1 - Dictionary*/
void generate_dictionary(u8* dictionary, size_t* dict_size, size_t SBOX_SIZE);
void dictionary_attack_toy1(u8* S, u8 pairs[][2], size_t n_pairs, u8* dictionary, size_t dict_size);

void toy1_3bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs, u8* dictionary);
void toy1_4bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs, u8* dictionary);

/* ToyCipher2 - Brute Force */
void brute_force_toy2(u8* S, u8 pairs[][4], size_t n_pairs, size_t SBOX_SIZE);

void toy2_3bit_brute_force(u8* S, u8 pairs[][4], size_t n_pairs);
void toy2_4bit_brute_force(u8* S, u8 pairs[][4], size_t n_pairs);

/* ToyCipher2 - Dictionary*/
void generate_dictionary2(u8* dictionary, size_t* dict_size, size_t SBOX_SIZE);
void dictionary_attack_toy2(u8* S, u8 pairs[][4], size_t n_pairs, u8* dictionary, size_t SBOX_SIZE);

void toy2_3bit_dictionary(u8* S, u8 pairs[][4], size_t n_pairs, u8* dictionary);
void toy2_4bit_dictionary(u8* S, u8 pairs[][4], size_t n_pairs, u8* dictionary);

#include "config.h"

void brute_force_toy1(u8* S, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE);

void toy1_3SBOX_SIZE_brute_force(u8* S, u8 pairs[][2], size_t n_pairs);
void toy1_4SBOX_SIZE_brute_force(u8* S, u8 pairs[][2], size_t n_pairs);

void dictionary_toy1(u8* S, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE);

void toy1_3SBOX_SIZE_dictionary(u8* S, u8 pairs[][2], size_t n_pairs);
void toy1_4SBOX_SIZE_dictionary(u8* S, u8 pairs[][2], size_t n_pairs);
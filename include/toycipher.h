#include "config.h"

void brute_force_toy1(u8* S, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE);

void toy1_3bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs);
void toy1_4bit_brute_force(u8* S, u8 pairs[][2], size_t n_pairs);

// Function to create the dictionary
void create_dictionary(u8* S, u8** dictionary, size_t SBOX_SIZE);
void search_key(u8** dictionary, u8 pairs[][2], size_t n_pairs, size_t SBOX_SIZE);

void toy1_3bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs);
void toy1_4bit_dictionary(u8* S, u8 pairs[][2], size_t n_pairs);

void brute_force_toy2(u8* S, u8 pairs[][4], size_t n_pairs, size_t SBOX_SIZE);
#include "config.h"
#include "linear_analysis.h"

// Function to calculate the parity of a number
int parity(int n) {
    int count = 0;
    while (n) {
        count ^= n & 1;
        n >>= 1;
    }
    return count;
}

// Function to generate the LAT
void GEN_LAT(u8 SBOX[SBOX_SIZE], u8 LAT[SBOX_SIZE][SBOX_SIZE]) {
    for (int input_mask = 0; input_mask < SBOX_SIZE; input_mask++) {
        for (int output_mask = 0; output_mask < SBOX_SIZE; output_mask++) {
            int count = 0;
            for (int x = 0; x < SBOX_SIZE; x++) {
                if (parity(x & input_mask) == parity(SBOX[x] & output_mask)) {
                    count++;
                }
            }
            LAT[input_mask][output_mask] = count - 8; // Adjusting for bias
        }
    }
}
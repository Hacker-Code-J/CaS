#include <stdio.h>
#include <stdint.h>

#include "config.h"
#include "linear_analysis.h"

int main() {
    // Define the S-box according to the given rules
    u8 SBOX[SBOX_SIZE] = {0xA, 0x8, 0xF, 0x4, 0x2, 0x9, 0xE, 0xD, 0xC, 0xB, 0x6, 0x0, 0x5, 0x1, 0x3, 0x7};

    u8 LAT[SBOX_SIZE][SBOX_SIZE];
    GEN_LAT(SBOX, LAT);

    // Print the LAT
    // printf("Linear Approximation Table (LAT):\n");
    for (int i = 0; i < SBOX_SIZE; i++) {
        for (int j = 0; j < SBOX_SIZE; j++) {
            printf("%02x ", LAT[i][j]);
        }
        printf("\n");
    }

    // Print the LAT with indices
    // printf("Linear Approximation Table (LAT):\n");
    // printf("   | ");
    // for (int i = 0; i < SBOX_SIZE; i++) {
    //     printf("%02X ", i);
    // }
    // printf("\n   -------------------------------------------------\n");

    // for (int i = 0; i < SBOX_SIZE; i++) {
    //     printf("%02X | ", i);
    //     for (int j = 0; j < SBOX_SIZE; j++) {
    //         printf("%02X ", LAT[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}
#include "utils.h"
#include "toycipher2.h"

// Function to check if the expressions for K1 and K2 are equal
bool checkExpressions(u8 K) {
    u8 K1 = (K >> 4) & 0xF;  // Extract the higher 4 bits
    u8 K2 = K & 0xF;         // Extract the lower 4 bits

    // Compute the expression for K1
    u8 exprK1 = ((K1 >> 3) & 1) ^  // K1[3]
                 ((K1 >> 2) & 1) ^  // K1[2]
                 (~(K1 >> 1) & 1) ^ // NOT K1[1]
                 (K1 & 1);          // K1[0]

    // Compute the expression for K2
    u8 exprK2 = ((K2 >> 3) & 1) ^   // K2[3]
                 ((K2 >> 2) & 1) ^   // K2[2]
                 (~(K2 >> 1) & 1) ^  // NOT K2[1]
                 (~(K2 & 1) & 1);    // NOT K2[0]

    return exprK1 == exprK2;
}

int main() {
    // print_SBOX2_LAT();
    visual_SBOX2_LAT();
    
    // puts("");
    // for (int K = 0; K < (1 << 8); ++K) {
    //     if (checkExpressions(K)) {
    //         printf("K = %02X\n", K);
    //     }
    // }
	return 0;
}
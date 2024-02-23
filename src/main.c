#include "lat.h"
#include "toy_cipher3.h"

// // Function to check if the expressions for K1 and K2 are equal
// bool checkExpressions(u8 K) {
//     u8 K1 = (K >> 4) & 0xF;  // Extract the higher 4 bits
//     u8 K2 = K & 0xF;         // Extract the lower 4 bits

//     // Compute the expression for K1
//     u8 exprK1 = ((K1 >> 3) & 1) ^  // K1[3]
//                  ((K1 >> 2) & 1) ^  // K1[2]
//                  (~(K1 >> 1) & 1) ^ // NOT K1[1]
//                  (K1 & 1);          // K1[0]

//     // Compute the expression for K2
//     u8 exprK2 = ((K2 >> 3) & 1) ^   // K2[3]
//                  ((K2 >> 2) & 1) ^   // K2[2]
//                  (~(K2 >> 1) & 1) ^  // NOT K2[1]
//                  (~(K2 & 1) & 1);    // NOT K2[0]

//     return exprK1 == exprK2;
// }

int main(int argc, char** argv) {
    // printLAT(SBOX_4BIT);

    u8 input1 = 0xDC, output1 = 0xB3;
    u8 input2 = 0x9B, output2 = 0xD9;
    u8 key = 0x00;

    u8 dst1 = 0;
    u8 dst2 = 0;

    // u8 test_key = 0xA2;
    // TOY3(&dst1, &input1, &test_key);
    // printf("%x\n", dst1);
    u32 ui;
    u64 start, end;
    start = __rdtsc();
    for (u32 idx = 0; idx < 0x100; idx++) {
        // printf("Loop 0x%X\n", idx);
        TOY3(&dst1, &input1, &key);
        TOY3(&dst2, &input2, &key);
        if (dst1 == output1) {
            printf("Good Key: %02X\n", key);
            if (dst2 == output2) { 
                printf("Perfect Key: %02X\n", key);
            } else {
                printf("Wrong!\n");
            }
        }
        key++;
    }
    end = __rdtscp(&ui);
    printf("cycle:%" PRIu64 "\n", end-start);
#if 0
    u8 i = 1;
    for (int K = 0; K < (1 << 8); ++K) {
        if (checkExpressions(K)) {
            printf("%03d | K = %02X\n", i++, K);
        }
    }
#endif
	return 0;
}
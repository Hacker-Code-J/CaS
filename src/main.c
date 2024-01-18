#include <stdio.h>

#define MAX_EXPRESSIONS 100 // Maximum number of expressions

// Global variables
int expressions[MAX_EXPRESSIONS][6];
int idx = 0;

// Modified findCombinations function
void findCombinations(int x[], int y[], int sumX, int sumY, int index) {
    if (index == 3) {
        if (sumX == sumY && sumX > 0) {
            expressions[idx][0] = x[0];
            expressions[idx][1] = x[1];
            expressions[idx][2] = x[2];
            expressions[idx][3] = y[0];
            expressions[idx][4] = y[1];
            expressions[idx][5] = y[2];
            idx++;
        }
        return;
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            x[index] = i;
            y[index] = j;
            findCombinations(x, y, sumX + i, sumY + j, index + 1);
        }
    }
}

int main() {

// Initialize the variables
    int x2 = 1, x1 = 1, x0 = 0;
    int y2 = 0, y1 = 0, y0 = 1;
    
    // Loop through all combinations of coefficients a2, a1, b0
    for (int i = 0; i < 8; i++) { // Only need 8 combinations now
        // Extract the bits of i to use as coefficients
        int a2 = (i & 4) >> 2;
        int a1 = (i & 2) >> 1;
        int b0 = i & 1;
        
        // Check if at least one x and one y are present
        if ((a2 == 0 && a1 == 0) || b0 == 0) {
            // Skip this combination if it doesn't include at least one x and one y
            continue;
        }
        
        // Compute the linear expression parts
        int xPart = (a2 & x2) ^ (a1 & x1);
        int yPart = (b0 & y0);
        
        // Prepare strings to represent the x and y parts
        char xString[5] = "";
        if (a2) strcat(xString, "x2 ");
        if (a1) strcat(xString, "x1 ");
        char yString[5] = "y0 "; // yString is always "y0 " because y1 and y2 are 0
        
        // Print the equation
        printf("%s= %s(Result: %d)\n", xString, yString, xPart ^ yPart);
    }
    
    return 0;

#if 0
    // Define the 3-bit plaintext to ciphertext mapping
    int mapping[8][2] = {
        {0b000, 0b111}, // 000 -> 111
        {0b001, 0b000}, // 001 -> 000
        {0b010, 0b110}, // 010 -> 110
        {0b011, 0b100}, // 011 -> 100
        {0b100, 0b101}, // 100 -> 101
        {0b101, 0b010}, // 101 -> 010
        {0b110, 0b001}, // 110 -> 001
        {0b111, 0b011}  // 111 -> 011
    };

    // Initialize variables
    int x[3] = {0};
    int y[3] = {0};

    // Generate expressions
    findCombinations(x, y, 0, 0, 0);

    // Use the expressions array as needed
    // Example: print the generated expressions
    for (int i = 0; i < idx; i++) {
        printf("%02d: (%d, %d, %d, %d, %d, %d)\n", i, expressions[i][0], expressions[i][1], expressions[i][2], expressions[i][3], expressions[i][4], expressions[i][5]);
    }

    // Further processing, such as evaluating these expressions against mappings, can be done here

    // Iterate over each expression
    for (int i = 0; i < 19; i++) {
        int correctCount = 0;

        // Iterate over all mappings
        for (int j = 0; j < 8; j++) {
            int x[3] = { (mapping[j][0] >> 2) & 1, (mapping[j][0] >> 1) & 1, mapping[j][0] & 1 };
            int y[3] = { (mapping[j][1] >> 2) & 1, (mapping[j][1] >> 1) & 1, mapping[j][1] & 1 };
            int lhs = x[0] * expressions[i][0] + x[1] * expressions[i][1] + x[2] * expressions[i][2];
            int rhs = y[0] * expressions[i][3] + y[1] * expressions[i][4] + y[2] * expressions[i][5];

            if (lhs == rhs) {
                correctCount++;
            }
        }

        // Print the number of times the expression is correct for all mappings
        printf("Expression %d is correct %d times\n", i, correctCount);
    }

    return 0;
#endif
}

#if 0
#include <stdio.h>
#include <stdint.h>

#include "config.h"
#include "linear_analysis.h"

int idx = 0;

void findCombinations(int x[], int y[], int sumX, int sumY, int index, int maxX, int maxY) {
    if (index == 3) { // Base case: 3 digits processed
        if (sumX == sumY && sumX > 0) { // Check if valid combination
            printf("%02d: (%d, %d, %d, %d, %d, %d)\n", idx++, x[0], x[1], x[2], y[0], y[1], y[2]);
        }
        return;
    }
    // Recursive case: try all combinations for current index
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            x[index] = i;
            y[index] = j;
            findCombinations(x, y, sumX + i, sumY + j, index + 1, maxX, maxY);
        }
    }
}

// Function to evaluate direct assignment and negation expressions
int evaluate_expression(int x, int y, int is_negation) {
    return is_negation ? (x != y) : (x == y);
}

int main() {
    // Define the S-box according to the given rules
    // u8 SBOX[SBOX_SIZE] = {0xA, 0x8, 0xF, 0x4, 0x2, 0x9, 0xE, 0xD, 0xC, 0xB, 0x6, 0x0, 0x5, 0x1, 0x3, 0x7};
    u8 SBOX[SBOX_SIZE] = {0x7, 0x0, 0x6, 0x4, 0x5, 0x2, 0x1, 0x3};

    u8 LAT[SBOX_SIZE][SBOX_SIZE];
    construct_LAT(SBOX, LAT);

    // Print the LAT
    // printf("Linear Approximation Table (LAT):\n");
    for (int i = 0; i < SBOX_SIZE; i++) {
        for (int j = 0; j < SBOX_SIZE; j++) {
            printf("%03d ", LAT[i][j]);
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

    // Define the 3-bit plaintext to ciphertext mapping
    int mapping[8][2] = {
        {0b000, 0b111}, // 000 -> 111
        {0b001, 0b000}, // 001 -> 000
        {0b010, 0b110}, // 010 -> 110
        {0b011, 0b100}, // 011 -> 100
        {0b100, 0b101}, // 100 -> 101
        {0b101, 0b010}, // 101 -> 010
        {0b110, 0b001}, // 110 -> 001
        {0b111, 0b011}  // 111 -> 011
    };

    // int correctCount = 0;

    // // Evaluate the expression x1 = y1 + 1 for each mapping
    // for (int i = 0; i < 8; i++) {
    //     int x = mapping[i][0]; // plaintext
    //     int y = mapping[i][1]; // ciphertext

    //     // Extract bits x1 and y1
    //     int x1 = (x >> 1) & 1;
    //     int y1 = (y >> 1) & 1;

    //     // Check if the expression x1 = y1 + 1 is correct
    //     if (x1 == ((y1 + 1) % 2)) {
    //         correctCount++;
    //     }
    // }

    // // Print the number of times the expression is correct
    // printf("Expression 'x1 = y1 + 1' is correct %d times\n", correctCount);

    // Iterate over all combinations of x2, x1, x0, y2, y1, y0
    for (int x2 = 0; x2 <= 1; x2++) {
        for (int x1 = 0; x1 <= 1; x1++) {
            for (int x0 = 0; x0 <= 1; x0++) {
                for (int y2 = 0; y2 <= 1; y2++) {
                    for (int y1 = 0; y1 <= 1; y1++) {
                        for (int y0 = 0; y0 <= 1; y0++) {
                            // Check if the equation holds
                            if (x2 + x1 + x0 == y2 + y1 + y0) {
                                // Print the combination
                                printf("(%d, %d, %d, %d, %d, %d)\n", x2, x1, x0, y2, y1, y0);
                            }
                        }
                    }
                }
            }
        }
    }
    int idx = 0;
    printf("\nNew:\n");
    // Iterate over all combinations of x2, x1, x0, y2, y1, y0
    for (int x2 = 0; x2 <= 1; x2++) {
        for (int x1 = 0; x1 <= 1; x1++) {
            for (int x0 = 0; x0 <= 1; x0++) {
                for (int y2 = 0; y2 <= 1; y2++) {
                    for (int y1 = 0; y1 <= 1; y1++) {
                        for (int y0 = 0; y0 <= 1; y0++) {
                            // Ensure at least one of x and y is 1
                            if ((x2 + x1 + x0 > 0) && (y2 + y1 + y0 > 0)) {
                                // Check if the equation holds
                                if (x2 + x1 + x0 == y2 + y1 + y0) {
                                    // Print the combination
                                    printf("%2d: (%d, %d, %d, %d, %d, %d)\n", idx++, x2, x1, x0, y2, y1, y0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    idx = 0;
    printf("\nNew Fn:\n");
    int x[3] = {0}, y[3] = {0};
    findCombinations(x, y, 0, 0, 0, 3, 3);

    // Define the expressions
    int expressions[19][6] = {
        {0, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 1, 0}, {0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 0, 1}, {0, 1, 0, 0, 1, 0}, {0, 1, 0, 1, 0, 0},
        {0, 1, 1, 0, 1, 1}, {0, 1, 1, 1, 0, 1}, {0, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 1}, {1, 0, 1, 1, 0, 1}, {1, 0, 1, 1, 1, 0},
        {1, 1, 0, 0, 1, 1}, {1, 1, 0, 1, 0, 1}, {1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1}
    };

    // Iterate over each expression
    for (int i = 0; i < 19; i++) {
        int correctCount = 0;

        // Iterate over all mappings
        for (int j = 0; j < 8; j++) {
            int x[3] = { (mapping[j][0] >> 2) & 1, (mapping[j][0] >> 1) & 1, mapping[j][0] & 1 };
            int y[3] = { (mapping[j][1] >> 2) & 1, (mapping[j][1] >> 1) & 1, mapping[j][1] & 1 };
            int lhs = x[0] * expressions[i][0] + x[1] * expressions[i][1] + x[2] * expressions[i][2];
            int rhs = y[0] * expressions[i][3] + y[1] * expressions[i][4] + y[2] * expressions[i][5];

            if (lhs == rhs) {
                correctCount++;
            }
        }

        // Print the number of times the expression is correct for all mappings
        printf("Expression %d is correct %d times\n", i, correctCount);
    }

    return 0;
}
#endif
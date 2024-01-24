#include "utils.h"
#include "sbox_lat.h"

void print_lat(u8* S, u8 n, u8 m) {
    u8 n_range = 1 << n;
    u8 m_range = 1 << m;
    i8** L = lat(S, n, m);

    // Pru8 column headers
    printf("     "); // Space for row header
    for (u8 beta = 0; beta < m_range; beta++) {
        printf("%02X ", beta);
    }
    printf("\n");

    // Pru8 a separator line
    printf("   +"); // Alignment for row header
    for (u8 beta = 0; beta < m_range; beta++) {
        printf("---");
    }
    printf("\n");

    for (u8 alpha = 0; alpha < n_range; alpha++) {
        // Pru8 row header
        printf("%02X | ", alpha);

        for (u8 beta = 0; beta < m_range; beta++) {
            printf("%2d ", L[alpha][beta]);  // Right-align numbers in a field of width 2
        }
        printf("\n");

        // Free memory for each row
        free(L[alpha]);
    }

    // Free the top-level pou8er
    free(L);
}

void parsing_lat(u8* S, u8 n, u8 m) {
    u8 n_range = 1 << n;
    u8 m_range = 1 << m;
    i8** L = lat(S, n, m);
    for (u8 alpha = 0; alpha < n_range; alpha++) {
        for (u8 beta = 0; beta < m_range; beta++) {
            printf("%2d ", L[alpha][beta]);  // Right-align numbers in a field of width 2
        }
        printf("\n");

        // Free memory for each row
        free(L[alpha]);
    }

    // Free the top-level pou8er
    free(L);
}
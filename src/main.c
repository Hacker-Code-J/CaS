#include <stdio.h>
#include <stdlib.h>

int dot(int u, int v) {
    int w = u & v;
    int dot = 0;

    // Using Kernighan's algorithm to count the number of set bits
    while (w) {
        dot ^= 1;
        w &= w - 1;  // clear the least significant bit set
    }

    return dot;
}

int success(int* S, int alpha, int beta, int n) {
	int e = 0;
	int range = 1 << n;  // 2 ** n
	
	for (int x = 0; x < range; x++) {
		if ((dot(alpha, x) ^ dot(beta, S[x])) == 0) {
			e++;
		}
	}
	
	return e;
}

int bias_integer(int* S, int alpha, int beta, int n) {
	int e = 0;
	int range = 1 << n;  // 2 ** n
	
	for (int x = 0; x < range; x++) {
		if ((dot(alpha, x) ^ dot(beta, S[x])) == 0) {
			e++;
		}
	}
	
	return e - (range >> 1);  // range / 2 or 2 ** (n - 1)
}

int** lat(int* S, int n, int m) {
	int n_range = 1 << n;
	int m_range = 1 << m;
	
	// Dynamically allocate 2D array
	int** L = (int**)malloc(n_range * sizeof(int*));
	for (int i = 0; i < n_range; i++) {
		L[i] = (int*)malloc(m_range * sizeof(int));
	}
	
	// Compute the LAT
	for (int alpha = 0; alpha < n_range; alpha++) {
		for (int beta = 0; beta < m_range; beta++) {
			L[alpha][beta] = success(S, alpha, beta, n);
			// L[alpha][beta] = bias_integer(S, alpha, beta, n);
		}
	}
	
	return L;
}

void print_lat(int* S, int n, int m) {
    int n_range = 1 << n;
    int m_range = 1 << m;
    int** L = lat(S, n, m);

    // Print column headers
    printf("     "); // Space for row header
    for (int beta = 0; beta < m_range; beta++) {
        printf("%02X ", beta);
    }
    printf("\n");

    // Print a separator line
    printf("   +"); // Alignment for row header
    for (int beta = 0; beta < m_range; beta++) {
        printf("---");
    }
    printf("\n");

    for (int alpha = 0; alpha < n_range; alpha++) {
        // Print row header
        printf("%02X | ", alpha);

        for (int beta = 0; beta < m_range; beta++) {
            printf("%02d ", L[alpha][beta]);  // Right-align numbers in a field of width 2
        }
        printf("\n");

        // Free memory for each row
        free(L[alpha]);
    }

    // Free the top-level pointer
    free(L);
}

int main() {
#if 0
    int S[] = {0x7, 0x0, 0x6, 0x4,
		   0x5, 0x2, 0x1, 0x3};  // Example S-box (replace with actual values)
    int n = 3;  // Example number of input bits
    int m = 3;  // Example number of output bits
#endif
#if 1
	int S[] = {0xA, 0x8, 0xF, 0x4,
               0x2, 0x9, 0xE, 0xD,
               0xC, 0xB, 0x6, 0x0,
               0x5, 0x1, 0x3, 0x7};  // Example S-box (replace with actual values)
    int n = 4;  // Example number of input bits
    int m = 4;  // Example number of output bits
#endif
    print_lat(S, n, m);
	
	return 0;
}
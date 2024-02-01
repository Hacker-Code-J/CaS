#include "toycipher2.h"

i8 bias_integer(const u8* S, u8 alpha, u8 beta, u8 n) {
    u8 e = 0;
	u8 range = 1 << n;  // 2 ** n
	
	for (u8 x = 0; x < range; x++) {
		if ((dot(alpha, x) ^ dot(beta, S[x])) == 0) {
			e++;
		}
	}
	
	return e - (range >> 1);  // range / 2 or 2 ** (n - 1)
}
i8** LAT(const u8* S, u8 n, u8 m) {
    u8 n_range = 1 << n;
	u8 m_range = 1 << m;
	
	// Dynamically allocate 2D array
	i8** L = (i8**)malloc(n_range * sizeof(i8*));
	for (u8 i = 0; i < n_range; i++) {
		L[i] = (i8*)malloc(m_range * sizeof(i8));
	}
	
	// Compute the LAT
	for (u8 alpha = 0; alpha < n_range; alpha++) {
		for (u8 beta = 0; beta < m_range; beta++) {
			// L[alpha][beta] = success(S, alpha, beta, n);
			L[alpha][beta] = bias_integer(S, alpha, beta, n);
		}
	}
	
	return L;
}

void print_SBOX2_LAT(void) {
    u8 n = 4;
    u8 m = 4;
    u8 n_range = 1 << n;
    u8 m_range = 1 << m;
    i8** L = LAT(SBOX2, n, m);

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

// Function to add an index to the list
void addIndex(Index** list, u8 alpha, u8 beta, int* size, int* capacity) {
    if (*size >= *capacity) {
        *capacity *= 2;
        *list = (Index*)realloc(*list, (*capacity) * sizeof(Index));
    }
    (*list)[*size].alpha = alpha;
    (*list)[*size].beta = beta;
    (*size)++;
}

// Function to find all indices with max absolute value
Index* findAllMaxAbsIndices(const u8* S, u8 n, u8 m, int* count) {
    i8** L = LAT(S, n, m); // Generate the table
    u8 n_range = 1 << n;
    u8 m_range = 1 << m;
    i8 max_abs_value = 0;

    // First pass: Find the max absolute value
    for (u8 alpha = 0; alpha < n_range; alpha++) {
        for (u8 beta = 0; beta < m_range; beta++) {
            if (abs(L[alpha][beta]) > abs(max_abs_value)) {
                max_abs_value = abs(L[alpha][beta]);
            }
        }
    }

    // Second pass: Collect all indices with the max absolute value
    int capacity = 10; // Initial capacity
    Index* indices = (Index*)malloc(capacity * sizeof(Index));
    *count = 0;
    for (u8 alpha = 0; alpha < n_range; alpha++) {
        for (u8 beta = 0; beta < m_range; beta++) {
            if (abs(L[alpha][beta]) == max_abs_value) {
                addIndex(&indices, alpha, beta, count, &capacity);
            }
        }
    }

    // Free allocated memory for L
    for (u8 i = 0; i < n_range; i++) {
        free(L[i]);
    }
    free(L);

    return indices;
}

void findIdx(void) {
    int count;

    Index* indices = findAllMaxAbsIndices(SBOX2, 4, 4, &count);
    printf("Indices with max abs value:\n");
    for (int i = 0; i < count; i++) {
        printf("[%u][%u]\n", indices[i].alpha, indices[i].beta);
    }

    free(indices); // Free allocated memory for indices
}
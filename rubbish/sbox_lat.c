#include "sbox_lat.h"

u8 dot(u8 u, u8 v) {
    u8 w = u & v;
    u8 dot = 0;

    // Using Kernighan's algorithm to count the number of set bits
    while (w) {
        dot ^= 1;
        w &= w - 1;  // clear the least significant bit set
    }

    return dot;
}

u8 success(u8* S, u8 alpha, u8 beta, u8 n) {
	u8 e = 0;
	u8 range = 1 << n;  // 2 ** n
	
	for (u8 x = 0; x < range; x++) {
		if ((dot(alpha, x) ^ dot(beta, S[x])) == 0) {
			e++;
		}
	}
	
	return e;
}

i8 bias_integer(u8* S, u8 alpha, u8 beta, u8 n) {
	u8 e = 0;
	u8 range = 1 << n;  // 2 ** n
	
	for (u8 x = 0; x < range; x++) {
		if ((dot(alpha, x) ^ dot(beta, S[x])) == 0) {
			e++;
		}
	}
	
	return e - (range >> 1);  // range / 2 or 2 ** (n - 1)
}

i8** lat(u8* S, u8 n, u8 m) {
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
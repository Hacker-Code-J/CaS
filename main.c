#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "sbox_lat.h"

int main() {
#if 0
    int S[] = {0x7, 0x0, 0x6, 0x4,
		   0x5, 0x2, 0x1, 0x3};  // Example S-box (replace with actual values)
    int n = 3;  // Example number of input bits
    int m = 3;  // Example number of output bits
#endif
#if 1
	u8 S[] = {0xA, 0x8, 0xF, 0x4,
               0x2, 0x9, 0xE, 0xD,
               0xC, 0xB, 0x6, 0x0,
               0x5, 0x1, 0x3, 0x7};  // Example S-box (replace with actual values)
    size_t n = 4;  // Example number of input bits
    size_t m = 4;  // Example number of output bits
#endif
    print_lat(S, n, m);
    // parsing_lat(S, n, m);
	
	return 0;
}
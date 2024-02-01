/*
 * CaS Study 1 (20240113)
*/

#if 1 /* 3-bit S-Box LAT */
    int S[] = {0x7, 0x0, 0x6, 0x4,
		   0x5, 0x2, 0x1, 0x3};  // Example S-box (replace with actual values)
    int n = 3;  // Example number of input bits
    int m = 3;  // Example number of output bits

    print_lat(S, n, m);
#endif

#if 0 /* 4-bit S-Box LAT */
	u8 S[] = {0xA, 0x8, 0xF, 0x4,
               0x2, 0x9, 0xE, 0xD,
               0xC, 0xB, 0x6, 0x0,
               0x5, 0x1, 0x3, 0x7};  // Example S-box (replace with actual values)
    size_t n = 4;  // Example number of input bits
    size_t m = 4;  // Example number of output bits

    print_lat(S, n, m);
    // parsing_lat(S, n, m);
#endif
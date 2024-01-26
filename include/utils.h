#include "config.h"

// Read Time-Stamp Counter
static inline u64 rdtsc() {
    u32 lo, hi;
    
    // Inline assembly syntax for GCC. This tells the compiler to emit the rdtsc instruction,
    // which stores the result in two 32-bit registers: the lower 32 bits in 'eax' (mapped to 'lo' in C),
    // and the higher 32 bits in 'edx' (mapped to 'hi' in C).
    __asm__ __volatile__ (
      "rdtsc" : "=a" (lo), "=d" (hi)
    );
    
    // Combine the high and low 32-bit values into a single 64-bit integer.
    // The high value is shifted left by 32 bits and then combined with the low value.
    return ((u64)hi << 32) | lo;
}

void print_lat(u8* S, u8 n, u8 m);
void parsing_lat(u8* S, u8 n, u8 m);

// // Define any necessary constants or properties
// // For example, if keys have a known pattern, specific bits set, or parity conditions
// const u8 REQUIRED_PATTERN = 0bxxxxxx;  // Replace 'xxxxxx' with the actual pattern
// const u8 PATTERN_MASK = 0bxxxxxx;      // Mask to isolate relevant bits

// int is_valid_key(u8 key) {
//     // Check for specific patterns in the key
//     if ((key & PATTERN_MASK) != REQUIRED_PATTERN) {
//         return 0;  // Key does not match the required pattern
//     }
    
//     // Check for other properties
//     // Example: check if the key has an even number of bits set (even parity)
//     if (__builtin_popcount(key) % 2 != 0) {  // Assuming GCC's built-in function
//         return 0;  // Key does not have even parity
//     }

//     // Add any other conditions based on your knowledge of the keys
//     // ...

//     return 1;  // The key meets all the criteria
// }
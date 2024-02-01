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
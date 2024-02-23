#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <x86intrin.h> // for __rdtscp and __rdtsc
#include <inttypes.h> // for PRIu64 macro

// #if __STDC_VERSION__ >= 199901L
// #define _XOPEN_SOURCE 600
// #else
// #define _XOPEN_SOURCE 500
// #endif /* __STDC_VERSION__ */

#ifndef _CONFIG_H
#define _CONFIG_H

typedef int8_t i8;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;

#endif /* _CONFIG_H */
#include "config.h"

#ifndef _SBOX_LAT_H
#define _SBOX_LAT_H

u8 dot(u8 u, u8 v);
u8 success(u8* S, u8 alpha, u8 beta, u8 n);
i8 bias_integer(u8* S, u8 alpha, u8 beta, u8 n);
i8** lat(u8* S, u8 n, u8 m);

#endif /* _SBOX_LAT */
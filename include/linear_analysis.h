#include "config.h"

#ifndef _LINEAR_ANALYSIS_H
#define _LINEAR_ANALYSIS_H

int parity(int n);
void construct_LAT(u8 SBOX[SBOX_SIZE], u8 LAT[SBOX_SIZE][SBOX_SIZE]);

#endif // _LINEAR_ANALYSIS_H
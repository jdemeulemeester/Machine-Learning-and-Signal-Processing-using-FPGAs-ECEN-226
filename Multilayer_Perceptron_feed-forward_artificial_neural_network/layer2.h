#ifndef LAYER2_H_
#define LAYER2_H_

#include "activation.h"
#include "w2.h"
#include "b2.h"

#define L2_ROWS_A 10
#define L2_COLS_A 25
#define L2_ROWS_B L2_COLS_A
#define L2_COLS_B 1
#define L2_ROWS_C L2_ROWS_A
#define L2_COLS_C L2_COLS_B 

typedef int T;
typedef ap_fixed<16,2, AP_RND, AP_SAT> LYR2_in; // many more decimal bits to match activation output
typedef ap_fixed<8,2, AP_RND, AP_SAT> WGHT;     // 2 int bits to represent input range of -2 to 1


void layer2(
 LYR2_in x[L2_ROWS_B],
 NL_out y[L2_ROWS_C]);
#endif
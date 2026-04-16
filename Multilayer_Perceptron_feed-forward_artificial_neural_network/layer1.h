#ifndef LAYER1_H_
#define LAYER1_H_

#include "activation.h"
#include "w1.h"
#include "b1.h"

#define L1_ROWS_A 25    //hidden layer nodes
#define L1_COLS_A 784   //num inputs
#define L1_ROWS_B L1_COLS_A
#define L1_COLS_B 1
#define L1_ROWS_C L1_ROWS_A
#define L1_COLS_C L1_COLS_B 

typedef int T;
typedef ap_fixed<8,2, AP_RND, AP_SAT> LYR1_in;  //2 int bits to represent input range of -2 to 1
typedef ap_fixed<8,2, AP_RND, AP_SAT> WGHT;     //2 int bits to represent input range of -2 to 1


void layer1(
 LYR1_in x[L1_ROWS_B],
 NL_out y[L1_ROWS_C]);
#endif
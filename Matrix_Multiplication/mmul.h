#ifndef MMUL_H_
#define MMUL_H_

#include "ap_fixed.h"

#define PRAGMA_SUB(x) _Pragma (#x)
#define PRAGMA_HLS(x) PRAGMA_SUB(x)

// define the dimensions of the two input operand matrices A and B
#define NROWS_A 3
#define NCOLS_A 4
#define NROWS_B NCOLS_A
#define NCOLS_B 6
#define NROWS_C NROWS_A
#define NCOLS_C NCOLS_B 

// data type used for the golden reference matrix product function
typedef int T;


#define MMUL_NUM_INT_BITS 16
#define MMUL_NUM_FRAC_BITS 0

typedef ap_fixed<MMUL_NUM_INT_BITS, MMUL_NUM_INT_BITS, AP_TRN, AP_WRAP> MM_DATA_T;

#endif

// function prototypes

void mmul(MM_DATA_T a[NROWS_A][NCOLS_A], MM_DATA_T b[NROWS_A][NCOLS_B], MM_DATA_T c[NROWS_C][NCOLS_C]);
void mmul_reference(T a[NROWS_A][NROWS_B], T b[NROWS_B][NCOLS_B], T c[NROWS_C][NCOLS_C]);


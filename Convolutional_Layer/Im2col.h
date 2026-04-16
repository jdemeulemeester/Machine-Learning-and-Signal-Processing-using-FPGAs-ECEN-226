#ifndef IM2COL_H_
#define IM2COL_H_
#include "ap_fixed.h"

#define x_nrows 28
#define x_ncols 28
#define filter_nrows 3
#define filter_ncols 3
#define im2col_ofm_nrows (x_nrows - filter_nrows + 1)
#define im2col_ofm_ncols (x_ncols - filter_ncols + 1)
#define buffRow (filter_nrows*filter_ncols)
#define buffCol (im2col_ofm_nrows*im2col_ofm_ncols)

//typedef float DataIn;
//typedef float DataOut;

typedef ap_fixed<16,2, AP_RND, AP_SAT> DataIn;
typedef ap_fixed<32,4, AP_RND, AP_SAT> DataOut;


void Im2col(
  DataIn x[x_nrows][x_ncols],
  DataIn y[buffRow][buffCol]
);
#endif
#include "Im2col.h"
void Im2col(
  DataIn x[x_nrows][x_ncols],
  DataIn y[buffRow][buffCol]
){
#pragma HLS ARRAY_PARTITION variable=y dim=1 type=complete
#pragma HLS ARRAY_PARTITION variable=x dim=1 type=complete
    unsigned int col = 0;
    unsigned int m,n,p,q;
    unsigned int row_offset, k;

    t1:for(m=0;m<im2col_ofm_nrows;m++){
        #pragma HLS PIPELINE II=1
        t2:for(n=0;n<im2col_ofm_ncols;n++){
            k = 0;
            t3:for(p=0;p<filter_ncols;p++){
                #pragma HLS UNROLL
                t4:for(q=0;q<filter_nrows;q++){
                    #pragma HLS UNROLL
                    y[k][col] = x[m+p][n+q];
                    k = k + 1;
                }
            }
            col = col +1;
        }
    }
}

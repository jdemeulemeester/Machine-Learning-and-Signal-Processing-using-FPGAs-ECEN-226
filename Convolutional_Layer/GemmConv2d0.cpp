#include "GemmConv2d0.h"

void GemmConv2d0(
  DataIn input[x_nrows][x_ncols],
  DataOut product[buffCol])
{
  #pragma HLS DATAFLOW
  #pragma HLS ARRAY_PARTITION variable=input complete dim=2

  DataIn inputHat[buffRow][buffCol];
#pragma HLS ARRAY_PARTITION variable=inputHat dim=1 type=complete

  Im2col(input, inputHat);
  mmul(inputHat, product);
}

void mmul(
  DataIn inputHat[buffRow][buffCol],
  DataOut product[buffCol])
{
    #pragma HLS ARRAY_PARTITION variable=conv2d0_w complete dim=1
    #pragma HLS ARRAY_PARTITION variable=inputHat  complete dim=1

    DataOut bias_wide;
    DataIn w;

    col: for(unsigned int i=0; i<buffCol; i++){
        #pragma HLS PIPELINE II=1
        DataOut acc = 0;
        row: for(unsigned int j=0; j<buffRow; j++){
            #pragma HLS UNROLL
            w = conv2d0_w[j];
            acc += w * inputHat[j][i];
        }
        bias_wide = conv2d0_b;
        product[i] = acc + bias_wide;
    }
}
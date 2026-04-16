#ifndef GEMMCONV2D0_H_
#define GEMMCONV2D0_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
#include "math.h"
#include "ap_fixed.h"
#include "Im2col.h"
#include "conv2d0_w.h"
#include "conv2d0_b.h"


void GemmConv2d0(
  DataIn input[x_nrows][x_ncols],
  DataOut product[buffCol]
);
void mmul(
  DataIn inputHat[buffRow][buffCol],
  DataOut product[buffCol]
);

//void tanh_reference(double z, double *y);
//void sigmoid_reference(double z, double *y);
#endif
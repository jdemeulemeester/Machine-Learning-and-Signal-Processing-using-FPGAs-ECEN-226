#ifndef MLP_H_
#define MLP_H_

#include "layer1.h"
#include "layer2.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

#define NUM_SAMPLES 100


void mlp(
 LYR1_in in[L1_ROWS_B],
 NL_out out[L2_ROWS_C]
);
#endif
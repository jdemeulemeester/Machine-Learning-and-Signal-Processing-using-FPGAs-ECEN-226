#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
#include "math.h"
#include "ap_fixed.h"

#define kNumActivationFunctions 2
#define POLY_ORDER 2
#define SIGMOID 0
#define TANH 1

#define NUM_SAMPLES 20

#define ZMAX_SLOC 4
#define ZMAX_TLOC 2

#define ZMIN -8
#define ZMAX 8


//typedef float Poly_coeff_t;
//typedef float NL_inp_arg_t;
//typedef float NL_out_arg_t;

typedef ap_fixed<16,8> Poly_coeff_t;
typedef ap_fixed<16,8> NL_inp_arg_t;
typedef ap_fixed<16,8> NL_out_arg_t;


void Activation(
  unsigned int activation_mode,
  Poly_coeff_t coeff[kNumActivationFunctions][POLY_ORDER+1],
  NL_inp_arg_t z,
  NL_out_arg_t *y
);

void tanh_reference(double z, double *y);
void sigmoid_reference(double z, double *y);

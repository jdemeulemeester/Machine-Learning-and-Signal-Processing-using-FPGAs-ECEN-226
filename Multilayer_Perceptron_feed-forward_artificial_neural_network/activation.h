#ifndef ACTIVATION_H_
#define ACTIVATION_H_

#include "ap_fixed.h"
#include "sigmoid_coeffs.h"

#define POLY_ORDER 2
#define ZMAX_SLOC 4
#define ZMIN -8
#define ZMAX 8

typedef ap_fixed<16,2, AP_RND, AP_SAT> Poly_coeff;  //want precision for poly coeffs
typedef ap_fixed<16,3, AP_RND, AP_SAT> NL_in;   //max inputs 8 to -8, this caps at -7 to 6 which is close enough
typedef ap_fixed<16,2, AP_RND, AP_SAT> NL_out;  //good precision for output
typedef ap_fixed<32,8, AP_RND, AP_SAT> NL_wide; // need more room for fixed point multiplications

NL_out activation(NL_in z);
#endif
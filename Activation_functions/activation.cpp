#include "activation.h"
void Activation(unsigned int activation_mode, Poly_coeff_t coeff[kNumActivationFunctions][POLY_ORDER+1], NL_inp_arg_t z, NL_out_arg_t *y){
    //clean data path at beginning and select output at end
    //coeff is 2d array holding sigmoid and tanh coefficients
    //don't need seperate data path for both, just selecting different inputs to data path and Zmax/Zmin local
    NL_out_arg_t sigmoid_o;
    NL_out_arg_t tanh_o;
    NL_inp_arg_t zsquare;
    NL_inp_arg_t temp;
    NL_inp_arg_t abs_z;

    abs_z = (z >= NL_inp_arg_t(0)) ? z : NL_inp_arg_t(-z);

    zsquare = z*z;
    sigmoid_o = coeff[0][0] + coeff[0][1]*abs_z + coeff[0][2]*zsquare;
    tanh_o = coeff[1][0] + coeff[1][1]*abs_z + coeff[1][2]*zsquare;

    if(activation_mode){    //tanh
        tanh_o = (abs_z > NL_inp_arg_t(ZMAX_TLOC)) ? NL_out_arg_t(1) : tanh_o;    //poly_apprx_max
        *y = (z < NL_inp_arg_t(0)) ? NL_inp_arg_t(-tanh_o) : tanh_o;  //negative or positive
    }  else {   //sigmoid
        sigmoid_o = (abs_z > NL_inp_arg_t(ZMAX_SLOC)) ? NL_out_arg_t(1) : sigmoid_o;  //poly_apprx_max
        *y = (z < NL_inp_arg_t(0)) ? NL_inp_arg_t(NL_out_arg_t(1) - sigmoid_o) : sigmoid_o; //negative or positive
    }
}
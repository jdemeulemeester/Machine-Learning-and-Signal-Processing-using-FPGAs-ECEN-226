#include "activation.h"

NL_out activation(NL_in z){
    NL_in abs_z;        //declare variables so they have right type
    NL_wide zsquare;
    NL_wide c0, c1, c2, sum;
    NL_out sigmoid_o;

    abs_z = (z >= NL_in(0)) ? z : NL_in(-z);    //get absolute value of input

    zsquare = z*z;  //Doing assigns before operation to set type,
    c0 = coeff[0];  //important to set type with fixed point
    c1 = coeff[1];
    c1 = c1*abs_z;
    c2 = coeff[2];
    c2 = c2*zsquare;
    sum = c0 + c1 + c2;
    sigmoid_o = sum;    //sigmoid apprx output for input absolute value

    sigmoid_o = (abs_z > NL_in(ZMAX_SLOC)) ? NL_out(1) : sigmoid_o;  //cap at max inputs
    if(z < NL_in(0)){
        sigmoid_o = NL_out(1) - sigmoid_o;
        return sigmoid_o; //negative val output
    } else {
        return sigmoid_o; //positive val output
    }
}
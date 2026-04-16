#ifndef __INNER_PRODUCT_H__
#define __INNER_PRODUCT_H__
#include "ap_fixed.h"
#define N	8
#define MAX_NUM 100

#if 1
#define OPERAND_NBITS 16
#define OPERAND_NBITS_FRAC 0
#define OPERAND_NBITS_INT OPERAND_NBITS - OPERAND_NBITS_FRAC
typedef ap_fixed<OPERAND_NBITS, OPERAND_NBITS_INT>	data_t;
#else
typedef int data_t;

#endif

// function prototypes
void inner_product(data_t a[N], data_t b[N], data_t &s);
void inner_product_reference(data_t a[N], data_t b[N], data_t &s);

#endif

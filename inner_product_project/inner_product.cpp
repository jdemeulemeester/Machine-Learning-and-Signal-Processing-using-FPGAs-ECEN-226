#include "inner_product.h"

void inner_product(data_t a[N], data_t b[N], data_t& s)
{
	int i;
	data_t acc;

	acc = 0;
	inner_product_loop:
	for (int i=0; i<N; i++)
	{
		acc += a[i] * b[i];
	}
	s = acc;
}

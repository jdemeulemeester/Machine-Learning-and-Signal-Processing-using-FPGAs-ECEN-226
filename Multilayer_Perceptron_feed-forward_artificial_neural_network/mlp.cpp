#include "mlp.h"

void mlp(
 LYR1_in in[L1_ROWS_B],
 NL_out out[L2_ROWS_C])
{
    LYR2_in hidden[L1_ROWS_C];  //intermediate between layers
	layer1(in, hidden);
    layer2(hidden, out);
}
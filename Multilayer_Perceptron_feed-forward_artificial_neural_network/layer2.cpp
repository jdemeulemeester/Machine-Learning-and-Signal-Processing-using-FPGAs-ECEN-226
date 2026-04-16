#include "layer2.h"

void layer2(
 LYR2_in x[L2_ROWS_B],
 NL_out y[L2_ROWS_C])
{
    int i, j, k;    //declare variables so they have right type
	NL_wide acc;
    NL_wide b_wide;
    NL_in z;
    WGHT w;

	row:for (i=0; i<L2_ROWS_A; i++)
	{
        acc = 0;
		col:for (j=0; j<L2_COLS_A; j++)
		{
            w = w2[j][i];   //python gave data as weights coming out of each input
			acc += w * x[j];    //for layer 1 that is 25 weights per input
		}
        b_wide = b2[i];         //Doing assigns before operation to set type,
        acc = acc + b_wide;     //important to set type with fixed point
        z = acc;
        y[i] = activation(z);
	}
}
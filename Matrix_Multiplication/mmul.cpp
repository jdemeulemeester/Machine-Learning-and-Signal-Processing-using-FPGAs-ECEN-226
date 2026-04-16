#include "mmul.h"

void mmul(MM_DATA_T a[NROWS_A][NCOLS_A], MM_DATA_T b[NROWS_B][NCOLS_B], MM_DATA_T c[NROWS_C][NCOLS_C])
{
	int i, j, k;
	MM_DATA_T acc=0;

	row:for (i=0; i<NROWS_A; i++)
	{
		col:for (j=0; j<NCOLS_B; j++)
		{
			prod:for (k=0; k<NROWS_B; k++)
			{
				if (k==0) acc = 0;
				acc	 += a[i][k] * b[k][j];
				if (k==NROWS_B-1) c[i][j] = acc;
			}
		}
	}
}

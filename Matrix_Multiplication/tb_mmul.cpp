#include <iostream>
#include <fstream>
#include "mmul.h"

#define MAX_NUM 18		// max range of values used for input array initialization

int main(void)
{

	int i, j;
	T a1[NROWS_A][NCOLS_A];
	T b1[NROWS_B][NCOLS_B];
	T c1[NROWS_C][NCOLS_C];

	MM_DATA_T a2[NROWS_A][NCOLS_A];
	MM_DATA_T b2[NROWS_B][NCOLS_B];
	MM_DATA_T c2[NROWS_C][NCOLS_C];

	// initialize the input arrays A and B with psuedo randon numbers

	for (i=0; i<NROWS_A; i++)
		for (j=0; j<NCOLS_A; j++)
			a1[i][j] = rand() % MAX_NUM;

	for (i=0; i<NROWS_B; i++)
		for (j=0; j<NCOLS_B; j++)
			b1[i][j] = rand() % MAX_NUM;

	std::cout << "matrix a" << std::endl;

	for (i=0; i<NROWS_A; i++)
	{
		for (j=0; j<NCOLS_A; j++)
			std::cout << a1[i][j] << "\t";
		std::cout << std::endl;		
	}

	std::cout << "matrix b" << std::endl;

	for (i=0; i<NROWS_B; i++)
	{
		for (j=0; j<NCOLS_B; j++)
			std::cout << b1[i][j] << "\t";
		std::cout << std::endl;		
	}

	// call the reference function

	mmul_reference(a1, b1, c1);

	// write the golden reference to the console

	std::cout << "reference data" << std::endl;

	for (i=0; i<NROWS_C; i++)
	{
		for (j=0; j<NCOLS_C; j++)
			std::cout << c1[i][j] << "\t";
		std::cout << std::endl;		
	}

	for (i=0; i<NROWS_A; i++)
		for (j=0; j<NCOLS_A; j++)
			a2[i][j] = a1[i][j];

	for (i=0; i<NROWS_B; i++)
		for (j=0; j<NCOLS_B; j++)
			b2[i][j] = b1[i][j];

	// call the HLS function


	mmul(a2, b2, c2);

	std::cout << std::endl;
	std::cout << "HLS data" << std::endl;

	for (i=0; i<NROWS_C; i++)
	{
		for (j=0; j<NCOLS_C; j++)
			std::cout << c2[i][j] << "\t";
		std::cout << std::endl;		
	}


	// compare the HLS result with the golden reference

	int err_cnt = 0;
	for (i=0; i<NROWS_C; i++)
		for (j=0; j<NCOLS_C; j++)
		{
			if (c1[i][j] != c2[i][j])
				err_cnt++;
		}

	std::cout << "error count = " << err_cnt << std::endl;
	std::cout << "HLS matrix product matches golden reference data" << std::endl;

	if (err_cnt == 0)
		return 0;
	else
		return 1;
}


// matrix product golden refernce 
void mmul_reference(T a[NROWS_A][NROWS_B], T b[NROWS_B][NCOLS_B], T c[NROWS_C][NCOLS_C])
{
	int i,j,k;
	int mcount = 0;
	for (i=0; i<NROWS_A; i++)
	{
		for (j=0; j<NCOLS_B; j++)
		{
			c[i][j] = 0;
			for (k=0; k<NROWS_B; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
				mcount++;
			}
		}
	}
	std::cout << "mpy count = " << mcount << std::endl;
}

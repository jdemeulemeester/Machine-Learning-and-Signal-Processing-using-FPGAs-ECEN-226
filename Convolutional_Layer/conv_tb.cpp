#include "GemmConv2d0.h"

#define IMAGE_TEST_FILENAME "image.dat"
#define TRACE_FILENAME "trace.dat"
#define CONV_OUTPUT_FILENAME "conv_output.dat"

int main(void)
{
	std::ifstream test_image;				// Test input for convolution
	std::ifstream trace_data;				// The known correct answer for each test input
	std::ofstream conv_output;				// save outputs this stream

	DataIn image[x_nrows][x_ncols];							// input test
	DataOut conv_out[buffCol];	// output of conv
	float golden[im2col_ofm_nrows][im2col_ofm_ncols];		// golden reference

	//used for forloops
	unsigned int i,j;
	int w = 10;

	//open files
	test_image.open(IMAGE_TEST_FILENAME);
	if (test_image.is_open()==0){
		std::cout << "failure opening file: " << IMAGE_TEST_FILENAME << std::endl;
		exit(0);
	} else {
		std::cout << "opening file: " << IMAGE_TEST_FILENAME << std::endl;
	}

	trace_data.open(TRACE_FILENAME);
	if (trace_data.is_open()==0){
		std::cout << "failure opening file: " << TRACE_FILENAME << std::endl;
		exit(0);
	} else {
		std::cout << "opening file: " << TRACE_FILENAME << std::endl;
	}

	conv_output.open(CONV_OUTPUT_FILENAME);
	if (conv_output.is_open()==0){
		std::cout << "failure opening file: " << CONV_OUTPUT_FILENAME << std::endl;
		exit(0);
	} else {
		std::cout << "opening file: " << CONV_OUTPUT_FILENAME << std::endl;
	}
	

	float temp;
	float max = 0;
	float min = 0;
	// read test inputs
	for (i=0; i<x_nrows; i++)
	{
		for(j=0; j<x_ncols; j++)
		{
			test_image >> temp;
			if(temp > max) max = temp;
			if(temp < min) min = temp;
			image[i][j] = temp;
		}
	}
	std::cout << std::endl <<  "Max input val" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << std::setw(w) << std::left << max;
	std::cout << std::endl;

	std::cout << std::endl <<  "Min input val" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << std::setw(w) << std::left << min;
	std::cout << std::endl;


	max = 0;
	min = 0;
	// read golden reference data
	for (i=0; i<im2col_ofm_nrows; i++)
	{
		for(j=0; j<im2col_ofm_ncols; j++)
		{
			trace_data >> temp;
			if(temp > max) max = temp;
			if(temp < min) min = temp;
			golden[i][j] =  temp;
		}
	}

	std::cout << std::endl <<  "Max output" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << std::setw(w) << std::left << max;
	std::cout << std::endl;

	std::cout << std::endl <<  "Min output" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << std::setw(w) << std::left << min;
	std::cout << std::endl;
	

	// print out input test to check if read in right
	std::cout << std::endl <<  "Test input one first 15 vals" << std::endl;
	std::cout << std::endl << std::endl; 
	for(j=0; j<15; j++)
		std::cout << std::setw(w) << std::left << image[0][j];
	std::cout << std::endl;

	// print out golden reference to check if read in right
	std::cout << std::endl <<  "Golden reference first 15 vals" << std::endl;
	std::cout << std::endl << std::endl;
	for(j=0; j<15; j++)
		std::cout << std::setw(w) << std::left << golden[0][j];
	std::cout << std::endl;


	// run tests through MLP
	GemmConv2d0(image, conv_out);

	// print out first output so I can see if anything looks odd
	std::cout << std::endl <<  "First output" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << conv_out[0] << std::endl;
	std::cout << conv_out[1] << std::endl;
	std::cout << conv_out[2] << std::endl;
	std::cout << conv_out[3] << std::endl;
	std::cout << conv_out[4] << std::endl;
	std::cout << conv_out[5] << std::endl;
	std::cout << conv_out[6] << std::endl;
	std::cout << conv_out[7] << std::endl;
	std::cout << conv_out[8] << std::endl;
	std::cout << conv_out[9] << std::endl;
	std::cout << std::endl << std::endl;


	float abs_err = 0;
	float max_abs_err = 0;		// |calculated - true|
	float perc_err = 0;			// ((|calculated - true|) / true) * 100
	float ave_perc_err = 0;

	// Find error
	for(i=0; i<im2col_ofm_nrows; i++)
	{
		for(j=0; j<im2col_ofm_ncols; j++)
		{
			abs_err = abs(float(conv_out[(i*im2col_ofm_nrows)+j]) - golden[i][j]);
			perc_err = (abs_err/abs(golden[i][j]))*100;
			if(perc_err > max_abs_err)
			{
				max_abs_err = perc_err;
			}
			ave_perc_err += perc_err;
			conv_output << std::setw(w) << std::left << conv_out[(i*im2col_ofm_nrows)+j] << std::endl;
		}
	}

	// calculate accuracy
	ave_perc_err = ave_perc_err/buffCol;

	std::cout << std::endl <<  "The max error is: " << max_abs_err << "%" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << std::endl <<  "The average error is: " << ave_perc_err << "%" << std::endl;
	std::cout << std::endl << std::endl;


	// closing files
	std::cout << "cleaning-up" << std::endl;

	test_image.close();
	trace_data.close();
	conv_output.close();

	return 0;
}
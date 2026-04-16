#include "mlp.h"

#define X_TEST_FILENAME "x_test.dat"
#define Y_TEST_FILENAME "y_test.dat"
#define Y_PREDICTED_FILENAME "y_pred.dat"

int main(void)
{
	std::ifstream test_inputs;					// Test inputs for MLP
	std::ifstream golden_reference;				// The known correct answer for each test input
	std::ofstream y_predicted;					// save outputs this stream

	LYR1_in in[NUM_SAMPLES][L1_ROWS_B];			//inputs for each sample
 	NL_out outputs[NUM_SAMPLES][L2_ROWS_C];		//outputs for each sample input
	unsigned int golden[NUM_SAMPLES];			// golden reference array

	//used for forloops
	unsigned int i,j;

	//open files
	test_inputs.open(X_TEST_FILENAME);
	if (test_inputs.is_open()==0){
		std::cout << "failure opening file: " << X_TEST_FILENAME << std::endl;
		exit(0);
	} else {
		std::cout << "opening file: " << X_TEST_FILENAME << std::endl;
	}

	golden_reference.open(Y_TEST_FILENAME);
	if (golden_reference.is_open()==0){
		std::cout << "failure opening file: " << Y_TEST_FILENAME << std::endl;
		exit(0);
	} else {
		std::cout << "opening file: " << Y_TEST_FILENAME << std::endl;
	}

	y_predicted.open(Y_PREDICTED_FILENAME);
	if (y_predicted.is_open()==0){
		std::cout << "failure opening file: " << Y_PREDICTED_FILENAME << std::endl;
		exit(0);
	} else {
		std::cout << "opening file: " << Y_PREDICTED_FILENAME << std::endl;
	}
	

	LYR1_in temp;
	// read test inputs
	for (i=0; i<NUM_SAMPLES; i++)
	{
		for(j=0; j<L1_ROWS_B; j++)
		{
			test_inputs >> temp;
			in[i][j] = temp;
		}
	}

	// read golden reference data
	for (i=0; i<NUM_SAMPLES; i++)
	{
		golden_reference >> j;
		golden[i] =  j;
	}
	

	// print out input test to check if read in right
	std::cout << std::endl <<  "Test input one first 15 vals" << std::endl;
	std::cout << std::endl << std::endl;
	int w = 10; 
	for(j=0; j<15; j++)
		std::cout << std::setw(w) << std::left << in[0][j];
	std::cout << std::endl;

	// print out golden reference to check if read in right
	std::cout << std::endl <<  "Golden reference first 15 vals" << std::endl;
	std::cout << std::endl << std::endl;
	for(j=0; j<15; j++)
		std::cout << std::setw(w) << std::left << golden[j];
	std::cout << std::endl;

	float accuracy = 0;
	unsigned int predicted_out [NUM_SAMPLES];


	// run tests through MLP
	for(i=0; i<NUM_SAMPLES; i++)
	{
		mlp(in[i],outputs[i]);
	}

	// print out first output so I can see if anything looks odd
	std::cout << std::endl <<  "First output" << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << outputs[0][0] << std::endl;
	std::cout << outputs[0][1] << std::endl;
	std::cout << outputs[0][2] << std::endl;
	std::cout << outputs[0][3] << std::endl;
	std::cout << outputs[0][4] << std::endl;
	std::cout << outputs[0][5] << std::endl;
	std::cout << outputs[0][6] << std::endl;
	std::cout << outputs[0][7] << std::endl;
	std::cout << outputs[0][8] << std::endl;
	std::cout << outputs[0][9] << std::endl;
	std::cout << std::endl << std::endl;

	// Find predicted result from output vectors
	for(i=0; i<NUM_SAMPLES; i++)
	{
		unsigned int max = 0;
		for(j=1; j<L2_ROWS_A; j++)	//find max of the 10 outputs
		{
			if(outputs[i][j] > outputs[i][max])
			{
				max = j;
			}
		}
		predicted_out[i] = max;		//save max as predicted answer
		y_predicted << std::setw(w) << std::left << max << std::endl;
		if(max == golden[i])		//compare predicted with golden result
			accuracy = accuracy + 1;
	}

	// calculate accuracy
	accuracy = 100*(accuracy/NUM_SAMPLES);

	std::cout << std::endl <<  "The accuracy is: " << accuracy << "%" << std::endl;
	std::cout << std::endl << std::endl;


	// closing files
	std::cout << "cleaning-up" << std::endl;

	test_inputs.close();
	golden_reference.close();
	y_predicted.close();

	return 0;
}
/*
 * The first coefficient in the LS approximation to tanh(z) is always 0.
 * In this version of tanh(z) the complete set of polynomial coefficients are read.
 * But then re-arranged to remove the 0 valued coefficient.
 *
 * This version includes a mode bit. Ultimately the mode bit will be used to select
 * between sigmoid and tanh. This is a first experiment heading in the direction of a FU
 * that can compute both sigmoid and tanh.
 *
 */

#include "activation.h"

#define NL_FILENAME "poly.dat"
#define POLY_COEFFS_SIGMOID_FILENAME "sigmoid_coeffs.dat"
#define POLY_COEFFS_TANH_FILENAME "tanh_coeffs.dat"

int main(void)
{

	unsigned int i,j;

	std::ifstream poly_coeffs_sigmoid;						// coefficients for polynomial approximation - sigmoid
	std::ifstream poly_coeffs_tanh;							// coefficients for polynomial approximation - tanh
	std::ofstream nl_file;									// save non-linearity function approximation to this stream
	Poly_coeff_t coeffs[kNumActivationFunctions][POLY_ORDER+1];	// polynomial coefficients
	float error_matrix[NUM_SAMPLES];			// difference betweeen non-linearity reference and approximation
	double nlin_reference;						// golden reference for non-linear function
	
	double zmin;
	double zmax;
	unsigned int n = NUM_SAMPLES;
	zmin = ZMIN;
	zmax = ZMAX;

	poly_coeffs_sigmoid.open(POLY_COEFFS_SIGMOID_FILENAME);
	if (poly_coeffs_sigmoid.is_open()==0)
	{
		std::cout << "failure opening file: " << POLY_COEFFS_SIGMOID_FILENAME << std::endl;
		exit(0);
	}
	else
	{
		std::cout << "opening file: " << POLY_COEFFS_SIGMOID_FILENAME << std::endl;
	}

	poly_coeffs_tanh.open(POLY_COEFFS_TANH_FILENAME);
	if (poly_coeffs_tanh.is_open()==0)
	{
		std::cout << "failure opening file: " << POLY_COEFFS_TANH_FILENAME << std::endl;
		exit(0);
	}
	else
	{
		std::cout << "opening file: " << POLY_COEFFS_TANH_FILENAME << std::endl;
	}

	nl_file.open(NL_FILENAME);
	if (nl_file.is_open()==0)
	{
		std::cout << "failure opening file: " << NL_FILENAME << std::endl;
		exit(0);
	}
	else
	{
		std::cout << "opening file: " << NL_FILENAME << std::endl;
	}
	

	// read coefficients - sigmoid
	
	//float floating_point_tmp;
	NL_inp_arg_t tmp;

	for (j=0; j<=POLY_ORDER; j++)
	{
		//poly_coeffs_sigmoid >> floating_point_tmp;
		//coeffs[SIGMOID][j] =  floating_point_tmp;
		poly_coeffs_sigmoid >> tmp;
		coeffs[SIGMOID][j] =  tmp;
	}
	
	// read coefficients - tanh
	

	for (j=0; j<=POLY_ORDER; j++)
	{
		//poly_coeffs_tanh >> floating_point_tmp;
		//coeffs[TANH][j] =  floating_point_tmp;
		poly_coeffs_tanh >> tmp;
		coeffs[TANH][j] =  tmp;
	}

	std::cout << std::endl <<  "polynomial coefficients - sigmoid" << std::endl;
	std::cout << std::endl << std::endl;
	int w = 14;

	for (j=0; j<=POLY_ORDER; j++)
		std::cout << std::setw(w) << std::left << coeffs[SIGMOID][j];

	std::cout << std::endl;

	std::cout << std::endl <<  "polynomial coefficients - tanh" << std::endl;
	std::cout << std::endl << std::endl;

	for (j=0; j<=POLY_ORDER; j++)
		std::cout << std::setw(w) << std::left << coeffs[TANH][j];

	std::cout << std::endl;
	
	double delta_z = (zmax-zmin) / double(n-1);
	double z;
	NL_inp_arg_t zfxp;
	NL_out_arg_t y;
	double err;	
	double max_err = 0;
	double MSE=0;			// mean-squared-error
	z = zmin;


	// test tanh ------------------------------------

	w = 14;
	std::cout << std::setw(w) << "z";
	std::cout << std::setw(w) << "nl(z)";
	std::cout << std::setw(w) << std::left << "nl(z) - FXP";
	std::cout << std::setw(w) << std::left << "err";
	std::cout << std::setw(w) << std::left << "mse";
	std::cout << std::endl << std::endl;

	unsigned int activation_mode = TANH;

	for (i=0; i<n; i++)
	{
		zfxp = NL_inp_arg_t(z);
		Activation(activation_mode, coeffs, zfxp, &y);
		tanh_reference(z, &nlin_reference);
		z += delta_z;

		err = fabs(float(y) - nlin_reference);

		if (err > max_err)
		{
			max_err = err;
		}

		double tmp = err*err;
		MSE = MSE + tmp;

		std::cout << std::setw(w) << std::left << (z-delta_z);
		std::cout << std::setw(w) << std::left << nlin_reference;
		std::cout << std::setw(w) << std::left << float(y);
		std::cout << std::setw(w) << std::left << err;
		std::cout << std::setw(w) << std::left << MSE;
		std::cout << std::endl;

		nl_file << std::setw(w) << std::left << float(y) << std::endl;
	}

	double MSE_tanh = (MSE / double(n));
	double max_err_tanh = max_err;
	
	// test sigmoid ------------------------------------
	
	w = 14;
	std::cout << std::endl;
	std::cout << std::setw(w) << "z";
	std::cout << std::setw(w) << "nl(z)";
	std::cout << std::setw(w) << std::left << "nl(z) - FXP";
	std::cout << std::setw(w) << std::left << "err";
	std::cout << std::setw(w) << std::left << "mse";
	std::cout << std::endl << std::endl;

	activation_mode = SIGMOID;

	z = zmin;
	MSE = 0;
	max_err = 0;

	for (i=0; i<n; i++)
	{
		zfxp = NL_inp_arg_t(z);
		Activation(activation_mode, coeffs, zfxp, &y);
		sigmoid_reference(z, &nlin_reference);
		z += delta_z;

		err = fabs(float(y) - nlin_reference);

		if (err > max_err)
		{
			max_err = err;
		}

		double tmp = err*err;
		MSE = MSE + tmp;

		std::cout << std::setw(w) << std::left << (z-delta_z);
		std::cout << std::setw(w) << std::left << nlin_reference;
		std::cout << std::setw(w) << std::left << float(y);
		std::cout << std::setw(w) << std::left << err;
		std::cout << std::setw(w) << std::left << MSE;
		std::cout << std::endl;

		nl_file << std::setw(w) << std::left << float(y) << std::endl;
	}

	double MSE_sigmoid = (MSE / double(n));
	double max_err_sigmoid = max_err;


	std::cout << std::endl;
	std::cout << "MSE - sigmoid = " << MSE_sigmoid << std::endl;
	std::cout << "maximum error_sigmoid = " << max_err_sigmoid << std::endl;

	std::cout << "MSE - tanh = " << MSE_tanh  << std::endl;
	std::cout << "maximum error_tanh = " << max_err_tanh << std::endl;
	
	// cleaning up

	std::cout << std::endl;
	std::cout << "cleaning-up" << std::endl;

	poly_coeffs_sigmoid.close();
	poly_coeffs_tanh.close();
	nl_file.close();

	return 0;
}

void tanh_reference(double z, double *y)
/*
 *	Calculate reference y = tanh(z)
 */
{
	*y = (exp(z) - exp(-z)) / (exp(z) + exp(-z));
}

void sigmoid_reference(double z, double *y)
/*
 *	Calculate reference y = sigmoid(z)
 */
{
	*y = 1.0 / (1.0 + exp(-z));
}


#include <math.h>
#include <iostream>
#include <fstream>
#include "inner_product.h"

using namespace std;

int main ()
{

	std::ifstream inputData;
	std::ifstream goldenData;

	data_t xin;
	int sim_status = 0;

	int i;
	int simStatus = 0;
	data_t a[N], b[N], s, s1;

	for (i=0; i<N; i++)
	{
		a[i] = rand() % MAX_NUM;
		b[i] = rand() % MAX_NUM;
	}


	inner_product_reference(a, b, s);
	inner_product(a, b, s1);


	std::cout << s << '\t' << s1 << std::endl;

	if (s != s1)
		sim_status = 1;

	// clean-up

	if (sim_status==0)
		std::cout << "simulation passed" << std::endl;
	else
		std::cout << "simulation failed" << std::endl;
  
	return(sim_status);

}

void inner_product_reference(data_t a[N], data_t b[N], data_t &s)
{
	s = 0;
	for (int i=0; i<N; i++)
		s += a[i] * b[i];
}

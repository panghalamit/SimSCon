#include "vm.h"


VM :: VM(double *arr, double sr)
{
	arrival_rates = arr;
	service_rate = sr;
}


double VM :: getArrivalRate(int t)
{
	return arrival_rates[t];
} 

double VM :: getServiceRate()
{
	return service_rate;
}

VM :: ~VM ()
{}

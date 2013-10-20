#include "vm.h"


VM :: VM(double *arr, double sr)
{
	this.arrival_rates = arr;
	this.serice_rate = sr;
}


double VM :: getArrivalRate(int t)
{
	return arrival_rates[t];
} 

double VM :: getServiceRate()
{
	return serice_rate;
}

VM :: ~VM ()
{}

#include "vm.h"

VM :: VM(double *arr, double sr, int i)
{
	arrival_rates = arr;
	service_rate = sr;
	index = i;
}


double VM :: getArrivalRate(int t)
{
	return arrival_rates[t];
} 

double VM :: getServiceRate()
{
	return service_rate;
}

int VM :: getIndex()
{
	return index;
}

double VM :: getNextArrivalTime(double time)
{
	return (double) poisson(arrival_rates[(int) time]); 
}

double VM :: getNextDepartureTime(double time)
{
	return (double) expon(service_rate);
}
VM :: ~VM ()
{}

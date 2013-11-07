#include "vm.h"

VM :: VM(double arr, double sr, int i)
{
	arrival_rate = arr;
	service_rate = sr;
	index = i;
}

VM :: VM(const VM &vm)
{
	arrival_rate = vm.arrival_rate;
	service_rate = vm.service_rate;
	index = vm.index;
}

double VM :: getArrivalRate()
{
	return arrival_rate;
} 

double VM :: getServiceRate()
{
	return service_rate;
}

int VM :: getIndex()
{
	return index;
}

double VM :: getNextInterArrivalTime()
{
	return (double) poisson(arrival_rate); 
}

double VM :: getNextServiceTime()
{
	return (double) expon(service_rate);
}

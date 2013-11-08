#include "vm.h"

VM :: VM(float arr, float sr, int i)
{
	arrival_rate = arr;
	service_rate = sr;
	index = i;
	st_file = new ofstream((string("results/service_time_vm") +
						static_cast<ostringstream*>(&(ostringstream()<<index))->str() + string(".txt")).c_str());
	if(!st_file->is_open())
	{
		cout<<"error occured, cannot open file!"<<endl;
		exit(1);
	}
}

VM :: VM(const VM &vm)
{
	arrival_rate = vm.arrival_rate;
	service_rate = vm.service_rate;
	index = vm.index;
}

float VM :: getArrivalRate()
{
	return arrival_rate;
}

float VM :: getServiceRate()
{
	return service_rate;
}

int VM :: getIndex()
{
	return index;
}

float VM :: getNextInterArrivalTime()
{
	return poisson(arrival_rate);
}

float VM :: getNextServiceTime()
{
	float st = expon(service_rate);
	*st_file << st << endl;
	return st;
}

void VM :: stop()
{
	st_file->close();
}

VM :: ~VM()
{
	delete st_file;
}

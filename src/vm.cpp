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

float VM :: getNextServiceTime(SimData *sdata, int *vm_to_pm_map)
{
	float st = expon(service_rate);
	int pm = vm_to_pm_map[index];

	float sum_rho = 0;
	for(int i=0; i<sdata->getNumVM(); i++)
	{
		if(vm_to_pm_map[i]==pm)
			sum_rho += (sdata->getArrivalRate(i)/sdata->getFixedServiceRate(i));
	}

	st = st/(1-(arrival_rate/service_rate)/sum_rho);
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

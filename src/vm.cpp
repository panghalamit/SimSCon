#include "vm.h"

VM :: VM(float arr, float sr, int i)
{
	arrival_rate = arr;
	service_rate = sr;
	index = i;
	avg_waiting_time=0;
	avg_response_time=0;
	avg_queue_length=0;
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
	avg_waiting_time = vm.avg_waiting_time;
	avg_response_time = vm.avg_response_time;
	avg_queue_length = vm.avg_queue_length;
	list<float>::const_iterator it;
	server_queue.clear();
	for(it= (vm.server_queue).begin(); it!=(vm.server_queue).end(); it++)
	{
		server_queue.push_back(*it);
	}
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

bool VM :: ifIdle()
{
	return (server_queue.size() == 0);
}

float VM :: getTopInQ()
{
	if(server_queue.size()==0)
	{
		cout<<"illegal access: server queue empty"<<endl;
		exit(0);
	}
	return server_queue.front();
}


float VM :: getAvgWaitingTime()
{
	return avg_waiting_time;
}
	
float VM :: getAvgResponseTime()
{
	return avg_response_time;
}
	
float VM :: getAvgQLength()
{
	return avg_queue_length;
}

int VM :: getTotalReqs()
{
	return total_reqs;
}

void VM :: update_on_arrival(float t, float serv_t)
{
	total_reqs++;
	if(server_queue.size() > 0)
	{
		server_queue.push_back(t);
		avg_queue_length += (server_queue.size()/total_reqs);
	}
	else if(serv_t != -1) //waiting time zero
		avg_response_time += (serv_t/total_reqs);
}
	
void VM :: update_on_departure(float t)
{
	if(server_queue.size() > 0)
	{
		avg_waiting_time += ((t-server_queue.front())/total_reqs);
		server_queue.pop_front();
	}
}

void VM :: stop()
{
	st_file->close();
}

VM :: ~VM()
{
	delete st_file;
}

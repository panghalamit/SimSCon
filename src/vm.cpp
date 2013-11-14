#include "vm.h"

VM :: VM(float arr, float sr, int i)
{
	arrival_rate = arr;
	service_rate = sr;
	index = i;
	busy = false;

	cum_waiting_time=0; delayed_customers = 0;
	cum_response_time=0; total_departures = 0;
	cum_queue_length=0; last_update_time = 0;

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

	cum_waiting_time = vm.cum_waiting_time;
	cum_response_time = vm.cum_response_time;
	cum_queue_length = vm.cum_queue_length;

	list<float>::const_iterator it;
	server_queue.clear();
	for(it= (vm.server_queue).begin(); it!=(vm.server_queue).end(); it++)
		server_queue.push_back(*it);
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
	return expon(1/arrival_rate);
}

float VM :: getNextServiceTime(SimData *sdata, Policy* policy, float current_time, bool mig)
{
	float st = expon(1/service_rate);
	int phase_num = ((int)(current_time/PHASE_LENGTH))%(sdata->getNumPhases());
	vector<int> vm_to_pm_map = policy->getMapping(phase_num);
	vector<int mig_list = policy->getMigrationList(phase_num);
	int pm = vm_to_pm_map[index];

	float sum_rho = 0;
	for(int i=0; i<sdata->getNumVM(); i++)
	{
		if(vm_to_pm_map[i] == pm)
			sum_rho += (sdata->getArrivalRate(i)/sdata->getFixedServiceRate(i));

		if(mig)
			if((mig_list[i] == pm) || (mig_list[i] != -1 && vm_to_pm_map[i] == pm)
				sum_rho += MOHCPUINTENSIVE * (sdata->getArrivalRate(i)/sdata->getFixedServiceRate(i));
	}

	st = st/(arrival_rate/service_rate)*sum_rho*;
	*st_file << st << endl;
	return st;
}

bool VM :: isIdle()
{
	return !busy;
}

bool VM :: isEmptyQueue()
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
	return cum_waiting_time/delayed_customers;
}

float VM :: getAvgResponseTime()
{
	return (cum_response_time/total_departures);
}

float VM :: getAvgQLength(float current_time)
{
	return (cum_queue_length + (current_time - last_update_time) * server_queue.size())/current_time;
}

int VM :: getTotalReqs()
{
	return total_reqs;
}

void VM :: update_on_arrival(float current_time, float serv_time)
{
	total_reqs++;
	if(busy)
	{
		server_queue.push_back(current_time);
		cum_queue_length += server_queue.size() * (current_time - last_update_time);
		last_update_time = current_time;
	} else
	{
		busy = true;
		total_departures++;
		cum_response_time += serv_time;
	}
}

void VM :: update_on_departure(float current_time, float serv_time)
{
	if(server_queue.size() > 0)
	{
		delayed_customers++; cum_waiting_time += current_time - server_queue.front();
		total_departures++; cum_response_time += serv_time + current_time - server_queue.front();
		server_queue.pop_front();
	} else
		busy = false;

	cum_queue_length += server_queue.size() * (current_time - last_update_time);
	last_update_time = current_time;
}

void VM :: stop()
{
	st_file->close();
}

VM :: ~VM()
{
	delete st_file;
}

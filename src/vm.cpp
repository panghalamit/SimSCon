#include "vm.h"

VM :: VM(SimSData *ssdata, int vmi)
{
	num_phases = ssdata->getNumPhases();
	arrival_rate = new float[num_phases];
	cum_waiting_time=new float[num_phases];
	cum_response_time=new float[num_phases];
	cum_queue_length=new float[num_phases];
	delayed_customers = new int[num_phases];
	total_departures = new int[num_phases];
	
	for(int i=0; i<num_phases; i++)
	{
		arrival_rate[i] = ssdata->getArrivalRate(i, vmi);
		cum_waiting_time[i] = 0;
		cum_response_time[i] = 0;
		cum_queue_length[i] = 0;
		delayed_customers[i] = 0;
		total_departures[i] = 0;
    }

	service_rate = ssdata->getFixedServiceRate(vmi);
	index = vmi;
	busy = false;
	last_update_time = 0;

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
	index = vm.index;

	cum_waiting_time = vm.cum_waiting_time;
	cum_response_time = vm.cum_response_time;
	cum_queue_length = vm.cum_queue_length;

	list<float>::const_iterator it;
	server_queue.clear();
	for(it= (vm.server_queue).begin(); it!=(vm.server_queue).end(); it++)
		server_queue.push_back(*it);
}

int VM :: getIndex()
{
	return index;
}

float VM :: getNextInterArrivalTime(int phase_num)
{
	return expon(1/arrival_rate[phase_num%num_phases]);
}

float VM :: getNextServiceTime(SimSData *ssdata, Policy* policy, int phase_num, float sim_time, bool mig)
{
	int mod_phase_num = phase_num%num_phases;
	float st = expon(1/service_rate);
	vector<int> vm_to_pm_map = policy->getMapping(mod_phase_num);
	vector<int> mig_list = policy->getMigrationList(mod_phase_num);
	int pm = vm_to_pm_map[index];

	float sum_rho = 0;
	for(int i=0; i<ssdata->getNumVM(); i++)
	{
		if(vm_to_pm_map[i] == pm)
			sum_rho += (ssdata->getArrivalRate(mod_phase_num, i)/ssdata->getFixedServiceRate(i));

		if(mig)
			if((mig_list[i] == pm) || ((mig_list[i] != -1) && (vm_to_pm_map[i] == pm)))
				sum_rho += MOHCPUINTENSIVE * (ssdata->getArrivalRate(mod_phase_num, i)/ssdata->getFixedServiceRate(i));
	}

	st = st/(arrival_rate[mod_phase_num]/service_rate)*sum_rho;
	*st_file << sim_time << "\t" << st << endl;
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


float VM :: getAvgWaitingTime(int phase_num)
{
	return cum_waiting_time[phase_num]/delayed_customers[phase_num];
}

float VM :: getAvgResponseTime(int phase_num)
{
	return (cum_response_time[phase_num]/total_departures[phase_num]);
}

float VM :: getAvgQLength(int phase_num)
{
	return (cum_queue_length[phase_num]/PHASE_DURATION;
}

int VM :: getTotalReqs()
{
	return total_reqs;
}

void VM :: update_on_arrival(float current_time, float serv_time, int phase_num)
{
	phase_num %= num_phases;
	total_reqs++;
	if(busy)
	{
		server_queue.push_back(current_time);
		cum_queue_length[phase_num] += server_queue.size() * (current_time - last_update_time);
		last_update_time = current_time;
	} else
	{
		busy = true;
		total_departures[phase_num]++;
		cum_response_time[phase_num] += serv_time;
	}
}

void VM :: update_on_departure(float current_time, float serv_time, int phase_num)
{
    phase_num %= num_phases;
	if(server_queue.size() > 0)
	{
		delayed_customers[phase_num]++; cum_waiting_time[phase_num] += current_time - server_queue.front();
		total_departures[phase_num]++; cum_response_time[phase_num] += serv_time + current_time - server_queue.front();
		server_queue.pop_front();
	} else
		busy = false;

	cum_queue_length[phase_num] += server_queue.size() * (current_time - last_update_time);
	last_update_time = current_time;
}

void VM :: stop()
{
	st_file->close();
}

VM :: ~VM()
{
	delete [] arrival_rate;
	delete st_file;
}

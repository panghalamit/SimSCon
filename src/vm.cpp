#include "vm.h"

VM::VM(SimSData *ssdata, int vmi)
{
	num_phases = ssdata->getNumPhases();
	num_vms = ssdata->getNumVM();
	index = vmi;
	threshold = ssdata->getResponseLimit(index);
	revenue = ssdata->getVmRevenue(index);
	penalty = ssdata->getVmPenalty(index);

	arrival_rate = new float[num_phases];
	cum_waiting_time = new float[num_phases];
	cum_response_time = new float[2*num_phases];
	cum_queue_length = new float[num_phases];
	delayed_customers = new int[num_phases];
	total_departures = new int[2*num_phases];
	total_dep_phase = new int[num_phases];
	last_update_time = new float[num_phases];
	total_reqs = new int[num_phases];
	num_sla_violated = new int[num_phases];
	profit = new float[num_phases];

	for(int i=0; i<num_phases; i++)
	{
		arrival_rate[i] = ssdata->getArrivalRate(i, vmi);
		cum_waiting_time[i] = 0;
		cum_queue_length[i] = 0;
		delayed_customers[i] = 0;
		total_dep_phase[i] = 0;
		last_update_time[i] = 0;
		total_reqs[i] = 0;
		num_sla_violated[i] = 0;
		profit[i] = 0;
    }
    for(int i=0; i<2*num_phases; i++)
	{
		cum_response_time[i] = 0;
		total_departures[i] = 0;
    }
	service_rate = ssdata->getFixedServiceRate(vmi);

	busy = false;
	st_file = new ofstream((string("results/service_time_vm") +
						static_cast<ostringstream*>(&(ostringstream()<<index))->str() + string(".txt")).c_str());
	rt_file = new ofstream((string("results/response_time_vm") +
						static_cast<ostringstream*>(&(ostringstream()<<index))->str() + string(".txt")).c_str());
	if(!(st_file->is_open() && rt_file->is_open()))
	{
		cout<<"error occured, cannot open file!"<<endl;
		exit(1);
	}
}

int VM::getIndex() { return index;}
float VM::getArrivalRate(int phase_num) { return arrival_rate[phase_num];}
float VM::getServiceRate() { return service_rate;}
float VM::getNextInterArrivalTime(int phase_num) { return expon(1/arrival_rate[phase_num]);}

float VM::getNextServiceTime(SimSData *ssdata, Policy* policy, int phase_num, float sim_time, bool mig)
{
	float st = expon(1/service_rate);
	vector<int>* vm_to_pm_map = new vector<int>(num_vms, -1);
	vector<int>* mig_list = new vector<int>(num_vms, -1);
	policy->getMigrationList(phase_num, mig_list);
	policy->getMapping(phase_num, vm_to_pm_map);
	int pm = (*vm_to_pm_map)[index];

	float sum_rho = 0;
	for(int i=0; i<num_vms; i++)
	{
		if((*vm_to_pm_map)[i] == pm)
			sum_rho += (ssdata->getArrivalRate(phase_num, i)/ssdata->getFixedServiceRate(i));

		if(mig)
			if(((*mig_list)[i] == pm) || (((*mig_list)[i] != -1) && ((*vm_to_pm_map)[i] == pm)))
				sum_rho += MOHCPUINTENSIVE * (ssdata->getArrivalRate(phase_num, i)/ssdata->getFixedServiceRate(i));
	}

	st = st/(arrival_rate[phase_num]/service_rate)*sum_rho;
	*st_file << sim_time << "\t" << st << endl;

	delete vm_to_pm_map;
	delete mig_list;
	return st;
}

int VM::getTotalReqs(int phase_num) { return total_reqs[phase_num];}
bool VM::isIdle() {	return !busy;}
bool VM::isEmptyQueue() { return (server_queue.size() == 0);}

float VM::getTopInQ()
{
	if(server_queue.size()==0)
	{
		cout<<"illegal access: server queue empty"<<endl;
		exit(0);
	}

	return server_queue.front();
}

void VM::updateOnArrival(float current_time, float serv_time, int phase_num, bool mig)
{
	total_reqs[phase_num]++;
	if(busy)
	{
		server_queue.push_back(current_time);
		cum_queue_length[phase_num] += server_queue.size() * (current_time - last_update_time[phase_num]);
		last_update_time[phase_num] = current_time;
	} else
	{
		busy = true;
		delayed_customers[phase_num]++;
		total_departures[phase_num*2+mig]++; total_dep_phase[phase_num]++; cum_response_time[phase_num*2+mig] += serv_time;
		*rt_file << current_time << "\t" << serv_time << endl;
		if(serv_time > threshold)
			num_sla_violated[phase_num]++;
	}
}

void VM::updateOnDeparture(float current_time, float serv_time, int phase_num, bool mig)
{
	if(server_queue.size() > 0)
	{
		delayed_customers[phase_num]++; cum_waiting_time[phase_num] += current_time - server_queue.front();
		float response_time = serv_time + current_time - server_queue.front();
		total_departures[phase_num*2+mig]++; total_dep_phase[phase_num]++; cum_response_time[phase_num*2+mig] += response_time;
		*rt_file << current_time << "\t" << response_time << endl;
		server_queue.pop_front();
		if(response_time > threshold)
			num_sla_violated[phase_num]++;
	} else
		busy = false;

	cum_queue_length[phase_num] += server_queue.size() * (current_time - last_update_time[phase_num]);
	last_update_time[phase_num] = current_time;
}

void VM::updateOnPhaseChange(float current_time, int phase_num)
{
	cum_queue_length[phase_num] += server_queue.size() * (current_time - last_update_time[phase_num]);
	last_update_time[phase_num] = current_time;

	if(total_dep_phase[phase_num] != 0)
		profit[phase_num] += (-num_sla_violated[phase_num]*penalty + (total_dep_phase[phase_num]-num_sla_violated[phase_num])*revenue)/total_dep_phase[phase_num] * PHASE_LENGTH;
	else
		profit[phase_num] += revenue * PHASE_LENGTH;
	num_sla_violated[phase_num] = 0;
	total_dep_phase[phase_num] = 0;
}

float VM::getAvgWaitingTime(int phase_num)
{
	return cum_waiting_time[phase_num]/delayed_customers[phase_num];
}

float VM::getAvgResponseTime(int phase_num, bool mig)
{
	return (cum_response_time[phase_num*2+mig]/total_departures[phase_num*2+mig]);
}

float VM::getAvgQLength(int phase_num, float current_time)
{
	int num_p = current_time/PHASE_LENGTH/num_phases;
	float total_phase_time = num_p*PHASE_LENGTH;
	if((int)current_time % (PHASE_LENGTH*num_phases) >= (phase_num+1) * PHASE_LENGTH)
		num_p += 1;
	else if((int)current_time % PHASE_LENGTH >= phase_num * PHASE_LENGTH)
	{
		cum_queue_length[phase_num] += (current_time - last_update_time[phase_num]) * server_queue.size();
		total_phase_time += current_time - last_update_time[phase_num];
	}

	return (cum_queue_length[phase_num]/total_phase_time);
}

float VM::getAvgProfit(int phase_num, float current_time)
{
	int num_p = current_time/(PHASE_LENGTH*num_phases);
	if(((int)current_time) % (PHASE_LENGTH*num_phases) >= (phase_num+1) * PHASE_LENGTH)
		num_p +=1;

	return (profit[phase_num]/num_p);
}

float VM::getOverallResponseTime()
{
	float overall_cum_response_time = 0;
	float overall_total_departures = 0;
	for(int i=0; i<2*num_phases; i++)
	{
		overall_cum_response_time += cum_response_time[i];
		overall_total_departures += total_departures[i];
	}

	return overall_cum_response_time/overall_total_departures;
}

float VM::getOverallWaitingTime()
{
	float overall_cum_waiting_time = 0;
	float overall_delayed_customers = 0;
	for(int i=0; i<num_phases; i++)
	{
		overall_cum_waiting_time += cum_waiting_time[i];
		overall_delayed_customers += delayed_customers[i];
	}

	return overall_cum_waiting_time/overall_delayed_customers;
}

float VM::getOverallQueueLength(float current_time)
{
	float overall_cum_queue_length = 0;
	for(int i=0; i<num_phases; i++)
		overall_cum_queue_length += cum_queue_length[i];

	return overall_cum_queue_length/current_time;
}

float VM::getOverallProfit()
{
	float total_profit = 0;
	for(int i=0; i<num_phases; i++)
		total_profit += profit[i];

	return total_profit;
}

void VM::stop()
{
	st_file->close();
	rt_file->close();
}

VM::~VM()
{
	delete [] arrival_rate;
	delete [] cum_waiting_time;
	delete [] cum_response_time;
	delete [] cum_queue_length;
	delete [] delayed_customers;
	delete [] total_departures;
	delete [] total_dep_phase;
	delete [] last_update_time;
	delete [] total_reqs;
	delete [] num_sla_violated;
	delete [] profit;
	delete st_file;
	delete rt_file;
}

#include "simulation.h"

Simulation :: Simulation(SimData *sdata)
{
	s_data = sdata;
	for(int i=0; i<sdata->getNumVM(); i++)
		vmlist.push_back(new VM(sdata->getArrivalRate(i), sdata->getFixedServiceRate(i), i));

	policy = new int*[sdata->getNumPhases()];
	for(int i=0; i<sdata->getNumPhases(); i++)
	{
		policy[i] = new int[sdata->getNumVM()];\
		for(int j=0; j<sdata->getNumPhases(); j++)
			policy[i][j] = 0;
	}
}

void Simulation :: start()
{
	for(unsigned int i=0; i<vmlist.size(); i++)
		event_list.push(Event(ARRIVAL, vmlist[i]->getNextInterArrivalTime(), vmlist[i]->getIndex()));
	cout<<"Yay!! Simulation started..."<<endl;
}

void Simulation :: run(double stop_time)
{
	while(!event_list.empty())
	{
		Event e = event_list.top();
		sim_time = e.getTime();
		float serv_time = -1;
		int phase_number = ((int) (sim_time/PHASE_LENGTH)) % s_data->getNumPhases();
		if(sim_time > stop_time)
			break;
		e.printDetails();
		if(e.getEventType() == ARRIVAL)
		{
			event_list.push(Event(ARRIVAL, sim_time+vmlist[e.getVMIndex()]->getNextInterArrivalTime(), e.getVMIndex()));
			if(vmlist[e.getVMIndex()]->ifIdle())
			{
				serv_time = vmlist[e.getVMIndex()]->getNextServiceTime(s_data, policy[phase_number]);
				event_list.push(Event(DEPARTURE, sim_time+serv_time, e.getVMIndex()));

			}
			vmlist[e.getVMIndex()]->update_on_arrival(sim_time, serv_time);
		}
		else if(e.getEventType() == DEPARTURE)
		{
			if(!vmlist[e.getVMIndex()]->ifIdle())
				event_list.push(Event(DEPARTURE, vmlist[e.getVMIndex()]->getTopInQ()+vmlist[e.getVMIndex()]->getNextServiceTime(s_data, policy[phase_number]), e.getVMIndex()));
			vmlist[e.getVMIndex()]->update_on_departure(sim_time);
		}
		event_list.pop();
	}

	cout<<"Simulation completed..."<<endl;
}

void Simulation :: stop ()
{
	for(unsigned int i=0; i<vmlist.size(); i++)
	{
		vmlist[i]->stop();
		delete vmlist[i];
	}

	for(int i=0; i<s_data->getNumPhases(); i++)
		delete [] policy[i];
	delete [] policy;
}

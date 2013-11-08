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
		event_list.push(Event(ARRIVAL, 0, vmlist[i]->getIndex()));
	cout<<"Yay!! Simulation started..."<<endl;
}

void Simulation :: run(double stop_time)
{
	while(!event_list.empty())
	{
		Event e = event_list.top();
		if(e.getTime() > stop_time)
			break;

		e.printDetails();
		if(e.getEventType() == ARRIVAL)
		{
			float current_time = e.getTime();
			int phase_number = ((int) (current_time/PHASE_LENGTH)) % s_data->getNumPhases();
			event_list.push(Event(ARRIVAL, current_time+vmlist[e.getVMIndex()]->getNextInterArrivalTime(), e.getVMIndex()));
			event_list.push(Event(DEPARTURE, current_time+vmlist[e.getVMIndex()]->getNextServiceTime(s_data, policy[phase_number]), e.getVMIndex()));
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

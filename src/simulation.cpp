#include "simulation.h"

Simulation :: Simulation(vector<VM*> v)
{
	for(unsigned int i=0; i<vmlist.size(); i++)
		vmlist[i] = v[i];
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
			event_list.push(Event(ARRIVAL, e.getTime()+vmlist[e.getVMIndex()]->getNextInterArrivalTime(), e.getVMIndex()));
			event_list.push(Event(DEPARTURE, e.getTime()+vmlist[e.getVMIndex()]->getNextServiceTime(), e.getVMIndex()));
		}
		event_list.pop();
	}

	cout<<"Simulation completed \\m/"<<endl;
}

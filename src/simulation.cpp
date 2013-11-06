#include "simulation.h"



Simulation :: Simulation(double *ar, double sr, int numvm)
{
	for(int i=0; i<numvm; i++)
		vmlist[i] = new VM(ar, sr, i);
	event_list.push(new Event(ARRIVAL, 0, 0));
}
void Simulation :: start()
{
	while(!event_list.empty())
	{
		Event * e = event_list.top();

		Event * new_event = getNextEvent(e);

		event_list.pop();

        event_list.push(new_event);

		delete e;
	}
}

Event * Simulation :: getNextEvent(Event * e)
{
	if(e->getEventType() == ARRIVAL)
	{
		return new Event(ARRIVAL, e->getTime()+(vmlist[e->getVMIndex()])->getNextArrivalTime(e->getTime()), e->getVMIndex());
	}
	else 
	{
		return new Event(DEPARTURE, e->getTime()+(vmlist[e->getVMIndex()])->getNextDepartureTime(e->getTime()), e->getVMIndex());
	}
}

Simulation :: ~Simulation()
{
	vmlist.clear();
}

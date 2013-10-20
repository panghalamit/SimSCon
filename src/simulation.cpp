#include "simulation.h"


Simulation :: Simulation(double *ar, double sr)
{
	vm = new VM(ar, sr);
	event_list.push(new Event(ARRIVAL, 0));
}

void Simulation :: start()
{
	while(!event_list.empty())
	{
		Event * e = event_list.top();

		if(e->getEventType() == ARRIVAL)
		{

		}
		else
		{
			
		}

		event_list.pop();
		delete e;
	}
}


Simulation :: ~Simulation()
{
	delete vm;
}

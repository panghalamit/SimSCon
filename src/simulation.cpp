#include "simulation.h"

Simulation :: Simulation(VM* v)
{
	vm = v;
}

void Simulation :: start()
{
	event_list.push(Event(ARRIVAL, 0, vm->getIndex()));
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
			event_list.push(Event(ARRIVAL, e.getTime()+vm->getNextInterArrivalTime(), vm->getIndex()));
			event_list.push(Event(DEPARTURE, e.getTime()+vm->getNextServiceTime(), vm->getIndex()));
		}
		event_list.pop();
	}

	cout<<"Simulation completed \\m/"<<endl;
}

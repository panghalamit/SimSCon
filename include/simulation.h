#ifndef SIMULATION_H
#define SIMULATION_H 

#include <queue>
#include <vector>
#include <iostream>
#include "event.h"
#include "vm.h"
using namespace std;

class Simulation
{
	VM *vm;
	priority_queue<Event> event_list;
  public:
	Simulation(VM*);
	Event getNextEvent(Event);
	void start();
	void run(double stop_time);
};

#endif

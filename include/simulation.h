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
	private:
		priority_queue<Event *> event_list;
		vector<VM*> vmlist;
	public:
		Simulation(double *, double, int);
		Event * getNextEvent(Event * );
		void start();
		~Simulation();
};

#endif

#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include <iostream>
#include "config.h"
#include "event.h"
#include "vm.h"
#include "simdata.h"
using namespace std;

class Simulation
{
	vector<VM*> vmlist;
	priority_queue<Event> event_list;
	SimData *s_data;
	int **policy;

  public:
	Simulation(SimData *);
	Event getNextEvent(Event);
	void start();
	void run(double);
	void stop();
};

#endif

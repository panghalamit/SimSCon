#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include "config.h"
#include "event.h"
#include "vm.h"
#include "simdata.h"
#include "policy.h"
using namespace std;

class Simulation
{
	vector<VM*> vmlist;
	priority_queue<Event> event_list;
	SimData *s_data;
	Policy *policy;
	float sim_time;
	bool migration_phase;

  public:
	Simulation(SimData *);
	void start();
	void run(double);
	void stop();
};

#endif

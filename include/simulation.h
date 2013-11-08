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
using namespace std;

class Simulation
{
	vector<VM*> vmlist;
	priority_queue<Event> event_list;
	SimData *s_data;
	int **policy;
	float sim_time;

  public:
	Simulation(SimData *);
	void start();
	void run(double);
	void stop();
};

#endif

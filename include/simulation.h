#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "config.h"
#include "event.h"
#include "vm.h"
#include "simsdata.h"
#include "policy.h"
#include "staticmap.h"
#include "simdata.h"
using namespace std;

class Simulation
{
	vector<VM*> vmlist;
	priority_queue<Event> event_list;
	SimSData *ssdata;
	Policy *policy;
	float sim_time;
	int phase_num;
	bool migration_phase;

  public:
	Simulation(SimSData*);
	~Simulation();
	void start();
	void run(double);
	void stop();
};

#endif

#ifndef VM_H
#define VM_H

#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <list>
#include "simsdata.h"
#include "common.h"

#include "config.h"
#include "policy.h"
#include "khanna.h"
#include "simdata.h"
using namespace std;

class VM
{
	float *arrival_rate;
	float service_rate;
	int index;
	int num_phases;
	ofstream *st_file;
	bool busy;
	list<float> server_queue;
	float cum_waiting_time; int delayed_customers;
	float cum_response_time; int total_departures;
	float cum_queue_length; float last_update_time;
	int total_reqs;

  public:
	VM(SimSData*, int);
	~VM();
	VM(const VM&);
	float getArrivalRate(int phase_num);
	float getServiceRate();
	float getNextInterArrivalTime(int phase_num);
	float getNextServiceTime(SimSData*, Policy*, int, float, bool);
	int getIndex();
	float getAvgWaitingTime();
	float getAvgResponseTime();
	float getAvgQLength(float);
	int getTotalReqs();
	bool isIdle();
	bool isEmptyQueue();
	float getTopInQ();
	void update_on_arrival(float, float);
	void update_on_departure(float, float);
	void stop();
};

#endif

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
#include "simdata.h"
using namespace std;

class VM
{
	int index;
	float threshold;
	float revenue;
	float penalty;
	float *arrival_rate;
	float service_rate;
	float *cum_waiting_time; int *delayed_customers;
	float *cum_response_time; int *total_departures;
	float *cum_queue_length; float *last_update_time;
	int *total_reqs;
	int *num_sla_violated;
	float *profit;
	ofstream *st_file;
	ofstream *rt_file;
	bool busy;
	list<float> server_queue;

  public:
  	int num_phases;
	VM(SimSData*, int);
	~VM();
	int getIndex();
	float getArrivalRate(int phase_num);
	float getServiceRate();
	float getNextInterArrivalTime(int phase_num);
	float getNextServiceTime(SimSData*, Policy*, int, float, bool);
	int getTotalReqs(int);
	bool isIdle();
	bool isEmptyQueue();
	float getTopInQ();
	void updateOnArrival(float, float, int);
	void updateOnDeparture(float, float, int);
	void updateOnPhaseChange(float, int);
	float getAvgWaitingTime(int);
	float getAvgResponseTime(int);
	float getAvgQLength(int, float);
	float getAvgProfit(int, float);
	float getOverallResponseTime();
	float getOverallWaitingTime();
	float getOverallQueueLength(float);
	float getOverallProfit(float);
	void stop();
};

#endif

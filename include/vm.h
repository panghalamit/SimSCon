#ifndef VM_H
#define VM_H

#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <list>
#include "simdata.h"
#include "common.h"
using namespace std;

class VM
{
	float arrival_rate;
	float service_rate;
	int index;
	ofstream *st_file;
	list<float> server_queue;
	float avg_waiting_time;
	float avg_response_time;
	float avg_queue_length;
	int total_reqs;
  public:
	VM(float, float, int);
	~VM();
	VM(const VM&);
	float getArrivalRate();
	float getServiceRate();
	float getNextInterArrivalTime();
	float getNextServiceTime(SimData*, int*);
	int getIndex();
	float getAvgWaitingTime();
	float getAvgResponseTime();
	float getAvgQLength();
	int getTotalReqs();
	bool ifIdle();
	float getTopInQ();
	void update_on_arrival(float, float);
	void update_on_departure(float);
	void stop();
};

#endif

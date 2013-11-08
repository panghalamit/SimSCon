#ifndef VM_H
#define VM_H

#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include "simdata.h"
#include "common.h"
using namespace std;

class VM
{
	float arrival_rate;
	float service_rate;
	int index;
	ofstream *st_file;

  public:
	VM(float, float, int);
	~VM();
	VM(const VM&);
	float getArrivalRate();
	float getServiceRate();
	float getNextInterArrivalTime();
	float getNextServiceTime(SimData*, int*);
	int getIndex();
	void stop();
};

#endif

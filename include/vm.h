#ifndef VM_H
#define VM_H

#include "common.h"

class VM
{
	double arrival_rate;
	double service_rate;
	int index;
  public:
	VM(double, double, int);
	VM(const VM&);
	double getArrivalRate();
	double getServiceRate();
	double getNextInterArrivalTime();
	double getNextServiceTime();
	int getIndex();
};

#endif

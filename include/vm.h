#include "common.h"

class VM
{
private:
	double *arrival_rates;
	double service_rate;
	int index;
public:
	VM(double *ar, double sr, int i);
	double getArrivalRate(int time);
	double getServiceRate();
	double getNextArrivalTime(double time);
	double getNextDepartureTime(double time);
	int getIndex();
	~VM();
};

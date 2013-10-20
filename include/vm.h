

class VM
{
private:
	double *arrival_rates;
	double service_rate;
public:
	VM(double *ar, double sr);
	double getArrivalRate(int time);
	double getServiceRate();
	~VM();
};

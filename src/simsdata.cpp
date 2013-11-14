#include "simsdata.h"

SimSData :: SimSData(int num_vms, int num_phases)
{
	this->num_vms = num_vms;
	this->num_phases = num_phases;
	this->arrival_rates = new float[num_vms];
	this->service_rates = new float[num_vms];
	sdata = new SimData(num_vms, num_phases);
}

void SimSData :: readInput()
{
	sdata->readInput();
	for (int i=0; i<num_vms; i++) { cin>>arrival_rates[i];}
	for (int i=0; i<num_vms; i++) { cin>>service_rates[i];}
}

int SimSData :: getNumVM() { return num_vms;}
int SimSData :: getNumPhases() { return num_phases;}
float SimSData :: getArrivalRate(int vmi) { return arrival_rates[vmi];}
float SimSData :: getFixedServiceRate(int vmi) {return service_rates[vmi];}

SimSData :: ~SimSData()
{
	delete [] service_rates;
	delete [] arrival_rates;
	delete sdata;
}

SimData* SimSData :: getSimData()
{
	return sdata;
}

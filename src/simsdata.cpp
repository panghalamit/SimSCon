#include "simdata.h"

SimData::SimData(int num_vms, int num_phases)
{
	this->num_vms = num_vms;
	this->num_phases = num_phases;
	this->arrival_rates = new float[num_vms];
	this->service_rates = new float[num_vms];
}

void SimData::readInput()
{
	for (int i=0; i<num_vms; i++) { cin>>arrival_rates[i];}
	for (int i=0; i<num_vms; i++) { cin>>service_rates[i];}
}

int SimData::getNumVM() { return num_vms;}
int SimData::getNumPhases() { return num_phases;}
float SimData::getArrivalRate(int vmi) {return arrival_rates[vmi];}
float SimData::getFixedServiceRate(int vmi) {return service_rates[vmi];}

SimData::~SimData()
{
	delete [] service_rates;
	delete [] arrival_rates;
}

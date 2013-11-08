#include "simdata.h"

SimData::SimData(int num_vms, int num_phases)
{
	this->num_vms = num_vms;
	this->num_phases = num_phases;
 #if DSCP_ON
	this->workload = new Matrix<float>(num_phases, num_vms);
	this->vm_revenue = new float[num_vms];
	this->vm_penalty = new float[num_vms];
 #endif
	this->arrival_rates = new float[num_vms];
	this->service_rates = new float[num_vms];
}

void SimData::readInput()
{
 #if DSCP_ON
	for(int i=0; i<num_phases; i++)
		for(int j=0; j<num_vms; j++)
			cin>>(*workload)(i, j);
	for (int i=0; i<num_vms; i++) { cin>>vm_revenue[i];}
	for (int i=0; i<num_vms; i++) { cin>>vm_penalty[i];}
 #endif
	for (int i=0; i<num_vms; i++) { cin>>arrival_rates[i];}
	for (int i=0; i<num_vms; i++) { cin>>service_rates[i];}
}

int SimData::getNumVM() { return num_vms;}
int SimData::getNumPhases() { return num_phases;}
#if DSCP_ON
float SimData::getWorkload(int phase, int vm) { return (*workload)(phase, vm);}
float SimData::getVmRevenue(int vm) { return vm_revenue[vm];}
float SimData::getVmPenalty(int vm) { return vm_penalty[vm];}
#endif
float SimData::getArrivalRate(int vmi) {return arrival_rates[vmi];}
float SimData::getFixedServiceRate(int vmi) {return service_rates[vmi];}

SimData::~SimData()
{
 #if DSCP_ON
	delete workload;
	delete [] vm_revenue;
	delete [] vm_penalty;
 #endif
	delete [] service_rates;
	delete [] arrival_rates;
}

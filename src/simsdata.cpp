#include "simsdata.h"

SimSData::SimSData(int num_vms, int num_phases)
{
	this->num_vms = num_vms;
	this->num_phases = num_phases;
	this->arrival_rates = new Matrix<float>(num_phases, num_vms);
	this->service_rates = new float[num_vms];
	this->response_limit = new float[num_vms];
	sdata = new SimData(num_vms, num_phases);
}

void SimSData::readInput()
{
	float temp;
	for (int i=0; i<num_vms; i++) { cin>>temp; sdata->setVmRevenue(i, temp);}
	for (int i=0; i<num_vms; i++) { cin>>temp; sdata->setVmPenalty(i, temp);}

	for(int j=0; j<num_vms; j++)
		for(int i=0; i<num_phases; i++)
	 		cin>>(*arrival_rates)(i, j);

	for(int i=0; i<num_vms; i++)
	 	cin>>service_rates[i];

	for(int i=0; i<num_vms; i++)
	 	cin>>response_limit[i];

	for(int i=0; i<num_phases; i++)
		for(int j=0; j<num_vms; j++)
			sdata->setWorkload(i, j, ((*arrival_rates)(i,j)/service_rates[j]));
}

int SimSData::getNumVM() { return num_vms;}
int SimSData::getNumPhases() { return num_phases;}
float SimSData::getArrivalRate(int phase_number, int vmi) { return (*arrival_rates)(phase_number, vmi);}
float SimSData::getFixedServiceRate(int vmi) { return service_rates[vmi];}
float SimSData::getVmRevenue(int vm) { return sdata->getVmRevenue(vm);}
float SimSData::getVmPenalty(int vm) { return sdata->getVmPenalty(vm);}
float SimSData::getResponseLimit(int vm) { return response_limit[vm];}

SimSData::~SimSData()
{
	delete [] service_rates;
	delete arrival_rates;
	delete [] response_limit;
	delete sdata;
}

SimData* SimSData::getSimData()
{
	return sdata;
}

#include "simsdata.h"

SimSData :: SimSData(int num_vms, int num_phases)
{
	this->num_vms = num_vms;
	this->num_phases = num_phases;
	this->arrival_rates = new Matrix<float>(num_phases, num_vms);
	this->service_rates = new float[num_vms];
	sdata = new SimData(num_vms, num_phases);
}

void SimSData :: readInput()
{
	float temp;
	for (int i=0; i<num_vms; i++) { cin>>temp; sdata->setVmRevenue(i, temp);}
	for (int i=0; i<num_vms; i++) { cin>>temp; sdata->setVmPenalty(i, temp);}

	for(int i=0; i<num_phases; i++)
		for(int j=0; j<num_vms; j++)
	 		cin>>(*arrival_rates)(i, j);

	for(int i=0; i<num_vms; i++)
	 	cin>>service_rates[i];

	for(int i=0; i<num_phases; i++)
		for(int j=0; j<num_vms; j++)
			sdata->setWorkload(i, j, ((*arrival_rates)(i,j)/service_rates[j]));
}

int SimSData :: getNumVM() { return num_vms;}
int SimSData :: getNumPhases() { return num_phases;}
float SimSData :: getArrivalRate(int phase_number, int vmi) { return (*arrival_rates)(phase_number, vmi);}
float SimSData :: getFixedServiceRate(int vmi) { return service_rates[vmi];}

SimSData :: ~SimSData()
{
	delete [] service_rates;
	delete arrival_rates;
	delete sdata;
}

SimData* SimSData :: getSimData()
{
	return sdata;
}

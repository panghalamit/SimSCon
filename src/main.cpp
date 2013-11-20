#include <iostream>
#include <vector>
#include "simulation.h"
#include "simdata.h"
#include "vm.h"

int main()
{
	int num_vms, num_phases;
	cin>>num_vms>>num_phases;
	SimSData *ssdata = new SimSData(num_vms, num_phases);
	ssdata->readInput();

	setStream(14);
	Simulation sim(ssdata);
	sim.start();
	sim.run(3*3600);
	sim.stop();
	delete ssdata;
	return 0;
}

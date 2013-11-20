#include <iostream>
#include <vector>
#include <cstdlib>
#include "simulation.h"
#include "simdata.h"
#include "vm.h"

int main()
{
	int num_vms, num_phases;
	cin>>num_vms>>num_phases;
	SimSData *ssdata = new SimSData(num_vms, num_phases);
	ssdata->readInput();

	int Stream = atoi(getenv("STREAM"));
	setStream(Stream);
	cout<<endl<<"*** running for stream="<<Stream<<endl;
	Simulation sim(ssdata);
	sim.start();
	sim.run(6*3600);
	sim.stop();
	delete ssdata;
	return 0;
}

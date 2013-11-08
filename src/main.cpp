#include <iostream>
#include <vector>
#include "simulation.h"
#include "simdata.h"
#include "vm.h"

int main()
{
	int num_vms, num_phases;
	cin>>num_vms>>num_phases;
	SimData *s_data = new SimData(num_vms, num_phases);
	s_data->readInput();

	Simulation sim(s_data);
	sim.start();
	sim.run(50);
	sim.run(100);
	sim.stop();

	delete s_data;
	return 0;
}

#include <iostream>
#include <vector>
#include "simulation.h"
#include "simdata.h"
#include "vm.h"

int main()
{
	int num_vms, num_phases;
	cin>>num_vms>>num_phases;
	cout<<__LINE__<<endl;
	SimData *s_data = new SimData(num_vms, num_phases);
	cout<<__LINE__<<endl;
	s_data->readInput();
	cout<<__LINE__<<endl;
	Simulation sim(s_data);
	cout<<__LINE__<<endl;
	sim.start();
	sim.run(50);
	sim.run(100);
	delete s_data;
	return 0;
}

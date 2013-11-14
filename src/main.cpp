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

	Simulation sim(ssdata);

	for(int i=0; i<200; i++)
	{
		setStream(i);
		sim.start();
		sim.run(200);
		sim.stop();
		system(string("cat results/stats.txt >> results/out.txt").c_str()) ;
	}

	delete ssdata;
	return 0;
}

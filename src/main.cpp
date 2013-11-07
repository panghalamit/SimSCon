#include <iostream>
#include <vector>
#include "simulation.h"
#include "vm.h"

int main()
{
	vector<VM*> vml;
	vml[0] = new VM(0.5, 0.6, 0);
	vml[1] = new VM(0.3, 0.4, 1);
	Simulation sim(vml);
	sim.start();
	sim.run(50);
	sim.run(100);
	return 0;
}

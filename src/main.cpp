#include <iostream>
#include "simulation.h"
#include "vm.h"

int main()
{
	VM vm(0.5, 0.6, 0);
	Simulation sim(&vm);
	sim.start();
	sim.run(50);
	sim.run(100);
	return 0;
}

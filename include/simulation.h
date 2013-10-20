#include <queue>
#include <iostream>
#include "event.h"
#include "vm.h"

using namespace std;

class Simulation
{
	private:
		priority_queue<Event *> event_list;
		VM * vm;
	public:
		Simulation(double *, double);
		void start();
		~Simulation();
};

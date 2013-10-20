#include <iostream>
#include "simulation.h"


int main()
{
	int N;
	cin>>N;
	double *arr = new double[N];
	double sr;
	for(int i=0; i<N; i++)
		cin>>arr[i];
	cin>>sr;
	Simulation * sim = new Simulation(arr, sr);
	sim->start();
	return 0;
}
#include <iostream>
#include "simulation.h"


int main()
{
	int N, st;
	long seed;
	cin>>N;
	double *arr = new double[N];
	double sr;
	for(int i=0; i<N; i++)
		cin>>arr[i];
	cin>>sr;
	cin>>st>>seed;
	setStream(st);
	lcgrandst (seed, st);
	Simulation * sim = new Simulation(arr, sr, N);
	sim->start();
	return 0;
}
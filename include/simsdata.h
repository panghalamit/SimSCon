/*
This class handles the input data. It reads from standard
input stream and provides API to access the data
*/

#ifndef SIMDATA_H
#define SIMDATA_H

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class SimData
{
    int num_vms;
    int num_phases;
    float *arrival_rates;
    float *service_rates;

  public:
    SimData(int, int);
    ~SimData();
    void readInput();
    int getNumVM();
    int getNumPhases();
    float getArrivalRate(int);
    float getFixedServiceRate(int);
};

#endif
